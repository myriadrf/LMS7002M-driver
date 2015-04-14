/**
@file 	dlgGFIR_Coefficients.h
@author	Lime Microsystems
*/

#ifndef DLGGFIR_COEFFICIENTS_H
#define DLGGFIR_COEFFICIENTS_H

//(*Headers(dlgGFIR_Coefficients)
#include <wx/dialog.h>
class wxGrid;
class wxSpinEvent;
class wxStaticText;
class wxFlexGridSizer;
class wxSpinCtrl;
class wxButton;
class wxGridEvent;
//*)

class LMS7002_MainControl;

class dlgGFIR_Coefficients: public wxDialog
{
	public:

		dlgGFIR_Coefficients(wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		void Initialize(LMS7002_MainControl *control, wxString filename, int gfirID, bool Rx);
		virtual ~dlgGFIR_Coefficients();

		//(*Declarations(dlgGFIR_Coefficients)
		wxButton* btnClearTable;
		wxStaticText* txtLoadSource;
		wxButton* btnSave;
		wxButton* btnLoadFile;
		wxButton* btnCancel;
		wxStaticText* StaticText3;
		wxButton* btnOK;
		wxStaticText* txtFilename;
		wxGrid* gridCoef;
		wxSpinCtrl* spinCoefCount;
		//*)

	protected:
        LMS7002_MainControl *lmsControl;
        bool m_Rx;
        int m_gfirID;
		//(*Identifiers(dlgGFIR_Coefficients)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL1;
		static const long ID_GRID1;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		//*)

	private:

		//(*Handlers(dlgGFIR_Coefficients)
		void OnbtnLoadFileClick(wxCommandEvent& event);
		void OnspinCoefCountChange(wxSpinEvent& event);
		void OnbtnClearTableClick(wxCommandEvent& event);
		void OnbtnOKClick(wxCommandEvent& event);
		void OnbtnCancelClick(wxCommandEvent& event);
		void OnbtnSaveClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
