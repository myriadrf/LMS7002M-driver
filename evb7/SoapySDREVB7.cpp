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
#include "twbw_helper.h"

/***********************************************************************
 * FPGA EMIOs that are controlled by sysfs GPIO
 **********************************************************************/
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

/***********************************************************************
 * FPGA register space for misc controls
 **********************************************************************/
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

/***********************************************************************
 * Settings for the AXI DMA and framer/deframer
 **********************************************************************/
#define RX_DMA_INDEX 0
#define TX_DMA_INDEX 1
#define RX_FRAME_SIZE 1000 //buff size - hdrs
#define TX_FRAME_SIZE 1000 //buff size - hdrs

#define DATA_NUM_BUFFS 16
#define DATA_BUFF_SIZE 4096

#define CTRL_NUM_BUFFS 16
#define CTRL_BUFF_SIZE 64

#define XFER_SIZE sizeof(uint32_t)

//sanity check tags that the framers echo back in their responses
#define RX_TAG_ACTIVATE uint8_t('A')
#define RX_TAG_DEACTIVATE uint8_t('D')
#define TX_TAG_TRANSMIT uint8_t('T')

/***********************************************************************
 * Clock rates for this system
 **********************************************************************/
//the reference clock on the EVB7
#define EXT_REF_CLK (61.44e6/2)

//using an independent FPGA clock to drive the device timer
#define IF_TIME_CLK 100e6

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
        this->writeRegister(FPGA_REG_WR_TX_TEST, 0); //test off, normal tx from deframer

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

        //enable all ADCs and DACs
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
        /*
        long long t0 = this->getHardwareTime("");
        sleep(1);
        long long t1 = this->getHardwareTime("");
        SoapySDR::logf(SOAPY_SDR_INFO, "HW sec/PC sec %f", (t1-t0)/1e9);
        */

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

        _tx_data_dma = pzdud_create(TX_DMA_INDEX, PZDUD_MM2S);
        if (_tx_data_dma == NULL) throw std::runtime_error("EVB7 fail create tx data DMA");
        pzdud_reset(_tx_data_dma);

        _tx_stat_dma = pzdud_create(TX_DMA_INDEX, PZDUD_S2MM);
        if (_tx_stat_dma == NULL) throw std::runtime_error("EVB7 fail create tx stat DMA");
        pzdud_reset(_tx_stat_dma);

        SoapySDR::logf(SOAPY_SDR_INFO, "EVB7() setup OK");

        //try test
        /*
        this->writeRegister(FPGA_REG_WR_TX_TEST, 1); //test registers drive tx
        this->writeRegister(FPGA_REG_WR_TX_CHA, 0xAAAABBBB);
        this->writeRegister(FPGA_REG_WR_TX_CHB, 0xCCCCDDDD);
        LMS7002M_setup_digital_loopback(_lms);
        sleep(1);
        SoapySDR::logf(SOAPY_SDR_INFO, "FPGA_REG_RD_RX_CHA 0x%x", xumem_read32(_regs, FPGA_REG_RD_RX_CHA));
        SoapySDR::logf(SOAPY_SDR_INFO, "FPGA_REG_RD_RX_CHB 0x%x", xumem_read32(_regs, FPGA_REG_RD_RX_CHB));
        //*/

        LMS7002M_rxtsp_tsg_const(_lms, LMS_CHA, 1 << 14, 1 << 14);
        LMS7002M_rxtsp_tsg_const(_lms, LMS_CHB, 1 << 14, 1 << 14);
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
        pzdud_destroy(_tx_data_dma);
        pzdud_destroy(_tx_stat_dma);

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
        if (format != "CS16") throw std::runtime_error("EVB7::setupStream: "+format);
        if (channels.size() != 1) throw std::runtime_error("EVB7::setupStream: only one channel for now");
        if (channels[0] != 0) throw std::runtime_error("EVB7::setupStream: only ch0 for now");

        if (direction == SOAPY_SDR_RX)
        {
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

            //ensure stream inactive
            this->sendControlMessage(RX_TAG_DEACTIVATE, false, true, RX_FRAME_SIZE, 1, 0);

            //flush
            this->rxFlush();

            return reinterpret_cast<SoapySDR::Stream *>(_rx_data_dma);
        }

        if (direction == SOAPY_SDR_TX)
        {
            //allocate dma memory
            int ret = 0;
            ret = pzdud_alloc(_tx_data_dma, DATA_NUM_BUFFS, DATA_BUFF_SIZE);
            if (ret != PZDUD_OK) throw std::runtime_error("EVB7::setupStream: fail alloc tx data DMA");
            ret = pzdud_alloc(_tx_stat_dma, CTRL_NUM_BUFFS, CTRL_BUFF_SIZE);
            if (ret != PZDUD_OK) throw std::runtime_error("EVB7::setupStream: fail alloc tx stat DMA");

            //start the channels
            ret = pzdud_init(_tx_data_dma, true);
            if (ret != PZDUD_OK) throw std::runtime_error("EVB7::setupStream: fail init tx data DMA");
            ret = pzdud_init(_tx_stat_dma, true);
            if (ret != PZDUD_OK) throw std::runtime_error("EVB7::setupStream: fail init tx stat DMA");

            return reinterpret_cast<SoapySDR::Stream *>(_tx_data_dma);
        }
    }

    void rxFlush(void)
    {
        while (true)
        {
            int ret = pzdud_wait(_rx_data_dma, 1000);
            if (ret != 0) break;
            size_t len = 0;
            int handle = pzdud_acquire(_rx_data_dma, &len);
            if (handle < 0) break;
            pzdud_release(_rx_data_dma, handle, 0);
        }
    }

    void closeStream(SoapySDR::Stream *stream)
    {
        if (stream == reinterpret_cast<SoapySDR::Stream *>(_rx_data_dma))
        {
            //halt the channels
            pzdud_halt(_rx_data_dma);
            pzdud_halt(_rx_ctrl_dma);

            //free dma memory
            pzdud_free(_rx_data_dma);
            pzdud_free(_rx_ctrl_dma);
        }

        if (stream == reinterpret_cast<SoapySDR::Stream *>(_tx_data_dma))
        {
            //halt the channels
            pzdud_halt(_tx_data_dma);
            pzdud_halt(_tx_stat_dma);

            //free dma memory
            pzdud_free(_tx_data_dma);
            pzdud_free(_tx_stat_dma);
        }
    }

    int sendControlMessage(const int tag, const bool timeFlag, const bool burstFlag, const int frameSize, const int burstSize, const long long time)
    {
        size_t len = 0;
        int handle = pzdud_acquire(_rx_ctrl_dma, &len);
        if (handle < 0) return SOAPY_SDR_STREAM_ERROR;

        twbw_framer_ctrl_packer(
            pzdud_addr(_rx_ctrl_dma, handle), len,
            tag, timeFlag, time,
            burstFlag, frameSize, burstSize
        );

        pzdud_release(_rx_ctrl_dma, handle, len);
        return 0;
    }

    int activateStream(
        SoapySDR::Stream *stream,
        const int flags,
        const long long timeNs,
        const size_t numElems)
    {
        if (stream == reinterpret_cast<SoapySDR::Stream *>(_rx_data_dma))
        {
            return sendControlMessage(
                RX_TAG_ACTIVATE,
                (flags & SOAPY_SDR_HAS_TIME) != 0, //timeFlag
                (flags & SOAPY_SDR_END_BURST) != 0, //burstFlag
                RX_FRAME_SIZE, numElems, this->timeNsToTicks(timeNs));
        }

        if (stream == reinterpret_cast<SoapySDR::Stream *>(_tx_data_dma))
        {
            return 0;
        }

        return SOAPY_SDR_STREAM_ERROR;
    }

    int deactivateStream(
        SoapySDR::Stream *stream,
        const int flags,
        const long long timeNs)
    {
        if (stream == reinterpret_cast<SoapySDR::Stream *>(_rx_data_dma))
        {
            int ret = sendControlMessage(
                RX_TAG_DEACTIVATE,
                (flags & SOAPY_SDR_HAS_TIME) != 0, //timeFlag
                true, //burstFlag
                RX_FRAME_SIZE, 1, this->timeNsToTicks(timeNs));
            this->rxFlush();
            return ret;
        }

        if (stream == reinterpret_cast<SoapySDR::Stream *>(_tx_data_dma))
        {
            return 0;
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
        size_t len = 0;
        int ret = 0;
        flags = 0;

        //wait with timeout then acquire
        ret = pzdud_wait(_rx_data_dma, timeoutUs);
        if (ret != 0) return SOAPY_SDR_TIMEOUT;
        int handle = pzdud_acquire(_rx_data_dma, &len);
        if (handle == PZDUD_ERROR_CLAIMED) throw std::runtime_error("EVB7::readStream() all claimed");

        //unpack the header
        const void *payload;
        size_t numSamples;
        bool overflow;
        int idTag;
        bool hasTime;
        long long timeTicks;
        bool timeError;
        bool isBurst;
        bool burstEnd;
        twbw_framer_data_unpacker(
            pzdud_addr(_rx_data_dma, handle), len, XFER_SIZE,
            payload, numSamples, overflow, idTag,
            hasTime, timeTicks,
            timeError, isBurst, burstEnd);

        //gather time even if its not valid
        timeNs = this->ticksToTimeNs(timeTicks);

        //error indicators
        if (overflow) ret = SOAPY_SDR_OVERFLOW;
        if (hasTime) flags |= SOAPY_SDR_HAS_TIME;
        if (burstEnd) flags |= SOAPY_SDR_END_BURST;

        //old packet from the deactivate command, just ignore it with timeout
        if (idTag == RX_TAG_DEACTIVATE)
        {
            ret = SOAPY_SDR_TIMEOUT;
        }

        //not an activate or deactivate tag, this is bad!
        else if (idTag != RX_TAG_ACTIVATE)
        {
            SoapySDR::logf(SOAPY_SDR_ERROR,
                "readStream tag error tag=0x%x, len=%d", idTag, len);
            ret = SOAPY_SDR_STREAM_ERROR;
        }

        //a bad time was specified in the command packet
        else if (timeError)
        {
            SoapySDR::logf(SOAPY_SDR_ERROR,
                "readStream time error time now %f, time pkt %f, len=%d",
                this->getHardwareTime("")/1e9, timeNs/1e9, len);
            ret = SOAPY_SDR_STREAM_ERROR;
        }

        //restart streaming when overflow in continuous mode
        if (overflow and not isBurst)
        {
            SoapySDR::log(SOAPY_SDR_TRACE, "O");
            sendControlMessage( //restart streaming
                RX_TAG_ACTIVATE,
                false, //timeFlag
                false, //burstFlag
                RX_FRAME_SIZE, 0, 0);
        }

        if (ret == 0) //no errors yet, copy buffer -- sorry for the copy, zero copy in the future...
        {
            //TODO if numElems < numSamples, keep remainder...
            if (numElems < numSamples) SoapySDR::log(SOAPY_SDR_TRACE, "Truncated!");
            ret = std::min(numSamples, numElems);
            const uint32_t *in = (const uint32_t *)payload;
            std::complex<int16_t> *out = (std::complex<int16_t> *)buffs[0];
            for (int i = 0; i < ret; i++)
            {
                int16_t i16 = uint16_t(in[i] >> 16);
                int16_t q16 = uint16_t(in[i] & 0xffff);
                out[i] = std::complex<int16_t>(i16, q16);
            }
        }

        //always release the buffer back the SG engine
        pzdud_release(_rx_data_dma, handle, 0);

        //std::cout << "ret = " << ret << std::endl;
        return ret;
    }

    int writeStream(
        SoapySDR::Stream *,
        const void * const *buffs,
        const size_t numElems,
        int &flags,
        const long long timeNs,
        const long timeoutUs
    )
    {
        size_t len = 0;
        int ret = 0;

        //wait with timeout then acquire
        ret = pzdud_wait(_tx_data_dma, timeoutUs);
        if (ret != 0) return SOAPY_SDR_TIMEOUT;
        int handle = pzdud_acquire(_tx_data_dma, &len);
        if (handle == PZDUD_ERROR_CLAIMED) throw std::runtime_error("EVB7::writeStream() all claimed");

        //pack the header
        void *payload;
        size_t numSamples = std::min<size_t>(TX_FRAME_SIZE, numElems);
        twbw_deframer_data_packer(
            pzdud_addr(_tx_data_dma, handle), len, XFER_SIZE,
            payload, numSamples, TX_TAG_TRANSMIT,
            (flags & SOAPY_SDR_HAS_TIME) != 0,
            this->timeNsToTicks(timeNs),
            (flags & SOAPY_SDR_END_BURST) != 0
        );

        //convert the samples
        uint32_t *out = (uint32_t *)payload;
        std::complex<const int16_t> *in = (std::complex<const int16_t> *)buffs[0];
        for (size_t i = 0; i < numSamples; i++)
        {
            uint16_t i16 = in[i].real();
            uint16_t q16 = in[i].imag();
            out[i] = (uint32_t(i16) << 16) | q16;
        }

        //always release the buffer back the SG engine
        pzdud_release(_tx_data_dma, handle, 0);

        return numSamples;
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
        //the rf frequency as passed -n or specifically from args
        //double rfFreq = (args.count("RF") != 0)?atof(args.at("RF").c_str()):frequency;

        //optional LO offset from the args
        //double offset = (args.count("OFFSET") != 0)?atof(args.at("OFFSET").c_str()):0.0;

        //rfFreq += offset;

        //tune the LO
        //int ret = LMS7002M_set_lo_freq(_lms, (direction == SOAPY_SDR_RX)?LMS_RX:LMS_RX, _masterClockRate, frequency, &_cachedLOFrequencies[direction]);

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
        if (factor < 2.0) throw std::runtime_error("EVB7::setSampleRate() -- rate too high");
        const int intFactor = int(factor + 0.5);
        if (intFactor > 32) throw std::runtime_error("EVB7::setSampleRate() -- rate too low");

        if (std::abs(factor-intFactor) > 0.01) SoapySDR::logf(SOAPY_SDR_WARNING,
            "EVB7::setSampleRate(): not a power of two factor: TSP Rate = %f MHZ, Requested rate = %f MHz", baseRate/1e6, rate/1e6);

        //apply the settings, both the interp/decim has to be matched with the lml interface divider
        //the lml interface needs a clock rate 2x the sample rate for DDR TRX IQ mode
        if (direction == SOAPY_SDR_RX)
        {
            LMS7002M_rxtsp_set_decim(_lms, LMS_CHAB, intFactor);
            LMS7002M_configure_lml_port(_lms, LMS_PORT2, LMS_RX, intFactor/2);
        }
        if (direction == SOAPY_SDR_TX)
        {
            LMS7002M_txtsp_set_interp(_lms, LMS_CHAB, intFactor);
            LMS7002M_configure_lml_port(_lms, LMS_PORT1, LMS_TX, intFactor/2);
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
        int ret = LMS7002M_set_data_clock(_lms, EXT_REF_CLK, rate, &_masterClockRate);
        if (ret != 0)
        {
            SoapySDR::logf(SOAPY_SDR_ERROR, "LMS7002M_set_data_clock(%f MHz) -> %d", rate/1e6, ret);
            throw std::runtime_error("EVB7 fail LMS7002M_set_data_clock()");
        }
        SoapySDR::logf(SOAPY_SDR_TRACE, "LMS7002M_set_data_clock(%f MHz) -> %f MHz", rate/1e6, _masterClockRate/1e6);
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
        return ticks/(IF_TIME_CLK/1e9);
    }

    long long timeNsToTicks(const long long timeNs) const
    {
        return timeNs/(1e9/IF_TIME_CLK);
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
