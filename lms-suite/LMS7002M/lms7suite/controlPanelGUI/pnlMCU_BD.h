/**
@file 	pnlMCU_BD.h
@author Lime Microsystems
*/

#ifndef PNLMCU_BD_H
#define PNLMCU_BD_H

#include "MCU_BD.h"
#include "LMS7002_MainControl.h"

//(*Headers(pnlMCU_BD)
#include <wx/panel.h>
class wxGauge;
class wxCheckBox;
class wxTextCtrl;
class wxRadioBox;
class wxRadioButton;
class wxStaticText;
class wxFlexGridSizer;
class wxBoxSizer;
class wxButton;
class wxStaticBoxSizer;
class wxChoice;
class wxGridSizer;
//*)

class pnlMCU_BD: public wxPanel
{



	public:
	    LMS7002_MainControl * lmsControl;
		pnlMCU_BD(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles=0, wxString idname="");
		void InitDialog();
		virtual ~pnlMCU_BD();
		void Initialize(LMS7002_MainControl *pControl);
		void SetProgressBar(int i);

		//(*Declarations(pnlMCU_BD)
		wxStaticText* StaticText10;
		wxButton* RunInstr;
		wxButton* btnLoadTestFile;
		wxButton* Button4;
		wxButton* btnTxIQ;
		wxStaticText* ProgCodeFile;
		wxButton* EraseIRAM;
		wxButton* ViewIRAM;
		wxStaticText* StaticText2;
		wxRadioButton* RadioButton6;
		wxStaticText* StaticText6;
		wxChoice* SelDiv;
		wxStaticText* StaticText8;
		wxStaticText* m_sProgFinished;
		wxRadioButton* RadioButton7;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxRadioBox* rgrMode;
		wxTextCtrl* InstrNo;
		wxStaticText* lblAlgorithmStatus;
		wxRadioButton* m_cCtrlMCU_BD;
		wxTextCtrl* m_sTestNo;
		wxStaticText* TestResultsFile;
		wxStaticText* PCValue;
		wxButton* ViewSFRs;
		wxButton* ResetPC;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxTextCtrl* TextCtrl1;
		wxGauge* gaugeProgress;
		wxButton* btnRxDC;
		wxButton* btnTxDC;
		wxButton* btnRunTest;
		wxButton* Button_LOADHEX;
		wxStaticText* StaticText4;
		wxButton* btnStartProgramming;
		wxChoice* Choice1;
		wxStaticText* P;
		wxCheckBox* chkReset;
		wxStaticText* ReadResult;
		wxCheckBox* DebugMode;
		//*)

	protected:

		//(*Identifiers(pnlMCU_BD)
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON_LOADHEX;
		static const long ID_CHECKBOX_RESETMCU;
		static const long ID_RADIOBOX1;
		static const long ID_BUTTON_STARTPROG;
		static const long ID_S_PROGFINISHED;
		static const long ID_STATICTEXT3;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT4;
		static const long ID_TESTNO;
		static const long ID_BUTTON3;
		static const long ID_DEBUGMODE;
		static const long ID_RUNINSTR;
		static const long ID_STATICTEXT6;
		static const long ID_INSTRNO;
		static const long ID_RESETPC;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_VIEWSFRS;
		static const long ID_VIEWIRAM;
		static const long ID_ERASEIRAM;
		static const long ID_STATICTEXT10;
		static const long ID_SELDIV;
		static const long ID_RADIOBUTTON4;
		static const long ID_RADIOBUTTON5;
		static const long ID_STATICTEXT5;
		static const long ID_CHOICE1;
		static const long ID_RADIOBUTTON7;
		static const long ID_STATICTEXT11;
		static const long ID_TEXTCTRL1;
		static const long ID_RADIOBUTTON6;
		static const long ID_STATICTEXT9;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_STATICTEXT2;
		static const long ID_GAUGE1;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		//*)

	private:

		//(*Handlers(pnlMCU_BD)
		void OnRadioBox1Select(wxCommandEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnButton4Click(wxCommandEvent& event);
		void OnRadioButton2Select(wxCommandEvent& event);
		void OnRadioButton3Select(wxCommandEvent& event);
		void OnRadioButton1Select(wxCommandEvent& event);
		void Onm_sTestNoText(wxCommandEvent& event);
		void OnButton3Click(wxCommandEvent& event);
		void OnDebugModeClick(wxCommandEvent& event);
		void OnInstrNoText(wxCommandEvent& event);
		void OnResetPCClick(wxCommandEvent& event);
		void OnViewSFRsClick(wxCommandEvent& event);
		void OnViewIRAMClick(wxCommandEvent& event);
		void OnEraseIRAMClick(wxCommandEvent& event);
		void OnSelDivSelect(wxCommandEvent& event);
		void OnButton1Click1(wxCommandEvent& event);
		void Onm_cCtrlBasebandSelect(wxCommandEvent& event);
		void Onm_cCtrlMCU_BDSelect(wxCommandEvent& event);
		void OnChoice1Select(wxCommandEvent& event);
		void OnRadioButton7Select(wxCommandEvent& event);
		void OnRadioButton6Select(wxCommandEvent& event);
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnButton4Click1(wxCommandEvent& event);
		void OnchkResetClick(wxCommandEvent& event);
		void OnchkResetClick1(wxCommandEvent& event);
		void OnbtnStartProgrammingClick(wxCommandEvent& event);
		void OnButton_LOADHEXClick(wxCommandEvent& event);
		void OnbtnLoadTestFileClick(wxCommandEvent& event);
		void OnbtnRunTestClick(wxCommandEvent& event);
		void OnbtnRxDCClick(wxCommandEvent& event);
		void OnbtnTxDCClick(wxCommandEvent& event);
		void OnbtnTxIQClick(wxCommandEvent& event);
		//*)
         int m_iTestNo;
         int m_iInstrNo;
         int m_iPCvalue;
         int m_iDebug;

         int m_iTestResultFileLine;
         int TestResultArray_code[256];
         int TestResultArray_address[256];
         int TestResultArray_value[256];

         unsigned short m_iRegAddress;
         int m_iRegRead;
         unsigned short m_iRegData;

		DECLARE_EVENT_TABLE()
};

#endif
