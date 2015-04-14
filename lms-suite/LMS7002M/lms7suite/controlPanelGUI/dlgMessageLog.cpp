/**
@file	dlgMessageLog.cpp
@author	Lime Microsystems
@brief	dialog for displaying log messages
*/

#include "dlgMessageLog.h"
#include <sstream>
using namespace std;
//(*InternalHeaders(dlgMessageLog)
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgMessageLog)
const long dlgMessageLog::ID_RICHTEXTCTRL1 = wxNewId();
const long dlgMessageLog::ID_CHECKBOX1 = wxNewId();
const long dlgMessageLog::ID_CHECKBOX2 = wxNewId();
const long dlgMessageLog::ID_CHECKBOX3 = wxNewId();
const long dlgMessageLog::ID_CHECKBOX4 = wxNewId();
const long dlgMessageLog::ID_BUTTON1 = wxNewId();
const long dlgMessageLog::ID_BUTTON2 = wxNewId();
//*)

#include "MessageLog.h"
#include <wx/filedlg.h>

BEGIN_EVENT_TABLE(dlgMessageLog,wxDialog)
	//(*EventTable(dlgMessageLog)
	//*)
END_EVENT_TABLE()

dlgMessageLog::dlgMessageLog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void dlgMessageLog::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgMessageLog)
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _T("Message Log"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	txtTextField = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
	wxRichTextAttr rchtxtAttr_1;
	rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
	txtTextField->SetMinSize(wxSize(400,500));
	FlexGridSizer1->Add(txtTextField, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _T("Log messages"));
	chkINFO = new wxCheckBox(this, ID_CHECKBOX1, _T("INFO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkINFO->SetValue(false);
	StaticBoxSizer1->Add(chkINFO, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkWARNINGS = new wxCheckBox(this, ID_CHECKBOX2, _T("WARNINGS"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkWARNINGS->SetValue(false);
	StaticBoxSizer1->Add(chkWARNINGS, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkERRORS = new wxCheckBox(this, ID_CHECKBOX3, _T("ERRORS"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkERRORS->SetValue(false);
	StaticBoxSizer1->Add(chkERRORS, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkDATA = new wxCheckBox(this, ID_CHECKBOX4, _T("DATA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkDATA->SetValue(false);
	StaticBoxSizer1->Add(chkDATA, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSave = new wxButton(this, ID_BUTTON1, _T("Save to file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(btnSave, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(94,304,1, wxALL|wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	btnClear = new wxButton(this, ID_BUTTON2, _T("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(btnClear, 1, wxALL|wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgMessageLog::OnChangeFilter);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgMessageLog::OnChangeFilter);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgMessageLog::OnChangeFilter);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgMessageLog::OnChangeFilter);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgMessageLog::OnbtnSaveClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgMessageLog::OnbtnClearClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&dlgMessageLog::OnInit);
	//*)
	wxFont font(8, wxFONTFAMILY_TELETYPE, wxNORMAL, wxNORMAL);
	txtTextField->SetFont(font);
}

dlgMessageLog::~dlgMessageLog()
{
	//(*Destroy(dlgMessageLog)
	//*)
}


void dlgMessageLog::OnbtnSaveClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Save log file"), "", "", "Text file (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    MessageLog::getInstance()->saveToFile(dlg.GetPath().ToStdString());
}

void dlgMessageLog::OnbtnClearClick(wxCommandEvent& event)
{
    MessageLog::getInstance()->clear();
    txtTextField->Clear();
}

void dlgMessageLog::OnInit(wxInitDialogEvent& event)
{
    list<string> logMessages;
    logMessages = MessageLog::getInstance()->getLogMessages();
    stringstream ss;
    for(list<string>::iterator iter=logMessages.begin(); iter!=logMessages.end(); ++iter)
    {
        ss << *iter;
    }
    txtTextField->Clear();
    txtTextField->WriteText( ss.str() );
    unsigned int filter = MessageLog::getInstance()->GetLogFilter();
    if(( filter & LOG_INFO) == LOG_INFO)
        chkINFO->SetValue(true);
    if(( filter & LOG_WARNING) == LOG_WARNING)
        chkWARNINGS->SetValue(true);
    if(( filter & LOG_ERROR) == LOG_ERROR)
        chkERRORS->SetValue(true);
    if(( filter & LOG_DATA) == LOG_DATA)
        chkDATA->SetValue(true);
}

void dlgMessageLog::OnChangeFilter(wxCommandEvent& event)
{
    unsigned int filter = 0;
    if(chkINFO->GetValue())
        filter |= LOG_INFO;
    if(chkWARNINGS->GetValue())
        filter |= LOG_WARNING;
    if(chkERRORS->GetValue())
        filter |= LOG_ERROR;
    if(chkDATA->GetValue())
        filter |= LOG_DATA;

    MessageLog::getInstance()->SetLogFilter(filter);
    MessageLog::getInstance()->SetConsoleFilter(filter, false);
}

void dlgMessageLog::Write(const char* text)
{
    txtTextField->WriteText( text );
    txtTextField->ShowPosition(txtTextField->GetLastPosition()-1);
}
