/**
@file 	pnlBIST.h
@author Lime Microsystems
*/

#ifndef pnlBIST_H
#define pnlBIST_H
//(*Headers(pnlBIST)
#include <wx/panel.h>
class wxCheckBox;
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
class pnlBIST : public wxPanel, GUIPanel
{
public:
    pnlBIST(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
    void Initialize(LMS7002_MainControl *pControl);
    void UpdateGUI();
    void UpdateReadOnlyValues();
    virtual ~pnlBIST();

//(*Declarations(pnlBIST)
wxButton* btnUpdateValues;
wxStaticText* StaticText2;
wxStaticText* lblBSIGR;
wxStaticText* StaticText0;
wxStaticText* lblBSIGC;
wxStaticText* StaticText1;
wxStaticText* StaticText3;
wxCheckBox* chkBENR;
wxStaticText* lblBSIGT;
wxCheckBox* chkBENT;
wxCheckBox* chkBENC;
wxCheckBox* chkBSTART;
wxStaticText* lblBSTATE;
//*)

protected:
//(*Identifiers(pnlBIST)
static const long ID_BENC;
static const long ID_BENT;
static const long ID_BENR;
static const long ID_BSTART;
static const long ID_STATICTEXT2;
static const long ID_BSTATE;
static const long ID_STATICTEXT1;
static const long ID_BSIGT;
static const long ID_STATICTEXT3;
static const long ID_BSIGR;
static const long ID_STATICTEXT4;
static const long ID_BSIGC;
static const long ID_BUTTON1;
//*)

private:
//(*Handlers(pnlBIST)
    void ParameterChangeHandler(wxCommandEvent& event);
void OnbtnUpdateValuesClick(wxCommandEvent& event);
//*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void AssignEnumsToIds();
    DECLARE_EVENT_TABLE()
};
#endif
