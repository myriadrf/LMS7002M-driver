/**
@file	pnlBIST.cpp
@author	Lime Microsystems
@brief 	BIST module panel
*/

#include "pnlBIST.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "LMS7002_MainControl.h"
//(*InternalHeaders(pnlBIST)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)
//(*IdInit(pnlBIST)
const long pnlBIST::ID_BENC = wxNewId();
const long pnlBIST::ID_BENT = wxNewId();
const long pnlBIST::ID_BENR = wxNewId();
const long pnlBIST::ID_BSTART = wxNewId();
const long pnlBIST::ID_STATICTEXT2 = wxNewId();
const long pnlBIST::ID_BSTATE = wxNewId();
const long pnlBIST::ID_STATICTEXT1 = wxNewId();
const long pnlBIST::ID_BSIGT = wxNewId();
const long pnlBIST::ID_STATICTEXT3 = wxNewId();
const long pnlBIST::ID_BSIGR = wxNewId();
const long pnlBIST::ID_STATICTEXT4 = wxNewId();
const long pnlBIST::ID_BSIGC = wxNewId();
const long pnlBIST::ID_BUTTON1 = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlBIST,wxPanel)
//(*EventTable(pnlBIST)
//*)
END_EVENT_TABLE()

void pnlBIST::AssignEnumsToIds()
{
    wndId2Enum[ID_BENC] = BENC;
    wndId2Enum[ID_BENR] = BENR;
    wndId2Enum[ID_BENT] = BENT;
    wndId2Enum[ID_BSTART] = BSTART;
}

pnlBIST::pnlBIST(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlBIST::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlBIST)
wxFlexGridSizer* BIST1Sizer;
wxFlexGridSizer* FlexGridSizer1;
wxStaticBoxSizer* BISTSizer;

Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
BISTSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("BIST"));
BIST1Sizer = new wxFlexGridSizer(0, 2, 2, 10);
chkBENC = new wxCheckBox(this, ID_BENC, _("Enable CGEN BIST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BENC"));
chkBENC->SetValue(false);
chkBENC->SetToolTip(_("enables CGEN BIST"));
BIST1Sizer->Add(chkBENC, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBENT = new wxCheckBox(this, ID_BENT, _("Enable transmitter BIST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BENT"));
chkBENT->SetValue(false);
chkBENT->SetToolTip(_("enables transmitter  BIST"));
BIST1Sizer->Add(chkBENT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBENR = new wxCheckBox(this, ID_BENR, _("Enable receiver BIST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BENR"));
chkBENR->SetValue(false);
chkBENR->SetToolTip(_("enables receiver BIST"));
BIST1Sizer->Add(chkBENR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBSTART = new wxCheckBox(this, ID_BSTART, _("Start delta sigma BIST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BSTART"));
chkBSTART->SetValue(false);
chkBSTART->SetToolTip(_("Starts delta sigma built in self test. Keep it at 1 one at least three clock cycles"));
BIST1Sizer->Add(chkBSTART, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("BIST state"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
BIST1Sizer->Add(StaticText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblBSTATE = new wxStaticText(this, ID_BSTATE, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BSTATE"));
BIST1Sizer->Add(lblBSTATE, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText0 = new wxStaticText(this, ID_STATICTEXT1, _("BIST signature (Transmitter)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
BIST1Sizer->Add(StaticText0, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblBSIGT = new wxStaticText(this, ID_BSIGT, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BSIGT"));
BIST1Sizer->Add(lblBSIGT, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("BIST signature (Receiver)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
BIST1Sizer->Add(StaticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblBSIGR = new wxStaticText(this, ID_BSIGR, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BSIGR"));
BIST1Sizer->Add(lblBSIGR, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("BIST signature (CGEN)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
BIST1Sizer->Add(StaticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblBSIGC = new wxStaticText(this, ID_BSIGC, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BSIGC"));
BIST1Sizer->Add(lblBSIGC, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnUpdateValues = new wxButton(this, ID_BUTTON1, _("Read BIST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
BIST1Sizer->Add(btnUpdateValues, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
BISTSizer->Add(BIST1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(BISTSizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_BENC,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBIST::ParameterChangeHandler);
Connect(ID_BENT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBIST::ParameterChangeHandler);
Connect(ID_BENR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBIST::ParameterChangeHandler);
Connect(ID_BSTART,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBIST::ParameterChangeHandler);
Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlBIST::OnbtnUpdateValuesClick);
//*)
}
pnlBIST::~pnlBIST()
{
//(*Destroy(pnlBIST)
//*)
}
void pnlBIST::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlBIST panel don't have control module assigned" << std::endl;
        return;
    }

    //LMS7002_Parameter parameter;
    /*try
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
    }*/
    //always send BIST controls as seen in GUI
    unsigned short regValue = 0;
    regValue |= (lmsControl->GetParam(EN_SDM_TSTO_SXT, false)) << 6;
    regValue |= (lmsControl->GetParam(EN_SDM_TSTO_SXR, false)) << 5;
    regValue |= (lmsControl->GetParam(EN_SDM_TSTO_CGEN, false)) << 4;
    regValue |= chkBENC->GetValue() << 3;
    regValue |= chkBENR->GetValue() << 2;
    regValue |= chkBENT->GetValue() << 1;
    regValue |= chkBSTART->GetValue();
    lmsControl->getRegistersMap()->SetRegisterValue(0x00A8, regValue);
}

void pnlBIST::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    UpdateTooltips(this);
}

void pnlBIST::UpdateGUI()
{
    //GetParent()->Freeze();
    long value = 0;
    value = lmsControl->GetParam(BENC);
    chkBENC->SetValue(value);

    value = lmsControl->GetParam(BENR);
    chkBENR->SetValue(value);

    value = lmsControl->GetParam(BENT);
    chkBENT->SetValue(value);

    value = lmsControl->GetParam(BSTART);
    chkBSTART->SetValue(value);

    //UpdateReadOnlyValues();
    //GetParent()->Thaw();
}

void pnlBIST::UpdateReadOnlyValues()
{
    int value;
    value = lmsControl->GetParam(BSIGC, true, false);
    lblBSIGC->SetLabel(wxString::Format("0x%0.6X", value));
    value = lmsControl->GetParam(BSIGR, true, false);
    lblBSIGR->SetLabel(wxString::Format("0x%0.6X", value));
    value = lmsControl->GetParam(BSIGT, true, false);
    lblBSIGT->SetLabel(wxString::Format("0x%0.6X", value));
    value = lmsControl->GetParam(BSTATE, true, false);
    lblBSTATE->SetLabel(wxString::Format("0x%X", value));
}


void pnlBIST::OnbtnUpdateValuesClick(wxCommandEvent& event)
{
    UpdateReadOnlyValues();
}
