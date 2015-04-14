/**
@file 	pnlRFE.h
@author Lime Microsystems
*/

#ifndef pnlRFE_H
#define pnlRFE_H
//(*Headers(pnlRFE)
#include <wx/panel.h>
class wxCheckBox;
class wxComboBox;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)
#include <map>
#include "RegistersMap.h"
#include "GUIPanel.h"
class LMS7002_MainControl;
class ComboBoxMap;
class pnlRFE : public wxPanel, GUIPanel
{
public:
    pnlRFE(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
    void Initialize(LMS7002_MainControl *pControl);
    void UpdateGUI();
    virtual ~pnlRFE();

//(*Declarations(pnlRFE)
wxStaticText* StaticText10;
wxCheckBox* chkEN_DIR_RFE;
wxStaticText* StaticText9;
ComboBoxMap* cmbICT_LNA_RFE;
ComboBoxMap* cmbCGSIN_LNA_RFE;
wxCheckBox* chkPD_RLOOPB_1_RFE;
ComboBoxMap* cmbG_TIA_RFE;
wxCheckBox* chkPD_RLOOPB_2_RFE;
ComboBoxMap* cmbG_RXLOOPB_RFE;
ComboBoxMap* cmbCDC_Q_RFE;
wxStaticText* StaticText13;
wxStaticText* StaticText2;
wxStaticText* StaticText14;
ComboBoxMap* cmbDCOFFQ_RFE;
wxCheckBox* chkEN_INSHSW_LB1_RFE;
wxStaticText* StaticText6;
wxCheckBox* chkPD_TIA_RFE;
wxCheckBox* chkEN_G_RFE;
ComboBoxMap* cmbCAP_RXMXO_RFE;
wxStaticText* StaticText19;
wxStaticText* StaticText8;
wxStaticText* StaticText0;
wxStaticText* StaticText11;
wxStaticText* StaticText18;
wxCheckBox* chkPD_QGEN_RFE;
ComboBoxMap* cmbRCOMP_TIA_RFE;
wxStaticText* StaticText1;
ComboBoxMap* cmbSEL_PATH_RFE;
ComboBoxMap* cmbDCOFFI_RFE;
wxStaticText* StaticText3;
wxCheckBox* chkEN_NEXTRX_RFE;
ComboBoxMap* cmbCCOMP_TIA_RFE;
wxButton* btnDCclbrRSSI;
wxCheckBox* chkPD_RSSI_RFE;
wxCheckBox* chkEN_INSHSW_W_RFE;
wxStaticText* StaticText5;
wxStaticText* StaticText7;
wxCheckBox* chkPD_LNA_RFE;
ComboBoxMap* cmbICT_LODC_RFE;
ComboBoxMap* cmbCFB_TIA_RFE;
ComboBoxMap* cmbG_LNA_RFE;
wxCheckBox* chkEN_DCOFF_RXFE_RFE;
wxStaticText* StaticText15;
ComboBoxMap* cmbICT_LOOPB_RFE;
wxStaticText* StaticText12;
wxCheckBox* chkPD_MXLOBUF_RFE;
ComboBoxMap* cmbICT_TIAOUT_RFE;
wxStaticText* StaticText17;
wxStaticText* StaticText4;
wxCheckBox* chkEN_INSHSW_LB2_RFE;
ComboBoxMap* cmbICT_LNACMO_RFE;
ComboBoxMap* cmbICT_TIAMAIN_RFE;
ComboBoxMap* cmbCDC_I_RFE;
wxCheckBox* chkEN_INSHSW_L_RFE;
wxStaticText* StaticText16;
ComboBoxMap* cmbRFB_TIA_RFE;
//*)

protected:
//(*Identifiers(pnlRFE)
static const long ID_PD_LNA_RFE;
static const long ID_PD_RLOOPB_1_RFE;
static const long ID_PD_RLOOPB_2_RFE;
static const long ID_PD_MXLOBUF_RFE;
static const long ID_PD_QGEN_RFE;
static const long ID_PD_RSSI_RFE;
static const long ID_PD_TIA_RFE;
static const long ID_EN_G_RFE;
static const long ID_EN_DIR_RFE;
static const long ID_STATICTEXT1;
static const long ID_SEL_PATH_RFE;
static const long ID_STATICTEXT2;
static const long ID_CAP_RXMXO_RFE;
static const long ID_STATICTEXT3;
static const long ID_CGSIN_LNA_RFE;
static const long ID_STATICTEXT4;
static const long ID_RCOMP_TIA_RFE;
static const long ID_STATICTEXT5;
static const long ID_RFB_TIA_RFE;
static const long ID_EN_NEXTRX_RFE;
static const long ID_EN_INSHSW_LB1_RFE;
static const long ID_EN_INSHSW_LB2_RFE;
static const long ID_EN_INSHSW_L_RFE;
static const long ID_EN_INSHSW_W_RFE;
static const long ID_STATICTEXT6;
static const long ID_DCOFFI_RFE;
static const long ID_STATICTEXT7;
static const long ID_DCOFFQ_RFE;
static const long ID_STATICTEXT8;
static const long ID_ICT_LODC_RFE;
static const long ID_EN_DCOFF_RXFE_RFE;
static const long ID_BUTTON2;
static const long ID_STATICTEXT9;
static const long ID_ICT_LOOPB_RFE;
static const long ID_STATICTEXT10;
static const long ID_ICT_TIAMAIN_RFE;
static const long ID_STATICTEXT11;
static const long ID_ICT_TIAOUT_RFE;
static const long ID_STATICTEXT12;
static const long ID_ICT_LNACMO_RFE;
static const long ID_STATICTEXT13;
static const long ID_ICT_LNA_RFE;
static const long ID_STATICTEXT14;
static const long ID_CCOMP_TIA_RFE;
static const long ID_STATICTEXT15;
static const long ID_CFB_TIA_RFE;
static const long ID_STATICTEXT16;
static const long ID_G_LNA_RFE;
static const long ID_STATICTEXT17;
static const long ID_G_RXLOOPB_RFE;
static const long ID_STATICTEXT18;
static const long ID_G_TIA_RFE;
static const long ID_STATICTEXT19;
static const long ID_CDC_I_RFE;
static const long ID_STATICTEXT20;
static const long ID_CDC_Q_RFE;
//*)

private:
//(*Handlers(pnlRFE)
    void ParameterChangeHandler(wxCommandEvent& event);
    void OnbtnCalibrateDCClick(wxCommandEvent& event);
void OnbtnDCclbrRSSIClick(wxCommandEvent& event);
//*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void AssignEnumsToIds();
    DECLARE_EVENT_TABLE()
};
#endif
