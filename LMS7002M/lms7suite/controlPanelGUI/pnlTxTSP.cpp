/**
@file 	pnlTxTSP.cpp
@author	Lime Microsystems
@brief 	TxTSP module panel
*/

#include "pnlTxTSP.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "dlgFloatInput.h"
#include "LMS7002_MainControl.h"
#include "../CommonUtilities.h"
#include "dlgGFIR_Coefficients.h"
#include "dlgNCOSweepTest.h"
//(*InternalHeaders(pnlTxTSP)
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
//(*IdInit(pnlTxTSP)
const long pnlTxTSP::ID_STATICTEXT2 = wxNewId();
const long pnlTxTSP::ID_BSTATE_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT1 = wxNewId();
const long pnlTxTSP::ID_BSIGI_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT3 = wxNewId();
const long pnlTxTSP::ID_BSIGQ_TXTSP = wxNewId();
const long pnlTxTSP::ID_BSTART_TXTSP = wxNewId();
const long pnlTxTSP::ID_BUTTON2 = wxNewId();
const long pnlTxTSP::ID_STATICTEXT4 = wxNewId();
const long pnlTxTSP::ID_GCORRQ_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT5 = wxNewId();
const long pnlTxTSP::ID_GCORRI_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT6 = wxNewId();
const long pnlTxTSP::ID_IQCORR_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT16 = wxNewId();
const long pnlTxTSP::ID_STATICTEXT17 = wxNewId();
const long pnlTxTSP::ID_BUTTON10 = wxNewId();
const long pnlTxTSP::ID_STATICTEXT8 = wxNewId();
const long pnlTxTSP::ID_DCCORRI_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT9 = wxNewId();
const long pnlTxTSP::ID_DCCORRQ_TXTSP = wxNewId();
const long pnlTxTSP::ID_BUTTON11 = wxNewId();
const long pnlTxTSP::ID_BUTTON8 = wxNewId();
const long pnlTxTSP::ID_STATICTEXT7 = wxNewId();
const long pnlTxTSP::ID_HBI_OVR_TXTSP = wxNewId();
const long pnlTxTSP::ID_CMIX_BYP_TXTSP = wxNewId();
const long pnlTxTSP::ID_ISINC_BYP_TXTSP = wxNewId();
const long pnlTxTSP::ID_GFIR3_BYP_TXTSP = wxNewId();
const long pnlTxTSP::ID_GFIR2_BYP_TXTSP = wxNewId();
const long pnlTxTSP::ID_GFIR1_BYP_TXTSP = wxNewId();
const long pnlTxTSP::ID_DC_BYP_TXTSP = wxNewId();
const long pnlTxTSP::ID_GC_BYP_TXTSP = wxNewId();
const long pnlTxTSP::ID_PH_BYP_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT10 = wxNewId();
const long pnlTxTSP::ID_GFIR1_L_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT11 = wxNewId();
const long pnlTxTSP::ID_GFIR1_N_TXTSP = wxNewId();
const long pnlTxTSP::ID_BUTTON3 = wxNewId();
const long pnlTxTSP::ID_STATICTEXT12 = wxNewId();
const long pnlTxTSP::ID_GFIR2_L_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT13 = wxNewId();
const long pnlTxTSP::ID_GFIR2_N_TXTSP = wxNewId();
const long pnlTxTSP::ID_BUTTON4 = wxNewId();
const long pnlTxTSP::ID_STATICTEXT14 = wxNewId();
const long pnlTxTSP::ID_GFIR3_L_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT15 = wxNewId();
const long pnlTxTSP::ID_GFIR3_N_TXTSP = wxNewId();
const long pnlTxTSP::ID_BUTTON5 = wxNewId();
const long pnlTxTSP::ID_EN_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT24 = wxNewId();
const long pnlTxTSP::ID_CMIX_GAIN_TXTSP = wxNewId();
const long pnlTxTSP::ID_CMIX_SC_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT26 = wxNewId();
const long pnlTxTSP::ID_MODE_TX = wxNewId();
const long pnlTxTSP::ID_STATICTEXT25 = wxNewId();
const long pnlTxTSP::ID_DTHBIT_TX = wxNewId();
const long pnlTxTSP::ID_BUTTON7 = wxNewId();
const long pnlTxTSP::ID_STATICTEXT18 = wxNewId();
const long pnlTxTSP::ID_STATICTEXT19 = wxNewId();
const long pnlTxTSP::ID_STATICTEXT20 = wxNewId();
const long pnlTxTSP::ID_BUTTON1 = wxNewId();
const long pnlTxTSP::ID_BUTTON6 = wxNewId();
const long pnlTxTSP::ID_STATICTEXT21 = wxNewId();
const long pnlTxTSP::ID_STATICTEXT22 = wxNewId();
const long pnlTxTSP::ID_TSGSWAPIQ_TXTSP = wxNewId();
const long pnlTxTSP::ID_TSGFCW_TXTSP = wxNewId();
const long pnlTxTSP::ID_TSGMODE_TXTSP = wxNewId();
const long pnlTxTSP::ID_INSEL_TXTSP = wxNewId();
const long pnlTxTSP::ID_TSGFC_TXTSP = wxNewId();
const long pnlTxTSP::ID_STATICTEXT23 = wxNewId();
const long pnlTxTSP::ID_DC_REG_TXTSP = wxNewId();
const long pnlTxTSP::ID_BUTTON_LOADDCI = wxNewId();
const long pnlTxTSP::ID_BUTTON_LOADDCQ = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlTxTSP,wxPanel)
//(*EventTable(pnlTxTSP)
//*)
END_EVENT_TABLE()

void pnlTxTSP::AssignEnumsToIds()
{
    wndId2Enum[ID_MODE_TX] = MODE_TX;
    wndId2Enum[ID_BSTART_TXTSP] = BSTART_TXTSP;
    wndId2Enum[ID_CMIX_BYP_TXTSP] = CMIX_BYP_TXTSP;
    wndId2Enum[ID_CMIX_GAIN_TXTSP] = CMIX_GAIN_TXTSP;
    wndId2Enum[ID_DCCORRI_TXTSP] = DCCORRI_TXTSP;
    wndId2Enum[ID_DCCORRQ_TXTSP] = DCCORRQ_TXTSP;
    wndId2Enum[ID_DC_BYP_TXTSP] = DC_BYP_TXTSP;
    wndId2Enum[ID_EN_TXTSP] = EN_TXTSP;
    wndId2Enum[ID_GCORRI_TXTSP] = GCORRI_TXTSP;
    wndId2Enum[ID_GCORRQ_TXTSP] = GCORRQ_TXTSP;
    wndId2Enum[ID_GC_BYP_TXTSP] = GC_BYP_TXTSP;
    wndId2Enum[ID_GFIR1_BYP_TXTSP] = GFIR1_BYP_TXTSP;
    wndId2Enum[ID_GFIR1_L_TXTSP] = GFIR1_L_TXTSP;
    wndId2Enum[ID_GFIR1_N_TXTSP] = GFIR1_N_TXTSP;
    wndId2Enum[ID_GFIR2_BYP_TXTSP] = GFIR2_BYP_TXTSP;
    wndId2Enum[ID_GFIR2_L_TXTSP] = GFIR2_L_TXTSP;
    wndId2Enum[ID_GFIR2_N_TXTSP] = GFIR2_N_TXTSP;
    wndId2Enum[ID_GFIR3_BYP_TXTSP] = GFIR3_BYP_TXTSP;
    wndId2Enum[ID_GFIR3_L_TXTSP] = GFIR3_L_TXTSP;
    wndId2Enum[ID_GFIR3_N_TXTSP] = GFIR3_N_TXTSP;
    wndId2Enum[ID_HBI_OVR_TXTSP] = HBI_OVR_TXTSP;
    wndId2Enum[ID_IQCORR_TXTSP] = IQCORR_TXTSP;
    wndId2Enum[ID_ISINC_BYP_TXTSP] = ISINC_BYP_TXTSP;
    wndId2Enum[ID_PH_BYP_TXTSP] = PH_BYP_TXTSP;
    wndId2Enum[ID_CMIX_SC_TXTSP] = CMIX_SC_TXTSP;

    wndId2Enum[ID_TSGFCW_TXTSP] = TSGFCW_TXTSP;
    wndId2Enum[ID_TSGSWAPIQ_TXTSP] = TSGSWAPIQ_TXTSP;
    wndId2Enum[ID_TSGMODE_TXTSP] = TSGMODE_TXTSP;
    wndId2Enum[ID_INSEL_TXTSP] = INSEL_TXTSP;
    wndId2Enum[ID_TSGFC_TXTSP] = TSGFC_TXTSP;
    wndId2Enum[ID_DTHBIT_TX] = DTHBIT_TX;
}

pnlTxTSP::pnlTxTSP(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    coefFilenames[0] = "";
    coefFilenames[1] = "";
    coefFilenames[2] = "";
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlTxTSP::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
dlgNCOSweep = NULL;
//(*Initialize(pnlTxTSP)
wxStaticBoxSizer* GFIR2Sizer;
wxStaticBoxSizer* StaticBoxSizer2;
wxFlexGridSizer* FlexGridSizer4;
wxFlexGridSizer* BIST1Sizer;
wxFlexGridSizer* FlexGridSizer10;
wxFlexGridSizer* FlexGridSizer3;
wxFlexGridSizer* GFIR15Sizer;
wxStaticBoxSizer* InterpolationSizer;
wxFlexGridSizer* FlexGridSizer5;
wxFlexGridSizer* FlexGridSizer9;
wxStaticBoxSizer* GFIR1Sizer;
wxFlexGridSizer* FlexGridSizer2;
wxFlexGridSizer* FlexGridSizer7;
wxFlexGridSizer* GFIR37Sizer;
wxStaticBoxSizer* BypassSizer;
wxStaticBoxSizer* IQCorrectorSizer;
wxFlexGridSizer* Interpolation3Sizer;
wxFlexGridSizer* IQCorrector2Sizer;
wxFlexGridSizer* FlexGridSizer8;
wxFlexGridSizer* FlexGridSizer14;
wxStaticBoxSizer* DCCorrectorSizer;
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
wxStaticBoxSizer* GFIR3Sizer;

Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 5);
FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 5);
BISTSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("BIST"));
BIST1Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("BIST state"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
BIST1Sizer->Add(StaticText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblBSTATE_TXTSP = new wxStaticText(this, ID_BSTATE_TXTSP, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BSTATE_TXTSP"));
BIST1Sizer->Add(lblBSTATE_TXTSP, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText0 = new wxStaticText(this, ID_STATICTEXT1, _("BIST signature ch. I"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
BIST1Sizer->Add(StaticText0, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblBSIGI_TXTSP = new wxStaticText(this, ID_BSIGI_TXTSP, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BSIGI_TXTSP"));
BIST1Sizer->Add(lblBSIGI_TXTSP, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("BIST signature ch. Q"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
BIST1Sizer->Add(StaticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
lblBSIGQ_TXTSP = new wxStaticText(this, ID_BSIGQ_TXTSP, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BSIGQ_TXTSP"));
BIST1Sizer->Add(lblBSIGQ_TXTSP, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBSTART_TXTSP = new wxCheckBox(this, ID_BSTART_TXTSP, _("Start BIST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BSTART_TXTSP"));
chkBSTART_TXTSP->SetValue(false);
chkBSTART_TXTSP->SetToolTip(_("Starts delta sigma built in self test. Keep it at 1 one at least three clock cycles"));
BIST1Sizer->Add(chkBSTART_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnReadBIST = new wxButton(this, ID_BUTTON2, _("Read BIST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
BIST1Sizer->Add(btnReadBIST, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
BISTSizer->Add(BIST1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer3->Add(BISTSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
IQCorrectorSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("IQ Corrector"));
IQCorrector2Sizer = new wxFlexGridSizer(0, 2, 0, 5);
IQCorrector2Sizer->AddGrowableCol(0);
StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _("Gain ch. Q"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
IQCorrector2Sizer->Add(StaticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGCORRQ_TXTSP = new ComboBoxMap(this, ID_GCORRQ_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GCORRQ_TXTSP"));
cmbGCORRQ_TXTSP->SetToolTip(_("corrector value, channel Q Unsigned integer"));
IQCorrector2Sizer->Add(cmbGCORRQ_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("Gain ch. I"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
IQCorrector2Sizer->Add(StaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGCORRI_TXTSP = new ComboBoxMap(this, ID_GCORRI_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GCORRI_TXTSP"));
cmbGCORRI_TXTSP->SetToolTip(_("corrector value, channel I Unsigned integer"));
IQCorrector2Sizer->Add(cmbGCORRI_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText5 = new wxStaticText(this, ID_STATICTEXT6, _("Phase corrector"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
IQCorrector2Sizer->Add(StaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbIQCORR_TXTSP = new ComboBoxMap(this, ID_IQCORR_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_IQCORR_TXTSP"));
cmbIQCORR_TXTSP->SetToolTip(_("Phase corrector value (tan(Alpha/2)). Integer, 2\'s complement"));
IQCorrector2Sizer->Add(cmbIQCORR_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText15 = new wxStaticText(this, ID_STATICTEXT16, _("Alpha"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
IQCorrector2Sizer->Add(StaticText15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
txtPhaseAlpha = new wxStaticText(this, ID_STATICTEXT17, _("0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
IQCorrector2Sizer->Add(txtPhaseAlpha, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
btnCalibrateIQ = new wxButton(this, ID_BUTTON10, _("IQ calibration"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
btnCalibrateIQ->Hide();
IQCorrector2Sizer->Add(btnCalibrateIQ, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
IQCorrectorSizer->Add(IQCorrector2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer3->Add(IQCorrectorSizer, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
DCCorrectorSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("DC Corrector"));
DCCorrector4Sizer = new wxFlexGridSizer(0, 2, 0, 5);
DCCorrector4Sizer->AddGrowableCol(0);
StaticText7 = new wxStaticText(this, ID_STATICTEXT8, _("DC ch. I"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
DCCorrector4Sizer->Add(StaticText7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbDCCORRI_TXTSP = new ComboBoxMap(this, ID_DCCORRI_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DCCORRI_TXTSP"));
cmbDCCORRI_TXTSP->SetToolTip(_("DC corrector value, channel I. Integer, 2\'s complement"));
DCCorrector4Sizer->Add(cmbDCCORRI_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText8 = new wxStaticText(this, ID_STATICTEXT9, _("DC ch. Q"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
DCCorrector4Sizer->Add(StaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbDCCORRQ_TXTSP = new ComboBoxMap(this, ID_DCCORRQ_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DCCORRQ_TXTSP"));
cmbDCCORRQ_TXTSP->SetToolTip(_("DC corrector value, channel Q. Integer, 2\'s complement"));
DCCorrector4Sizer->Add(cmbDCCORRQ_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnCalibrateDC_PDET_simple = new wxButton(this, ID_BUTTON11, _("Calibrate DC PDET simple"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
btnCalibrateDC_PDET_simple->Hide();
DCCorrector4Sizer->Add(btnCalibrateDC_PDET_simple, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
btnCalibrateDC_RFLOOP = new wxButton(this, ID_BUTTON8, _("Calibrate DC  RF LOOP"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
DCCorrector4Sizer->Add(btnCalibrateDC_RFLOOP, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
DCCorrectorSizer->Add(DCCorrector4Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer3->Add(DCCorrectorSizer, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
InterpolationSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Interpolation"));
Interpolation3Sizer = new wxFlexGridSizer(0, 2, 0, 0);
Interpolation3Sizer->AddGrowableCol(0);
StaticText6 = new wxStaticText(this, ID_STATICTEXT7, _("HBI ratio"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
Interpolation3Sizer->Add(StaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbHBI_OVR_TXTSP = new ComboBoxMap(this, ID_HBI_OVR_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_HBI_OVR_TXTSP"));
cmbHBI_OVR_TXTSP->SetToolTip(_("HBI interpolation ratio"));
Interpolation3Sizer->Add(cmbHBI_OVR_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
InterpolationSizer->Add(Interpolation3Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer3->Add(InterpolationSizer, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
BypassSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Bypass"));
Bypass8Sizer = new wxFlexGridSizer(0, 2, 0, 0);
chkCMIX_BYP_TXTSP = new wxCheckBox(this, ID_CMIX_BYP_TXTSP, _("CMIX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CMIX_BYP_TXTSP"));
chkCMIX_BYP_TXTSP->SetValue(false);
chkCMIX_BYP_TXTSP->SetToolTip(_("CMIX bypass"));
Bypass8Sizer->Add(chkCMIX_BYP_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkISINC_BYP_TXTSP = new wxCheckBox(this, ID_ISINC_BYP_TXTSP, _("ISINC "), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ISINC_BYP_TXTSP"));
chkISINC_BYP_TXTSP->SetValue(false);
chkISINC_BYP_TXTSP->SetToolTip(_("ISINC bypass"));
Bypass8Sizer->Add(chkISINC_BYP_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkGFIR3_BYP_TXTSP = new wxCheckBox(this, ID_GFIR3_BYP_TXTSP, _("GFIR3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GFIR3_BYP_TXTSP"));
chkGFIR3_BYP_TXTSP->SetValue(false);
chkGFIR3_BYP_TXTSP->SetToolTip(_("GFIR3 bypass"));
Bypass8Sizer->Add(chkGFIR3_BYP_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkGFIR2_BYP_TXTSP = new wxCheckBox(this, ID_GFIR2_BYP_TXTSP, _("GFIR2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GFIR2_BYP_TXTSP"));
chkGFIR2_BYP_TXTSP->SetValue(false);
chkGFIR2_BYP_TXTSP->SetToolTip(_("GFIR2 bypass"));
Bypass8Sizer->Add(chkGFIR2_BYP_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkGFIR1_BYP_TXTSP = new wxCheckBox(this, ID_GFIR1_BYP_TXTSP, _("GFIR1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GFIR1_BYP_TXTSP"));
chkGFIR1_BYP_TXTSP->SetValue(false);
chkGFIR1_BYP_TXTSP->SetToolTip(_("GFIR1 bypass"));
Bypass8Sizer->Add(chkGFIR1_BYP_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkDC_BYP_TXTSP = new wxCheckBox(this, ID_DC_BYP_TXTSP, _("DC corrector"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DC_BYP_TXTSP"));
chkDC_BYP_TXTSP->SetValue(false);
chkDC_BYP_TXTSP->SetToolTip(_("DC corrector bypass"));
Bypass8Sizer->Add(chkDC_BYP_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkGC_BYP_TXTSP = new wxCheckBox(this, ID_GC_BYP_TXTSP, _("Gain corrector"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GC_BYP_TXTSP"));
chkGC_BYP_TXTSP->SetValue(false);
chkGC_BYP_TXTSP->SetToolTip(_("Gain corrector bypass"));
Bypass8Sizer->Add(chkGC_BYP_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPH_BYP_TXTSP = new wxCheckBox(this, ID_PH_BYP_TXTSP, _("Phase corrector"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PH_BYP_TXTSP"));
chkPH_BYP_TXTSP->SetValue(false);
chkPH_BYP_TXTSP->SetToolTip(_("Phase corrector bypass"));
Bypass8Sizer->Add(chkPH_BYP_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
BypassSizer->Add(Bypass8Sizer, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer3->Add(BypassSizer, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
GFIR1Sizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("GFIR1"));
GFIR15Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText9 = new wxStaticText(this, ID_STATICTEXT10, _("Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
GFIR15Sizer->Add(StaticText9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR1_L_TXTSP = new ComboBoxMap(this, ID_GFIR1_L_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GFIR1_L_TXTSP"));
cmbGFIR1_L_TXTSP->SetToolTip(_("Parameter l of GFIR1 (l = roundUp(CoeffN/5)-1). Unsigned integer"));
GFIR15Sizer->Add(cmbGFIR1_L_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText10 = new wxStaticText(this, ID_STATICTEXT11, _("Clock Division Ratio:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
GFIR15Sizer->Add(StaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR1_N_TXTSP = new ComboBoxMap(this, ID_GFIR1_N_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GFIR1_N_TXTSP"));
cmbGFIR1_N_TXTSP->SetToolTip(_("Clock division ratio of GFIR1 is GFIR1_N + 1. Unsigned integer"));
GFIR15Sizer->Add(cmbGFIR1_N_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnLoadGFIR1Coef = new wxButton(this, ID_BUTTON3, _("Coefficients"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
GFIR15Sizer->Add(btnLoadGFIR1Coef, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
GFIR1Sizer->Add(GFIR15Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer3->Add(GFIR1Sizer, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
GFIR2Sizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("GFIR2"));
GFIR26Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText11 = new wxStaticText(this, ID_STATICTEXT12, _("Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
GFIR26Sizer->Add(StaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR2_L_TXTSP = new ComboBoxMap(this, ID_GFIR2_L_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GFIR2_L_TXTSP"));
cmbGFIR2_L_TXTSP->SetToolTip(_("Parameter l of GFIR2 (l = roundUp(CoeffN/5)-1). Unsigned integer"));
GFIR26Sizer->Add(cmbGFIR2_L_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText12 = new wxStaticText(this, ID_STATICTEXT13, _("Clock Division Ratio:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
GFIR26Sizer->Add(StaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR2_N_TXTSP = new ComboBoxMap(this, ID_GFIR2_N_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GFIR2_N_TXTSP"));
cmbGFIR2_N_TXTSP->SetToolTip(_("Clock division ratio of GFIR2 is GFIR2_N + 1. Unsigned integer"));
GFIR26Sizer->Add(cmbGFIR2_N_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnLoadGFIR2Coef = new wxButton(this, ID_BUTTON4, _("Coefficients"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
GFIR26Sizer->Add(btnLoadGFIR2Coef, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
GFIR2Sizer->Add(GFIR26Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer3->Add(GFIR2Sizer, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
GFIR3Sizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("GFIR3"));
GFIR37Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText13 = new wxStaticText(this, ID_STATICTEXT14, _("Length"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
GFIR37Sizer->Add(StaticText13, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR3_L_TXTSP = new ComboBoxMap(this, ID_GFIR3_L_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GFIR3_L_TXTSP"));
cmbGFIR3_L_TXTSP->SetToolTip(_("Parameter l of GFIR3 (l = roundUp(CoeffN/5)-1). Unsigned integer"));
GFIR37Sizer->Add(cmbGFIR3_L_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText14 = new wxStaticText(this, ID_STATICTEXT15, _("Clock Division Ratio:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
GFIR37Sizer->Add(StaticText14, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbGFIR3_N_TXTSP = new ComboBoxMap(this, ID_GFIR3_N_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GFIR3_N_TXTSP"));
cmbGFIR3_N_TXTSP->SetToolTip(_("Clock division ratio of GFIR3 is GFIR3_N + 1. Unsigned integer"));
GFIR37Sizer->Add(cmbGFIR3_N_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
btnLoadGFIR3Coef = new wxButton(this, ID_BUTTON5, _("Coefficients"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
GFIR37Sizer->Add(btnLoadGFIR3Coef, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
GFIR3Sizer->Add(GFIR37Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer3->Add(GFIR3Sizer, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer9 = new wxFlexGridSizer(0, 1, 0, 0);
chkEN_TXTSP = new wxCheckBox(this, ID_EN_TXTSP, _("Enable TxTSP"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_TXTSP"));
chkEN_TXTSP->SetValue(false);
chkEN_TXTSP->SetToolTip(_("TxTSP modules enable"));
FlexGridSizer9->Add(chkEN_TXTSP, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer11 = new wxFlexGridSizer(0, 2, 0, 0);
StaticText21 = new wxStaticText(this, ID_STATICTEXT24, _("CMIX_GAIN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
FlexGridSizer11->Add(StaticText21, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
cmbCMIX_GAIN_TXTSP = new ComboBoxMap(this, ID_CMIX_GAIN_TXTSP, wxEmptyString, wxDefaultPosition, wxSize(80,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CMIX_GAIN_TXTSP"));
cmbCMIX_GAIN_TXTSP->SetToolTip(_("Gain of CMIX output"));
FlexGridSizer11->Add(cmbCMIX_GAIN_TXTSP, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer9->Add(FlexGridSizer11, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer3->Add(FlexGridSizer9, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_1[2] =
{
	_("Upconvert"),
	_("Downconvert")
};
rgrCMIX_SC_TXTSP = new wxRadioBox(this, ID_CMIX_SC_TXTSP, _("CMIX Spectrum control"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CMIX_SC_TXTSP"));
rgrCMIX_SC_TXTSP->SetSelection(0);
rgrCMIX_SC_TXTSP->SetToolTip(_("Spectrum control of CMIX"));
FlexGridSizer3->Add(rgrCMIX_SC_TXTSP, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer1->Add(FlexGridSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("NCO"));
FlexGridSizer2 = new wxFlexGridSizer(3, 1, 0, 0);
FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
FlexGridSizer14 = new wxFlexGridSizer(0, 3, 0, 0);
StaticText23 = new wxStaticText(this, ID_STATICTEXT26, _("Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
FlexGridSizer14->Add(StaticText23, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
rgrMODE = new wxComboBox(this, ID_MODE_TX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_MODE_TX"));
rgrMODE->Append(_("FCW"));
rgrMODE->Append(_("PHO"));
FlexGridSizer14->Add(rgrMODE, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer4->Add(FlexGridSizer14, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer12 = new wxFlexGridSizer(0, 2, 0, 0);
StaticText22 = new wxStaticText(this, ID_STATICTEXT25, _("NCO bits to dither:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
FlexGridSizer12->Add(StaticText22, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
cmbDTHBIT_TX = new wxComboBox(this, ID_DTHBIT_TX, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_DTHBIT_TX"));
cmbDTHBIT_TX->SetSelection( cmbDTHBIT_TX->Append(_("0")) );
cmbDTHBIT_TX->Append(_("1"));
cmbDTHBIT_TX->Append(_("2"));
cmbDTHBIT_TX->Append(_("3"));
cmbDTHBIT_TX->Append(_("4"));
cmbDTHBIT_TX->Append(_("5"));
cmbDTHBIT_TX->Append(_("6"));
cmbDTHBIT_TX->Append(_("7"));
cmbDTHBIT_TX->Append(_("8"));
cmbDTHBIT_TX->Append(_("9"));
cmbDTHBIT_TX->Append(_("10"));
cmbDTHBIT_TX->Append(_("11"));
cmbDTHBIT_TX->Append(_("12"));
cmbDTHBIT_TX->Append(_("13"));
cmbDTHBIT_TX->Append(_("14"));
cmbDTHBIT_TX->Append(_("15"));
cmbDTHBIT_TX->SetToolTip(_("NCO bits to dither"));
FlexGridSizer12->Add(cmbDTHBIT_TX, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
btnSweepTest = new wxButton(this, ID_BUTTON7, _("NCO Sweeping..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
btnSweepTest->Hide();
FlexGridSizer12->Add(btnSweepTest, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer4->Add(FlexGridSizer12, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer2->Add(FlexGridSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
sizerNCOgrid = new wxFlexGridSizer(0, 4, 2, 5);
sizerNCOgrid->Add(-1,-1,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText16 = new wxStaticText(this, ID_STATICTEXT18, _("FCW(MHz)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
sizerNCOgrid->Add(StaticText16, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText17 = new wxStaticText(this, ID_STATICTEXT19, _("PHO"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
sizerNCOgrid->Add(StaticText17, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText18 = new wxStaticText(this, ID_STATICTEXT20, _("Angle"), wxDefaultPosition, wxSize(48,13), 0, _T("ID_STATICTEXT20"));
sizerNCOgrid->Add(StaticText18, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer2->Add(sizerNCOgrid, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer5 = new wxFlexGridSizer(0, 4, 0, 0);
btnUploadNCO = new wxButton(this, ID_BUTTON1, _("Upload NCO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
FlexGridSizer5->Add(btnUploadNCO, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
btnSetRefClk = new wxButton(this, ID_BUTTON6, _("Set Reference Clk"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
FlexGridSizer5->Add(btnSetRefClk, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticText19 = new wxStaticText(this, ID_STATICTEXT21, _("RefClk(MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
FlexGridSizer5->Add(StaticText19, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
lblRefClk = new wxStaticText(this, ID_STATICTEXT22, _("30.72"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
FlexGridSizer5->Add(lblRefClk, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer2->Add(FlexGridSizer5, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer1->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer13 = new wxFlexGridSizer(0, 3, 0, 0);
StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("TSG"));
FlexGridSizer8 = new wxFlexGridSizer(0, 1, 0, 0);
chkTSGSWAPIQ_TXTSP = new wxCheckBox(this, ID_TSGSWAPIQ_TXTSP, _("Swap I and Q signal\n sources from TSG"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TSGSWAPIQ_TXTSP"));
chkTSGSWAPIQ_TXTSP->SetValue(false);
chkTSGSWAPIQ_TXTSP->SetToolTip(_("Swap signals at test signal generator\'s output"));
FlexGridSizer8->Add(chkTSGSWAPIQ_TXTSP, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
wxString __wxRadioBoxChoices_2[2] =
{
	_("TSP clk/8"),
	_("TSP clk/4")
};
rgrTSGFCW_TXTSP = new wxRadioBox(this, ID_TSGFCW_TXTSP, _("TSGFCW"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_TSGFCW_TXTSP"));
rgrTSGFCW_TXTSP->SetToolTip(_("Set frequency of TSG\'s NCO"));
FlexGridSizer7->Add(rgrTSGFCW_TXTSP, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_3[2] =
{
	_("NCO"),
	_("DC source")
};
rgrTSGMODE_TXTSP = new wxRadioBox(this, ID_TSGMODE_TXTSP, _("TSGMODE"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_3, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_TSGMODE_TXTSP"));
rgrTSGMODE_TXTSP->SetToolTip(_("Test signal generator mode"));
FlexGridSizer7->Add(rgrTSGMODE_TXTSP, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_4[2] =
{
	_("LML output"),
	_("Test signal")
};
rgrINSEL_TXTSP = new wxRadioBox(this, ID_INSEL_TXTSP, _("Input source"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_4, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_INSEL_TXTSP"));
rgrINSEL_TXTSP->SetToolTip(_("Input source of TxTSP"));
FlexGridSizer7->Add(rgrINSEL_TXTSP, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer8->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer10 = new wxFlexGridSizer(0, 1, 0, 0);
wxString __wxRadioBoxChoices_5[2] =
{
	_("-6dB"),
	_("Full scale")
};
rgrTSGFC_TXTSP = new wxRadioBox(this, ID_TSGFC_TXTSP, _("TSGFC"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_5, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_TSGFC_TXTSP"));
rgrTSGFC_TXTSP->SetToolTip(_("TSG full scale control"));
FlexGridSizer10->Add(rgrTSGFC_TXTSP, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
StaticText20 = new wxStaticText(this, ID_STATICTEXT23, _("DC_REG(hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
FlexGridSizer6->Add(StaticText20, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
txtDC_REG_TXTSP = new wxTextCtrl(this, ID_DC_REG_TXTSP, _("ffff"), wxDefaultPosition, wxSize(76,-1), 0, wxDefaultValidator, _T("ID_DC_REG_TXTSP"));
FlexGridSizer6->Add(txtDC_REG_TXTSP, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
btnLoadDCI = new wxButton(this, ID_BUTTON_LOADDCI, _("Load to DC I"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOADDCI"));
FlexGridSizer6->Add(btnLoadDCI, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
btnLoadDCQ = new wxButton(this, ID_BUTTON_LOADDCQ, _("Load to DC Q"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOADDCQ"));
FlexGridSizer6->Add(btnLoadDCQ, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer10->Add(FlexGridSizer6, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer8->Add(FlexGridSizer10, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer2->Add(FlexGridSizer8, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer13->Add(StaticBoxSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer1->Add(FlexGridSizer13, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_BSTART_TXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnReadBISTClick);
Connect(ID_GCORRQ_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_GCORRI_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_IQCORR_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnCalibrateIQClick);
Connect(ID_DCCORRI_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_DCCORRQ_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnCalibrateDC_PDET_simpleClick);
Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnCalibrateDC_RFLOOPClick);
Connect(ID_HBI_OVR_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_CMIX_BYP_TXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_ISINC_BYP_TXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_GFIR3_BYP_TXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_GFIR2_BYP_TXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_GFIR1_BYP_TXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_DC_BYP_TXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_GC_BYP_TXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_PH_BYP_TXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_GFIR1_L_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_GFIR1_N_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnLoadGFIR1CoefClick);
Connect(ID_GFIR2_L_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_GFIR2_N_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnLoadGFIR2CoefClick);
Connect(ID_GFIR3_L_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_GFIR3_N_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnLoadGFIR3CoefClick);
Connect(ID_EN_TXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_CMIX_GAIN_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_CMIX_SC_TXTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_MODE_TX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_DTHBIT_TX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnSweepTestClick);
Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnUploadNCOClick);
Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnSetRefClkClick);
Connect(ID_TSGSWAPIQ_TXTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_TSGFCW_TXTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_TSGMODE_TXTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_INSEL_TXTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_TSGFC_TXTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlTxTSP::ParameterChangeHandler);
Connect(ID_BUTTON_LOADDCI,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnLoadDCIClick);
Connect(ID_BUTTON_LOADDCQ,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlTxTSP::OnbtnLoadDCQClick);
//*)
    InitializeNCOgrid();
}
pnlTxTSP::~pnlTxTSP()
{
//(*Destroy(pnlTxTSP)
//*)
}
void pnlTxTSP::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlTxTSP panel don't have control module assigned" << std::endl;
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
    case IQCORR_TXTSP: // when changed recalculate alpha text field
        evtint = event.GetInt();
        atangent = atan( evtint/2048.0 );
        angle = atangent * 180/3.141596;
        txtPhaseAlpha->SetLabel( wxString::Format("%.3f", angle));
        lmsControl->SetParam( parameter, event.GetInt());
        break;
    case HBI_OVR_TXTSP:
        lmsControl->SetParam( parameter, (event.GetInt()==5) ? 7 : event.GetInt());
        break;
    case TSGFCW_TXTSP:
        lmsControl->SetParam( parameter, event.GetInt()+1);
        break;
    default:
        lmsControl->SetParam( parameter, event.GetInt());
        //std::cout << "control id " << event.GetId() << " value " << event.GetInt() << std::endl;
    }
}

void pnlTxTSP::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    char ctemp[80];
    vector<cmbKeyValuePair> keyvalues;
    vector<string> temp;
    temp.clear();
    temp.push_back("0 dB");
    temp.push_back("+6 dB");
    temp.push_back("-6 dB");
    cmbCMIX_GAIN_TXTSP->Clear();
    cmbCMIX_GAIN_TXTSP->Append(temp);

    keyvalues.clear();
    for(int i=-128; i<=127; ++i)
    {
        sprintf(ctemp, "%i", i);
        keyvalues.push_back(cmbKeyValuePair(i, ctemp));
    }
    cmbDCCORRI_TXTSP->Clear();
    cmbDCCORRI_TXTSP->Set(keyvalues);
    cmbDCCORRQ_TXTSP->Clear();
    cmbDCCORRQ_TXTSP->Set(keyvalues);

    temp.clear();
    for(int i=0; i<2048; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGCORRI_TXTSP->Clear();
    cmbGCORRI_TXTSP->Append(temp);

    temp.clear();
    for(int i=0; i<2048; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGCORRQ_TXTSP->Clear();
    cmbGCORRQ_TXTSP->Append(temp);

    temp.clear();
    for(int i=0; i<8; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR1_L_TXTSP->Clear();
    cmbGFIR1_L_TXTSP->Append(temp);

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR1_N_TXTSP->Clear();
    cmbGFIR1_N_TXTSP->Append(temp);

    temp.clear();
    for(int i=0; i<8; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR2_L_TXTSP->Clear();
    cmbGFIR2_L_TXTSP->Append(temp);

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR2_N_TXTSP->Clear();
    cmbGFIR2_N_TXTSP->Append(temp);

    temp.clear();
    for(int i=0; i<8; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR3_L_TXTSP->Clear();
    cmbGFIR3_L_TXTSP->Append(temp);

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGFIR3_N_TXTSP->Clear();
    cmbGFIR3_N_TXTSP->Append(temp);

    temp.clear();
    temp.push_back("2^1");
    temp.push_back("2^2");
    temp.push_back("2^3");
    temp.push_back("2^4");
    temp.push_back("2^5");
    temp.push_back("Bypass");
    cmbHBI_OVR_TXTSP->Clear();
    cmbHBI_OVR_TXTSP->Append(temp);

    keyvalues.clear();
    for(int i=-2048; i<2048; ++i)
    {
        sprintf(ctemp, "%i", i);
        keyvalues.push_back(cmbKeyValuePair(i, ctemp));
    }
    cmbIQCORR_TXTSP->Clear();
    cmbIQCORR_TXTSP->Set(keyvalues);
    UpdateTooltips(this);
    UpdateGUI(); // sets default selections

}

void pnlTxTSP::UpdateGUI()
{
    float refClk = lmsControl->GetReferenceFrequencyNCO(false);
    lblRefClk->SetLabel(wxString::Format("%f", refClk));
    unsigned long value = 0;
    value = lmsControl->GetParam(BSTART_TXTSP);
    chkBSTART_TXTSP->SetValue(value);

    value = lmsControl->GetParam(CMIX_BYP_TXTSP);
    chkCMIX_BYP_TXTSP->SetValue(value);

    value = lmsControl->GetParam(CMIX_GAIN_TXTSP);
    cmbCMIX_GAIN_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(DCCORRI_TXTSP);
    cmbDCCORRI_TXTSP->SetSelection( (char)value);

    value = lmsControl->GetParam(DCCORRQ_TXTSP);
    cmbDCCORRQ_TXTSP->SetSelection( (char)value);

    value = lmsControl->GetParam(DC_BYP_TXTSP);
    chkDC_BYP_TXTSP->SetValue(value);

    value = lmsControl->GetParam(EN_TXTSP);
    chkEN_TXTSP->SetValue(value);

    value = lmsControl->GetParam(GCORRI_TXTSP);
    cmbGCORRI_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(GCORRQ_TXTSP);
    cmbGCORRQ_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(GC_BYP_TXTSP);
    chkGC_BYP_TXTSP->SetValue(value);

    value = lmsControl->GetParam(GFIR1_BYP_TXTSP);
    chkGFIR1_BYP_TXTSP->SetValue(value);

    value = lmsControl->GetParam(GFIR1_L_TXTSP);
    cmbGFIR1_L_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(GFIR1_N_TXTSP);
    cmbGFIR1_N_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(GFIR2_BYP_TXTSP);
    chkGFIR2_BYP_TXTSP->SetValue(value);

    value = lmsControl->GetParam(GFIR2_L_TXTSP);
    cmbGFIR2_L_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(GFIR2_N_TXTSP);
    cmbGFIR2_N_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(GFIR3_BYP_TXTSP);
    chkGFIR3_BYP_TXTSP->SetValue(value);

    value = lmsControl->GetParam(GFIR3_L_TXTSP);
    cmbGFIR3_L_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(GFIR3_N_TXTSP);
    cmbGFIR3_N_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(HBI_OVR_TXTSP);
    if(value == 7) //change value to combo box index
        value = 5;
    cmbHBI_OVR_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(IQCORR_TXTSP);
    short iqcorr_val = value;
    iqcorr_val = (iqcorr_val & 0x800) ? iqcorr_val|0xF000 : iqcorr_val;
    cmbIQCORR_TXTSP->SetSelection(iqcorr_val);

    value = lmsControl->GetParam(ISINC_BYP_TXTSP);
    chkISINC_BYP_TXTSP->SetValue(value);

    value = lmsControl->GetParam(PH_BYP_TXTSP);
    chkPH_BYP_TXTSP->SetValue(value);

    value = lmsControl->GetParam(MODE_TX);
    rgrMODE->SetSelection(value);

    value = lmsControl->GetParam(DTHBIT_TX);
    cmbDTHBIT_TX->SetSelection(value);

    value = lmsControl->GetParam(SEL_TX);
    if(value < ncoRadioButtons.size())
        ncoRadioButtons[value]->SetValue(true);

    value = lmsControl->GetParam(TSGFCW_TXTSP);
    if(value == 1)
        value = 0;
    else if(value == 2)
        value = 1;
    rgrTSGFCW_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(TSGMODE_TXTSP);
    rgrTSGMODE_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(INSEL_TXTSP);
    rgrINSEL_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(TSGSWAPIQ_TXTSP);
    chkTSGSWAPIQ_TXTSP->SetValue(value);

    value = lmsControl->GetParam(TSGFC_TXTSP);
    rgrTSGFC_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(DC_REG_TXTSP);
    txtDC_REG_TXTSP->SetValue( wxString::Format("%lx", value));

    vector<double> fcwFreqs;
    vector<int> phoCodes;
    lmsControl->GetNCOconfiguration(fcwFreqs, phoCodes, false);
    SetNCOgrid(fcwFreqs, phoCodes);    
}

void pnlTxTSP::OnbtnReadBISTClick(wxCommandEvent& event)
{
    lmsControl->SetAutoDownload(true);
    int value;
    value = lmsControl->GetParam(BSTATE_TXTSP);
    lblBSTATE_TXTSP->SetLabel(wxString::Format("%i", value));
    value = lmsControl->GetParam(BSIGI_TXTSP);
    lblBSIGI_TXTSP->SetLabel(wxString::Format("0x%0.6X", value));
    value = lmsControl->GetParam(BSIGQ_TXTSP);
    lblBSIGQ_TXTSP->SetLabel(wxString::Format("0x%0.6X", value));
    lmsControl->SetAutoDownload(false);
}

void pnlTxTSP::OnbtnLoadGFIR1CoefClick(wxCommandEvent& event)
{
    dlgGFIR_Coefficients dlg;
    dlg.Initialize(lmsControl, coefFilenames[0], 1, false);
    dlg.ShowModal();

    coefFilenames[0] = dlg.txtFilename->GetLabel();
}

void pnlTxTSP::OnbtnLoadGFIR2CoefClick(wxCommandEvent& event)
{
    dlgGFIR_Coefficients dlg;
    dlg.Initialize(lmsControl, coefFilenames[1], 2, false);
    dlg.ShowModal();

    coefFilenames[1] = dlg.txtFilename->GetLabel();
}

void pnlTxTSP::OnbtnLoadGFIR3CoefClick(wxCommandEvent& event)
{
    dlgGFIR_Coefficients dlg;
    dlg.Initialize(lmsControl, coefFilenames[2], 3, false);
    dlg.ShowModal();

    coefFilenames[2] = dlg.txtFilename->GetLabel();
}

void pnlTxTSP::InitializeNCOgrid()
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
        Connect(btnId,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&pnlTxTSP::OnrgrSELSelect);
        fcwField = new wxTextCtrl(this, wxNewId(), wxString::Format("%f", 0.0) , wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
        sizerNCOgrid->Add(fcwField, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
        fcwFields.push_back(fcwField);
        phoField = new wxTextCtrl(this, wxNewId(), wxString::Format("%f", 0.0) , wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
        sizerNCOgrid->Add(phoField, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
        phoFields.push_back(phoField);
        phoAngle = new wxStaticText(this, wxNewId(), "0.0000");
        sizerNCOgrid->Add(phoAngle, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
        phoAngles.push_back(phoAngle);
        Connect(phoField->GetId(),wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&pnlTxTSP::OnPHOAngleChanged);
    }
    ncoRadioButtons[0]->SetValue(true);
}

void pnlTxTSP::SetNCOgrid(const vector<double> &FCW, const vector<int> &PHO)
{
    for(unsigned i=0; i<FCW.size(); ++i)
        fcwFields[i]->SetValue(wxString::Format("%f", FCW[i]));
    for(unsigned i=0; i<PHO.size(); ++i)
        phoFields[i]->SetValue(wxString::Format("%i", PHO[i]));
}

void pnlTxTSP::OnbtnUploadNCOClick(wxCommandEvent& event)
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
    lmsControl->SetNCOconfiguration(fcwValues, phoValues, false);
}

void pnlTxTSP::OnrgrSELSelect(wxCommandEvent& event)
{
    for(unsigned int i=0; i<ncoRadioButtons.size(); ++i)
        if(ncoRadioButtons[i]->GetId() == event.GetId())
        {
            lmsControl->SetParam(SEL_TX, i);
            break;
        }
}

void pnlTxTSP::OnbtnSetRefClkClick(wxCommandEvent& event)
{
    dlgFloatInput dlg(this, "Reference frequency (MHz):", "Tx NCO Reference Frequency", lmsControl->GetReferenceFrequencyNCO(false));
    if( dlg.ShowModal() == wxID_OK)
    {
        lmsControl->SetReferenceFrequencyNCO(dlg.GetValue(), false);
        lblRefClk->SetLabel(wxString::Format("%f", dlg.GetValue()));
    }
}

void pnlTxTSP::OnPHOAngleChanged(wxCommandEvent& event)
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

void pnlTxTSP::OnbtnLoadDCIClick(wxCommandEvent& event)
{
    unsigned int sample;
    string value = txtDC_REG_TXTSP->GetValue().ToStdString() ;
    sscanf(value.c_str(), "%x", &sample);
    int valToLoad = sample;
    lmsControl->SetParam(DC_REG_TXTSP, valToLoad);
    lmsControl->SetParam(TSGDCLDI_TXTSP, 0);
    lmsControl->SetParam(TSGDCLDI_TXTSP, 1);
    lmsControl->SetParam(TSGDCLDI_TXTSP, 0);
    lmsControl->mDC_REG[0][lmsControl->GetConfigChannel()][0] = valToLoad;
}

void pnlTxTSP::OnbtnLoadDCQClick(wxCommandEvent& event)
{
    unsigned int sample;
    string value = txtDC_REG_TXTSP->GetValue().ToStdString() ;
    sscanf(value.c_str(), "%x", &sample);
    int valToLoad = sample;
    lmsControl->SetParam(DC_REG_TXTSP, valToLoad);
    lmsControl->SetParam(TSGDCLDQ_TXTSP, 0);
    lmsControl->SetParam(TSGDCLDQ_TXTSP, 1);
    lmsControl->SetParam(TSGDCLDQ_TXTSP, 0);
    lmsControl->mDC_REG[1][lmsControl->GetConfigChannel()][0] = valToLoad;
}

void pnlTxTSP::OnbtnSweepTestClick(wxCommandEvent& event)
{
    if(dlgNCOSweep == NULL)
    {
        dlgNCOSweep = new dlgNCOSweepTest(this);
        dlgNCOSweep->Initialize(lmsControl, false);
        dlgNCOSweep->Show();
    }
    else
        dlgNCOSweep->Show();
}

void pnlTxTSP::OnbtnCalibrateDC_PDET_simpleClick(wxCommandEvent& event)
{
    if(lmsControl->algorithms->DCCalibrationTX_PDET() != 0)
        wxMessageBox(_("DC Calibration failed"),_("Error"),wxCLOSE,this);
    else
        wxMessageBox(_("DC Calibration Finished"),_("Info"),wxOK,this);
    lmsControl->DownloadAll();
    UpdateGUI();
}

void pnlTxTSP::OnbtnCalibrateIQClick(wxCommandEvent& event)
{
    if(lmsControl->algorithms->TXIQCalibration() != 0)
        wxMessageBox(_("IQ Calibration failed"),_("Error"),wxCLOSE,this);
    else
        wxMessageBox(_("IQ Calibration Finished"),_("Info"),wxOK,this);
    lmsControl->DownloadAll();
    UpdateGUI();
}

void pnlTxTSP::OnbtnCalibrateDC_RFLOOPClick(wxCommandEvent& event)
{
    if(lmsControl->algorithms->DCCalibrationTX_RFLOOP(true) != 0)
        wxMessageBox(_("TX DC Calibration failed"),_("Error"),wxCLOSE,this);
    else
        wxMessageBox(_("TX DC Calibration Finished"),_("Info"),wxOK,this);
    lmsControl->DownloadAll();
    UpdateGUI();
}

void pnlTxTSP::OnPaint(wxPaintEvent& event)
{
}

void pnlTxTSP::OnbtnTxDcMCUClick(wxCommandEvent& event)
{
    if(lmsControl->algorithms->DCCalibrationTX_RFLOOP_MCU(true) != 0)
        wxMessageBox(_("TX DC Calibration failed"),_("Error"),wxCLOSE,this);
    else
        wxMessageBox(_("TX DC Calibration Finished"),_("Info"),wxOK,this);
    UpdateGUI();
}
