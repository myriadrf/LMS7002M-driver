/**
@file 	dlgNCOSweepTest.h
@author Lime Microsystems
*/

#ifndef DLGNCOSWEEPTEST_H
#define DLGNCOSWEEPTEST_H

//(*Headers(dlgNCOSweepTest)
#include <wx/dialog.h>
class wxGauge;
class wxCheckBox;
class wxTextCtrl;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
//*)
#include "wx/timer.h"
#include <fstream>
#include "GUIPanel.h"
#include "wx/choice.h"
class LMS7002_MainControl;

class dlgNCOSweepTest: public wxDialog, public GUIPanel
{
	public:

		dlgNCOSweepTest(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgNCOSweepTest();
		void Initialize(LMS7002_MainControl *pControl, bool Rx);
		void UpdateGUI();
        void AddParameters();
        void Sweep();
		//(*Declarations(dlgNCOSweepTest)
		wxCheckBox* chkResampleRSSI0;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxGauge* progressBar;
		wxTextCtrl* txtFreqStepMHz;
		wxStaticText* StaticText1;
		wxStaticText* lblCurrentFreq;
		wxStaticText* StaticText3;
		wxTextCtrl* txtDuration;
		wxFlexGridSizer* m_parametersList;
		wxTextCtrl* txtStartFreqMHz;
		wxStaticText* lblTimeLeft;
		wxStaticText* StaticText5;
		wxTextCtrl* txtEndFreqMHz;
		wxButton* btnStartStop;
		wxFlexGridSizer* FlexGridSizer1;
		wxStaticText* StaticText4;
		//*)
		wxTextCtrl *txtparambeg;
		wxTextCtrl *txtparamend;
		wxTextCtrl *txtparamstep;
		wxChoice *paramchoice;

	protected:

		//(*Identifiers(dlgNCOSweepTest)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT6;
		static const long ID_TEXTCTRL4;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_STATICTEXT7;
		static const long ID_STATICTEXT8;
		static const long ID_GAUGE1;
		static const long ID_CHECKBOX1;
		//*)
		static const long ID_TIMER;
		static const long ID_TIMER_LEFT;

	private:

		//(*Handlers(dlgNCOSweepTest)
        void ParameterChangeHandler(wxCommandEvent& event);
		void OnbtnStartStopClick(wxCommandEvent& event);
		//*)

	protected:
	    bool m_sweeping;
	    vector<LMS7002_Parameter> parameters;
	    long m_paramBeg;
	    long m_paramEnd;
	    long m_paramStep;
	    int mStep_parameter;
	    int m_activeParameter;
	    double RSSI0;
	    bool firstRead;
	    std::fstream fout;
	    bool mRx;
	    double mStartFreqMHz;
	    double mEndFreqMHz;
	    double mStepFreqMHz;
	    int mStepPeriod_ms;
	    int mUpdatePeriod_ms;
	    int mStep;
	    int mTimeRemaining_ms;
	    wxTimer* m_pTimer;
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
