/**
@file	pnlSXT.cpp
@author	Lime Microsystems
@brief	SXR/SXT module panel
*/

#include "pnlSXT.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "LMS7002_MainControl.h"
#include "dlgVCO_SX.h"
#include "dlgFloatInput.h"
//(*InternalHeaders(pnlSXT)
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
//(*IdInit(pnlSXT)
const long pnlSXT::ID_STATICTEXT4 = wxNewId();
const long pnlSXT::ID_PW_DIV2_LOCH = wxNewId();
const long pnlSXT::ID_STATICTEXT5 = wxNewId();
const long pnlSXT::ID_PW_DIV4_LOCH = wxNewId();
const long pnlSXT::ID_STATICTEXT6 = wxNewId();
const long pnlSXT::ID_DIV_LOCH = wxNewId();
const long pnlSXT::ID_PD_FBDIV = wxNewId();
const long pnlSXT::ID_PD_LOCH_T2RBUF = wxNewId();
const long pnlSXT::ID_PD_CP = wxNewId();
const long pnlSXT::ID_PD_FDIV = wxNewId();
const long pnlSXT::ID_PD_SDM = wxNewId();
const long pnlSXT::ID_PD_VCO_COMP = wxNewId();
const long pnlSXT::ID_PD_VCO = wxNewId();
const long pnlSXT::ID_EN_G = wxNewId();
const long pnlSXT::ID_EN_DIR_SXRSXT = wxNewId();
const long pnlSXT::ID_SEL_VCO = wxNewId();
const long pnlSXT::ID_BUTTON4 = wxNewId();
const long pnlSXT::ID_STATICTEXT16 = wxNewId();
const long pnlSXT::ID_VCO_CMPHO = wxNewId();
const long pnlSXT::ID_STATICTEXT17 = wxNewId();
const long pnlSXT::ID_VCO_CMPLO = wxNewId();
const long pnlSXT::ID_BUTTON1 = wxNewId();
const long pnlSXT::ID_STATICTEXT9 = wxNewId();
const long pnlSXT::ID_VDIV_VCO = wxNewId();
const long pnlSXT::ID_STATICTEXT10 = wxNewId();
const long pnlSXT::ID_ICT_VCO = wxNewId();
const long pnlSXT::ID_BUTTON6 = wxNewId();
const long pnlSXT::ID_STATICTEXT14 = wxNewId();
const long pnlSXT::ID_STATICTEXT15 = wxNewId();
const long pnlSXT::ID_RESET_N = wxNewId();
const long pnlSXT::ID_SPDUP_VCO = wxNewId();
const long pnlSXT::ID_BYPLDO_VCO = wxNewId();
const long pnlSXT::ID_EN_COARSEPLL = wxNewId();
const long pnlSXT::ID_CURLIM_VCO = wxNewId();
const long pnlSXT::ID_REVPH_PFD = wxNewId();
const long pnlSXT::ID_EN_INTONLY_SDM = wxNewId();
const long pnlSXT::ID_EN_SDM_CLK = wxNewId();
const long pnlSXT::ID_EN_SDM_TSTO_SXR = wxNewId();
const long pnlSXT::ID_EN_SDM_TSTO_SXT = wxNewId();
const long pnlSXT::ID_REV_SDMCLK = wxNewId();
const long pnlSXT::ID_SX_DITHER_EN = wxNewId();
const long pnlSXT::ID_STATICTEXT29 = wxNewId();
const long pnlSXT::ID_EN_DIV2_DIVPROGenabled = wxNewId();
const long pnlSXT::ID_STATICTEXT7 = wxNewId();
const long pnlSXT::ID_TST_SX = wxNewId();
const long pnlSXT::ID_STATICTEXT8 = wxNewId();
const long pnlSXT::ID_SEL_SDMCLK = wxNewId();
const long pnlSXT::ID_STATICTEXT11 = wxNewId();
const long pnlSXT::ID_RSEL_LDO_VCO = wxNewId();
const long pnlSXT::ID_STATICTEXT12 = wxNewId();
const long pnlSXT::ID_IOFFSET_CP = wxNewId();
const long pnlSXT::ID_STATICTEXT13 = wxNewId();
const long pnlSXT::ID_IPULSE_CP = wxNewId();
const long pnlSXT::ID_STATICTEXT1 = wxNewId();
const long pnlSXT::ID_CSW_VCO = wxNewId();
const long pnlSXT::ID_STATICTEXT18 = wxNewId();
const long pnlSXT::ID_CP2_PLL = wxNewId();
const long pnlSXT::ID_STATICTEXT19 = wxNewId();
const long pnlSXT::ID_CP3_PLL = wxNewId();
const long pnlSXT::ID_STATICTEXT20 = wxNewId();
const long pnlSXT::ID_CZ = wxNewId();
const long pnlSXT::ID_TEXTCTRL1 = wxNewId();
const long pnlSXT::ID_BUTTON2 = wxNewId();
const long pnlSXT::ID_BUTTON3 = wxNewId();
const long pnlSXT::ID_BUTTON5 = wxNewId();
const long pnlSXT::ID_STATICTEXT2 = wxNewId();
const long pnlSXT::ID_STATICTEXT3 = wxNewId();
const long pnlSXT::ID_STATICTEXT21 = wxNewId();
const long pnlSXT::ID_STATICTEXT22 = wxNewId();
const long pnlSXT::ID_STATICTEXT23 = wxNewId();
const long pnlSXT::ID_STATICTEXT24 = wxNewId();
const long pnlSXT::ID_STATICTEXT25 = wxNewId();
const long pnlSXT::ID_STATICTEXT26 = wxNewId();
const long pnlSXT::ID_STATICTEXT27 = wxNewId();
const long pnlSXT::ID_STATICTEXT28 = wxNewId();
const long pnlSXT::ID_STATICTEXT30 = wxNewId();
const long pnlSXT::ID_EN_DIV2_DIVPROG = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlSXT,wxPanel)
//(*EventTable(pnlSXT)
//*)
END_EVENT_TABLE()

void pnlSXT::AssignEnumsToIds()
{
    wndId2Enum[ID_BYPLDO_VCO] = BYPLDO_VCO;
    wndId2Enum[ID_CP2_PLL] = CP2_PLL;
    wndId2Enum[ID_CP3_PLL] = CP3_PLL;
    wndId2Enum[ID_CSW_VCO] = CSW_VCO;
    wndId2Enum[ID_CURLIM_VCO] = CURLIM_VCO;
    wndId2Enum[ID_CZ] = CZ;
    wndId2Enum[ID_DIV_LOCH] = DIV_LOCH;
    wndId2Enum[ID_EN_COARSEPLL] = EN_COARSEPLL;
    wndId2Enum[ID_EN_DIV2_DIVPROG] = EN_DIV2_DIVPROG;
    wndId2Enum[ID_EN_G] = EN_G;
    wndId2Enum[ID_EN_INTONLY_SDM] = EN_INTONLY_SDM;
    wndId2Enum[ID_EN_SDM_CLK] = EN_SDM_CLK;    
    wndId2Enum[ID_ICT_VCO] = ICT_VCO;
    wndId2Enum[ID_IOFFSET_CP] = IOFFSET_CP;
    wndId2Enum[ID_IPULSE_CP] = IPULSE_CP;
    wndId2Enum[ID_PD_CP] = PD_CP;
    wndId2Enum[ID_PD_FDIV] = PD_FDIV;
    wndId2Enum[ID_PD_LOCH_T2RBUF] = PD_LOCH_T2RBUF;
    wndId2Enum[ID_PD_SDM] = PD_SDM;
    wndId2Enum[ID_PD_VCO] = PD_VCO;
    wndId2Enum[ID_PD_VCO_COMP] = PD_VCO_COMP;
    wndId2Enum[ID_PW_DIV2_LOCH] = PW_DIV2_LOCH;
    wndId2Enum[ID_PW_DIV4_LOCH] = PW_DIV4_LOCH;
    wndId2Enum[ID_RESET_N] = RESET_N;
    wndId2Enum[ID_REVPH_PFD] = REVPH_PFD;
    wndId2Enum[ID_REV_SDMCLK] = REV_SDMCLK;
    wndId2Enum[ID_RSEL_LDO_VCO] = RSEL_LDO_VCO;
    wndId2Enum[ID_SEL_SDMCLK] = SEL_SDMCLK;
    wndId2Enum[ID_SEL_VCO] = SEL_VCO;
    wndId2Enum[ID_SPDUP_VCO] = SPDUP_VCO;
    wndId2Enum[ID_SX_DITHER_EN] = SX_DITHER_EN;
    wndId2Enum[ID_TST_SX] = TST_SX;
    wndId2Enum[ID_VDIV_VCO] = VDIV_VCO;
    wndId2Enum[ID_PD_FBDIV] = PD_FBDIV;
    wndId2Enum[ID_EN_DIR_SXRSXT] = EN_DIR_SXRSXT;
    wndId2Enum[ID_EN_SDM_TSTO_SXR] = EN_SDM_TSTO_SXR;
    wndId2Enum[ID_EN_SDM_TSTO_SXT] = EN_SDM_TSTO_SXT;
}

pnlSXT::pnlSXT(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlSXT::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlSXT)
wxStaticBoxSizer* StaticBoxSizer2;
wxFlexGridSizer* Divisionratio2Sizer;
wxFlexGridSizer* FlexGridSizer4;
wxStaticBoxSizer* VCOSizer;
wxStaticBoxSizer* DivisionratioSizer;
wxStaticBoxSizer* StaticBoxSizer4;
wxFlexGridSizer* FlexGridSizer3;
wxFlexGridSizer* FlexGridSizer5;
wxStaticBoxSizer* SXTcontrolsSizer;
wxFlexGridSizer* VCO1Sizer;
wxFlexGridSizer* FlexGridSizer2;
wxFlexGridSizer* FlexGridSizer7;
wxStaticBoxSizer* StaticBoxSizer3;
wxFlexGridSizer* FlexGridSizer8;
wxFlexGridSizer* SXTcontrols4Sizer;
wxFlexGridSizer* Powerdowncontrols3Sizer;
wxStaticBoxSizer* PowerdowncontrolsSizer;
wxFlexGridSizer* FlexGridSizer6;
wxStaticBoxSizer* StaticBoxSizer1;
wxFlexGridSizer* FlexGridSizer1;
wxStaticBoxSizer* StaticBoxSizer5;

Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
DivisionratioSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Division ratio"));
Divisionratio2Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Trim duty cycle of DIV2 LOCH"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
Divisionratio2Sizer->Add(StaticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbPW_DIV2_LOCH = new ComboBoxMap(this, ID_PW_DIV2_LOCH, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_PW_DIV2_LOCH"));
cmbPW_DIV2_LOCH->SetToolTip(_("trims the duty cycle of DIV2 LOCH. Only works when forward divider is dividing by at least 2 (excluding quadrature block division). If in bypass mode, this does not work"));
Divisionratio2Sizer->Add(cmbPW_DIV2_LOCH, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("Trim duty cycle of DIV4 LOCH"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
Divisionratio2Sizer->Add(StaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbPW_DIV4_LOCH = new ComboBoxMap(this, ID_PW_DIV4_LOCH, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_PW_DIV4_LOCH"));
cmbPW_DIV4_LOCH->SetToolTip(_("trims the duty cycle of DIV4 LOCH. Only works when forward divider is dividing by at least 4 (excluding quadrature block division). If in bypass mode, this does not work"));
Divisionratio2Sizer->Add(cmbPW_DIV4_LOCH, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText5 = new wxStaticText(this, ID_STATICTEXT6, _("LOCH_DIV division ratio"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
Divisionratio2Sizer->Add(StaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbDIV_LOCH = new ComboBoxMap(this, ID_DIV_LOCH, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DIV_LOCH"));
cmbDIV_LOCH->SetToolTip(_("Controls the division ratio in the LOCH_DIV"));
Divisionratio2Sizer->Add(cmbDIV_LOCH, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
DivisionratioSizer->Add(Divisionratio2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(DivisionratioSizer, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
PowerdowncontrolsSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Power down controls"));
Powerdowncontrols3Sizer = new wxFlexGridSizer(0, 1, 0, 0);
chkPD_FBDIV = new wxCheckBox(this, ID_PD_FBDIV, _("Feedback divider block"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_FBDIV"));
chkPD_FBDIV->SetValue(false);
chkPD_FBDIV->SetToolTip(_("Power down the feedback divider block"));
Powerdowncontrols3Sizer->Add(chkPD_FBDIV, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
chkPD_LOCH_T2RBUF = new wxCheckBox(this, ID_PD_LOCH_T2RBUF, _("LO buffer from SXT to SXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_LOCH_T2RBUF"));
chkPD_LOCH_T2RBUF->SetValue(false);
chkPD_LOCH_T2RBUF->SetToolTip(_("Power down for LO buffer from SXT to SXR. To be active only in the TDD mode"));
Powerdowncontrols3Sizer->Add(chkPD_LOCH_T2RBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_CP = new wxCheckBox(this, ID_PD_CP, _("Charge pump"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_CP"));
chkPD_CP->SetValue(false);
chkPD_CP->SetToolTip(_("Power down for Charge Pump"));
Powerdowncontrols3Sizer->Add(chkPD_CP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_FDIV = new wxCheckBox(this, ID_PD_FDIV, _("Forward frequency divider and divider chain of LO chain"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_FDIV"));
chkPD_FDIV->SetValue(false);
chkPD_FDIV->SetToolTip(_("Power down for feedback frequency and forward dividers"));
Powerdowncontrols3Sizer->Add(chkPD_FDIV, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_SDM = new wxCheckBox(this, ID_PD_SDM, _("SDM"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_SDM"));
chkPD_SDM->SetValue(false);
chkPD_SDM->SetToolTip(_("Power down for SDM"));
Powerdowncontrols3Sizer->Add(chkPD_SDM, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_VCO_COMP = new wxCheckBox(this, ID_PD_VCO_COMP, _("VCO comparator"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_VCO_COMP"));
chkPD_VCO_COMP->SetValue(false);
chkPD_VCO_COMP->SetToolTip(_("Power down for VCO comparator"));
Powerdowncontrols3Sizer->Add(chkPD_VCO_COMP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_VCO = new wxCheckBox(this, ID_PD_VCO, _("VCO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_VCO"));
chkPD_VCO->SetValue(false);
chkPD_VCO->SetToolTip(_("Power down for VCO"));
Powerdowncontrols3Sizer->Add(chkPD_VCO, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_G = new wxCheckBox(this, ID_EN_G, _("Enable SXR/SXT module"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_G"));
chkEN_G->SetValue(false);
chkEN_G->SetToolTip(_("Enable control for all the SXT power downs"));
Powerdowncontrols3Sizer->Add(chkEN_G, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Direct control"));
chkEN_DIR_SXRSXT = new wxCheckBox(this, ID_EN_DIR_SXRSXT, _("Enable direct control of PDs and ENs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_DIR_SXRSXT"));
chkEN_DIR_SXRSXT->SetValue(false);
chkEN_DIR_SXRSXT->SetToolTip(_("Enables direct control of PDs and ENs for SXR/SXT module"));
StaticBoxSizer4->Add(chkEN_DIR_SXRSXT, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
Powerdowncontrols3Sizer->Add(StaticBoxSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
PowerdowncontrolsSizer->Add(Powerdowncontrols3Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
FlexGridSizer2->Add(PowerdowncontrolsSizer, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
VCOSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("VCO"));
VCO1Sizer = new wxFlexGridSizer(0, 1, 0, 0);
wxString __wxRadioBoxChoices_1[3] =
{
	_("VCOL"),
	_("VCOM"),
	_("VCOH")
};
rgrSEL_VCO = new wxRadioBox(this, ID_SEL_VCO, _("Active VCO"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_SEL_VCO"));
rgrSEL_VCO->SetSelection(0);
rgrSEL_VCO->SetToolTip(_("Selects the active VCO. It is set by SX_SWC_calibration"));
VCO1Sizer->Add(rgrSEL_VCO, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnShowVCO = new wxButton(this, ID_BUTTON4, _("VCO params"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
VCO1Sizer->Add(btnShowVCO, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
VCOSizer->Add(VCO1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("VCO Comparators"));
FlexGridSizer3 = new wxFlexGridSizer(0, 4, 0, 0);
FlexGridSizer3->AddGrowableRow(0);
StaticText15 = new wxStaticText(this, ID_STATICTEXT16, _("High:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
FlexGridSizer3->Add(StaticText15, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblVCO_CMPHO = new wxStaticText(this, ID_VCO_CMPHO, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_VCO_CMPHO"));
FlexGridSizer3->Add(lblVCO_CMPHO, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText16 = new wxStaticText(this, ID_STATICTEXT17, _("Low:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
FlexGridSizer3->Add(StaticText16, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 10);
lblVCO_CMPLO = new wxStaticText(this, ID_VCO_CMPLO, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_VCO_CMPLO"));
FlexGridSizer3->Add(lblVCO_CMPLO, 0, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer2->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
btnUpdateValues = new wxButton(this, ID_BUTTON1, _("Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
StaticBoxSizer2->Add(btnUpdateValues, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
VCOSizer->Add(StaticBoxSizer2, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
StaticText8 = new wxStaticText(this, ID_STATICTEXT9, _("VCO LDO output voltage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
FlexGridSizer5->Add(StaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbVDIV_VCO = new ComboBoxMap(this, ID_VDIV_VCO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VDIV_VCO"));
cmbVDIV_VCO->SetToolTip(_("Controls VCO LDO output voltage"));
FlexGridSizer5->Add(cmbVDIV_VCO, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText9 = new wxStaticText(this, ID_STATICTEXT10, _("Scales VCO bias current"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
FlexGridSizer5->Add(StaticText9, 0, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
cmbICT_VCO = new ComboBoxMap(this, ID_ICT_VCO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ICT_VCO"));
cmbICT_VCO->SetToolTip(_("Scales the VCO bias current from 0 to 2.5xInom"));
FlexGridSizer5->Add(cmbICT_VCO, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
VCOSizer->Add(FlexGridSizer5, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer2->Add(VCOSizer, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer8 = new wxFlexGridSizer(0, 3, 0, 0);
btnChangeRefClk = new wxButton(this, ID_BUTTON6, _("Change reference clock"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
FlexGridSizer8->Add(btnChangeRefClk, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText13 = new wxStaticText(this, ID_STATICTEXT14, _("Reference clock(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
FlexGridSizer8->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
lblRefClk_MHz = new wxStaticText(this, ID_STATICTEXT15, _("\?\?\?"), wxDefaultPosition, wxSize(116,13), 0, _T("ID_STATICTEXT15"));
FlexGridSizer8->Add(lblRefClk_MHz, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer2->Add(FlexGridSizer8, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
SXTcontrolsSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("SXT/SXR controls"));
SXTcontrols4Sizer = new wxFlexGridSizer(0, 2, 0, 0);
chkRESET_N = new wxCheckBox(this, ID_RESET_N, _("Reset SX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RESET_N"));
chkRESET_N->SetValue(false);
chkRESET_N->SetToolTip(_("Resets SX. A pulse should be used in the start-up to reset"));
SXTcontrols4Sizer->Add(chkRESET_N, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_VCO = new wxCheckBox(this, ID_SPDUP_VCO, _("Bypass noise filter resistor"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_VCO"));
chkSPDUP_VCO->SetValue(false);
chkSPDUP_VCO->SetToolTip(_("Bypasses the noise filter resistor for fast settling time. It should be connected to a 1uS pulse"));
SXTcontrols4Sizer->Add(chkSPDUP_VCO, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYPLDO_VCO = new wxCheckBox(this, ID_BYPLDO_VCO, _("Bypass SX LDO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYPLDO_VCO"));
chkBYPLDO_VCO->SetValue(false);
chkBYPLDO_VCO->SetToolTip(_("Controls the bypass signal for the SX LDO"));
SXTcontrols4Sizer->Add(chkBYPLDO_VCO, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_COARSEPLL = new wxCheckBox(this, ID_EN_COARSEPLL, _("Enable coarse tuning"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_COARSEPLL"));
chkEN_COARSEPLL->SetValue(false);
chkEN_COARSEPLL->SetToolTip(_("Enable signal for coarse tuning block"));
SXTcontrols4Sizer->Add(chkEN_COARSEPLL, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkCURLIM_VCO = new wxCheckBox(this, ID_CURLIM_VCO, _("Enable current limit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CURLIM_VCO"));
chkCURLIM_VCO->SetValue(false);
chkCURLIM_VCO->SetToolTip(_("Enables the output current limitation in the VCO regulator"));
SXTcontrols4Sizer->Add(chkCURLIM_VCO, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkREVPH_PFD = new wxCheckBox(this, ID_REVPH_PFD, _("Reverse pulses of PFD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_REVPH_PFD"));
chkREVPH_PFD->SetValue(false);
chkREVPH_PFD->SetToolTip(_("Reverse the pulses of PFD. It can be used to reverse the polarity of the PLL loop (positive feedback to negative feedback)"));
SXTcontrols4Sizer->Add(chkREVPH_PFD, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_INTONLY_SDM = new wxCheckBox(this, ID_EN_INTONLY_SDM, _("Enable INTEGER_N mode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_INTONLY_SDM"));
chkEN_INTONLY_SDM->SetValue(false);
chkEN_INTONLY_SDM->SetToolTip(_("Enables INTEGER-N mode of the SX "));
SXTcontrols4Sizer->Add(chkEN_INTONLY_SDM, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_SDM_CLK = new wxCheckBox(this, ID_EN_SDM_CLK, _("Enable SDM clock"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_SDM_CLK"));
chkEN_SDM_CLK->SetValue(false);
chkEN_SDM_CLK->SetToolTip(_("Enables/Disables SDM clock. In INT-N mode or for noise testing, SDM clock can be disabled"));
SXTcontrols4Sizer->Add(chkEN_SDM_CLK, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_SDM_TSTO_SXR = new wxCheckBox(this, ID_EN_SDM_TSTO_SXR, _("Enambe SDM_TSTO_SXR outputs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_SDM_TSTO_SXR"));
chkEN_SDM_TSTO_SXR->SetValue(false);
chkEN_SDM_TSTO_SXR->SetToolTip(_("Enables the SDM_TSTO_SXR"));
SXTcontrols4Sizer->Add(chkEN_SDM_TSTO_SXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_SDM_TSTO_SXT = new wxCheckBox(this, ID_EN_SDM_TSTO_SXT, _("Enable SDM_TSTO_SXT outputs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_SDM_TSTO_SXT"));
chkEN_SDM_TSTO_SXT->SetValue(false);
chkEN_SDM_TSTO_SXT->SetToolTip(_("Enables the SDM_TSTO_SXT"));
SXTcontrols4Sizer->Add(chkEN_SDM_TSTO_SXT, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
chkREV_SDMCLK = new wxCheckBox(this, ID_REV_SDMCLK, _("Reverse SDM clock"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_REV_SDMCLK"));
chkREV_SDMCLK->SetValue(false);
chkREV_SDMCLK->SetToolTip(_("Reverses the SDM clock"));
SXTcontrols4Sizer->Add(chkREV_SDMCLK, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSX_DITHER_EN = new wxCheckBox(this, ID_SX_DITHER_EN, _("Enable dithering in SDM"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SX_DITHER_EN"));
chkSX_DITHER_EN->SetValue(false);
chkSX_DITHER_EN->SetToolTip(_("Enabled dithering in SDM"));
SXTcontrols4Sizer->Add(chkSX_DITHER_EN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText14 = new wxStaticText(this, ID_STATICTEXT29, _("Enable additional DIV2 prescaler"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
SXTcontrols4Sizer->Add(StaticText14, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
cmbEN_DIV2_DIVPROGenabled = new wxComboBox(this, ID_EN_DIV2_DIVPROGenabled, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_EN_DIV2_DIVPROGenabled"));
cmbEN_DIV2_DIVPROGenabled->Append(_("Disable"));
cmbEN_DIV2_DIVPROGenabled->SetSelection( cmbEN_DIV2_DIVPROGenabled->Append(_("Enable")) );
cmbEN_DIV2_DIVPROGenabled->SetToolTip(_("Enables additional DIV2 prescaler at the input of the Programmable divider. The core of programmable divider in the SX feedback divider works up to 5.5GHz. For FVCO>5.5GHz, the prescaler is needed to lower the input frequency to DIVPROG_SX."));
SXTcontrols4Sizer->Add(cmbEN_DIV2_DIVPROGenabled, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText6 = new wxStaticText(this, ID_STATICTEXT7, _("Test mode of SX"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
SXTcontrols4Sizer->Add(StaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbTST_SX = new ComboBoxMap(this, ID_TST_SX, wxEmptyString, wxDefaultPosition, wxSize(370,-1), 0, 0, 0, wxDefaultValidator, _T("ID_TST_SX"));
cmbTST_SX->SetToolTip(_("Controls the test mode of PLLs. TST signal lines are shared between all PLLs (CGEN, RX and TX). Only one TST signal of any PLL should be active at a given time.\n    0 – TST disabled; RSSI analog outputs enabled if RSSI blocks active and when all PLL test signals are off (default)\n    1 – tstdo[0]=VCO/20 clock*; tstdo[1]=VCO/40 clock*; tstao = High impedance;\n    2 – tstdo[0]=SDM clock; tstdo[1]= feedback divider output; tstao = VCO tune through a 60kOhm resistor;\n    3 – tstdo[0]=Reference clock; tstdo[1]= feedback divider output; tstao = VCO tune through a 10kOhm resistor;\n    4 – tstdo[0]= High impedance; tstdo[1]= High impedance; tstao = High impedance;\n    5 – tstdo[0]=Charge pump Down signal; tstdo[1]=Charge pump Up signal; tstao = High impedance;\n    6 – tstdo[0]= High impedance; tstdo[1]= High impedance; tstao = VCO tune through a 60kOhm resistor;\n    7 – tstdo[0]= High impedance; tstdo[1]= High impedance; tstao = VCO tune through a 10kOhm resistor;\n\n    if TST_SX[2]=1 --> VCO_TSTBUF active generating VCO_TST_DIV20 and VCO_TST_DIV40\n    * When EN_DIV2_DIVPROG_(SXR, SXT) is active, the division ratio must be multiplied by 2 (40/80)"));
SXTcontrols4Sizer->Add(cmbTST_SX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText7 = new wxStaticText(this, ID_STATICTEXT8, _("Feedback divider for SDM"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
SXTcontrols4Sizer->Add(StaticText7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbSEL_SDMCLK = new ComboBoxMap(this, ID_SEL_SDMCLK, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_SEL_SDMCLK"));
cmbSEL_SDMCLK->SetToolTip(_("Selects between the feedback divider output and Fref for SDM"));
SXTcontrols4Sizer->Add(cmbSEL_SDMCLK, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText10 = new wxStaticText(this, ID_STATICTEXT11, _("Reference voltage"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
SXTcontrols4Sizer->Add(StaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRSEL_LDO_VCO = new ComboBoxMap(this, ID_RSEL_LDO_VCO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RSEL_LDO_VCO"));
cmbRSEL_LDO_VCO->SetToolTip(_("Set the reference voltage that supplies bias voltage of switch-cap array and varactor"));
SXTcontrols4Sizer->Add(cmbRSEL_LDO_VCO, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText11 = new wxStaticText(this, ID_STATICTEXT12, _("Scales offset of charge pump"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
SXTcontrols4Sizer->Add(StaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbIOFFSET_CP = new ComboBoxMap(this, ID_IOFFSET_CP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_IOFFSET_CP"));
cmbIOFFSET_CP->SetToolTip(_("Scales the offset current of the charge pump, 0-->63. This current is used in Fran-N mode to create an offset in the CP response and avoid the non-linear section"));
SXTcontrols4Sizer->Add(cmbIOFFSET_CP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText12 = new wxStaticText(this, ID_STATICTEXT13, _("Scales pulse current of charge pump"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
SXTcontrols4Sizer->Add(StaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbIPULSE_CP = new ComboBoxMap(this, ID_IPULSE_CP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_IPULSE_CP"));
cmbIPULSE_CP->SetToolTip(_("Scales the pulse current of the charge pump"));
SXTcontrols4Sizer->Add(cmbIPULSE_CP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText2 = new wxStaticText(this, ID_STATICTEXT1, _("CSW_VCO"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
SXTcontrols4Sizer->Add(StaticText2, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
cmbCSW_VCO = new ComboBoxMap(this, ID_CSW_VCO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CSW_VCO"));
cmbCSW_VCO->SetToolTip(_("Coarse control of VCO frequency, 0 for lowest frequency and 255 for highest. This control is set by SX_SWC_calibration"));
SXTcontrols4Sizer->Add(cmbCSW_VCO, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
SXTcontrolsSizer->Add(SXTcontrols4Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer7->Add(SXTcontrolsSizer, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("PLL loop filter"));
FlexGridSizer6 = new wxFlexGridSizer(0, 2, 0, 0);
StaticText17 = new wxStaticText(this, ID_STATICTEXT18, _("CP2"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
FlexGridSizer6->Add(StaticText17, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCP2_PLL = new ComboBoxMap(this, ID_CP2_PLL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CP2_PLL"));
cmbCP2_PLL->SetToolTip(_("Controls the value of CP2 (cap from CP output to GND) in the PLL filter"));
FlexGridSizer6->Add(cmbCP2_PLL, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText18 = new wxStaticText(this, ID_STATICTEXT19, _("CP3"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
FlexGridSizer6->Add(StaticText18, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCP3_PLL = new ComboBoxMap(this, ID_CP3_PLL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CP3_PLL"));
cmbCP3_PLL->SetToolTip(_("Controls the value of CP3 (cap from VCO Vtune input to GND) in the PLL filter"));
FlexGridSizer6->Add(cmbCP3_PLL, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText19 = new wxStaticText(this, ID_STATICTEXT20, _("CZ"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
FlexGridSizer6->Add(StaticText19, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbCZ = new ComboBoxMap(this, ID_CZ, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CZ"));
cmbCZ->SetToolTip(_("Controls the value of CZ (Zero capacitor) in the PLL filter"));
FlexGridSizer6->Add(cmbCZ, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticBoxSizer5->Add(FlexGridSizer6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer7->Add(StaticBoxSizer5, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
sizerFrequencyControl = new wxFlexGridSizer(0, 3, 0, 0);
StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Frequency, GHz"));
txtFrequency = new wxTextCtrl(this, ID_TEXTCTRL1, _("2.14"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
StaticBoxSizer1->Add(txtFrequency, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
btnCalculate = new wxButton(this, ID_BUTTON2, _("Calculate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
StaticBoxSizer1->Add(btnCalculate, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
btnTune = new wxButton(this, ID_BUTTON3, _("Tune"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
StaticBoxSizer1->Add(btnTune, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
btnCoarseTune = new wxButton(this, ID_BUTTON5, _("Coarse Tune"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
btnCoarseTune->Hide();
StaticBoxSizer1->Add(btnCoarseTune, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
sizerFrequencyControl->Add(StaticBoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Calculated Values for Fractional Mode"));
FlexGridSizer4 = new wxFlexGridSizer(0, 4, 5, 10);
StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("N Integer:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
FlexGridSizer4->Add(StaticText1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblINT_SDM = new wxStaticText(this, ID_STATICTEXT3, _("\?\?\?"), wxDefaultPosition, wxSize(91,13), 0, _T("ID_STATICTEXT3"));
FlexGridSizer4->Add(lblINT_SDM, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText20 = new wxStaticText(this, ID_STATICTEXT21, _("N Fractional:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
FlexGridSizer4->Add(StaticText20, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblFRAC_SDM = new wxStaticText(this, ID_STATICTEXT22, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
FlexGridSizer4->Add(lblFRAC_SDM, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText22 = new wxStaticText(this, ID_STATICTEXT23, _("Divider:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
FlexGridSizer4->Add(StaticText22, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblDivider = new wxStaticText(this, ID_STATICTEXT24, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
FlexGridSizer4->Add(lblDivider, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText24 = new wxStaticText(this, ID_STATICTEXT25, _("Output Freq, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
FlexGridSizer4->Add(StaticText24, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblRealOutFrequency = new wxStaticText(this, ID_STATICTEXT26, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
FlexGridSizer4->Add(lblRealOutFrequency, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText26 = new wxStaticText(this, ID_STATICTEXT27, _("VCO Freq, GHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
FlexGridSizer4->Add(StaticText26, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblVCOfreq = new wxStaticText(this, ID_STATICTEXT28, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
FlexGridSizer4->Add(lblVCOfreq, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText21 = new wxStaticText(this, ID_STATICTEXT30, _("DIV2 prescaler:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
FlexGridSizer4->Add(StaticText21, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblEN_DIV2_DIVPROG = new wxStaticText(this, ID_EN_DIV2_DIVPROG, _("\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_EN_DIV2_DIVPROG"));
FlexGridSizer4->Add(lblEN_DIV2_DIVPROG, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer3->Add(FlexGridSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
sizerFrequencyControl->Add(StaticBoxSizer3, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer7->Add(sizerFrequencyControl, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer1->Add(FlexGridSizer7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_PW_DIV2_LOCH,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_PW_DIV4_LOCH,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_DIV_LOCH,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_PD_FBDIV,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_PD_LOCH_T2RBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_PD_CP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_PD_FDIV,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_PD_SDM,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_PD_VCO_COMP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_PD_VCO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_EN_G,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_EN_DIR_SXRSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_SEL_VCO,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSXT::OnbtnShowVCOClick);
Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSXT::OnbtnUpdateValuesClick);
Connect(ID_VDIV_VCO,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_ICT_VCO,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSXT::OnbtnChangeRefClkClick);
Connect(ID_RESET_N,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_SPDUP_VCO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_BYPLDO_VCO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_EN_COARSEPLL,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_CURLIM_VCO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_REVPH_PFD,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_EN_INTONLY_SDM,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_EN_SDM_CLK,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_EN_SDM_TSTO_SXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_EN_SDM_TSTO_SXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_REV_SDMCLK,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_SX_DITHER_EN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_TST_SX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_SEL_SDMCLK,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_RSEL_LDO_VCO,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_IOFFSET_CP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_IPULSE_CP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_CSW_VCO,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_CP2_PLL,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_CP3_PLL,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_CZ,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlSXT::ParameterChangeHandler);
Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSXT::OnbtnCalculateClick);
Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSXT::OnbtnTuneClick);
Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSXT::OnbntTuneCoarseClick);
//*)
mLastRealOutFreq[0] = "???";
mLastRealOutFreq[1] = "???";
mLastVCOFreq[0] = "???";
mLastVCOFreq[1] = "???";

}
pnlSXT::~pnlSXT()
{
//(*Destroy(pnlSXT)
//*)
}
void pnlSXT::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlSXT panel don't have control module assigned" << std::endl;
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

void pnlSXT::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    char ctemp[80];
    vector<string> temp;

    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%.3f pF", (i*6*387.0)/1000.0); temp.push_back(ctemp);}
    cmbCP2_PLL->Clear();
    cmbCP2_PLL->Append(temp);
    cmbCP2_PLL->SetSelection( lmsControl->GetParam(CP2_PLL));

    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%.3f pF", (i*6*980.0)/1000.0); temp.push_back(ctemp);}
    cmbCP3_PLL->Clear();
    cmbCP3_PLL->Append(temp);
    cmbCP3_PLL->SetSelection( lmsControl->GetParam(CP3_PLL));

    temp.clear();
    for(int i=0; i<256; ++i)
{sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbCSW_VCO->Clear();
    cmbCSW_VCO->Append(temp);
    cmbCSW_VCO->SetSelection( lmsControl->GetParam(CSW_VCO));

    temp.clear();
    for(int i=0; i<16; ++i)
        {sprintf(ctemp, "%.3f pF", i*8*5.88); temp.push_back(ctemp);}
    cmbCZ->Clear();
    cmbCZ->Append(temp);
    cmbCZ->SetSelection( lmsControl->GetParam(CZ));

    temp.clear();
    for(int i=0; i<8; ++i)
{sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbDIV_LOCH->Clear();
    cmbDIV_LOCH->Append(temp);
    cmbDIV_LOCH->SetSelection( lmsControl->GetParam(DIV_LOCH));

    temp.clear();
    for(int i=0; i<256; ++i)
{sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbICT_VCO->Clear();
    cmbICT_VCO->Append(temp);
    cmbICT_VCO->SetSelection( lmsControl->GetParam(ICT_VCO));

    temp.clear();
    for(int i=0; i<64; ++i)
        {sprintf(ctemp, "%.3f uA", 0.243*i); temp.push_back(ctemp);}
    cmbIOFFSET_CP->Clear();
    cmbIOFFSET_CP->Append(temp);
    cmbIOFFSET_CP->SetSelection( lmsControl->GetParam(IOFFSET_CP));

    temp.clear();
    for(int i=0; i<64; ++i)
{sprintf(ctemp, "%.3f uA", 2.312*i); temp.push_back(ctemp);}
    cmbIPULSE_CP->Clear();
    cmbIPULSE_CP->Append(temp);
    cmbIPULSE_CP->SetSelection( lmsControl->GetParam(IPULSE_CP));

    temp.clear();
    for(int i=0; i<8; ++i)
{sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbPW_DIV2_LOCH->Clear();
    cmbPW_DIV2_LOCH->Append(temp);
    cmbPW_DIV2_LOCH->SetSelection( lmsControl->GetParam(PW_DIV2_LOCH));

    temp.clear();
    for(int i=0; i<8; ++i)
{sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbPW_DIV4_LOCH->Clear();
    cmbPW_DIV4_LOCH->Append(temp);
    cmbPW_DIV4_LOCH->SetSelection( lmsControl->GetParam(PW_DIV4_LOCH));

    temp.clear();
    for(int i=0; i<=6; ++i)
        {sprintf(ctemp, "1.6 V"); temp.push_back(ctemp);}
    for(int i=7; i<32; ++i)
        {sprintf(ctemp, "%.3f V", (0.000060*180000.0/i)); temp.push_back(ctemp);}
        //{sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbRSEL_LDO_VCO->Clear();
    cmbRSEL_LDO_VCO->Append(temp);
    cmbRSEL_LDO_VCO->SetSelection( lmsControl->GetParam(RSEL_LDO_VCO));

    temp.clear();
    temp.push_back("CLK_DIV");
    temp.push_back("CLK_REF");
    cmbSEL_SDMCLK->Clear();
    cmbSEL_SDMCLK->Append(temp);
    cmbSEL_SDMCLK->SetSelection( lmsControl->GetParam(SEL_SDMCLK));

    vector<cmbKeyValuePair> keyvalues;
    keyvalues.push_back(cmbKeyValuePair(0,"TST disabled"));
    keyvalues.push_back(cmbKeyValuePair(1,"TST[0]=VCO/20 clk*; TST[1]=VCO/40 clk*; TSTA=Hi Z"));
    keyvalues.push_back(cmbKeyValuePair(2,"TST[0]=SDM clk; TST[1]=FBD output; TSTA=Vtune@60kOhm"));
    keyvalues.push_back(cmbKeyValuePair(3,"TST[0]=Ref clk; TST[1]=FBD output; TSTA=Vtune@10kOhm"));
    keyvalues.push_back(cmbKeyValuePair(4,"TST[0]=Hi Z; TST[1]=Hi Z; TSTA=Hi Z"));
    keyvalues.push_back(cmbKeyValuePair(5,"TST[0]=CP Down offset; TST[1]=CP Up offset; TSTA=Hi Z"));
    keyvalues.push_back(cmbKeyValuePair(6,"TST[0]=Hi Z; TST[1]=Hi Z; TSTA=Vtune@60kOhm"));
    keyvalues.push_back(cmbKeyValuePair(7,"TST[0]=Hi Z; TST[1]=Hi Z; TSTA=Vtune@10kOhm"));
    cmbTST_SX->Clear();
    cmbTST_SX->Set(keyvalues);
    cmbTST_SX->SetSelection( lmsControl->GetParam(TST_SX));

    temp.clear();
    sprintf(ctemp, "%.4f V", 1.6628); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6626); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6623); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6621); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6618); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6616); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6614); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6611); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6608); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6606); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6603); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6601); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6598); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6596); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6593); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.659); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6608); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6606); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6603); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6601); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6598); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6596); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6593); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.659); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6587); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6585); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6582); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6579); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6576); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6574); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6571); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6568); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6587); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6585); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6582); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6579); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6576); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6574); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6571); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6568); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6565); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6562); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6559); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6556); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6553); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.655); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6547); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6544); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6565); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6562); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6559); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6556); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6553); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.655); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6547); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6544); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6541); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6537); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6534); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6531); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6528); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6524); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6521); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6518); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6421); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6417); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6412); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6408); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6403); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6399); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6394); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6389); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6384); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.638); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6375); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.637); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6365); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.636); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6354); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6349); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6384); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.638); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6375); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.637); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6365); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.636); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6354); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6349); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6344); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6339); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6333); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6328); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6322); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6316); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6311); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6305); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6344); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6339); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6333); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6328); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6322); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6316); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6311); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6305); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6299); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6293); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6287); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6281); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6275); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6269); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6262); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6256); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6299); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6293); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6287); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6281); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6275); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6269); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6262); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6256); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6249); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6243); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6236); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6229); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6222); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6215); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6208); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.6201); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5981); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.597); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5959); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5947); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5936); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5924); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5912); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.59); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5888); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5875); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5862); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5849); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5836); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5822); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5808); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5794); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5888); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5875); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5862); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5849); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5836); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5822); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5808); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5794); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5779); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5765); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.575); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5734); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5718); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5702); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5686); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5669); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5779); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5765); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.575); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5734); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5718); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5702); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5686); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5669); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5652); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5634); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5616); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5598); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5579); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.556); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.554); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.552); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5652); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5634); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5616); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5598); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5579); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.556); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.554); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.552); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5499); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5478); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5456); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5433); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5411); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5387); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5363); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.5338); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.4388); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.433); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.4268); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.4205); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.4138); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.4069); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3996); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.392); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.384); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3756); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3667); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3574); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3476); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3373); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3264); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3148); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.384); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3756); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3667); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3574); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3476); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3373); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3264); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3148); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3025); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.2895); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.2756); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.2608); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.245); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.228); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.2098); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.1902); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.3025); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.2895); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.2756); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.2608); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.245); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.228); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.2098); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.1902); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.169); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.1461); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.1211); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.0939); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.0641); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.0313); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.9951); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.9549); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.169); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.1461); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.1211); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.0939); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.0641); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 1.0313); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.9951); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.9549); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.9099); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.8593); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.802); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.7365); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.6609); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.5727); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.4685); temp.push_back(ctemp);
    sprintf(ctemp, "%.4f V", 0.3436); temp.push_back(ctemp);
    cmbVDIV_VCO->Clear();
    cmbVDIV_VCO->Append(temp);
    cmbVDIV_VCO->SetSelection( lmsControl->GetParam(VDIV_VCO));
    UpdateTooltips(this);
}

void pnlSXT::UpdateGUI()
{
    long value = 0;
    value = lmsControl->GetParam(BYPLDO_VCO);
    chkBYPLDO_VCO->SetValue(value);

    value = lmsControl->GetParam(CP2_PLL);
    cmbCP2_PLL->SetSelection(value);

    value = lmsControl->GetParam(CP3_PLL);
    cmbCP3_PLL->SetSelection(value);

    value = lmsControl->GetParam(CSW_VCO);
    cmbCSW_VCO->SetSelection(value);

    value = lmsControl->GetParam(CURLIM_VCO);
    chkCURLIM_VCO->SetValue(value);

    value = lmsControl->GetParam(CZ);
    cmbCZ->SetSelection(value);

    value = lmsControl->GetParam(DIV_LOCH);
    cmbDIV_LOCH->SetSelection(value);

    value = lmsControl->GetParam(EN_COARSEPLL);
    chkEN_COARSEPLL->SetValue(value);

    value = lmsControl->GetParam(EN_DIV2_DIVPROG);
    lblEN_DIV2_DIVPROG->SetLabel(wxString::Format("%li", value));

    value = lmsControl->GetParam(EN_G);
    chkEN_G->SetValue(value);

    value = lmsControl->GetParam(EN_INTONLY_SDM);
    chkEN_INTONLY_SDM->SetValue(value);

    value = lmsControl->GetParam(EN_SDM_CLK);
    chkEN_SDM_CLK->SetValue(value);

    value = lmsControl->GetParam(EN_SDM_TSTO_SXR);
    chkEN_SDM_TSTO_SXR->SetValue(value);

    value = lmsControl->GetParam(EN_SDM_TSTO_SXT);
    chkEN_SDM_TSTO_SXT->SetValue(value);

    value = lmsControl->GetParam(ICT_VCO);
    cmbICT_VCO->SetSelection(value);

    value = lmsControl->GetParam(IOFFSET_CP);
    cmbIOFFSET_CP->SetSelection(value);

    value = lmsControl->GetParam(IPULSE_CP);
    cmbIPULSE_CP->SetSelection(value);

    value = lmsControl->GetParam(PD_CP);
    chkPD_CP->SetValue(value);

    value = lmsControl->GetParam(PD_FDIV);
    chkPD_FDIV->SetValue(value);

    value = lmsControl->GetParam(PD_LOCH_T2RBUF);
    chkPD_LOCH_T2RBUF->SetValue(value);

    value = lmsControl->GetParam(PD_SDM);
    chkPD_SDM->SetValue(value);

    value = lmsControl->GetParam(PD_VCO);
    chkPD_VCO->SetValue(value);

    value = lmsControl->GetParam(PD_VCO_COMP);
    chkPD_VCO_COMP->SetValue(value);

    value = lmsControl->GetParam(PW_DIV2_LOCH);
    cmbPW_DIV2_LOCH->SetSelection(value);

    value = lmsControl->GetParam(PW_DIV4_LOCH);
    cmbPW_DIV4_LOCH->SetSelection(value);

    value = lmsControl->GetParam(RESET_N);
    chkRESET_N->SetValue(value);

    value = lmsControl->GetParam(REVPH_PFD);
    chkREVPH_PFD->SetValue(value);

    value = lmsControl->GetParam(REV_SDMCLK);
    chkREV_SDMCLK->SetValue(value);

    value = lmsControl->GetParam(RSEL_LDO_VCO);
    cmbRSEL_LDO_VCO->SetSelection(value);

    value = lmsControl->GetParam(SEL_SDMCLK);
    cmbSEL_SDMCLK->SetSelection(value);

    value = lmsControl->GetParam(SEL_VCO);
    rgrSEL_VCO->SetSelection(value);

    value = lmsControl->GetParam(SPDUP_VCO);
    chkSPDUP_VCO->SetValue(value);

    value = lmsControl->GetParam(SX_DITHER_EN);
    chkSX_DITHER_EN->SetValue(value);

    value = lmsControl->GetParam(TST_SX);
    cmbTST_SX->SetSelection(value);

    value = lmsControl->GetParam(VDIV_VCO);
    cmbVDIV_VCO->SetSelection(value);

    value = lmsControl->GetParam(INT_SDM);
    lblINT_SDM->SetLabel(wxString::Format("%li", value));

    value = lmsControl->GetParam(FRAC_SDM);
    lblFRAC_SDM->SetLabel(wxString::Format("%li", value));

    value = lmsControl->GetParam(DIV_LOCH);
    lblDivider->SetLabel(wxString::Format("%.0f", pow(2.0, value+1)));

    value = lmsControl->GetParam(PD_FBDIV);
    chkPD_FBDIV->SetValue(value);

    double freq = lmsControl->GetFrequency()/1000;
    txtFrequency->SetValue( wxString::Format("%f", freq));
    lblRealOutFrequency->SetLabel(mLastRealOutFreq[lmsControl->GetConfigChannel()]);

    lblVCOfreq->SetLabel(mLastVCOFreq[lmsControl->GetConfigChannel()]);

    int activeChannel = lmsControl->GetConfigChannel();
    if( activeChannel == 1) //SXT
        lblRefClk_MHz->SetLabel(wxString::Format("%f", lmsControl->GetReferenceFrequencyPLL( false )));
    else
        lblRefClk_MHz->SetLabel(wxString::Format("%f", lmsControl->GetReferenceFrequencyPLL( true )));
}

void pnlSXT::UpdateReadOnlyValues()
{
    lmsControl->SetAutoDownload(true);
    int value;
    value = lmsControl->GetParam(VCO_CMPHO);
    lblVCO_CMPHO->SetLabel(wxString::Format("%i", value));
    value = lmsControl->GetParam(VCO_CMPLO);
    lblVCO_CMPLO->SetLabel(wxString::Format("%i", value));
    lmsControl->SetAutoDownload(false);
}

void pnlSXT::OnbtnUpdateValuesClick(wxCommandEvent& event)
{
    UpdateReadOnlyValues();
}

void pnlSXT::OnbtnCalculateClick(wxCommandEvent& event)
{
    double desFreq_MHz, realFreq_MHz, Fvco;
    unsigned Nint, Nfrac, iVCO, iDind, iEnDiv2;
    txtFrequency->GetValue().ToDouble(&desFreq_MHz);
    desFreq_MHz *= 1000; // freq to MHz
    int EnDiv2mode = 0;
    EnDiv2mode = (cmbEN_DIV2_DIVPROGenabled->GetSelection() == 1) ? 0 : 2;
    int status = lmsControl->SetFrequency(desFreq_MHz, realFreq_MHz, Nint, Nfrac, iVCO, Fvco, iDind, iEnDiv2, EnDiv2mode);
    if( status == -1)
    {
        wxMessageBox( "Cannot deliver requested frequency!" ); return;
    }
    else if( status == 1)
    {
        wxMessageBox( "Requested frequency out of range. Frequency set to closest available frequency." );

    }
    lblEN_DIV2_DIVPROG->SetLabel(wxString::Format("%li", lmsControl->GetParam(EN_DIV2_DIVPROG)));
    lblINT_SDM->SetLabel(wxString::Format("%i", Nint));
    lblFRAC_SDM->SetLabel(wxString::Format("%i", Nfrac));
    lblDivider->SetLabel(wxString::Format("%1.0f", pow(2.0, iDind+1)));
    lblRealOutFrequency->SetLabel(wxString::Format("%1.6f", realFreq_MHz/1000));
    mLastRealOutFreq[lmsControl->GetConfigChannel()] = lblRealOutFrequency->GetLabel();
    lblVCOfreq->SetLabel(wxString::Format("%1.6f", Fvco/1000));
    mLastVCOFreq[lmsControl->GetConfigChannel()] = lblVCOfreq->GetLabel();
    rgrSEL_VCO->SetSelection(iVCO);
    cmbDIV_LOCH->SetSelection(iDind);
}

void pnlSXT::OnbtnTuneClick(wxCommandEvent& event)
{
    double fdes = 0;
    txtFrequency->GetValue().ToDouble(&fdes);
    fdes = fdes*1000; //to MHz
    lmsControl->algorithms->VCO_Tuning_SXT_SXR(lmsControl->GetConfigChannel()==0);
    lmsControl->GetParam(CSW_VCO, true, true);
    UpdateGUI();
}

void pnlSXT::OnbtnShowVCOClick(wxCommandEvent& event)
{
    dlgVCO_SX dlg(lmsControl->getPLL_SX(), lmsControl->getPLL_CGEN(), this);
    dlg.ShowModal();
}

void pnlSXT::OnbtnChangeRefClkClick(wxCommandEvent& event)
{
    dlgFloatInput dlg(this, "Reference clock", "Enter reference clock (MHz):", lmsControl->GetReferenceFrequencyPLL( lmsControl->GetConfigChannel() != 1 ) );
    if( dlg.ShowModal() == wxID_OK)
    {
        int activeChannel = lmsControl->GetConfigChannel();
        if( activeChannel == 1) //SXT
        {
            lmsControl->SetReferenceFrequencyPLL(dlg.GetValue(), false);
            lblRefClk_MHz->SetLabel(wxString::Format("%f", lmsControl->GetReferenceFrequencyPLL( false )));
        }
        else
        {
            lmsControl->SetReferenceFrequencyPLL(dlg.GetValue(), true);
            lblRefClk_MHz->SetLabel(wxString::Format("%f", lmsControl->GetReferenceFrequencyPLL( true )));
        }
    }
}

void pnlSXT::OnbntTuneCoarseClick(wxCommandEvent& event)
{
    double fdes = 0;
    txtFrequency->GetValue().ToDouble(&fdes);
    fdes = fdes*1000; //to MHz
    lmsControl->algorithms->VCO_CoarseTuning_SXT_SXR(lmsControl->GetReferenceFrequencyPLL(lmsControl->GetConfigChannel()), fdes , lmsControl->GetConfigChannel());
    lmsControl->GetParam(CSW_VCO, true, true);
    UpdateGUI();
}
