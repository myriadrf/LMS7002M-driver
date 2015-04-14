/**
@file 	pnlTesting.cpp
@author Lime Microsystems
@brief	panel for showing testing utilities
*/
#include "pnlTesting.h"

//(*InternalHeaders(pnlTesting)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

#include "dlgNCOSweepTest.h"
#include "dlgVCOSweepTest.h"

//(*IdInit(pnlTesting)
const long pnlTesting::ID_BUTTON1 = wxNewId();
const long pnlTesting::ID_BUTTON3 = wxNewId();
const long pnlTesting::ID_BUTTON2 = wxNewId();
const long pnlTesting::ID_BUTTON4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlTesting,wxPanel)
	//(*EventTable(pnlTesting)
	//*)
END_EVENT_TABLE()

pnlTesting::pnlTesting(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, long style, wxString name)
{
    lmsControl = NULL;
    dlgNCOSweepRx = NULL;
    dlgVCOSweepRx = NULL;
    dlgNCOSweepTx = NULL;
    dlgVCOSweepTx = NULL;
	BuildContent(parent,id,pos,size);
}

void pnlTesting::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
}

void pnlTesting::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlTesting)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	btnNCOSweepRx = new wxButton(this, ID_BUTTON1, _T("NCO Sweep RX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(btnNCOSweepRx, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnVCOSweepRx = new wxButton(this, ID_BUTTON3, _T("VCO Sweep Rx"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer1->Add(btnVCOSweepRx, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnNCOSweepTx = new wxButton(this, ID_BUTTON2, _T("NCO Sweep TX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer1->Add(btnNCOSweepTx, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnVCOSweepTx = new wxButton(this, ID_BUTTON4, _T("VCO Sweep Tx"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer1->Add(btnVCOSweepTx, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTesting::OnbtnNCOSweepRxClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTesting::OnbtnVCOSweepRxClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTesting::OnbtnNCOSweepTxClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTesting::OnbtnVCOSweepTxClick);
	//*)
}

pnlTesting::~pnlTesting()
{
	//(*Destroy(pnlTesting)
	//*)
}

void pnlTesting::OnbtnNCOSweepRxClick(wxCommandEvent& event)
{
    if(dlgNCOSweepRx == NULL)
    {
        dlgNCOSweepRx = new dlgNCOSweepTest(this);
        dlgNCOSweepRx->Initialize(lmsControl, true);
        dlgNCOSweepRx->Show();
    }
    else
        dlgNCOSweepRx->Show();
}

void pnlTesting::OnbtnNCOSweepTxClick(wxCommandEvent& event)
{
    if(dlgNCOSweepTx == NULL)
    {
        dlgNCOSweepTx = new dlgNCOSweepTest(this);
        dlgNCOSweepTx->Initialize(lmsControl, false);
        dlgNCOSweepTx->Show();
    }
    else
        dlgNCOSweepTx->Show();
}

void pnlTesting::UpdateGUI()
{
    if(dlgNCOSweepRx)
        dlgNCOSweepRx->UpdateGUI();
    if(dlgNCOSweepTx)
        dlgNCOSweepTx->UpdateGUI();
    if(dlgVCOSweepRx)
        dlgVCOSweepRx->UpdateGUI();
    if(dlgVCOSweepTx)
        dlgVCOSweepTx->UpdateGUI();
}

void pnlTesting::OnbtnVCOSweepRxClick(wxCommandEvent& event)
{
    if(dlgVCOSweepRx == NULL)
    {
        dlgVCOSweepRx = new dlgVCOSweepTest(this);
        dlgVCOSweepRx->Initialize(lmsControl, true);
        dlgVCOSweepRx->Show();
    }
    else
        dlgVCOSweepRx->Show();
}

void pnlTesting::OnbtnVCOSweepTxClick(wxCommandEvent& event)
{
    if(dlgVCOSweepTx == NULL)
    {
        dlgVCOSweepTx = new dlgVCOSweepTest(this);
        dlgVCOSweepTx->Initialize(lmsControl, false);
        dlgVCOSweepTx->Show();
    }
    else
        dlgVCOSweepTx->Show();
}
