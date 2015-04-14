/**
@file 	pnlRBB.h
@author Lime Microsystems
*/

#ifndef pnlRBB_H
#define pnlRBB_H
//(*Headers(pnlRBB)
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
class pnlRBB : public wxPanel, GUIPanel
{
public:
    pnlRBB(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
    virtual void Initialize(LMS7002_MainControl *pControl);
    virtual void UpdateGUI();
    virtual ~pnlRBB();

//(*Declarations(pnlRBB)
wxComboBox* cmbBBLoopback;
wxStaticText* StaticText13;
wxCheckBox* chkPD_LPFH_RBB;
ComboBoxMap* cmbICT_PGA_IN_RBB;
ComboBoxMap* cmbG_PGA_RBB;
wxStaticText* StaticText1;
wxStaticText* StaticText10;
wxStaticText* StaticText3;
wxRadioBox* rgrOSW_PGA_RBB;
ComboBoxMap* cmbICT_LPF_OUT_RBB;
wxCheckBox* chkPD_PGA_RBB;
wxStaticText* StaticText8;
wxStaticText* StaticText12;
ComboBoxMap* cmbC_CTL_LPFL_RBB;
wxStaticText* StaticText0;
ComboBoxMap* cmbRCC_CTL_LPFH_RBB;
wxStaticText* StaticText7;
ComboBoxMap* cmbINPUT_CTL_PGA_RBB;
ComboBoxMap* cmbRCC_CTL_PGA_RBB;
wxCheckBox* chkEN_DIR_RBB;
ComboBoxMap* cmbICT_LPF_IN_RBB;
wxStaticText* StaticText4;
ComboBoxMap* cmbRCC_CTL_LPFL_RBB;
wxCheckBox* chkEN_G_RBB;
wxStaticText* StaticText5;
wxStaticText* StaticText2;
wxCheckBox* chkPD_LPFL_RBB;
ComboBoxMap* cmbC_CTL_LPFH_RBB;
wxStaticText* StaticText6;
ComboBoxMap* cmbR_CTL_LPF_RBB;
ComboBoxMap* cmbICT_PGA_OUT_RBB;
wxStaticText* StaticText9;
ComboBoxMap* cmbC_CTL_PGA_RBB;
wxStaticText* StaticText11;
//*)

protected:
//(*Identifiers(pnlRBB)
static const long ID_STATICTEXT14;
static const long ID_BBLoopback;
static const long ID_STATICTEXT1;
static const long ID_INPUT_CTL_PGA_RBB;
static const long ID_STATICTEXT2;
static const long ID_G_PGA_RBB;
static const long ID_STATICTEXT3;
static const long ID_C_CTL_PGA_RBB;
static const long ID_OSW_PGA_RBB;
static const long ID_STATICTEXT4;
static const long ID_R_CTL_LPF_RBB;
static const long ID_STATICTEXT5;
static const long ID_C_CTL_LPFH_RBB;
static const long ID_STATICTEXT6;
static const long ID_C_CTL_LPFL_RBB;
static const long ID_PD_LPFH_RBB;
static const long ID_PD_LPFL_RBB;
static const long ID_PD_PGA_RBB;
static const long ID_EN_G_RBB;
static const long ID_EN_DIR_RBB;
static const long ID_STATICTEXT7;
static const long ID_RCC_CTL_LPFH_RBB;
static const long ID_STATICTEXT8;
static const long ID_RCC_CTL_LPFL_RBB;
static const long ID_STATICTEXT9;
static const long ID_ICT_LPF_IN_RBB;
static const long ID_STATICTEXT10;
static const long ID_ICT_LPF_OUT_RBB;
static const long ID_STATICTEXT11;
static const long ID_ICT_PGA_OUT_RBB;
static const long ID_STATICTEXT12;
static const long ID_ICT_PGA_IN_RBB;
static const long ID_STATICTEXT13;
static const long ID_RCC_CTL_PGA_RBB;
//*)

private:
//(*Handlers(pnlRBB)
    void ParameterChangeHandler(wxCommandEvent& event);
void OnbtnCalibrateLowBandClick(wxCommandEvent& event);
void OnbtnCalibrateHighBandClick(wxCommandEvent& event);
void OncmbBBLoopbackSelected(wxCommandEvent& event);
//*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void AssignEnumsToIds();
    DECLARE_EVENT_TABLE()
};
#endif
