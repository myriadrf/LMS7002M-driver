/**
@file	pnlRxTSP.cpp
@author	Lime Microsystems
@brief	RxTSP module panel
*/

#include "pnlRxTSP.h"
#include <iostream>
#include <math.h>
#include "ComboBoxMap.h"
#include "dlgFloatInput.h"
#include "LMS7002_MainControl.h"
#include "../CommonUtilities.h"
#include "dlgGFIR_Coefficients.h"
#include "dlgNCOSweepTest.h"
//(*InternalHeaders(pnlRxTSP)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)
//(*IdInit(pnlRxTSP)
const long pnlRxTSP::ID_CMIX_SC_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT7 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT34 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT28 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT35 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT29 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT36 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT31 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT38 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT30 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT37 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT32 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT39 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT5 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT6 = wxNewId();
const long pnlRxTSP::ID_BUTTON1 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT33 = wxNewId();
const long pnlRxTSP::ID_CMIX_GAIN_RXTSP = wxNewId();
const long pnlRxTSP::ID_EN_RXTSP = wxNewId();
const long pnlRxTSP::ID_BSTART_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT12 = wxNewId();
const long pnlRxTSP::ID_DCCORR_AVG_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT11 = wxNewId();
const long pnlRxTSP::ID_HBD_OVR_RXTSP = wxNewId();
const long pnlRxTSP::ID_CMIX_BYP_RXTSP = wxNewId();
const long pnlRxTSP::ID_AGC_BYP_RXTSP = wxNewId();
const long pnlRxTSP::ID_GFIR3_BYP_RXTSP = wxNewId();
const long pnlRxTSP::ID_GFIR2_BYP_RXTSP = wxNewId();
const long pnlRxTSP::ID_GFIR1_BYP_RXTSP = wxNewId();
const long pnlRxTSP::ID_DC_BYP_RXTSP = wxNewId();
const long pnlRxTSP::ID_GC_BYP_RXTSP = wxNewId();
const long pnlRxTSP::ID_PH_BYP_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT13 = wxNewId();
const long pnlRxTSP::ID_GFIR1_L_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT14 = wxNewId();
const long pnlRxTSP::ID_GFIR1_N_RXTSP = wxNewId();
const long pnlRxTSP::ID_BUTTON2 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT15 = wxNewId();
const long pnlRxTSP::ID_GFIR2_L_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT16 = wxNewId();
const long pnlRxTSP::ID_GFIR2_N_RXTSP = wxNewId();
const long pnlRxTSP::ID_BUTTON3 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT17 = wxNewId();
const long pnlRxTSP::ID_GFIR3_L_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT18 = wxNewId();
const long pnlRxTSP::ID_GFIR3_N_RXTSP = wxNewId();
const long pnlRxTSP::ID_BUTTON4 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT1 = wxNewId();
const long pnlRxTSP::ID_AGC_K_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT3 = wxNewId();
const long pnlRxTSP::ID_AGC_AVG_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT2 = wxNewId();
const long pnlRxTSP::ID_AGC_ADESIRED_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT27 = wxNewId();
const long pnlRxTSP::ID_AGC_MODE_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT8 = wxNewId();
const long pnlRxTSP::ID_GCORRQ_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT9 = wxNewId();
const long pnlRxTSP::ID_GCORRI_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT10 = wxNewId();
const long pnlRxTSP::ID_IQCORR_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT19 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT20 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT4 = wxNewId();
const long pnlRxTSP::ID_MODE_RX = wxNewId();
const long pnlRxTSP::ID_STATICTEXT40 = wxNewId();
const long pnlRxTSP::ID_DTHBIT_RX = wxNewId();
const long pnlRxTSP::ID_BUTTON5 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT21 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT22 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT23 = wxNewId();
const long pnlRxTSP::ID_BUTTON6 = wxNewId();
const long pnlRxTSP::ID_BUTTON7 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT24 = wxNewId();
const long pnlRxTSP::ID_STATICTEXT25 = wxNewId();
const long pnlRxTSP::ID_TSGSWAPIQ_RXTSP = wxNewId();
const long pnlRxTSP::ID_TSGFCW_RXTSP = wxNewId();
const long pnlRxTSP::ID_TSGMODE_RXTSP = wxNewId();
const long pnlRxTSP::ID_INSEL_RXTSP = wxNewId();
const long pnlRxTSP::ID_TSGFC_RXTSP = wxNewId();
const long pnlRxTSP::ID_STATICTEXT26 = wxNewId();
const long pnlRxTSP::ID_DC_REG_RXTSP = wxNewId();
const long pnlRxTSP::ID_BUTTON_LOADDCI = wxNewId();
const long pnlRxTSP::ID_BUTTON_LOADDCQ = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlRxTSP,wxPanel)
//(*EventTable(pnlRxTSP)
//*)
END_EVENT_TABLE()

void pnlRxTSP::AssignEnumsToIds()
{
    wndId2Enum[ID_MODE_RX] = MODE_RX;
    wndId2Enum[ID_AGC_ADESIRED_RXTSP] = AGC_ADESIRED_RXTSP;
    wndId2Enum[ID_AGC_AVG_RXTSP] = AGC_AVG_RXTSP;
    wndId2Enum[ID_AGC_BYP_RXTSP] = AGC_BYP_RXTSP;
    wndId2Enum[ID_AGC_K_RXTSP] = AGC_K_RXTSP;
    wndId2Enum[ID_AGC_MODE_RXTSP] = AGC_MODE_RXTSP;
    wndId2Enum[ID_BSTART_RXTSP] = BSTART_RXTSP;
    wndId2Enum[ID_CMIX_BYP_RXTSP] = CMIX_BYP_RXTSP;
    wndId2Enum[ID_CMIX_GAIN_RXTSP] = CMIX_GAIN_RXTSP;
    wndId2Enum[ID_DCCORR_AVG_RXTSP] = DCCORR_AVG_RXTSP;
    wndId2Enum[ID_DC_BYP_RXTSP] = DC_BYP_RXTSP;
    wndId2Enum[ID_EN_RXTSP] = EN_RXTSP;
    wndId2Enum[ID_GCORRI_RXTSP] = GCORRI_RXTSP;
    wndId2Enum[ID_GCORRQ_RXTSP] = GCORRQ_RXTSP;
    wndId2Enum[ID_GC_BYP_RXTSP] = GC_BYP_RXTSP;
    wndId2Enum[ID_GFIR1_BYP_RXTSP] = GFIR1_BYP_RXTSP;
    wndId2Enum[ID_GFIR1_L_RXTSP] = GFIR1_L_RXTSP;
    wndId2Enum[ID_GFIR1_N_RXTSP] = GFIR1_N_RXTSP;
    wndId2Enum[ID_GFIR2_BYP_RXTSP] = GFIR2_BYP_RXTSP;
    wndId2Enum[ID_GFIR2_L_RXTSP] = GFIR2_L_RXTSP;
    wndId2Enum[ID_GFIR2_N_RXTSP] = GFIR2_N_RXTSP;
    wndId2Enum[ID_GFIR3_BYP_RXTSP] = GFIR3_BYP_RXTSP;
    wndId2Enum[ID_GFIR3_L_RXTSP] = GFIR3_L_RXTSP;
    wndId2Enum[ID_GFIR3_N_RXTSP] = GFIR3_N_RXTSP;
    wndId2Enum[ID_HBD_OVR_RXTSP] = HBD_OVR_RXTSP;
    wndId2Enum[ID_IQCORR_RXTSP] = IQCORR_RXTSP;
    wndId2Enum[ID_PH_BYP_RXTSP] = PH_BYP_RXTSP;
    wndId2Enum[ID_CMIX_SC_RXTSP] = CMIX_SC_RXTSP;

    wndId2Enum[ID_TSGFCW_RXTSP] = TSGFCW_RXTSP;
    wndId2Enum[ID_TSGSWAPIQ_RXTSP] = TSGSWAPIQ_RXTSP;
    wndId2Enum[ID_TSGMODE_RXTSP] = TSGMODE_RXTSP;
    wndId2Enum[ID_INSEL_RXTSP] = INSEL_RXTSP;
//    wndId2Enum[ID_CAPSEL] = CAPSEL;
    wndId2Enum[ID_TSGFC_RXTSP] = TSGFC_RXTSP;
    wndId2Enum[ID_DTHBIT_RX] = DTHBIT_RX;
}

pnlRxTSP::pnlRxTSP(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    dlgNCOSweep = NULL;
    coefFilenames[0] = "";
    coefFilenames[1] = "";
    coefFilenames[2] = "";
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlRxTSP::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlRxTSP)
wxStaticBoxSizer* GFIR2Sizer;
wxStaticBoxSizer* StaticBoxSizer2;
wxFlexGridSizer* FlexGridSizer4;
wxFlexGridSizer* FlexGridSizer16;
wxFlexGridSizer* FlexGridSizer19;
wxFlexGridSizer* FlexGridSizer10;
wxFlexGridSizer* FlexGridSizer3;
wxFlexGridSizer* GFIR15Sizer;
wxStaticBoxSizer* InterpolationSizer;
wxFlexGridSizer* FlexGridSizer5;
wxFlexGridSizer* FlexGridSizer22;
wxFlexGridSizer* FlexGridSizer9;
wxStaticBoxSizer* GFIR1Sizer;
wxFlexGridSizer* FlexGridSizer2;
wxFlexGridSizer* FlexGridSizer7;
wxFlexGridSizer* GFIR37Sizer;
wxStaticBoxSizer* BypassSizer;
wxStaticBoxSizer* IQCorrectorSizer;
wxStaticBoxSizer* StaticBoxSizer3;
wxFlexGridSizer* Interpolation3Sizer;
wxFlexGridSizer* FlexGridSizer15;
wxFlexGridSizer* IQCorrector2Sizer;
wxFlexGridSizer* FlexGridSizer18;
wxFlexGridSizer* FlexGridSizer8;
wxFlexGridSizer* FlexGridSizer21;
wxFlexGridSizer* FlexGridSizer14;
wxStaticBoxSizer* DCCorrectorSizer;
wxFlexGridSizer* FlexGridSizer20;
wxFlexGridSizer* Bypass8Sizer;
wxFlexGridSizer* GFIR26Sizer;
wxFlexGridSizer* FlexGridSizer13;
wxFlexGridSizer* FlexGridSizer12;
wxFlexGridSizer* DCCorrector4Sizer;
wxFlexGridSizer* FlexGridSizer6;
wxStaticBoxSizer* StaticBoxSizer1;
wxFlexGridSizer* FlexGridSizer1;
wxStaticBoxSizer* BISTSizer;
wxFlexGridSizer* FlexGridSizer11;
wxFlexGridSizer* FlexGridSizer17;
wxStaticBoxSizer* GFIR3Sizer;

Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 5);
FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 5);
FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 5);
BISTSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Ungrouped"));
FlexGridSizer8 = new wxFlexGridSizer(0, 1, 0, 0);
FlexGridSizer15 = new wxFlexGridSizer(0, 2, 0, 0);
wxString __wxRadioBoxChoices_1[2] =
{
	_("Upconvert"),
	_("Downconvert")
};
rgrCMIX_SC_RXTSP = new wxRadioBox(this, ID_CMIX_SC_RXTSP, _("CMIX spectrum control"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CMIX_SC_RXTSP"));
rgrCMIX_SC_RXTSP->SetSelection(0);
rgrCMIX_SC_RXTSP->SetToolTip(_("Spectrum control of CMIX"));
FlexGridSizer15->Add(rgrCMIX_SC_RXTSP, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer17 = new wxFlexGridSizer(0, 4, 2, 5);
StaticText5 = new wxStaticText(this, ID_STATICTEXT7, _("ADCI:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
FlexGridSizer17->Add(StaticText5, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblADCI = new wxStaticText(this, ID_STATICTEXT34, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT34"));
FlexGridSizer17->Add(lblADCI, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText6 = new wxStaticText(this, ID_STATICTEXT28, _("ADCQ:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
FlexGridSizer17->Add(StaticText6, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblADCQ = new wxStaticText(this, ID_STATICTEXT35, _("\?\?\?"), wxDefaultPosition, wxSize(48,-1), 0, _T("ID_STATICTEXT35"));
FlexGridSizer17->Add(lblADCQ, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText25 = new wxStaticText(this, ID_STATICTEXT29, _("BISTI:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
FlexGridSizer17->Add(StaticText25, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblBISTI = new wxStaticText(this, ID_STATICTEXT36, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT36"));
FlexGridSizer17->Add(lblBISTI, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText27 = new wxStaticText(this, ID_STATICTEXT31, _("BISTQ:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
FlexGridSizer17->Add(StaticText27, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblBISTQ = new wxStaticText(this, ID_STATICTEXT38, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT38"));
FlexGridSizer17->Add(lblBISTQ, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText26 = new wxStaticText(this, ID_STATICTEXT30, _("BSTATE_I:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
FlexGridSizer17->Add(StaticText26, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblBSTATE_I = new wxStaticText(this, ID_STATICTEXT37, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT37"));
FlexGridSizer17->Add(lblBSTATE_I, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText28 = new wxStaticText(this, ID_STATICTEXT32, _("BSTATE_Q:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
FlexGridSizer17->Add(StaticText28, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblBSTATE_Q = new wxStaticText(this, ID_STATICTEXT39, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT39"));
FlexGridSizer17->Add(lblBSTATE_Q, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("RSSI:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
FlexGridSizer17->Add(StaticText4, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
lblRSSI = new wxStaticText(this, ID_STATICTEXT6, _("\?\?\?"), wxDefaultPosition, wxSize(48,-1), 0, _T("ID_STATICTEXT6"));
FlexGridSizer17->Add(lblRSSI, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
Button1 = new wxButton(this, ID_BUTTON1, _("Read"), wxDefaultPosition, wxSize(53,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
FlexGridSizer17->Add(Button1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer15->Add(FlexGridSizer17, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
FlexGridSizer8->Add(FlexGridSizer15, 1, wxBOTTOM|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer16 = new wxFlexGridSizer(0, 3, 0, 0);
FlexGridSizer18 = new wxFlexGridSizer(0, 3, 0, 0);
StaticText29 = new wxStaticText(this, ID_STATICTEXT33, _("CMIX_GAIN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
FlexGridSizer18->Add(StaticText29, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
cmbCMIX_GAIN_RXTSP = new ComboBoxMap(this, ID_CMIX_GAIN_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(80,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CMIX_GAIN_RXTSP"));
cmbCMIX_GAIN_RXTSP->SetToolTip(_("Gain of CMIX output"));
FlexGridSizer18->Add(cmbCMIX_GAIN_RXTSP, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer16->Add(FlexGridSizer18, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
chkEN_RXTSP = new wxCheckBox(this, ID_EN_RXTSP, _("Enable RxTSP"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_RXTSP"));
chkEN_RXTSP->SetValue(false);
chkEN_RXTSP->SetToolTip(_("RxTSP modules enable"));
FlexGridSizer16->Add(chkEN_RXTSP, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
chkBSTART_RXTSP = new wxCheckBox(this, ID_BSTART_RXTSP, _("Start BIST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BSTART_RXTSP"));
chkBSTART_RXTSP->SetValue(false);
chkBSTART_RXTSP->SetToolTip(_("Starts delta sigma built in self test. Keep it at 1 one at least three clock cycles"));
FlexGridSizer16->Add(chkBSTART_RXTSP, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer8->Add(FlexGridSizer16, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
BISTSizer->Add(FlexGridSizer8, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer3->Add(BISTSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer21 = new wxFlexGridSizer(0, 2, 0, 5);
DCCorrectorSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("DC Corrector"));
DCCorrector4Sizer = new wxFlexGridSizer(0, 2, 0, 5);
DCCorrector4Sizer->AddGrowableCol(1);
StaticText11 = new wxStaticText(this, ID_STATICTEXT12, _("Number of samples"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
DCCorrector4Sizer->Add(StaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbDCCORR_AVG_RXTSP = new ComboBoxMap(this, ID_DCCORR_AVG_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_DCCORR_AVG_RXTSP"));
cmbDCCORR_AVG_RXTSP->SetToolTip(_("Number of samples to average for Automatic DC corrector. Number of samples to average is 2DCCORR_AVG + 12"));
DCCorrector4Sizer->Add(cmbDCCORR_AVG_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
DCCorrectorSizer->Add(DCCorrector4Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer21->Add(DCCorrectorSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
InterpolationSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Decimation"));
Interpolation3Sizer = new wxFlexGridSizer(0, 2, 0, 5);
Interpolation3Sizer->AddGrowableCol(0);
StaticText10 = new wxStaticText(this, ID_STATICTEXT11, _("HBD ratio"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
Interpolation3Sizer->Add(StaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbHBD_OVR_RXTSP = new ComboBoxMap(this, ID_HBD_OVR_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_HBD_OVR_RXTSP"));
cmbHBD_OVR_RXTSP->SetToolTip(_("HBD interpolation ratio. Interpolation ratio is 2HBD_OVR+1"));
Interpolation3Sizer->Add(cmbHBD_OVR_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
InterpolationSizer->Add(Interpolation3Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer21->Add(InterpolationSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
BypassSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Bypass"));
Bypass8Sizer = new wxFlexGridSizer(0, 2, 0, 0);
chkCMIX_BYP_RXTSP = new wxCheckBox(this, ID_CMIX_BYP_RXTSP, _("CMIX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CMIX_BYP_RXTSP"));
chkCMIX_BYP_RXTSP->SetValue(false);
chkCMIX_BYP_RXTSP->SetToolTip(_("CMIX bypass"));
Bypass8Sizer->Add(chkCMIX_BYP_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkAGC_BYP_RXTSP = new wxCheckBox(this, ID_AGC_BYP_RXTSP, _("AGC"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_AGC_BYP_RXTSP"));
chkAGC_BYP_RXTSP->SetValue(false);
chkAGC_BYP_RXTSP->SetToolTip(_("AGC bypass"));
Bypass8Sizer->Add(chkAGC_BYP_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkGFIR3_BYP_RXTSP = new wxCheckBox(this, ID_GFIR3_BYP_RXTSP, _("GFIR3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GFIR3_BYP_RXTSP"));
chkGFIR3_BYP_RXTSP->SetValue(false);
chkGFIR3_BYP_RXTSP->SetToolTip(_("GFIR3 bypass"));
Bypass8Sizer->Add(chkGFIR3_BYP_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkGFIR2_BYP_RXTSP = new wxCheckBox(this, ID_GFIR2_BYP_RXTSP, _("GFIR2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GFIR2_BYP_RXTSP"));
chkGFIR2_BYP_RXTSP->SetValue(false);
chkGFIR2_BYP_RXTSP->SetToolTip(_("GFIR2 bypass"));
Bypass8Sizer->Add(chkGFIR2_BYP_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkGFIR1_BYP_RXTSP = new wxCheckBox(this, ID_GFIR1_BYP_RXTSP, _("GFIR1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GFIR1_BYP_RXTSP"));
chkGFIR1_BYP_RXTSP->SetValue(false);
chkGFIR1_BYP_RXTSP->SetToolTip(_("GFIR1 bypass"));
Bypass8Sizer->Add(chkGFIR1_BYP_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkDC_BYP_RXTSP = new wxCheckBox(this, ID_DC_BYP_RXTSP, _("DC corrector"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DC_BYP_RXTSP"));
chkDC_BYP_RXTSP->SetValue(false);
chkDC_BYP_RXTSP->SetToolTip(_("DC corrector bypass"));
Bypass8Sizer->Add(chkDC_BYP_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkGC_BYP_RXTSP = new wxCheckBox(this, ID_GC_BYP_RXTSP, _("Gain corrector"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GC_BYP_RXTSP"));
chkGC_BYP_RXTSP->SetValue(false);
chkGC_BYP_RXTSP->SetToolTip(_("Gain corrector bypass"));
Bypass8Sizer->Add(chkGC_BYP_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPH_BYP_RXTSP = new wxCheckBox(this, ID_PH_BYP_RXTSP, _("Phase corrector"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PH_BYP_RXTSP"));
chkPH_BYP_RXTSP->SetValue(false);
chkPH_BYP_RXTSP->SetToolTip(_("Phase corrector bypass"));
Bypass8Sizer->Add(chkPH_BYP_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
BypassSizer->Add(Bypass8Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer21->Add(BypassSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
GFIR1Sizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("GFIR1"));
GFIR15Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText12 = new wxStaticText(this, ID_STATICTEXT13, _("Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
GFIR15Sizer->Add(StaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR1_L_RXTSP = new ComboBoxMap(this, ID_GFIR1_L_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GFIR1_L_RXTSP"));
cmbGFIR1_L_RXTSP->SetToolTip(_("Parameter l of GFIR1 (l = roundUp(CoeffN/5)-1). Unsigned integer"));
GFIR15Sizer->Add(cmbGFIR1_L_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText13 = new wxStaticText(this, ID_STATICTEXT14, _("Clock Division Ratio:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
GFIR15Sizer->Add(StaticText13, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR1_N_RXTSP = new ComboBoxMap(this, ID_GFIR1_N_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GFIR1_N_RXTSP"));
cmbGFIR1_N_RXTSP->SetToolTip(_("Clock division ratio of GFIR1 is GFIR1_N + 1. Unsigned integer"));
GFIR15Sizer->Add(cmbGFIR1_N_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnLoadGFIR1Coef = new wxButton(this, ID_BUTTON2, _("Coefficients"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
GFIR15Sizer->Add(btnLoadGFIR1Coef, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
GFIR1Sizer->Add(GFIR15Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer21->Add(GFIR1Sizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
GFIR2Sizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("GFIR2"));
GFIR26Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText14 = new wxStaticText(this, ID_STATICTEXT15, _("Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
GFIR26Sizer->Add(StaticText14, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR2_L_RXTSP = new ComboBoxMap(this, ID_GFIR2_L_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GFIR2_L_RXTSP"));
cmbGFIR2_L_RXTSP->SetToolTip(_("Parameter l of GFIR2 (l = roundUp(CoeffN/5)-1). Unsigned integer"));
GFIR26Sizer->Add(cmbGFIR2_L_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText15 = new wxStaticText(this, ID_STATICTEXT16, _("Clock Division Ratio:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
GFIR26Sizer->Add(StaticText15, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR2_N_RXTSP = new ComboBoxMap(this, ID_GFIR2_N_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GFIR2_N_RXTSP"));
cmbGFIR2_N_RXTSP->SetToolTip(_("Clock division ratio of GFIR2 is GFIR2_N + 1. Unsigned integer"));
GFIR26Sizer->Add(cmbGFIR2_N_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnLoadGFIR2Coef = new wxButton(this, ID_BUTTON3, _("Coefficients"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
GFIR26Sizer->Add(btnLoadGFIR2Coef, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
GFIR2Sizer->Add(GFIR26Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer21->Add(GFIR2Sizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
GFIR3Sizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("GFIR3"));
GFIR37Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText16 = new wxStaticText(this, ID_STATICTEXT17, _("Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
GFIR37Sizer->Add(StaticText16, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR3_L_RXTSP = new ComboBoxMap(this, ID_GFIR3_L_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GFIR3_L_RXTSP"));
cmbGFIR3_L_RXTSP->SetToolTip(_("Parameter l of GFIR3 (l = roundUp(CoeffN/5)-1). Unsigned integer"));
GFIR37Sizer->Add(cmbGFIR3_L_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText17 = new wxStaticText(this, ID_STATICTEXT18, _("Clock Division Ratio:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
GFIR37Sizer->Add(StaticText17, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR3_N_RXTSP = new ComboBoxMap(this, ID_GFIR3_N_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GFIR3_N_RXTSP"));
cmbGFIR3_N_RXTSP->SetToolTip(_("Clock division ratio of GFIR3 is GFIR3_N + 1. Unsigned integer"));
GFIR37Sizer->Add(cmbGFIR3_N_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnLoadGFIR3Coef = new wxButton(this, ID_BUTTON4, _("Coefficients"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
GFIR37Sizer->Add(btnLoadGFIR3Coef, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
GFIR3Sizer->Add(GFIR37Sizer, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer21->Add(GFIR3Sizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer3->Add(FlexGridSizer21, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer5->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 5);
FlexGridSizer9->AddGrowableCol(1);
StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("AGC"));
FlexGridSizer20 = new wxFlexGridSizer(0, 1, 0, 5);
FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
StaticText0 = new wxStaticText(this, ID_STATICTEXT1, _("AGC loop gain"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
FlexGridSizer2->Add(StaticText0, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
spinAGC_K_RXTSP = new wxSpinCtrl(this, ID_AGC_K_RXTSP, _T("1"), wxDefaultPosition, wxSize(64,-1), 0, 0, 262143, 1, _T("ID_AGC_K_RXTSP"));
spinAGC_K_RXTSP->SetValue(_T("1"));
spinAGC_K_RXTSP->SetToolTip(_("AGC loop gain"));
FlexGridSizer2->Add(spinAGC_K_RXTSP, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("AGC Averaging window size"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
FlexGridSizer2->Add(StaticText2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbAGC_AVG_RXTSP = new ComboBoxMap(this, ID_AGC_AVG_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_AGC_AVG_RXTSP"));
cmbAGC_AVG_RXTSP->SetToolTip(_("AGC Averaging window size"));
FlexGridSizer2->Add(cmbAGC_AVG_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("Desired output signal level"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
FlexGridSizer2->Add(StaticText1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbAGC_ADESIRED_RXTSP = new ComboBoxMap(this, ID_AGC_ADESIRED_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_AGC_ADESIRED_RXTSP"));
cmbAGC_ADESIRED_RXTSP->SetToolTip(_("AGC_ADESIRED"));
FlexGridSizer2->Add(cmbAGC_ADESIRED_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText24 = new wxStaticText(this, ID_STATICTEXT27, _("AGC Mode"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
FlexGridSizer2->Add(StaticText24, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
rgrAGC_MODE_RXTSP = new wxComboBox(this, ID_AGC_MODE_RXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_AGC_MODE_RXTSP"));
rgrAGC_MODE_RXTSP->Append(_("AGC"));
rgrAGC_MODE_RXTSP->Append(_("RSSI"));
rgrAGC_MODE_RXTSP->Append(_("Bypass"));
FlexGridSizer2->Add(rgrAGC_MODE_RXTSP, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer20->Add(FlexGridSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer1->Add(FlexGridSizer20, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer9->Add(StaticBoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
IQCorrectorSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("IQ Corrector"));
IQCorrector2Sizer = new wxFlexGridSizer(0, 2, 0, 5);
IQCorrector2Sizer->AddGrowableCol(1);
StaticText7 = new wxStaticText(this, ID_STATICTEXT8, _("Gain ch. Q"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
IQCorrector2Sizer->Add(StaticText7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGCORRQ_RXTSP = new ComboBoxMap(this, ID_GCORRQ_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GCORRQ_RXTSP"));
cmbGCORRQ_RXTSP->SetToolTip(_("corrector value, channel Q Unsigned integer"));
IQCorrector2Sizer->Add(cmbGCORRQ_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText8 = new wxStaticText(this, ID_STATICTEXT9, _("Gain ch. I"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
IQCorrector2Sizer->Add(StaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGCORRI_RXTSP = new ComboBoxMap(this, ID_GCORRI_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GCORRI_RXTSP"));
cmbGCORRI_RXTSP->SetToolTip(_("corrector value, channel I Unsigned integer"));
IQCorrector2Sizer->Add(cmbGCORRI_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText9 = new wxStaticText(this, ID_STATICTEXT10, _("Phase corrector"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
IQCorrector2Sizer->Add(StaticText9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbIQCORR_RXTSP = new ComboBoxMap(this, ID_IQCORR_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_IQCORR_RXTSP"));
cmbIQCORR_RXTSP->SetToolTip(_("Phase corrector value (tan(Alpha/2)). Integer, 2\'s complement"));
IQCorrector2Sizer->Add(cmbIQCORR_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText18 = new wxStaticText(this, ID_STATICTEXT19, _("Alpha"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
IQCorrector2Sizer->Add(StaticText18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
txtPhaseAlpha = new wxStaticText(this, ID_STATICTEXT20, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
IQCorrector2Sizer->Add(txtPhaseAlpha, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
IQCorrectorSizer->Add(IQCorrector2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer9->Add(IQCorrectorSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer5->Add(FlexGridSizer9, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer1->Add(FlexGridSizer5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("NCO"));
FlexGridSizer4 = new wxFlexGridSizer(3, 1, 0, 0);
FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
FlexGridSizer22 = new wxFlexGridSizer(0, 3, 0, 0);
StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
FlexGridSizer22->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
rgrMODE = new wxComboBox(this, ID_MODE_RX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_MODE_RX"));
rgrMODE->Append(_("FCW"));
rgrMODE->Append(_("PHO"));
FlexGridSizer22->Add(rgrMODE, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer6->Add(FlexGridSizer22, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer19 = new wxFlexGridSizer(0, 2, 0, 0);
StaticText30 = new wxStaticText(this, ID_STATICTEXT40, _("NCO bits to dither:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT40"));
FlexGridSizer19->Add(StaticText30, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
cmbDTHBIT_RX = new wxComboBox(this, ID_DTHBIT_RX, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_DTHBIT_RX"));
cmbDTHBIT_RX->SetSelection( cmbDTHBIT_RX->Append(_("0")) );
cmbDTHBIT_RX->Append(_("1"));
cmbDTHBIT_RX->Append(_("2"));
cmbDTHBIT_RX->Append(_("3"));
cmbDTHBIT_RX->Append(_("4"));
cmbDTHBIT_RX->Append(_("5"));
cmbDTHBIT_RX->Append(_("6"));
cmbDTHBIT_RX->Append(_("7"));
cmbDTHBIT_RX->Append(_("8"));
cmbDTHBIT_RX->Append(_("9"));
cmbDTHBIT_RX->Append(_("10"));
cmbDTHBIT_RX->Append(_("11"));
cmbDTHBIT_RX->Append(_("12"));
cmbDTHBIT_RX->Append(_("13"));
cmbDTHBIT_RX->Append(_("14"));
cmbDTHBIT_RX->Append(_("15"));
cmbDTHBIT_RX->SetToolTip(_("NCO bits to dither"));
FlexGridSizer19->Add(cmbDTHBIT_RX, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
btnSweepTest = new wxButton(this, ID_BUTTON5, _("NCO Sweeping..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
btnSweepTest->Hide();
FlexGridSizer19->Add(btnSweepTest, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer6->Add(FlexGridSizer19, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer4->Add(FlexGridSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
sizerNCOgrid = new wxFlexGridSizer(0, 4, 2, 5);
sizerNCOgrid->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText19 = new wxStaticText(this, ID_STATICTEXT21, _("FCW(MHz)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
sizerNCOgrid->Add(StaticText19, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText20 = new wxStaticText(this, ID_STATICTEXT22, _("PHO"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
sizerNCOgrid->Add(StaticText20, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText21 = new wxStaticText(this, ID_STATICTEXT23, _("Angle"), wxDefaultPosition, wxSize(48,13), 0, _T("ID_STATICTEXT23"));
sizerNCOgrid->Add(StaticText21, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer4->Add(sizerNCOgrid, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer7 = new wxFlexGridSizer(0, 4, 0, 0);
btnUploadNCO = new wxButton(this, ID_BUTTON6, _("Upload NCO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
FlexGridSizer7->Add(btnUploadNCO, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
btnSetRefClk = new wxButton(this, ID_BUTTON7, _("Set Reference Clk"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
FlexGridSizer7->Add(btnSetRefClk, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticText22 = new wxStaticText(this, ID_STATICTEXT24, _("RefClk(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
FlexGridSizer7->Add(StaticText22, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
lblRefClk = new wxStaticText(this, ID_STATICTEXT25, _("30.72"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
FlexGridSizer7->Add(lblRefClk, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer4->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer2->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer1->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer10 = new wxFlexGridSizer(0, 3, 0, 0);
StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("TSG"));
FlexGridSizer11 = new wxFlexGridSizer(0, 1, 0, 0);
chkTSGSWAPIQ_RXTSP = new wxCheckBox(this, ID_TSGSWAPIQ_RXTSP, _("Swap I and Q signal\n sources from TSG"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TSGSWAPIQ_RXTSP"));
chkTSGSWAPIQ_RXTSP->SetValue(false);
chkTSGSWAPIQ_RXTSP->SetToolTip(_("Swap signals at test signal generator\'s output"));
FlexGridSizer11->Add(chkTSGSWAPIQ_RXTSP, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer12 = new wxFlexGridSizer(0, 1, 0, 0);
wxString __wxRadioBoxChoices_2[2] =
{
	_("TSP clk/8"),
	_("TSP clk/4")
};
rgrTSGFCW_RXTSP = new wxRadioBox(this, ID_TSGFCW_RXTSP, _("TSGFCW"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_TSGFCW_RXTSP"));
rgrTSGFCW_RXTSP->SetToolTip(_("Set frequency of TSG\'s NCO"));
FlexGridSizer12->Add(rgrTSGFCW_RXTSP, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_3[2] =
{
	_("NCO"),
	_("DC source")
};
rgrTSGMODE_RXTSP = new wxRadioBox(this, ID_TSGMODE_RXTSP, _("TSGMODE"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_3, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_TSGMODE_RXTSP"));
rgrTSGMODE_RXTSP->SetToolTip(_("Test signal generator mode"));
FlexGridSizer12->Add(rgrTSGMODE_RXTSP, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_4[2] =
{
	_("ADC"),
	_("Test signal")
};
rgrINSEL_RXTSP = new wxRadioBox(this, ID_INSEL_RXTSP, _("Input source"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_4, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_INSEL_RXTSP"));
rgrINSEL_RXTSP->SetToolTip(_("Input source of RxTSP"));
FlexGridSizer12->Add(rgrINSEL_RXTSP, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer11->Add(FlexGridSizer12, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer14 = new wxFlexGridSizer(0, 1, 0, 0);
wxString __wxRadioBoxChoices_5[2] =
{
	_("-6dB"),
	_("Full scale")
};
rgrTSGFC_RXTSP = new wxRadioBox(this, ID_TSGFC_RXTSP, _("TSGFC"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_5, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_TSGFC_RXTSP"));
rgrTSGFC_RXTSP->SetToolTip(_("TSG full scale control"));
FlexGridSizer14->Add(rgrTSGFC_RXTSP, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer13 = new wxFlexGridSizer(0, 1, 0, 0);
StaticText23 = new wxStaticText(this, ID_STATICTEXT26, _("DC_REG(hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
FlexGridSizer13->Add(StaticText23, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
txtDC_REG_RXTSP = new wxTextCtrl(this, ID_DC_REG_RXTSP, _("ffff"), wxDefaultPosition, wxSize(75,-1), 0, wxDefaultValidator, _T("ID_DC_REG_RXTSP"));
FlexGridSizer13->Add(txtDC_REG_RXTSP, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
btnLoadDCI = new wxButton(this, ID_BUTTON_LOADDCI, _("Load to DC I"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOADDCI"));
FlexGridSizer13->Add(btnLoadDCI, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
btnLoadDCQ = new wxButton(this, ID_BUTTON_LOADDCQ, _("Load to DC Q"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOADDCQ"));
FlexGridSizer13->Add(btnLoadDCQ, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer14->Add(FlexGridSizer13, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer11->Add(FlexGridSizer14, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer3->Add(FlexGridSizer11, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer10->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer1->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_CMIX_SC_RXTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxTSP::OnbtnReadAllValuesClick);
Connect(ID_CMIX_GAIN_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_EN_RXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_BSTART_RXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_DCCORR_AVG_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_HBD_OVR_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_CMIX_BYP_RXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_AGC_BYP_RXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_GFIR3_BYP_RXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_GFIR2_BYP_RXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_GFIR1_BYP_RXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_DC_BYP_RXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_GC_BYP_RXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_PH_BYP_RXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_GFIR1_L_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_GFIR1_N_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxTSP::OnbtnLoadGFIR1CoefClick);
Connect(ID_GFIR2_L_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_GFIR2_N_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxTSP::OnbtnLoadGFIR2CoefClick);
Connect(ID_GFIR3_L_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_GFIR3_N_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxTSP::OnbtnLoadGFIR3CoefClick);
Connect(ID_AGC_K_RXTSP,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&pnlRxTSP::OnspinAGC_K_RXTSPChange);
Connect(ID_AGC_AVG_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_AGC_ADESIRED_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_AGC_MODE_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_GCORRQ_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_GCORRI_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_IQCORR_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_MODE_RX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_DTHBIT_RX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxTSP::OnbtnSweepTestClick);
Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxTSP::OnbtnUploadNCOClick);
Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxTSP::OnbtnSetRefClkClick);
Connect(ID_TSGSWAPIQ_RXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_TSGFCW_RXTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_TSGMODE_RXTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_INSEL_RXTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_TSGFC_RXTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlRxTSP::ParameterChangeHandler);
Connect(ID_BUTTON_LOADDCI,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxTSP::OnbtnLoadDCIClick);
Connect(ID_BUTTON_LOADDCQ,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlRxTSP::OnbtnLoadDCQClick);
//*)
    InitializeNCOgrid();
}
pnlRxTSP::~pnlRxTSP()
{
//(*Destroy(pnlRxTSP)
//*)
}
void pnlRxTSP::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlRxTSP panel don't have control module assigned" << std::endl;
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

    int evtint;
    float atangent;
    float angle;

    switch(parameter)
    {
    case IQCORR_RXTSP: // when changed recalculate alpha text field
        {
        short evtint = event.GetInt();
        evtint = (evtint << 4);
        evtint = (evtint >> 4);
        atangent = atan( evtint/2048.0 );
        angle = atangent * 180/3.141596;
        txtPhaseAlpha->SetLabel( wxString::Format("%.3f", angle));
        lmsControl->SetParam( parameter, event.GetInt());
        break;
        }
    case HBD_OVR_RXTSP:
        lmsControl->SetParam( parameter, (event.GetInt()==5) ? 7 : event.GetInt());
        break;
    case TSGFCW_RXTSP:
        lmsControl->SetParam( parameter, event.GetInt()+1);
        break;
    default:
        lmsControl->SetParam( parameter, event.GetInt());
    }
}

void pnlRxTSP::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    char ctemp[80];
    vector<cmbKeyValuePair> keyvalues;
    vector<string> temp;
    temp.push_back("0 dB");
    temp.push_back("+6 dB");
    temp.push_back("-6 dB");
    cmbCMIX_GAIN_RXTSP->Clear();
    cmbCMIX_GAIN_RXTSP->Append(temp);

    temp.clear();
    for(int i=0; i<4096; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbAGC_ADESIRED_RXTSP->Clear();
    cmbAGC_ADESIRED_RXTSP->Append(temp);    

    temp.clear();
    temp.push_back("2^7");
    temp.push_back("2^8");
    temp.push_back("2^9");
    temp.push_back("2^10");
    temp.push_back("2^11");
    temp.push_back("2^12");
    temp.push_back("2^13");
    temp.push_back("2^14");
    cmbAGC_AVG_RXTSP->Clear();
    cmbAGC_AVG_RXTSP->Append(temp);
    //cmbAGC_AVG_RXTSP->SetSelection( lmsControl->GetParam(AGC_AVG_RXTSP));

    spinAGC_K_RXTSP->SetRange(0, 262143);
    spinAGC_K_RXTSP->SetValue( lmsControl->GetParam(AGC_K_RXTSP));

    temp.clear();
    temp.push_back("2^12");
    temp.push_back("2^13");
    temp.push_back("2^14");
    temp.push_back("2^15");
    temp.push_back("2^16");
    temp.push_back("2^17");
    temp.push_back("2^18");
    temp.push_back("2^19");
    cmbDCCORR_AVG_RXTSP->Clear();
    cmbDCCORR_AVG_RXTSP->Append(temp);    

    temp.clear();
    for(int i=0; i<2048; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGCORRI_RXTSP->Clear();
    cmbGCORRI_RXTSP->Append(temp);    

    temp.clear();
    for(int i=0; i<2048; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGCORRQ_RXTSP->Clear();
    cmbGCORRQ_RXTSP->Append(temp);    

    temp.clear();
    for(int i=0; i<8; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR1_L_RXTSP->Clear();
    cmbGFIR1_L_RXTSP->Append(temp);

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR1_N_RXTSP->Clear();
    cmbGFIR1_N_RXTSP->Append(temp);    

    temp.clear();
    for(int i=0; i<8; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR2_L_RXTSP->Clear();
    cmbGFIR2_L_RXTSP->Append(temp);    

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR2_N_RXTSP->Clear();
    cmbGFIR2_N_RXTSP->Append(temp);    

    temp.clear();
    for(int i=0; i<8; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR3_L_RXTSP->Clear();
    cmbGFIR3_L_RXTSP->Append(temp);    

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR3_N_RXTSP->Clear();
    cmbGFIR3_N_RXTSP->Append(temp);    

    temp.clear();
    temp.push_back("2^1");
    temp.push_back("2^2");
    temp.push_back("2^3");
    temp.push_back("2^4");
    temp.push_back("2^5");
    temp.push_back("Bypass");
    cmbHBD_OVR_RXTSP->Clear();
    cmbHBD_OVR_RXTSP->Append(temp);

    keyvalues.clear();
    for(int i=-2048; i<2048; ++i)
    {
        sprintf(ctemp, "%i", i);
        keyvalues.push_back(cmbKeyValuePair(i&0xFFF, ctemp));
    }
    cmbIQCORR_RXTSP->Clear();
    cmbIQCORR_RXTSP->Set(keyvalues);    
    UpdateTooltips(this);
    UpdateGUI(); //sets default selections
}

void pnlRxTSP::UpdateGUI()
{
    float refClk = lmsControl->GetReferenceFrequencyNCO(true);
    lblRefClk->SetLabel(wxString::Format("%f", refClk));    
    long value = 0;
    value = lmsControl->GetParam(AGC_ADESIRED_RXTSP);
    cmbAGC_ADESIRED_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(AGC_AVG_RXTSP);
    cmbAGC_AVG_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(AGC_BYP_RXTSP);
    chkAGC_BYP_RXTSP->SetValue(value);

    value = lmsControl->GetParam(AGC_K_RXTSP);
    spinAGC_K_RXTSP->SetValue(value);

    value = lmsControl->GetParam(AGC_MODE_RXTSP);
    rgrAGC_MODE_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(BSTART_RXTSP);
    chkBSTART_RXTSP->SetValue(value);

    value = lmsControl->GetParam(CMIX_BYP_RXTSP);
    chkCMIX_BYP_RXTSP->SetValue(value);

    value = lmsControl->GetParam(CMIX_GAIN_RXTSP);
    cmbCMIX_GAIN_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(DCCORR_AVG_RXTSP);
    cmbDCCORR_AVG_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(DC_BYP_RXTSP);
    chkDC_BYP_RXTSP->SetValue(value);

    value = lmsControl->GetParam(EN_RXTSP);
    chkEN_RXTSP->SetValue(value);

    value = lmsControl->GetParam(GCORRI_RXTSP);
    cmbGCORRI_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(GCORRQ_RXTSP);
    cmbGCORRQ_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(GC_BYP_RXTSP);
    chkGC_BYP_RXTSP->SetValue(value);

    value = lmsControl->GetParam(GFIR1_BYP_RXTSP);
    chkGFIR1_BYP_RXTSP->SetValue(value);

    value = lmsControl->GetParam(GFIR1_L_RXTSP);
    cmbGFIR1_L_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(GFIR1_N_RXTSP);
    cmbGFIR1_N_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(GFIR2_BYP_RXTSP);
    chkGFIR2_BYP_RXTSP->SetValue(value);

    value = lmsControl->GetParam(GFIR2_L_RXTSP);
    cmbGFIR2_L_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(GFIR2_N_RXTSP);
    cmbGFIR2_N_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(GFIR3_BYP_RXTSP);
    chkGFIR3_BYP_RXTSP->SetValue(value);

    value = lmsControl->GetParam(GFIR3_L_RXTSP);
    cmbGFIR3_L_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(GFIR3_N_RXTSP);
    cmbGFIR3_N_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(HBD_OVR_RXTSP);
    if(value == 7)
        value = 5; //change value to combo box index
    cmbHBD_OVR_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(IQCORR_RXTSP);
    unsigned short iqcorr_val = value & 0xFFF;
    cmbIQCORR_RXTSP->SetSelection(iqcorr_val);

    value = lmsControl->GetParam(PH_BYP_RXTSP);
    chkPH_BYP_RXTSP->SetValue(value);

    value = lmsControl->GetParam(MODE_RX);
    rgrMODE->SetSelection(value);

    value = lmsControl->GetParam(DTHBIT_RX);
    cmbDTHBIT_RX->SetSelection(value);

    value = lmsControl->GetParam(TSGFCW_RXTSP);
    if(value == 1)
        value = 0;
    else if(value == 2)
        value = 1;
    rgrTSGFCW_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(TSGMODE_RXTSP);
    rgrTSGMODE_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(INSEL_RXTSP);
    rgrINSEL_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(TSGSWAPIQ_RXTSP);
    chkTSGSWAPIQ_RXTSP->SetValue(value);

    value = lmsControl->GetParam(DC_REG_RXTSP);
    txtDC_REG_RXTSP->SetValue( wxString::Format("%lX", value));

    value = lmsControl->GetParam(MODE_RX);
    rgrMODE->SetSelection(value);

    value = lmsControl->GetParam(TSGFC_RXTSP);
    rgrTSGFC_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(SEL_RX);
    if(value < ncoRadioButtons.size())
        ncoRadioButtons[value]->SetValue(true);

    vector<double> fcwFreqs;
    vector<int> phoCodes;
    lmsControl->GetNCOconfiguration(fcwFreqs, phoCodes, true);
    SetNCOgrid(fcwFreqs, phoCodes);    
}

void pnlRxTSP::OnspinAGC_K_RXTSPChange(wxSpinEvent& event)
{
    ParameterChangeHandler(event);
}

void pnlRxTSP::OnbtnLoadGFIR1CoefClick(wxCommandEvent& event)
{
    dlgGFIR_Coefficients dlg;
    dlg.Initialize(lmsControl, coefFilenames[0], 1, true);
    dlg.ShowModal();

    coefFilenames[0] = dlg.txtFilename->GetLabel();
}

void pnlRxTSP::OnbtnLoadGFIR2CoefClick(wxCommandEvent& event)
{
    dlgGFIR_Coefficients dlg;
    dlg.Initialize(lmsControl, coefFilenames[1], 2, true);
    dlg.ShowModal();

    coefFilenames[1] = dlg.txtFilename->GetLabel();
}

void pnlRxTSP::OnbtnLoadGFIR3CoefClick(wxCommandEvent& event)
{
    dlgGFIR_Coefficients dlg;
    dlg.Initialize(lmsControl, coefFilenames[2], 3, true);
    dlg.ShowModal();

    coefFilenames[2] = dlg.txtFilename->GetLabel();
}

void pnlRxTSP::InitializeNCOgrid()
{
    fcwFields.clear();
    phoFields.clear();
    ncoRadioButtons.clear();
    phoAngles.clear();
    wxRadioButton *radiobtn;
    wxTextCtrl *fcwField;
    wxTextCtrl *phoField;
    wxStaticText *phoAngle;
    for(int i=0; i<16; ++i)
    {
        int btnId = wxNewId();
        if(i == 0)
            radiobtn = new wxRadioButton(this, btnId, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRB_GROUP, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
        else
            radiobtn = new wxRadioButton(this, btnId, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
        sizerNCOgrid->Add(radiobtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
        ncoRadioButtons.push_back(radiobtn);
        Connect(btnId,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&pnlRxTSP::OnrgrSELSelect);
        fcwField = new wxTextCtrl(this, wxNewId(), wxString::Format("%f", 0.0) , wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
        sizerNCOgrid->Add(fcwField, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
        fcwFields.push_back(fcwField);
        phoField = new wxTextCtrl(this, wxNewId(), wxString::Format("%f", 0.0) , wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
        sizerNCOgrid->Add(phoField, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
        phoFields.push_back(phoField);
        phoAngle = new wxStaticText(this, wxNewId(), "0.0000");
        sizerNCOgrid->Add(phoAngle, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
        phoAngles.push_back(phoAngle);
        Connect(phoField->GetId(),wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&pnlRxTSP::OnPHOAngleChanged);
    }
    ncoRadioButtons[0]->SetValue(true);
}

void pnlRxTSP::SetNCOgrid(const vector<double> &FCW, const vector<int> &PHO)
{
    for(unsigned i=0; i<FCW.size(); ++i)
        fcwFields[i]->SetValue(wxString::Format("%f", FCW[i]));
    for(unsigned i=0; i<PHO.size(); ++i)
        phoFields[i]->SetValue(wxString::Format("%i", PHO[i]));
}


void pnlRxTSP::OnbtnUploadNCOClick(wxCommandEvent& event)
{
    vector<double> fcwValues;
    vector<int> phoValues;

    double dvalue;
    long lvalue;
    for(int i=0; i<16; ++i)
    {
        fcwFields[i]->GetValue().ToDouble(&dvalue);
        fcwValues.push_back(dvalue);
        phoFields[i]->GetValue().ToLong(&lvalue);
        phoValues.push_back(lvalue);
    }
    lmsControl->SetNCOconfiguration(fcwValues, phoValues, true);
}

void pnlRxTSP::OnrgrSELSelect(wxCommandEvent& event)
{
    for(unsigned int i=0; i<ncoRadioButtons.size(); ++i)
        if(ncoRadioButtons[i]->GetId() == event.GetId())
        {
            lmsControl->SetParam(SEL_RX, i);
            break;
        }
}

void pnlRxTSP::OnbtnSetRefClkClick(wxCommandEvent& event)
{
    dlgFloatInput dlg(this, "Reference frequency (MHz):", "Rx NCO Reference Frequency", lmsControl->GetReferenceFrequencyNCO(true));
    if( dlg.ShowModal() == wxID_OK)
    {
        lmsControl->SetReferenceFrequencyNCO(dlg.GetValue(), true);
        lblRefClk->SetLabel(wxString::Format("%f", dlg.GetValue()));
    }
}

void pnlRxTSP::OnPHOAngleChanged(wxCommandEvent& event)
{
    long phoVal = 0;
    for(unsigned i=0; i<phoFields.size(); ++i)
    {
        if(phoFields[i]->GetId() == event.GetId())
        {
            phoFields[i]->GetValue().ToLong(&phoVal);
            phoAngles[i]->SetLabel(wxString::Format("%3.4f", 2.0*180*phoVal/(65536.0)));
            break;
        }
    }
}

void pnlRxTSP::OnbtnLoadDCIClick(wxCommandEvent& event)
{
    unsigned int sample;
    string value = txtDC_REG_RXTSP->GetValue().ToStdString() ;
    sscanf(value.c_str(), "%x", &sample);
    int valToLoad = sample;
    lmsControl->SetParam(DC_REG_RXTSP, valToLoad);
    lmsControl->SetParam(TSGDCLDI_RXTSP, 0);
    lmsControl->SetParam(TSGDCLDI_RXTSP, 1);
    lmsControl->SetParam(TSGDCLDI_RXTSP, 0);
    lmsControl->mDC_REG[0][lmsControl->GetConfigChannel()][1] = valToLoad;
}
/*
void pnlRxTSP::OnbtnCaptureClick(wxCommandEvent& event)
{
    lmsControl->SetParam(CAPTURE, 0);
    lmsControl->SetParam(CAPTURE, 1);
    lmsControl->SetParam(CAPTURE, 0);
    lmsControl->SetAutoDownload(true);
    long value = lmsControl->GetParam(CAPD);
    lmsControl->SetAutoDownload(false);
    lblCAPD->SetLabel( wxString::Format("%#.8X", value));
}
*/
void pnlRxTSP::OnbtnLoadDCQClick(wxCommandEvent& event)
{
    unsigned int sample;
    string value = txtDC_REG_RXTSP->GetValue().ToStdString() ;
    sscanf(value.c_str(), "%x", &sample);
    int valToLoad = sample;
    lmsControl->SetParam(DC_REG_RXTSP, valToLoad);
    lmsControl->SetParam(TSGDCLDQ_RXTSP, 0);
    lmsControl->SetParam(TSGDCLDQ_RXTSP, 1);
    lmsControl->SetParam(TSGDCLDQ_RXTSP, 0);
    lmsControl->mDC_REG[1][lmsControl->GetConfigChannel()][1] = valToLoad;
}

void pnlRxTSP::OnbtnReadAllValuesClick(wxCommandEvent& event)
{
    long value = 0;
    long value2 = 0;
    long valrez = 0;
    //Read RSSI
    lmsControl->SetParam(CAPSEL, 0);
    lmsControl->SetParam(CAPTURE, 0);
    lmsControl->SetParam(CAPTURE, 1);
    lmsControl->SetParam(CAPTURE, 0);
    value = lmsControl->getRegistersMap()->GetRegisterValue(0x040E, true);
    value2 = lmsControl->getRegistersMap()->GetRegisterValue(0x040F, true);
    valrez = ((value & 0x3) | (value2<<2)) & 0x3FFFF;
    lblRSSI->SetLabel( wxString::Format("0x%0.5X", valrez));

    //Read ADCI, ADCQ
    lmsControl->SetParam(CAPSEL, 1);
    lmsControl->SetParam(CAPTURE, 1);
    lmsControl->SetParam(CAPTURE, 0);
    value = lmsControl->getRegistersMap()->GetRegisterValue(0x040E, true);
    value2 = lmsControl->getRegistersMap()->GetRegisterValue(0x040F, true);
    lblADCI->SetLabel( wxString::Format("0x%0.3X", value & 0x3ff));
    lblADCQ->SetLabel( wxString::Format("0x%0.3X", value2& 0x3ff));

    //Read BISTI BSTATE
    lmsControl->SetParam(CAPSEL, 2);
    lmsControl->SetParam(CAPTURE, 1);
    lmsControl->SetParam(CAPTURE, 0);
    value = lmsControl->getRegistersMap()->GetRegisterValue(0x040E, true);
    value2 = lmsControl->getRegistersMap()->GetRegisterValue(0x040F, true);
    valrez = ((value2 << 15) | (value >> 1)) & 0x7FFFFF;
    lblBISTI->SetLabel( wxString::Format("0x%0.6X", valrez));
    lblBSTATE_I->SetLabel( wxString::Format("0x%0.1X", value & 0x1));

    //Read BISTI BSTATE
    lmsControl->SetParam(CAPSEL, 3);
    lmsControl->SetParam(CAPTURE, 1);
    lmsControl->SetParam(CAPTURE, 0);
    value = lmsControl->getRegistersMap()->GetRegisterValue(0x040E, true);
    value2 = lmsControl->getRegistersMap()->GetRegisterValue(0x040F, true);
    valrez = ((value2 << 15) | (value >> 1)) & 0x7FFFFF;
    lblBISTQ->SetLabel( wxString::Format("0x%0.6X", valrez));
    lblBSTATE_Q->SetLabel( wxString::Format("0x%0.1X", value & 0x1));
}

void pnlRxTSP::OnbtnSweepTestClick(wxCommandEvent& event)
{
    if(dlgNCOSweep == NULL)
    {
        dlgNCOSweep = new dlgNCOSweepTest(this);
        dlgNCOSweep->Initialize(lmsControl, true);
        dlgNCOSweep->Show();
    }
    else
        dlgNCOSweep->Show();
}
