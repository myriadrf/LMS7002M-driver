/**
@file pnlWFMLoader.h
@author Lime Microsystems
*/
#ifndef PNLWFMLOADER_H
#define PNLWFMLOADER_H

//(*Headers(pnlWFMLoader)
#include <wx/panel.h>
class wxGauge;
class wxStaticText;
class wxBitmapButton;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)

#include "PluginPanel.h"
#include <vector>
#include <map>

class ConnectionManager;

class pnlWFMLoader: public wxPanel, public PluginPanel
{
	public:
		pnlWFMLoader(ConnectionManager* pSerPort, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~pnlWFMLoader();

        int UploadFile(const char* filename);
		//(*Declarations(pnlWFMLoader)
		wxButton* btnPlayWFM;
		wxButton* btnStopWFM;
		wxStaticText* lblProgressPercent;
		wxGauge* progressBar;
		wxBitmapButton* btnOpenWFM;
		wxButton* btnLoadOnetone;
		wxStaticText* txtFilename;
		wxButton* btnLoadCustom;
		wxButton* btnLoadWCDMA;
		//*)

	protected:

		//(*Identifiers(pnlWFMLoader)
		static const long ID_BUTTON6;
		static const long ID_BUTTON7;
		static const long ID_BUTTON8;
		static const long ID_BITMAPBUTTON1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT5;
		static const long ID_GAUGE1;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		//*)

	private:

		//(*Handlers(pnlWFMLoader)
		void OnbtnUploadClick(wxCommandEvent& event);
		void OnbtnOpenFileClick(wxCommandEvent& event);
		void OnbtnMifClick(wxCommandEvent& event);
		void OnbtnHexClick(wxCommandEvent& event);
		void OnbtnPlayWFMClick(wxCommandEvent& event);
		void OnbtnStopWFMClick(wxCommandEvent& event);
		void OnbtnLoadOnetoneClick(wxCommandEvent& event);
		void OnbtnLoadWCDMAClick(wxCommandEvent& event);
		void OnbtnLoadCustomClick(wxCommandEvent& event);
		//*)

	protected:
        ConnectionManager* m_serPort;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
