//
// SoapySDR wrapper for the LMS7002M driver.
//
// Copyright (c) 2015-2015 Fairwaves, Inc.
// Copyright (c) 2015-2015 Rice University
// SPDX-License-Identifier: Apache-2.0
// http://www.apache.org/licenses/LICENSE-2.0
//

#include "EVB7Device.hpp"
#include <arm_neon.h>

/*******************************************************************
 * Conversions
 ******************************************************************/
void convert_cs16_to_word32(const void *inp, void *outp, const size_t n)
{
    std::memcpy(outp, inp, n*sizeof(uint32_t));
}

void convert_cf32_to_word32(const void *inp, void *outp, const size_t n)
{
    const float *in = (const float *)inp;
    int16_t *out = (int16_t *)outp;
    for (size_t i = 0; i < n; i+=2) //simd convert 2 complex samples
    {
        float32x4_t sampsf = vld1q_f32(in);
        float32x4_t scaled = vmulq_n_f32(sampsf, float32_t(30e3f));
        int32x4_t samps32 = vcvtq_s32_f32(scaled);
        int16x4_t samps16 = vmovn_s32(samps32);
        vst1_s16(out, samps16);
        out += 4;
        in += 4;
    }
    if ((n % 2) == 1) //remainder
    {
        *(out++) = int16_t(*(in++)*30e3f);
        *(out++) = int16_t(*(in++)*30e3f);
    }
}

void convert_word32_to_cs16(const void *inp, void *outp, const size_t n)
{
    std::memcpy(outp, inp, n*sizeof(uint32_t));
}

void convert_word32_to_cf32(const void *inp, void *outp, const size_t n)
{
    const int16_t *in = (const int16_t *)inp;
    float *out = (float *)outp;
    for (size_t i = 0; i < n; i+=2) //simd convert 2 complex samples
    {
        int16x4_t samps16 = vld1_s16(in);
        int32x4_t samps32 = vmovl_s16(samps16);
        float32x4_t sampsf = vcvtq_f32_s32(samps32);
        float32x4_t scaled = vmulq_n_f32(sampsf, float32_t(1.0/30e3f));
        vst1q_f32(out, scaled);
        out += 4;
        in += 4;
    }
    if ((n % 2) == 1) //remainder
    {
        *(out++) = float(*(in++)/30e3f);
        *(out++) = float(*(in++)/30e3f);
    }
}

/*******************************************************************
 * Stream config
 ******************************************************************/
SoapySDR::Stream *EVB7::setupStream(
    const int direction,
    const std::string &format,
    const std::vector<size_t> &channels,
    const SoapySDR::Kwargs &)
{
    //check the format config
    StreamFormat f;
    if (format == "CS16") f = SF_CS16;
    else if (format == "CF32") f = SF_CF32;
    else throw std::runtime_error("EVB7::setupStream: "+format);

    //check the channel config
    if (channels.size() != 1 or channels[0] != 0) throw std::runtime_error("EVB7::setupStream: only one channel supported");

    //store the format
    if (direction == SOAPY_SDR_TX) _txFormat = f;
    if (direction == SOAPY_SDR_RX) _rxFormat = f;

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

    return nullptr;
}

void EVB7::rxFlush(void)
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

void EVB7::closeStream(SoapySDR::Stream *stream)
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

size_t EVB7::getStreamMTU(SoapySDR::Stream *stream) const
{
    if (stream == reinterpret_cast<SoapySDR::Stream *>(_rx_data_dma)) return RX_FRAME_SIZE;
    if (stream == reinterpret_cast<SoapySDR::Stream *>(_tx_data_dma)) return TX_FRAME_SIZE;
    return SoapySDR::Device::getStreamMTU(stream);
}

int EVB7::sendControlMessage(const int tag, const bool timeFlag, const bool burstFlag, const int frameSize, const int burstSize, const long long time)
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

int EVB7::activateStream(
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

int EVB7::deactivateStream(
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

int EVB7::convertRemainder(void *outp, const size_t numOutSamps, int &flags)
{
    if (_remainderHandle == -1) return 0; //nothing

    //convert the maximum possible number of samples
    const size_t n = std::min(_remainderSamps, numOutSamps);
    switch (_rxFormat)
    {
    case SF_CS16: convert_word32_to_cs16(_remainderBuff, outp, n); break;
    case SF_CF32: convert_word32_to_cf32(_remainderBuff, outp, n); break;
    }

    //deal with remainder and releasing buffer if done
    _remainderBuff += n;
    _remainderSamps -= n;
    if (_remainderSamps == 0)
    {
        this->releaseReadBuffer((SoapySDR::Stream *)SOAPY_SDR_RX, _remainderHandle);
        _remainderHandle = -1;
    }
    else
    {
        flags |= SOAPY_SDR_MORE_FRAGMENTS;
    }

    return n;
}

int EVB7::readStream(
    SoapySDR::Stream *stream,
    void * const *buffs,
    const size_t numElems,
    int &flags,
    long long &timeNs,
    const long timeoutUs)
{
    int ret = 0;

    //check remainder
    ret = this->convertRemainder(buffs[0], numElems, flags);
    if (ret != 0) return ret;

    //call into direct buffer access
    size_t handle;
    const void *payload;
    ret = this->acquireReadBuffer(stream, handle, &payload, flags, timeNs, timeoutUs);
    if (ret < 0) return ret;

    //no errors, convert good buffer
    //stash conversion
    _remainderHandle = handle;
    _remainderBuff = (const uint32_t *)payload;
    _remainderSamps = ret;
    const size_t numConvert(std::min(numElems, size_t(ret)));
    return this->convertRemainder(buffs[0], numConvert, flags);
}

int EVB7::writeStream(
    SoapySDR::Stream *stream,
    const void * const *buffs,
    const size_t numElems,
    int &flags,
    const long long timeNs,
    const long timeoutUs
)
{
    //acquire from direct buffer access
    size_t handle;
    void *payload;
    int ret = this->acquireWriteBuffer(stream, handle, &payload, timeoutUs);
    if (ret < 0) return ret;

    //only end burst if the last sample can be released
    const size_t numSamples = std::min<size_t>(ret, numElems);
    if (numSamples < numElems) flags &= ~(SOAPY_SDR_END_BURST);

    //convert the samples
    switch (_txFormat)
    {
    case SF_CS16: convert_cs16_to_word32(buffs[0], payload, numSamples); break;
    case SF_CF32: convert_cf32_to_word32(buffs[0], payload, numSamples); break;
    }

    //release to direct buffer access
    this->releaseWriteBuffer(stream, handle, numSamples, flags, timeNs);
    return numSamples;
}

int EVB7::readStreamStatus(
    SoapySDR::Stream *stream,
    size_t &chanMask,
    int &flags,
    long long &timeNs,
    const long timeoutUs)
{
    if (stream != reinterpret_cast<SoapySDR::Stream *>(_tx_data_dma)) return SOAPY_SDR_NOT_SUPPORTED;

    //didnt get the magic keyword? then user is calling: disable tx auto stat read
    #define AUTO_READ_STAT_MAGIC 0x1234ABCD
    if (flags != AUTO_READ_STAT_MAGIC) _userHandlesTxStatus = true;

    chanMask = (1 << 0); //always ch0

    if (pzdud_wait(_tx_stat_dma, timeoutUs) != 0) return SOAPY_SDR_TIMEOUT;

    size_t len = 0;
    int handle = pzdud_acquire(_tx_stat_dma, &len);
    bool underflow;
    int idTag = 0;
    bool hasTime;
    long long timeTicks;
    bool timeError;
    bool burstEnd;
    twbw_deframer_stat_unpacker(
        pzdud_addr(_tx_stat_dma, handle), len,
        underflow, idTag, hasTime, timeTicks, timeError, burstEnd);

    //gather time even if its not valid
    timeNs = this->ticksToTimeNs(timeTicks);

    //error indicators
    if (hasTime) flags |= SOAPY_SDR_HAS_TIME;
    if (burstEnd) flags |= SOAPY_SDR_END_BURST;

    //SoapySDR::logf(SOAPY_SDR_TRACE, "handle=%d, TxStat=%d", handle, idTag);
    if (underflow) std::cerr << "U" << std::flush;
    if (timeError) std::cerr << "T" << std::flush;

    pzdud_release(_tx_stat_dma, handle, len);

    if (timeError) return SOAPY_SDR_TIME_ERROR;
    if (underflow) return SOAPY_SDR_UNDERFLOW;
    return 0;
}

size_t EVB7::getNumDirectAccessBuffers(SoapySDR::Stream *)
{
    return DATA_NUM_BUFFS;
}

int EVB7::acquireReadBuffer(
    SoapySDR::Stream *stream,
    size_t &handleOut,
    const void **buffs,
    int &flags,
    long long &timeNs,
    const long timeoutUs)
{
    pzdud_t *data_dma = (pzdud_t *)stream;

    size_t len = 0;
    int ret = 0;
    flags = 0;

    //wait with timeout then acquire
    if (pzdud_wait(data_dma, timeoutUs) != 0) return SOAPY_SDR_TIMEOUT;
    int handle =  pzdud_acquire(data_dma, &len);
    if (handle == PZDUD_ERROR_CLAIMED) throw std::runtime_error("EVB7::readStream() all claimed");
    handleOut = handle;

    //unpack the header
    size_t numSamples;
    bool overflow;
    int idTag;
    bool hasTime;
    long long timeTicks;
    bool timeError;
    bool isBurst;
    bool burstEnd;
    twbw_framer_data_unpacker(
        pzdud_addr(data_dma, handle), len, sizeof(uint32_t),
        buffs[0], numSamples, overflow, idTag,
        hasTime, timeTicks,
        timeError, isBurst, burstEnd);

    //gather time even if its not valid
    timeNs = this->ticksToTimeNs(timeTicks);

    //error indicators
    if (overflow) flags |= SOAPY_SDR_END_ABRUPT;
    if (hasTime) flags |= SOAPY_SDR_HAS_TIME;
    if (burstEnd) flags |= SOAPY_SDR_END_BURST;

    //old packet from the deactivate command, just ignore it with timeout
    if (idTag == RX_TAG_ACTIVATE)
    {
        ret = SOAPY_SDR_TIMEOUT;
    }

    //not an activate or deactivate tag, this is bad!
    else if (idTag != RX_TAG_DEACTIVATE)
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
        std::cerr << "O" << std::flush;
        sendControlMessage( //restart streaming
            RX_TAG_ACTIVATE,
            false, //timeFlag
            false, //burstFlag
            RX_FRAME_SIZE, 0, 0);
    }

    return (ret == 0)?numSamples:ret;
}

void EVB7::releaseReadBuffer(
    SoapySDR::Stream *stream,
    const size_t handle)
{
    pzdud_release((pzdud_t *)stream, handle, 0);
}

int EVB7::acquireWriteBuffer(
    SoapySDR::Stream *stream,
    size_t &handleOut,
    void **buffs,
    const long timeoutUs)
{
    pzdud_t *data_dma = (pzdud_t *)stream;
    size_t len = 0;

    //handle stat reporting when user isnt
    if (not _userHandlesTxStatus)
    {
        size_t chanMask = 0;
        int flags_s = AUTO_READ_STAT_MAGIC;
        long long timeNs_s = 0;
        this->readStreamStatus(stream, chanMask, flags_s, timeNs_s, 0);
    }

    //wait with timeout then acquire
    if (pzdud_wait(data_dma, timeoutUs) != 0) return SOAPY_SDR_TIMEOUT;
    int handle = pzdud_acquire(data_dma, &len);
    if (handle == PZDUD_ERROR_CLAIMED) throw std::runtime_error("EVB7::writeStream() all claimed");
    handleOut = handle;

    //offset by header space
    buffs[0] = ((uint32_t *)pzdud_addr(data_dma, handle)) + 4;
    return (len/sizeof(uint32_t)) - 4;
}

void EVB7::releaseWriteBuffer(
    SoapySDR::Stream *stream,
    const size_t handle,
    const size_t numElems,
    int &flags,
    const long long timeNs)
{
    pzdud_t *data_dma = (pzdud_t *)stream;
    static int id = 0;

    //pack the header
    void *payload;
    size_t len = 0;
    const bool hasTime((flags & SOAPY_SDR_HAS_TIME) != 0);
    const long long timeTicks(this->timeNsToTicks(timeNs));
    const bool burstEnd((flags & SOAPY_SDR_END_BURST) != 0);

    twbw_deframer_data_packer(
        pzdud_addr(data_dma, handle), len, sizeof(uint32_t),
        payload, numElems, id++, hasTime, timeTicks, burstEnd);

    //release the buffer back the SG engine
    pzdud_release(data_dma, handle, len);
}
