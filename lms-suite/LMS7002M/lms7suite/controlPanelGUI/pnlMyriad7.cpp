/**
@file 	pnlMyriad7.cpp
@author Lime Microsystems
@brief	panel for controlling Myriad7 board GPIO
*/
#include "pnlMyriad7.h"

//(*InternalHeaders(pnlMyriad7)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)

//(*IdInit(pnlMyriad7)
const long pnlMyriad7::ID_STATICTEXT1 = wxNewId();
const long pnlMyriad7::ID_COMBOBOX1 = wxNewId();
const long pnlMyriad7::ID_STATICTEXT2 = wxNewId();
const long pnlMyriad7::ID_COMBOBOX2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlMyriad7,wxPanel)
	//(*EventTable(pnlMyriad7)
	//*)
END_EVENT_TABLE()

pnlMyriad7::pnlMyriad7(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    : PluginPanel(this)
{
	BuildContent(parent,id,pos,size);
}

void pnlMyriad7::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlMyriad7)
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("Rx (A/B) Input:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cmbGPIO_1_0 = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	cmbGPIO_1_0->SetSelection( cmbGPIO_1_0->Append(_T("No connection")) );
	cmbGPIO_1_0->Append(_T("LNAW"));
	cmbGPIO_1_0->Append(_T("LNAH"));
	cmbGPIO_1_0->Append(_T("LNAL"));
	FlexGridSizer2->Add(cmbGPIO_1_0, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("Tx (A/B) output:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	cmbGPIO2 = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	cmbGPIO2->SetSelection( cmbGPIO2->Append(_T("TX1")) );
	cmbGPIO2->Append(_T("TX2"));
	FlexGridSizer2->Add(cmbGPIO2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMyriad7::ParameterChangeHandler);
	Connect(ID_COMBOBOX2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlMyriad7::ParameterChangeHandler);
	//*)
}

pnlMyriad7::~pnlMyriad7()
{
	//(*Destroy(pnlMyriad7)
	//*)
}

void pnlMyriad7::Initialize(LMS7002_MainControl* pControl)
{
    lmsControl = pControl;
}

void pnlMyriad7::ParameterChangeHandler(wxCommandEvent& event)
{
    vector<unsigned char> gpios;
    unsigned rxInput = cmbGPIO_1_0->GetSelection();
    unsigned txOutput = cmbGPIO2->GetSelection();
    unsigned char value = txOutput << 2 | rxInput;
    gpios.push_back(value);
    if(lmsControl == NULL)
        return;
    if(lmsControl->SetGPIOStates(gpios) == false)
        wxMessageDialog(this, "Failed to set GPIO", "Error", wxICON_ERROR | wxOK);
}

void pnlMyriad7::UpdatePanel()
{
    vector<unsigned char> gpios;
    lmsControl->DownloadGPIOStates();
    lmsControl->GetGPIOStates(gpios);
    cmbGPIO_1_0->SetSelection(gpios[0] & 0x3);
    cmbGPIO2->SetSelection((gpios[0]&0x4) > 0);
}
