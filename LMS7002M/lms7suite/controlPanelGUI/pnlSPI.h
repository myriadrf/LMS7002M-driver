/**
@file 	pnlSPI.h
@author	Lime Microsystems
*/

#ifndef PNLSPI_H
#define PNLSPI_H

//(*Headers(pnlSPI)
#include <wx/panel.h>
class wxSpinEvent;
class wxCheckBox;
class wxTextCtrl;
class wxRichTextCtrl;
class wxRadioBox;
class wxStaticText;
class wxFlexGridSizer;
class wxSpinCtrl;
class wxButton;
class wxStaticBoxSizer;
//*)

#include <string>

class LMS7002_MainControl;
class ConnectionManager;

class pnlSPI: public wxPanel
{
	public:

		pnlSPI(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
		void Initialize( LMS7002_MainControl *pControl);
		virtual ~pnlSPI();
		void PrintLine(const std::string msg);

		int RunModuleTest(int moduleId, bool customInterval = false);

		//(*Declarations(pnlSPI)
		wxStaticText* StaticText10;
		wxButton* btnBatchRead;
		wxStaticText* StaticText22;
		wxButton* btnTestTBB;
		wxStaticText* StaticText9;
		wxButton* btnTestLimeLight;
		wxStaticText* StaticText20;
		wxCheckBox* chkSaveToFile;
		wxStaticText* lblReadVal;
		wxButton* btnTestBIST;
		wxCheckBox* chkTestWrittenData;
		wxCheckBox* chkTripleCheck;
		wxButton* btnTestAFE;
		wxStaticBoxSizer* groupBoxRegistersTest;
		wxTextCtrl* txtReadAddrBrd;
		wxButton* btnTestRBB;
		wxStaticText* lblWstatusI2C;
		wxRichTextCtrl* txtTestText;
		wxButton* btnTestRxNCO;
		wxStaticText* StaticText13;
		wxTextCtrl* txtEndAddr;
		wxStaticText* StaticText2;
		wxStaticText* StaticText14;
		wxStaticText* StaticText6;
		wxButton* btnTestInterval;
		wxButton* btnWrTester;
		wxTextCtrl* txtReadAddrI2C;
		wxButton* btnWrite;
		wxStaticText* StaticText19;
		wxFlexGridSizer* sizerRegistersTest;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxStaticText* StaticText18;
		wxButton* btnTestRxTSP;
		wxButton* btnTestCDS;
		wxButton* btnReadBrd;
		wxTextCtrl* txtWvalueI2C;
		wxTextCtrl* txtWvalueBrd;
		wxStaticText* StaticText1;
		wxButton* btnWriteI2C;
		wxStaticText* StaticText3;
		wxStaticText* lblRstatus;
		wxRadioBox* rgrChannelSelect;
		wxButton* btnTestSXRSXT;
		wxStaticText* StaticText23;
		wxButton* btnTestBIAS;
		wxTextCtrl* txtWriteAddrI2C;
		wxSpinCtrl* spinBatchCount;
		wxButton* btnTestTxNCO;
		wxTextCtrl* txtStartAddr;
		wxStaticText* StaticText5;
		wxStaticText* lblWstatusBrd;
		wxButton* btnTestCGEN;
		wxStaticText* StaticText7;
		wxButton* btnTestXBUF;
		wxStaticText* lblReadValI2C;
		wxTextCtrl* txtWvalue;
		wxButton* btnTestLDO;
		wxButton* btnTestRFE;
		wxButton* btnPurgeCOM;
		wxStaticText* lblRstatusI2C;
		wxButton* btnWriteBrd;
		wxButton* btnTestTxTSP;
		wxTextCtrl* txtWriteAddrBrd;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		wxStaticText* lblReadValBrd;
		wxStaticText* lblRstatusBrd;
		wxCheckBox* chkSaveToFileBatch;
		wxButton* btnTestTRF;
		wxStaticText* StaticText25;
		wxButton* btnRead;
		wxTextCtrl* txtWriteAddr;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		wxTextCtrl* txtReadAddr;
		wxStaticText* lblWstatus;
		wxTextCtrl* txtHexInput;
		wxButton* btnReadI2C;
		wxStaticText* StaticText16;
		wxCheckBox* chkBatchWR;
		//*)

	protected:

		//(*Identifiers(pnlSPI)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT9;
		static const long ID_TEXTCTRL3;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT3;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_BUTTON21;
		static const long ID_STATICTEXT13;
		static const long ID_SPINCTRL1;
		static const long ID_CHECKBOX3;
		static const long ID_BUTTON22;
		static const long ID_CHECKBOX4;
		static const long ID_BUTTON23;
		static const long ID_CHECKBOX5;
		static const long ID_RADIOBOX1;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT10;
		static const long ID_TEXTCTRL4;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_STATICTEXT11;
		static const long ID_TEXTCTRL5;
		static const long ID_STATICTEXT12;
		static const long ID_TEXTCTRL6;
		static const long ID_BUTTON20;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_BUTTON7;
		static const long ID_BUTTON8;
		static const long ID_BUTTON9;
		static const long ID_BUTTON19;
		static const long ID_BUTTON10;
		static const long ID_BUTTON11;
		static const long ID_BUTTON12;
		static const long ID_BUTTON13;
		static const long ID_BUTTON14;
		static const long ID_BUTTON15;
		static const long ID_BUTTON16;
		static const long ID_BUTTON17;
		static const long ID_BUTTON18;
		static const long ID_RICHTEXTCTRL1;
		static const long ID_STATICTEXT15;
		static const long ID_TEXTCTRL7;
		static const long ID_STATICTEXT16;
		static const long ID_TEXTCTRL8;
		static const long ID_BUTTON24;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_STATICTEXT19;
		static const long ID_TEXTCTRL9;
		static const long ID_BUTTON25;
		static const long ID_STATICTEXT20;
		static const long ID_STATICTEXT21;
		static const long ID_STATICTEXT22;
		static const long ID_STATICTEXT23;
		static const long ID_STATICTEXT24;
		static const long ID_TEXTCTRL10;
		static const long ID_STATICTEXT25;
		static const long ID_TEXTCTRL11;
		static const long ID_BUTTON26;
		static const long ID_STATICTEXT26;
		static const long ID_STATICTEXT27;
		static const long ID_STATICTEXT28;
		static const long ID_TEXTCTRL12;
		static const long ID_BUTTON27;
		static const long ID_STATICTEXT29;
		static const long ID_STATICTEXT30;
		static const long ID_STATICTEXT31;
		static const long ID_STATICTEXT32;
		//*)

	private:

		//(*Handlers(pnlSPI)
		void OnbtnWriteClick(wxCommandEvent& event);
		void OnbtnReadClick(wxCommandEvent& event);
		void OnrgrChannelSelectSelect(wxCommandEvent& event);
		void OnbtnTestLimeLightClick(wxCommandEvent& event);
		void OnbtnTestAFEClick(wxCommandEvent& event);
		void OnbtnTestBIASClick(wxCommandEvent& event);
		void OnbtnTestXBUFClick(wxCommandEvent& event);
		void OnbtnTestCGENClick(wxCommandEvent& event);
		void OnbtnTestLDOClick(wxCommandEvent& event);
		void OnbtnTestBISTClick(wxCommandEvent& event);
		void OnbtnTestTRFClick(wxCommandEvent& event);
		void OnbtnTestTBBClick(wxCommandEvent& event);
		void OnbtnTestRFEClick(wxCommandEvent& event);
		void OnbtnTestRBBClick(wxCommandEvent& event);
		void OnbtnTestSXRSXTClick(wxCommandEvent& event);
		void OnbtnTestTxTSPClick(wxCommandEvent& event);
		void OnbtnTestTxNCOClick(wxCommandEvent& event);
		void OnbtnTestRxTSPClick(wxCommandEvent& event);
		void OnbtnTestRxNCOClick(wxCommandEvent& event);
		void OnbtnTestCDSClick(wxCommandEvent& event);
		void OnbtnTestIntervalClick(wxCommandEvent& event);
		void OnbtnBatchReadClick(wxCommandEvent& event);
		void OnbtnWrTesterClick(wxCommandEvent& event);
		void OnchkTripleCheckClick(wxCommandEvent& event);
		void OnbtnPurgeCOMClick(wxCommandEvent& event);
		void OnchkTestWrittenDataClick(wxCommandEvent& event);
		void OnbtnWriteBrdClick(wxCommandEvent& event);
		void OnbtnReadBrdClick(wxCommandEvent& event);
		void OnbtnWriteI2CClick(wxCommandEvent& event);
		void OnbtnReadI2CClick(wxCommandEvent& event);
		//*)

	protected:
	    LMS7002_MainControl *lmsControl;
        ConnectionManager *m_serPort;
		void BuildContent(wxWindow *parent, wxWindowID id);

		DECLARE_EVENT_TABLE()
};

#endif
