/**
@file	pnlBIAS.h
@author	Lime Microsystems
*/

#ifndef pnlBIAS_H
#define pnlBIAS_H
//(*Headers(pnlBIAS)
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
class pnlBIAS : public wxPanel, GUIPanel
{
public:
    pnlBIAS(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
    void Initialize(LMS7002_MainControl *pControl);
    void UpdateGUI();
    virtual ~pnlBIAS();

//(*Declarations(pnlBIAS)
ComboBoxMap* cmbMUX_BIAS_OUT;
wxStaticText* StaticText0;
wxStaticText* StaticText1;
wxCheckBox* chkPD_FRP_BIAS;
wxCheckBox* chkPD_BIAS_MASTER;
wxCheckBox* chkPD_PTRP_BIAS;
wxCheckBox* chkPD_F_BIAS;
ComboBoxMap* cmbRP_CALIB_BIAS;
wxCheckBox* chkPD_PT_BIAS;
wxButton* btnCalibrate;
//*)

protected:
//(*Identifiers(pnlBIAS)
static const long ID_PD_FRP_BIAS;
static const long ID_PD_F_BIAS;
static const long ID_PD_PTRP_BIAS;
static const long ID_PD_PT_BIAS;
static const long ID_PD_BIAS_MASTER;
static const long ID_STATICTEXT1;
static const long ID_MUX_BIAS_OUT;
static const long ID_STATICTEXT2;
static const long ID_RP_CALIB_BIAS;
static const long ID_BUTTON1;
//*)

private:
//(*Handlers(pnlBIAS)
    void ParameterChangeHandler(wxCommandEvent& event);
void OnbtnCalibrateClick(wxCommandEvent& event);
//*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void AssignEnumsToIds();
    DECLARE_EVENT_TABLE()
};
#endif
