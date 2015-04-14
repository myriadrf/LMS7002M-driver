/**
@file	pnlFFTviewer.cpp
@author	Lime Microsystems
@brief	Implementation of FFT viewer main panel
*/

#include "pnlFFTviewer.h"
#include <wx/msgdlg.h>

#include "ConnectionManager.h"
#include "SamplesCollector.h"
#include "FFTcalculator.h"
#include "PlotUpdateThread.h"
#include "dlgAbout.h"
#include "dlgConnectionManager.h"
#include "CommonUtilities.h"
#include "Packets.h"
#include "LMS7002_MainControl.h"
#include "ControlParameters.h"
#include "iniParser.h"
const char *config_filename = "config.ini";

const int CHANNEL_COUNT = 2;

//(*InternalHeaders(pnlFFTviewer)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/splitter.h>
#include <wx/glcanvas.h>
#include <wx/spinctrl.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlFFTviewer)
const long pnlFFTviewer::ID_GLCANVAS4 = wxNewId();
const long pnlFFTviewer::ID_GLCANVAS5 = wxNewId();
const long pnlFFTviewer::ID_PANEL1 = wxNewId();
const long pnlFFTviewer::ID_GLCANVAS1 = wxNewId();
const long pnlFFTviewer::ID_PANEL2 = wxNewId();
const long pnlFFTviewer::ID_SPLITTERWINDOW1 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT4 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL1 = wxNewId();
const long pnlFFTviewer::ID_BUTTON1 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT5 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL2 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX1 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL7 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX4 = wxNewId();
const long pnlFFTviewer::ID_COMBOBOX1 = wxNewId();
const long pnlFFTviewer::ID_BUTTON2 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT2 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT3 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT6 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT7 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT8 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT9 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX6 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT12 = wxNewId();
const long pnlFFTviewer::ID_SPINCTRL1 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX9 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX7 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX2 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX8 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX3 = wxNewId();
const long pnlFFTviewer::ID_CHECKBOX5 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT10 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL3 = wxNewId();
const long pnlFFTviewer::ID_BUTTON3 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT11 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL4 = wxNewId();
const long pnlFFTviewer::ID_BUTTON4 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT18 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL6 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT19 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL5 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT28 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT24 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT25 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT13 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL8 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT14 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL9 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT15 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT16 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT17 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL10 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT21 = wxNewId();
const long pnlFFTviewer::ID_TEXTCTRL11 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT22 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT23 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT26 = wxNewId();
const long pnlFFTviewer::ID_STATICTEXT27 = wxNewId();
const long pnlFFTviewer::ID_BUTTON6 = wxNewId();
const long pnlFFTviewer::ID_TAB_SPECTRUM = wxNewId();
const long pnlFFTviewer::ID_NOTEBOOK1 = wxNewId();
//*)

wxDEFINE_EVENT(wxEVT_COMMAND_THREAD_UPDATE, wxThreadEvent);
BEGIN_EVENT_TABLE(pnlFFTviewer,wxFrame)
    //(*EventTable(pnlFFTviewer)
    //*)
    EVT_THREAD(wxID_ANY, pnlFFTviewer::OnThreadUpdatePlots)
    EVT_CLOSE(pnlFFTviewer::OnClose)
END_EVENT_TABLE()

pnlFFTviewer::pnlFFTviewer(ConnectionManager* pControlPort, ConnectionManager* pDataPort, wxWindow* parent,wxWindowID id)//:
    //PluginPanel(this)
{
    lmsControl = NULL;
    t2 = t1 = getMilis();
    m_samplesChannels = NULL;
    m_fftOutputs = NULL;
    m_collector = NULL;
    m_calculator = NULL;

    m_redrawsDone = 0;
    m_controlPort = pControlPort;
    m_dataPort = pDataPort;

    m_dataReading = false;
    m_plotThread = NULL;

    m_extraControls = new dlgExtraControls(this, m_controlPort);
    //Create(parent, id, "FFTviewer", wxDefaultPosition, wxDefaultSize, wxCAPTION|wxDEFAULT_FRAME_STYLE|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxCLIP_CHILDREN, _T("id"));
    //(*Initialize(pnlFFTviewer)
    wxStaticBoxSizer* StaticBoxSizer2;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer16;
    wxFlexGridSizer* FlexGridSizer19;
    wxFlexGridSizer* m_plotSizer;
    wxFlexGridSizer* m_TimeConstSizer;
    wxFlexGridSizer* m_spectrumSizer;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* m_controlsSizer;
    wxFlexGridSizer* FlexGridSizer7;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxFlexGridSizer* FlexGridSizer15;
    wxFlexGridSizer* FlexGridSizer18;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer14;
    wxFlexGridSizer* FlexGridSizer20;
    wxFlexGridSizer* FlexGridSizer13;
    wxFlexGridSizer* FlexGridSizer12;
    wxFlexGridSizer* FlexGridSizer6;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer11;
    wxFlexGridSizer* FlexGridSizer17;
    wxStaticBoxSizer* StaticBoxSizer5;
    wxFlexGridSizer* m_FFTsizer;

    Create(parent, id, "FFTviewer", wxDefaultPosition, wxDefaultSize, wxCAPTION|wxDEFAULT_FRAME_STYLE|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxCLIP_CHILDREN, _T("id"));
    SetMinSize(wxSize(800,400));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    m_MainTabs = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    m_tabSpectrum = new wxPanel(m_MainTabs, ID_TAB_SPECTRUM, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TAB_SPECTRUM"));
    m_spectrumSizer = new wxFlexGridSizer(0, 2, 0, 0);
    m_spectrumSizer->AddGrowableCol(0);
    m_spectrumSizer->AddGrowableRow(0);
    m_plotSizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_plotSizer->AddGrowableCol(0);
    m_plotSizer->AddGrowableRow(0);
    m_plotSplitter = new wxSplitterWindow(m_tabSpectrum, ID_SPLITTERWINDOW1, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxFULL_REPAINT_ON_RESIZE, _T("ID_SPLITTERWINDOW1"));
    m_plotSplitter->SetMinSize(wxSize(100,100));
    m_plotSplitter->SetMinimumPaneSize(100);
    m_plotSplitter->SetSashGravity(0.5);
    Panel1 = new wxPanel(m_plotSplitter, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    m_TimeConstSizer = new wxFlexGridSizer(0, 2, 0, 5);
    m_TimeConstSizer->AddGrowableCol(0);
    m_TimeConstSizer->AddGrowableCol(1);
    m_TimeConstSizer->AddGrowableRow(0);
    sizerTimeDomain = new wxFlexGridSizer(0, 1, 0, 0);
    sizerTimeDomain->AddGrowableCol(0);
    sizerTimeDomain->AddGrowableRow(0);
    int GLCanvasAttributes_1[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    m_gltimePlot = new OpenGLGraph(Panel1, ID_GLCANVAS4, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS4"), GLCanvasAttributes_1);
    m_gltimePlot->SetMinSize(wxSize(225,150));
    m_gltimePlot->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));
    sizerTimeDomain->Add(m_gltimePlot, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_TimeConstSizer->Add(sizerTimeDomain, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    int GLCanvasAttributes_2[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    m_glconstellationPlot = new OpenGLGraph(Panel1, ID_GLCANVAS5, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS5"), GLCanvasAttributes_2);
    m_glconstellationPlot->SetMinSize(wxSize(225,150));
    m_glconstellationPlot->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));
    m_TimeConstSizer->Add(m_glconstellationPlot, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    Panel1->SetSizer(m_TimeConstSizer);
    m_TimeConstSizer->Fit(Panel1);
    m_TimeConstSizer->SetSizeHints(Panel1);
    Panel2 = new wxPanel(m_plotSplitter, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Panel2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    m_FFTsizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_FFTsizer->AddGrowableCol(0);
    m_FFTsizer->AddGrowableRow(0);
    int GLCanvasAttributes_3[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    m_glFFTplot = new OpenGLGraph(Panel2, ID_GLCANVAS1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_3);
    m_glFFTplot->SetMinSize(wxSize(300,200));
    m_glFFTplot->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOBK));
    m_FFTsizer->Add(m_glFFTplot, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    Panel2->SetSizer(m_FFTsizer);
    m_FFTsizer->Fit(Panel2);
    m_FFTsizer->SetSizeHints(Panel2);
    m_plotSplitter->SplitHorizontally(Panel1, Panel2);
    m_plotSizer->Add(m_plotSplitter, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_spectrumSizer->Add(m_plotSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_controlsSizer = new wxFlexGridSizer(0, 1, 0, 0);
    m_controlsSizer->AddGrowableCol(0);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, m_tabSpectrum, _T("FFT parameters"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    StaticText4 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT4, _T("Sampling frequency:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer4->Add(StaticText4, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    txtSamplingFreq = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL1, _T("15.36"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer4->Add(txtSamplingFreq, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnSamplingFreqRatio = new UnitsButton(m_tabSpectrum, ID_BUTTON1, _T("MHz"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer4->Add(btnSamplingFreqRatio, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer6 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer6->AddGrowableCol(1);
    StaticText5 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT5, _T("FFT samples count:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer6->Add(StaticText5, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    txtFFTsize = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL2, _T("16384"), wxDefaultPosition, wxSize(64,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer6->Add(txtFFTsize, 1, wxLEFT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer5->AddGrowableCol(1);
    chkCalcAverage = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX1, _T("Calculate average"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    chkCalcAverage->SetValue(false);
    FlexGridSizer5->Add(chkCalcAverage, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    spinAvg = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL7, _T("20"), wxDefaultPosition, wxSize(64,-1), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    spinAvg->SetMaxLength(4);
    FlexGridSizer5->Add(spinAvg, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer20 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer20->AddGrowableCol(1);
    chkDCcorrection = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX4, _T("DC correction"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    chkDCcorrection->SetValue(false);
    FlexGridSizer20->Add(chkDCcorrection, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    cmbWindowFunction = new wxComboBox(m_tabSpectrum, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    cmbWindowFunction->SetSelection( cmbWindowFunction->Append(_T("No window")) );
    cmbWindowFunction->Append(_T("Blackman-Harris"));
    cmbWindowFunction->Append(_T("Hamming"));
    cmbWindowFunction->Append(_T("Hanning"));
    FlexGridSizer20->Add(cmbWindowFunction, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer20, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer2->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_controlsSizer->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, m_tabSpectrum, _T("Data Reading"));
    FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer7->AddGrowableCol(1);
    btnStartStop = new wxButton(m_tabSpectrum, ID_BUTTON2, _T("START"), wxDefaultPosition, wxSize(76,76), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer7->Add(btnStartStop, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer14 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer8 = new wxFlexGridSizer(0, 2, 5, 5);
    StaticText2 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT2, _T("Data rate:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer8->Add(StaticText2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_lblDatarate = new wxStaticText(m_tabSpectrum, ID_STATICTEXT3, _T("0 MB/s"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer8->Add(m_lblDatarate, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT6, _T("FFT/s:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer8->Add(StaticText3, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_lblFFTperSecond = new wxStaticText(m_tabSpectrum, ID_STATICTEXT7, _T("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer8->Add(m_lblFFTperSecond, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT8, _T("Updates/s:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    FlexGridSizer8->Add(StaticText6, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_lblUpdatePerSecond = new wxStaticText(m_tabSpectrum, ID_STATICTEXT9, _T("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    FlexGridSizer8->Add(m_lblUpdatePerSecond, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer14->Add(FlexGridSizer8, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
    chkSaveStreamToFile = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX6, _T("Save stream to file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    chkSaveStreamToFile->SetValue(false);
    FlexGridSizer14->Add(chkSaveStreamToFile, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer15 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticText9 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT12, _T("Frames to capture:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    FlexGridSizer15->Add(StaticText9, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    spinFrameLimit = new wxSpinCtrl(m_tabSpectrum, ID_SPINCTRL1, _T("16384"), wxDefaultPosition, wxDefaultSize, 0, 1, 16777216, 16384, _T("ID_SPINCTRL1"));
    spinFrameLimit->SetValue(_T("16384"));
    FlexGridSizer15->Add(spinFrameLimit, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer14->Add(FlexGridSizer15, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer7->Add(FlexGridSizer14, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer3->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_controlsSizer->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer12 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer12->AddGrowableCol(1);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, m_tabSpectrum, _T("Graphs"));
    FlexGridSizer19 = new wxFlexGridSizer(0, 2, 0, 0);
    chkShowTime = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX9, _T("Show time domain"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
    chkShowTime->SetValue(true);
    FlexGridSizer19->Add(chkShowTime, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkFreezeIQtime = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX7, _T("Freeze time domain"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    chkFreezeIQtime->SetValue(false);
    FlexGridSizer19->Add(chkFreezeIQtime, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkShowConstellation = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX2, _T("Show I versus Q"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    chkShowConstellation->SetValue(true);
    FlexGridSizer19->Add(chkShowConstellation, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkFreezeIversusQ = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX8, _T("Freeze I versus Q"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    chkFreezeIversusQ->SetValue(false);
    FlexGridSizer19->Add(chkFreezeIversusQ, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkShowFFT = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX3, _T("Show FFT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    chkShowFFT->SetValue(true);
    FlexGridSizer19->Add(chkShowFFT, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkFreezeDrawing = new wxCheckBox(m_tabSpectrum, ID_CHECKBOX5, _T("Freeze FFT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    chkFreezeDrawing->SetValue(false);
    FlexGridSizer19->Add(chkFreezeDrawing, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer4->Add(FlexGridSizer19, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer12->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_controlsSizer->Add(FlexGridSizer12, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxVERTICAL, m_tabSpectrum, _T("Analyzer controls"));
    FlexGridSizer9 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer9->AddGrowableCol(0);
    FlexGridSizer17 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer10 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer10->AddGrowableCol(0);
    StaticText7 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT10, _T("Center:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    FlexGridSizer10->Add(StaticText7, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_txtCenterFreq = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL3, _T("0"), wxDefaultPosition, wxSize(60,-1), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    FlexGridSizer10->Add(m_txtCenterFreq, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    btnCenterFreqRatio = new UnitsButton(m_tabSpectrum, ID_BUTTON3, _T("MHz"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer10->Add(btnCenterFreqRatio, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer17->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer11 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer11->AddGrowableCol(0);
    StaticText8 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT11, _T("Span:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    FlexGridSizer11->Add(StaticText8, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_txtFreqSpan = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL4, _T("10"), wxDefaultPosition, wxSize(60,-1), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    FlexGridSizer11->Add(m_txtFreqSpan, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    btnFreqSpanRatio = new UnitsButton(m_tabSpectrum, ID_BUTTON4, _T("MHz"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer11->Add(btnFreqSpanRatio, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer17->Add(FlexGridSizer11, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer9->Add(FlexGridSizer17, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer16 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer16->AddGrowableCol(0);
    StaticText15 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT18, _T("max Y:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
    FlexGridSizer16->Add(StaticText15, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    txtYaxisTop = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL6, _T("0"), wxDefaultPosition, wxSize(48,-1), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    FlexGridSizer16->Add(txtYaxisTop, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticText16 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT19, _T("min Y:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    FlexGridSizer16->Add(StaticText16, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    txtYaxisBottom = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL5, _T("-100"), wxDefaultPosition, wxSize(48,-1), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    FlexGridSizer16->Add(txtYaxisBottom, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer9->Add(FlexGridSizer16, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer5->Add(FlexGridSizer9, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_controlsSizer->Add(StaticBoxSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, m_tabSpectrum, _T("Measurement"));
    FlexGridSizer13 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer13->AddGrowableCol(0);
    FlexGridSizer18 = new wxFlexGridSizer(0, 2, 0, 15);
    FlexGridSizer18->AddGrowableCol(1);    
    StaticText20 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT28, _T("Peak to avg ratio(dB):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
    FlexGridSizer18->Add(StaticText20, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblIratio = new wxStaticText(m_tabSpectrum, ID_STATICTEXT24, _T("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    FlexGridSizer18->Add(lblIratio, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);    
    FlexGridSizer13->Add(FlexGridSizer18, 1, wxBOTTOM|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    sizerPowerMeasure = new wxFlexGridSizer(0, 2, 0, 5);
    sizerPowerMeasure->AddGrowableCol(1);
    StaticText10 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT13, _T("Ch 1. center offset(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    sizerPowerMeasure->Add(StaticText10, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtCFreq1 = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL8, _T("0"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    txtCFreq1->SetExtraStyle( txtCFreq1->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
    sizerPowerMeasure->Add(txtCFreq1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText11 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT14, _T("Bandwidth(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    sizerPowerMeasure->Add(StaticText11, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    txtBW1 = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL9, _T("1"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
    txtBW1->SetExtraStyle( txtBW1->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
    sizerPowerMeasure->Add(txtBW1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText12 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT15, _T("Power(dbFS):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    sizerPowerMeasure->Add(StaticText12, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    lblPwrCh1 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT16, _T("0.00"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    sizerPowerMeasure->Add(lblPwrCh1, 1, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText13 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT17, _T("Ch 2. center offset(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    sizerPowerMeasure->Add(StaticText13, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    txtCFreq2 = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL10, _T("0"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL10"));
    txtCFreq2->SetExtraStyle( txtCFreq2->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
    sizerPowerMeasure->Add(txtCFreq2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText14 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT21, _T("Bandwidth(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    sizerPowerMeasure->Add(StaticText14, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    txtBW2 = new wxTextCtrl(m_tabSpectrum, ID_TEXTCTRL11, _T("1"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL11"));
    txtBW2->SetExtraStyle( txtBW2->GetExtraStyle() | wxWS_EX_BLOCK_EVENTS );
    sizerPowerMeasure->Add(txtBW2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText18 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT22, _T("Power(dbFS):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    sizerPowerMeasure->Add(StaticText18, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    lblPwrCh2 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT23, _T("0.00"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
    sizerPowerMeasure->Add(lblPwrCh2, 1, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticText19 = new wxStaticText(m_tabSpectrum, ID_STATICTEXT26, _T("dBc:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
    sizerPowerMeasure->Add(StaticText19, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    lbldBc = new wxStaticText(m_tabSpectrum, ID_STATICTEXT27, _T("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
    sizerPowerMeasure->Add(lbldBc, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    FlexGridSizer13->Add(sizerPowerMeasure, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer1->Add(FlexGridSizer13, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_controlsSizer->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    btnExtraControls = new wxButton(m_tabSpectrum, ID_BUTTON6, _T("Extra Controls"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    m_controlsSizer->Add(btnExtraControls, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    m_spectrumSizer->Add(m_controlsSizer, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    m_tabSpectrum->SetSizer(m_spectrumSizer);
    m_spectrumSizer->Fit(m_tabSpectrum);
    m_spectrumSizer->SetSizeHints(m_tabSpectrum);
    m_MainTabs->AddPage(m_tabSpectrum, _T("Spectrum"), false);
    FlexGridSizer1->Add(m_MainTabs, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnspinAvgChange);
    Connect(ID_TEXTCTRL7,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlFFTviewer::OnspinAvgChange);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnchkDCcorrectionClick);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlFFTviewer::OncmbWindowFunctionSelected);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnbtnStartStopClick);
    Connect(ID_CHECKBOX9,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnChangePlotVisibility);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnChangePlotVisibility);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnChangePlotVisibility);
    Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlFFTviewer::OnCenterSpanChange);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnCenterSpanChange);
    Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlFFTviewer::OnCenterSpanChange);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnCenterSpanChange);
    Connect(ID_TEXTCTRL6,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlFFTviewer::OnYaxisChange);
    Connect(ID_TEXTCTRL5,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&pnlFFTviewer::OnYaxisChange);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlFFTviewer::OnbtnExtraControlsClick);
    //*)
    btnSamplingFreqRatio->SetUnits("Hz");
    btnCenterFreqRatio->SetUnits("Hz");
    btnFreqSpanRatio->SetUnits("Hz");

    int w,h;
    GetSize(&w, &h);
    SetMinSize(wxSize(w, h));


    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxCommandEvent evt;

    //load gui configuration from file
    iniParser m_options;
    m_options.Open(config_filename);
    m_options.SelectSection("fft_parameters");
    txtFFTsize->SetValue( m_options.Get("fft_size", "16384"));
    txtSamplingFreq->SetValue( m_options.Get("sampling_freq", "15.36"));
    btnSamplingFreqRatio->SetPower(m_options.Get("sampling_freq_10power", 6));
    chkCalcAverage->SetValue( m_options.Get("calculate_average", true));
    spinAvg->SetValue( m_options.Get("average_count", "20"));
    chkDCcorrection->SetValue( m_options.Get("dc_correction", 0));

    m_options.SelectSection("GUI options");
    //cmbChannelSelection->SetSelection(m_options.Get("channel_selection", 0));

    chkShowFFT->SetValue(m_options.Get("show_fft", 1));
    chkShowConstellation->SetValue(m_options.Get("show_constellation", 1));
    chkShowTime->SetValue(m_options.Get("show_timedomain", 1));
    m_options.SelectSection("oscilloscope");
    m_txtCenterFreq->SetValue( m_options.Get("center_frequency", "0"));
    btnCenterFreqRatio->SetPower(m_options.Get("center_frequency_10power", 6));
    m_txtFreqSpan->SetValue( m_options.Get("span", "10"));
    btnFreqSpanRatio->SetPower(m_options.Get("span_10power", 6));

     //fill some default values to plots
    long samplesCount = 0;
    double fs = 0;
    vector<double> vecTime;
    vector<float> vecZeros;

    txtFFTsize->GetValue().ToLong(&samplesCount);
    txtSamplingFreq->GetValue().ToDouble(&fs);
    fs = fs*btnSamplingFreqRatio->GetRatio();
    for(int i=0; i<samplesCount-1; ++i)
    {
        vecTime.push_back(i);
        vecZeros.push_back(0);
    }

    OnChangePlotVisibility(evt);

    m_gltimePlot->settings.useVBO = true;
        m_gltimePlot->AddSerie(new cDataSerie());
        m_gltimePlot->AddSerie(new cDataSerie());
        m_gltimePlot->AddSerie(new cDataSerie());
        m_gltimePlot->AddSerie(new cDataSerie());
        m_gltimePlot->SetInitialDisplayArea(0, 1024, -2048, 2048);
        m_gltimePlot->settings.title = "IQ samples";
        m_gltimePlot->series[0]->color = 0xFF0000FF;
        m_gltimePlot->series[1]->color = 0x0000FFFF;
        m_gltimePlot->series[2]->color = 0xFF00FFFF;
        m_gltimePlot->series[3]->color = 0x00FFFFFF;
        m_gltimePlot->settings.marginLeft = 40;

    m_glconstellationPlot->settings.useVBO = true;
        m_glconstellationPlot->AddSerie(new cDataSerie());
        m_glconstellationPlot->AddSerie(new cDataSerie());
        m_glconstellationPlot->series[0]->color = 0xFF0000FF;
        m_glconstellationPlot->series[1]->color = 0xFF00FFFF;
        m_glconstellationPlot->SetInitialDisplayArea(-2048, 2048, -2048, 2048);
        m_glconstellationPlot->SetDrawingMode(GLG_POINTS);
        m_glconstellationPlot->settings.title = "I versus Q";
        m_glconstellationPlot->settings.titleXaxis = "I";
        m_glconstellationPlot->settings.titleYaxis = "Q";
        m_glconstellationPlot->settings.gridXlines = 8;
        m_glconstellationPlot->settings.gridYlines = 8;
        m_glconstellationPlot->settings.marginLeft = 40;

    m_glFFTplot->settings.useVBO = true;
        m_glFFTplot->AddSerie(new cDataSerie());
        m_glFFTplot->AddSerie(new cDataSerie());
        m_glFFTplot->series[0]->color = 0xFF0000FF;
        m_glFFTplot->series[1]->color = 0xFF00FFFF;
        m_glFFTplot->SetDrawingMode(GLG_LINE);
        m_glFFTplot->settings.gridXlines = 15;
        m_glFFTplot->SetInitialDisplayArea(-5000000, 5000000, -100, 0);

        m_glFFTplot->settings.title = "FFT";
        m_glFFTplot->settings.titleXaxis = "Frequency(MHz)";
        m_glFFTplot->settings.titleYaxis = "Amplitude(dBFS)";
        m_glFFTplot->settings.xUnits = "";
        m_glFFTplot->settings.gridXprec = 3;
        //m_glFFTplot->settings.yUnits = "dB";
        m_glFFTplot->settings.markersEnabled = true;

        m_glFFTplot->settings.marginLeft = 40;
        m_glFFTplot->settings.staticGrid = true;

        m_glFFTplot->Refresh();
    OnChannelSelectionSelect(evt);

//    vector<float> data;
//    vector<float> freqVector;
//    for(int i=0; i<samplesCount / 2-1; ++i)
//    {
//        data.push_back(i%1024);
//        freqVector.push_back(1000*(i-samplesCount/4));
//    }
//    m_glFFTplot->series[0]->AssignValues(&freqVector[0], &data[0], samplesCount / 2-1);
//    m_glFFTplot->series[1]->AssignValues(&freqVector[0], &data[0], samplesCount / 2-1);
}

pnlFFTviewer::~pnlFFTviewer()
{
    StopCapturing();
    SaveConfig();
    if(m_collector)
        delete m_collector;
    if(m_calculator)
        delete m_calculator;
    if(m_plotThread)
        delete m_plotThread;
    //(*Destroy(pnlFFTviewer)
    //*)
}

void pnlFFTviewer::OnQuit(wxCommandEvent& event)
{
    wxCloseEvent evt;
    OnClose(evt);
    printf("Quitting\n");
}

void pnlFFTviewer::switchGUIEnables(bool dataReading)
{
    txtSamplingFreq->Enable(!dataReading);
    txtFFTsize->Enable(!dataReading);
    btnSamplingFreqRatio->Enable(!dataReading);
    chkSaveStreamToFile->Enable(!dataReading);
}

void pnlFFTviewer::OnbtnStartStopClick(wxCommandEvent& event)
{
    if(m_dataReading == false) //start process
    {
        bool saveTofile = chkSaveStreamToFile->IsChecked();
        wxString filename;
        if(saveTofile)
        {
            wxFileDialog dlg(this, _("Save file for stream data"), "", "", "binary (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
            if (dlg.ShowModal() == wxID_CANCEL)
                return;
            filename = dlg.GetPath();
        }
        long fftsize = 0;
        txtFFTsize->GetValue().ToLong(&fftsize);
        if(m_samplesChannels)
            delete m_samplesChannels;
        m_samplesChannels = new BlockingFIFO<SamplesPacket>();
        if(m_fftOutputs)
            delete m_fftOutputs;
        m_fftOutputs = new BlockingFIFO<FFTPacket>();
        if(m_collector)
            delete m_collector;
        m_collector = new SamplesCollector(m_controlPort, m_dataPort, m_samplesChannels);
//        if(lmsControl && cmbChannelSelection->GetSelection() == 0)
            m_collector->frameStart = lmsControl->GetParam(LML1_FIDM);
//        if(lmsControl && cmbChannelSelection->GetSelection() == 1)
//            m_collector->frameStart = lmsControl->GetParam(LML_FIDM2);
        m_collector->SwitchSource(BOARD_STREAM);
        m_extraControls->SetSamplesCollector(m_collector);
        m_collector->m_dataSource = m_extraControls->rxDataSource->GetSelection() ? 3 : 0;
        if(m_calculator)
            delete m_calculator;
        m_calculator = new FFTcalculator(m_samplesChannels, m_fftOutputs, CHANNEL_COUNT);

        m_samplesChannels->setLength(128, 2*fftsize);
        m_fftOutputs->setLength(8, 2*fftsize);

        m_redrawsDone = 0;
        if(m_plotThread)
            delete m_plotThread;
        m_plotThread = new PlotUpdateThread(this);

        m_collector->SetPacketSize(2*fftsize);
        int filelimit = 0;
        filelimit = spinFrameLimit->GetValue();
        m_collector->SetWriteToFile(saveTofile, filename.c_str(), filelimit);
        m_calculator->SetFFTsize(fftsize);
        m_plotThread->SetFFTsize(fftsize);
        double Fs = 0;
        txtSamplingFreq->GetValue().ToDouble(&Fs);
        m_calculator->SetSamplingFrequency(Fs*btnSamplingFreqRatio->GetRatio());
        m_plotThread->SetSamplingFrequency(Fs*btnSamplingFreqRatio->GetRatio());
        m_calculator->SetDCcorrection(chkDCcorrection->IsChecked());
        wxCommandEvent temp_evt;
        OnspinAvgChange(temp_evt);
        //m_calculator->SetAveragingCount(spinAverageCount->GetValue(), chkCalcAverage->IsChecked());
		if (m_controlPort->IsOpen() == false || m_dataPort->IsOpen() == false)
        {
            wxMessageDialog dlg(this, "Device not connected!", "Error", wxOK);
            dlg.ShowModal();
            return;
        }

        m_samplesChannels->reset();
        m_fftOutputs->reset();

        //start samples collector
        if(m_collector->StartSampling() != true)
        {
            return;
        }
        //start fft calculations
        if(m_calculator->Start() != true)
        {
            delete m_plotThread;
            m_plotThread = NULL;
            m_collector->StopSampling();
            return;
        }
        //start graphs drawing
        if(m_plotThread->Run() != wxTHREAD_NO_ERROR)
        {
            delete m_plotThread;
            m_plotThread = NULL;
            m_collector->StopSampling();
            m_calculator->Stop();
            return;
        }
        m_dataReading = true;
        btnStartStop->SetLabel("STOP");
    }
    else //stop process
    {
        m_plotThread->Stop();
        m_calculator->Stop();
        m_collector->StopSampling();
        m_dataReading = false;
        btnStartStop->SetLabel("START");
    }
    switchGUIEnables(m_dataReading);
}

void pnlFFTviewer::OnThreadUpdatePlots(wxThreadEvent &evt)
{
    //printf("THREAD UPDATE EVENT\n");
    if(m_collector == NULL || m_calculator == NULL)
        return;

    t2 = getMilis();
    if(t2 - t1 >= 1000)
    {
        float fps = 0;
        fps = (1000.0*m_redrawsDone)/(t2-t1);
        m_redrawsDone = 0;
        t1 = t2;

        float dataRate = m_collector->m_dataRate;
        if(dataRate > 1000000)
            m_lblDatarate->SetLabel(wxString::Format("%.1f MiB/s", dataRate/1048576.0));
        else if(dataRate > 1000)
            m_lblDatarate->SetLabel(wxString::Format("%.1f KiB/s", dataRate/1024.0));
        else
            m_lblDatarate->SetLabel(wxString::Format("%.1f B/s", dataRate));
        m_lblFFTperSecond->SetLabel(wxString::Format("%.1f", m_calculator->GetFFTrate()));
        m_lblUpdatePerSecond->SetLabel(wxString::Format("%.1f", fps));
        //if(cmbChannelSelection->GetSelection() == 0)
            m_collector->frameStart = lmsControl->GetParam(LML1_FIDM, false);
//        if(cmbChannelSelection->GetSelection() == 1)
//            m_collector->frameStart = lmsControl->GetParam(LML_FIDM2, false);
    }

    //wxCriticalSectionLocker lock(m_dataCS);
//    m_glFFTplot->Refresh();
//    m_glFFTplot->Update();
//    m_gltimePlot->Refresh();
//    m_gltimePlot->Update();
//    m_glconstellationPlot->Refresh();
//    m_glconstellationPlot->Update();
    //++m_redrawsDone;
    //wxYield();
}

void pnlFFTviewer::SaveConfig()
{
    iniParser m_options;
    m_options.Open(config_filename);
    //save all gui settings to file
    m_options.SelectSection("fft_parameters");
    m_options.Set("fft_size", txtFFTsize->GetValue().ToAscii());
    m_options.Set("sampling_freq", txtSamplingFreq->GetValue().ToAscii());
    m_options.Set("sampling_freq_10power", btnSamplingFreqRatio->GetPower());
    m_options.Set("calculate_average", chkCalcAverage->GetValue());
    m_options.Set("average_count", spinAvg->GetValue());
    m_options.Set("dc_correction", chkDCcorrection->GetValue());
    m_options.SelectSection("GUI options");
//    m_options.Set("channel_selection", cmbChannelSelection->GetSelection());
    m_options.Set("show_fft", chkShowFFT->GetValue());
    m_options.Set("show_constellation", chkShowConstellation->GetValue());
    m_options.Set("show_timedomain", chkShowTime->GetValue());
    m_options.SelectSection("oscilloscope");
    m_options.Set("center_frequency", m_txtCenterFreq->GetValue());
    m_options.Set("center_frequency_10power", btnCenterFreqRatio->GetPower());
    m_options.Set("span", m_txtFreqSpan->GetValue());
    m_options.Set("span_10power", btnFreqSpanRatio->GetPower());
    m_options.Save(config_filename);
}

void pnlFFTviewer::OnClose(wxCloseEvent& event)
{
    StopCapturing();
    SaveConfig();

    if(event.CanVeto() == false)
        Destroy();
    else
    {
        Hide();
        event.Veto();
    }
}

void pnlFFTviewer::OnChannelSelectionSelect(wxCommandEvent& event)
{
    int chsel = event.GetInt();
    if( chsel == 0)
    {
        if(m_glconstellationPlot->series.size() > 0)
        {
            m_glconstellationPlot->series[0]->visible = true;
            m_glconstellationPlot->series[1]->visible = false;
            m_gltimePlot->series[0]->visible = true;
            m_gltimePlot->series[1]->visible = true;
            m_gltimePlot->series[2]->visible = false;
            m_gltimePlot->series[3]->visible = false;
            m_glFFTplot->series[0]->visible = true;
            m_glFFTplot->series[1]->visible = false;
            if(m_calculator)
                m_calculator->EnableChannels(0x1);
        }
    }
    else if( chsel == 1)
    {
        if(m_glconstellationPlot->series.size() > 0)
        {
            m_glconstellationPlot->series[0]->visible = false;
            m_glconstellationPlot->series[1]->visible = true;
            m_gltimePlot->series[0]->visible = false;
            m_gltimePlot->series[1]->visible = false;
            m_gltimePlot->series[2]->visible = true;
            m_gltimePlot->series[3]->visible = true;
            m_glFFTplot->series[0]->visible = false;
            m_glFFTplot->series[1]->visible = true;
            if(m_calculator)
                m_calculator->EnableChannels(0x2);
        }
    }
    else
    {
        if(m_glconstellationPlot->series.size() > 0)
        {
            m_glconstellationPlot->series[0]->visible = true;
            m_glconstellationPlot->series[1]->visible = true;
            m_gltimePlot->series[0]->visible = true;
            m_gltimePlot->series[1]->visible = true;
            m_gltimePlot->series[2]->visible = true;
            m_gltimePlot->series[3]->visible = true;
            m_glFFTplot->series[0]->visible = true;
            m_glFFTplot->series[1]->visible = true;
            if(m_calculator)
                m_calculator->EnableChannels(0x3);
        }
    }
    m_glconstellationPlot->Draw();
    m_glFFTplot->Draw();
    m_gltimePlot->Draw();
}

void pnlFFTviewer::OnChangePlotVisibility(wxCommandEvent& event)
{
    bool iqtime = chkShowTime->IsChecked();
    bool iqconst = chkShowConstellation->IsChecked();
    bool iqplot = iqtime | iqconst;
    bool fftplot = chkShowFFT->IsChecked();

    if( !fftplot && !(iqtime || iqplot))
    {
        fftplot = true;
        chkShowFFT->SetValue(true);
    }

    m_plotSplitter->Unsplit();
    sizerTimeDomain->Show(iqtime);
    m_glconstellationPlot->Show(iqconst);

    if((iqplot || iqtime) && fftplot)
    {
        m_plotSplitter->SplitHorizontally(Panel1, Panel2);
        Panel1->Show(true);
        Panel2->Show(true);
        Panel1->Enable(true);
        Panel2->Enable(true);
    }
    else if((iqplot || iqtime) && !fftplot)
    {
        Panel1->Show(true);
        Panel1->Enable(true);
        Panel2->Show(false);
        Panel2->Enable(false);
    }
    else if(!(iqplot || iqtime) && fftplot)
    {
        m_plotSplitter->ReplaceWindow( m_plotSplitter->GetWindow1(), Panel2);
        Panel2->Show(true);
        Panel2->Enable(true);
        Panel1->Show(false);
        Panel1->Enable(false);
    }
    else
    {
        m_plotSplitter->SplitHorizontally(Panel1, Panel2);
        Panel1->Show(true);
        Panel2->Show(true);
        Panel1->Enable(true);
        Panel2->Enable(true);
    }
    Panel1->Layout();
    Panel1->Update();
    Panel2->Update();
    Update();
}

void pnlFFTviewer::OnCenterSpanChange(wxCommandEvent& event)
{
    double dFreq = 0;
    double dSpan = 0;
    m_txtCenterFreq->GetValue().ToDouble(&dFreq);
    dFreq *= btnCenterFreqRatio->GetRatio();
    m_txtFreqSpan->GetValue().ToDouble(&dSpan);
    dSpan *= btnFreqSpanRatio->GetRatio();
    m_glFFTplot->ZoomX(dFreq, dSpan);
}

void pnlFFTviewer::OnYaxisChange(wxCommandEvent& event)
{
    double dFreq = 0;
    double dSpan = 0;
    m_txtCenterFreq->GetValue().ToDouble(&dFreq);
    dFreq *= btnCenterFreqRatio->GetRatio();
    m_txtFreqSpan->GetValue().ToDouble(&dSpan);
    dSpan *= btnFreqSpanRatio->GetRatio();
    double ymin = 0;
    double ymax = 0;
    txtYaxisBottom->GetValue().ToDouble(&ymin);
    txtYaxisTop->GetValue().ToDouble(&ymax);
    m_glFFTplot->ZoomY((ymax+ymin)/2, abs(ymax-ymin));
}

void pnlFFTviewer::OnchkDCcorrectionClick(wxCommandEvent& event)
{
    if(m_calculator)
        m_calculator->SetDCcorrection(chkDCcorrection->IsChecked());
}

void pnlFFTviewer::OnbtnRefreshClick(wxCommandEvent& event)
{
    m_glFFTplot->Refresh();
}

void pnlFFTviewer::OnbtnExtraControlsClick(wxCommandEvent& event)
{
    if(m_extraControls == NULL)
        m_extraControls = new dlgExtraControls(this, m_controlPort);
    m_extraControls->Show();
}

void pnlFFTviewer::OncmbWindowFunctionSelected(wxCommandEvent& event)
{
    if(m_calculator)
        m_calculator->SetWindowFunction(cmbWindowFunction->GetSelection());
}

void pnlFFTviewer::StopCapturing()
{
    if(m_dataReading) //stop data reading before closing window
    {
        wxCommandEvent evt;
        OnbtnStartStopClick(evt);
    }
}

void pnlFFTviewer::OnspinAvgChange(wxCommandEvent& event)
{
    long avgCount = 0;
    spinAvg->GetValue().ToLong(&avgCount);
    if(avgCount <= 0)
    {
        avgCount = 1;
        spinAvg->SetValue("1");
    }
    if(m_calculator)
        m_calculator->SetAveragingCount(avgCount, chkCalcAverage->IsChecked());
}

void pnlFFTviewer::AssignControl(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
}

void pnlFFTviewer::SetBoardType(unsigned i)
{
    //if(i < cmbBoardType->GetCount())
        //cmbBoardType->SetSelection(i);
}

void pnlFFTviewer::ChangeFrequencyOffset(int offset_kHz)
{
    wxCriticalSectionLocker lock(m_dataCS);
    m_glFFTplot->settings.gridXoffset = offset_kHz/1000;
    m_glFFTplot->Refresh();
}

void pnlFFTviewer::HandleMessage(const LMS_Message &msg)
{
    if(msg.type == MSG_RX_FREQUENCY_CHANGED)
    {
        ChangeFrequencyOffset(msg.param1);
    }
    if(msg.type == MSG_CGEN_FREQUENCY_CHANGED)
    {
        float samplingFreq_MHz = lmsControl->GetReferenceFrequencyNCO(true);
        txtSamplingFreq->SetValue(wxString::Format("%.3f", samplingFreq_MHz/2));
        m_glFFTplot->SetInitialDisplayArea(-1000000*samplingFreq_MHz/4, 1000000*samplingFreq_MHz/4, -100, 0);
    }
}
