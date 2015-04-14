/**
@file 	dlgRegisterTest.h
@author Lime Microsystems
*/

#ifndef DLGREGISTERTEST_H
#define DLGREGISTERTEST_H

#include "SignalHandler.h"

//(*Headers(dlgRegisterTest)
#include <wx/dialog.h>
class wxRichTextCtrl;
class wxFlexGridSizer;
class wxButton;
//*)

class LMS7002_MainControl;

class dlgRegisterTest: public wxDialog, public SignalHandler
{
	public:

		dlgRegisterTest(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, LMS7002_MainControl *mainControl = NULL);
		virtual ~dlgRegisterTest();
		void HandleMessage(const LMS_Message &msg);

		//(*Declarations(dlgRegisterTest)
		wxButton* btnStart;
		wxButton* btnClose;
		wxRichTextCtrl* richTextField;
		//*)

	protected:

		//(*Identifiers(dlgRegisterTest)
		static const long ID_BUTTON2;
		static const long ID_RICHTEXTCTRL1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(dlgRegisterTest)
		void OnbtnCloseClick(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnbtnStartClick(wxCommandEvent& event);
		//*)

	protected:
        LMS7002_MainControl *lmsControl;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
		bool m_testStarted;
		DECLARE_EVENT_TABLE()
};

#endif
