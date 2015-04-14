/**
@file 	pnlCLKGEN.cpp
@author	Lime Microsystems
@brief	CLKGEN module panel
*/

#include "pnlCLKGEN.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "LMS7002_MainControl.h"
#include "dlgVCO_SX.h"
#include "dlgFloatInput.h"
#include "ConnectionManager.h"
//(*InternalHeaders(pnlCLKGEN)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)
//(*IdInit(pnlCLKGEN)
const long pnlCLKGEN::ID_SPDUP_VCO_CGEN = wxNewId();
const long pnlCLKGEN::ID_RESET_N_CGEN = wxNewId();
const long pnlCLKGEN::ID_EN_COARSE_CKLGEN = wxNewId();
const long pnlCLKGEN::ID_EN_INTONLY_SDM_CGEN = wxNewId();
const long pnlCLKGEN::ID_EN_SDM_CLK_CGEN = wxNewId();
const long pnlCLKGEN::ID_EN_SDM_TSTO_CGEN = wxNewId();
const long pnlCLKGEN::ID_REV_SDMCLK_CGEN = wxNewId();
const long pnlCLKGEN::ID_SX_DITHER_EN_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT1 = wxNewId();
const long pnlCLKGEN::ID_EN_ADCCLKH_CLKGN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT4 = wxNewId();
const long pnlCLKGEN::ID_TST_CGEN = wxNewId();
const long pnlCLKGEN::ID_REV_CLKDAC_CGEN = wxNewId();
const long pnlCLKGEN::ID_REV_CLKADC_CGEN = wxNewId();
const long pnlCLKGEN::ID_REVPH_PFD_CGEN = wxNewId();
const long pnlCLKGEN::ID_COARSE_START_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT5 = wxNewId();
const long pnlCLKGEN::ID_COARSE_STEPDONE_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT6 = wxNewId();
const long pnlCLKGEN::ID_COARSEPLL_COMPO_CGEN = wxNewId();
const long pnlCLKGEN::ID_BUTTON1 = wxNewId();
const long pnlCLKGEN::ID_SEL_SDMCLK_CGEN = wxNewId();
const long pnlCLKGEN::ID_PD_CP_CGEN = wxNewId();
const long pnlCLKGEN::ID_PD_FDIV_FB_CGEN = wxNewId();
const long pnlCLKGEN::ID_PD_FDIV_O_CGEN = wxNewId();
const long pnlCLKGEN::ID_PD_SDM_CGEN = wxNewId();
const long pnlCLKGEN::ID_PD_VCO_CGEN = wxNewId();
const long pnlCLKGEN::ID_PD_VCO_COMP_CGEN = wxNewId();
const long pnlCLKGEN::ID_EN_G_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT20 = wxNewId();
const long pnlCLKGEN::ID_CSW_VCO_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT9 = wxNewId();
const long pnlCLKGEN::ID_ICT_VCO_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT11 = wxNewId();
const long pnlCLKGEN::ID_VCO_CMPHO_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT12 = wxNewId();
const long pnlCLKGEN::ID_VCO_CMPLO_CGEN = wxNewId();
const long pnlCLKGEN::ID_BUTTON2 = wxNewId();
const long pnlCLKGEN::ID_BUTTON5 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT13 = wxNewId();
const long pnlCLKGEN::ID_CP2_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT14 = wxNewId();
const long pnlCLKGEN::ID_CP3_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT15 = wxNewId();
const long pnlCLKGEN::ID_CZ_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT16 = wxNewId();
const long pnlCLKGEN::ID_IOFFSET_CP_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT17 = wxNewId();
const long pnlCLKGEN::ID_IPULSE_CP_CGEN = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT10 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT18 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT3 = wxNewId();
const long pnlCLKGEN::ID_TEXTCTRL1 = wxNewId();
const long pnlCLKGEN::ID_CLKH_OV_CLKL_CGEN = wxNewId();
const long pnlCLKGEN::ID_TEXTCTRL2 = wxNewId();
const long pnlCLKGEN::ID_BUTTON3 = wxNewId();
const long pnlCLKGEN::ID_BUTTON4 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT7 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT8 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT21 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT22 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT2 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT19 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT25 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT26 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT27 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT28 = wxNewId();
const long pnlCLKGEN::ID_BUTTON6 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT23 = wxNewId();
const long pnlCLKGEN::ID_STATICTEXT24 = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlCLKGEN,wxPanel)
//(*EventTable(pnlCLKGEN)
//*)
END_EVENT_TABLE()

void pnlCLKGEN::AssignEnumsToIds()
{
    wndId2Enum[ID_CLKH_OV_CLKL_CGEN] = CLKH_OV_CLKL_CGEN;
    wndId2Enum[ID_COARSE_START_CGEN] = COARSE_START_CGEN;
    wndId2Enum[ID_CP2_CGEN] = CP2_CGEN;
    wndId2Enum[ID_CP3_CGEN] = CP3_CGEN;
    wndId2Enum[ID_CSW_VCO_CGEN] = CSW_VCO_CGEN;
    wndId2Enum[ID_CZ_CGEN] = CZ_CGEN;
    //wndId2Enum[ID_DIV_OUTCH_CGEN] = DIV_OUTCH_CGEN;
    wndId2Enum[ID_EN_COARSE_CKLGEN] = EN_COARSE_CKLGEN;
    wndId2Enum[ID_EN_ADCCLKH_CLKGN] = EN_ADCCLKH_CLKGN;
    wndId2Enum[ID_EN_G_CGEN] = EN_G_CGEN;
    wndId2Enum[ID_EN_INTONLY_SDM_CGEN] = EN_INTONLY_SDM_CGEN;
    wndId2Enum[ID_EN_SDM_CLK_CGEN] = EN_SDM_CLK_CGEN;
    wndId2Enum[ID_EN_SDM_TSTO_CGEN] = EN_SDM_TSTO_CGEN;
    //wndId2Enum[ID_FRAC_SDM_CGEN] = FRAC_SDM_CGEN;
    wndId2Enum[ID_ICT_VCO_CGEN] = ICT_VCO_CGEN;
    //wndId2Enum[ID_INT_SDM_CGEN] = INT_SDM_CGEN;
    wndId2Enum[ID_IOFFSET_CP_CGEN] = IOFFSET_CP_CGEN;
    wndId2Enum[ID_IPULSE_CP_CGEN] = IPULSE_CP_CGEN;
    wndId2Enum[ID_PD_CP_CGEN] = PD_CP_CGEN;
    wndId2Enum[ID_PD_FDIV_FB_CGEN] = PD_FDIV_FB_CGEN;
    wndId2Enum[ID_PD_FDIV_O_CGEN] = PD_FDIV_O_CGEN;
    wndId2Enum[ID_PD_SDM_CGEN] = PD_SDM_CGEN;
    wndId2Enum[ID_PD_VCO_CGEN] = PD_VCO_CGEN;
    wndId2Enum[ID_PD_VCO_COMP_CGEN] = PD_VCO_COMP_CGEN;
    wndId2Enum[ID_RESET_N_CGEN] = RESET_N_CGEN;
    wndId2Enum[ID_REVPH_PFD_CGEN] = REVPH_PFD_CGEN;
    wndId2Enum[ID_REV_CLKADC_CGEN] = REV_CLKADC_CGEN;
    wndId2Enum[ID_REV_CLKDAC_CGEN] = REV_CLKDAC_CGEN;
    wndId2Enum[ID_REV_SDMCLK_CGEN] = REV_SDMCLK_CGEN;
    wndId2Enum[ID_SEL_SDMCLK_CGEN] = SEL_SDMCLK_CGEN;
    wndId2Enum[ID_SPDUP_VCO_CGEN] = SPDUP_VCO_CGEN;
    wndId2Enum[ID_SX_DITHER_EN_CGEN] = SX_DITHER_EN_CGEN;
    wndId2Enum[ID_TST_CGEN] = TST_CGEN;
}

pnlCLKGEN::pnlCLKGEN(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlCLKGEN::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlCLKGEN)
wxStaticBoxSizer* StaticBoxSizer2;
wxFlexGridSizer* FlexGridSizer4;
wxStaticBoxSizer* VCOSizer;
wxFlexGridSizer* VCOPLLSizer;
wxFlexGridSizer* FlexGridSizer3;
wxFlexGridSizer* FlexGridSizer5;
wxFlexGridSizer* Powerdowncontrols2Sizer;
wxFlexGridSizer* FlexGridSizer2;
wxFlexGridSizer* FlexGridSizer7;
wxFlexGridSizer* UNGROUPED1Sizer;
wxFlexGridSizer* VCO4Sizer;
wxFlexGridSizer* PLLfilter5Sizer;
wxStaticBoxSizer* UNGROUPEDSizer;
wxStaticBoxSizer* StaticBoxSizer3;
wxStaticBoxSizer* PLLfilterSizer;
wxBoxSizer* BoxSizer1;
wxFlexGridSizer* Chargepump6Sizer;
wxStaticBoxSizer* PowerdowncontrolsSizer;
wxFlexGridSizer* FlexGridSizer6;
wxFlexGridSizer* FlexGridSizer1;
wxStaticBoxSizer* ChargepumpSizer;

Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 5);
FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
UNGROUPEDSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("UNGROUPED"));
UNGROUPED1Sizer = new wxFlexGridSizer(0, 2, 0, 5);
chkSPDUP_VCO_CGEN = new wxCheckBox(this, ID_SPDUP_VCO_CGEN, _("Bypass noise filter resistor"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_VCO_CGEN"));
chkSPDUP_VCO_CGEN->SetValue(false);
chkSPDUP_VCO_CGEN->SetToolTip(_("Bypasses the noise filter resistor for fast setlling time. It should be connected to a 1us pulse"));
UNGROUPED1Sizer->Add(chkSPDUP_VCO_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkRESET_N_CGEN = new wxCheckBox(this, ID_RESET_N_CGEN, _("Pulse used in start-up to reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RESET_N_CGEN"));
chkRESET_N_CGEN->SetValue(false);
chkRESET_N_CGEN->SetToolTip(_("A pulse should be used in the start-up to reset ( 1-normal operation)"));
UNGROUPED1Sizer->Add(chkRESET_N_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_COARSE_CKLGEN = new wxCheckBox(this, ID_EN_COARSE_CKLGEN, _("Enable coarse tuning block"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_COARSE_CKLGEN"));
chkEN_COARSE_CKLGEN->SetValue(false);
chkEN_COARSE_CKLGEN->SetToolTip(_("Enable signal for coarse tuning block"));
UNGROUPED1Sizer->Add(chkEN_COARSE_CKLGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_INTONLY_SDM_CGEN = new wxCheckBox(this, ID_EN_INTONLY_SDM_CGEN, _("Enable INTEGER-N mode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_INTONLY_SDM_CGEN"));
chkEN_INTONLY_SDM_CGEN->SetValue(false);
chkEN_INTONLY_SDM_CGEN->SetToolTip(_("Enables INTEGER-N mode of the SX "));
UNGROUPED1Sizer->Add(chkEN_INTONLY_SDM_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_SDM_CLK_CGEN = new wxCheckBox(this, ID_EN_SDM_CLK_CGEN, _("Enable SDM clock"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_SDM_CLK_CGEN"));
chkEN_SDM_CLK_CGEN->SetValue(false);
chkEN_SDM_CLK_CGEN->SetToolTip(_("Enables/Disables SDM clock. In INT-N mode or for noise testing, SDM clock can be disabled"));
UNGROUPED1Sizer->Add(chkEN_SDM_CLK_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_SDM_TSTO_CGEN = new wxCheckBox(this, ID_EN_SDM_TSTO_CGEN, _("Enable SDM_TSTO outputs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_SDM_TSTO_CGEN"));
chkEN_SDM_TSTO_CGEN->SetValue(false);
chkEN_SDM_TSTO_CGEN->SetToolTip(_("Enables the SDM_TSTO"));
UNGROUPED1Sizer->Add(chkEN_SDM_TSTO_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkREV_SDMCLK_CGEN = new wxCheckBox(this, ID_REV_SDMCLK_CGEN, _("Reverse SDM clock"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_REV_SDMCLK_CGEN"));
chkREV_SDMCLK_CGEN->SetValue(false);
chkREV_SDMCLK_CGEN->SetToolTip(_("Reverses the SDM clock"));
UNGROUPED1Sizer->Add(chkREV_SDMCLK_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSX_DITHER_EN_CGEN = new wxCheckBox(this, ID_SX_DITHER_EN_CGEN, _("Enable dithering in SDM"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SX_DITHER_EN_CGEN"));
chkSX_DITHER_EN_CGEN->SetValue(false);
chkSX_DITHER_EN_CGEN->SetToolTip(_("Enabled dithering in SDM"));
UNGROUPED1Sizer->Add(chkSX_DITHER_EN_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText0 = new wxStaticText(this, ID_STATICTEXT1, _("Connection to FCLK_ADC"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
UNGROUPED1Sizer->Add(StaticText0, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbEN_ADCCLKH_CLKGN = new ComboBoxMap(this, ID_EN_ADCCLKH_CLKGN, wxEmptyString, wxDefaultPosition, wxSize(179,-1), 0, 0, 0, wxDefaultValidator, _T("ID_EN_ADCCLKH_CLKGN"));
cmbEN_ADCCLKH_CLKGN->SetToolTip(_("Selects if F_CLKH or F_CLKL is connected to FCLK_ADC"));
UNGROUPED1Sizer->Add(cmbEN_ADCCLKH_CLKGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Test mode of SX"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
UNGROUPED1Sizer->Add(StaticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbTST_CGEN = new ComboBoxMap(this, ID_TST_CGEN, wxEmptyString, wxDefaultPosition, wxSize(340,-1), 0, 0, 0, wxDefaultValidator, _T("ID_TST_CGEN"));
cmbTST_CGEN->SetToolTip(_("Controls the test mode of the SX\n    0 – TST disabled; RSSI analog outputs enabled if RSSI blocks active and when all PLL test signals are off\n    1 – tstdo[0]=ADC clock; tstdo[1]=DAC clock; tstao = High impedance;\n    2 – tstdo[0]=SDM clock; tstdo[1]= feedback divider output; tstao = VCO tune through a 60kOhm resistor;\n    3 – tstdo[0]=Reference clock; tstdo[1]= feedback divider output; tstao = VCO tune through a 10kOhm resistor;\n    4 – tstdo[0]= High impedance; tstdo[1]= High impedance; tstao = High impedance;\n    5 – tstdo[0]=Charge pump Down signal; tstdo[1]=Charge pump Up signal; tstao = High impedance;\n    6 – tstdo[0]= High impedance; tstdo[1]= High impedance; tstao = VCO tune through a 60kOhm resistor;\n    7 – tstdo[0]= High impedance; tstdo[1]= High impedance; tstao = VCO tune through a 10kOhm resistor;\n\n    if TST_SX[2]=1 --> VCO_TSTBUF active generating VCO_TST_DIV20 and VCO_TST_DIV40"));
UNGROUPED1Sizer->Add(cmbTST_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkREV_CLKDAC_CGEN = new wxCheckBox(this, ID_REV_CLKDAC_CGEN, _("Invert DAC F_CLKL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_REV_CLKDAC_CGEN"));
chkREV_CLKDAC_CGEN->SetValue(false);
chkREV_CLKDAC_CGEN->SetToolTip(_("Inverts the clock F_CLKL"));
UNGROUPED1Sizer->Add(chkREV_CLKDAC_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkREV_CLKADC_CGEN = new wxCheckBox(this, ID_REV_CLKADC_CGEN, _("Invert ADC F_CLKL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_REV_CLKADC_CGEN"));
chkREV_CLKADC_CGEN->SetValue(false);
chkREV_CLKADC_CGEN->SetToolTip(_("Inverts the clock F_CLKL"));
UNGROUPED1Sizer->Add(chkREV_CLKADC_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkREVPH_PFD_CGEN = new wxCheckBox(this, ID_REVPH_PFD_CGEN, _("REVPH_PFD_CGEN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_REVPH_PFD_CGEN"));
chkREVPH_PFD_CGEN->SetValue(false);
chkREVPH_PFD_CGEN->SetToolTip(_("Reverse the pulses of PFD. It can be used to reverse the polarity of the PLL loop (positive feedback to negative feedback)"));
UNGROUPED1Sizer->Add(chkREVPH_PFD_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkCOARSE_START_CGEN = new wxCheckBox(this, ID_COARSE_START_CGEN, _("Signal coarse tuning algorithm"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COARSE_START_CGEN"));
chkCOARSE_START_CGEN->SetValue(false);
chkCOARSE_START_CGEN->SetToolTip(_("Control signal for coarse tuning algorithm (SX_SWC_calibration)"));
UNGROUPED1Sizer->Add(chkCOARSE_START_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("COARSE_STEPDONE_CGEN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
UNGROUPED1Sizer->Add(StaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblCOARSE_STEPDONE_CGEN = new wxStaticText(this, ID_COARSE_STEPDONE_CGEN, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_COARSE_STEPDONE_CGEN"));
UNGROUPED1Sizer->Add(lblCOARSE_STEPDONE_CGEN, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText5 = new wxStaticText(this, ID_STATICTEXT6, _("COARSEPLL_COMPO_CGEN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
UNGROUPED1Sizer->Add(StaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblCOARSEPLL_COMPO_CGEN = new wxStaticText(this, ID_COARSEPLL_COMPO_CGEN, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_COARSEPLL_COMPO_CGEN"));
UNGROUPED1Sizer->Add(lblCOARSEPLL_COMPO_CGEN, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnUpdateValues = new wxButton(this, ID_BUTTON1, _("Update ReadOnly values"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
UNGROUPED1Sizer->Add(btnUpdateValues, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
wxString __wxRadioBoxChoices_1[2] =
{
	_("Feedback divider"),
	_("Fref")
};
rgrSEL_SDMCLK_CGEN = new wxRadioBox(this, ID_SEL_SDMCLK_CGEN, _("Output for SDM"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_SEL_SDMCLK_CGEN"));
rgrSEL_SDMCLK_CGEN->SetSelection(0);
rgrSEL_SDMCLK_CGEN->SetToolTip(_("Selects between the feedback divider output and Fref for SDM"));
UNGROUPED1Sizer->Add(rgrSEL_SDMCLK_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
UNGROUPEDSizer->Add(UNGROUPED1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer5->Add(UNGROUPEDSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
PowerdowncontrolsSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Power down controls"));
Powerdowncontrols2Sizer = new wxFlexGridSizer(0, 2, 0, 0);
chkPD_CP_CGEN = new wxCheckBox(this, ID_PD_CP_CGEN, _("Charge pump"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_CP_CGEN"));
chkPD_CP_CGEN->SetValue(false);
chkPD_CP_CGEN->SetToolTip(_("Power down for Charge Pump"));
Powerdowncontrols2Sizer->Add(chkPD_CP_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_FDIV_FB_CGEN = new wxCheckBox(this, ID_PD_FDIV_FB_CGEN, _("Feedback frequency divider"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_FDIV_FB_CGEN"));
chkPD_FDIV_FB_CGEN->SetValue(false);
chkPD_FDIV_FB_CGEN->SetToolTip(_("Power down for feedback frequency divider"));
Powerdowncontrols2Sizer->Add(chkPD_FDIV_FB_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_FDIV_O_CGEN = new wxCheckBox(this, ID_PD_FDIV_O_CGEN, _("Frequency divider"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_FDIV_O_CGEN"));
chkPD_FDIV_O_CGEN->SetValue(false);
chkPD_FDIV_O_CGEN->SetToolTip(_("Power down for forward frequency divider of the CGEN block"));
Powerdowncontrols2Sizer->Add(chkPD_FDIV_O_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_SDM_CGEN = new wxCheckBox(this, ID_PD_SDM_CGEN, _("SDM"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_SDM_CGEN"));
chkPD_SDM_CGEN->SetValue(false);
chkPD_SDM_CGEN->SetToolTip(_("Power down for SDM"));
Powerdowncontrols2Sizer->Add(chkPD_SDM_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_VCO_CGEN = new wxCheckBox(this, ID_PD_VCO_CGEN, _("VCO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_VCO_CGEN"));
chkPD_VCO_CGEN->SetValue(false);
chkPD_VCO_CGEN->SetToolTip(_("Power down for VCO"));
Powerdowncontrols2Sizer->Add(chkPD_VCO_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_VCO_COMP_CGEN = new wxCheckBox(this, ID_PD_VCO_COMP_CGEN, _("VCO comparator"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_VCO_COMP_CGEN"));
chkPD_VCO_COMP_CGEN->SetValue(false);
chkPD_VCO_COMP_CGEN->SetToolTip(_("Power down for VCO comparator"));
Powerdowncontrols2Sizer->Add(chkPD_VCO_COMP_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_G_CGEN = new wxCheckBox(this, ID_EN_G_CGEN, _("Enable CLKGEN module"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_G_CGEN"));
chkEN_G_CGEN->SetValue(false);
chkEN_G_CGEN->SetToolTip(_("Enable control for all the CGEN power downs"));
Powerdowncontrols2Sizer->Add(chkEN_G_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
PowerdowncontrolsSizer->Add(Powerdowncontrols2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer5->Add(PowerdowncontrolsSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer1->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
VCOPLLSizer = new wxFlexGridSizer(0, 2, 0, 5);
VCOSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VCO"));
VCO4Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText17 = new wxStaticText(this, ID_STATICTEXT20, _("CSW_VCO_CGEN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
VCO4Sizer->Add(StaticText17, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
cmbCSW_VCO_CGEN = new ComboBoxMap(this, ID_CSW_VCO_CGEN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CSW_VCO_CGEN"));
VCO4Sizer->Add(cmbCSW_VCO_CGEN, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
StaticText8 = new wxStaticText(this, ID_STATICTEXT9, _("Scales VCO bias current"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
VCO4Sizer->Add(StaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbICT_VCO_CGEN = new ComboBoxMap(this, ID_ICT_VCO_CGEN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_VCO_CGEN"));
cmbICT_VCO_CGEN->SetToolTip(_("Scales the VCO bias current from 0 to 2.5xInom"));
VCO4Sizer->Add(cmbICT_VCO_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText10 = new wxStaticText(this, ID_STATICTEXT11, _("VCO_CMPHO_CGEN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
VCO4Sizer->Add(StaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblVCO_CMPHO_CGEN = new wxStaticText(this, ID_VCO_CMPHO_CGEN, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_VCO_CMPHO_CGEN"));
VCO4Sizer->Add(lblVCO_CMPHO_CGEN, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText11 = new wxStaticText(this, ID_STATICTEXT12, _("VCO_CMPLO_CGEN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
VCO4Sizer->Add(StaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblVCO_CMPLO_CGEN = new wxStaticText(this, ID_VCO_CMPLO_CGEN, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_VCO_CMPLO_CGEN"));
VCO4Sizer->Add(lblVCO_CMPLO_CGEN, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnReadCMP = new wxButton(this, ID_BUTTON2, _("Read VCO_CMP"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
VCO4Sizer->Add(btnReadCMP, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
btnShowVCO = new wxButton(this, ID_BUTTON5, _("VCO params"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
VCO4Sizer->Add(btnShowVCO, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
VCOSizer->Add(VCO4Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
VCOPLLSizer->Add(VCOSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
PLLfilterSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("PLL loop filter"));
PLLfilter5Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText12 = new wxStaticText(this, ID_STATICTEXT13, _("CP2"), wxDefaultPosition, wxSize(30,13), 0, _T("ID_STATICTEXT13"));
PLLfilter5Sizer->Add(StaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCP2_CGEN = new ComboBoxMap(this, ID_CP2_CGEN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CP2_CGEN"));
cmbCP2_CGEN->SetToolTip(_("Controls the value of CP2 (cap from CP output to GND) in the PLL filter"));
PLLfilter5Sizer->Add(cmbCP2_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText13 = new wxStaticText(this, ID_STATICTEXT14, _("CP3"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
PLLfilter5Sizer->Add(StaticText13, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCP3_CGEN = new ComboBoxMap(this, ID_CP3_CGEN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CP3_CGEN"));
cmbCP3_CGEN->SetToolTip(_("Controls the value of CP3 (cap from VCO Vtune input to GND) in the PLL filter"));
PLLfilter5Sizer->Add(cmbCP3_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText14 = new wxStaticText(this, ID_STATICTEXT15, _("CZ"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
PLLfilter5Sizer->Add(StaticText14, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCZ_CGEN = new ComboBoxMap(this, ID_CZ_CGEN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CZ_CGEN"));
cmbCZ_CGEN->SetToolTip(_("Controls the value of CZ (Zero capacitor) in the PLL filter"));
PLLfilter5Sizer->Add(cmbCZ_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
PLLfilterSizer->Add(PLLfilter5Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
VCOPLLSizer->Add(PLLfilterSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer2->Add(VCOPLLSizer, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
ChargepumpSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Charge pump"));
Chargepump6Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText15 = new wxStaticText(this, ID_STATICTEXT16, _("Scales offset current"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
Chargepump6Sizer->Add(StaticText15, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbIOFFSET_CP_CGEN = new ComboBoxMap(this, ID_IOFFSET_CP_CGEN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_IOFFSET_CP_CGEN"));
cmbIOFFSET_CP_CGEN->SetToolTip(_("Scales the offset current of the charge pump, 0-->63. This current is used in Fran-N mode to create an offset in the CP response and avoide the non-linear section"));
Chargepump6Sizer->Add(cmbIOFFSET_CP_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText16 = new wxStaticText(this, ID_STATICTEXT17, _("Scales pulse current"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
Chargepump6Sizer->Add(StaticText16, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbIPULSE_CP_CGEN = new ComboBoxMap(this, ID_IPULSE_CP_CGEN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_IPULSE_CP_CGEN"));
cmbIPULSE_CP_CGEN->SetToolTip(_("Scales the pulse current of the charge pump"));
Chargepump6Sizer->Add(cmbIPULSE_CP_CGEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
ChargepumpSizer->Add(Chargepump6Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(ChargepumpSizer, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer6 = new wxFlexGridSizer(0, 2, 0, 0);
StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Frequency"));
FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 10);
StaticText7 = new wxStaticText(this, ID_STATICTEXT10, _("CLK_H (MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
FlexGridSizer3->Add(StaticText7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText9 = new wxStaticText(this, ID_STATICTEXT18, _("CLKH_OV_CLKL"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
FlexGridSizer3->Add(StaticText9, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("CLK_L(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
FlexGridSizer3->Add(StaticText2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
txtFrequency = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
FlexGridSizer3->Add(txtFrequency, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
cmbCLKH_OV_CLKL_CGEN = new ComboBoxMap(this, ID_CLKH_OV_CLKL_CGEN, wxEmptyString, wxDefaultPosition, wxSize(48,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CLKH_OV_CLKL_CGEN"));
cmbCLKH_OV_CLKL_CGEN->SetToolTip(_("FCLKL here is ADC clock. FCLKH is the clock to the DAC and if no division is added to the ADC as well"));
FlexGridSizer3->Add(cmbCLKH_OV_CLKL_CGEN, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
txtFrequencyCLKL = new wxTextCtrl(this, ID_TEXTCTRL2, _("0"), wxDefaultPosition, wxSize(48,-1), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL2"));
txtFrequencyCLKL->Disable();
FlexGridSizer3->Add(txtFrequencyCLKL, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer2->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
btnCalculate = new wxButton(this, ID_BUTTON3, _("Calculate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
BoxSizer1->Add(btnCalculate, 1, wxRIGHT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
btnTune = new wxButton(this, ID_BUTTON4, _("Tune"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
BoxSizer1->Add(btnTune, 1, wxLEFT|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
StaticBoxSizer2->Add(BoxSizer1, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
FlexGridSizer6->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Calculated Values for Fractional Mode"));
FlexGridSizer4 = new wxFlexGridSizer(5, 2, 5, 10);
StaticText6 = new wxStaticText(this, ID_STATICTEXT7, _("N Integer:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
FlexGridSizer4->Add(StaticText6, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblINT_SDM = new wxStaticText(this, ID_STATICTEXT8, _("\?\?\?"), wxDefaultPosition, wxSize(91,13), 0, _T("ID_STATICTEXT8"));
FlexGridSizer4->Add(lblINT_SDM, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText20 = new wxStaticText(this, ID_STATICTEXT21, _("N Fractional:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
FlexGridSizer4->Add(StaticText20, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblFRAC_SDM = new wxStaticText(this, ID_STATICTEXT22, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
FlexGridSizer4->Add(lblFRAC_SDM, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("Divider:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
FlexGridSizer4->Add(StaticText1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblDivider = new wxStaticText(this, ID_STATICTEXT19, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
FlexGridSizer4->Add(lblDivider, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText24 = new wxStaticText(this, ID_STATICTEXT25, _("Output Freq, MHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
FlexGridSizer4->Add(StaticText24, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblRealOutFrequency = new wxStaticText(this, ID_STATICTEXT26, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
FlexGridSizer4->Add(lblRealOutFrequency, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText26 = new wxStaticText(this, ID_STATICTEXT27, _("VCO Freq, MHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
FlexGridSizer4->Add(StaticText26, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblVCOfreq = new wxStaticText(this, ID_STATICTEXT28, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
FlexGridSizer4->Add(lblVCOfreq, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer3->Add(FlexGridSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer6->Add(StaticBoxSizer3, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer2->Add(FlexGridSizer6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
btnChangeRefClk = new wxButton(this, ID_BUTTON6, _("Change reference clock"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
FlexGridSizer7->Add(btnChangeRefClk, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText18 = new wxStaticText(this, ID_STATICTEXT23, _("Reference clock(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
FlexGridSizer7->Add(StaticText18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
lblRefClk_MHz = new wxStaticText(this, ID_STATICTEXT24, _("\?\?\?"), wxDefaultPosition, wxSize(116,13), 0, _T("ID_STATICTEXT24"));
FlexGridSizer7->Add(lblRefClk_MHz, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer2->Add(FlexGridSizer7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_SPDUP_VCO_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_RESET_N_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_EN_COARSE_CKLGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_EN_INTONLY_SDM_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_EN_SDM_CLK_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_EN_SDM_TSTO_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_REV_SDMCLK_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_SX_DITHER_EN_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_EN_ADCCLKH_CLKGN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_TST_CGEN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_REV_CLKDAC_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_REV_CLKADC_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_REVPH_PFD_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_COARSE_START_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::OnbtnUpdateValuesClick);
Connect(ID_SEL_SDMCLK_CGEN,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_PD_CP_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_PD_FDIV_FB_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_PD_FDIV_O_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_PD_SDM_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_PD_VCO_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_PD_VCO_COMP_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_EN_G_CGEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_CSW_VCO_CGEN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_ICT_VCO_CGEN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::OnbtnReadCMPClick);
Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::OnbtnShowVCOClick);
Connect(ID_CP2_CGEN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_CP3_CGEN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_CZ_CGEN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_IOFFSET_CP_CGEN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_IPULSE_CP_CGEN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_CLKH_OV_CLKL_CGEN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlCLKGEN::ParameterChangeHandler);
Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::OnbtnCalculateClick);
Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::OnbtnTuneClick);
Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlCLKGEN::OnbtnChangeRefClkClick);
//*)
}
pnlCLKGEN::~pnlCLKGEN()
{
//(*Destroy(pnlCLKGEN)
//*)
}
void pnlCLKGEN::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlCLKGEN panel don't have control module assigned" << std::endl;
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

    double cgenFreq = 0;
    switch(parameter)
    {
    case CLKH_OV_CLKL_CGEN:
        lmsControl->SetParam( parameter, event.GetInt());
        txtFrequency->GetValue().ToDouble(&cgenFreq);
        txtFrequencyCLKL->SetValue( wxString::Format("%.3f", cgenFreq/pow(2.0, cmbCLKH_OV_CLKL_CGEN->GetSelection())));
        OnbtnCalculateClick(event); //clkl freq changed need to recalculate fref
    break;
    case EN_ADCCLKH_CLKGN:
        lmsControl->SetParam( parameter, event.GetInt());
        lmsControl->ReconfigureNCO(0, true);
        lmsControl->ReconfigureNCO(1, true);
        lmsControl->ReconfigureNCO(0, false);
        lmsControl->ReconfigureNCO(1, false);
        break;
    default:
        lmsControl->SetParam( parameter, event.GetInt());
    }
}

void pnlCLKGEN::Initialize(LMS7002_MainControl *pControl)
{
    vector<cmbKeyValuePair> keyvalues;
    lmsControl = pControl;
    char ctemp[80];
    vector<string> temp;
    temp.clear();
    keyvalues.push_back(cmbKeyValuePair(0,"1"));
    keyvalues.push_back(cmbKeyValuePair(1,"2"));
    keyvalues.push_back(cmbKeyValuePair(2,"4"));
    keyvalues.push_back(cmbKeyValuePair(3,"8"));
    cmbCLKH_OV_CLKL_CGEN->Clear();
    cmbCLKH_OV_CLKL_CGEN->Set(keyvalues);
    cmbCLKH_OV_CLKL_CGEN->SetSelection( lmsControl->GetParam(CLKH_OV_CLKL_CGEN));

    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%.3f pF", (i*6*63.2)/1000.0); temp.push_back(ctemp);}
    cmbCP2_CGEN->Clear();
    cmbCP2_CGEN->Append(temp);
    cmbCP2_CGEN->SetSelection( lmsControl->GetParam(CP2_CGEN));

    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%.3f pF", (i*248.0)/1000.0); temp.push_back(ctemp);}
    cmbCP3_CGEN->Clear();
    cmbCP3_CGEN->Append(temp);
    cmbCP3_CGEN->SetSelection( lmsControl->GetParam(CP3_CGEN));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbCSW_VCO_CGEN->Clear();
    cmbCSW_VCO_CGEN->Append(temp);
    cmbCSW_VCO_CGEN->SetSelection( lmsControl->GetParam(CSW_VCO_CGEN));

    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%.0f pF", (i*8*365.0)/1000.0); temp.push_back(ctemp);}
    cmbCZ_CGEN->Clear();
    cmbCZ_CGEN->Append(temp);
    cmbCZ_CGEN->SetSelection( lmsControl->GetParam(CZ_CGEN));

//    temp.clear();
//    for(int i=0; i<256; ++i)
//        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
//    cmbDIV_OUTCH_CGEN->Clear();
//    cmbDIV_OUTCH_CGEN->Append(temp);
//    cmbDIV_OUTCH_CGEN->SetSelection( lmsControl->GetParam(DIV_OUTCH_CGEN));

    temp.clear();
//    temp.push_back("FCLK_ADC=F_CLKH & FCLK_DAC=F_CLKL");
//    temp.push_back("FCLK_ADC=F_CLKL & FCLK_DAC=F_CLKH");
    temp.push_back("F_CLKH -> ADC");
    temp.push_back("F_CLKH -> DAC");
    cmbEN_ADCCLKH_CLKGN->Clear();
    cmbEN_ADCCLKH_CLKGN->Append(temp);
    cmbEN_ADCCLKH_CLKGN->SetSelection( lmsControl->GetParam(EN_ADCCLKH_CLKGN));

    temp.clear();
    for(int i=0; i<32; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_VCO_CGEN->Clear();
    cmbICT_VCO_CGEN->Append(temp);
    cmbICT_VCO_CGEN->SetSelection( lmsControl->GetParam(ICT_VCO_CGEN));

    temp.clear();
    for(int i=0; i<64; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbIOFFSET_CP_CGEN->Clear();
    cmbIOFFSET_CP_CGEN->Append(temp);
    cmbIOFFSET_CP_CGEN->SetSelection( lmsControl->GetParam(IOFFSET_CP_CGEN));

    temp.clear();
    for(int i=0; i<64; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbIPULSE_CP_CGEN->Clear();
    cmbIPULSE_CP_CGEN->Append(temp);
    cmbIPULSE_CP_CGEN->SetSelection( lmsControl->GetParam(IPULSE_CP_CGEN));

    keyvalues.clear();
    keyvalues.push_back(cmbKeyValuePair(0,"TST disabled"));
    keyvalues.push_back(cmbKeyValuePair(1,"TST[0]=ADC clk; TST[1]=DAC clk; TSTA=Hi Z"));
    keyvalues.push_back(cmbKeyValuePair(2,"TST[0]=SDM clk; TST[1]=FBD output; TSTA=Vtune@60kOhm"));
    keyvalues.push_back(cmbKeyValuePair(3,"TST[0]=Ref clk; TST[1]=FBD output; TSTA=Vtune@10kOhm"));
    keyvalues.push_back(cmbKeyValuePair(4,"TST[0]=Hi Z; TST[1]=Hi Z; TSTA=Hi Z"));
    keyvalues.push_back(cmbKeyValuePair(5,"TST[0]=CP Down offset; TST[1]=CP Up offset; TSTA=Hi Z"));
    keyvalues.push_back(cmbKeyValuePair(6,"TST[0]=Hi Z; TST[1]=Hi Z; TSTA=Vtune@60kOhm"));
    keyvalues.push_back(cmbKeyValuePair(7,"TST[0]=Hi Z; TST[1]=Hi Z; TSTA=Vtune@10kOhm"));
    cmbTST_CGEN->Clear();
    cmbTST_CGEN->Set(keyvalues);
    cmbTST_CGEN->SetSelection( lmsControl->GetParam(TST_CGEN));
    UpdateTooltips(this);

    wxString freq = wxString::Format("%f", lmsControl->GetFrequencyCGEN());
    char ctempp[1024];
    sprintf(ctempp, "%s", freq.ToStdString().c_str());
    txtFrequency->SetValue(freq);
    lblRefClk_MHz->SetLabel(wxString::Format("%f", lmsControl->GetReferenceFrequencyCGEN()));

    wxCommandEvent evt;
    OnbtnCalculateClick(evt); //updates NCO reference clocks
}

void pnlCLKGEN::UpdateGUI()
{
    txtFrequency->SetLabel(wxString::Format("%f", lmsControl->GetFrequencyCGEN()));
    lblRefClk_MHz->SetLabel(wxString::Format("%f", lmsControl->GetReferenceFrequencyCGEN()));

    long value = 0;
    value = lmsControl->GetParam(CLKH_OV_CLKL_CGEN);
    cmbCLKH_OV_CLKL_CGEN->SetSelection(value);

    value = lmsControl->GetParam(COARSE_START_CGEN);
    chkCOARSE_START_CGEN->SetValue(value);

    value = lmsControl->GetParam(CP2_CGEN);
    cmbCP2_CGEN->SetSelection(value);

    value = lmsControl->GetParam(CP3_CGEN);
    cmbCP3_CGEN->SetSelection(value);

    value = lmsControl->GetParam(CSW_VCO_CGEN);
    cmbCSW_VCO_CGEN->SetSelection(value);

    value = lmsControl->GetParam(CZ_CGEN);
    cmbCZ_CGEN->SetSelection(value);

//    value = lmsControl->GetParam(DIV_OUTCH_CGEN);
//    cmbDIV_OUTCH_CGEN->SetSelection(value);

    value = lmsControl->GetParam(EN_COARSE_CKLGEN);
    chkEN_COARSE_CKLGEN->SetValue(value);

    value = lmsControl->GetParam(EN_ADCCLKH_CLKGN);
    cmbEN_ADCCLKH_CLKGN->SetSelection(value);

    value = lmsControl->GetParam(EN_G_CGEN);
    chkEN_G_CGEN->SetValue(value);

    value = lmsControl->GetParam(EN_INTONLY_SDM_CGEN);
    chkEN_INTONLY_SDM_CGEN->SetValue(value);

    value = lmsControl->GetParam(EN_SDM_CLK_CGEN);
    chkEN_SDM_CLK_CGEN->SetValue(value);

    value = lmsControl->GetParam(EN_SDM_TSTO_CGEN);
    chkEN_SDM_TSTO_CGEN->SetValue(value);

    //value = lmsControl->GetParam(FRAC_SDM_CGEN);
    //cmbFRAC_SDM_CGEN->SetSelection(value);

    value = lmsControl->GetParam(ICT_VCO_CGEN);
    cmbICT_VCO_CGEN->SetSelection(value);

    //value = lmsControl->GetParam(INT_SDM_CGEN);
    //cmbINT_SDM_CGEN->SetSelection(value);

    value = lmsControl->GetParam(IOFFSET_CP_CGEN);
    cmbIOFFSET_CP_CGEN->SetSelection(value);

    value = lmsControl->GetParam(IPULSE_CP_CGEN);
    cmbIPULSE_CP_CGEN->SetSelection(value);

    value = lmsControl->GetParam(PD_CP_CGEN);
    chkPD_CP_CGEN->SetValue(value);

    value = lmsControl->GetParam(PD_FDIV_FB_CGEN);
    chkPD_FDIV_FB_CGEN->SetValue(value);

    value = lmsControl->GetParam(PD_FDIV_O_CGEN);
    chkPD_FDIV_O_CGEN->SetValue(value);

    value = lmsControl->GetParam(PD_SDM_CGEN);
    chkPD_SDM_CGEN->SetValue(value);

    value = lmsControl->GetParam(PD_VCO_CGEN);
    chkPD_VCO_CGEN->SetValue(value);

    value = lmsControl->GetParam(PD_VCO_COMP_CGEN);
    chkPD_VCO_COMP_CGEN->SetValue(value);

    value = lmsControl->GetParam(RESET_N_CGEN);
    chkRESET_N_CGEN->SetValue(value);

    value = lmsControl->GetParam(REVPH_PFD_CGEN);
    chkREVPH_PFD_CGEN->SetValue(value);

    value = lmsControl->GetParam(REV_CLKADC_CGEN);
    chkREV_CLKADC_CGEN->SetValue(value);

    value = lmsControl->GetParam(REV_CLKDAC_CGEN);
    chkREV_CLKDAC_CGEN->SetValue(value);

    value = lmsControl->GetParam(REV_SDMCLK_CGEN);
    chkREV_SDMCLK_CGEN->SetValue(value);

    value = lmsControl->GetParam(SEL_SDMCLK_CGEN);
    rgrSEL_SDMCLK_CGEN->SetSelection(value);

    value = lmsControl->GetParam(SPDUP_VCO_CGEN);
    chkSPDUP_VCO_CGEN->SetValue(value);

    value = lmsControl->GetParam(SX_DITHER_EN_CGEN);
    chkSX_DITHER_EN_CGEN->SetValue(value);

    value = lmsControl->GetParam(TST_CGEN);
    cmbTST_CGEN->SetSelection(value);
}

void pnlCLKGEN::UpdateReadOnlyValues()
{
    int param;
    param = lmsControl->GetParam(COARSE_STEPDONE, true, true);
    lblCOARSE_STEPDONE_CGEN->SetLabel(wxString::Format("%i", param));

    param = lmsControl->GetParam(COARSEPLL_COMPO_CGEN, true, true);
    lblCOARSEPLL_COMPO_CGEN->SetLabel(wxString::Format("%i", param));
}


void pnlCLKGEN::OnbtnUpdateValuesClick(wxCommandEvent& event)
{
    UpdateReadOnlyValues();
}

void pnlCLKGEN::OnbtnReadCMPClick(wxCommandEvent& event)
{
    int param;
    param = lmsControl->GetParam(VCO_CMPHO_CGEN, true, true);
    lblVCO_CMPHO_CGEN->SetLabel(wxString::Format("%i", param));

    param = lmsControl->GetParam(VCO_CMPLO_CGEN, true, true);
    lblVCO_CMPLO_CGEN->SetLabel(wxString::Format("%i", param));
}

void pnlCLKGEN::OnbtnTuneClick(wxCommandEvent& event)
{
    double freq;
    txtFrequency->GetValue().ToDouble(&freq);
    lmsControl->algorithms->VCO_Tuning_CGEN();
    lmsControl->GetParam(CSW_VCO_CGEN, true, true);
    UpdateGUI();
}

void pnlCLKGEN::OnbtnCalculateClick(wxCommandEvent& event)
{
    double desFreq_MHz, realFreq_MHz, Fvco;
    unsigned Nint, Nfrac, iHDiv;
    txtFrequency->GetValue().ToDouble(&desFreq_MHz);
    if( lmsControl->SetFrequencyCGEN(desFreq_MHz, realFreq_MHz, Nint, Nfrac, Fvco, iHDiv) )
    {
        lblINT_SDM->SetLabel(wxString::Format("%i", Nint));
        lblFRAC_SDM->SetLabel(wxString::Format("%i", Nfrac));
        lblDivider->SetLabel(wxString::Format("%i", iHDiv));
        lblRealOutFrequency->SetLabel(wxString::Format("%1.6f", realFreq_MHz));
        lblVCOfreq->SetLabel(wxString::Format("%1.6f", Fvco));
        int dMul;
        dMul = cmbCLKH_OV_CLKL_CGEN->GetSelection();
        double clklfreq = realFreq_MHz/pow(2.0, dMul);
        txtFrequencyCLKL->SetLabel( wxString::Format("%.3f", clklfreq));

        double clkDAC = 0;
        double clkADC = 0;
        if(lmsControl->GetParam(EN_ADCCLKH_CLKGN) == 0)
        {
            clkDAC = clklfreq;
            clkADC = realFreq_MHz;
        }
        else
        {
            clkDAC = realFreq_MHz;
            clkADC = clklfreq;
        }
        lmsControl->SetReferenceFrequencyNCO(clkDAC, false);
        lmsControl->SetReferenceFrequencyNCO(clkADC/4.0, true);
        if(lmsControl->getSerPort()->IsOpen() == true)
        {
            lmsControl->ReconfigureNCO(0, true);
            lmsControl->ReconfigureNCO(1, true);
            lmsControl->ReconfigureNCO(0, false);
            lmsControl->ReconfigureNCO(1, false);
        }
        lmsControl->Notify(LMS_Message(MSG_CGEN_FREQUENCY_CHANGED, "", 0, 0));
    }
    else
    {
        wxMessageBox("Cannot deliver desired frequency", "ERROR");
    }
}

void pnlCLKGEN::OnbtnShowVCOClick(wxCommandEvent& event)
{
    dlgVCO_SX dlg(lmsControl->getPLL_SX(), lmsControl->getPLL_CGEN(), this);
    dlg.ShowModal();
}

void pnlCLKGEN::OnbtnChangeRefClkClick(wxCommandEvent& event)
{
    dlgFloatInput dlg(this, "Reference clock", "Enter reference clock (MHz):", lmsControl->GetReferenceFrequencyCGEN() );
    if( dlg.ShowModal() == wxID_OK)
    {
        lmsControl->SetReferenceFrequencyCGEN(dlg.GetValue());
        lblRefClk_MHz->SetLabel(wxString::Format("%f", lmsControl->GetReferenceFrequencyCGEN()));
    }
}

void pnlCLKGEN::OnbtnTuneCoarseClick(wxCommandEvent& event)
{
    double freq;
    txtFrequency->GetValue().ToDouble(&freq);
    lmsControl->algorithms->VCO_CoarseTuning_CGEN(lmsControl->GetReferenceFrequencyPLL(false), freq);
    lmsControl->GetParam(CSW_VCO_CGEN, true, true);
    UpdateGUI();
}
