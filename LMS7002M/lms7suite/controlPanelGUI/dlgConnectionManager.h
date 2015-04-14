/**
@file	dlgConnectionManager.h
@author	Lime Microsystems
*/

#ifndef DLGCONNECTIONMANAGER_H
#define DLGCONNECTIONMANAGER_H

//(*Headers(dlgConnectionManager)
#include <wx/dialog.h>
class wxCheckBox;
class wxStaticLine;
class wxListBox;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
//*)

class ConnectionManager;

class dlgConnectionManager: public wxDialog
{
public:
    dlgConnectionManager(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    void SetConnectionManager(ConnectionManager *pControlPort, ConnectionManager *pDataPort);
    virtual ~dlgConnectionManager();

    void CloseManager(int code);

    //(*Declarations(dlgConnectionManager)
    wxStaticText* StaticText2;
    wxButton* btnCancel;
    wxListBox* listTransmitters;
    wxStaticText* StaticText1;
    wxButton* btnOK;
    wxStaticLine* StaticLine2;
    wxListBox* listReceivers;
    wxStaticLine* StaticLine1;
    wxButton* btnDisconnect;
    wxCheckBox* chkAutoConnect;
    //*)

protected:

    //(*Identifiers(dlgConnectionManager)
    static const long ID_STATICTEXT1;
    static const long ID_STATICLINE1;
    static const long ID_STATICTEXT2;
    static const long ID_LISTBOX1;
    static const long ID_STATICLINE2;
    static const long ID_LISTBOX2;
    static const long ID_CHECKBOX1;
    static const long ID_BUTTON1;
    static const long ID_BUTTON2;
    static const long ID_BUTTON3;
    //*)

private:
    ConnectionManager *m_controlPort;
    ConnectionManager *m_dataPort;
    //(*Handlers(dlgConnectionManager)
    void OnbtnOKClick(wxCommandEvent& event);
    void OnbtnCancelClick(wxCommandEvent& event);
    void OnInit(wxInitDialogEvent& event);
    void OnbtnDisconnectClick(wxCommandEvent& event);
    //*)

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    DECLARE_EVENT_TABLE()
};

#endif
