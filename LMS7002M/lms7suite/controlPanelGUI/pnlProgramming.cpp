/**
@file 	pnlProgramming.cpp
@author	Lime Microsystems
@brief	panel for uploading data to FPGA
*/
#include "pnlProgramming.h"

//(*InternalHeaders(pnlProgramming)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/gauge.h>
//*)
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/wfstream.h>
#include "Programmer.h"

//(*IdInit(pnlProgramming)
const long pnlProgramming::ID_BUTTON1 = wxNewId();
const long pnlProgramming::ID_STATICTEXT1 = wxNewId();
const long pnlProgramming::ID_STATICTEXT2 = wxNewId();
const long pnlProgramming::ID_BUTTON2 = wxNewId();
const long pnlProgramming::ID_STATICTEXT5 = wxNewId();
const long pnlProgramming::ID_GAUGE1 = wxNewId();
const long pnlProgramming::ID_STATICTEXT3 = wxNewId();
const long pnlProgramming::ID_STATICTEXT6 = wxNewId();
const long pnlProgramming::ID_CHOICE2 = wxNewId();
const long pnlProgramming::ID_CHOICE1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlProgramming,wxPanel)
	//(*EventTable(pnlProgramming)
	//*)
END_EVENT_TABLE()

pnlProgramming::pnlProgramming(ConnectionManager* pSerPort, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name):
    PluginPanel(this)
{
    m_programmer = new Programmer(pSerPort);
	BuildContent(parent,id,pos,size);
}

void pnlProgramming::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlProgramming)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 5, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	btnOpen = new wxButton(this, ID_BUTTON1, _T("Open"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(btnOpen, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("File:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer6->Add(StaticText1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	lblFilename = new wxStaticText(this, ID_STATICTEXT2, _T("\?"), wxDefaultPosition, wxSize(400,-1), 0, _T("ID_STATICTEXT2"));
	FlexGridSizer6->Add(lblFilename, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnProgram = new wxButton(this, ID_BUTTON2, _T("Program"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(btnProgram, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer8 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer8->AddGrowableCol(1);
	lblProgressPercent = new wxStaticText(this, ID_STATICTEXT5, _T("0 %"), wxDefaultPosition, wxSize(48,-1), 0, _T("ID_STATICTEXT5"));
	FlexGridSizer8->Add(lblProgressPercent, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	progressBar = new wxGauge(this, ID_GAUGE1, 100, wxDefaultPosition, wxSize(-1,21), 0, wxDefaultValidator, _T("ID_GAUGE1"));
	FlexGridSizer8->Add(progressBar, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _T("Device:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer7->Add(StaticText2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT6, _T("Programming mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer7->Add(StaticText3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbDevice = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	cmbDevice->Append(_T("HPM1000"));
	cmbDevice->SetSelection( cmbDevice->Append(_T("Altera FPGA")) );
	FlexGridSizer7->Add(cmbDevice, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	cmbProgMode = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxSize(176,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	cmbProgMode->SetSelection( cmbProgMode->Append(_T("0")) );
	cmbProgMode->Append(_T("1"));
	cmbProgMode->Append(_T("2"));
	cmbProgMode->Append(_T("3"));
	cmbProgMode->Append(_T("4"));
	cmbProgMode->Append(_T("5"));
	cmbProgMode->Append(_T("6"));
	cmbProgMode->Append(_T("7"));
	cmbProgMode->Append(_T("8"));
	FlexGridSizer7->Add(cmbProgMode, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3->Add(FlexGridSizer7, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlProgramming::OnbtnOpenClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlProgramming::OnbtnProgMyriadClick);
	Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&pnlProgramming::OncmbDeviceSelect);
	//*)
	wxCommandEvent evt;
	OncmbDeviceSelect(evt);
}

pnlProgramming::~pnlProgramming()
{
	//(*Destroy(pnlProgramming)
	//*)
}


void pnlProgramming::OnbtnOpenClick(wxCommandEvent& event)
{
    if(!m_programmer)
        return;
    wxFileDialog dlg(this, _("Select file"), "", "", "rbf (*.rbf)| *.rbf|bin (*.bin)| *.bin|All files(*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    lblFilename->SetLabel(dlg.GetPath());

}

void pnlProgramming::OnbtnProgMyriadClick(wxCommandEvent& event)
{
    progressBar->SetValue(0);
    lblProgressPercent->SetLabel(wxString::Format("%3.1f%%", 0.0));
    if(!m_programmer)
        return;
    if( (cmbDevice->GetSelection() == 1 && cmbProgMode->GetSelection() == 2) == false)
    {
		if (lblFilename->GetLabel().length() <= 1)
		{
			wxMessageBox("Program file not selected");
			return;
		}
        wxFFileInputStream fin(lblFilename->GetLabel());

        if(!fin.IsOk())
        {
            wxMessageBox("Error loading program file");
            return;
        }
        fin.SeekI(0, wxFromEnd);
        unsigned int m_data_size = fin.TellI();

        unsigned char *m_data = new unsigned char[m_data_size];
        fin.SeekI(0, wxFromStart);
        fin.Read((char*)m_data, m_data_size);
        m_programmer->LoadArray(m_data, m_data_size);
        delete m_data;
    }
    m_programmer->RegisterForNotifications(this);
    int status = m_programmer->UploadProgram(cmbDevice->GetSelection(), cmbProgMode->GetSelection());
    if(status != 0)
    {
        if(status == -3)
            wxMessageBox("Board not connected");
        if(status == -2)
            wxMessageBox("Program file not selected");
    }
    m_programmer->UnregisterFromNotifications(this);
    Notify(LMS_Message(MSG_PROGRAMMING_COMPLETED, "", 0, 0));
}

void pnlProgramming::HandleMessage(const LMS_Message &msg)
{
    switch(msg.type)
    {
    case MSG_INFO:
    case MSG_ERROR:
        wxMessageBox( wxString::Format("%s", msg.text), _(""));
        break;
    case MSG_PROGRAMMING_PACKET_SENT:
        if(progressBar->GetRange() != msg.param2)
            progressBar->SetRange(msg.param2);
        progressBar->SetValue(msg.param1);
        lblProgressPercent->SetLabel(wxString::Format("%3.1f%%", 100.0*msg.param1/msg.param2));
        wxYield();
        break;
    default:
        break;
    }
}

void pnlProgramming::OncmbDeviceSelect(wxCommandEvent& event)
{
    if(cmbDevice->GetSelection() == 1)
    {
        cmbProgMode->Clear();
        cmbProgMode->Append("Bitstream to FPGA");
        cmbProgMode->Append("Bitstream to Flash");
        cmbProgMode->Append("Bitstream from Flash");
        cmbProgMode->SetSelection(0);
    }
    else
    {
        cmbProgMode->Clear();
        for(int i=0; i<=8; ++i)
            cmbProgMode->Append(wxString::Format("%i", i));
        cmbProgMode->SetSelection(0);
    }
}
