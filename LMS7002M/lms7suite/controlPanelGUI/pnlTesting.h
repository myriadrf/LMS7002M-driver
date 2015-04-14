/**
@file 	pnlTesting.h
@author Lime Microsystems
*/

#ifndef PNLTESTING_H
#define PNLTESTING_H

//(*Headers(pnlTesting)
#include <wx/panel.h>
class wxFlexGridSizer;
class wxButton;
//*)

#include "GUIPanel.h"
class dlgNCOSweepTest;
class dlgVCOSweepTest;

class pnlTesting: public wxPanel, GUIPanel
{
	public:

		pnlTesting(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, long style=0, wxString name=wxEmptyString);
		void Initialize(LMS7002_MainControl *pControl);
		void UpdateGUI();
		virtual ~pnlTesting();

		//(*Declarations(pnlTesting)
		wxButton* btnNCOSweepTx;
		wxButton* btnNCOSweepRx;
		wxButton* btnVCOSweepTx;
		wxButton* btnVCOSweepRx;
		//*)

	protected:
        dlgNCOSweepTest *dlgNCOSweepRx;
        dlgNCOSweepTest *dlgNCOSweepTx;
        dlgVCOSweepTest *dlgVCOSweepRx;
        dlgVCOSweepTest *dlgVCOSweepTx;
		//(*Identifiers(pnlTesting)
		static const long ID_BUTTON1;
		static const long ID_BUTTON3;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		//*)

	private:

		//(*Handlers(pnlTesting)
		void OnbtnNCOSweepRxClick(wxCommandEvent& event);
		void OnbtnNCOSweepTxClick(wxCommandEvent& event);
		void OnbtnVCOSweepRxClick(wxCommandEvent& event);
		void OnbtnVCOSweepTxClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
