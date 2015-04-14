/**
@file	dlgAbout.cpp
@author	Lime Microsystems
*/

#include "dlgAbout.h"
#include "ResourceImagesLoader.h"
#include "../version.h"
//(*InternalHeaders(dlgAbout)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/bitmap.h>
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/hyperlink.h>
#include <wx/statbmp.h>
#include <wx/button.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgAbout)
const long dlgAbout::ID_STATICBITMAP1 = wxNewId();
const long dlgAbout::ID_STATICTEXT1 = wxNewId();
const long dlgAbout::ID_STATICTEXT2 = wxNewId();
const long dlgAbout::ID_STATICTEXT3 = wxNewId();
const long dlgAbout::ID_STATICTEXT4 = wxNewId();
const long dlgAbout::ID_STATICTEXT5 = wxNewId();
const long dlgAbout::ID_HYPERLINKCTRL1 = wxNewId();
const long dlgAbout::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgAbout,wxDialog)
	//(*EventTable(dlgAbout)
	//*)
END_EVENT_TABLE()

dlgAbout::dlgAbout(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void dlgAbout::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    #ifndef __UNIX__
    wxBitmap *image = CreateBitmapFromPngResource("splashImage");
    #else
#warning image loading from resources not implemented for Linux
    wxBitmap *image = new wxBitmap();
    #endif
	//(*Initialize(dlgAbout)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _T("About"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticBitmap1 = new wxStaticBitmap(this, ID_STATICBITMAP1, *image, wxDefaultPosition, wxSize(195,106), wxSIMPLE_BORDER, _T("ID_STATICBITMAP1"));
	FlexGridSizer2->Add(StaticBitmap1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer3->AddGrowableRow(0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("LMS7002 Software "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	wxFont StaticText1Font(18,wxDEFAULT,wxFONTSTYLE_NORMAL,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer3->Add(StaticText1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtVersion = new wxStaticText(this, ID_STATICTEXT2, _T("v. 1.0.0.0\nBuild date: 2013-10-01"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer3->Add(txtVersion, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtDescription = new wxStaticText(this, ID_STATICTEXT3, _T("Software Description"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(txtDescription, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 50);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _T("Lime Microsystems\nSurrey Tech Centre\nOccam Road\nThe Surrey Research Park\nGuildford Surrey\nGU2 7YG\nUNITED KINGDOM"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _T("Phone: +44 (0) 1483 685 063"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer5->Add(StaticText4, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	HyperlinkCtrl1 = new wxHyperlinkCtrl(this, ID_HYPERLINKCTRL1, _T("http://www.limemicro.com"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_CENTRE|wxNO_BORDER, _T("ID_HYPERLINKCTRL1"));
	FlexGridSizer5->Add(HyperlinkCtrl1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer4->Add(FlexGridSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnClose = new wxButton(this, ID_BUTTON1, _T("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(btnClose, 1, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgAbout::OnbtnCloseClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&dlgAbout::OnInit);
	//*)
}

dlgAbout::~dlgAbout()
{
	//(*Destroy(dlgAbout)
	//*)
}


void dlgAbout::OnInit(wxInitDialogEvent& event)
{
    wxString msg;
	msg << "Version: " << wxString::Format("%i.%i.%i.%i %s\n", AutoVersion::year%100, AutoVersion::month, AutoVersion::day, AutoVersion::buildsCounter, AutoVersion::branchName);
    msg << "Build date: " << wxString::Format("%04i-%02i-%02i", AutoVersion::year, AutoVersion::month, AutoVersion::day);
    txtVersion->SetLabel(msg);
    txtDescription->SetLabel("");
}

void dlgAbout::OnbtnCloseClick(wxCommandEvent& event)
{
    EndModal(wxID_CLOSE);
}
