/**
@file 	pnlCLKGEN.h
@author	Lime Microsystems
*/

#ifndef pnlCLKGEN_H
#define pnlCLKGEN_H
//(*Headers(pnlCLKGEN)
#include <wx/panel.h>
class wxCheckBox;
class wxTextCtrl;
class wxComboBox;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxBoxSizer;
class wxButton;
class wxStaticBoxSizer;
//*)
#include <map>
#include "RegistersMap.h"
#include "GUIPanel.h"
class LMS7002_MainControl;
class ComboBoxMap;
class pnlCLKGEN : public wxPanel, GUIPanel
{
public:
    pnlCLKGEN(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
    void Initialize(LMS7002_MainControl *pControl);
    void UpdateGUI();
    void UpdateReadOnlyValues();
    virtual ~pnlCLKGEN();

//(*Declarations(pnlCLKGEN)
wxStaticText* StaticText10;
wxStaticText* StaticText9;
wxStaticText* StaticText20;
ComboBoxMap* cmbIPULSE_CP_CGEN;
wxStaticText* lblVCOfreq;
wxButton* btnUpdateValues;
wxCheckBox* chkPD_SDM_CGEN;
ComboBoxMap* cmbCP2_CGEN;
wxStaticText* lblRefClk_MHz;
wxStaticText* StaticText13;
wxStaticText* StaticText2;
wxStaticText* StaticText14;
wxCheckBox* chkEN_COARSE_CKLGEN;
ComboBoxMap* cmbCP3_CGEN;
wxStaticText* StaticText26;
wxStaticText* StaticText6;
wxCheckBox* chkEN_INTONLY_SDM_CGEN;
ComboBoxMap* cmbCZ_CGEN;
wxStaticText* lblFRAC_SDM;
wxStaticText* lblRealOutFrequency;
wxStaticText* StaticText8;
wxStaticText* StaticText0;
wxStaticText* StaticText11;
wxButton* btnTune;
wxStaticText* StaticText18;
wxCheckBox* chkPD_CP_CGEN;
wxCheckBox* chkREV_SDMCLK_CGEN;
wxStaticText* lblVCO_CMPHO_CGEN;
wxStaticText* StaticText1;
wxStaticText* StaticText3;
ComboBoxMap* cmbICT_VCO_CGEN;
wxTextCtrl* txtFrequencyCLKL;
wxStaticText* lblCOARSE_STEPDONE_CGEN;
wxStaticText* StaticText24;
wxButton* btnCalculate;
wxTextCtrl* txtFrequency;
ComboBoxMap* cmbTST_CGEN;
wxCheckBox* chkCOARSE_START_CGEN;
wxStaticText* StaticText5;
wxStaticText* StaticText7;
wxCheckBox* chkPD_FDIV_FB_CGEN;
wxStaticText* lblCOARSEPLL_COMPO_CGEN;
wxCheckBox* chkREV_CLKDAC_CGEN;
wxCheckBox* chkEN_G_CGEN;
wxCheckBox* chkPD_FDIV_O_CGEN;
wxCheckBox* chkRESET_N_CGEN;
wxRadioBox* rgrSEL_SDMCLK_CGEN;
ComboBoxMap* cmbCLKH_OV_CLKL_CGEN;
wxButton* btnShowVCO;
wxStaticText* StaticText15;
wxStaticText* StaticText12;
wxCheckBox* chkPD_VCO_CGEN;
wxCheckBox* chkEN_SDM_CLK_CGEN;
wxCheckBox* chkREVPH_PFD_CGEN;
wxCheckBox* chkREV_CLKADC_CGEN;
wxCheckBox* chkEN_SDM_TSTO_CGEN;
wxStaticText* lblVCO_CMPLO_CGEN;
ComboBoxMap* cmbIOFFSET_CP_CGEN;
ComboBoxMap* cmbCSW_VCO_CGEN;
wxStaticText* StaticText17;
wxStaticText* StaticText4;
ComboBoxMap* cmbEN_ADCCLKH_CLKGN;
wxCheckBox* chkSPDUP_VCO_CGEN;
wxStaticText* lblDivider;
wxCheckBox* chkPD_VCO_COMP_CGEN;
wxStaticText* StaticText16;
wxButton* btnReadCMP;
wxStaticText* lblINT_SDM;
wxButton* btnChangeRefClk;
wxCheckBox* chkSX_DITHER_EN_CGEN;
//*)

protected:
//(*Identifiers(pnlCLKGEN)
static const long ID_SPDUP_VCO_CGEN;
static const long ID_RESET_N_CGEN;
static const long ID_EN_COARSE_CKLGEN;
static const long ID_EN_INTONLY_SDM_CGEN;
static const long ID_EN_SDM_CLK_CGEN;
static const long ID_EN_SDM_TSTO_CGEN;
static const long ID_REV_SDMCLK_CGEN;
static const long ID_SX_DITHER_EN_CGEN;
static const long ID_STATICTEXT1;
static const long ID_EN_ADCCLKH_CLKGN;
static const long ID_STATICTEXT4;
static const long ID_TST_CGEN;
static const long ID_REV_CLKDAC_CGEN;
static const long ID_REV_CLKADC_CGEN;
static const long ID_REVPH_PFD_CGEN;
static const long ID_COARSE_START_CGEN;
static const long ID_STATICTEXT5;
static const long ID_COARSE_STEPDONE_CGEN;
static const long ID_STATICTEXT6;
static const long ID_COARSEPLL_COMPO_CGEN;
static const long ID_BUTTON1;
static const long ID_SEL_SDMCLK_CGEN;
static const long ID_PD_CP_CGEN;
static const long ID_PD_FDIV_FB_CGEN;
static const long ID_PD_FDIV_O_CGEN;
static const long ID_PD_SDM_CGEN;
static const long ID_PD_VCO_CGEN;
static const long ID_PD_VCO_COMP_CGEN;
static const long ID_EN_G_CGEN;
static const long ID_STATICTEXT20;
static const long ID_CSW_VCO_CGEN;
static const long ID_STATICTEXT9;
static const long ID_ICT_VCO_CGEN;
static const long ID_STATICTEXT11;
static const long ID_VCO_CMPHO_CGEN;
static const long ID_STATICTEXT12;
static const long ID_VCO_CMPLO_CGEN;
static const long ID_BUTTON2;
static const long ID_BUTTON5;
static const long ID_STATICTEXT13;
static const long ID_CP2_CGEN;
static const long ID_STATICTEXT14;
static const long ID_CP3_CGEN;
static const long ID_STATICTEXT15;
static const long ID_CZ_CGEN;
static const long ID_STATICTEXT16;
static const long ID_IOFFSET_CP_CGEN;
static const long ID_STATICTEXT17;
static const long ID_IPULSE_CP_CGEN;
static const long ID_STATICTEXT10;
static const long ID_STATICTEXT18;
static const long ID_STATICTEXT3;
static const long ID_TEXTCTRL1;
static const long ID_CLKH_OV_CLKL_CGEN;
static const long ID_TEXTCTRL2;
static const long ID_BUTTON3;
static const long ID_BUTTON4;
static const long ID_STATICTEXT7;
static const long ID_STATICTEXT8;
static const long ID_STATICTEXT21;
static const long ID_STATICTEXT22;
static const long ID_STATICTEXT2;
static const long ID_STATICTEXT19;
static const long ID_STATICTEXT25;
static const long ID_STATICTEXT26;
static const long ID_STATICTEXT27;
static const long ID_STATICTEXT28;
static const long ID_BUTTON6;
static const long ID_STATICTEXT23;
static const long ID_STATICTEXT24;
//*)

private:
//(*Handlers(pnlCLKGEN)
    void ParameterChangeHandler(wxCommandEvent& event);
void OnbtnUpdateValuesClick(wxCommandEvent& event);
void OnbtnReadCMPClick(wxCommandEvent& event);
void OnbtnTuneClick(wxCommandEvent& event);
void OnbtnCalculateClick(wxCommandEvent& event);
void OnbtnShowVCOClick(wxCommandEvent& event);
void OnbtnChangeRefClkClick(wxCommandEvent& event);
void OnbtnTuneCoarseClick(wxCommandEvent& event);
//*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void AssignEnumsToIds();
    DECLARE_EVENT_TABLE()
};
#endif
