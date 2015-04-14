/**
@file 	pnlMyriad7.h
@author Lime Microsystems
*/
#ifndef PNLMYRIAD7_H
#define PNLMYRIAD7_H

//(*Headers(pnlMyriad7)
#include <wx/panel.h>
class wxComboBox;
class wxStaticText;
class wxFlexGridSizer;
//*)

#include "GUIPanel.h"
#include "PluginPanel.h"
class LMS7002_MainControl;

class pnlMyriad7: public wxPanel, public GUIPanel, public PluginPanel
{
	public:

		pnlMyriad7(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		void Initialize(LMS7002_MainControl* pControl);
		virtual ~pnlMyriad7();
		virtual void UpdatePanel();

		//(*Declarations(pnlMyriad7)
		wxStaticText* StaticText2;
		wxComboBox* cmbGPIO2;
		wxStaticText* StaticText1;
		wxComboBox* cmbGPIO_1_0;
		//*)

		//(*Identifiers(pnlMyriad7)
		static const long ID_STATICTEXT1;
		static const long ID_COMBOBOX1;
		static const long ID_STATICTEXT2;
		static const long ID_COMBOBOX2;
		//*)

		//(*Handlers(pnlMyriad7)
        void ParameterChangeHandler(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
