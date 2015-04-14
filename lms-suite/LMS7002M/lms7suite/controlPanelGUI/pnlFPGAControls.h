/**
@file pnlFPGAControls.h
@author Lime Microsystems
*/
#ifndef PNLFPGACONTROLS_H
#define PNLFPGACONTROLS_H

//(*Headers(pnlFPGAControls)
#include <wx/panel.h>
class wxFlexGridSizer;
//*)

#include "PluginPanel.h"
class ConnectionManager;
class pnlWFMLoader;

class pnlFPGAControls: public wxPanel, public PluginPanel
{
	public:

		pnlFPGAControls(ConnectionManager* pSerPort, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~pnlFPGAControls();

		//(*Declarations(pnlFPGAControls)
		wxFlexGridSizer* mPanelContainer;
		//*)

		//(*Identifiers(pnlFPGAControls)
		//*)

		//(*Handlers(pnlFPGAControls)
		//*)

	protected:
	    pnlWFMLoader* mWFM;
        ConnectionManager* m_serPort;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
