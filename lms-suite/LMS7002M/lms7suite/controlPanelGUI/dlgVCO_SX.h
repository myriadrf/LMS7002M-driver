/**
@file dlgVCO_SX.h
@author Lime Microsystems
*/

#ifndef DLGVCO_SX_H
#define DLGVCO_SX_H

#include "pnlFreqTable.h"
//(*Headers(dlgVCO_SX)
#include <wx/dialog.h>
class wxPanel;
class wxCheckBox;
class wxStaticText;
class wxFlexGridSizer;
class wxButton;
//*)

class PLL_SX;
class PLL_CGEN;

class dlgVCO_SX: public wxDialog
{
	public:

		dlgVCO_SX(PLL_SX *data, PLL_CGEN *data_cgen, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~dlgVCO_SX();

		//(*Declarations(dlgVCO_SX)
		wxButton* btnSave;
		wxButton* btnCancel;
		wxStaticText* lblFilename;
		pnlFreqTable* pnlVCOL;
		wxStaticText* StaticText1;
		wxButton* btnOK;
		wxCheckBox* chkLoadFileOnStartup;
		wxButton* btnLoad;
		pnlFreqTable* pnlVCOM;
		pnlFreqTable* pnlVCOH;
		pnlFreqTable* pnlVCO_CGEN;
		//*)

	protected:
        PLL_SX *pll_data;
        PLL_CGEN *pll_data_cgen;
		//(*Identifiers(dlgVCO_SX)
		static const long ID_PANEL1;
		static const long ID_PANEL2;
		static const long ID_PANEL3;
		static const long ID_PANEL4;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_CHECKBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		//*)

	private:

		//(*Handlers(dlgVCO_SX)
		void OnInit(wxInitDialogEvent& event);
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnbtnLoadClick(wxCommandEvent& event);
		void OnbtnSaveClick(wxCommandEvent& event);
		void OnchkLoadFileOnStartupClick(wxCommandEvent& event);
		//*)

	protected:
        void SaveConfig();
		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
