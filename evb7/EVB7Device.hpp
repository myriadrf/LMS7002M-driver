//
// SoapySDR wrapper for the LMS7002M driver.
//
// Copyright (c) 2015-2015 Fairwaves, Inc.
// Copyright (c) 2015-2015 Rice University
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
//

#include "EVB7Regs.hpp"
#include "twbw_helper.h"
#include "spidev_interface.h"
#include "sysfs_gpio_interface.h"
#include "xilinx_user_gpio.h"
#include "xilinx_user_mem.h"

#include <SoapySDR/Device.hpp>
#include <SoapySDR/Logger.hpp>
#include <SoapySDR/Time.hpp>
#include <pothos_zynq_dma_driver.h>
#include <mutex>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

#include <LMS7002M/LMS7002M.h>

class EVB7 : public SoapySDR::Device
{
public:
    EVB7(void);

    ~EVB7(void);

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
        const SoapySDR::Kwargs &);

    void rxFlush(void);

    void closeStream(SoapySDR::Stream *stream);

    size_t getStreamMTU(SoapySDR::Stream *stream) const;

    int sendControlMessage(const int tag, const bool timeFlag, const bool burstFlag, const int frameSize, const int burstSize, const long long time);

    int convertRemainder(SoapySDR::Stream *stream, void *outp, const size_t numOutSamps, int &flags);

    int activateStream(
        SoapySDR::Stream *stream,
        const int flags,
        const long long timeNs,
        const size_t numElems);

    int deactivateStream(
        SoapySDR::Stream *stream,
        const int flags,
        const long long timeNs);

    int readStream(
        SoapySDR::Stream *,
        void * const *buffs,
        const size_t numElems,
        int &flags,
        long long &timeNs,
        const long timeoutUs);

    int writeStream(
        SoapySDR::Stream *,
        const void * const *buffs,
        const size_t numElems,
        int &flags,
        const long long timeNs,
        const long timeoutUs
    );

    int readStreamStatus(
        SoapySDR::Stream *stream,
        size_t &chanMask,
        int &flags,
        long long &timeNs,
        const long timeoutUs);

    size_t getNumDirectAccessBuffers(SoapySDR::Stream *stream);
    int getDirectAccessBufferAddrs(SoapySDR::Stream *stream, const size_t handle, void **buffs);

    int acquireReadBuffer(
        SoapySDR::Stream *stream,
        size_t &handle,
        const void **buffs,
        int &flags,
        long long &timeNs,
        const long timeoutUs);

    void releaseReadBuffer(
        SoapySDR::Stream *stream,
        const size_t handle);

    int acquireWriteBuffer(
        SoapySDR::Stream *stream,
        size_t &handle,
        void **buffs,
        const long timeoutUs);

    void releaseWriteBuffer(
        SoapySDR::Stream *stream,
        const size_t handle,
        const size_t numElems,
        int &flags,
        const long long timeNs);

    //rx streaming
    int _remainderHandle;
    size_t _remainderSamps;
    const uint32_t *_remainderBuff;

    //tx streaming
    bool _userHandlesTxStatus;

    //stream configuration
    enum StreamFormat
    {
        SF_CS16,
        SF_CF32,
    };
    StreamFormat _rxFormat;
    StreamFormat _txFormat;

    /*******************************************************************
     * Antenna API
     ******************************************************************/
    std::vector<std::string> listAntennas(const int direction, const size_t channel) const;
    void setAntenna(const int direction, const size_t channel, const std::string &name);
    std::string getAntenna(const int direction, const size_t channel) const;

    std::map<int, std::map<size_t, std::string>> _cachedAntValues;

    /*******************************************************************
     * Frontend corrections API
     ******************************************************************/
    bool _rxDCOffsetMode;
    std::complex<double> _txDCOffset;

    void setDCOffsetMode(const int direction, const size_t channel, const bool automatic);

    bool getDCOffsetMode(const int direction, const size_t channel) const;

    void setDCOffset(const int direction, const size_t channel, const std::complex<double> &offset);

    std::complex<double> getDCOffset(const int direction, const size_t channel) const;

    void setIQBalance(const int direction, const size_t channel, const std::complex<double> &balance);

    std::complex<double> getIQBalance(const int direction, const size_t channel) const;

    std::map<int, std::map<size_t, std::complex<double>>> _cachedIqBalValues;

    /*******************************************************************
     * Gain API
     ******************************************************************/
    std::vector<std::string> listGains(const int direction, const size_t channel) const;
    void setGain(const int direction, const size_t channel, const std::string &name, const double value);
    double getGain(const int direction, const size_t channel, const std::string &name) const;
    SoapySDR::Range getGainRange(const int direction, const size_t channel, const std::string &name) const;

    std::map<int, std::map<size_t, std::map<std::string, double>>> _cachedGainValues;

    /*******************************************************************
     * Frequency API
     ******************************************************************/
    void setFrequency(const int direction, const size_t channel, const std::string &, const double frequency, const SoapySDR::Kwargs &args);
    double getFrequency(const int direction, const size_t channel, const std::string &name) const;
    std::vector<std::string> listFrequencies(const int, const size_t) const;
    SoapySDR::RangeList getFrequencyRange(const int, const size_t, const std::string &) const;

    std::map<int, std::map<size_t, std::map<std::string, double>>> _cachedFreqValues;

    /*******************************************************************
     * Sample Rate API
     ******************************************************************/
    void setSampleRate(const int direction, const size_t, const double rate);
    double getSampleRate(const int direction, const size_t) const;
    std::vector<double> listSampleRates(const int direction, const size_t) const;

    std::map<int, double> _cachedSampleRates;

    /*******************************************************************
     * BW filter API
     ******************************************************************/
    void setBandwidth(const int direction, const size_t channel, const double bw);
    double getBandwidth(const int direction, const size_t channel) const;
    std::vector<double> listBandwidths(const int direction, const size_t channel) const;

    std::map<int, std::map<size_t, double>> _cachedFilterBws;

    /*******************************************************************
     * Clocking API
     ******************************************************************/
    double getTSPRate(const int direction) const;
    void setMasterClockRate(const double rate);
    double getMasterClockRate(void) const;

    /*******************************************************************
     * Time API
     ******************************************************************/

    long long ticksToTimeNs(const long long ticks) const
    {
        return SoapySDR::ticksToTimeNs(ticks, IF_TIME_CLK);
    }

    long long timeNsToTicks(const long long timeNs) const
    {
        return SoapySDR::timeNsToTicks(timeNs, IF_TIME_CLK);
    }

    bool hasHardwareTime(const std::string &what) const;
    long long getHardwareTime(const std::string &) const;
    void setHardwareTime(const long long timeNs, const std::string &);

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

    /*!
     * Write arbitrary settings in the form of key/value pairs
     * that are otherwise not covered by the other API calls.
     * Example: setting loopback and test modes.
     *
     * - FPGA_TX_TEST(TRUE/FALSE) - in test mode, the normal TX path is bypassed,
     *   and a constant level configured by FPGA_TSG_CONST is driven into TX DIQ.
     *   When test mode is off, this value drives the input to the CORDIC when idle.
     *
     * - RXTSP_ENABLE(TRUE/FALSE) - call the RX TSP enable routine.
     *   Call with TRUE (enable) to reapply default settings.
     *
     * - TXTSP_ENABLE(TRUE/FALSE) - call the TX TSP enable routine.
     *   Call with TRUE (enable) to reapply default settings.
     *
     * - RBB_ENABLE(TRUE/FALSE) - call the RX baseband enable routine.
     *   Call with TRUE (enable) to reapply default settings.
     *
     * - TBB_ENABLE(TRUE/FALSE) - call the TX baseband enable routine.
     *   Call with TRUE (enable) to reapply default settings.
     *
     * - RXTSP_TSG_CONST(amplitude) - set the RX digital signal generator
     *   for a constant valued output.
     *
     * - TXTSP_TSG_CONST(amplitude) - set the TX digital signal generator
     *   for a constant valued output.
     *
     * - TBB_ENABLE_LOOPBACK(path) - enable TX baseband loopback.
     *   Use LB_DISCONNECTED, LB_DAC_CURRENT, LB_LB_LADDER, or LB_MAIN_TBB for the path.
     *
     * - RBB_SET_PATH(path) set the RX baseband input path.
     *   Use BYP, LBF, HBF for bypassing or filter path.
     *   Use LB_BYP, LB_LBF, LB_HBF for loopback versions.
     *
     * - FPGA_TSG_CONST(amplitude) - set the FPGA's TX digital signal generator
     *   for a constant valued output. When FPGA_TX_TEST is FALSE,
     *   this value drives the TX FPGA CORDIC when no user stream is applied.
     *   When FPGA_TX_TEST is TRUE, this value directly drives the TX DIQ bus.
     */
    void writeSetting(const std::string &key, const std::string &value);

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

    LMS7002M_dir_t dir2LMS(const int direction) const
    {
        return (direction == SOAPY_SDR_RX)?LMS_RX:LMS_TX;
    }

    LMS7002M_chan_t ch2LMS(const size_t channel) const
    {
        return (channel == 0)?LMS_CHA:LMS_CHB;
    }

    const char *dir2Str(const int direction) const
    {
        return (direction == SOAPY_SDR_RX)?"RX":"TX";
    }

    void *_regs;
    void *_spiHandle;
    LMS7002M_t *_lms;
    pzdud_t *_rx_data_dma;
    pzdud_t *_rx_ctrl_dma;
    pzdud_t *_tx_data_dma;
    pzdud_t *_tx_stat_dma;
    double _masterClockRate;

    //register protection
    std::mutex _mutex;
};
