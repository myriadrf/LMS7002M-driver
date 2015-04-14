/**
@file 	pnlAFE.h
@author	Lime Microsystems
*/

#ifndef pnlAFE_H
#define pnlAFE_H
//(*Headers(pnlAFE)
#include <wx/panel.h>
class wxCheckBox;
class wxComboBox;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxStaticBoxSizer;
//*)
#include <map>
#include "RegistersMap.h"
#include "GUIPanel.h"
class LMS7002_MainControl;
class ComboBoxMap;
class pnlAFE : public wxPanel, GUIPanel
{
public:
    pnlAFE(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
    void Initialize(LMS7002_MainControl *pControl);
    void UpdateGUI();
    virtual ~pnlAFE();

//(*Declarations(pnlAFE)
wxCheckBox* chkPD_AFE;
wxStaticText* StaticText2;
wxCheckBox* chkPD_RX_AFE1;
wxCheckBox* chkPD_RX_AFE2;
ComboBoxMap* cmbISEL_DAC_AFE;
wxStaticText* StaticText0;
wxStaticText* StaticText1;
wxCheckBox* chkPD_TX_AFE1;
wxCheckBox* chkPD_TX_AFE2;
ComboBoxMap* cmbMUX_AFE_1;
wxCheckBox* chkEN_G_AFE;
ComboBoxMap* cmbMUX_AFE_2;
wxRadioBox* rgrMODE_INTERLEAVE_AFE;
//*)

protected:
//(*Identifiers(pnlAFE)
static const long ID_STATICTEXT1;
static const long ID_ISEL_DAC_AFE;
static const long ID_STATICTEXT2;
static const long ID_MUX_AFE_1;
static const long ID_STATICTEXT3;
static const long ID_MUX_AFE_2;
static const long ID_MODE_INTERLEAVE_AFE;
static const long ID_PD_AFE;
static const long ID_PD_RX_AFE1;
static const long ID_PD_RX_AFE2;
static const long ID_PD_TX_AFE1;
static const long ID_PD_TX_AFE2;
static const long ID_EN_G_AFE;
//*)

private:
//(*Handlers(pnlAFE)
    void ParameterChangeHandler(wxCommandEvent& event);
//*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void AssignEnumsToIds();

    DECLARE_EVENT_TABLE()
};
#endif
