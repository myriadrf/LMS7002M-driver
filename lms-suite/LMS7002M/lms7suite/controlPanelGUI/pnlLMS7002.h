/**
@file 	pnlLMS7002.h
@author Lime Microsystems
*/

#ifndef PNLLMS7002_H
#define PNLLMS7002_H

#include <wx/notebook.h>
#include "SignalHandler.h"
#include "dlgRegisterMap.h"
#include "dlgMessageLog.h"
//(*Headers(pnlLMS7002)
#include <wx/panel.h>
class wxCheckBox;
class wxNotebookEvent;
class wxRichTextCtrl;
class wxNotebook;
class wxRadioButton;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)

class pnlAlgorithms;
class LMS7002_MainControl;
class pnlSi5351;
class pnlADF;
class pnlRFE;
class pnlRBB;
class pnlTRF;
class pnlTBB;
class pnlLDO;
class pnlAFE;
class pnlBIAS;
class pnlXBUF;
class pnlCLKGEN;
class pnlSXT;
class pnlLimeLightPAD;
class pnlTxTSP;
class pnlRxTSP;
class pnlBIST;
class pnlCDS;
class pnlMCU_BD;
class pnlSPI;
class pnlBoard;
class pnlSocketBoard;
class pnlBuffersEVB7v2;
class pnlTesting;
#include "PluginPanel.h"

class pnlLMS7002: public wxPanel, public SignalHandler, public PluginPanel
{
	public:

		pnlLMS7002(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, const wxString name="name");
		virtual ~pnlLMS7002();

		void HandleMessage(const LMS_Message &msg);
        static void MessageHandler(const int signal, const char *msg, const int paraml);

        void SwitchChannel(int channel, bool configBoth);
        void Initialize();
        void UpdateGUI();
        void UpdateStatusBar();

        LMS7002_MainControl* getLMScontrol();

		//(*Declarations(pnlLMS7002)
		wxRadioButton* rbtnEnChannelA;
		pnlTxTSP* tabTxTSP;
		pnlXBUF* tabXBUF;
		wxButton* btnClearMsgLog;
		pnlBIAS* tabBIAS;
		wxButton* btnSaveProject;
		wxButton* btnNewProject;
		pnlTBB* tabTBB;
		pnlCLKGEN* tabCLKGEN;
		wxCheckBox* chkSyncAB;
		wxRadioButton* rbtnEnChannelB;
		wxPanel* tabBoard1;
		pnlTRF* tabTRF;
		pnlCDS* tabCDS;
		pnlBoard* tabBoard;
		wxNotebook* m_modulesNotebook;
		pnlRFE* tabRFE;
		wxButton* btnDownloadAll;
		pnlAFE* tabAFE;
		pnlLimeLightPAD* tabLimeLightPAD;
		pnlAlgorithms* tabAlgorithms;
		wxButton* btnReset;
		pnlRxTSP* tabRxTSP;
		wxFlexGridSizer* sizerBoardSetup;
		pnlLDO* tabLDO;
		pnlBIST* tabBIST;
		wxStaticText* txtActiveChannel;
		pnlSPI* tabSPI;
		wxButton* btnUploadAll;
		wxRichTextCtrl* txtMessageLog;
		pnlMCU_BD* tabMCU_BD;
		wxFlexGridSizer* m_channelNameLayout;
		wxButton* btnOpenProject;
		wxButton* btnShowLog;
		pnlSXT* tabSXT;
		pnlRBB* tabRBB;
		//*)
		pnlBuffersEVB7v2* tabBuffersEVB7v2;
        pnlTesting* tabTesting;
        pnlSocketBoard* tabSocketBoard;

		//(*Identifiers(pnlLMS7002)
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_BUTTON8;
		static const long ID_CHECKBOX1;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_ALGORITHMTAB;
		static const long ID_TABBOARD;
		static const long ID_TABBOARD1;
		static const long ID_RFE;
		static const long ID_RBB;
		static const long ID_TRF;
		static const long ID_TBB;
		static const long ID_AFE;
		static const long ID_BIAS;
		static const long ID_LDO;
		static const long ID_XBUF;
		static const long ID_CLKGEN;
		static const long ID_SXRSXT;
		static const long ID_LIMELIGHTPAD;
		static const long ID_TXTSP;
		static const long ID_RXTSP;
		static const long ID_CDS;
		static const long ID_MCUBD;
		static const long ID_BIST;
		static const long ID_SPITAB;
		static const long ID_NOTEBOOK1;
		static const long ID_CONTROL_PANEL_MSG_LOG;
		static const long ID_BUTTON4;
		static const long ID_BUTTON7;
		//*)
        static const long ID_TABBUFFERSEVB7V2;
        static const long ID_TABTESTING;
        static const long ID_TABSOCKETBOARD;
		//(*Handlers(pnlLMS7002)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnbtnClearMsgLogClick(wxCommandEvent& event);
        void OnbtnFindDevicesClick(wxCommandEvent& event);
        void OnmenuConnectionSettingsSelected(wxCommandEvent& event);
        void OnbtnNewProjectClick(wxCommandEvent& event);
        void OnbtnUpdateGUIClick(wxCommandEvent& event);
        void OnbtnOpenProjectClick(wxCommandEvent& event);
        void OnbtnSaveProjectClick(wxCommandEvent& event);
        void OnbtnUploadAllClick(wxCommandEvent& event);
        void OnConfiguringChannelsChange(wxCommandEvent& event);
        void Onmnu_SaveRegistersToFileSelected(wxCommandEvent& event);
        void OnbtnDownloadAllClick(wxCommandEvent& event);
        void OnmnuResetChipSelected(wxCommandEvent& event);
        void OnbtnShowLogClick(wxCommandEvent& event);
        void OnmnuRegistersTestSelected(wxCommandEvent& event);
        void OnbtnResetClick(wxCommandEvent& event);
        void OnmnuReadToHexSelected(wxCommandEvent& event);
        void OnmnuRegistersMapSelected(wxCommandEvent& event);
        void Onm_modulesNotebookPageChanged(wxNotebookEvent& event);
        void OnmnuSaveRegistersRVHEXSelected(wxCommandEvent& event);
        void Onmnu_VerifyWrittenDataSelected(wxCommandEvent& event);
		//*)
		void AddTab(wxNotebookPage* tab, wxString title);
        bool RemoveTab(const long windowID);

	protected:
        dlgMessageLog* mDlgLog;
        bool m_overrideChannel;
        int m_selectedChannel;
        int m_lastUsedChannel;
        int m_selectedTab;
        dlgRegisterMap *m_regMapDlg;
        LMS7002_MainControl *lmsControl;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
