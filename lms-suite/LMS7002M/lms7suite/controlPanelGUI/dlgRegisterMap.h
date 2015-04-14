/**
@file 	dlgRegisterMap.h
@author	Lime Microsystems
*/

#ifndef DLGREGISTERMAP_H
#define DLGREGISTERMAP_H

//(*Headers(dlgRegisterMap)
#include <wx/dialog.h>
class wxGrid;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxGridEvent;
//*)

#include "SignalHandler.h"

class LMS7002_MainControl;

class dlgRegisterMap: public wxDialog, public SignalHandler
{
	public:

		dlgRegisterMap(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgRegisterMap();
        void Initialize(LMS7002_MainControl *mainControl);
		void HandleMessage(const LMS_Message &msg);
        void UpdateTables();
		//(*Declarations(dlgRegisterMap)
		wxGrid* gridCh1;
		wxStaticText* StaticText2;
		wxButton* btnClose;
		wxGrid* gridCh0;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxButton* btnForceRefresh;
		wxStaticText* txtAction;
		//*)

	protected:

		//(*Identifiers(dlgRegisterMap)
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT1;
		static const long ID_GRID1;
		static const long ID_GRID2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_BUTTON2;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(dlgRegisterMap)
		void OnbtnCloseClick(wxCommandEvent& event);
		void OnbtnForceRefreshClick(wxCommandEvent& event);
		//*)

	protected:
        LMS7002_MainControl *lmsControl;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
