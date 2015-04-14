/**
@file 	dlgViewIRAM.h
@author Lime Microsystems
*/

#ifndef DLGVIEWIRAM_H
#define DLGVIEWIRAM_H

//(*Headers(dlgViewIRAM)
#include <wx/dialog.h>
class wxGrid;
class wxBoxSizer;
class wxGridEvent;
//*)


#include "pnlMCU_BD.h"
//#include <wx/arrstr.h>

class dlgViewIRAM: public wxDialog
{
	public:

		dlgViewIRAM(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgViewIRAM();

		//(*Declarations(dlgViewIRAM)
		wxGrid* Grid1;
		//*)

		pnlMCU_BD * pPnlMCU_BD;

		void InitDialog();
		void InitGridData();

	protected:

		//(*Identifiers(dlgViewIRAM)
		static const long ID_GRID1;
		//*)

	private:

		//(*Handlers(dlgViewIRAM)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
