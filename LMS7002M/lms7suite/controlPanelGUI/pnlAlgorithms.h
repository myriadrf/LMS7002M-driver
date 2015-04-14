/**
@file 	pnlAlgorithms.h
@author	Lime Microsystems
*/

#ifndef PNLALGORITHMS_H
#define PNLALGORITHMS_H

//(*Headers(pnlAlgorithms)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "GUIPanel.h"
#include "SignalHandler.h"
#include "ComboBoxMap.h"
#include <vector>

class pnlAlgorithms: public wxPanel, GUIPanel, public SignalHandler
{
	public:

		pnlAlgorithms(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name="");
		virtual ~pnlAlgorithms();
		void Initialize(LMS7002_MainControl *pControl);
        void UpdateGUI();
        void HandleMessage(const LMS_Message &msg);

        void InitDemoStages();
        std::vector<wxStaticText*> mStageNames;
        int ActivateStageName(int i);

        int DemoCalibration();

		//(*Declarations(pnlAlgorithms)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		ComboBoxMap* cmbGCORRQ_RXTSP;
		wxButton* btnNextDemo;
		ComboBoxMap* cmbIQCORR_TXTSP;
		ComboBoxMap* cmbGCORRQ_TXTSP;
		ComboBoxMap* cmbDCCORRQ_TXTSP;
		wxStaticText* StaticText2;
		ComboBoxMap* cmbDCOFFQ_RFE;
		wxFlexGridSizer* sizerStages;
		wxStaticText* StaticText6;
		wxButton* btnCalibrateRXIQ;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		ComboBoxMap* cmbDCCORRI_TXTSP;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		ComboBoxMap* cmbDCOFFI_RFE;
		ComboBoxMap* cmbGCORRI_RXTSP;
		ComboBoxMap* cmbGCORRI_TXTSP;
		ComboBoxMap* cmbIQCORR_RXTSP;
		wxStaticText* StaticText5;
		wxButton* btnCalibrateTXIQ;
		wxCheckBox* chkEN_DCOFF_RXFE_RFE;
		wxButton* btnCalibrateAll;
		wxButton* btnRepeatDemo;
		wxStaticText* StaticText4;
		wxButton* btnResetDemo;
		//*)

	protected:

		//(*Identifiers(pnlAlgorithms)
		static const long ID_STATICTEXT3;
		static const long ID_GCORRQ_RXTSP;
		static const long ID_STATICTEXT10;
		static const long ID_GCORRI_RXTSP;
		static const long ID_STATICTEXT11;
		static const long ID_IQCORR_RXTSP;
		static const long ID_STATICTEXT6;
		static const long ID_DCOFFI_RFE;
		static const long ID_STATICTEXT7;
		static const long ID_DCOFFQ_RFE;
		static const long ID_EN_DCOFF_RXFE_RFE;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT4;
		static const long ID_GCORRQ_TXTSP;
		static const long ID_STATICTEXT5;
		static const long ID_GCORRI_TXTSP;
		static const long ID_STATICTEXT2;
		static const long ID_IQCORR_TXTSP;
		static const long ID_STATICTEXT1;
		static const long ID_DCCORRI_TXTSP;
		static const long ID_STATICTEXT9;
		static const long ID_DCCORRQ_TXTSP;
		static const long ID_BUTTON10;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		//*)

	private:

		//(*Handlers(pnlAlgorithms)
		void ParameterChangeHandler(wxCommandEvent& event);
		void OnbtnCalibrateRXDCClick(wxCommandEvent& event);
		void OnbtnCalibrateRXDCClick1(wxCommandEvent& event);
		void OnbtnCalibrateDC_RFLOOPClick(wxCommandEvent& event);
		void OnbtnCalibrateRXIQClick(wxCommandEvent& event);
		void OnbtnCalibrateTXIQClick(wxCommandEvent& event);
		void OnbtnCalibrateAllClick(wxCommandEvent& event);
		void OnbtnResetDemoClick(wxCommandEvent& event);
		void OnbtnRepeatDemoClick(wxCommandEvent& event);
		void OnbtnNextDemoClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
        void AssignEnumsToIds();
		DECLARE_EVENT_TABLE()
};

#endif
