/**
@file	pnlBIAS.cpp
@author	Lime Microsystems
@brief BIAS module panel
*/

#include "pnlBIAS.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "LMS7002_MainControl.h"
//(*InternalHeaders(pnlBIAS)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)
//(*IdInit(pnlBIAS)
const long pnlBIAS::ID_PD_FRP_BIAS = wxNewId();
const long pnlBIAS::ID_PD_F_BIAS = wxNewId();
const long pnlBIAS::ID_PD_PTRP_BIAS = wxNewId();
const long pnlBIAS::ID_PD_PT_BIAS = wxNewId();
const long pnlBIAS::ID_PD_BIAS_MASTER = wxNewId();
const long pnlBIAS::ID_STATICTEXT1 = wxNewId();
const long pnlBIAS::ID_MUX_BIAS_OUT = wxNewId();
const long pnlBIAS::ID_STATICTEXT2 = wxNewId();
const long pnlBIAS::ID_RP_CALIB_BIAS = wxNewId();
const long pnlBIAS::ID_BUTTON1 = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlBIAS,wxPanel)
//(*EventTable(pnlBIAS)
//*)
END_EVENT_TABLE()

void pnlBIAS::AssignEnumsToIds()
{
    wndId2Enum[ID_PD_BIAS_MASTER] = PD_BIAS_MASTER;
    //wndId2Enum[ID_EN_G_BIAS] = EN_G_BIAS;
    wndId2Enum[ID_MUX_BIAS_OUT] = MUX_BIAS_OUT;
    wndId2Enum[ID_PD_FRP_BIAS] = PD_FRP_BIAS;
    wndId2Enum[ID_PD_F_BIAS] = PD_F_BIAS;
    wndId2Enum[ID_PD_PTRP_BIAS] = PD_PTRP_BIAS;
    wndId2Enum[ID_PD_PT_BIAS] = PD_PT_BIAS;
    wndId2Enum[ID_RP_CALIB_BIAS] = RP_CALIB_BIAS;
}

pnlBIAS::pnlBIAS(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlBIAS::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlBIAS)
wxFlexGridSizer* Powerdowncontrols1Sizer;
wxFlexGridSizer* BIAS2Sizer;
wxStaticBoxSizer* PowerdowncontrolsSizer;
wxFlexGridSizer* FlexGridSizer1;
wxStaticBoxSizer* BIASSizer;

Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 5);
PowerdowncontrolsSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Power down controls"));
Powerdowncontrols1Sizer = new wxFlexGridSizer(0, 1, 0, 0);
chkPD_FRP_BIAS = new wxCheckBox(this, ID_PD_FRP_BIAS, _("Fix/RP block"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_FRP_BIAS"));
chkPD_FRP_BIAS->SetValue(false);
chkPD_FRP_BIAS->SetToolTip(_("Power down signal for Fix/RP block"));
Powerdowncontrols1Sizer->Add(chkPD_FRP_BIAS, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_F_BIAS = new wxCheckBox(this, ID_PD_F_BIAS, _("Fix"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_F_BIAS"));
chkPD_F_BIAS->SetValue(false);
chkPD_F_BIAS->SetToolTip(_("Power down signal for Fix"));
Powerdowncontrols1Sizer->Add(chkPD_F_BIAS, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_PTRP_BIAS = new wxCheckBox(this, ID_PD_PTRP_BIAS, _("PTAT/RP block"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_PTRP_BIAS"));
chkPD_PTRP_BIAS->SetValue(false);
chkPD_PTRP_BIAS->SetToolTip(_("Power down signal for PTAT/RP block"));
Powerdowncontrols1Sizer->Add(chkPD_PTRP_BIAS, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_PT_BIAS = new wxCheckBox(this, ID_PD_PT_BIAS, _("PTAT block"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_PT_BIAS"));
chkPD_PT_BIAS->SetValue(false);
chkPD_PT_BIAS->SetToolTip(_("Power down signal for PTAT block"));
Powerdowncontrols1Sizer->Add(chkPD_PT_BIAS, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_BIAS_MASTER = new wxCheckBox(this, ID_PD_BIAS_MASTER, _("Power down all block"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_BIAS_MASTER"));
chkPD_BIAS_MASTER->SetValue(false);
chkPD_BIAS_MASTER->SetToolTip(_("Enable signal for central bias block"));
Powerdowncontrols1Sizer->Add(chkPD_BIAS_MASTER, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
PowerdowncontrolsSizer->Add(Powerdowncontrols1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(PowerdowncontrolsSizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
BIASSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("BIAS"));
BIAS2Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText0 = new wxStaticText(this, ID_STATICTEXT1, _("BIAS_TOP test mode"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
BIAS2Sizer->Add(StaticText0, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbMUX_BIAS_OUT = new ComboBoxMap(this, ID_MUX_BIAS_OUT, wxEmptyString, wxDefaultPosition, wxSize(372,-1), 0, 0, 0, wxDefaultValidator, _T("ID_MUX_BIAS_OUT"));
cmbMUX_BIAS_OUT->SetToolTip(_("Test mode of the BIAS_TOP"));
BIAS2Sizer->Add(cmbMUX_BIAS_OUT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("RP_CALIB_BIAS"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
BIAS2Sizer->Add(StaticText1, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
cmbRP_CALIB_BIAS = new ComboBoxMap(this, ID_RP_CALIB_BIAS, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RP_CALIB_BIAS"));
cmbRP_CALIB_BIAS->SetToolTip(_("Calibration code for rppolywo. This code is set by the calibration algorithm: BIAS_RPPOLY_calibration"));
BIAS2Sizer->Add(cmbRP_CALIB_BIAS, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
btnCalibrate = new wxButton(this, ID_BUTTON1, _("Calibrate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
btnCalibrate->Hide();
BIAS2Sizer->Add(btnCalibrate, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
BIASSizer->Add(BIAS2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(BIASSizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_PD_FRP_BIAS,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBIAS::ParameterChangeHandler);
Connect(ID_PD_F_BIAS,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBIAS::ParameterChangeHandler);
Connect(ID_PD_PTRP_BIAS,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBIAS::ParameterChangeHandler);
Connect(ID_PD_PT_BIAS,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBIAS::ParameterChangeHandler);
Connect(ID_PD_BIAS_MASTER,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlBIAS::ParameterChangeHandler);
Connect(ID_MUX_BIAS_OUT,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlBIAS::ParameterChangeHandler);
Connect(ID_RP_CALIB_BIAS,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlBIAS::ParameterChangeHandler);
Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlBIAS::OnbtnCalibrateClick);
//*)
}
pnlBIAS::~pnlBIAS()
{
//(*Destroy(pnlBIAS)
//*)
}
void pnlBIAS::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlBIAS panel don't have control module assigned" << std::endl;
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

void pnlBIAS::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    char ctemp[80];
    vector<string> temp;
    temp.clear();
    temp.push_back("NO test mode");
    temp.push_back("vr_ext_bak and vr_cal_ref=600mV passed to ADC input MUX");
    temp.push_back("BIAS_TOP test outputs will be connected to ADC channel 1 input");
    temp.push_back("RSSI 1 output will be connected to ADC 1 input");
    cmbMUX_BIAS_OUT->Clear();
    cmbMUX_BIAS_OUT->Append(temp);
    cmbMUX_BIAS_OUT->SetSelection( lmsControl->GetParam(MUX_BIAS_OUT));

    temp.clear();
    for(int i=0; i<32; ++i)
    {
        sprintf(ctemp, "%i", i);
        temp.push_back( ctemp );
    }
    cmbRP_CALIB_BIAS->Clear();
    cmbRP_CALIB_BIAS->Append(temp);
    cmbRP_CALIB_BIAS->SetSelection( lmsControl->GetParam(RP_CALIB_BIAS));
    UpdateTooltips(this);
}

void pnlBIAS::UpdateGUI()
{
    //GetParent()->Freeze();
    long value = 0;
    value = lmsControl->GetParam(PD_BIAS_MASTER);
    chkPD_BIAS_MASTER->SetValue(value);

    value = lmsControl->GetParam(MUX_BIAS_OUT);
    cmbMUX_BIAS_OUT->SetSelection(value);

    value = lmsControl->GetParam(PD_FRP_BIAS);
    chkPD_FRP_BIAS->SetValue(value);

    value = lmsControl->GetParam(PD_F_BIAS);
    chkPD_F_BIAS->SetValue(value);

    value = lmsControl->GetParam(PD_PTRP_BIAS);
    chkPD_PTRP_BIAS->SetValue(value);

    value = lmsControl->GetParam(PD_PT_BIAS);
    chkPD_PT_BIAS->SetValue(value);

    value = lmsControl->GetParam(RP_CALIB_BIAS);
    cmbRP_CALIB_BIAS->SetSelection(value);

    //GetParent()->Thaw();
}


void pnlBIAS::OnbtnCalibrateClick(wxCommandEvent& event)
{
    lmsControl->algorithms->Resistor_calibration();
    UpdateGUI();
}
