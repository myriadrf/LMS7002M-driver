//
// SoapySDR wrapper for the LMS7002M driver.
//
// Copyright (c) 2015-2015 Fairwaves, Inc.
// Copyright (c) 2015-2015 Rice University
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
//

#include "EVB7Device.hpp"
#include <SoapySDR/Registry.hpp>
#include <LMS7002M/LMS7002M_impl.h>

/***********************************************************************
 * Constructor
 **********************************************************************/
EVB7::EVB7(void):
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

    //LMS7002M_load_ini(_lms, "/root/src/TBB_to_LPFL_RBB_loopback.ini");
    //LMS7002M_set_spi_mode(_lms, 4); //set 4-wire spi mode first

    //read info register
    LMS7002M_regs_spi_read(_lms, 0x002f);
    SoapySDR::logf(SOAPY_SDR_INFO, "rev 0x%x", LMS7002M_regs(_lms)->reg_0x002f_rev);
    SoapySDR::logf(SOAPY_SDR_INFO, "ver 0x%x", LMS7002M_regs(_lms)->reg_0x002f_ver);

    //turn the clocks on
    this->setMasterClockRate(61.44e6);

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

    //enable components
    LMS7002M_afe_enable(_lms, LMS_TX, LMS_CHA, true);
    LMS7002M_afe_enable(_lms, LMS_TX, LMS_CHB, true);
    LMS7002M_afe_enable(_lms, LMS_RX, LMS_CHA, true);
    LMS7002M_afe_enable(_lms, LMS_RX, LMS_CHB, true);
    LMS7002M_rxtsp_enable(_lms, LMS_CHAB, true);
    LMS7002M_txtsp_enable(_lms, LMS_CHAB, true);
    LMS7002M_rbb_enable(_lms, LMS_CHAB, true);
    LMS7002M_tbb_enable(_lms, LMS_CHAB, true);
    LMS7002M_rfe_enable(_lms, LMS_CHAB, true);
    LMS7002M_trf_enable(_lms, LMS_CHAB, true);
    LMS7002M_sxx_enable(_lms, LMS_RX, true);
    LMS7002M_sxx_enable(_lms, LMS_TX, true);

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

    //constant DC level
    /*
    LMS7002M_rxtsp_tsg_const(_lms, LMS_CHA, 1 << 14, 1 << 14);
    LMS7002M_rxtsp_tsg_const(_lms, LMS_CHB, 1 << 14, 1 << 14);
    //*/

    //tx baseband loopback to rx baseband
    //LMS7002M_tbb_enable_loopback(_lms, LMS_CHAB, LMS7002M_TBB_MAIN_TBB, false);
    //LMS7002M_rbb_select_input(_lms, LMS_CHAB, LMS7002M_RBB_BYP_LB);

    //tone from tx dsp
    //LMS7002M_txtsp_tsg_tone(_lms, LMS_CHAB);

/*
    LMS7002M_rxtsp_tsg_tone(_lms, LMS_CHA);
    LMS7002M_rxtsp_tsg_tone(_lms, LMS_CHB);
    */
/*
    sleep(1);
    SoapySDR::logf(SOAPY_SDR_INFO, "FPGA_REG_RD_RX_CHA 0x%x", xumem_read32(_regs, FPGA_REG_RD_RX_CHA));
    SoapySDR::logf(SOAPY_SDR_INFO, "FPGA_REG_RD_RX_CHB 0x%x", xumem_read32(_regs, FPGA_REG_RD_RX_CHB));
*/
    //some defaults to avoid throwing
    _cachedSampleRates[SOAPY_SDR_RX] = 1e6;
    _cachedSampleRates[SOAPY_SDR_TX] = 1e6;
    for (size_t i = 0; i < 2; i++)
    {
        _cachedFreqValues[SOAPY_SDR_RX][i]["RF"] = 1e9;
        _cachedFreqValues[SOAPY_SDR_TX][i]["RF"] = 1e9;
        _cachedFreqValues[SOAPY_SDR_RX][i]["BB"] = 0;
        _cachedFreqValues[SOAPY_SDR_TX][i]["BB"] = 0;
        this->setAntenna(SOAPY_SDR_RX, i, "LNAW");
        this->setAntenna(SOAPY_SDR_TX, i, "BAND1");
        this->setGain(SOAPY_SDR_RX, i, "LNA", 0.0);
        this->setGain(SOAPY_SDR_RX, i, "TIA", 0.0);
        this->setGain(SOAPY_SDR_RX, i, "PGA", 0.0);
        this->setBandwidth(SOAPY_SDR_RX, i, 200e6);
        this->setBandwidth(SOAPY_SDR_TX, i, 200e6);
    }

    //LMS7002M_dump_ini(_lms, "/root/src/regs.ini");
}

EVB7::~EVB7(void)
{
    //power down and clean up
    LMS7002M_afe_enable(_lms, LMS_TX, LMS_CHA, false);
    LMS7002M_afe_enable(_lms, LMS_TX, LMS_CHB, false);
    LMS7002M_afe_enable(_lms, LMS_RX, LMS_CHA, false);
    LMS7002M_afe_enable(_lms, LMS_RX, LMS_CHB, false);
    LMS7002M_rxtsp_enable(_lms, LMS_CHAB, false);
    LMS7002M_txtsp_enable(_lms, LMS_CHAB, false);
    LMS7002M_rbb_enable(_lms, LMS_CHAB, false);
    LMS7002M_tbb_enable(_lms, LMS_CHAB, false);
    LMS7002M_rfe_enable(_lms, LMS_CHAB, false);
    LMS7002M_trf_enable(_lms, LMS_CHAB, false);
    LMS7002M_sxx_enable(_lms, LMS_RX, false);
    LMS7002M_sxx_enable(_lms, LMS_TX, false);
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
 * Antenna API
 ******************************************************************/
std::vector<std::string> EVB7::listAntennas(const int direction, const size_t) const
{
    std::vector<std::string> ants;
    if (direction == SOAPY_SDR_RX)
    {
        ants.push_back("LNAH");
        ants.push_back("LNAL");
        ants.push_back("LNAW");
    }
    if (direction == SOAPY_SDR_TX)
    {
        ants.push_back("BAND1");
        ants.push_back("BAND2");
    }
    return ants;
}

void EVB7::setAntenna(const int direction, const size_t channel, const std::string &name)
{
    if (direction == SOAPY_SDR_RX)
    {
        int path = LMS7002M_RFE_NONE;
        if (name == "LNAH") path = LMS7002M_RFE_LNAH;
        else if (name == "LNAL") path = LMS7002M_RFE_LNAL;
        else if (name == "LNAW") path = LMS7002M_RFE_LNAW;
        else throw std::runtime_error("EVB7::setAntenna(RX, "+name+") - unknown antenna name");
        LMS7002M_rfe_select_input(_lms, ch2LMS(channel), path);
    }
    if (direction == SOAPY_SDR_TX)
    {
        int band = 0;
        if (name == "BAND1") band = 1;
        else if (name == "BAND2") band = 2;
        else throw std::runtime_error("EVB7::setAntenna(TX, "+name+") - unknown antenna name");
        LMS7002M_trf_select_band(_lms, ch2LMS(channel), band);
    }
    _cachedAntValues[direction][channel] = name;
}

std::string EVB7::getAntenna(const int direction, const size_t channel) const
{
    return _cachedAntValues.at(direction).at(channel);
}

/*******************************************************************
 * Gain API
 ******************************************************************/
std::vector<std::string> EVB7::listGains(const int direction, const size_t) const
{
    std::vector<std::string> gains;
    if (direction == SOAPY_SDR_RX)
    {
        gains.push_back("LNA");
        gains.push_back("TIA");
        gains.push_back("PGA");
    }
    if (direction == SOAPY_SDR_TX)
    {
        gains.push_back("IAMP");
    }
    return gains;
}

void EVB7::setGain(const int direction, const size_t channel, const std::string &name, const double value)
{
    SoapySDR::logf(SOAPY_SDR_INFO, "EVB7::setGain(%d, ch%d, %s, %f dB)", direction, channel, name.c_str(), value);

    double &actualValue = _cachedGainValues[direction][channel][name];

    if (direction == SOAPY_SDR_RX and name == "LNA")
    {
        actualValue = LMS7002M_rfe_set_lna(_lms, ch2LMS(channel), value);
    }

    if (direction == SOAPY_SDR_RX and name == "TIA")
    {
        actualValue = LMS7002M_rfe_set_tia(_lms, ch2LMS(channel), value);
    }

    if (direction == SOAPY_SDR_RX and name == "PGA")
    {
        actualValue = LMS7002M_rbb_set_pga(_lms, ch2LMS(channel), value);
    }

    if (direction == SOAPY_SDR_TX and name == "IAMP")
    {
        actualValue = LMS7002M_tbb_set_iamp(_lms, ch2LMS(channel), value);
    }
}

double EVB7::getGain(const int direction, const size_t channel, const std::string &name) const
{
    return _cachedGainValues.at(direction).at(channel).at(name);
}

SoapySDR::Range EVB7::getGainRange(const int direction, const size_t channel, const std::string &name) const
{
    if (direction == SOAPY_SDR_RX and name == "LNA") return SoapySDR::Range(0.0, 30.0);
    if (direction == SOAPY_SDR_RX and name == "TIA") return SoapySDR::Range(0.0, 12.0);
    if (direction == SOAPY_SDR_RX and name == "PGA") return SoapySDR::Range(-12.0, 19.0);
    if (direction == SOAPY_SDR_TX and name == "IAMP") return SoapySDR::Range(0.0, 63.0);
    return SoapySDR::Device::getGainRange(direction, channel, name);
}

/*******************************************************************
 * Frequency API
 ******************************************************************/
void EVB7::setFrequency(const int direction, const size_t channel, const std::string &name, const double frequency, const SoapySDR::Kwargs &)
{
    SoapySDR::logf(SOAPY_SDR_INFO, "EVB7::setFrequency(%d, ch%d, %s, %f MHz)", direction, channel, name.c_str(), frequency/1e6);

    if (name == "RF")
    {
        double actualFreq = 0.0;
        int ret = LMS7002M_set_lo_freq(_lms, dir2LMS(direction), _masterClockRate, frequency, &actualFreq);
        if (ret != 0) throw std::runtime_error("EVB7::setFrequency(" + std::to_string(frequency/1e6) + " MHz) failed - " + std::to_string(ret));
        _cachedFreqValues[direction][0][name] = actualFreq;
        _cachedFreqValues[direction][1][name] = actualFreq;
    }

    if (name == "BB")
    {
        const double baseRate = this->getTSPRate(direction);
        if (direction == SOAPY_SDR_RX) LMS7002M_rxtsp_set_freq(_lms, ch2LMS(channel), frequency/baseRate);
        if (direction == SOAPY_SDR_TX) LMS7002M_txtsp_set_freq(_lms, ch2LMS(channel), frequency/baseRate);
        _cachedFreqValues[direction][channel][name] = frequency;
    }
}

double EVB7::getFrequency(const int direction, const size_t channel, const std::string &name) const
{
    return _cachedFreqValues.at(direction).at(channel).at(name);
}

std::vector<std::string> EVB7::listFrequencies(const int, const size_t) const
{
    std::vector<std::string> opts;
    opts.push_back("RF");
    opts.push_back("BB");
    return opts;
}

SoapySDR::RangeList EVB7::getFrequencyRange(const int direction, const size_t, const std::string &name) const
{
    SoapySDR::RangeList ranges;
    if (name == "RF")
    {
        ranges.push_back(SoapySDR::Range(100e3, 3.8e9));
    }
    if (name == "BB")
    {
        const double rate = this->getTSPRate(direction);
        ranges.push_back(SoapySDR::Range(-rate/2, rate/2));
    }
    return ranges;
}
/*******************************************************************
 * Sample Rate API
 ******************************************************************/
void EVB7::setSampleRate(const int direction, const size_t, const double rate)
{
    const double baseRate = this->getTSPRate(direction);
    const double factor = baseRate/rate;
    SoapySDR::logf(SOAPY_SDR_INFO, "EVB7::setSampleRate(%d, %f MHz), baseRate %f MHz, factor %f", direction, rate/1e6, baseRate/1e6, factor);
    if (factor < 2.0) throw std::runtime_error("EVB7::setSampleRate() -- rate too high");
    int intFactor = 1 << int((std::log(factor)/std::log(2.0)) + 0.5);
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

double EVB7::getSampleRate(const int direction, const size_t) const
{
    return _cachedSampleRates.at(direction);
}

std::vector<double> EVB7::listSampleRates(const int direction, const size_t) const
{
    const double baseRate = this->getTSPRate(direction);
    std::vector<double> rates;
    for (int i = 5; i >= 0; i--)
    {
        rates.push_back(baseRate/(1 << i));
    }
    return rates;
}

/*******************************************************************
 * BW filter API
 ******************************************************************/
void EVB7::setBandwidth(const int direction, const size_t channel, const double bw)
{
    double &actualBw = _cachedFilterBws[direction][channel];
    if (direction == SOAPY_SDR_RX)
    {
        actualBw = LMS7002M_rbb_set_filter_bw(_lms, ch2LMS(channel), bw);
    }
    if (direction == SOAPY_SDR_TX)
    {
        actualBw = LMS7002M_tbb_set_filter_bw(_lms, ch2LMS(channel), bw);
    }
}

double EVB7::getBandwidth(const int direction, const size_t channel) const
{
    return _cachedFilterBws.at(direction).at(channel);
}

std::vector<double> EVB7::listBandwidths(const int direction, const size_t) const
{
    std::vector<double> bws;

    if (direction == SOAPY_SDR_RX)
    {
        bws.push_back(1.4e6);
        bws.push_back(3.0e6);
        bws.push_back(5.0e6);
        bws.push_back(10.0e6);
        bws.push_back(15.0e6);
        bws.push_back(20.0e6);
        bws.push_back(37.0e6);
        bws.push_back(66.0e6);
        bws.push_back(108.0e6);
    }
    if (direction == SOAPY_SDR_TX)
    {
        bws.push_back(2.4e6);
        bws.push_back(2.74e6);
        bws.push_back(5.5e6);
        bws.push_back(8.2e6);
        bws.push_back(11.0e6);
        bws.push_back(18.5e6);
        bws.push_back(38.0e6);
        bws.push_back(54.0e6);
    }

    return bws;
}

/*******************************************************************
 * Clocking API
 ******************************************************************/
double EVB7::getTSPRate(const int direction) const
{
    return (direction == SOAPY_SDR_TX)? _masterClockRate : _masterClockRate/4;
}

void EVB7::setMasterClockRate(const double rate)
{
    int ret = LMS7002M_set_data_clock(_lms, EXT_REF_CLK, rate, &_masterClockRate);
    if (ret != 0)
    {
        SoapySDR::logf(SOAPY_SDR_ERROR, "LMS7002M_set_data_clock(%f MHz) -> %d", rate/1e6, ret);
        throw std::runtime_error("EVB7 fail LMS7002M_set_data_clock()");
    }
    SoapySDR::logf(SOAPY_SDR_TRACE, "LMS7002M_set_data_clock(%f MHz) -> %f MHz", rate/1e6, _masterClockRate/1e6);
}

double EVB7::getMasterClockRate(void) const
{
    return _masterClockRate;
}

/*******************************************************************
 * Time API
 ******************************************************************/
bool EVB7::hasHardwareTime(const std::string &what) const
{
    if (what.empty()) return true;
    return false;
}

long long EVB7::getHardwareTime(const std::string &) const
{
    long long timeLo = this->readRegister(FPGA_REG_RD_TIME_LO);
    long long timeHi = this->readRegister(FPGA_REG_RD_TIME_HI);
    return this->ticksToTimeNs((timeHi << 32) | timeLo);
}

void EVB7::setHardwareTime(const long long timeNs, const std::string &)
{
    long long ticks = this->timeNsToTicks(timeNs);
    this->writeRegister(FPGA_REG_WR_TIME_LO, ticks & 0xffffffff);
    this->writeRegister(FPGA_REG_WR_TIME_HI, ticks >> 32);
    this->writeRegister(FPGA_REG_WR_TIME_LATCH, 1);
    this->writeRegister(FPGA_REG_WR_TIME_LATCH, 0);
}

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
