/**
@file	pnlBuffersEVB7v2.cpp
@author Lime Microsystems
@brief	panel for EVB7v2 board
*/
#include "pnlBuffersEVB7v2.h"

//(*InternalHeaders(pnlBuffersEVB7v2)
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/string.h>
//*)

//(*IdInit(pnlBuffersEVB7v2)
const long pnlBuffersEVB7v2::ID_CHECKBOX1 = wxNewId();
const long pnlBuffersEVB7v2::ID_CHECKBOX2 = wxNewId();
const long pnlBuffersEVB7v2::ID_CHECKBOX3 = wxNewId();
const long pnlBuffersEVB7v2::ID_CHECKBOX4 = wxNewId();
const long pnlBuffersEVB7v2::ID_CHECKBOX5 = wxNewId();
const long pnlBuffersEVB7v2::ID_CHECKBOX6 = wxNewId();
const long pnlBuffersEVB7v2::ID_CHECKBOX7 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlBuffersEVB7v2,wxPanel)
	//(*EventTable(pnlBuffersEVB7v2)
	//*)
END_EVENT_TABLE()

pnlBuffersEVB7v2::pnlBuffersEVB7v2(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size,int style, wxString name)
{
    gpioStates.resize(56, 0);
	BuildContent(parent,id,pos,size);
}

void pnlBuffersEVB7v2::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlBuffersEVB7v2)
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxSize(800,700), wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Buffers"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	chkDIO_DIR_CTRL1 = new wxCheckBox(this, ID_CHECKBOX1, _T("DIO_DIR_CTRL1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkDIO_DIR_CTRL1->SetValue(false);
	chkDIO_DIR_CTRL1->SetToolTip(_T("On board buffers direction control for Port 1. If selected, Port 1 is receiver."));
	FlexGridSizer2->Add(chkDIO_DIR_CTRL1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkDIO_DIR_CTRL2 = new wxCheckBox(this, ID_CHECKBOX2, _T("DIO_DIR_CTRL2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkDIO_DIR_CTRL2->SetValue(true);
	chkDIO_DIR_CTRL2->SetToolTip(_T("On board buffers direction control for Port 2. If selected, Port 2 is receiver."));
	FlexGridSizer2->Add(chkDIO_DIR_CTRL2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkDIO_BUFF_OE = new wxCheckBox(this, ID_CHECKBOX3, _T("DIO_BUFF_OE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkDIO_BUFF_OE->SetValue(false);
	chkDIO_BUFF_OE->SetToolTip(_T("If selected, sets onboard buffers to Hi-Impedance state."));
	FlexGridSizer2->Add(chkDIO_BUFF_OE, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkIQSEL1_DIR = new wxCheckBox(this, ID_CHECKBOX4, _T("IQSEL1_DIR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkIQSEL1_DIR->SetValue(true);
	chkIQSEL1_DIR->SetToolTip(_T("On board buffers IQSEL pin direction control for Port 1. If selected, Port 1 is receiver."));
	FlexGridSizer2->Add(chkIQSEL1_DIR, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkIQSEL2_DIR = new wxCheckBox(this, ID_CHECKBOX5, _T("IQSEL2_DIR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkIQSEL2_DIR->SetValue(false);
	chkIQSEL2_DIR->SetToolTip(_T("On board buffers IQSEL pin direction control for Port 2. If selected, Port 2 is receiver."));
	FlexGridSizer2->Add(chkIQSEL2_DIR, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkG_PWR_DWN = new wxCheckBox(this, ID_CHECKBOX6, _T("G_PWR_DWN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chkG_PWR_DWN->SetValue(false);
	chkG_PWR_DWN->SetToolTip(_T("External enable control signal for the internal LDO\'s."));
	FlexGridSizer2->Add(chkG_PWR_DWN, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkDIG_RST = new wxCheckBox(this, ID_CHECKBOX7, _T("DIG_RST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chkDIG_RST->SetValue(false);
	chkDIG_RST->Hide();
	chkDIG_RST->SetToolTip(_T("Controls Hardware pin logic reset."));
	FlexGridSizer2->Add(chkDIG_RST, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	SetSizer(FlexGridSizer1);
	Layout();

	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBuffersEVB7v2::OnchkDIO_DIR_CTRL1Click);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBuffersEVB7v2::OnchkDIO_DIR_CTRL2Click);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBuffersEVB7v2::OnchkDIO_BUFF_OEClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBuffersEVB7v2::OnchkIQSEL1_DIRClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBuffersEVB7v2::OnchkIQSEL2_DIRClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBuffersEVB7v2::OnchkG_PWR_DWNClick);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBuffersEVB7v2::OnchkDIG_RSTClick);
	//*)
}

pnlBuffersEVB7v2::~pnlBuffersEVB7v2()
{
	//(*Destroy(pnlBuffersEVB7v2)
	//*)
}

int pnlBuffersEVB7v2::SendCommand()
{
    Refresh();
    int status = lmsControl->SetGPIOStates(gpioStates);
    UpdateGUI();
    return status;
}

int pnlBuffersEVB7v2::ReadbackGPIOStates()
{
    lmsControl->GetGPIOStates(gpioStates);
    chkDIG_RST->SetValue(getbit(gpioStates[0], 6));
    chkDIO_BUFF_OE->SetValue(getbit(gpioStates[0], 2));
    chkDIO_DIR_CTRL1->SetValue(getbit(gpioStates[0], 0));
    chkDIO_DIR_CTRL2->SetValue(getbit(gpioStates[0], 1));
    chkIQSEL1_DIR->SetValue(getbit(gpioStates[0], 3));
    chkIQSEL2_DIR->SetValue(getbit(gpioStates[0], 4));
    chkG_PWR_DWN->SetValue(getbit(gpioStates[0], 5));

    Refresh();
    return 0;
}

void pnlBuffersEVB7v2::OnchkDIO_DIR_CTRL1Click(wxCommandEvent& event)
{
    //gpioStates[DIO_DIR_CTRL1] = chkDIO_DIR_CTRL1->GetValue();
    gpioStates[0] = setbit(gpioStates[0], 0, chkDIO_DIR_CTRL1->GetValue());
    SendCommand();
}

void pnlBuffersEVB7v2::OnchkDIO_DIR_CTRL2Click(wxCommandEvent& event)
{
    //gpioStates[DIO_DIR_CTRL2] = chkDIO_DIR_CTRL2->GetValue();
    gpioStates[0] = setbit(gpioStates[0], 1, chkDIO_DIR_CTRL2->GetValue());
    SendCommand();
}

void pnlBuffersEVB7v2::OnchkDIO_BUFF_OEClick(wxCommandEvent& event)
{
    //gpioStates[DIO_BUFF_OE] = chkDIO_BUFF_OE->GetValue();
    gpioStates[0] = setbit(gpioStates[0], 2, chkDIO_BUFF_OE->GetValue());
    SendCommand();
}

void pnlBuffersEVB7v2::OnchkIQSEL1_DIRClick(wxCommandEvent& event)
{
    //gpioStates[IQSEL1_DIR] = chkIQSEL1_DIR->GetValue();
    gpioStates[0] = setbit(gpioStates[0], 3, chkIQSEL1_DIR->GetValue());
    SendCommand();
}

void pnlBuffersEVB7v2::OnchkIQSEL2_DIRClick(wxCommandEvent& event)
{
    //gpioStates[IQSEL2_DIR] = chkIQSEL2_DIR->GetValue();
    gpioStates[0] = setbit(gpioStates[0], 4, chkIQSEL2_DIR->GetValue());
    SendCommand();
}

void pnlBuffersEVB7v2::OnchkG_PWR_DWNClick(wxCommandEvent& event)
{
    //gpioStates[G_PWR_DWN] = chkG_PWR_DWN->GetValue();
    gpioStates[0] = setbit(gpioStates[0], 5, chkG_PWR_DWN->GetValue());
    SendCommand();
}

void pnlBuffersEVB7v2::OnchkDIG_RSTClick(wxCommandEvent& event)
{
    //gpioStates[DIG_RST] = chkDIG_RST->GetValue();
    gpioStates[0] = setbit(gpioStates[0], 6, chkDIG_RST->GetValue());
    SendCommand();
}

unsigned char pnlBuffersEVB7v2::setbit(const unsigned char src, const int pos, const bool value)
{
    int val = src;
    val = val & ~(0x1 << pos);
    val |= value << pos;
    return val;
}

bool pnlBuffersEVB7v2::getbit(const unsigned char src, const int pos)
{
    return (src >> pos) & 0x01;
}

void pnlBuffersEVB7v2::UpdateGUI()
{
    ReadbackGPIOStates();
    Refresh();
}

void pnlBuffersEVB7v2::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
}
