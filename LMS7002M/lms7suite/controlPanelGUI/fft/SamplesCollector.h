/**
@file 	SamplesCollector.h
@author Lime Microsystems
*/

#ifndef SAMPLES_GENERATOR
#define SAMPLES_GENERATOR

#ifndef __unix__
    #include <windows.h>
#endif
#include "BlockingFIFO.h"
#include "lmThread.h"
#include "ConnectionManager.h"

#include "Packets.h"
using namespace std;

enum eBOARD_FFT_SOURCE
{
    BOARD_UNKNOWN = -1,
    BOARD_DIGIGREEN,
    BOARD_DIGIRED,
    BOARD_NOVENA,
    BOARD_STREAM
};

class SamplesCollector
{
public:
    SamplesCollector(ConnectionManager *m_controlPort, ConnectionManager *m_dataPort, BlockingFIFO<SamplesPacket> *channels);
    ~SamplesCollector();

    bool StartSampling();
    void StopSampling();

    bool m_running;
    float m_dataRate;
    unsigned long m_packetsDiscarded;

    bool SetPacketSize(int samplesCount);
    void SwitchSource(eBOARD_FFT_SOURCE device);
    void SetWriteToFile(bool writeToFile, const char* filename, unsigned long frames_limit);

    int m_dataSource;
    int frameStart;
protected:
    BlockingFIFO<SamplesPacket> *m_channels;
    int m_channelsCount;

    eBOARD_FFT_SOURCE m_selectedDevice;
    int m_samplesToPacket;
    ConnectionManager *m_controlPort;
    ConnectionManager *m_dataPort;
    static void* DigiGreenSamplingThread(void* pCollector);
    static void* DigiRedSamplingThread(void* pCollector);
    static void* StreamSamplingThread(void* pCollector);
    static void* TestingSamplingThread(void* pCollector);
    lmThread m_samplingThread;

    bool m_writeToFile;
    string m_filename;
    unsigned long m_framesLimit;
};

#endif // SAMPLES_GENERATOR

