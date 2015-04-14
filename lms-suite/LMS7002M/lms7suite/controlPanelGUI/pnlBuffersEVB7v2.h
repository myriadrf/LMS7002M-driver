/**
@file 	pnlBuffersEVB7v2.h
@author Lime Microsystems
*/
#ifndef pnlBuffersEVB7v2_H
#define pnlBuffersEVB7v2_H

//(*Headers(pnlBuffersEVB7v2)
#include <wx/panel.h>
class wxCheckBox;
class wxFlexGridSizer;
class wxStaticBoxSizer;
//*)

#include <GUIPanel.h>

#include <vector>

class LMS7002_MainControl;

class pnlBuffersEVB7v2: public wxPanel, GUIPanel
{
	public:

		pnlBuffersEVB7v2(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style=0, wxString name=wxEmptyString);
		void Initialize(LMS7002_MainControl *pControl);
		void UpdateGUI();
		int ReadbackGPIOStates();
		int SendCommand();
		virtual ~pnlBuffersEVB7v2();

		//(*Declarations(pnlBuffersEVB7v2)
		wxCheckBox* chkDIG_RST;
		wxCheckBox* chkG_PWR_DWN;
		wxCheckBox* chkDIO_DIR_CTRL1;
		wxCheckBox* chkIQSEL2_DIR;
		wxCheckBox* chkIQSEL1_DIR;
		wxCheckBox* chkDIO_DIR_CTRL2;
		wxCheckBox* chkDIO_BUFF_OE;
		//*)

	protected:

		//(*Identifiers(pnlBuffersEVB7v2)
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX7;
		//*)

	private:

		//(*Handlers(pnlBuffersEVB7v2)
        void OnPaint(wxPaintEvent& event);
		void OnEraseBackground(wxEraseEvent& event);
		void OnchkDIO_DIR_CTRL1Click(wxCommandEvent& event);
		void OnchkDIO_DIR_CTRL2Click(wxCommandEvent& event);
		void OnchkDIO_BUFF_OEClick(wxCommandEvent& event);
		void OnchkIQSEL1_DIRClick(wxCommandEvent& event);
		void OnchkIQSEL2_DIRClick(wxCommandEvent& event);
		void OnchkG_PWR_DWNClick(wxCommandEvent& event);
		void OnchkDIG_RSTClick(wxCommandEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		std::vector<unsigned char> gpioStates;
		unsigned char setbit(const unsigned char src, const int pos, const bool value);
        bool getbit(const unsigned char src, const int pos);

		DECLARE_EVENT_TABLE()
};

#endif
