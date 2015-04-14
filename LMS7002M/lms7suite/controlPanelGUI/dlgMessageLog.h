/**
@file 	dlgMessageLog.h
@author	Lime Microsystems
*/

#ifndef dlgMessageLog_H
#define dlgMessageLog_H

//(*Headers(dlgMessageLog)
#include <wx/dialog.h>
class wxCheckBox;
class wxRichTextCtrl;
class wxFlexGridSizer;
class wxButton;
class wxStaticBoxSizer;
//*)

class dlgMessageLog: public wxDialog
{
	public:

		dlgMessageLog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		void Write(const char *text);
		virtual ~dlgMessageLog();

		//(*Declarations(dlgMessageLog)
		wxButton* btnSave;
		wxCheckBox* chkWARNINGS;
		wxCheckBox* chkDATA;
		wxButton* btnClear;
		wxCheckBox* chkERRORS;
		wxCheckBox* chkINFO;
		wxRichTextCtrl* txtTextField;
		//*)

	protected:

		//(*Identifiers(dlgMessageLog)
		static const long ID_RICHTEXTCTRL1;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(dlgMessageLog)
		void OnbtnSaveClick(wxCommandEvent& event);
		void OnbtnClearClick(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		void OnChangeFilter(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
