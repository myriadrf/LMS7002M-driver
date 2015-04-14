/**
@file 	pnlTBB.h
@author	Lime Microsystems
*/

#ifndef pnlTBB_H
#define pnlTBB_H
//(*Headers(pnlTBB)
#include <wx/panel.h>
class wxStaticBoxSizer;
class wxComboBox;
class wxFlexGridSizer;
class wxStaticText;
class wxCheckBox;
//*)
#include <map>
#include "RegistersMap.h"
#include "GUIPanel.h"
class LMS7002_MainControl;
class ComboBoxMap;
class pnlTBB : public wxPanel, GUIPanel
{
public:
    pnlTBB(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
    void Initialize(LMS7002_MainControl *pControl);
    void UpdateGUI();
    virtual ~pnlTBB();

//(*Declarations(pnlTBB)
ComboBoxMap* cmbICT_IAMP_GG_FRP_TBB;
ComboBoxMap* cmbICT_LPFS5_F_TBB;
ComboBoxMap* cmbICT_LPF_H_PT_TBB;
ComboBoxMap* cmbICT_IAMP_FRP_TBB;
wxStaticText* StaticText13;
wxStaticText* StaticText14;
wxCheckBox* chkPD_LPFH_TBB;
ComboBoxMap* cmbRCAL_LPFS5_TBB;
wxCheckBox* chkEN_DIR_TBB;
wxStaticText* StaticText1;
wxStaticText* StaticText10;
wxStaticText* StaticText3;
ComboBoxMap* cmbICT_LPFLAD_PT_TBB;
wxCheckBox* chkEN_G_TBB;
ComboBoxMap* cmbLOOPB_TBB;
ComboBoxMap* cmbICT_LPFS5_PT_TBB;
ComboBoxMap* cmbCCAL_LPFLAD_TBB;
wxCheckBox* chkPD_LPFLAD_TBB;
ComboBoxMap* cmbICT_LPFLAD_F_TBB;
wxStaticText* StaticText8;
wxStaticText* StaticText12;
wxStaticText* StaticText0;
ComboBoxMap* cmbRCAL_LPFLAD_TBB;
ComboBoxMap* cmbICT_LPFH_F_TBB;
ComboBoxMap* cmbRCAL_LPFH_TBB;
wxStaticText* StaticText7;
ComboBoxMap* cmbTSTIN_TBB;
wxStaticText* StaticText4;
wxStaticText* StaticText5;
wxStaticText* StaticText2;
wxStaticText* StaticText6;
wxCheckBox* chkBYPLADDER_TBB;
wxCheckBox* chkPD_LPFIAMP_TBB;
wxStaticText* StaticText9;
wxCheckBox* chkPD_LPFS5_TBB;
ComboBoxMap* cmbCG_IAMP_TBB;
wxStaticText* StaticText11;
//*)

protected:
//(*Identifiers(pnlTBB)
static const long ID_STATICTEXT1;
static const long ID_LOOPB_TBB;
static const long ID_STATICTEXT2;
static const long ID_CG_IAMP_TBB;
static const long ID_STATICTEXT3;
static const long ID_ICT_IAMP_FRP_TBB;
static const long ID_STATICTEXT4;
static const long ID_ICT_IAMP_GG_FRP_TBB;
static const long ID_STATICTEXT5;
static const long ID_TSTIN_TBB;
static const long ID_BYPLADDER_TBB;
static const long ID_PD_LPFH_TBB;
static const long ID_PD_LPFIAMP_TBB;
static const long ID_PD_LPFLAD_TBB;
static const long ID_PD_LPFS5_TBB;
static const long ID_EN_G_TBB;
static const long ID_EN_DIR_TBB;
static const long ID_STATICTEXT6;
static const long ID_ICT_LPFS5_F_TBB;
static const long ID_STATICTEXT7;
static const long ID_ICT_LPFS5_PT_TBB;
static const long ID_STATICTEXT8;
static const long ID_ICT_LPF_H_PT_TBB;
static const long ID_STATICTEXT9;
static const long ID_ICT_LPFH_F_TBB;
static const long ID_STATICTEXT10;
static const long ID_ICT_LPFLAD_F_TBB;
static const long ID_STATICTEXT11;
static const long ID_ICT_LPFLAD_PT_TBB;
static const long ID_STATICTEXT12;
static const long ID_RCAL_LPFH_TBB;
static const long ID_STATICTEXT13;
static const long ID_RCAL_LPFLAD_TBB;
static const long ID_STATICTEXT14;
static const long ID_CCAL_LPFLAD_TBB;
static const long ID_STATICTEXT15;
static const long ID_RCAL_LPFS5_TBB;
//*)

private:
//(*Handlers(pnlTBB)
    void ParameterChangeHandler(wxCommandEvent& event);
void OnbtnCalibrateLowBandClick(wxCommandEvent& event);
void OnbtnCalibrateHighBandClick(wxCommandEvent& event);
//*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void AssignEnumsToIds();
    DECLARE_EVENT_TABLE()
};
#endif
