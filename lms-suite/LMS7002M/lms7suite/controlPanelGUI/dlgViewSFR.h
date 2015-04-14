/**
@file 	dlgViewSFR.h
@author Lime Microsystems
*/

#ifndef DLGVIEWSFR_H
#define DLGVIEWSFR_H

//(*Headers(dlgViewSFR)
#include <wx/dialog.h>
class wxGrid;
class wxBoxSizer;
class wxGridEvent;
//*)

#include "pnlMCU_BD.h"
#include <wx/arrstr.h>

class dlgViewSFR: public wxDialog
{
	public:

		dlgViewSFR(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgViewSFR();

		//(*Declarations(dlgViewSFR)
		wxGrid* Grid1;
		//*)

	protected:

		//(*Identifiers(dlgViewSFR)
		static const long ID_GRID1;
		//*)
		pnlMCU_BD * pPnlMCU_BD;
		wxArrayString strArray;
		void StrArrayIni();
		void InitDialog();
		void InitGridData();

	private:


		//(*Handlers(dlgViewSFR)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
