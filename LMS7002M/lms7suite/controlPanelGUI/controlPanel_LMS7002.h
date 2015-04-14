/**
@file 	controlPanel_LMS7002.h
@author	Lime Microsystems
@brief 	Header for controlPanel_LMS7002.cpp
*/

#ifndef CONTROLPANEL_LMS7002_H
#define CONTROLPANEL_LMS7002_H

#include <wx/notebook.h>
#include "SignalHandler.h"
#include "dlgRegisterMap.h"
#include "dlgMessageLog.h"
#include "PluginPanel.h"
#include "pnlMyriad7.h"
//(*Headers(controlPanel_LMS7002)
#include <wx/frame.h>
class wxPanel;
class wxStatusBar;
class wxMenuBar;
class wxComboBox;
class wxStaticText;
class wxMenu;
class wxFlexGridSizer;
class wxAuiManager;
class wxAuiManagerEvent;
//*)
class LMS7002_MainControl;
class pnlLMS7002;
class ConnectionManager;
class pnlMinimalControls;
class pnlFFTviewer;
class pnlFPGAControls;
class pnlProgramming;
class pnlMyriad7;
class pnlSi5351;

class controlPanel_LMS7002: public wxFrame, public SignalHandler
{
public:
    void HandleMessage(const LMS_Message &msg);
    static void MessageHandler(const int signal, const char *msg, const int paraml);

    controlPanel_LMS7002(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~controlPanel_LMS7002();

    int SetAvailableModules(unsigned long ePluginsConfiguration_flags);

    //(*Declarations(controlPanel_LMS7002)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxPanel* Panel1;
    wxStaticText* StaticText1;
    wxMenu* Menu1;
    wxAuiManager* panelsManager;
    wxMenuItem* MenuItem3;
    wxMenuBar* MenuBar1;
    wxMenu* menuModules;
    wxComboBox* cmbPluginsConfig;
    wxMenu* Menu2;
    wxMenu* Menu4;
    wxStatusBar* m_controlStatusbar;
    //*)

protected:
	LMS7002_MainControl* lmsControl;
    pnlLMS7002* pnl_lms7ctrl;
    pnlFFTviewer* pnlfft;
    pnlFPGAControls* pnlFPGA;
    pnlProgramming* pnlProg;
    pnlMinimalControls* minCtrl;
    pnlMyriad7* myriad7;
    pnlSi5351* si5351;

    ConnectionManager* m_controlPort;
    ConnectionManager* m_dataPort;
    unsigned long m_pluginsConfiguration;
    std::vector<PluginPanel*> plugins;
    void OnPaneClose(wxAuiManagerEvent& event);
    //(*Identifiers(controlPanel_LMS7002)
    static const long ID_STATICTEXT1;
    static const long ID_COMBOBOX1;
    static const long ID_PANEL1;
    static const long ID_CONTROL_STATUSBAR;
    static const long ID_MENUITEM1;
    static const long ID_MENUITEM2;
    static const long ID_MENUITEM3;
    //*)

private:

    //(*Handlers(controlPanel_LMS7002)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnmenuConnectionSettingsSelected(wxCommandEvent& event);
    void OnShowModule(wxCommandEvent& event);
    void OncmbPluginsConfigSelected(wxCommandEvent& event);
    void OnShowFFT(wxCommandEvent& event);
    //*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

    DECLARE_EVENT_TABLE()
};

#endif
