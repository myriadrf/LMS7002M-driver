/**
@file 	SamplesCollector.cpp
@author Lime Microsystems
@brief 	Class for IQ samples data acquisition from board
*/
#include "SamplesCollector.h"
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include "CommonUtilities.h"
#define M_PI 3.14159265359

SamplesCollector::SamplesCollector(ConnectionManager *controlPort, ConnectionManager *dataPort, BlockingFIFO<SamplesPacket> *channels) : m_running(false)
{
    frameStart = 0;
    m_packetsDiscarded = 0;
    m_channels = channels;
    m_selectedDevice = BOARD_UNKNOWN;
    m_samplesToPacket = 16384;
    m_dataRate = 0;
    m_controlPort = controlPort;
    m_dataPort = dataPort;

    m_writeToFile = false;
    m_filename = "DataInStream_bin.txt";
    m_framesLimit = 16384;
    m_dataSource = 0;
}

SamplesCollector::~SamplesCollector()
{

}

/** @brief Gets connected board type and starts it's sampling process
*/
bool SamplesCollector::StartSampling()
{
    if(m_channels == NULL)
    {
        fprintf(stderr, "Samples collector has no assigned data buffers!\n");
        return false;
    }

    m_running = true;
    m_selectedDevice = BOARD_STREAM;
    switch(m_selectedDevice)
    {
    case BOARD_STREAM:
		lmThread_create(m_samplingThread, &StreamSamplingThread, this);
        break;
    case BOARD_UNKNOWN:
    default:
        m_running = false;
        return false;
    }
    return true;
}

/** @brief Signals to stop sampling process and blocks until sampling is finished
*/
void SamplesCollector::StopSampling()
{
    printf("Stopping\n");
    m_running = false;
    lmThread_join(m_samplingThread);
}

/** @brief Sampling procedure for DigiRed board
    @param pCollector pointer to Samples Collector
*/
void* SamplesCollector::StreamSamplingThread(void* pCollector)
{
    int samplesCollected = 0;
    int buffer_size = 4096*64;
    const int buffers_count = 32; // must be power of 2
    int buffers_count_mask = buffers_count-1;
    int handles[buffers_count];
    memset(handles, 0, sizeof(int)*buffers_count);
    char *buffers = NULL;
    buffers = new char[buffers_count*buffer_size];
    if(buffers == 0)
    {
        printf("error allocating buffers\n");
        return 0;
    }
    memset(buffers, 0, buffers_count*buffer_size);

    SamplesCollector *pthis;
    pthis = static_cast<SamplesCollector*>(pCollector);
    pthis->m_dataRate = 0;
    pthis->m_packetsDiscarded = 0;
    SamplesPacket *samples = new SamplesPacket(pthis->m_samplesToPacket);

    unsigned long t1, t2; //timers for data rate calculation
    t1 = getMilis();
    t2 = t1;
    unsigned long totalBytesReceived = 0;

    short tempInt = 0;
    int bi = 0; //buffer index

    fstream fout;
    fstream foutI;
    fstream foutQ;
    bool wToFile = pthis->m_writeToFile;
    unsigned long framesLimit = pthis->m_framesLimit; // 1 frame = 4 bytes
    unsigned long framesCaptured = 0;
    if(wToFile)
    {
        fout.open(pthis->m_filename.c_str(), ios::out | ios::binary);
        foutI.open("Isamples.txt", ios::out);
        foutQ.open("Qsamples.txt", ios::out);
    }

    unsigned char ctrbuf[64];
    unsigned char inbuf[64];
    memset(ctrbuf, 0, 64);
    ctrbuf[0] = CMD_BRDSPI_RD;
    ctrbuf[1] = 0;
    ctrbuf[2] = 0x01;
    ctrbuf[8] = 0x00;
    ctrbuf[9] = 0x05;
    pthis->m_dataPort->Port_write_direct(ctrbuf, 64);
    long len = 64;
    pthis->m_dataPort->Port_read_direct(inbuf, len);
    unsigned short regVal = (inbuf[10] * 256) + inbuf[11];
    ctrbuf[0] = CMD_BRDSPI_WR;
    ctrbuf[1] = 0;
    ctrbuf[2] = 0x01;
    ctrbuf[8] = 0x00;
    ctrbuf[9] = 0x05;
    ctrbuf[10] = 0;
    ctrbuf[11] = regVal | 0x4;
    pthis->m_dataPort->Port_write_direct(ctrbuf, 64);
    len = 64;
    pthis->m_dataPort->Port_read_direct(inbuf, len);

    for (int i=0; i<buffers_count; ++i)
		handles[i] = pthis->m_dataPort->BeginDataReading(&buffers[i*buffer_size], buffer_size);

    long m_bufferFailures = 0;
    long bytesToRead = 0;
    long packetsReceived = 0;

    bool skip = false;
    while(pthis->m_running)
    {
        if(pthis->m_dataPort->WaitForReading(handles[bi], 1000) == false)
		{
			++m_bufferFailures;
		}
		// Must always call FinishDataXfer to release memory of contexts[i]
		bytesToRead = buffer_size;
		if (pthis->m_dataPort->FinishDataReading(&buffers[bi*buffer_size], bytesToRead, handles[bi]))
  		{
			++packetsReceived;
			totalBytesReceived += bytesToRead;
			if(wToFile && framesCaptured < framesLimit)
            {
                fout.write((const char*)&buffers[bi*buffer_size], bytesToRead);
            }
			skip = false;
		}
		else
		{
			++m_bufferFailures;
			skip = true;
		}

        t2 = getMilis();
        if( t2 - t1 >= 1000)
        {
            pthis->m_dataRate = 1000.0*totalBytesReceived/(t2-t1);
            t1 = t2;
            totalBytesReceived = 0;
            printf("Download rate: %f\tDiscarded packets:%li failures:%li\n", pthis->m_dataRate, pthis->m_packetsDiscarded, m_bufferFailures);
            pthis->m_channels[0].status();
            pthis->m_packetsDiscarded = 0;
            m_bufferFailures = 0;
        }

        short* buf;
        buf = (short*)&buffers[bi*buffer_size];
        int framestart = 1;
        for(int b=0; b<buffer_size/2 && !skip; ++b)
        {
            if(samplesCollected == 0)
            {
                //find frame start
                for(int fs=b; fs<buffer_size/2; ++fs)
                {
                    if( ((buf[b]&0x1000)>0) == framestart)
                        break;
                    ++b;
                }
            }
            tempInt = buf[b] & 0x0FFF;
            tempInt = tempInt << 4;
            samples->iqdata[samplesCollected] = tempInt >> 4;
            ++samplesCollected;
            if(samplesCollected >= samples->samplesCount)
            {
                for(int ss=0; ss<samples->samplesCount && framesCaptured < framesLimit; ss+=2)
                {
                    foutI << samples->iqdata[ss] << endl;
                    foutQ << samples->iqdata[ss+1] << endl;
                    ++framesCaptured;
                }
                if(pthis->m_channels[0].push_back(samples, 0) == false)
                    ++pthis->m_packetsDiscarded;
                samplesCollected = 0;
				break;
            }
        }

        // Re-submit this request to keep the queue full
        memset(&buffers[bi*buffer_size], 0, buffer_size);
        handles[bi] = pthis->m_dataPort->BeginDataReading(&buffers[bi*buffer_size], buffer_size);
        bi = (bi+1) & buffers_count_mask;
    }

    // Wait for all the queued requests to be cancelled
    pthis->m_dataPort->AbortReading();
	for(int j=0; j<buffers_count; j++)
	{
		bytesToRead = buffer_size;
		pthis->m_dataPort->WaitForReading(handles[j], 1000);
		pthis->m_dataPort->FinishDataReading(&buffers[j*buffer_size], bytesToRead, handles[j]);
	}
	memset(ctrbuf, 0, 64);
    ctrbuf[0] = CMD_BRDSPI_RD;
    ctrbuf[1] = 0;
    ctrbuf[2] = 0x01;
    ctrbuf[8] = 0x00;
    ctrbuf[9] = 0x05;
    pthis->m_dataPort->Port_write_direct(ctrbuf, 64);
    len = 64;
    pthis->m_dataPort->Port_read_direct(inbuf, len);
    regVal = (inbuf[10] * 256) + inbuf[11];
    ctrbuf[0] = CMD_BRDSPI_WR;
    ctrbuf[1] = 0;
    ctrbuf[2] = 0x01;
    ctrbuf[8] = 0x00;
    ctrbuf[9] = 0x05;
    ctrbuf[10] = 0;
    ctrbuf[11] = regVal & ~0x4;
    pthis->m_dataPort->Port_write_direct(ctrbuf, 64);
    len = 64;
    pthis->m_dataPort->Port_read_direct(inbuf, len);
	fout.close();
	foutI.close();
	foutQ.close();
	delete []buffers;
	delete samples;
    printf("FULLY STOPPED\n");
    return 0;
}

/** @brief Sampling procedure for DigiRed board
    @param pCollector pointer to Samples Collector
*/
void* SamplesCollector::TestingSamplingThread(void* pCollector)
{
    int samplesCollected = 0;
    int buffer_size = 16384*4;
    const int buffers_count = 32; // must be power of 2
    int buffers_count_mask = buffers_count-1;
    int handles[buffers_count];
    memset(handles, 0, sizeof(int)*buffers_count);
    char *buffers = NULL;
    buffers = new char[buffers_count*buffer_size];
    if(buffers == 0)
    {
        printf("error allocating buffers\n");
        return 0;
    }
    memset(buffers, 0, buffers_count*buffer_size);

    SamplesCollector *pthis;
    pthis = static_cast<SamplesCollector*>(pCollector);
    pthis->m_dataRate = 0;
    pthis->m_packetsDiscarded = 0;
    SamplesPacket *samples = new SamplesPacket(pthis->m_samplesToPacket);

    unsigned long t1, t2; //timers for data rate calculation
    t1 = getMilis();
    t2 = t1;
    unsigned long totalBytesReceived = 0;

    short tempInt = 0;
    int bi = 0; //buffer index

    fstream fout;
    bool wToFile = pthis->m_writeToFile;
    unsigned long fileSizeLimit = pthis->m_framesLimit;
    unsigned long fileSize = 0;
    if(wToFile)
        fout.open(pthis->m_filename.c_str(), ios::out | ios::binary);

    long m_bufferFailures = 0;
    long bytesToRead = 0;
    long packetsReceived = 0;

    bool skip = false;

    double Fs = 15;
    double timeIndex = 0;
    double timeStep = 1/Fs;
    double freqMHz = 1;

    while(pthis->m_running)
    {
		// Must always call FinishDataXfer to release memory of contexts[i]
		bytesToRead = buffer_size;
		short *gbuf = (short*)&buffers[bi*buffer_size];
		for(int i=0; i<(bytesToRead)/sizeof(short); i+=2)
        {
            gbuf[i] = 1024*cos(2*M_PI*freqMHz*timeIndex);            			
            gbuf[i+1] = 1024*cos(2*M_PI*freqMHz*timeIndex-M_PI/2);
			gbuf[i+1] |= 0x1000;
            timeIndex+=timeStep;
        }
        milSleep(1);
        ++packetsReceived;
        totalBytesReceived += bytesToRead;

        t2 = getMilis();
        if( t2 - t1 >= 1000)
        {
            pthis->m_dataRate = 1000.0*totalBytesReceived/(t2-t1);
            t1 = t2;
            totalBytesReceived = 0;
            printf("Download rate: %f\tDiscarded packets:%li failures:%li\n", pthis->m_dataRate, pthis->m_packetsDiscarded, m_bufferFailures);
            pthis->m_channels[0].status();
            pthis->m_packetsDiscarded = 0;
            m_bufferFailures = 0;
        }

        short* buf;
        buf = (short*)&buffers[bi*buffer_size];
        int framestart = pthis->frameStart;
        for(int b=0; b<buffer_size/2 && !skip; ++b)
        {
            if(samplesCollected == 0)
            {
                //find frame start
                for(int fs=b; fs<buffer_size/2; ++fs)
                {
                    if( ((buf[b]&0x1000)>0) == (framestart>0))
                        break;
                    ++b;
                }
            }
            tempInt = buf[b] & 0x0FFF;
            tempInt = tempInt << 4;
            samples->iqdata[samplesCollected] = tempInt >> 4;
            ++samplesCollected;
            if(samplesCollected >= samples->samplesCount)
            {
                if(pthis->m_channels[0].push_back(samples, 0) == false)
                    ++pthis->m_packetsDiscarded;
                samplesCollected = 0;
				break;
            }
        }

        // Re-submit this request to keep the queue full
        memset(&buffers[bi*buffer_size], 0, buffer_size);
        bi = (bi+1) & buffers_count_mask;
    }

	fout.close();
	delete []buffers;
	delete samples;
    printf("FULLY STOPPED\n");
    return 0;
}


bool SamplesCollector::SetPacketSize(int samplesCount)
{
    if(!m_running)
    {
        m_samplesToPacket = samplesCount;
        return true;
    }
    else
        return false;
}

void SamplesCollector::SwitchSource(eBOARD_FFT_SOURCE device)
{
    m_selectedDevice = device;
}

/** @brief Enables writing of received data to file
    @param writeToFile enable writing to file
    @param filename Destination filename
    @param sizeLimit_B file size limit in bytes
*/
void SamplesCollector::SetWriteToFile(bool writeToFile, const char* filename, unsigned long frames_limit)
{
    m_writeToFile = writeToFile;
    m_filename = filename;
    m_framesLimit = frames_limit;
}
