/**
@file	dlgAbout.h
@author	Lime Microsystems
@brief	Header for dlgAbout.cpp
*/

#ifndef DLGABOUT_H
#define DLGABOUT_H

//(*Headers(dlgAbout)
#include <wx/dialog.h>
class wxHyperlinkCtrl;
class wxStaticBitmap;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
//*)

class dlgAbout: public wxDialog
{
	public:

		dlgAbout(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgAbout();

		//(*Declarations(dlgAbout)
		wxButton* btnClose;
		wxStaticBitmap* StaticBitmap1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxHyperlinkCtrl* HyperlinkCtrl1;
		wxStaticText* txtDescription;
		wxStaticText* txtVersion;
		wxStaticText* StaticText4;
		//*)

	protected:

		//(*Identifiers(dlgAbout)
		static const long ID_STATICBITMAP1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_HYPERLINKCTRL1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(dlgAbout)
		void OnInit(wxInitDialogEvent& event);
		void OnbtnCloseClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
