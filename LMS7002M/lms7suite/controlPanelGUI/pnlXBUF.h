/**
@file 	pnlXBUF.h
@author Lime Microsystems
*/

#ifndef pnlXBUF_H
#define pnlXBUF_H
//(*Headers(pnlXBUF)
#include <wx/panel.h>
class wxCheckBox;
class wxFlexGridSizer;
class wxStaticBoxSizer;
//*)
#include <map>
#include "RegistersMap.h"
#include "GUIPanel.h"
class LMS7002_MainControl;
class ComboBoxMap;
class pnlXBUF : public wxPanel, GUIPanel
{
public:
    pnlXBUF(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
    void Initialize(LMS7002_MainControl *pControl);
    void UpdateGUI();
    virtual ~pnlXBUF();

//(*Declarations(pnlXBUF)
wxCheckBox* chkPD_XBUF_RX;
wxCheckBox* chkSLFB_XBUF_RX;
wxCheckBox* chkBYP_XBUF_TX;
wxCheckBox* chkEN_TBUFIN_XBUF_RX;
wxCheckBox* chkPD_XBUF_TX;
wxCheckBox* chkSLFB_XBUF_TX;
wxCheckBox* chkEN_OUT2_XBUF_TX;
wxCheckBox* chkEN_G_XBUF;
wxCheckBox* chkBYP_XBUF_RX;
//*)

protected:
//(*Identifiers(pnlXBUF)
static const long ID_SLFB_XBUF_RX;
static const long ID_SLFB_XBUF_TX;
static const long ID_BYP_XBUF_RX;
static const long ID_BYP_XBUF_TX;
static const long ID_EN_OUT2_XBUF_TX;
static const long ID_EN_TBUFIN_XBUF_RX;
static const long ID_PD_XBUF_RX;
static const long ID_PD_XBUF_TX;
static const long ID_EN_G_XBUF;
//*)

private:
//(*Handlers(pnlXBUF)
    void ParameterChangeHandler(wxCommandEvent& event);
//*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void AssignEnumsToIds();
    DECLARE_EVENT_TABLE()
};
#endif
