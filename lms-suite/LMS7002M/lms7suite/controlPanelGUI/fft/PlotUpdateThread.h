/**
@file 	PlotUpdateThread.h
@author Lime Microsystems
*/
#ifndef PLOT_UPDATE_THREAD_H
#define PLOT_UPDATE_THREAD_H

#include "wx/thread.h"
class pnlFFTviewer;

class PlotUpdateThread : public wxThread
{
public:
    PlotUpdateThread(pnlFFTviewer *mainFrame);
    ~PlotUpdateThread();
    virtual void* Entry();
    void Stop();
    bool SetFFTsize(int size);
    bool SetSamplingFrequency(double freq);
private:
    int m_FFTsize;
    double m_samplingFreq;
    pnlFFTviewer *m_mainframe;
    bool m_running;
};

#endif // PLOT_UPDATE_THREAD_H

