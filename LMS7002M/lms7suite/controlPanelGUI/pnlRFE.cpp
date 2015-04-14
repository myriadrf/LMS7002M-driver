/**
@file	pnlRFE.cpp
@author	Lime Microsystems
@brief	RFE module panel
*/

#include "pnlRFE.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "LMS7002_MainControl.h"
#include "../CommonUtilities.h"
//(*InternalHeaders(pnlRFE)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)
//(*IdInit(pnlRFE)
const long pnlRFE::ID_PD_LNA_RFE = wxNewId();
const long pnlRFE::ID_PD_RLOOPB_1_RFE = wxNewId();
const long pnlRFE::ID_PD_RLOOPB_2_RFE = wxNewId();
const long pnlRFE::ID_PD_MXLOBUF_RFE = wxNewId();
const long pnlRFE::ID_PD_QGEN_RFE = wxNewId();
const long pnlRFE::ID_PD_RSSI_RFE = wxNewId();
const long pnlRFE::ID_PD_TIA_RFE = wxNewId();
const long pnlRFE::ID_EN_G_RFE = wxNewId();
const long pnlRFE::ID_EN_DIR_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT1 = wxNewId();
const long pnlRFE::ID_SEL_PATH_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT2 = wxNewId();
const long pnlRFE::ID_CAP_RXMXO_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT3 = wxNewId();
const long pnlRFE::ID_CGSIN_LNA_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT4 = wxNewId();
const long pnlRFE::ID_RCOMP_TIA_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT5 = wxNewId();
const long pnlRFE::ID_RFB_TIA_RFE = wxNewId();
const long pnlRFE::ID_EN_NEXTRX_RFE = wxNewId();
const long pnlRFE::ID_EN_INSHSW_LB1_RFE = wxNewId();
const long pnlRFE::ID_EN_INSHSW_LB2_RFE = wxNewId();
const long pnlRFE::ID_EN_INSHSW_L_RFE = wxNewId();
const long pnlRFE::ID_EN_INSHSW_W_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT6 = wxNewId();
const long pnlRFE::ID_DCOFFI_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT7 = wxNewId();
const long pnlRFE::ID_DCOFFQ_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT8 = wxNewId();
const long pnlRFE::ID_ICT_LODC_RFE = wxNewId();
const long pnlRFE::ID_EN_DCOFF_RXFE_RFE = wxNewId();
const long pnlRFE::ID_BUTTON2 = wxNewId();
const long pnlRFE::ID_STATICTEXT9 = wxNewId();
const long pnlRFE::ID_ICT_LOOPB_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT10 = wxNewId();
const long pnlRFE::ID_ICT_TIAMAIN_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT11 = wxNewId();
const long pnlRFE::ID_ICT_TIAOUT_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT12 = wxNewId();
const long pnlRFE::ID_ICT_LNACMO_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT13 = wxNewId();
const long pnlRFE::ID_ICT_LNA_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT14 = wxNewId();
const long pnlRFE::ID_CCOMP_TIA_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT15 = wxNewId();
const long pnlRFE::ID_CFB_TIA_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT16 = wxNewId();
const long pnlRFE::ID_G_LNA_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT17 = wxNewId();
const long pnlRFE::ID_G_RXLOOPB_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT18 = wxNewId();
const long pnlRFE::ID_G_TIA_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT19 = wxNewId();
const long pnlRFE::ID_CDC_I_RFE = wxNewId();
const long pnlRFE::ID_STATICTEXT20 = wxNewId();
const long pnlRFE::ID_CDC_Q_RFE = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlRFE,wxPanel)
//(*EventTable(pnlRFE)
//*)
END_EVENT_TABLE()

void pnlRFE::AssignEnumsToIds()
{
    wndId2Enum[ID_CAP_RXMXO_RFE] = CAP_RXMXO_RFE;
    wndId2Enum[ID_CCOMP_TIA_RFE] = CCOMP_TIA_RFE;
    wndId2Enum[ID_CFB_TIA_RFE] = CFB_TIA_RFE;
    wndId2Enum[ID_CGSIN_LNA_RFE] = CGSIN_LNA_RFE;
    wndId2Enum[ID_DCOFFI_RFE] = DCOFFI_RFE;
    wndId2Enum[ID_DCOFFQ_RFE] = DCOFFQ_RFE;
    wndId2Enum[ID_EN_DCOFF_RXFE_RFE] = EN_DCOFF_RXFE_RFE;
    wndId2Enum[ID_EN_G_RFE] = EN_G_RFE;
    wndId2Enum[ID_EN_INSHSW_LB1_RFE] = EN_INSHSW_LB1_RFE;
    wndId2Enum[ID_EN_INSHSW_LB2_RFE] = EN_INSHSW_LB2_RFE;
    wndId2Enum[ID_EN_INSHSW_L_RFE] = EN_INSHSW_L_RFE;
    wndId2Enum[ID_EN_INSHSW_W_RFE] = EN_INSHSW_W_RFE;
    wndId2Enum[ID_EN_NEXTRX_RFE] = EN_NEXTRX_RFE;
    wndId2Enum[ID_G_LNA_RFE] = G_LNA_RFE;
    wndId2Enum[ID_G_RXLOOPB_RFE] = G_RXLOOPB_RFE;
    wndId2Enum[ID_G_TIA_RFE] = G_TIA_RFE;
    wndId2Enum[ID_ICT_LNACMO_RFE] = ICT_LNACMO_RFE;
    wndId2Enum[ID_ICT_LNA_RFE] = ICT_LNA_RFE;
    wndId2Enum[ID_ICT_LODC_RFE] = ICT_LODC_RFE;
    wndId2Enum[ID_ICT_LOOPB_RFE] = ICT_LOOPB_RFE;
    wndId2Enum[ID_ICT_TIAMAIN_RFE] = ICT_TIAMAIN_RFE;
    wndId2Enum[ID_ICT_TIAOUT_RFE] = ICT_TIAOUT_RFE;
    wndId2Enum[ID_PD_LNA_RFE] = PD_LNA_RFE;
    wndId2Enum[ID_PD_MXLOBUF_RFE] = PD_MXLOBUF_RFE;
    wndId2Enum[ID_PD_QGEN_RFE] = PD_QGEN_RFE;
    wndId2Enum[ID_PD_RLOOPB_1_RFE] = PD_RLOOPB_1_RFE;
    wndId2Enum[ID_PD_RLOOPB_2_RFE] = PD_RLOOPB_2_RFE;
    wndId2Enum[ID_PD_RSSI_RFE] = PD_RSSI_RFE;
    wndId2Enum[ID_PD_TIA_RFE] = PD_TIA_RFE;
    wndId2Enum[ID_RCOMP_TIA_RFE] = RCOMP_TIA_RFE;
    wndId2Enum[ID_RFB_TIA_RFE] = RFB_TIA_RFE;
    wndId2Enum[ID_SEL_PATH_RFE] = SEL_PATH_RFE;
    wndId2Enum[ID_CDC_I_RFE] = CDC_I_RFE;
    wndId2Enum[ID_CDC_Q_RFE] = CDC_Q_RFE;
    wndId2Enum[ID_EN_DIR_RFE] = EN_DIR_RFE;
}

pnlRFE::pnlRFE(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlRFE::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlRFE)
wxStaticBoxSizer* StaticBoxSizer2;
wxFlexGridSizer* FlexGridSizer4;
wxFlexGridSizer* Inputshortingswitches4Sizer;
wxFlexGridSizer* Capacitorcontrols7Sizer;
wxFlexGridSizer* Referencecurrent5Sizer;
wxFlexGridSizer* DC3Sizer;
wxFlexGridSizer* Powerdowncontrols1Sizer;
wxFlexGridSizer* FlexGridSizer3;
wxStaticBoxSizer* CapacitorcontrolsSizer;
wxStaticBoxSizer* ReferencecurrentSizer;
wxFlexGridSizer* FlexGridSizer2;
wxStaticBoxSizer* UNGROUPEDSizer;
wxFlexGridSizer* Gaincontrols8Sizer;
wxFlexGridSizer* UNGROUPED2Sizer;
wxStaticBoxSizer* InputshortingswitchesSizer;
wxStaticBoxSizer* PowerdowncontrolsSizer;
wxStaticBoxSizer* GaincontrolsSizer;
wxStaticBoxSizer* StaticBoxSizer1;
wxFlexGridSizer* FlexGridSizer1;
wxStaticBoxSizer* DCSizer;
wxFlexGridSizer* Currentcontrol6Sizer;
wxStaticBoxSizer* CurrentcontrolSizer;

Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 5);
FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 5);
PowerdowncontrolsSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Power down controls"));
Powerdowncontrols1Sizer = new wxFlexGridSizer(0, 1, 0, 0);
chkPD_LNA_RFE = new wxCheckBox(this, ID_PD_LNA_RFE, _("LNA_RFE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_LNA_RFE"));
chkPD_LNA_RFE->SetValue(false);
chkPD_LNA_RFE->SetToolTip(_("Power control signal for LNA_RFE"));
Powerdowncontrols1Sizer->Add(chkPD_LNA_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_RLOOPB_1_RFE = new wxCheckBox(this, ID_PD_RLOOPB_1_RFE, _("RXFE loopback 1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_RLOOPB_1_RFE"));
chkPD_RLOOPB_1_RFE->SetValue(false);
chkPD_RLOOPB_1_RFE->SetToolTip(_("Power control signal for RXFE loopback 1"));
Powerdowncontrols1Sizer->Add(chkPD_RLOOPB_1_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_RLOOPB_2_RFE = new wxCheckBox(this, ID_PD_RLOOPB_2_RFE, _("RXFE loopback 2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_RLOOPB_2_RFE"));
chkPD_RLOOPB_2_RFE->SetValue(false);
chkPD_RLOOPB_2_RFE->SetToolTip(_("Power control signal for RXFE loopback 2"));
Powerdowncontrols1Sizer->Add(chkPD_RLOOPB_2_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_MXLOBUF_RFE = new wxCheckBox(this, ID_PD_MXLOBUF_RFE, _("RXFE mixer LO buffer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_MXLOBUF_RFE"));
chkPD_MXLOBUF_RFE->SetValue(false);
chkPD_MXLOBUF_RFE->SetToolTip(_("Power control signal for RXFE mixer lo buffer"));
Powerdowncontrols1Sizer->Add(chkPD_MXLOBUF_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_QGEN_RFE = new wxCheckBox(this, ID_PD_QGEN_RFE, _("RXFE Quadrature LO generator"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_QGEN_RFE"));
chkPD_QGEN_RFE->SetValue(false);
chkPD_QGEN_RFE->SetToolTip(_("Power control signal for RXFE Quadrature LO generator"));
Powerdowncontrols1Sizer->Add(chkPD_QGEN_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_RSSI_RFE = new wxCheckBox(this, ID_PD_RSSI_RFE, _("RXFE RSSI"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_RSSI_RFE"));
chkPD_RSSI_RFE->SetValue(false);
chkPD_RSSI_RFE->SetToolTip(_("Power control signal for RXFE RSSI"));
Powerdowncontrols1Sizer->Add(chkPD_RSSI_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_TIA_RFE = new wxCheckBox(this, ID_PD_TIA_RFE, _("RXFE TIA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_TIA_RFE"));
chkPD_TIA_RFE->SetValue(false);
chkPD_TIA_RFE->SetToolTip(_("Power control signal for RXFE TIA"));
Powerdowncontrols1Sizer->Add(chkPD_TIA_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_G_RFE = new wxCheckBox(this, ID_EN_G_RFE, _("Enable RFE module"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_G_RFE"));
chkEN_G_RFE->SetValue(false);
chkEN_G_RFE->SetToolTip(_("Enable control for all the RFE_1 power downs"));
Powerdowncontrols1Sizer->Add(chkEN_G_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Direct control"));
chkEN_DIR_RFE = new wxCheckBox(this, ID_EN_DIR_RFE, _("Enable direct control of PDs and ENs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_DIR_RFE"));
chkEN_DIR_RFE->SetValue(false);
chkEN_DIR_RFE->SetToolTip(_("Enables direct control of PDs and ENs for RFE module"));
StaticBoxSizer1->Add(chkEN_DIR_RFE, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
Powerdowncontrols1Sizer->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
PowerdowncontrolsSizer->Add(Powerdowncontrols1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(PowerdowncontrolsSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
UNGROUPEDSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("UNGROUPED"));
UNGROUPED2Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText0 = new wxStaticText(this, ID_STATICTEXT1, _("Active path to the RXFE"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
UNGROUPED2Sizer->Add(StaticText0, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbSEL_PATH_RFE = new ComboBoxMap(this, ID_SEL_PATH_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_SEL_PATH_RFE"));
cmbSEL_PATH_RFE->SetToolTip(_("Selects the active path of the RXFE"));
UNGROUPED2Sizer->Add(cmbSEL_PATH_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("Decoupling cap at output of RX mixer"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
UNGROUPED2Sizer->Add(StaticText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCAP_RXMXO_RFE = new ComboBoxMap(this, ID_CAP_RXMXO_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CAP_RXMXO_RFE"));
cmbCAP_RXMXO_RFE->SetToolTip(_("Control the decoupling cap at the output of the RX Mixer"));
UNGROUPED2Sizer->Add(cmbCAP_RXMXO_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("Controls cap parallel with the LNA input"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
UNGROUPED2Sizer->Add(StaticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCGSIN_LNA_RFE = new ComboBoxMap(this, ID_CGSIN_LNA_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CGSIN_LNA_RFE"));
cmbCGSIN_LNA_RFE->SetToolTip(_("Controls the cap parallel with the LNA input input NMOS CGS to control the Q of the maching circuit and provides trade off between gain/NF and IIP. The higher the frequency, the lower CGSIN_LNA_RFE should be. Also, the higher CGSIN, the lower the Q, The lower the gain, the higher the NF, and the higher the IIP3"));
UNGROUPED2Sizer->Add(cmbCGSIN_LNA_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Compensation resistor of TIA opamp"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
UNGROUPED2Sizer->Add(StaticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRCOMP_TIA_RFE = new ComboBoxMap(this, ID_RCOMP_TIA_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RCOMP_TIA_RFE"));
cmbRCOMP_TIA_RFE->SetToolTip(_("Controls the compensation resistors of the TIA opamp"));
UNGROUPED2Sizer->Add(cmbRCOMP_TIA_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("Sets feedback resistor to nominal value"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
UNGROUPED2Sizer->Add(StaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRFB_TIA_RFE = new ComboBoxMap(this, ID_RFB_TIA_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RFB_TIA_RFE"));
cmbRFB_TIA_RFE->SetToolTip(_("Sets the feedback resistor to the nominal value"));
UNGROUPED2Sizer->Add(cmbRFB_TIA_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_NEXTRX_RFE = new wxCheckBox(this, ID_EN_NEXTRX_RFE, _("Enable Rx MIMO mode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_NEXTRX_RFE"));
chkEN_NEXTRX_RFE->SetValue(false);
chkEN_NEXTRX_RFE->SetToolTip(_("Enables the daisy chain LO buffer going from RXFE1  to RXFE2"));
UNGROUPED2Sizer->Add(chkEN_NEXTRX_RFE, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
UNGROUPEDSizer->Add(UNGROUPED2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(UNGROUPEDSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
InputshortingswitchesSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Input shorting switches"));
Inputshortingswitches4Sizer = new wxFlexGridSizer(0, 1, 0, 0);
chkEN_INSHSW_LB1_RFE = new wxCheckBox(this, ID_EN_INSHSW_LB1_RFE, _("input of loopback 1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_INSHSW_LB1_RFE"));
chkEN_INSHSW_LB1_RFE->SetValue(false);
chkEN_INSHSW_LB1_RFE->SetToolTip(_("Enables the input shorting switch at the input  of the loopback 1 (in parallel with LNAL mixer)"));
Inputshortingswitches4Sizer->Add(chkEN_INSHSW_LB1_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_INSHSW_LB2_RFE = new wxCheckBox(this, ID_EN_INSHSW_LB2_RFE, _("input of loopback 2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_INSHSW_LB2_RFE"));
chkEN_INSHSW_LB2_RFE->SetValue(false);
chkEN_INSHSW_LB2_RFE->SetToolTip(_("Enables the input shorting switch at the input  of the loopback 2 (in parallel with LNAW mixer)"));
Inputshortingswitches4Sizer->Add(chkEN_INSHSW_LB2_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_INSHSW_L_RFE = new wxCheckBox(this, ID_EN_INSHSW_L_RFE, _("input of LNAL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_INSHSW_L_RFE"));
chkEN_INSHSW_L_RFE->SetValue(false);
chkEN_INSHSW_L_RFE->SetToolTip(_("Enables the input shorting switch at the input  of the LNAL"));
Inputshortingswitches4Sizer->Add(chkEN_INSHSW_L_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_INSHSW_W_RFE = new wxCheckBox(this, ID_EN_INSHSW_W_RFE, _("input of LNAW"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_INSHSW_W_RFE"));
chkEN_INSHSW_W_RFE->SetValue(false);
chkEN_INSHSW_W_RFE->SetToolTip(_("Enables the input shorting switch at the input  of the LNAW"));
Inputshortingswitches4Sizer->Add(chkEN_INSHSW_W_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
InputshortingswitchesSizer->Add(Inputshortingswitches4Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(InputshortingswitchesSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
DCSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("DC"));
DC3Sizer = new wxFlexGridSizer(0, 2, 0, 5);
DC3Sizer->AddGrowableCol(1);
StaticText5 = new wxStaticText(this, ID_STATICTEXT6, _("Offset I side"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
DC3Sizer->Add(StaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbDCOFFI_RFE = new ComboBoxMap(this, ID_DCOFFI_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DCOFFI_RFE"));
cmbDCOFFI_RFE->SetToolTip(_("Controls DC offset at the output of the TIA by injecting current to the input of the TIA (I side)"));
DC3Sizer->Add(cmbDCOFFI_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText6 = new wxStaticText(this, ID_STATICTEXT7, _("Offset Q side"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
DC3Sizer->Add(StaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbDCOFFQ_RFE = new ComboBoxMap(this, ID_DCOFFQ_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DCOFFQ_RFE"));
cmbDCOFFQ_RFE->SetToolTip(_("Controls DC offset at the output of the TIA by injecting current to the input of the TIA (Q side)"));
DC3Sizer->Add(cmbDCOFFQ_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText7 = new wxStaticText(this, ID_STATICTEXT8, _("Mixer LO signal"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
DC3Sizer->Add(StaticText7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_LODC_RFE = new ComboBoxMap(this, ID_ICT_LODC_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_LODC_RFE"));
cmbICT_LODC_RFE->SetToolTip(_("Controls the DC of the mixer LO signal at the gate of the mixer switches"));
DC3Sizer->Add(cmbICT_LODC_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_DCOFF_RXFE_RFE = new wxCheckBox(this, ID_EN_DCOFF_RXFE_RFE, _("Enable DCOFFSET block"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_DCOFF_RXFE_RFE"));
chkEN_DCOFF_RXFE_RFE->SetValue(false);
chkEN_DCOFF_RXFE_RFE->SetToolTip(_("Enables the DCOFFSET block for the RXFE"));
DC3Sizer->Add(chkEN_DCOFF_RXFE_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnDCclbrRSSI = new wxButton(this, ID_BUTTON2, _("Calibrate DC"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
DC3Sizer->Add(btnDCclbrRSSI, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
DCSizer->Add(DC3Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(DCSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
ReferencecurrentSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Reference current"));
Referencecurrent5Sizer = new wxFlexGridSizer(0, 2, 0, 5);
Referencecurrent5Sizer->AddGrowableCol(1);
StaticText8 = new wxStaticText(this, ID_STATICTEXT9, _("Loopback amplifier"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
Referencecurrent5Sizer->Add(StaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_LOOPB_RFE = new ComboBoxMap(this, ID_ICT_LOOPB_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_LOOPB_RFE"));
cmbICT_LOOPB_RFE->SetToolTip(_("Controls the reference current of the RXFE loopback amplifier"));
Referencecurrent5Sizer->Add(cmbICT_LOOPB_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText9 = new wxStaticText(this, ID_STATICTEXT10, _("TIA 1st stage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
Referencecurrent5Sizer->Add(StaticText9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_TIAMAIN_RFE = new ComboBoxMap(this, ID_ICT_TIAMAIN_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_TIAMAIN_RFE"));
cmbICT_TIAMAIN_RFE->SetToolTip(_("Controls the reference current of the RXFE TIA first stage"));
Referencecurrent5Sizer->Add(cmbICT_TIAMAIN_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText10 = new wxStaticText(this, ID_STATICTEXT11, _("TIA 2nd stage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
Referencecurrent5Sizer->Add(StaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_TIAOUT_RFE = new ComboBoxMap(this, ID_ICT_TIAOUT_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_TIAOUT_RFE"));
cmbICT_TIAOUT_RFE->SetToolTip(_("Controls the reference current of the RXFE TIA 2nd stage"));
Referencecurrent5Sizer->Add(cmbICT_TIAOUT_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
ReferencecurrentSizer->Add(Referencecurrent5Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(ReferencecurrentSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
CurrentcontrolSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Current control"));
Currentcontrol6Sizer = new wxFlexGridSizer(0, 2, 0, 5);
Currentcontrol6Sizer->AddGrowableCol(1);
StaticText11 = new wxStaticText(this, ID_STATICTEXT12, _("LNA output common mode voltage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
Currentcontrol6Sizer->Add(StaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_LNACMO_RFE = new ComboBoxMap(this, ID_ICT_LNACMO_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_LNACMO_RFE"));
cmbICT_LNACMO_RFE->SetToolTip(_("Controls the current generating LNA output common mode voltage"));
Currentcontrol6Sizer->Add(cmbICT_LNACMO_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText12 = new wxStaticText(this, ID_STATICTEXT13, _("LNA core"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
Currentcontrol6Sizer->Add(StaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_LNA_RFE = new ComboBoxMap(this, ID_ICT_LNA_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_LNA_RFE"));
cmbICT_LNA_RFE->SetToolTip(_("Controls the current of the LNA core"));
Currentcontrol6Sizer->Add(cmbICT_LNA_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
CurrentcontrolSizer->Add(Currentcontrol6Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(CurrentcontrolSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
CapacitorcontrolsSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Capacitor controls"));
Capacitorcontrols7Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText13 = new wxStaticText(this, ID_STATICTEXT14, _("Compensation TIA"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
Capacitorcontrols7Sizer->Add(StaticText13, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCCOMP_TIA_RFE = new ComboBoxMap(this, ID_CCOMP_TIA_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CCOMP_TIA_RFE"));
cmbCCOMP_TIA_RFE->SetToolTip(_("Compensation capacitor for TIA"));
Capacitorcontrols7Sizer->Add(cmbCCOMP_TIA_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText14 = new wxStaticText(this, ID_STATICTEXT15, _("Feedback TIA"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
Capacitorcontrols7Sizer->Add(StaticText14, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCFB_TIA_RFE = new ComboBoxMap(this, ID_CFB_TIA_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CFB_TIA_RFE"));
cmbCFB_TIA_RFE->SetToolTip(_("Feeback capacitor for TIA. Controls the 3dB BW of the TIA. Should be set with calibration through digital baseband"));
Capacitorcontrols7Sizer->Add(cmbCFB_TIA_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
CapacitorcontrolsSizer->Add(Capacitorcontrols7Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer4->Add(CapacitorcontrolsSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
GaincontrolsSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Gain controls"));
Gaincontrols8Sizer = new wxFlexGridSizer(0, 2, 0, 5);
Gaincontrols8Sizer->AddGrowableCol(0);
StaticText15 = new wxStaticText(this, ID_STATICTEXT16, _("LNA"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
Gaincontrols8Sizer->Add(StaticText15, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbG_LNA_RFE = new ComboBoxMap(this, ID_G_LNA_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_G_LNA_RFE"));
cmbG_LNA_RFE->SetToolTip(_("Controls the gain of the LNA"));
Gaincontrols8Sizer->Add(cmbG_LNA_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText16 = new wxStaticText(this, ID_STATICTEXT17, _("Loopback"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
Gaincontrols8Sizer->Add(StaticText16, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbG_RXLOOPB_RFE = new ComboBoxMap(this, ID_G_RXLOOPB_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_G_RXLOOPB_RFE"));
cmbG_RXLOOPB_RFE->SetToolTip(_("Controls RXFE loopback gain"));
Gaincontrols8Sizer->Add(cmbG_RXLOOPB_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText17 = new wxStaticText(this, ID_STATICTEXT18, _("TIA"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
Gaincontrols8Sizer->Add(StaticText17, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbG_TIA_RFE = new ComboBoxMap(this, ID_G_TIA_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_G_TIA_RFE"));
cmbG_TIA_RFE->SetToolTip(_("Controls the Gain of the TIA"));
Gaincontrols8Sizer->Add(cmbG_TIA_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
GaincontrolsSizer->Add(Gaincontrols8Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer4->Add(GaincontrolsSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Trim duty cycle"));
FlexGridSizer3 = new wxFlexGridSizer(2, 2, 0, 0);
FlexGridSizer3->AddGrowableCol(0);
StaticText18 = new wxStaticText(this, ID_STATICTEXT19, _("I channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
FlexGridSizer3->Add(StaticText18, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
cmbCDC_I_RFE = new ComboBoxMap(this, ID_CDC_I_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CDC_I_RFE"));
FlexGridSizer3->Add(cmbCDC_I_RFE, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText19 = new wxStaticText(this, ID_STATICTEXT20, _("Q channel:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
FlexGridSizer3->Add(StaticText19, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
cmbCDC_Q_RFE = new ComboBoxMap(this, ID_CDC_Q_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CDC_Q_RFE"));
FlexGridSizer3->Add(cmbCDC_Q_RFE, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer2->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer4->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer1->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_PD_LNA_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_PD_RLOOPB_1_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_PD_RLOOPB_2_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_PD_MXLOBUF_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_PD_QGEN_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_PD_RSSI_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_PD_TIA_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_EN_G_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_EN_DIR_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_SEL_PATH_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_CAP_RXMXO_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_CGSIN_LNA_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_RCOMP_TIA_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_RFB_TIA_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_EN_NEXTRX_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_EN_INSHSW_LB1_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_EN_INSHSW_LB2_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_EN_INSHSW_L_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_EN_INSHSW_W_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_DCOFFI_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_DCOFFQ_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_ICT_LODC_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_EN_DCOFF_RXFE_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRFE::OnbtnDCclbrRSSIClick);
Connect(ID_ICT_LOOPB_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_ICT_TIAMAIN_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_ICT_TIAOUT_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_ICT_LNACMO_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_ICT_LNA_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_CCOMP_TIA_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_CFB_TIA_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_G_LNA_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_G_RXLOOPB_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_G_TIA_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_CDC_I_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
Connect(ID_CDC_Q_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRFE::ParameterChangeHandler);
//*)
}
pnlRFE::~pnlRFE()
{
//(*Destroy(pnlRFE)
//*)
}
void pnlRFE::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlRFE panel don't have control module assigned" << std::endl;
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
    lmsControl->SetParam( parameter, event.GetInt());
}

void pnlRFE::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    char ctemp[80];
    wxArrayString temp;
    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i fF", (i+1)*80); temp.push_back(ctemp);}
    cmbCAP_RXMXO_RFE->Clear();
    cmbCAP_RXMXO_RFE->Append(temp);
    cmbCAP_RXMXO_RFE->SetSelection( lmsControl->GetParam(CAP_RXMXO_RFE));

    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbCCOMP_TIA_RFE->Clear();
    cmbCCOMP_TIA_RFE->Append(temp);
    cmbCCOMP_TIA_RFE->SetSelection( lmsControl->GetParam(CCOMP_TIA_RFE));

    temp.clear();
    vector<cmbKeyValuePair> keyvalues;
    for(int i=0; i<4096; ++i)
    {
        sprintf(ctemp, "%i", i);
        keyvalues.push_back(cmbKeyValuePair(i,ctemp));
    }
    cmbCFB_TIA_RFE->Clear();
    cmbCFB_TIA_RFE->Set(keyvalues);
    cmbCFB_TIA_RFE->SetSelection( lmsControl->GetParam(CFB_TIA_RFE));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbCGSIN_LNA_RFE->Clear();
    cmbCGSIN_LNA_RFE->Append(temp);
    cmbCGSIN_LNA_RFE->SetSelection( lmsControl->GetParam(CGSIN_LNA_RFE));

    keyvalues.clear();
    for(int i=63; i>=0; --i)
    {
        sprintf(ctemp, "%i", -i);
        keyvalues.push_back(cmbKeyValuePair(i|0x40,ctemp));
    }
    for(int i=0; i<64; ++i)
    {
        sprintf(ctemp, "%i", i);
        keyvalues.push_back(cmbKeyValuePair(i,ctemp));
    }
    cmbDCOFFI_RFE->Clear();
    cmbDCOFFI_RFE->Set(keyvalues);
    cmbDCOFFI_RFE->SetSelection( lmsControl->GetParam(DCOFFI_RFE));
    cmbDCOFFQ_RFE->Clear();
    cmbDCOFFQ_RFE->Set(keyvalues);
    cmbDCOFFQ_RFE->SetSelection( lmsControl->GetParam(DCOFFQ_RFE));

    keyvalues.clear();
    keyvalues.push_back(cmbKeyValuePair(1,"Gmax-30"));
    keyvalues.push_back(cmbKeyValuePair(2,"Gmax-27"));
    keyvalues.push_back(cmbKeyValuePair(3,"Gmax-24"));
    keyvalues.push_back(cmbKeyValuePair(4,"Gmax-21"));
    keyvalues.push_back(cmbKeyValuePair(5,"Gmax-18"));
    keyvalues.push_back(cmbKeyValuePair(6,"Gmax-15"));
    keyvalues.push_back(cmbKeyValuePair(7,"Gmax-12"));
    keyvalues.push_back(cmbKeyValuePair(8,"Gmax-9"));
    keyvalues.push_back(cmbKeyValuePair(9,"Gmax-6"));
    keyvalues.push_back(cmbKeyValuePair(10,"Gmax-5"));
    keyvalues.push_back(cmbKeyValuePair(11,"Gmax-4"));
    keyvalues.push_back(cmbKeyValuePair(12,"Gmax-3"));
    keyvalues.push_back(cmbKeyValuePair(13,"Gmax-2"));
    keyvalues.push_back(cmbKeyValuePair(14,"Gmax-1"));
    keyvalues.push_back(cmbKeyValuePair(15,"Gmax"));
    cmbG_LNA_RFE->Clear();
    cmbG_LNA_RFE->Set(keyvalues);
    cmbG_LNA_RFE->SetSelection( lmsControl->GetParam(G_LNA_RFE));

    temp.clear();
    temp.push_back("Gmax-40");
    temp.push_back("Gmax-24");
    temp.push_back("Gmax-17");
    temp.push_back("Gmax-14");
    temp.push_back("Gmax-11");
    temp.push_back("Gmax-9");
    temp.push_back("Gmax-7.5");
    temp.push_back("Gmax-6.2");
    temp.push_back("Gmax-5");
    temp.push_back("Gmax-4");
    temp.push_back("Gmax-3");
    temp.push_back("Gmax-2.4");
    temp.push_back("Gmax-1.6");
    temp.push_back("Gmax-1");
    temp.push_back("Gmax-0.5");
    temp.push_back("Gmax");
    cmbG_RXLOOPB_RFE->Clear();
    cmbG_RXLOOPB_RFE->Append(temp);
    cmbG_RXLOOPB_RFE->SetSelection( lmsControl->GetParam(G_RXLOOPB_RFE));

    keyvalues.clear();
    keyvalues.push_back(cmbKeyValuePair(1,"Gmax-12"));
    keyvalues.push_back(cmbKeyValuePair(2,"Gmax-3"));
    keyvalues.push_back(cmbKeyValuePair(3,"Gmax"));
    cmbG_TIA_RFE->Clear();
    cmbG_TIA_RFE->Set(keyvalues);
    cmbG_TIA_RFE->SetSelection( lmsControl->GetParam(G_TIA_RFE));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_LNACMO_RFE->Clear();
    cmbICT_LNACMO_RFE->Append(temp);
    cmbICT_LNACMO_RFE->SetSelection( lmsControl->GetParam(ICT_LNACMO_RFE));

    temp.clear();
    float nominalCurrent = 500; //uA
    for(int i=0; i<32; ++i)
        //{sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
        {sprintf(ctemp, "%.1f uA", nominalCurrent*(i/12.0)); temp.push_back(ctemp);}
    cmbICT_LNA_RFE->Clear();
    cmbICT_LNA_RFE->Append(temp);
    cmbICT_LNA_RFE->SetSelection( lmsControl->GetParam(ICT_LNA_RFE));

    temp.clear();
    float Vth = 0.440; //V
    for(int i=0; i<32; ++i)
        //{sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
        {sprintf(ctemp, "%.3f V", Vth+3500*0.000020*(i/12.0)); temp.push_back(ctemp);}
    cmbICT_LODC_RFE->Clear();
    cmbICT_LODC_RFE->Append(temp);
    cmbICT_LODC_RFE->SetSelection( lmsControl->GetParam(ICT_LODC_RFE));

    temp.clear();
    float IsupplyNominal = 1.80; //uA
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%.3f uA", IsupplyNominal*(i/12.0)); temp.push_back(ctemp);}
        //{sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_LOOPB_RFE->Clear();
    cmbICT_LOOPB_RFE->Append(temp);
    cmbICT_LOOPB_RFE->SetSelection( lmsControl->GetParam(ICT_LOOPB_RFE));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_TIAMAIN_RFE->Clear();
    cmbICT_TIAMAIN_RFE->Append(temp);
    cmbICT_TIAMAIN_RFE->SetSelection( lmsControl->GetParam(ICT_TIAMAIN_RFE));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_TIAOUT_RFE->Clear();
    cmbICT_TIAOUT_RFE->Append(temp);
    cmbICT_TIAOUT_RFE->SetSelection( lmsControl->GetParam(ICT_TIAOUT_RFE));

    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbRCOMP_TIA_RFE->Clear();
    cmbRCOMP_TIA_RFE->Append(temp);
    cmbRCOMP_TIA_RFE->SetSelection( lmsControl->GetParam(RCOMP_TIA_RFE));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbRFB_TIA_RFE->Clear();
    cmbRFB_TIA_RFE->Append(temp);
    cmbRFB_TIA_RFE->SetSelection( lmsControl->GetParam(RFB_TIA_RFE));

    temp.clear();
    temp.push_back("No path active");
    temp.push_back("LNAH");
    temp.push_back("LNAL");
    temp.push_back("LNAW");
    cmbSEL_PATH_RFE->Clear();
    cmbSEL_PATH_RFE->Append(temp);
    cmbSEL_PATH_RFE->SetSelection( lmsControl->GetParam(SEL_PATH_RFE));

    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbCDC_I_RFE->Clear();
    cmbCDC_I_RFE->Append(temp);
    cmbCDC_I_RFE->SetSelection( lmsControl->GetParam(CDC_I_TRF));
    cmbCDC_Q_RFE->Clear();
    cmbCDC_Q_RFE->Append(temp);
    cmbCDC_Q_RFE->SetSelection( lmsControl->GetParam(CDC_Q_TRF));
    UpdateTooltips(this);
}

void pnlRFE::UpdateGUI()
{
    long value = 0;
    value = lmsControl->GetParam(CAP_RXMXO_RFE);
    cmbCAP_RXMXO_RFE->SetSelection(value);

    value = lmsControl->GetParam(CCOMP_TIA_RFE);
    cmbCCOMP_TIA_RFE->SetSelection(value);

    value = lmsControl->GetParam(CFB_TIA_RFE);
    cmbCFB_TIA_RFE->SetSelection(value);

    value = lmsControl->GetParam(CGSIN_LNA_RFE);
    cmbCGSIN_LNA_RFE->SetSelection(value);

    value = lmsControl->GetParam(DCOFFI_RFE);
    cmbDCOFFI_RFE->SetSelection(value);

    value = lmsControl->GetParam(DCOFFQ_RFE);
    cmbDCOFFQ_RFE->SetSelection(value);

    value = lmsControl->GetParam(EN_DCOFF_RXFE_RFE);
    chkEN_DCOFF_RXFE_RFE->SetValue(value);

    value = lmsControl->GetParam(EN_G_RFE);
    chkEN_G_RFE->SetValue(value);

    value = lmsControl->GetParam(EN_INSHSW_LB1_RFE);
    chkEN_INSHSW_LB1_RFE->SetValue(value);

    value = lmsControl->GetParam(EN_INSHSW_LB2_RFE);
    chkEN_INSHSW_LB2_RFE->SetValue(value);

    value = lmsControl->GetParam(EN_INSHSW_L_RFE);
    chkEN_INSHSW_L_RFE->SetValue(value);

    value = lmsControl->GetParam(EN_INSHSW_W_RFE);
    chkEN_INSHSW_W_RFE->SetValue(value);

    value = lmsControl->GetParam(EN_NEXTRX_RFE);
    chkEN_NEXTRX_RFE->SetValue(value);
    if(lmsControl->GetConfigChannel() == 0)
        chkEN_NEXTRX_RFE->Show();
    else
        chkEN_NEXTRX_RFE->Hide();

    value = lmsControl->GetParam(G_LNA_RFE);
    cmbG_LNA_RFE->SetSelection(value);

    value = lmsControl->GetParam(G_RXLOOPB_RFE);
    cmbG_RXLOOPB_RFE->SetSelection(value);

    value = lmsControl->GetParam(G_TIA_RFE);
    cmbG_TIA_RFE->SetSelection(value);

    value = lmsControl->GetParam(ICT_LNACMO_RFE);
    cmbICT_LNACMO_RFE->SetSelection(value);

    value = lmsControl->GetParam(ICT_LNA_RFE);
    cmbICT_LNA_RFE->SetSelection(value);

    value = lmsControl->GetParam(ICT_LODC_RFE);
    cmbICT_LODC_RFE->SetSelection(value);

    value = lmsControl->GetParam(ICT_LOOPB_RFE);
    cmbICT_LOOPB_RFE->SetSelection(value);

    value = lmsControl->GetParam(ICT_TIAMAIN_RFE);
    cmbICT_TIAMAIN_RFE->SetSelection(value);

    value = lmsControl->GetParam(ICT_TIAOUT_RFE);
    cmbICT_TIAOUT_RFE->SetSelection(value);

    value = lmsControl->GetParam(PD_LNA_RFE);
    chkPD_LNA_RFE->SetValue(value);

    value = lmsControl->GetParam(PD_MXLOBUF_RFE);
    chkPD_MXLOBUF_RFE->SetValue(value);

    value = lmsControl->GetParam(PD_QGEN_RFE);
    chkPD_QGEN_RFE->SetValue(value);

    value = lmsControl->GetParam(PD_RLOOPB_1_RFE);
    chkPD_RLOOPB_1_RFE->SetValue(value);

    value = lmsControl->GetParam(PD_RLOOPB_2_RFE);
    chkPD_RLOOPB_2_RFE->SetValue(value);

    value = lmsControl->GetParam(PD_RSSI_RFE);
    chkPD_RSSI_RFE->SetValue(value);

    value = lmsControl->GetParam(PD_TIA_RFE);
    chkPD_TIA_RFE->SetValue(value);

    value = lmsControl->GetParam(RCOMP_TIA_RFE);
    cmbRCOMP_TIA_RFE->SetSelection(value);

    value = lmsControl->GetParam(RFB_TIA_RFE);
    cmbRFB_TIA_RFE->SetSelection(value);

    value = lmsControl->GetParam(SEL_PATH_RFE);
    cmbSEL_PATH_RFE->SetSelection(value);
}


void pnlRFE::OnbtnCalibrateDCClick(wxCommandEvent& event)
{
    if(lmsControl->algorithms->DCCalibrationRX(true) != 0)
        wxMessageBox(_("DC Calibration failed"),_("Error"),wxCLOSE,this);
    else
        wxMessageBox(_("DC Calibration Finished"),_("Info"),wxOK,this);
    lmsControl->DownloadAll();
    UpdateGUI();
}

void pnlRFE::OnbtnDCclbrRSSIClick(wxCommandEvent& event)
{
    if(lmsControl->algorithms->DCCalibrationRX_RSSI(true) != 0)
        wxMessageBox(_("DC Calibration failed"),_("Error"),wxCLOSE,this);
    else
        wxMessageBox(_("DC Calibration Finished"),_("Info"),wxOK,this);
    lmsControl->DownloadAll();
    UpdateGUI();
}
