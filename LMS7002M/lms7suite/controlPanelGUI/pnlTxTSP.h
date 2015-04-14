/**
@file 	pnlTxTSP.cpp
@author	Lime Microsystems
*/

#ifndef pnlTxTSP_H
#define pnlTxTSP_H
//(*Headers(pnlTxTSP)
#include <wx/panel.h>
class wxCheckBox;
class wxTextCtrl;
class wxComboBox;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
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
class pnlTxTSP : public wxPanel, GUIPanel
{
public:
    pnlTxTSP(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
    void Initialize(LMS7002_MainControl *pControl);
    void UpdateGUI();
    virtual ~pnlTxTSP();

//(*Declarations(pnlTxTSP)
wxRadioBox* rgrTSGFC_TXTSP;
wxStaticText* StaticText10;
wxStaticText* StaticText22;
wxStaticText* StaticText9;
wxStaticText* StaticText20;
wxStaticText* txtPhaseAlpha;
ComboBoxMap* cmbIQCORR_TXTSP;
wxRadioBox* rgrTSGFCW_TXTSP;
ComboBoxMap* cmbGCORRQ_TXTSP;
ComboBoxMap* cmbDCCORRQ_TXTSP;
wxFlexGridSizer* sizerNCOgrid;
wxCheckBox* chkGC_BYP_TXTSP;
wxCheckBox* chkISINC_BYP_TXTSP;
wxButton* btnSweepTest;
wxStaticText* StaticText13;
wxStaticText* lblBSIGI_TXTSP;
wxStaticText* StaticText2;
wxRadioBox* rgrINSEL_TXTSP;
wxButton* btnCalibrateIQ;
wxStaticText* StaticText14;
wxStaticText* StaticText6;
wxRadioBox* rgrTSGMODE_TXTSP;
wxStaticText* lblBSIGQ_TXTSP;
wxCheckBox* chkBSTART_TXTSP;
wxStaticText* StaticText19;
wxStaticText* StaticText8;
wxStaticText* StaticText0;
wxStaticText* StaticText11;
ComboBoxMap* cmbDCCORRI_TXTSP;
wxStaticText* StaticText18;
wxCheckBox* chkGFIR2_BYP_TXTSP;
wxCheckBox* chkEN_TXTSP;
wxStaticText* StaticText1;
wxStaticText* StaticText3;
wxButton* btnUploadNCO;
wxStaticText* StaticText21;
ComboBoxMap* cmbCMIX_GAIN_TXTSP;
wxStaticText* StaticText23;
ComboBoxMap* cmbGFIR3_L_TXTSP;
ComboBoxMap* cmbGFIR2_N_TXTSP;
ComboBoxMap* cmbHBI_OVR_TXTSP;
wxButton* btnLoadGFIR3Coef;
wxRadioBox* rgrCMIX_SC_TXTSP;
wxCheckBox* chkDC_BYP_TXTSP;
ComboBoxMap* cmbGCORRI_TXTSP;
wxButton* btnLoadDCI;
wxStaticText* lblRefClk;
wxButton* btnSetRefClk;
wxStaticText* StaticText5;
ComboBoxMap* cmbGFIR1_N_TXTSP;
wxStaticText* StaticText7;
ComboBoxMap* cmbGFIR1_L_TXTSP;
wxComboBox* cmbDTHBIT_TX;
wxCheckBox* chkPH_BYP_TXTSP;
wxCheckBox* chkGFIR1_BYP_TXTSP;
wxCheckBox* chkGFIR3_BYP_TXTSP;
wxButton* btnLoadDCQ;
wxStaticText* StaticText15;
wxButton* btnReadBIST;
wxTextCtrl* txtDC_REG_TXTSP;
wxStaticText* StaticText12;
ComboBoxMap* cmbGFIR2_L_TXTSP;
wxButton* btnCalibrateDC_RFLOOP;
wxCheckBox* chkTSGSWAPIQ_TXTSP;
ComboBoxMap* cmbGFIR3_N_TXTSP;
wxButton* btnLoadGFIR2Coef;
wxButton* btnLoadGFIR1Coef;
wxStaticText* StaticText17;
wxStaticText* StaticText4;
wxComboBox* rgrMODE;
wxStaticText* StaticText16;
wxCheckBox* chkCMIX_BYP_TXTSP;
wxStaticText* lblBSTATE_TXTSP;
wxButton* btnCalibrateDC_PDET_simple;
//*)

protected:
//(*Identifiers(pnlTxTSP)
static const long ID_STATICTEXT2;
static const long ID_BSTATE_TXTSP;
static const long ID_STATICTEXT1;
static const long ID_BSIGI_TXTSP;
static const long ID_STATICTEXT3;
static const long ID_BSIGQ_TXTSP;
static const long ID_BSTART_TXTSP;
static const long ID_BUTTON2;
static const long ID_STATICTEXT4;
static const long ID_GCORRQ_TXTSP;
static const long ID_STATICTEXT5;
static const long ID_GCORRI_TXTSP;
static const long ID_STATICTEXT6;
static const long ID_IQCORR_TXTSP;
static const long ID_STATICTEXT16;
static const long ID_STATICTEXT17;
static const long ID_BUTTON10;
static const long ID_STATICTEXT8;
static const long ID_DCCORRI_TXTSP;
static const long ID_STATICTEXT9;
static const long ID_DCCORRQ_TXTSP;
static const long ID_BUTTON11;
static const long ID_BUTTON8;
static const long ID_STATICTEXT7;
static const long ID_HBI_OVR_TXTSP;
static const long ID_CMIX_BYP_TXTSP;
static const long ID_ISINC_BYP_TXTSP;
static const long ID_GFIR3_BYP_TXTSP;
static const long ID_GFIR2_BYP_TXTSP;
static const long ID_GFIR1_BYP_TXTSP;
static const long ID_DC_BYP_TXTSP;
static const long ID_GC_BYP_TXTSP;
static const long ID_PH_BYP_TXTSP;
static const long ID_STATICTEXT10;
static const long ID_GFIR1_L_TXTSP;
static const long ID_STATICTEXT11;
static const long ID_GFIR1_N_TXTSP;
static const long ID_BUTTON3;
static const long ID_STATICTEXT12;
static const long ID_GFIR2_L_TXTSP;
static const long ID_STATICTEXT13;
static const long ID_GFIR2_N_TXTSP;
static const long ID_BUTTON4;
static const long ID_STATICTEXT14;
static const long ID_GFIR3_L_TXTSP;
static const long ID_STATICTEXT15;
static const long ID_GFIR3_N_TXTSP;
static const long ID_BUTTON5;
static const long ID_EN_TXTSP;
static const long ID_STATICTEXT24;
static const long ID_CMIX_GAIN_TXTSP;
static const long ID_CMIX_SC_TXTSP;
static const long ID_STATICTEXT26;
static const long ID_MODE_TX;
static const long ID_STATICTEXT25;
static const long ID_DTHBIT_TX;
static const long ID_BUTTON7;
static const long ID_STATICTEXT18;
static const long ID_STATICTEXT19;
static const long ID_STATICTEXT20;
static const long ID_BUTTON1;
static const long ID_BUTTON6;
static const long ID_STATICTEXT21;
static const long ID_STATICTEXT22;
static const long ID_TSGSWAPIQ_TXTSP;
static const long ID_TSGFCW_TXTSP;
static const long ID_TSGMODE_TXTSP;
static const long ID_INSEL_TXTSP;
static const long ID_TSGFC_TXTSP;
static const long ID_STATICTEXT23;
static const long ID_DC_REG_TXTSP;
static const long ID_BUTTON_LOADDCI;
static const long ID_BUTTON_LOADDCQ;
//*)

private:
//(*Handlers(pnlTxTSP)
    void ParameterChangeHandler(wxCommandEvent& event);
void OnbtnReadBISTClick(wxCommandEvent& event);
void OnbtnLoadGFIR1CoefClick(wxCommandEvent& event);
void OnbtnLoadGFIR2CoefClick(wxCommandEvent& event);
void OnbtnLoadGFIR3CoefClick(wxCommandEvent& event);
void OnbtnUploadNCOClick(wxCommandEvent& event);
void OnrgrSELSelect(wxCommandEvent& event);
void OnbtnSetRefClkClick(wxCommandEvent& event);
void OnPHOAngleChanged(wxCommandEvent& event);
void OnbtnLoadDCIClick(wxCommandEvent& event);
void OnbtnLoadDCQClick(wxCommandEvent& event);
void OnbtnSweepTestClick(wxCommandEvent& event);
void OnbtnCalibrateDC_PDET_simpleClick(wxCommandEvent& event);
void OnbtnCalibrateIQClick(wxCommandEvent& event);
void OnbtnCalibrateDC_RFLOOPClick(wxCommandEvent& event);
void OnPaint(wxPaintEvent& event);
void OnbtnTxDcMCUClick(wxCommandEvent& event);
//*)
dlgNCOSweepTest* dlgNCOSweep;

protected:
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
