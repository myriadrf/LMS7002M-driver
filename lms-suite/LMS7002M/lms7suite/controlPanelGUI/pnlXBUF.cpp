/**
@file	pnlXBUF.cpp
@author	Lime Microsystems
@brief	XBUF module panel
*/

#include "pnlXBUF.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "LMS7002_MainControl.h"
//(*InternalHeaders(pnlXBUF)
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)
//(*IdInit(pnlXBUF)
const long pnlXBUF::ID_SLFB_XBUF_RX = wxNewId();
const long pnlXBUF::ID_SLFB_XBUF_TX = wxNewId();
const long pnlXBUF::ID_BYP_XBUF_RX = wxNewId();
const long pnlXBUF::ID_BYP_XBUF_TX = wxNewId();
const long pnlXBUF::ID_EN_OUT2_XBUF_TX = wxNewId();
const long pnlXBUF::ID_EN_TBUFIN_XBUF_RX = wxNewId();
const long pnlXBUF::ID_PD_XBUF_RX = wxNewId();
const long pnlXBUF::ID_PD_XBUF_TX = wxNewId();
const long pnlXBUF::ID_EN_G_XBUF = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlXBUF,wxPanel)
//(*EventTable(pnlXBUF)
//*)
END_EVENT_TABLE()

void pnlXBUF::AssignEnumsToIds()
{
    wndId2Enum[ID_BYP_XBUF_RX] = BYP_XBUF_RX;
    wndId2Enum[ID_BYP_XBUF_TX] = BYP_XBUF_TX;
    wndId2Enum[ID_EN_G_XBUF] = EN_G_XBUF;
    wndId2Enum[ID_EN_OUT2_XBUF_TX] = EN_OUT2_XBUF_TX;
    wndId2Enum[ID_EN_TBUFIN_XBUF_RX] = EN_TBUFIN_XBUF_RX;
    wndId2Enum[ID_PD_XBUF_RX] = PD_XBUF_RX;
    wndId2Enum[ID_PD_XBUF_TX] = PD_XBUF_TX;
    wndId2Enum[ID_SLFB_XBUF_RX] = SLFB_XBUF_RX;
    wndId2Enum[ID_SLFB_XBUF_TX] = SLFB_XBUF_TX;
}

pnlXBUF::pnlXBUF(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlXBUF::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlXBUF)
wxFlexGridSizer* Powerdowncontrols1Sizer;
wxFlexGridSizer* FlexGridSizer2;
wxStaticBoxSizer* PowerdowncontrolsSizer;
wxFlexGridSizer* FlexGridSizer1;

Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
chkSLFB_XBUF_RX = new wxCheckBox(this, ID_SLFB_XBUF_RX, _("Rx Enable biasing the input\'s DC voltage "), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLFB_XBUF_RX"));
chkSLFB_XBUF_RX->SetValue(false);
chkSLFB_XBUF_RX->SetToolTip(_("Self biasing digital contol SLFB_XBUF_RX"));
FlexGridSizer2->Add(chkSLFB_XBUF_RX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSLFB_XBUF_TX = new wxCheckBox(this, ID_SLFB_XBUF_TX, _("Tx Enable biasing the input\'s DC voltage "), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLFB_XBUF_TX"));
chkSLFB_XBUF_TX->SetValue(false);
chkSLFB_XBUF_TX->SetToolTip(_("Self biasing digital contol SLFB_XBUF_TX"));
FlexGridSizer2->Add(chkSLFB_XBUF_TX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_XBUF_RX = new wxCheckBox(this, ID_BYP_XBUF_RX, _("Shorts the Input 3.3V buffer in XBUF RX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_XBUF_RX"));
chkBYP_XBUF_RX->SetValue(false);
chkBYP_XBUF_RX->SetToolTip(_("Shorts the Input 3.3V buffer in XBUF"));
FlexGridSizer2->Add(chkBYP_XBUF_RX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_XBUF_TX = new wxCheckBox(this, ID_BYP_XBUF_TX, _("Shorts the Input 3.3V buffer in XBUF TX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_XBUF_TX"));
chkBYP_XBUF_TX->SetValue(false);
chkBYP_XBUF_TX->SetToolTip(_("Shorts the Input 3.3V buffer in XBUF"));
FlexGridSizer2->Add(chkBYP_XBUF_TX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_OUT2_XBUF_TX = new wxCheckBox(this, ID_EN_OUT2_XBUF_TX, _("EN_OUT2_XBUF_TX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_OUT2_XBUF_TX"));
chkEN_OUT2_XBUF_TX->SetValue(false);
chkEN_OUT2_XBUF_TX->SetToolTip(_("Enables the 2nd output of TX XBUF. This 2nd buffer goes to XBUF_RX. This should be active when only 1 XBUF is to be used"));
FlexGridSizer2->Add(chkEN_OUT2_XBUF_TX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_TBUFIN_XBUF_RX = new wxCheckBox(this, ID_EN_TBUFIN_XBUF_RX, _("EN_TBUFIN_XBUF_RX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_TBUFIN_XBUF_RX"));
chkEN_TBUFIN_XBUF_RX->SetValue(false);
chkEN_TBUFIN_XBUF_RX->SetToolTip(_("Disables the input from the external XOSC and buffers the 2nd input signal (from TX XBUF 2nd output) to the RX. This should be active when only 1 XBUF is to be used"));
FlexGridSizer2->Add(chkEN_TBUFIN_XBUF_RX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
PowerdowncontrolsSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Power down controls"));
Powerdowncontrols1Sizer = new wxFlexGridSizer(0, 1, 0, 0);
chkPD_XBUF_RX = new wxCheckBox(this, ID_PD_XBUF_RX, _("Power down Rx"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_XBUF_RX"));
chkPD_XBUF_RX->SetValue(false);
chkPD_XBUF_RX->SetToolTip(_("Power down signal PD_XBUF_RX"));
Powerdowncontrols1Sizer->Add(chkPD_XBUF_RX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_XBUF_TX = new wxCheckBox(this, ID_PD_XBUF_TX, _("Power down Tx"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_XBUF_TX"));
chkPD_XBUF_TX->SetValue(false);
chkPD_XBUF_TX->SetToolTip(_("Power down signal PD_XBUF_TX"));
Powerdowncontrols1Sizer->Add(chkPD_XBUF_TX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_G_XBUF = new wxCheckBox(this, ID_EN_G_XBUF, _("Enable XBUF module"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_G_XBUF"));
chkEN_G_XBUF->SetValue(false);
chkEN_G_XBUF->SetToolTip(_("Enable control for all the XBUF power downs"));
Powerdowncontrols1Sizer->Add(chkEN_G_XBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
PowerdowncontrolsSizer->Add(Powerdowncontrols1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(PowerdowncontrolsSizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_SLFB_XBUF_RX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlXBUF::ParameterChangeHandler);
Connect(ID_SLFB_XBUF_TX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlXBUF::ParameterChangeHandler);
Connect(ID_BYP_XBUF_RX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlXBUF::ParameterChangeHandler);
Connect(ID_BYP_XBUF_TX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlXBUF::ParameterChangeHandler);
Connect(ID_EN_OUT2_XBUF_TX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlXBUF::ParameterChangeHandler);
Connect(ID_EN_TBUFIN_XBUF_RX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlXBUF::ParameterChangeHandler);
Connect(ID_PD_XBUF_RX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlXBUF::ParameterChangeHandler);
Connect(ID_PD_XBUF_TX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlXBUF::ParameterChangeHandler);
Connect(ID_EN_G_XBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlXBUF::ParameterChangeHandler);
//*)
}
pnlXBUF::~pnlXBUF()
{
//(*Destroy(pnlXBUF)
//*)
}
void pnlXBUF::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlXBUF panel don't have control module assigned" << std::endl;
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

void pnlXBUF::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    wxArrayString temp;
    UpdateTooltips(this);
}

void pnlXBUF::UpdateGUI()
{
    long value = 0;
    value = lmsControl->GetParam(BYP_XBUF_RX);
    chkBYP_XBUF_RX->SetValue(value);

    value = lmsControl->GetParam(BYP_XBUF_TX);
    chkBYP_XBUF_TX->SetValue(value);

    value = lmsControl->GetParam(EN_G_XBUF);
    chkEN_G_XBUF->SetValue(value);

    value = lmsControl->GetParam(EN_OUT2_XBUF_TX);
    chkEN_OUT2_XBUF_TX->SetValue(value);

    value = lmsControl->GetParam(EN_TBUFIN_XBUF_RX);
    chkEN_TBUFIN_XBUF_RX->SetValue(value);

    value = lmsControl->GetParam(PD_XBUF_RX);
    chkPD_XBUF_RX->SetValue(value);

    value = lmsControl->GetParam(PD_XBUF_TX);
    chkPD_XBUF_TX->SetValue(value);

    value = lmsControl->GetParam(SLFB_XBUF_RX);
    chkSLFB_XBUF_RX->SetValue(value);

    value = lmsControl->GetParam(SLFB_XBUF_TX);
    chkSLFB_XBUF_TX->SetValue(value);
}
