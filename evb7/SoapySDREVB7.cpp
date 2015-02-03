//
// SoapySDR wrapper for the LMS7002M driver.
//
// Copyright (c) 2015-2015 Fairwaves, Inc.
// Copyright (c) 2015-2015 Rice University
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
//

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Registry.hpp>
#include <SoapySDR/Logger.hpp>
#include <pothos_zynq_dma_driver.h>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

#include <LMS7002M/LMS7002M.h>
#include <LMS7002M/LMS7002M_impl.h>
#include "spidev_interface.h"
#include "sysfs_gpio_interface.h"
#include "xilinx_user_gpio.h"
#include "xilinx_user_mem.h"

#define EMIO_OFFSET 54
#define RESET_EMIO    (EMIO_OFFSET+0)
#define DIG_RST_EMIO  (EMIO_OFFSET+1)
#define RXEN_EMIO     (EMIO_OFFSET+2)
#define TXEN_EMIO     (EMIO_OFFSET+3)
#define DIO_DIR_CTRL1_EMIO   (EMIO_OFFSET+4)
#define DIO_DIR_CTRL2_EMIO   (EMIO_OFFSET+5)
#define IQSEL1_DIR_EMIO      (EMIO_OFFSET+6)
#define IQSEL2_DIR_EMIO      (EMIO_OFFSET+7)

#define SET_EMIO_OUT_LVL(emio, lvl) \
    gpio_export(emio); \
    gpio_set_dir(emio, 1); \
    gpio_set_value(emio, lvl)

#define CLEANUP_EMIO(emio) \
    gpio_set_dir(emio, 0); \
    gpio_unexport(emio)

#define FPGA_REGS 0x43C00000
#define FPGA_REGS_SIZE 1024

#define FPGA_REG_RD_SENTINEL 0 //readback a known value
#define FPGA_REG_RD_RX_CLKS 8 //sanity check clock counter
#define FPGA_REG_RD_TX_CLKS 12 //sanity check clock counter
#define FPGA_REG_RD_TIME_LO 16
#define FPGA_REG_RD_TIME_HI 20
#define FPGA_REG_RD_RX_CHA 28
#define FPGA_REG_RD_RX_CHB 32

#define FPGA_REG_WR_EXT_RST 12 //active high external reset
#define FPGA_REG_WR_TIME_LO 16
#define FPGA_REG_WR_TIME_HI 20
#define FPGA_REG_WR_TIME_LATCH 24
#define FPGA_REG_WR_TX_CHA 28
#define FPGA_REG_WR_TX_CHB 32
#define FPGA_REG_WR_TX_TEST 36

#define RX_DMA_INDEX 0
#define TX_DMA_INDEX 1
#define RX_FRAME_SIZE 1000 //buff size - hdrs
#define TX_FRAME_SIZE 1000 //buff size - hdrs

#define DATA_NUM_BUFFS 16
#define DATA_BUFF_SIZE 4096

#define CTRL_NUM_BUFFS 16
#define CTRL_BUFF_SIZE 64

#define EXT_REF_CLK (61.44e6/2)

/***********************************************************************
 * Device interface
 **********************************************************************/
class EVB7 : public SoapySDR::Device
{
public:
    EVB7(void):
        _regs(NULL),
        _spiHandle(NULL),
        _lms(NULL),
        _rx_data_dma(NULL),
        _rx_ctrl_dma(NULL),
        _tx_data_dma(NULL),
        _tx_stat_dma(NULL),
        _masterClockRate(1.0e6)
    {
        SoapySDR::logf(SOAPY_SDR_INFO, "EVB7()");
        setvbuf(stdout, NULL, _IOLBF, 0);

        //map FPGA registers
        _regs = xumem_map_phys(FPGA_REGS, FPGA_REGS_SIZE);
        if (_regs == NULL)
        {
            throw std::runtime_error("EVB7 fail to map registers");
        }
        SoapySDR::logf(SOAPY_SDR_INFO, "Read sentinel 0x%x\n", xumem_read32(_regs, FPGA_REG_RD_SENTINEL));

        //perform reset
        SET_EMIO_OUT_LVL(RESET_EMIO, 0);
        SET_EMIO_OUT_LVL(RESET_EMIO, 1);

        //setup spi
        _spiHandle = spidev_interface_open("/dev/spidev32766.0");
        if (_spiHandle == NULL) std::runtime_error("EVB7 fail to spidev_interface_open()");

        //setup LMS7002M
        _lms = LMS7002M_create(spidev_interface_transact, _spiHandle);
        if (_lms == NULL) std::runtime_error("EVB7 fail to LMS7002M_create()");
        LMS7002M_set_spi_mode(_lms, 4); //set 4-wire spi mode first
        LMS7002M_reset(_lms);

        LMS7002M_afe_enable(_lms, LMS_TX, LMS_CHA, true);
        LMS7002M_afe_enable(_lms, LMS_TX, LMS_CHB, true);
        LMS7002M_afe_enable(_lms, LMS_RX, LMS_CHA, true);
        LMS7002M_afe_enable(_lms, LMS_RX, LMS_CHB, true);

        //LMS7002M_load_ini(_lms, "/root/src/test2.ini");
        //LMS7002M_set_spi_mode(_lms, 4); //set 4-wire spi mode first

        //read info register
        LMS7002M_regs_spi_read(_lms, 0x002f);
        SoapySDR::logf(SOAPY_SDR_INFO, "rev 0x%x", LMS7002M_regs(_lms)->reg_0x002f_rev);
        SoapySDR::logf(SOAPY_SDR_INFO, "ver 0x%x", LMS7002M_regs(_lms)->reg_0x002f_ver);

        //turn the clocks on
        this->setMasterClockRate(61e6);

        //configure data port directions and data clock rates
        LMS7002M_configure_lml_port(_lms, LMS_PORT1, LMS_TX, 1);
        LMS7002M_configure_lml_port(_lms, LMS_PORT2, LMS_RX, 1);

        //external reset now that clocks are on
        this->writeRegister(FPGA_REG_WR_EXT_RST, 1);
        this->writeRegister(FPGA_REG_WR_EXT_RST, 0);

        //estimate the clock rates with readback registers
        uint32_t rxt0 = xumem_read32(_regs, FPGA_REG_RD_RX_CLKS);
        uint32_t txt0 = xumem_read32(_regs, FPGA_REG_RD_TX_CLKS);
        sleep(1);
        uint32_t rxt1 = xumem_read32(_regs, FPGA_REG_RD_RX_CLKS);
        uint32_t txt1 = xumem_read32(_regs, FPGA_REG_RD_TX_CLKS);
        SoapySDR::logf(SOAPY_SDR_INFO, "RX rate %f Mhz", (rxt1-rxt0)/1e6);
        SoapySDR::logf(SOAPY_SDR_INFO, "TX rate %f Mhz", (txt1-txt0)/1e6);

        //clear time
        this->setHardwareTime(0, "");
        long long t0 = this->getHardwareTime("");
        sleep(1);
        long long t1 = this->getHardwareTime("");
        SoapySDR::logf(SOAPY_SDR_INFO, "HW sec/PC sec %f", (t1-t0)/1e9);

        //port output enables
        SET_EMIO_OUT_LVL(RXEN_EMIO, 1);
        SET_EMIO_OUT_LVL(TXEN_EMIO, 1);

        //setup dsp
        LMS7002M_rxtsp_init(_lms, LMS_CHAB);
        LMS7002M_txtsp_init(_lms, LMS_CHAB);

        //setup dma buffs
        _rx_data_dma = pzdud_create(RX_DMA_INDEX, PZDUD_S2MM);
        if (_rx_data_dma == NULL) throw std::runtime_error("EVB7 fail create rx data DMA");
        pzdud_reset(_rx_data_dma);

        _rx_ctrl_dma = pzdud_create(RX_DMA_INDEX, PZDUD_MM2S);
        if (_rx_ctrl_dma == NULL) throw std::runtime_error("EVB7 fail create rx ctrl DMA");
        pzdud_reset(_rx_ctrl_dma);

        /*
        _tx_data_dma = pzdud_create(TX_DMA_INDEX, PZDUD_MM2S);
        if (_tx_data_dma == NULL) throw std::runtime_error("EVB7 fail create tx data DMA");
        pzdud_reset(_tx_data_dma);

        _tx_stat_dma = pzdud_create(TX_DMA_INDEX, PZDUD_S2MM);
        if (_tx_stat_dma == NULL) throw std::runtime_error("EVB7 fail create tx stat DMA");
        pzdud_reset(_tx_stat_dma);
        */

        SoapySDR::logf(SOAPY_SDR_INFO, "EVB7() setup OK");

        //try test
        this->writeRegister(FPGA_REG_WR_TX_TEST, 0); //test off, normal tx from deframer
        /*
        this->writeRegister(FPGA_REG_WR_TX_TEST, 1); //test registers drive tx
        this->writeRegister(FPGA_REG_WR_TX_CHA, 0xAAAABBBB);
        this->writeRegister(FPGA_REG_WR_TX_CHB, 0xCCCCDDDD);
        LMS7002M_setup_digital_loopback(_lms);
        sleep(1);
        SoapySDR::logf(SOAPY_SDR_INFO, "FPGA_REG_RD_RX_CHA 0x%x", xumem_read32(_regs, FPGA_REG_RD_RX_CHA));
        SoapySDR::logf(SOAPY_SDR_INFO, "FPGA_REG_RD_RX_CHB 0x%x", xumem_read32(_regs, FPGA_REG_RD_RX_CHB));
        //*/

        LMS7002M_rxtsp_tsg_const(_lms, LMS_CHA, 1024, 1024);
        LMS7002M_rxtsp_tsg_const(_lms, LMS_CHB, 1024, 1024);
    /*
        LMS7002M_rxtsp_tsg_tone(_lms, LMS_CHA);
        LMS7002M_rxtsp_tsg_tone(_lms, LMS_CHB);
        */
/*
        sleep(1);
        SoapySDR::logf(SOAPY_SDR_INFO, "FPGA_REG_RD_RX_CHA 0x%x", xumem_read32(_regs, FPGA_REG_RD_RX_CHA));
        SoapySDR::logf(SOAPY_SDR_INFO, "FPGA_REG_RD_RX_CHB 0x%x", xumem_read32(_regs, FPGA_REG_RD_RX_CHB));

        LMS7002M_dump_ini(_lms, "/tmp/regs.ini");
*/
        //some defaults to avoid throwing
        _cachedSampleRates[SOAPY_SDR_RX] = 1e6;
        _cachedSampleRates[SOAPY_SDR_TX] = 1e6;
        _cachedLOFrequencies[SOAPY_SDR_RX] = 1e9;
        _cachedLOFrequencies[SOAPY_SDR_TX] = 1e9;
        _cachedBBFrequencies[SOAPY_SDR_RX][0] = 0;
        _cachedBBFrequencies[SOAPY_SDR_TX][0] = 0;
        _cachedBBFrequencies[SOAPY_SDR_RX][1] = 0;
        _cachedBBFrequencies[SOAPY_SDR_TX][1] = 0;
    }

    ~EVB7(void)
    {
        //power down and clean up
        LMS7002M_power_down(_lms);
        LMS7002M_destroy(_lms);

        //back to inputs
        CLEANUP_EMIO(RESET_EMIO);
        CLEANUP_EMIO(RXEN_EMIO);
        CLEANUP_EMIO(TXEN_EMIO);

        //dma cleanup
        pzdud_destroy(_rx_data_dma);
        pzdud_destroy(_rx_ctrl_dma);
        /*
        pzdud_destroy(_tx_data_dma);
        pzdud_destroy(_tx_stat_dma);
        */

        //spi cleanup
        spidev_interface_close(_spiHandle);

        //register unmap
        xumem_unmap_phys(_regs, FPGA_REGS_SIZE);
    }

/*******************************************************************
* Identification API
******************************************************************/
    std::string getDriverKey(void) const
    {
        return "EVB7";
    }

    std::string getHardwareKey(void) const
    {
        return "EVB7";
    }

/*******************************************************************
* Channels API
******************************************************************/
    size_t getNumChannels(const int) const
    {
        return 2;
    }

    bool getFullDuplex(const int, const size_t) const
    {
        return true;
    }

/*******************************************************************
* Stream API
******************************************************************/

    SoapySDR::Stream *setupStream(
        const int direction,
        const std::string &format,
        const std::vector<size_t> &channels,
        const SoapySDR::Kwargs &)
    {
        std::cout << "EVB7::setupStream() " << size_t(_rx_data_dma) << "\n";
        if (direction != SOAPY_SDR_RX) throw std::runtime_error("EVB7::setupStream: no TX support yet");
        if (format != "CS16") throw std::runtime_error("EVB7::setupStream: "+format);
        if (channels.size() != 1) throw std::runtime_error("EVB7::setupStream: only one channel for now");
        if (channels[0] != 0) throw std::runtime_error("EVB7::setupStream: only ch0 for now");

        //allocate dma memory
        int ret = 0;
        ret = pzdud_alloc(_rx_data_dma, DATA_NUM_BUFFS, DATA_BUFF_SIZE);
        if (ret != PZDUD_OK) throw std::runtime_error("EVB7::setupStream: fail alloc rx data DMA");
        ret = pzdud_alloc(_rx_ctrl_dma, CTRL_NUM_BUFFS, CTRL_BUFF_SIZE);
        if (ret != PZDUD_OK) throw std::runtime_error("EVB7::setupStream: fail alloc rx ctrl DMA");

        //start the channels
        ret = pzdud_init(_rx_data_dma, true);
        if (ret != PZDUD_OK) throw std::runtime_error("EVB7::setupStream: fail init rx data DMA");
        ret = pzdud_init(_rx_ctrl_dma, true);
        if (ret != PZDUD_OK) throw std::runtime_error("EVB7::setupStream: fail init rx ctrl DMA");

        return reinterpret_cast<SoapySDR::Stream *>(_rx_data_dma);
    }

    void closeStream(SoapySDR::Stream *stream)
    {
        std::cout << "EVB7::closeStream() " << size_t(stream) << "\n";
        if (stream == reinterpret_cast<SoapySDR::Stream *>(_rx_data_dma))
        {
            //halt the channels
            pzdud_halt(_rx_data_dma);
            pzdud_halt(_rx_ctrl_dma);

            //free dma memory
            pzdud_free(_rx_data_dma);
            pzdud_free(_rx_ctrl_dma);
        }
    }

    int sendControlMessage(const bool timeFlag, const bool burstFlag, const bool contFlag, const int frameSize, const int burstSize, const long long time)
    {
        size_t len = 0;
        int handle = pzdud_acquire(_rx_ctrl_dma, &len);
        if (handle < 0) return SOAPY_SDR_STREAM_ERROR;

        uint32_t *ctrl_msg = (uint32_t *)pzdud_addr(_rx_ctrl_dma, handle);
        ctrl_msg[0] = frameSize-1;
        if (timeFlag) ctrl_msg[0] |= (1 << 31);
        if (burstFlag) ctrl_msg[0] |= (1 << 28);
        if (contFlag) ctrl_msg[0] |= (1 << 27);
        ctrl_msg[1] = burstSize - 1;
        ctrl_msg[2] = time >> 32;
        ctrl_msg[3] = time & 0xffffffff;
        for (size_t i = 0; i < 4; i++) SoapySDR::logf(SOAPY_SDR_INFO, "ctrl_msg[%d] = 0x%x\n", int(i), ctrl_msg[i]);

        pzdud_release(_rx_ctrl_dma, handle, sizeof(uint32_t)*4);
        return 0;
    }

    int activateStream(
        SoapySDR::Stream *stream,
        const int flags,
        const long long timeNs,
        const size_t numElems)
    {
        std::cout << "EVB7::activateStream() " << size_t(stream) << "\n";
        if (stream == reinterpret_cast<SoapySDR::Stream *>(_rx_data_dma))
        {
            return sendControlMessage(
                false, //timeFlag
                true, //burstFlag
                false, //contFlag
                RX_FRAME_SIZE, RX_FRAME_SIZE*4, this->timeNsToTicks(timeNs));
            return sendControlMessage(
                (flags & SOAPY_SDR_HAS_TIME) != 0, //timeFlag
                (numElems) != 0, //burstFlag
                (flags & SOAPY_SDR_END_BURST) == 0, //contFlag
                RX_FRAME_SIZE, numElems, this->timeNsToTicks(timeNs));
        }
        return SOAPY_SDR_STREAM_ERROR;
    }

    int deactivateStream(
        SoapySDR::Stream *stream,
        const int flags,
        const long long timeNs)
    {
        std::cout << "EVB7::deactivateStream() " << size_t(stream) << "\n";
        if (stream == reinterpret_cast<SoapySDR::Stream *>(_rx_data_dma))
        {
            return sendControlMessage(
                (flags & SOAPY_SDR_HAS_TIME) != 0, //timeFlag
                false, //burstFlag
                false, //contFlag
        //TODO time ticks != time ns
                0, 0, timeNs);
        }
        return SOAPY_SDR_STREAM_ERROR;
    }

    int readStream(
        SoapySDR::Stream *,
        void * const *buffs,
        const size_t numElems,
        int &flags,
        long long &timeNs,
        const long timeoutUs)
    {
        //std::cout << "EVB7::readStream() " << numElems << "\n";
        size_t len = 0;
        int ret = 0;

        //wait with timeout then acquire
        ret = pzdud_wait(_rx_data_dma, timeoutUs);
        if (ret != 0) return SOAPY_SDR_TIMEOUT;
        int handle = pzdud_acquire(_rx_data_dma, &len);
        if (handle == PZDUD_ERROR_CLAIMED) throw std::runtime_error("EVB7::readStream() all claimed");

        //extract header
        uint32_t *hdr = (uint32_t *)pzdud_addr(_rx_data_dma, handle);
        const size_t burstCount = hdr[1] + 1;
        const size_t frameSize = (hdr[0] & 0xffff) + 1;
        const size_t numSamples = (len - (sizeof(uint32_t)*4))/sizeof(uint32_t);

        flags = 0;
        if (((hdr[0] >> 31) & 0x1) != 0) flags |= SOAPY_SDR_HAS_TIME;
        bool burstFlag = ((hdr[0] >> 28) & 0x1) != 0;
        bool continuousFlag = ((hdr[0] >> 27) & 0x1) != 0;
        SoapySDR::logf(SOAPY_SDR_TRACE, "numSamples = %d, x=0x%x", numSamples, hdr[numSamples/2]);

        if (burstFlag) //in burst
        {
            if (burstCount == numSamples) flags |= SOAPY_SDR_END_BURST;
            else if (frameSize != numSamples) ret = SOAPY_SDR_OVERFLOW;
        }
        else if (continuousFlag and frameSize != numSamples)
        {
            ret = SOAPY_SDR_OVERFLOW;
            SoapySDR::log(SOAPY_SDR_TRACE, "O");
        }

        //gather time even if its not valid
        timeNs = this->ticksToTimeNs((((uint64_t)hdr[2]) << 32) | hdr[3]);

        pzdud_release(_rx_data_dma, handle, 0);

        if (ret == 0) //no errors yet, copy buffer -- sorry for the copy, zero copy in the future...
        {
            //TODO if numElems < numSamples, keep remainder...
            ret = std::min(numSamples, numElems);
            std::memcpy(buffs[0], hdr+4, ret*sizeof(uint32_t));
        }

        std::cout << "ret = " << ret << std::endl;
        return ret;
    }


    /*******************************************************************
     * Antenna API
     ******************************************************************/

    /*******************************************************************
     * Frontend corrections API
     ******************************************************************/

    /*******************************************************************
     * Gain API
     ******************************************************************/

    /*******************************************************************
     * Frequency API
     ******************************************************************/
    void setFrequency(const int direction, const size_t channel, const double frequency, const SoapySDR::Kwargs &args)
    {
        //for now, we just tune the cordics
        const double baseRate = this->getTSPRate(direction);
        if (direction == SOAPY_SDR_RX) LMS7002M_rxtsp_set_freq(_lms, (channel == 0)?LMS_CHA:LMS_CHB, frequency/baseRate);
        if (direction == SOAPY_SDR_TX) LMS7002M_txtsp_set_freq(_lms, (channel == 0)?LMS_CHA:LMS_CHB, frequency/baseRate);
        _cachedBBFrequencies[direction][channel] = frequency;
    }

    double getFrequency(const int direction, const size_t channel) const
    {
        return getFrequency(direction, channel, "BB") + getFrequency(direction, channel, "RF");
    }

    double getFrequency(const int direction, const size_t channel, const std::string &name) const
    {
        if (name == "BB") return _cachedBBFrequencies.at(direction).at(channel);
        if (name == "RF") return _cachedLOFrequencies.at(direction);
        return SoapySDR::Device::getFrequency(direction, channel, name);
    }

    std::vector<std::string> listFrequencies(const int, const size_t) const
    {
        std::vector<std::string> opts;
        opts.push_back("RF");
        opts.push_back("BB");
        return opts;
    }

    SoapySDR::RangeList getFrequencyRange(const int, const size_t) const
    {
        SoapySDR::RangeList ranges;
        ranges.push_back(SoapySDR::Range(100e3, 3.8e9));
        return ranges;
    }

    std::map<int, double> _cachedLOFrequencies;
    std::map<int, std::map<size_t, double> > _cachedBBFrequencies;

    /*******************************************************************
     * Sample Rate API
     ******************************************************************/
    void setSampleRate(const int direction, const size_t, const double rate)
    {
        const double baseRate = this->getTSPRate(direction);
        const double factor = baseRate/rate;
        SoapySDR::logf(SOAPY_SDR_TRACE, "setSampleRate %f MHz, baseRate %f MHz, factor %f", rate/1e6, baseRate/1e6, factor);
        if (factor < 1.0) throw std::runtime_error("EVB7::setSampleRate() -- rate too high");
        const int intFactor = int(factor + 0.5);
        if (intFactor > 32) throw std::runtime_error("EVB7::setSampleRate() -- rate too low");

        if (std::abs(factor-intFactor) > 0.01) SoapySDR::logf(SOAPY_SDR_WARNING,
            "EVB7::setSampleRate(): not a power of two factor: TSP Rate = %f MHZ, Requested rate = %f MHz", baseRate/1e6, rate/1e6);

        //apply the settings, both the interp/decim has to be matched with the lml interface divider
        if (direction == SOAPY_SDR_RX)
        {
            LMS7002M_rxtsp_set_decim(_lms, LMS_CHAB, intFactor);
            LMS7002M_configure_lml_port(_lms, LMS_PORT2, LMS_RX, intFactor);
        }
        if (direction == SOAPY_SDR_TX)
        {
            LMS7002M_txtsp_set_interp(_lms, LMS_CHAB, intFactor);
            LMS7002M_configure_lml_port(_lms, LMS_PORT1, LMS_TX, intFactor);
        }

        _cachedSampleRates[direction] = baseRate/intFactor;
    }

    double getSampleRate(const int direction, const size_t) const
    {
        return _cachedSampleRates.at(direction);
    }

    std::vector<double> listSampleRates(const int direction, const size_t) const
    {
        const double baseRate = this->getTSPRate(direction);
        std::vector<double> rates;
        for (int i = 5; i >= 0; i--)
        {
            rates.push_back(baseRate/(1 << i));
        }
        return rates;
    }

    std::map<int, double> _cachedSampleRates;

    /*******************************************************************
     * Clocking API
     ******************************************************************/
    double getTSPRate(const int direction) const
    {
        return (direction == SOAPY_SDR_TX)? _masterClockRate : _masterClockRate/4;
    }

    void setMasterClockRate(const double rate)
    {
        int ret = LMS7002M_set_data_clock(_lms, EXT_REF_CLK, rate);
        if (ret != 0)
        {
            SoapySDR::logf(SOAPY_SDR_ERROR, "LMS7002M_set_data_clock(%f MHz) -> %d", rate/1e6, ret);
            throw std::runtime_error("EVB7 fail LMS7002M_set_data_clock()");
        }
        _masterClockRate = rate;
    }

    double getMasterClockRate(void) const
    {
        return _masterClockRate;
    }

    /*******************************************************************
     * Time API
     ******************************************************************/
    long long ticksToTimeNs(const long long ticks) const
    {
        return ticks/(_masterClockRate/1e9);
    }

    long long timeNsToTicks(const long long timeNs) const
    {
        return timeNs/(1e9/_masterClockRate);
    }

    bool hasHardwareTime(const std::string &what) const
    {
        if (what.empty()) return true;
        return EVB7::hasHardwareTime(what);
    }

    long long getHardwareTime(const std::string &) const
    {
        long long timeLo = this->readRegister(FPGA_REG_RD_TIME_LO);
        long long timeHi = this->readRegister(FPGA_REG_RD_TIME_HI);
        return this->ticksToTimeNs((timeHi << 32) | timeLo);
    }

    void setHardwareTime(const long long timeNs, const std::string &)
    {
        long long ticks = this->timeNsToTicks(timeNs);
        this->writeRegister(FPGA_REG_WR_TIME_LO, ticks & 0xffffffff);
        this->writeRegister(FPGA_REG_WR_TIME_HI, ticks >> 32);
        this->writeRegister(FPGA_REG_WR_TIME_LATCH, 1);
        this->writeRegister(FPGA_REG_WR_TIME_LATCH, 0);
    }

    /*******************************************************************
     * Sensor API
     ******************************************************************/

    /*******************************************************************
     * Register API
     ******************************************************************/
    void writeRegister(const unsigned addr, const unsigned value)
    {
        xumem_write32(_regs, addr, value);
    }

    unsigned readRegister(const unsigned addr) const
    {
        return xumem_read32(_regs, addr);
    }

    /*******************************************************************
     * Settings API
     ******************************************************************/

    /*******************************************************************
     * GPIO API
     ******************************************************************/

    /*******************************************************************
     * I2C API
     ******************************************************************/

    /*******************************************************************
     * SPI API
     ******************************************************************/

    /*******************************************************************
     * UART API
     ******************************************************************/

private:
    void *_regs;
    void *_spiHandle;
    LMS7002M_t *_lms;
    pzdud_t *_rx_data_dma;
    pzdud_t *_rx_ctrl_dma;
    pzdud_t *_tx_data_dma;
    pzdud_t *_tx_stat_dma;
    double _masterClockRate;
};

/***********************************************************************
 * Find available devices
 **********************************************************************/
std::vector<SoapySDR::Kwargs> findEVB7(const SoapySDR::Kwargs &args)
{
    //always discovery "args" -- the sdr is the board itself
    std::vector<SoapySDR::Kwargs> discovered;
    discovered.push_back(args);
    return discovered;
}

/***********************************************************************
 * Make device instance
 **********************************************************************/
SoapySDR::Device *makeEVB7(const SoapySDR::Kwargs &)
{
    //ignore the args because again, the sdr is the board
    return new EVB7();
}

/***********************************************************************
 * Registration
 **********************************************************************/
static SoapySDR::Registry registerEVB7("evb7", &findEVB7, &makeEVB7, SOAPY_SDR_ABI_VERSION);
