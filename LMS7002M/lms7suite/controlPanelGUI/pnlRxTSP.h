/**
@file	pnlRxTSP.h
@author Lime Microsystems
*/

#ifndef pnlRxTSP_H
#define pnlRxTSP_H
//(*Headers(pnlRxTSP)
#include <wx/panel.h>
class wxSpinEvent;
class wxCheckBox;
class wxTextCtrl;
class wxComboBox;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxSpinCtrl;
class wxButton;
class wxStaticBoxSizer;
//*)
class wxTextCtrl;
class wxRadioButton;
#include <map>
#include "RegistersMap.h"
#include "GUIPanel.h"
class LMS7002_MainControl;
class ComboBoxMap;
class dlgNCOSweepTest;
class pnlRxTSP : public wxPanel, GUIPanel
{
public:
    pnlRxTSP(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
    void Initialize(LMS7002_MainControl *pControl);
    void UpdateGUI();
    virtual ~pnlRxTSP();

//(*Declarations(pnlRxTSP)
wxStaticText* StaticText10;
wxStaticText* StaticText22;
wxStaticText* lblBSTATE_Q;
wxStaticText* StaticText9;
ComboBoxMap* cmbCMIX_GAIN_RXTSP;
wxStaticText* StaticText20;
wxRadioBox* rgrTSGFC_RXTSP;
wxStaticText* lblRSSI;
ComboBoxMap* cmbGCORRQ_RXTSP;
wxComboBox* cmbDTHBIT_RX;
wxStaticText* txtPhaseAlpha;
ComboBoxMap* cmbGFIR2_N_RXTSP;
ComboBoxMap* cmbGFIR2_L_RXTSP;
wxStaticText* StaticText29;
wxCheckBox* chkEN_RXTSP;
wxComboBox* rgrAGC_MODE_RXTSP;
ComboBoxMap* cmbAGC_ADESIRED_RXTSP;
wxFlexGridSizer* sizerNCOgrid;
wxButton* btnSweepTest;
wxStaticText* StaticText13;
wxStaticText* StaticText2;
ComboBoxMap* cmbDCCORR_AVG_RXTSP;
wxStaticText* StaticText30;
wxStaticText* StaticText14;
wxCheckBox* chkTSGSWAPIQ_RXTSP;
wxButton* Button1;
wxStaticText* StaticText26;
wxStaticText* StaticText6;
ComboBoxMap* cmbGFIR3_N_RXTSP;
wxStaticText* StaticText19;
wxStaticText* StaticText8;
wxStaticText* StaticText0;
wxStaticText* StaticText11;
wxCheckBox* chkDC_BYP_RXTSP;
wxStaticText* StaticText18;
wxStaticText* StaticText1;
wxStaticText* StaticText27;
wxStaticText* StaticText3;
wxStaticText* lblADCI;
wxButton* btnUploadNCO;
wxStaticText* lblBISTI;
ComboBoxMap* cmbGCORRI_RXTSP;
wxStaticText* StaticText21;
wxCheckBox* chkGC_BYP_RXTSP;
wxStaticText* StaticText23;
wxStaticText* StaticText24;
wxButton* btnLoadGFIR3Coef;
ComboBoxMap* cmbIQCORR_RXTSP;
wxButton* btnLoadDCI;
wxStaticText* lblBSTATE_I;
wxStaticText* lblRefClk;
wxButton* btnSetRefClk;
wxCheckBox* chkGFIR2_BYP_RXTSP;
wxStaticText* StaticText5;
wxStaticText* StaticText7;
ComboBoxMap* cmbGFIR3_L_RXTSP;
wxCheckBox* chkGFIR1_BYP_RXTSP;
wxCheckBox* chkBSTART_RXTSP;
wxRadioBox* rgrINSEL_RXTSP;
wxStaticText* StaticText28;
wxButton* btnLoadDCQ;
wxStaticText* StaticText15;
wxStaticText* StaticText12;
wxRadioBox* rgrTSGMODE_RXTSP;
ComboBoxMap* cmbAGC_AVG_RXTSP;
wxStaticText* lblBISTQ;
wxButton* btnLoadGFIR2Coef;
wxStaticText* StaticText25;
wxButton* btnLoadGFIR1Coef;
wxStaticText* lblADCQ;
ComboBoxMap* cmbHBD_OVR_RXTSP;
wxRadioBox* rgrTSGFCW_RXTSP;
wxStaticText* StaticText17;
wxStaticText* StaticText4;
wxCheckBox* chkGFIR3_BYP_RXTSP;
wxRadioBox* rgrCMIX_SC_RXTSP;
wxCheckBox* chkAGC_BYP_RXTSP;
wxComboBox* rgrMODE;
ComboBoxMap* cmbGFIR1_L_RXTSP;
wxSpinCtrl* spinAGC_K_RXTSP;
wxTextCtrl* txtDC_REG_RXTSP;
wxCheckBox* chkPH_BYP_RXTSP;
wxStaticText* StaticText16;
wxCheckBox* chkCMIX_BYP_RXTSP;
ComboBoxMap* cmbGFIR1_N_RXTSP;
//*)

protected:
//(*Identifiers(pnlRxTSP)
static const long ID_CMIX_SC_RXTSP;
static const long ID_STATICTEXT7;
static const long ID_STATICTEXT34;
static const long ID_STATICTEXT28;
static const long ID_STATICTEXT35;
static const long ID_STATICTEXT29;
static const long ID_STATICTEXT36;
static const long ID_STATICTEXT31;
static const long ID_STATICTEXT38;
static const long ID_STATICTEXT30;
static const long ID_STATICTEXT37;
static const long ID_STATICTEXT32;
static const long ID_STATICTEXT39;
static const long ID_STATICTEXT5;
static const long ID_STATICTEXT6;
static const long ID_BUTTON1;
static const long ID_STATICTEXT33;
static const long ID_CMIX_GAIN_RXTSP;
static const long ID_EN_RXTSP;
static const long ID_BSTART_RXTSP;
static const long ID_STATICTEXT12;
static const long ID_DCCORR_AVG_RXTSP;
static const long ID_STATICTEXT11;
static const long ID_HBD_OVR_RXTSP;
static const long ID_CMIX_BYP_RXTSP;
static const long ID_AGC_BYP_RXTSP;
static const long ID_GFIR3_BYP_RXTSP;
static const long ID_GFIR2_BYP_RXTSP;
static const long ID_GFIR1_BYP_RXTSP;
static const long ID_DC_BYP_RXTSP;
static const long ID_GC_BYP_RXTSP;
static const long ID_PH_BYP_RXTSP;
static const long ID_STATICTEXT13;
static const long ID_GFIR1_L_RXTSP;
static const long ID_STATICTEXT14;
static const long ID_GFIR1_N_RXTSP;
static const long ID_BUTTON2;
static const long ID_STATICTEXT15;
static const long ID_GFIR2_L_RXTSP;
static const long ID_STATICTEXT16;
static const long ID_GFIR2_N_RXTSP;
static const long ID_BUTTON3;
static const long ID_STATICTEXT17;
static const long ID_GFIR3_L_RXTSP;
static const long ID_STATICTEXT18;
static const long ID_GFIR3_N_RXTSP;
static const long ID_BUTTON4;
static const long ID_STATICTEXT1;
static const long ID_AGC_K_RXTSP;
static const long ID_STATICTEXT3;
static const long ID_AGC_AVG_RXTSP;
static const long ID_STATICTEXT2;
static const long ID_AGC_ADESIRED_RXTSP;
static const long ID_STATICTEXT27;
static const long ID_AGC_MODE_RXTSP;
static const long ID_STATICTEXT8;
static const long ID_GCORRQ_RXTSP;
static const long ID_STATICTEXT9;
static const long ID_GCORRI_RXTSP;
static const long ID_STATICTEXT10;
static const long ID_IQCORR_RXTSP;
static const long ID_STATICTEXT19;
static const long ID_STATICTEXT20;
static const long ID_STATICTEXT4;
static const long ID_MODE_RX;
static const long ID_STATICTEXT40;
static const long ID_DTHBIT_RX;
static const long ID_BUTTON5;
static const long ID_STATICTEXT21;
static const long ID_STATICTEXT22;
static const long ID_STATICTEXT23;
static const long ID_BUTTON6;
static const long ID_BUTTON7;
static const long ID_STATICTEXT24;
static const long ID_STATICTEXT25;
static const long ID_TSGSWAPIQ_RXTSP;
static const long ID_TSGFCW_RXTSP;
static const long ID_TSGMODE_RXTSP;
static const long ID_INSEL_RXTSP;
static const long ID_TSGFC_RXTSP;
static const long ID_STATICTEXT26;
static const long ID_DC_REG_RXTSP;
static const long ID_BUTTON_LOADDCI;
static const long ID_BUTTON_LOADDCQ;
//*)

private:
//(*Handlers(pnlRxTSP)
    void ParameterChangeHandler(wxCommandEvent& event);
void OnspinAGC_K_RXTSPChange(wxSpinEvent& event);
void OnbtnLoadGFIR1CoefClick(wxCommandEvent& event);
void OnbtnLoadGFIR2CoefClick(wxCommandEvent& event);
void OnbtnLoadGFIR3CoefClick(wxCommandEvent& event);
void OnbtnReadRSSIClick(wxCommandEvent& event);
void OnbtnUploadNCOClick(wxCommandEvent& event);
void OnrgrSELSelect(wxCommandEvent& event);
void OnbtnSetRefClkClick(wxCommandEvent& event);
void OnPHOAngleChanged(wxCommandEvent& event);
void OnbtnLoadDCIClick(wxCommandEvent& event);
void OnbtnCaptureClick(wxCommandEvent& event);
void OnbtnLoadDCQClick(wxCommandEvent& event);
void OnbtnReadAllValuesClick(wxCommandEvent& event);
void OnbtnSweepTestClick(wxCommandEvent& event);
//*)

protected:
    dlgNCOSweepTest *dlgNCOSweep;
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void AssignEnumsToIds();
    void InitializeNCOgrid();
    void SetNCOgrid(const vector<double> &FCW, const vector<int> &PHO);
    wxString coefFilenames[3];
    vector<wxTextCtrl*> fcwFields;
    vector<wxTextCtrl*> phoFields;
    vector<wxRadioButton*> ncoRadioButtons;
    vector<wxStaticText*> phoAngles;
    DECLARE_EVENT_TABLE()
};
#endif
