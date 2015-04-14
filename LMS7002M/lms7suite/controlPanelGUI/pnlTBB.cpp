/**
@file	pnlTBB.cpp
@author	Lime Microsystems
@brief	TBB module panel
*/

#include "pnlTBB.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "LMS7002_MainControl.h"
//(*InternalHeaders(pnlTBB)
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/stattext.h>
//*)
//(*IdInit(pnlTBB)
const long pnlTBB::ID_STATICTEXT1 = wxNewId();
const long pnlTBB::ID_LOOPB_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT2 = wxNewId();
const long pnlTBB::ID_CG_IAMP_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT3 = wxNewId();
const long pnlTBB::ID_ICT_IAMP_FRP_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT4 = wxNewId();
const long pnlTBB::ID_ICT_IAMP_GG_FRP_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT5 = wxNewId();
const long pnlTBB::ID_TSTIN_TBB = wxNewId();
const long pnlTBB::ID_BYPLADDER_TBB = wxNewId();
const long pnlTBB::ID_PD_LPFH_TBB = wxNewId();
const long pnlTBB::ID_PD_LPFIAMP_TBB = wxNewId();
const long pnlTBB::ID_PD_LPFLAD_TBB = wxNewId();
const long pnlTBB::ID_PD_LPFS5_TBB = wxNewId();
const long pnlTBB::ID_EN_G_TBB = wxNewId();
const long pnlTBB::ID_EN_DIR_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT6 = wxNewId();
const long pnlTBB::ID_ICT_LPFS5_F_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT7 = wxNewId();
const long pnlTBB::ID_ICT_LPFS5_PT_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT8 = wxNewId();
const long pnlTBB::ID_ICT_LPF_H_PT_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT9 = wxNewId();
const long pnlTBB::ID_ICT_LPFH_F_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT10 = wxNewId();
const long pnlTBB::ID_ICT_LPFLAD_F_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT11 = wxNewId();
const long pnlTBB::ID_ICT_LPFLAD_PT_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT12 = wxNewId();
const long pnlTBB::ID_RCAL_LPFH_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT13 = wxNewId();
const long pnlTBB::ID_RCAL_LPFLAD_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT14 = wxNewId();
const long pnlTBB::ID_CCAL_LPFLAD_TBB = wxNewId();
const long pnlTBB::ID_STATICTEXT15 = wxNewId();
const long pnlTBB::ID_RCAL_LPFS5_TBB = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlTBB,wxPanel)
//(*EventTable(pnlTBB)
//*)
END_EVENT_TABLE()

void pnlTBB::AssignEnumsToIds()
{
    wndId2Enum[ID_BYPLADDER_TBB] = BYPLADDER_TBB;
    wndId2Enum[ID_CCAL_LPFLAD_TBB] = CCAL_LPFLAD_TBB;
    wndId2Enum[ID_CG_IAMP_TBB] = CG_IAMP_TBB;
    wndId2Enum[ID_EN_G_TBB] = EN_G_TBB;
    wndId2Enum[ID_ICT_IAMP_FRP_TBB] = ICT_IAMP_FRP_TBB;
    wndId2Enum[ID_ICT_IAMP_GG_FRP_TBB] = ICT_IAMP_GG_FRP_TBB;
    wndId2Enum[ID_ICT_LPFH_F_TBB] = ICT_LPFH_F_TBB;
    wndId2Enum[ID_ICT_LPFLAD_F_TBB] = ICT_LPFLAD_F_TBB;
    wndId2Enum[ID_ICT_LPFLAD_PT_TBB] = ICT_LPFLAD_PT_TBB;
    wndId2Enum[ID_ICT_LPFS5_F_TBB] = ICT_LPFS5_F_TBB;
    wndId2Enum[ID_ICT_LPFS5_PT_TBB] = ICT_LPFS5_PT_TBB;
    wndId2Enum[ID_ICT_LPF_H_PT_TBB] = ICT_LPF_H_PT_TBB;
    wndId2Enum[ID_LOOPB_TBB] = LOOPB_TBB;
    wndId2Enum[ID_PD_LPFH_TBB] = PD_LPFH_TBB;
    wndId2Enum[ID_PD_LPFIAMP_TBB] = PD_LPFIAMP_TBB;
    wndId2Enum[ID_PD_LPFLAD_TBB] = PD_LPFLAD_TBB;
    wndId2Enum[ID_PD_LPFS5_TBB] = PD_LPFS5_TBB;
    wndId2Enum[ID_RCAL_LPFH_TBB] = RCAL_LPFH_TBB;
    wndId2Enum[ID_RCAL_LPFLAD_TBB] = RCAL_LPFLAD_TBB;
    wndId2Enum[ID_RCAL_LPFS5_TBB] = RCAL_LPFS5_TBB;
    wndId2Enum[ID_TSTIN_TBB] = TSTIN_TBB;
    wndId2Enum[ID_EN_DIR_TBB] = EN_DIR_TBB;
}

pnlTBB::pnlTBB(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlTBB::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlTBB)
wxStaticBoxSizer* StaticBoxSizer2;
wxFlexGridSizer* FlexGridSizer1;
wxFlexGridSizer* UNGROUPED1Sizer;
wxStaticBoxSizer* UNGROUPEDSizer;
wxFlexGridSizer* Powerdowncontrols2Sizer;
wxStaticBoxSizer* ResistorbanksSizer;
wxStaticBoxSizer* PowerdowncontrolsSizer;
wxFlexGridSizer* Operationalamplifier3Sizer;
wxStaticBoxSizer* OperationalamplifierSizer;
wxFlexGridSizer* Resistorbanks4Sizer;

Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 5);
UNGROUPEDSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("UNGROUPED"));
UNGROUPED1Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText0 = new wxStaticText(this, ID_STATICTEXT1, _("Tx BB loopback"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
UNGROUPED1Sizer->Add(StaticText0, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLOOPB_TBB = new ComboBoxMap(this, ID_LOOPB_TBB, wxEmptyString, wxDefaultPosition, wxSize(197,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LOOPB_TBB"));
cmbLOOPB_TBB->SetToolTip(_("This controls which signal is connected to the loopback output pins. Note: when both the lowpass ladder and real pole are powered down, the output of the active highband biquad is routed to the loopb output"));
UNGROUPED1Sizer->Add(cmbLOOPB_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("Frontend gain"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
UNGROUPED1Sizer->Add(StaticText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCG_IAMP_TBB = new ComboBoxMap(this, ID_CG_IAMP_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CG_IAMP_TBB"));
cmbCG_IAMP_TBB->SetToolTip(_("This controls the frontend gain of the TBB. For a given gain value, this control value varies with the set TX mode. After resistance calibration, the following table gives the nominal values for each frequency setting. However, this table is to be updated and corrected after calibration"));
UNGROUPED1Sizer->Add(cmbCG_IAMP_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("Reference bias current of IAMP main bias current sources"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
UNGROUPED1Sizer->Add(StaticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_IAMP_FRP_TBB = new ComboBoxMap(this, ID_ICT_IAMP_FRP_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_IAMP_FRP_TBB"));
cmbICT_IAMP_FRP_TBB->SetToolTip(_("This controls the reference bias current of the IAMP main bias current sources"));
UNGROUPED1Sizer->Add(cmbICT_IAMP_FRP_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Reference bias current of IAMP cascade transistors gate voltage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
UNGROUPED1Sizer->Add(StaticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_IAMP_GG_FRP_TBB = new ComboBoxMap(this, ID_ICT_IAMP_GG_FRP_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_IAMP_GG_FRP_TBB"));
cmbICT_IAMP_GG_FRP_TBB->SetToolTip(_("This controls the reference bias current of the IAMP\'s cascode transistors gate voltages that set the IAMP\'s input voltage level. The IAMP\'s input is connected to the DAC output"));
UNGROUPED1Sizer->Add(cmbICT_IAMP_GG_FRP_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("Enable Tx IQ analog input"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
UNGROUPED1Sizer->Add(StaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbTSTIN_TBB = new ComboBoxMap(this, ID_TSTIN_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_TSTIN_TBB"));
cmbTSTIN_TBB->SetToolTip(_("This control selects where the input test signal (vinp/n_aux_bbq/i) is routed to as well as disabling the route."));
UNGROUPED1Sizer->Add(cmbTSTIN_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYPLADDER_TBB = new wxCheckBox(this, ID_BYPLADDER_TBB, _("Bypass LPF ladder of TBB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYPLADDER_TBB"));
chkBYPLADDER_TBB->SetValue(false);
chkBYPLADDER_TBB->SetToolTip(_("This signal bypasses the LPF ladder of TBB and directly connects the output of current amplifier to the null port of the real pole stage of TBB low pass filter"));
UNGROUPED1Sizer->Add(chkBYPLADDER_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
UNGROUPEDSizer->Add(UNGROUPED1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(UNGROUPEDSizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
PowerdowncontrolsSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Power down controls"));
Powerdowncontrols2Sizer = new wxFlexGridSizer(0, 1, 0, 0);
chkPD_LPFH_TBB = new wxCheckBox(this, ID_PD_LPFH_TBB, _("LPFH_TBB biquad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_LPFH_TBB"));
chkPD_LPFH_TBB->SetValue(false);
chkPD_LPFH_TBB->SetToolTip(_("This selectively powers down the LPFH_TBB biquad"));
Powerdowncontrols2Sizer->Add(chkPD_LPFH_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_LPFIAMP_TBB = new wxCheckBox(this, ID_PD_LPFIAMP_TBB, _("LPFIAMP_TBB front-end current amp"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_LPFIAMP_TBB"));
chkPD_LPFIAMP_TBB->SetValue(false);
chkPD_LPFIAMP_TBB->SetToolTip(_("selectively powers down the LPFIAMP_TBB front-end current amp of the transmitter baseband"));
Powerdowncontrols2Sizer->Add(chkPD_LPFIAMP_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_LPFLAD_TBB = new wxCheckBox(this, ID_PD_LPFLAD_TBB, _("LPFLAD_TBB low pass ladder filter"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_LPFLAD_TBB"));
chkPD_LPFLAD_TBB->SetValue(false);
chkPD_LPFLAD_TBB->SetToolTip(_("This selectively powers down the LPFLAD_TBB low pass ladder filter of the transmitter baseband"));
Powerdowncontrols2Sizer->Add(chkPD_LPFLAD_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_LPFS5_TBB = new wxCheckBox(this, ID_PD_LPFS5_TBB, _("LPFS5_TBB low pass real-pole filter"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_LPFS5_TBB"));
chkPD_LPFS5_TBB->SetValue(false);
chkPD_LPFS5_TBB->SetToolTip(_("This selectively powers down the LPFS5_TBB low pass real-pole filter of the transmitter baseband"));
Powerdowncontrols2Sizer->Add(chkPD_LPFS5_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_G_TBB = new wxCheckBox(this, ID_EN_G_TBB, _("Enable TBB module"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_G_TBB"));
chkEN_G_TBB->SetValue(false);
chkEN_G_TBB->SetToolTip(_("Enable control for all the TBB_TOP power downs"));
Powerdowncontrols2Sizer->Add(chkEN_G_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Direct control"));
chkEN_DIR_TBB = new wxCheckBox(this, ID_EN_DIR_TBB, _("Enable direct control of PDs and ENs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_DIR_TBB"));
chkEN_DIR_TBB->SetValue(false);
chkEN_DIR_TBB->SetToolTip(_("Enables direct control of PDs and ENs for TBB module"));
StaticBoxSizer2->Add(chkEN_DIR_TBB, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
Powerdowncontrols2Sizer->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
PowerdowncontrolsSizer->Add(Powerdowncontrols2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(PowerdowncontrolsSizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
OperationalamplifierSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Operational amplifier"));
Operationalamplifier3Sizer = new wxFlexGridSizer(0, 2, 0, 5);
Operationalamplifier3Sizer->AddGrowableCol(1);
StaticText5 = new wxStaticText(this, ID_STATICTEXT6, _("Output stage bias current low band real pole filter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
Operationalamplifier3Sizer->Add(StaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_LPFS5_F_TBB = new ComboBoxMap(this, ID_ICT_LPFS5_F_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_LPFS5_F_TBB"));
cmbICT_LPFS5_F_TBB->SetToolTip(_("This controls the operational amplifier\'s output stage bias current of the low band real pole filter of the transmitter\'s baseband"));
Operationalamplifier3Sizer->Add(cmbICT_LPFS5_F_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText6 = new wxStaticText(this, ID_STATICTEXT7, _("Input stage bias current of low band real pole filter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
Operationalamplifier3Sizer->Add(StaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_LPFS5_PT_TBB = new ComboBoxMap(this, ID_ICT_LPFS5_PT_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_LPFS5_PT_TBB"));
cmbICT_LPFS5_PT_TBB->SetToolTip(_("This controls the operational amplifier\'s input stage bias current of the low band real pole filter of the transmitter\'s baseband"));
Operationalamplifier3Sizer->Add(cmbICT_LPFS5_PT_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText7 = new wxStaticText(this, ID_STATICTEXT8, _("Input stage bias reference current of high band low pass filter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
Operationalamplifier3Sizer->Add(StaticText7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_LPF_H_PT_TBB = new ComboBoxMap(this, ID_ICT_LPF_H_PT_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_LPF_H_PT_TBB"));
cmbICT_LPF_H_PT_TBB->SetToolTip(_("This controls the operational amplifiers input stage bias reference current of the high band low pass filter of the transmitter\'s baseband "));
Operationalamplifier3Sizer->Add(cmbICT_LPF_H_PT_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText8 = new wxStaticText(this, ID_STATICTEXT9, _("Output stage bias reference current of high band low pass filter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
Operationalamplifier3Sizer->Add(StaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_LPFH_F_TBB = new ComboBoxMap(this, ID_ICT_LPFH_F_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_LPFH_F_TBB"));
cmbICT_LPFH_F_TBB->SetToolTip(_("controls the operational amplifiers output stage bias reference current of the high band low pass filter of the transmitter\'s baseband (LPFH_TBB)"));
Operationalamplifier3Sizer->Add(cmbICT_LPFH_F_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText9 = new wxStaticText(this, ID_STATICTEXT10, _("Output stage bias reference of low band ladder filter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
Operationalamplifier3Sizer->Add(StaticText9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_LPFLAD_F_TBB = new ComboBoxMap(this, ID_ICT_LPFLAD_F_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_LPFLAD_F_TBB"));
cmbICT_LPFLAD_F_TBB->SetToolTip(_("This controls the operational amplfiers\' output stages bias referene current of the low band ladder filter of the transmisster\'s baseband"));
Operationalamplifier3Sizer->Add(cmbICT_LPFLAD_F_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText10 = new wxStaticText(this, ID_STATICTEXT11, _("Input stage bias reference of low band ladder filter"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
Operationalamplifier3Sizer->Add(StaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_LPFLAD_PT_TBB = new ComboBoxMap(this, ID_ICT_LPFLAD_PT_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_LPFLAD_PT_TBB"));
cmbICT_LPFLAD_PT_TBB->SetToolTip(_("This controls the operational amplifers\' input stages bias reference current of the low band ladder filter of the transmitter\'s baseband"));
Operationalamplifier3Sizer->Add(cmbICT_LPFLAD_PT_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
OperationalamplifierSizer->Add(Operationalamplifier3Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(OperationalamplifierSizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
ResistorbanksSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("TxLPF resistor banks"));
Resistorbanks4Sizer = new wxFlexGridSizer(0, 2, 0, 0);
StaticText11 = new wxStaticText(this, ID_STATICTEXT12, _("LPFH equivalent resistance stage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
Resistorbanks4Sizer->Add(StaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRCAL_LPFH_TBB = new ComboBoxMap(this, ID_RCAL_LPFH_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RCAL_LPFH_TBB"));
cmbRCAL_LPFH_TBB->SetToolTip(_("This controls the value of the equivalent resistance of the resistor banks of the biquad filter stage (of the high band section) of the transmitter baseband(TBB)"));
Resistorbanks4Sizer->Add(cmbRCAL_LPFH_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText12 = new wxStaticText(this, ID_STATICTEXT13, _("LPFLAD equivalent resistance stage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
Resistorbanks4Sizer->Add(StaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRCAL_LPFLAD_TBB = new ComboBoxMap(this, ID_RCAL_LPFLAD_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RCAL_LPFLAD_TBB"));
cmbRCAL_LPFLAD_TBB->SetToolTip(_("This controls the value of the equivalent resistance of the resistor banks of the low pass filter ladder (of the low band section) of the transmitter baseband(TBB)"));
Resistorbanks4Sizer->Add(cmbRCAL_LPFLAD_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText13 = new wxStaticText(this, ID_STATICTEXT14, _("Common control signal for all TBB filters"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
Resistorbanks4Sizer->Add(StaticText13, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCCAL_LPFLAD_TBB = new ComboBoxMap(this, ID_CCAL_LPFLAD_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CCAL_LPFLAD_TBB"));
cmbCCAL_LPFLAD_TBB->SetToolTip(_("A common control signal for all the capacitor banks of TBB filters (including the ladder, real pole, and the high band biquad). It is the calibrated value of the banks control that sets the value of the banks\' equivalent capacitor to their respective nominal values"));
Resistorbanks4Sizer->Add(cmbCCAL_LPFLAD_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText14 = new wxStaticText(this, ID_STATICTEXT15, _("LPFS5 equivalent resistance stage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
Resistorbanks4Sizer->Add(StaticText14, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRCAL_LPFS5_TBB = new ComboBoxMap(this, ID_RCAL_LPFS5_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RCAL_LPFS5_TBB"));
cmbRCAL_LPFS5_TBB->SetToolTip(_("This controls the value of the equivalent resistance of the resistor banks of the real pole filter stage (of the low band section) of the transmitter baseband (TBB). Following is a nominal values table that are corrected for any process variation after calibration"));
Resistorbanks4Sizer->Add(cmbRCAL_LPFS5_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
ResistorbanksSizer->Add(Resistorbanks4Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(ResistorbanksSizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_LOOPB_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_CG_IAMP_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_ICT_IAMP_FRP_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_ICT_IAMP_GG_FRP_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_TSTIN_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_BYPLADDER_TBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_PD_LPFH_TBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_PD_LPFIAMP_TBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_PD_LPFLAD_TBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_PD_LPFS5_TBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_EN_G_TBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_EN_DIR_TBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_ICT_LPFS5_F_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_ICT_LPFS5_PT_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_ICT_LPF_H_PT_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_ICT_LPFH_F_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_ICT_LPFLAD_F_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_ICT_LPFLAD_PT_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_RCAL_LPFH_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_RCAL_LPFLAD_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_CCAL_LPFLAD_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
Connect(ID_RCAL_LPFS5_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTBB::ParameterChangeHandler);
//*)
}
pnlTBB::~pnlTBB()
{
//(*Destroy(pnlTBB)
//*)
}
void pnlTBB::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlTBB panel don't have control module assigned" << std::endl;
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

void pnlTBB::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    char ctemp[80];
    vector<string> temp;
    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbCCAL_LPFLAD_TBB->Clear();
    cmbCCAL_LPFLAD_TBB->Append(temp);
    cmbCCAL_LPFLAD_TBB->SetSelection( lmsControl->GetParam(CCAL_LPFLAD_TBB));

    temp.clear();
    for(int i=0; i<64; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbCG_IAMP_TBB->Clear();
    cmbCG_IAMP_TBB->Append(temp);
    cmbCG_IAMP_TBB->SetSelection( lmsControl->GetParam(CG_IAMP_TBB));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_IAMP_FRP_TBB->Clear();
    cmbICT_IAMP_FRP_TBB->Append(temp);
    cmbICT_IAMP_FRP_TBB->SetSelection( lmsControl->GetParam(ICT_IAMP_FRP_TBB));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_IAMP_GG_FRP_TBB->Clear();
    cmbICT_IAMP_GG_FRP_TBB->Append(temp);
    cmbICT_IAMP_GG_FRP_TBB->SetSelection( lmsControl->GetParam(ICT_IAMP_GG_FRP_TBB));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_LPFH_F_TBB->Clear();
    cmbICT_LPFH_F_TBB->Append(temp);
    cmbICT_LPFH_F_TBB->SetSelection( lmsControl->GetParam(ICT_LPFH_F_TBB));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_LPFLAD_F_TBB->Clear();
    cmbICT_LPFLAD_F_TBB->Append(temp);
    cmbICT_LPFLAD_F_TBB->SetSelection( lmsControl->GetParam(ICT_LPFLAD_F_TBB));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_LPFLAD_PT_TBB->Clear();
    cmbICT_LPFLAD_PT_TBB->Append(temp);
    cmbICT_LPFLAD_PT_TBB->SetSelection( lmsControl->GetParam(ICT_LPFLAD_PT_TBB));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_LPFS5_F_TBB->Clear();
    cmbICT_LPFS5_F_TBB->Append(temp);
    cmbICT_LPFS5_F_TBB->SetSelection( lmsControl->GetParam(ICT_LPFS5_F_TBB));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_LPFS5_PT_TBB->Clear();
    cmbICT_LPFS5_PT_TBB->Append(temp);
    cmbICT_LPFS5_PT_TBB->SetSelection( lmsControl->GetParam(ICT_LPFS5_PT_TBB));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_LPF_H_PT_TBB->Clear();
    cmbICT_LPF_H_PT_TBB->Append(temp);
    cmbICT_LPF_H_PT_TBB->SetSelection( lmsControl->GetParam(ICT_LPF_H_PT_TBB));

    vector<cmbKeyValuePair> keyvalues;
    keyvalues.push_back(cmbKeyValuePair(0,"Disabled"));
    keyvalues.push_back(cmbKeyValuePair(1,"DAC current output"));
    keyvalues.push_back(cmbKeyValuePair(2,"LPFLAD ladder output"));
    keyvalues.push_back(cmbKeyValuePair(3,"TBB output"));
    keyvalues.push_back(cmbKeyValuePair(5,"DAC current output (IQ swap)"));
    keyvalues.push_back(cmbKeyValuePair(6,"LPFLAD ladder output (IQ swap)"));
    keyvalues.push_back(cmbKeyValuePair(7,"TBB output (IQ swap)"));
    cmbLOOPB_TBB->Clear();
    cmbLOOPB_TBB->Set(keyvalues);
    cmbLOOPB_TBB->SetSelection( lmsControl->GetParam(LOOPB_TBB));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbRCAL_LPFH_TBB->Clear();
    cmbRCAL_LPFH_TBB->Append(temp);
    cmbRCAL_LPFH_TBB->SetSelection( lmsControl->GetParam(RCAL_LPFH_TBB));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbRCAL_LPFLAD_TBB->Clear();
    cmbRCAL_LPFLAD_TBB->Append(temp);
    cmbRCAL_LPFLAD_TBB->SetSelection( lmsControl->GetParam(RCAL_LPFLAD_TBB));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbRCAL_LPFS5_TBB->Clear();
    cmbRCAL_LPFS5_TBB->Append(temp);
    cmbRCAL_LPFS5_TBB->SetSelection( lmsControl->GetParam(RCAL_LPFS5_TBB));

    temp.clear();
    temp.push_back("Disabled");
    temp.push_back("to Highband filter");
    temp.push_back("to Lowband filter");
    temp.push_back("to current amplifier");
    cmbTSTIN_TBB->Clear();
    cmbTSTIN_TBB->Append(temp);
    cmbTSTIN_TBB->SetSelection( lmsControl->GetParam(TSTIN_TBB));
    UpdateTooltips(this);
}

void pnlTBB::UpdateGUI()
{
    long value = 0;
    value = lmsControl->GetParam(BYPLADDER_TBB);
    chkBYPLADDER_TBB->SetValue(value);

    value = lmsControl->GetParam(CCAL_LPFLAD_TBB);
    cmbCCAL_LPFLAD_TBB->SetSelection(value);

    value = lmsControl->GetParam(CG_IAMP_TBB);
    cmbCG_IAMP_TBB->SetSelection(value);

    value = lmsControl->GetParam(EN_G_TBB);
    chkEN_G_TBB->SetValue(value);

    value = lmsControl->GetParam(ICT_IAMP_FRP_TBB);
    cmbICT_IAMP_FRP_TBB->SetSelection(value);

    value = lmsControl->GetParam(ICT_IAMP_GG_FRP_TBB);
    cmbICT_IAMP_GG_FRP_TBB->SetSelection(value);

    value = lmsControl->GetParam(ICT_LPFH_F_TBB);
    cmbICT_LPFH_F_TBB->SetSelection(value);

    value = lmsControl->GetParam(ICT_LPFLAD_F_TBB);
    cmbICT_LPFLAD_F_TBB->SetSelection(value);

    value = lmsControl->GetParam(ICT_LPFLAD_PT_TBB);
    cmbICT_LPFLAD_PT_TBB->SetSelection(value);

    value = lmsControl->GetParam(ICT_LPFS5_F_TBB);
    cmbICT_LPFS5_F_TBB->SetSelection(value);

    value = lmsControl->GetParam(ICT_LPFS5_PT_TBB);
    cmbICT_LPFS5_PT_TBB->SetSelection(value);

    value = lmsControl->GetParam(ICT_LPF_H_PT_TBB);
    cmbICT_LPF_H_PT_TBB->SetSelection(value);

    value = lmsControl->GetParam(LOOPB_TBB);
    cmbLOOPB_TBB->SetSelection(value);

    value = lmsControl->GetParam(PD_LPFH_TBB);
    chkPD_LPFH_TBB->SetValue(value);

    value = lmsControl->GetParam(PD_LPFIAMP_TBB);
    chkPD_LPFIAMP_TBB->SetValue(value);

    value = lmsControl->GetParam(PD_LPFLAD_TBB);
    chkPD_LPFLAD_TBB->SetValue(value);

    value = lmsControl->GetParam(PD_LPFS5_TBB);
    chkPD_LPFS5_TBB->SetValue(value);

    value = lmsControl->GetParam(RCAL_LPFH_TBB);
    cmbRCAL_LPFH_TBB->SetSelection(value);

    value = lmsControl->GetParam(RCAL_LPFLAD_TBB);
    cmbRCAL_LPFLAD_TBB->SetSelection(value);

    value = lmsControl->GetParam(RCAL_LPFS5_TBB);
    cmbRCAL_LPFS5_TBB->SetSelection(value);

    value = lmsControl->GetParam(TSTIN_TBB);
    cmbTSTIN_TBB->SetSelection(value);
}


void pnlTBB::OnbtnCalibrateLowBandClick(wxCommandEvent& event)
{
    lmsControl->algorithms->Calibration_LowBand_TBB(lmsControl->GetConfigChannel());
}

void pnlTBB::OnbtnCalibrateHighBandClick(wxCommandEvent& event)
{
    lmsControl->algorithms->Calibration_HighBand_TBB(lmsControl->GetConfigChannel());
}
