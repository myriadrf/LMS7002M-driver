/**
@file	dlgConnectionManager.cpp
@author	Lime Microsystems
@brief	Dialog for connecting to devices
*/

#include "dlgConnectionManager.h"
#include "ConnectionManager.h"
#include "iniParser.h"

//(*InternalHeaders(dlgConnectionManager)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/listbox.h>
#include <wx/statline.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgConnectionManager)
const long dlgConnectionManager::ID_STATICTEXT1 = wxNewId();
const long dlgConnectionManager::ID_STATICLINE1 = wxNewId();
const long dlgConnectionManager::ID_STATICTEXT2 = wxNewId();
const long dlgConnectionManager::ID_LISTBOX1 = wxNewId();
const long dlgConnectionManager::ID_STATICLINE2 = wxNewId();
const long dlgConnectionManager::ID_LISTBOX2 = wxNewId();
const long dlgConnectionManager::ID_CHECKBOX1 = wxNewId();
const long dlgConnectionManager::ID_BUTTON1 = wxNewId();
const long dlgConnectionManager::ID_BUTTON2 = wxNewId();
const long dlgConnectionManager::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgConnectionManager,wxDialog)
    //(*EventTable(dlgConnectionManager)
    //*)
END_EVENT_TABLE()

dlgConnectionManager::dlgConnectionManager(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_controlPort = NULL;
    m_dataPort = NULL;
    BuildContent(parent,id,pos,size);
}

void dlgConnectionManager::SetConnectionManager(ConnectionManager *pControlPort, ConnectionManager *pDataPort)
{
    m_controlPort = pControlPort;
    m_dataPort = pDataPort;
}

void dlgConnectionManager::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(dlgConnectionManager)
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, id, _("Connection Settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(400,300));
    Move(wxDefaultPosition);
    FlexGridSizer1 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableCol(2);
    FlexGridSizer2->AddGrowableRow(1);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("LMS7 control port:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(2,10), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    FlexGridSizer2->Add(StaticLine1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Stream board port:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer2->Add(StaticText2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    listReceivers = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    listReceivers->SetMinSize(wxSize(150,100));
    FlexGridSizer2->Add(listReceivers, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(-1,10), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    FlexGridSizer2->Add(StaticLine2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    listTransmitters = new wxListBox(this, ID_LISTBOX2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX2"));
    listTransmitters->SetMinSize(wxSize(150,100));
    FlexGridSizer2->Add(listTransmitters, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    chkAutoConnect = new wxCheckBox(this, ID_CHECKBOX1, _("Auto connect at startup"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    chkAutoConnect->SetValue(false);
    FlexGridSizer2->Add(chkAutoConnect, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
    btnOK = new wxButton(this, ID_BUTTON1, _("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer3->Add(btnOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer3->Add(btnCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnDisconnect = new wxButton(this, ID_BUTTON3, _("Disconnect"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer3->Add(btnDisconnect, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    SetSizer(FlexGridSizer1);
    Layout();
    Center();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgConnectionManager::OnbtnOKClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgConnectionManager::OnbtnCancelClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgConnectionManager::OnbtnDisconnectClick);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&dlgConnectionManager::OnInit);
    //*)
}

dlgConnectionManager::~dlgConnectionManager()
{
    //(*Destroy(dlgConnectionManager)
    //*)
}


void dlgConnectionManager::OnbtnOKClick(wxCommandEvent& event)
{
    if(!m_controlPort)
        return;


    int selReceiver = listReceivers->GetSelection();
    int selTransmitter = listTransmitters->GetSelection();
    if( selReceiver >= 0 )
        m_controlPort->Open( selReceiver );
    if( selTransmitter >= 0 && m_dataPort)
        m_dataPort->Open( selTransmitter );

    CloseManager(wxID_OK);
}

void dlgConnectionManager::OnbtnCancelClick(wxCommandEvent& event)
{
    CloseManager(wxID_CANCEL);
}

void dlgConnectionManager::OnInit(wxInitDialogEvent& event)
{
    if(!m_controlPort)
        return;
    m_controlPort->RefreshDeviceList();
    vector<string> deviceNames;
    deviceNames = m_controlPort->GetDeviceList();
    for(unsigned int i=0; i<deviceNames.size(); ++i)
        listReceivers->AppendAndEnsureVisible( deviceNames[i] );
    if(m_controlPort->GetOpenedIndex() < deviceNames.size() )
        listReceivers->SetSelection( m_controlPort->GetOpenedIndex());

    if(m_dataPort)
    {
        m_dataPort->RefreshDeviceList();
        deviceNames = m_dataPort->GetDeviceList();
        for(unsigned int i=0; i<deviceNames.size(); ++i)
            listTransmitters->AppendAndEnsureVisible( deviceNames[i] );
        if(m_dataPort->GetOpenedIndex() < deviceNames.size() )
            listTransmitters->SetSelection( m_dataPort->GetOpenedIndex() );
    }

    iniParser ini;
    ini.Open("gui_settings.ini");
    if(ini.SelectSection("connection_settings"))
    {
        bool autoConnect = ini.Get("connect_at_startup", false);
        if(autoConnect)
        {
            chkAutoConnect->SetValue(autoConnect);
        }
    }
}

void dlgConnectionManager::OnbtnDisconnectClick(wxCommandEvent& event)
{
    m_controlPort->Close();
    if(m_dataPort)
        m_dataPort->Close();
    CloseManager(wxID_ABORT);
}

void dlgConnectionManager::CloseManager(int code)
{
    iniParser ini;
    ini.Open("gui_settings.ini");
    if(ini.SelectSection("connection_settings"))
    {
        ini.Set("connect_at_startup", chkAutoConnect->GetValue());
        if( listReceivers->GetSelection() >= 0)
        {
            ini.Set("device", listReceivers->GetString( listReceivers->GetSelection() ).c_str());
        }
        else
            ini.Set("device", "");
    }
    ini.Save();
    EndModal(code);
}
