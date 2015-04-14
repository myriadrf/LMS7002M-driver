/**
@file	FFTviewerMain.h
@author Lime Microsystems
*/

#ifndef PNL_FFT_VIEWER_H
#define PNL_FFT_VIEWER_H

#include "UnitsButton.h"
#include "Packets.h"
#include "BlockingFIFO.h"
#include "oglGraph/OpenGLGraph.h"
#include "dlgExtraControls.h"
#include "PluginPanel.h"
#include <wx/frame.h>
#include "SignalHandler.h"
//(*Headers(pnlFFTviewer)
#include <wx/panel.h>
class wxSpinEvent;
class wxSplitterWindow;
class wxCheckBox;
class wxTextCtrl;
class wxNotebookEvent;
class wxSplitterEvent;
class wxComboBox;
class wxNotebook;
class wxStaticText;
class wxGLCanvas;
class wxFlexGridSizer;
class wxSpinCtrl;
class wxButton;
class wxStaticBoxSizer;
//*)

class SamplesCollector;
class FFTcalculator;
class ConnectionManager;
class PlotUpdateThread;
class dlgMarkers;
class ConnectionManager;
class LMS7002_MainControl;


wxDECLARE_EVENT(wxEVT_COMMAND_THREAD_UPDATE, wxThreadEvent);

class pnlFFTviewer: public wxFrame, public SignalHandler//, public PluginPanel
{
    friend class PlotUpdateThread;
    public:
        virtual void HandleMessage(const LMS_Message &msg);
        pnlFFTviewer(ConnectionManager* pControlPort, ConnectionManager* pDataPort, wxWindow* parent,wxWindowID id = -1);
        void AssignControl(LMS7002_MainControl *pControl);
        virtual ~pnlFFTviewer();
        wxCriticalSection m_dataCS;
        SamplesCollector *getSamplesCollector() { return m_collector; };
        void SaveConfig();
        void StopCapturing();
        void SetBoardType(unsigned i);
        void ChangeFrequencyOffset(int offset_MHz);
    private:
        long t1,t2;

        BlockingFIFO<SamplesPacket> *m_samplesChannels;
        BlockingFIFO<FFTPacket> *m_fftOutputs;
        dlgMarkers *m_dlgMarkers;
        PlotUpdateThread *m_plotThread;
        void RefreshDeviceList(wxCommandEvent &evt);
        void OnThreadUpdatePlots(wxThreadEvent& evt);
        bool m_dataReading;
        void switchGUIEnables(bool dataReading);

        LMS7002_MainControl *lmsControl;
        ConnectionManager *m_controlPort;
        ConnectionManager *m_dataPort;
        SamplesCollector *m_collector;
        FFTcalculator *m_calculator;
        unsigned long m_redrawsDone;

        dlgExtraControls *m_extraControls;

        //(*Handlers(pnlFFTviewer)
        void OnQuit(wxCommandEvent& event);
        void OnbtnStartStopClick(wxCommandEvent& event);
        void OncmbDeviceListSelected(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnChannelSelectionSelect(wxCommandEvent& event);
        void OnChangePlotVisibility(wxCommandEvent& event);
        void OnbtnConnectionSettingsClick(wxCommandEvent& event);
        void OnCenterSpanChange(wxCommandEvent& event);
        void OnYaxisChange(wxCommandEvent& event);
        void OnchkDCcorrectionClick(wxCommandEvent& event);
        void OnchkCalcAverageClick(wxCommandEvent& event);
        void OnspinAverageCountChange(wxSpinEvent& event);
        void OntxtMark0FreqText(wxCommandEvent& event);
        void OntxtMark1FreqTextEnter(wxCommandEvent& event);
        void OnchkMarkerEnableClick(wxCommandEvent& event);
        void OnbtnOpenMarkersClick(wxCommandEvent& event);
        void OnbtnRefreshClick(wxCommandEvent& event);
        void OnbtnExtraControlsClick(wxCommandEvent& event);
        void OncmbWindowFunctionSelected(wxCommandEvent& event);
        void OnspinAvgChange(wxCommandEvent& event);
        //*)

        //(*Identifiers(pnlFFTviewer)
        static const long ID_GLCANVAS4;
        static const long ID_GLCANVAS5;
        static const long ID_PANEL1;
        static const long ID_GLCANVAS1;
        static const long ID_PANEL2;
        static const long ID_SPLITTERWINDOW1;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL2;
        static const long ID_CHECKBOX1;
        static const long ID_TEXTCTRL7;
        static const long ID_CHECKBOX4;
        static const long ID_COMBOBOX1;
        static const long ID_BUTTON2;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_CHECKBOX6;
        static const long ID_STATICTEXT12;
        static const long ID_SPINCTRL1;
        static const long ID_CHECKBOX9;
        static const long ID_CHECKBOX7;
        static const long ID_CHECKBOX2;
        static const long ID_CHECKBOX8;
        static const long ID_CHECKBOX3;
        static const long ID_CHECKBOX5;
        static const long ID_STATICTEXT10;
        static const long ID_TEXTCTRL3;
        static const long ID_BUTTON3;
        static const long ID_STATICTEXT11;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON4;
        static const long ID_STATICTEXT18;
        static const long ID_TEXTCTRL6;
        static const long ID_STATICTEXT19;
        static const long ID_TEXTCTRL5;
        static const long ID_STATICTEXT28;
        static const long ID_STATICTEXT24;
        static const long ID_STATICTEXT25;
        static const long ID_STATICTEXT13;
        static const long ID_TEXTCTRL8;
        static const long ID_STATICTEXT14;
        static const long ID_TEXTCTRL9;
        static const long ID_STATICTEXT15;
        static const long ID_STATICTEXT16;
        static const long ID_STATICTEXT17;
        static const long ID_TEXTCTRL10;
        static const long ID_STATICTEXT21;
        static const long ID_TEXTCTRL11;
        static const long ID_STATICTEXT22;
        static const long ID_STATICTEXT23;
        static const long ID_STATICTEXT26;
        static const long ID_STATICTEXT27;
        static const long ID_BUTTON6;
        static const long ID_TAB_SPECTRUM;
        static const long ID_NOTEBOOK1;
        //*)

        //(*Declarations(pnlFFTviewer)
        wxStaticText* StaticText10;
        wxStaticText* StaticText9;
        wxStaticText* lblIratio;
        wxStaticText* StaticText20;
        wxComboBox* cmbWindowFunction;
        wxTextCtrl* txtCFreq2;
        wxTextCtrl* spinAvg;
        wxStaticText* m_lblFFTperSecond;
        wxCheckBox* chkShowFFT;
        UnitsButton* btnCenterFreqRatio;
        wxTextCtrl* m_txtCenterFreq;
        wxTextCtrl* txtBW2;
        wxCheckBox* chkFreezeDrawing;
        wxStaticText* StaticText13;
        wxStaticText* StaticText2;
        wxStaticText* StaticText14;
        wxStaticText* m_lblUpdatePerSecond;
        wxCheckBox* chkFreezeIversusQ;
        OpenGLGraph* m_glconstellationPlot;
        wxStaticText* StaticText6;
        wxTextCtrl* m_txtFreqSpan;
        wxTextCtrl* txtBW1;
        wxStaticText* StaticText19;
        wxStaticText* StaticText8;
        UnitsButton* btnSamplingFreqRatio;
        wxStaticText* StaticText11;
        wxStaticText* lbldBc;
        wxStaticText* StaticText18;
        wxNotebook* m_MainTabs;
        wxButton* btnExtraControls;
        wxPanel* Panel1;
        wxStaticText* StaticText3;
        wxCheckBox* chkSaveStreamToFile;
        OpenGLGraph* m_gltimePlot;
        wxStaticText* lblQratio;
        wxStaticText* m_lblDatarate;
        wxTextCtrl* txtYaxisBottom;
        wxSpinCtrl* spinFrameLimit;
        wxCheckBox* chkDCcorrection;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxTextCtrl* txtFFTsize;
        wxPanel* m_tabSpectrum;
        wxButton* btnStartStop;
        wxTextCtrl* txtYaxisTop;
        wxStaticText* StaticText15;
        wxFlexGridSizer* sizerPowerMeasure;
        wxStaticText* StaticText12;
        wxCheckBox* chkShowConstellation;
        wxPanel* Panel2;
        UnitsButton* btnFreqSpanRatio;
        wxCheckBox* chkCalcAverage;
        wxTextCtrl* txtSamplingFreq;
        wxStaticText* lblPwrCh1;
        wxTextCtrl* txtCFreq1;
        wxSplitterWindow* m_plotSplitter;
        OpenGLGraph* m_glFFTplot;
        wxStaticText* StaticText4;
        wxStaticText* lblPwrCh2;
        wxCheckBox* chkFreezeIQtime;
        wxFlexGridSizer* sizerTimeDomain;
        wxCheckBox* chkShowTime;
        wxStaticText* StaticText16;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SAMPLESTESTERMAIN_H
