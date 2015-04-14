/**
@file 	pnlBoard.h
@author Lime Microsystems
*/
#ifndef PNLBOARD_H
#define PNLBOARD_H

//(*Headers(pnlBoard)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/combobox.h>
//*)

#include "LMS7002M_Commands.h"

class ComboBoxMap;
class Si5351C;
class ADF_module;

class pnlBoard: public wxPanel
{
	public:

		pnlBoard(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int styles=0, wxString idname="");
		virtual ~pnlBoard();

		void Initialize(Si5351C* pModule, ADF_module *pADF);
		void ModifyClocksGUI(eLMS_DEV board);
		void ClockEnable(unsigned int i, bool enabled);

		//(*Declarations(pnlBoard)
		wxStaticText* StaticText10;
		wxStaticBoxSizer* sizerReferenceCounterLatch;
		wxStaticText* StaticText22;
		wxButton* btnUpload;
		wxStaticText* StaticText9;
		wxCheckBox* chkEN_CLK5;
		wxStaticText* StaticText20;
		wxRadioBox* rgrPDP_i;
		wxCheckBox* chkInvert_CLK6;
		wxTextCtrl* txtFreq_CLK7;
		wxTextCtrl* txtFreq_CLK1;
		ComboBoxMap* cmbCS1_f;
		wxCheckBox* chkEN_CLK3;
		wxCheckBox* chkEN_CLK4;
		wxCheckBox* chkInvert_CLK3;
		wxTextCtrl* txtFreq_CLK5;
		ComboBoxMap* cmbCS2_f;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxSpinCtrl* spinNCnt;
		wxTextCtrl* txtFreq_CLK0;
		wxStaticText* lblCLK6;
		wxStaticText* StaticText14;
		wxStaticText* lblCLK7;
		wxStaticText* lblCLK0;
		ComboBoxMap* cmbFL_i;
		wxStaticBoxSizer* sizerInitializationLatch;
		wxStaticText* StaticText6;
		wxStaticText* lblCLK5;
		wxStaticText* StaticText19;
		wxStaticBoxSizer* sizerFunctionLatch;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		ComboBoxMap* cmbLDP;
		wxStaticText* StaticText18;
		wxRadioBox* rgrPD1_f;
		wxButton* btnCalcSend;
		wxStaticText* StaticText1;
		wxRadioBox* rgrCPS_f;
		ComboBoxMap* cmbMOC_f;
		ComboBoxMap* cmbTC_i;
		wxStaticText* StaticText3;
		wxTextCtrl* txtFref;
		wxRadioBox* rgrPDP_f;
		ComboBoxMap* cmbFL_f;
		wxSpinCtrl* spinRCnt;
		wxStaticText* StaticText21;
		ComboBoxMap* cmbMOC_i;
		wxButton* btnConfigure;
		wxCheckBox* chkEN_CLK6;
		wxStaticText* StaticText23;
		wxStaticText* StaticText24;
		wxRadioBox* rgrCPS_i;
		wxStaticText* lblCLK4;
		wxStaticText* lblCLK2;
		wxTextCtrl* txtFreq_CLK3;
		wxTextCtrl* txtFreq_CLK6;
		ComboBoxMap* cmbCS1_i;
		wxTextCtrl* txtFreq_CLK2;
		wxRadioBox* rgrPD2_f;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		ComboBoxMap* cmbCPG;
		wxCheckBox* chkInvert_CLK2;
		wxCheckBox* chkInvert_CLK0;
		wxCheckBox* chkEN_CLK1;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		wxRadioBox* rgrPD1_i;
		wxStaticText* lblFcomp;
		wxStaticText* lblCLK3;
		wxCheckBox* chkEN_CLK7;
		wxCheckBox* chkInvert_CLK1;
		wxTextCtrl* txtFreq_CLK4;
		wxRadioBox* rgrCR_f;
		wxTextCtrl* txtFvco;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		ComboBoxMap* cmbTC_f;
		wxTextCtrl* txtCLKIN_MHz;
		wxStaticText* lblCLK1;
		wxRadioBox* rgrCR_i;
		wxStaticText* lblFvco;
		wxCheckBox* chkInvert_CLK7;
		wxCheckBox* chkInvert_CLK5;
		wxCheckBox* chkEN_CLK2;
		wxCheckBox* chkEN_CLK0;
		wxStaticText* StaticText16;
		wxRadioBox* rgrPD2_i;
		wxCheckBox* chkInvert_CLK4;
		ComboBoxMap* cmbCS2_i;
		ComboBoxMap* cmbABW;
		//*)

	protected:

		//(*Identifiers(pnlBoard)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_STATICTEXT3;
		static const long ID_COMBOBOX1;
		static const long ID_COMBOBOX2;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT4;
		static const long ID_STATICTEXT5;
		static const long ID_COMBOBOX3;
		static const long ID_SPINCTRL2;
		static const long ID_STATICTEXT6;
		static const long ID_STATICTEXT7;
		static const long ID_COMBOBOX4;
		static const long ID_COMBOBOX5;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT9;
		static const long ID_COMBOBOX6;
		static const long ID_COMBOBOX7;
		static const long ID_STATICTEXT10;
		static const long ID_COMBOBOX8;
		static const long ID_RADIOBOX1;
		static const long ID_RADIOBOX2;
		static const long ID_RADIOBOX3;
		static const long ID_RADIOBOX4;
		static const long ID_RADIOBOX5;
		static const long ID_STATICTEXT17;
		static const long ID_STATICTEXT18;
		static const long ID_COMBOBOX9;
		static const long ID_COMBOBOX10;
		static const long ID_STATICTEXT19;
		static const long ID_STATICTEXT20;
		static const long ID_COMBOBOX11;
		static const long ID_COMBOBOX12;
		static const long ID_STATICTEXT21;
		static const long ID_COMBOBOX13;
		static const long ID_RADIOBOX6;
		static const long ID_RADIOBOX7;
		static const long ID_RADIOBOX8;
		static const long ID_RADIOBOX9;
		static const long ID_RADIOBOX10;
		static const long ID_STATICTEXT11;
		static const long ID_STATICTEXT12;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT13;
		static const long ID_STATICTEXT14;
		static const long ID_STATICTEXT15;
		static const long ID_STATICTEXT16;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT22;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT23;
		static const long ID_STATICTEXT24;
		static const long ID_STATICTEXT25;
		static const long ID_STATICTEXT26;
		static const long ID_STATICTEXT27;
		static const long ID_CHECKBOX1;
		static const long ID_TEXTCTRL4;
		static const long ID_CHECKBOX9;
		static const long ID_STATICTEXT28;
		static const long ID_CHECKBOX2;
		static const long ID_TEXTCTRL5;
		static const long ID_CHECKBOX10;
		static const long ID_STATICTEXT29;
		static const long ID_CHECKBOX3;
		static const long ID_TEXTCTRL6;
		static const long ID_CHECKBOX11;
		static const long ID_STATICTEXT30;
		static const long ID_CHECKBOX4;
		static const long ID_TEXTCTRL7;
		static const long ID_CHECKBOX12;
		static const long ID_STATICTEXT31;
		static const long ID_CHECKBOX5;
		static const long ID_TEXTCTRL8;
		static const long ID_CHECKBOX13;
		static const long ID_STATICTEXT32;
		static const long ID_CHECKBOX6;
		static const long ID_TEXTCTRL9;
		static const long ID_CHECKBOX14;
		static const long ID_STATICTEXT33;
		static const long ID_CHECKBOX7;
		static const long ID_TEXTCTRL10;
		static const long ID_CHECKBOX15;
		static const long ID_STATICTEXT34;
		static const long ID_CHECKBOX8;
		static const long ID_TEXTCTRL11;
		static const long ID_CHECKBOX16;
		static const long ID_BUTTON5;
		//*)

	private:

		//(*Handlers(pnlBoard)
		void OnbtnConfigureClockClick(wxCommandEvent& event);
		void OnbtnSynchronizeClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		Si5351C* m_pSi5351C;
        ADF_module* m_pADF;
		DECLARE_EVENT_TABLE()
};

#endif
