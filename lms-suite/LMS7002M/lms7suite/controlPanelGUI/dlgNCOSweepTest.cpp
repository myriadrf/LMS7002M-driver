/**
@file	dlgNCOSweepTest.cpp
@author Lime Microsystems
@brief	dialog for testing purposes
*/
#include "dlgNCOSweepTest.h"

//(*InternalHeaders(dlgNCOSweepTest)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/gauge.h>
//*)
#include <vector>
#include "LMS7002_MainControl.h"
#include "RegistersMap.h"
#include "CommonUtilities.h"
#include "ComboBoxMap.h"
//(*IdInit(dlgNCOSweepTest)
const long dlgNCOSweepTest::ID_STATICTEXT1 = wxNewId();
const long dlgNCOSweepTest::ID_TEXTCTRL1 = wxNewId();
const long dlgNCOSweepTest::ID_STATICTEXT2 = wxNewId();
const long dlgNCOSweepTest::ID_TEXTCTRL2 = wxNewId();
const long dlgNCOSweepTest::ID_STATICTEXT3 = wxNewId();
const long dlgNCOSweepTest::ID_TEXTCTRL3 = wxNewId();
const long dlgNCOSweepTest::ID_STATICTEXT6 = wxNewId();
const long dlgNCOSweepTest::ID_TEXTCTRL4 = wxNewId();
const long dlgNCOSweepTest::ID_BUTTON1 = wxNewId();
const long dlgNCOSweepTest::ID_STATICTEXT4 = wxNewId();
const long dlgNCOSweepTest::ID_STATICTEXT5 = wxNewId();
const long dlgNCOSweepTest::ID_STATICTEXT7 = wxNewId();
const long dlgNCOSweepTest::ID_STATICTEXT8 = wxNewId();
const long dlgNCOSweepTest::ID_GAUGE1 = wxNewId();
const long dlgNCOSweepTest::ID_CHECKBOX1 = wxNewId();
//*)
const long dlgNCOSweepTest::ID_TIMER = wxNewId();

BEGIN_EVENT_TABLE(dlgNCOSweepTest,wxDialog)
	//(*EventTable(dlgNCOSweepTest)
	//*)
END_EVENT_TABLE()

dlgNCOSweepTest::dlgNCOSweepTest(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_sweeping = false;
    m_activeParameter = 0;
    mTimeRemaining_ms = 0;
    mUpdatePeriod_ms = 500;
    mStartFreqMHz = 1;
    mEndFreqMHz = 10;
    mStepFreqMHz = 1;
    mStepPeriod_ms = 10000;
    mStep = 0;
	BuildContent(parent,id,pos,size);
}

void dlgNCOSweepTest::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    mRx = false;
    lmsControl = NULL;
    m_pTimer = new wxTimer(this,ID_TIMER);
	//(*Initialize(dlgNCOSweepTest)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;

	Create(parent, wxID_ANY, _T("NCO Sweep"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("Start Freq (MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	txtStartFreqMHz = new wxTextCtrl(this, ID_TEXTCTRL1, _T("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer2->Add(txtStartFreqMHz, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("End Freq (MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	txtEndFreqMHz = new wxTextCtrl(this, ID_TEXTCTRL2, _T("10"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer2->Add(txtEndFreqMHz, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("Step (MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	txtFreqStepMHz = new wxTextCtrl(this, ID_TEXTCTRL3, _T("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer2->Add(txtFreqStepMHz, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _T("Step duration(s):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer2->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtDuration = new wxTextCtrl(this, ID_TEXTCTRL4, _T("10"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	FlexGridSizer2->Add(txtDuration, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnStartStop = new wxButton(this, ID_BUTTON1, _T("Start"), wxDefaultPosition, wxSize(200,40), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(btnStartStop, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _T("Current Freq (MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblCurrentFreq = new wxStaticText(this, ID_STATICTEXT5, _T("\?"), wxDefaultPosition, wxSize(64,-1), 0, _T("ID_STATICTEXT5"));
	FlexGridSizer3->Add(lblCurrentFreq, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT7, _T("time left:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer3->Add(StaticText5, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblTimeLeft = new wxStaticText(this, ID_STATICTEXT8, _T("0"), wxDefaultPosition, wxSize(64,-1), 0, _T("ID_STATICTEXT8"));
	FlexGridSizer3->Add(lblTimeLeft, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	progressBar = new wxGauge(this, ID_GAUGE1, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAUGE1"));
	FlexGridSizer1->Add(progressBar, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	m_parametersList = new wxFlexGridSizer(0, 1, 0, 0);
	chkResampleRSSI0 = new wxCheckBox(this, ID_CHECKBOX1, _T("Update RSSI0 each iteration"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkResampleRSSI0->SetValue(false);
	m_parametersList->Add(chkResampleRSSI0, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(m_parametersList, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer1->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgNCOSweepTest::OnbtnStartStopClick);
	//*)
}

dlgNCOSweepTest::~dlgNCOSweepTest()
{
    if(m_pTimer)
        m_pTimer->Stop();
	//(*Destroy(dlgNCOSweepTest)
	//*)
}

void dlgNCOSweepTest::Initialize(LMS7002_MainControl *pControl, bool Rx)
{
    SetTitle(GetTitle()+ (Rx?" Rx":" Tx"));
    lmsControl = pControl;
    mRx = Rx;
    AddParameters();
    UpdateGUI();
}

void dlgNCOSweepTest::OnbtnStartStopClick(wxCommandEvent& event)
{
    if(m_sweeping)
        m_sweeping = false;
    else
        Sweep();
    return;
}

void dlgNCOSweepTest::AddParameters()
{
    parameters.clear();
    parameters.push_back(R_CTL_LPF_RBB);
    parameters.push_back(C_CTL_LPFH_RBB);
    parameters.push_back(C_CTL_LPFL_RBB);
    parameters.push_back(G_PGA_RBB);
    parameters.push_back(CG_IAMP_TBB);
    parameters.push_back(RCAL_LPFH_TBB);
    parameters.push_back(RCAL_LPFLAD_TBB);
    parameters.push_back(RCAL_LPFS5_TBB);
    parameters.push_back(CCAL_LPFLAD_TBB);
    parameters.push_back(CFB_TIA_RFE);
    parameters.push_back(RFB_TIA_RFE);

    paramchoice = new wxChoice(this, wxNewId(), wxDefaultPosition, wxDefaultSize, 0, NULL, 0,wxDefaultValidator, "ParamChoice");
    for(unsigned i=0; i<parameters.size(); ++i)
    {
        ControlParameter paraminfo;
        paraminfo = lmsControl->getRegistersMap()->getParameterInfo(parameters[i]);
        wxString strname = wxString::Format("%s", paraminfo.m_name);
        paramchoice->Append(strname);
    }
    paramchoice->SetSelection(0);
    m_activeParameter = 0;
    wxFlexGridSizer* activeSizer = new wxFlexGridSizer(0, 7, 0, 0);
    activeSizer->Add(paramchoice, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
    txtparambeg = new wxTextCtrl(this, wxNewId(), "0", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "InputStart");
    txtparamend = new wxTextCtrl(this, wxNewId(), "0", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "InputEnd");
    txtparamstep = new wxTextCtrl(this, wxNewId(), "0", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "InputStep");
    wxStaticText *lbltemp = new wxStaticText(this, wxNewId(), "From:", wxDefaultPosition, wxDefaultSize, 0, "from");
    activeSizer->Add(lbltemp, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
    activeSizer->Add(txtparambeg, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
    lbltemp = new wxStaticText(this, wxNewId(), "To:", wxDefaultPosition, wxDefaultSize, 0, "To");
    activeSizer->Add(lbltemp, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
    activeSizer->Add(txtparamend, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
    lbltemp = new wxStaticText(this, wxNewId(), "Step:", wxDefaultPosition, wxDefaultSize, 0, "To");
    activeSizer->Add(lbltemp, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
    activeSizer->Add(txtparamstep, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer1->Add(activeSizer, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
}

void dlgNCOSweepTest::UpdateGUI()
{
    long value = 0;
    std::map<long, LMS7002_Parameter>::iterator iter;
    for(iter=wndId2Enum.begin(); iter!=wndId2Enum.end();++iter)
    {
        value = lmsControl->GetParam(iter->second);
        ComboBoxMap *boxmap = (ComboBoxMap*)wxWindow::FindWindowById(iter->first);
        boxmap->SetSelection(value);
    }
}

void dlgNCOSweepTest::Sweep()
{
    m_sweeping = true;
    m_paramBeg = 0;
    m_paramEnd = 0;
    m_paramStep = 0;
    mStep_parameter=0;
    txtparambeg->GetValue().ToLong(&m_paramBeg);
    txtparamend->GetValue().ToLong(&m_paramEnd);
    txtparamstep->GetValue().ToLong(&m_paramStep);
    if(m_paramStep == 0)
        m_paramStep = 1;
    fout.open("test_output.txt", ios::out);
    firstRead = true;
    mStep = 1000;
    mStartFreqMHz = 1;
    mEndFreqMHz = 10;
    txtStartFreqMHz->GetValue().ToDouble(&mStartFreqMHz);
    txtStartFreqMHz->Enable(false);
    txtEndFreqMHz->GetValue().ToDouble(&mEndFreqMHz);
    txtEndFreqMHz->Enable(false);
    txtFreqStepMHz->GetValue().ToDouble(&mStepFreqMHz);
    txtFreqStepMHz->Enable(false);
    txtDuration->Enable(false);
    btnStartStop->SetLabel("Stop");
    double timePeriod = 0;
    txtDuration->GetValue().ToDouble(&timePeriod);
    progressBar->SetValue(0);
    progressBar->SetRange(((m_paramEnd-m_paramBeg)/m_paramStep+1)*((mEndFreqMHz-mStartFreqMHz)/mStepFreqMHz+1.5));
    mStepPeriod_ms = timePeriod*1000;
    mUpdatePeriod_ms = mStepPeriod_ms > 500 ? 500 : mStepPeriod_ms;
    mTimeRemaining_ms = 0;
    m_activeParameter = paramchoice->GetSelection();

    ControlParameter paraminfo;
//    std::map<long, LMS7002_Parameter>::iterator iter;
//    for(iter=wndId2Enum.begin(); iter!=wndId2Enum.end();++iter)
//    {
    bool resampleRSSI0 = chkResampleRSSI0->IsChecked();
    for(unsigned i=0; i<parameters.size(); ++i)
    {
        paraminfo = lmsControl->getRegistersMap()->getParameterInfo(parameters[i]);
        long value = lmsControl->GetParam(parameters[i], true, true);
        fout << paraminfo.m_name << "\t" << value << endl;
    }
    paraminfo = lmsControl->getRegistersMap()->getParameterInfo(parameters[m_activeParameter]);

    wxLongLong t1 = wxGetUTCTimeMillis();
    int paramStep = 0;
    firstRead = true;
    for(int i=m_paramBeg; i<=m_paramEnd && m_sweeping; i+=m_paramStep)
    {
        fout << "-\t-\t" << paraminfo.m_name << "\t" << i << endl;
        char ctemp[512];
        sprintf(ctemp, "%s = %i\n", paraminfo.m_name.c_str(), i);
        cout << ctemp;
        lmsControl->SetParam(parameters[m_activeParameter], i);
        int mStep = 0;
        double freq = mStartFreqMHz;
        if(resampleRSSI0)
            firstRead = true;
        while(freq <= mEndFreqMHz && m_sweeping)
        {
            freq = mStartFreqMHz+mStep*mStepFreqMHz;
            ++mStep;
            progressBar->SetValue(paramStep*((mEndFreqMHz-mStartFreqMHz)/mStepFreqMHz+1.5)+mStep);
            std::vector<double> fcwValues;
            std::vector<int> phoValues;
            lblCurrentFreq->SetLabel(wxString::Format("%f", freq));
            mTimeRemaining_ms = mStepPeriod_ms;
            lblTimeLeft->SetLabel(wxString::Format("%.1f", mTimeRemaining_ms/1000.0));
            for(int i=0; i<16; ++i)
            {
                fcwValues.push_back(freq);
                phoValues.push_back(0);
            }
            lmsControl->SetNCOconfiguration(fcwValues, phoValues, mRx);
            while(wxGetUTCTimeMillis()-t1<mStepPeriod_ms && m_sweeping)
            {
                wxYield();
                wxMilliSleep(10);
            }
            t1 = wxGetUTCTimeMillis();
            //Read RSSI
            lmsControl->SetParam(CAPTURE, 0);
            lmsControl->SetParam(CAPSEL, 0);
            lmsControl->SetParam(CAPTURE, 1);
            lmsControl->SetParam(CAPTURE, 0);
            long value = lmsControl->getRegistersMap()->GetRegisterValue(0x040E, true, true);
            long value2 = lmsControl->getRegistersMap()->GetRegisterValue(0x040F, true, true);
            long val = ((value & 0x3) | (value2<<2)) & 0x3FFFF;
            char ctemp[40];
            sprintf(ctemp, "%.5X", val);
            double rssin = val;
            if(firstRead)
                RSSI0 = rssin;
            firstRead = false;
            if(RSSI0 == 0 || rssin == 0)
            {
                printf("ERROR RSSI = 0\n");
                fout << "rssi=0\t";
            }
            else
            {
                double result = 20*log10(rssin/RSSI0);
                fout << result << "\t";
            }
            fout << freq << "\t" << ctemp << "\t";
            fout << endl;
        }
        ++paramStep;
    }
    m_sweeping = false;
    fout.close();

    progressBar->SetValue(progressBar->GetRange());
    txtStartFreqMHz->Enable(true);
    txtEndFreqMHz->Enable(true);
    txtFreqStepMHz->Enable(true);
    txtDuration->Enable(true);
    btnStartStop->SetLabel("Start");
    lblTimeLeft->SetLabel(wxString::Format("%.1f", 0));
    fout.close();
}

void dlgNCOSweepTest::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "nco sweep panel don't have control module assigned" << std::endl;
        return;
    }

    LMS7002_Parameter parameter;
    try
    {
        parameter = wndId2Enum.at(event.GetId());
    }
    catch( std::exception & e )
    {
        std::cout << "Control element(ID = " << event.GetId() << ") don't have assigned LMS parameter enumeration." << std::endl;
        return;
    }
    switch(parameter)
    {
    default:
        lmsControl->SetParam( parameter, event.GetInt());
        //std::cout << "control id " << event.GetId() << " value " << event.GetInt() << std::endl;
    }
}
