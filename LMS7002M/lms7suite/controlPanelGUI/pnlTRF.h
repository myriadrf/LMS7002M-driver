/**
@file	pnlTRF.cpp
@author	Lime Microsystems
*/

#ifndef pnlTRF_H
#define pnlTRF_H
//(*Headers(pnlTRF)
#include <wx/panel.h>
class wxStaticBoxSizer;
class wxComboBox;
class wxFlexGridSizer;
class wxStaticText;
class wxRadioBox;
class wxCheckBox;
//*)
#include <map>
#include "RegistersMap.h"
#include "GUIPanel.h"
class LMS7002_MainControl;
class ComboBoxMap;
class pnlTRF : public wxPanel, GUIPanel
{
public:
    pnlTRF(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
    void Initialize(LMS7002_MainControl *pControl);
    void UpdateGUI();
    virtual ~pnlTRF();

//(*Declarations(pnlTRF)
wxCheckBox* chkPD_TXPAD_TRF;
ComboBoxMap* cmbICT_MAIN_TXPAD_TRF;
wxStaticText* StaticText13;
wxStaticText* StaticText14;
wxStaticText* StaticText15;
ComboBoxMap* cmbEN_AMPHF_PDET_TRF;
ComboBoxMap* cmbCDC_I_TRF;
wxRadioBox* rgrGCAS_GNDREF_TXPAD_TRF;
ComboBoxMap* cmbLOSS_LIN_TXPAD_TRF;
ComboBoxMap* cmbVGCAS_TXPAD_TRF;
ComboBoxMap* cmbCDC_Q_TRF;
wxCheckBox* chkPD_PDET_TRF;
wxComboBox* cmbTXFEoutput;
wxCheckBox* chkEN_DIR_TRF;
wxStaticText* StaticText1;
wxStaticText* StaticText10;
wxCheckBox* chkEN_LOOPB_TXPAD_TRF;
ComboBoxMap* cmbF_TXPAD_TRF;
wxStaticText* StaticText3;
ComboBoxMap* cmbLOBIASN_TXM_TRF;
ComboBoxMap* cmbICT_LIN_TXPAD_TRF;
wxStaticText* StaticText8;
wxStaticText* StaticText12;
wxStaticText* StaticText0;
ComboBoxMap* cmbLOSS_MAIN_TXPAD_TRF;
ComboBoxMap* cmbLOBIASP_TXX_TRF;
wxStaticText* StaticText7;
ComboBoxMap* cmbL_LOOPB_TXPAD_TRF;
wxCheckBox* chkPD_TLOBUF_TRF;
wxStaticText* StaticText4;
wxStaticText* StaticText5;
wxStaticText* StaticText2;
wxCheckBox* chkEN_G_TRF;
wxStaticText* StaticText6;
ComboBoxMap* cmbEN_LOWBWLOMX_TMX_TRF;
ComboBoxMap* cmbLOADR_PDET_TRF;
wxStaticText* StaticText9;
wxStaticText* StaticText11;
ComboBoxMap* cmbEN_NEXTTX_TRF;
//*)

protected:
//(*Identifiers(pnlTRF)
static const long ID_STATICTEXT1;
static const long ID_EN_LOWBWLOMX_TMX_TRF;
static const long ID_STATICTEXT2;
static const long ID_EN_NEXTTX_TRF;
static const long ID_STATICTEXT3;
static const long ID_EN_AMPHF_PDET_TRF;
static const long ID_STATICTEXT4;
static const long ID_F_TXPAD_TRF;
static const long ID_STATICTEXT5;
static const long ID_L_LOOPB_TXPAD_TRF;
static const long ID_STATICTEXT6;
static const long ID_LOSS_LIN_TXPAD_TRF;
static const long ID_STATICTEXT7;
static const long ID_LOSS_MAIN_TXPAD_TRF;
static const long ID_STATICTEXT8;
static const long ID_VGCAS_TXPAD_TRF;
static const long ID_STATICTEXT9;
static const long ID_LOBIASN_TXM_TRF;
static const long ID_STATICTEXT10;
static const long ID_LOBIASP_TXX_TRF;
static const long ID_STATICTEXT16;
static const long ID_TXFEoutput;
static const long ID_EN_LOOPB_TXPAD_TRF;
static const long ID_STATICTEXT11;
static const long ID_LOADR_PDET_TRF;
static const long ID_STATICTEXT12;
static const long ID_ICT_LIN_TXPAD_TRF;
static const long ID_STATICTEXT13;
static const long ID_ICT_MAIN_TXPAD_TRF;
static const long ID_PD_PDET_TRF;
static const long ID_PD_TLOBUF_TRF;
static const long ID_PD_TXPAD_TRF;
static const long ID_EN_G_TRF;
static const long ID_EN_DIR_TRF;
static const long ID_GCAS_GNDREF_TXPAD_TRF;
static const long ID_STATICTEXT14;
static const long ID_CDC_I_TRF;
static const long ID_STATICTEXT15;
static const long ID_CDC_Q_TRF;
//*)

private:
//(*Handlers(pnlTRF)
    void ParameterChangeHandler(wxCommandEvent& event);
void OncmbTXFEoutputSelected(wxCommandEvent& event);
//*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void AssignEnumsToIds();
    DECLARE_EVENT_TABLE()
};
#endif
