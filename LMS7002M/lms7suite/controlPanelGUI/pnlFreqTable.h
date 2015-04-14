/**
@file 	pnlFreqTable.h
@author	Lime Microsystems
*/

#ifndef PNLFREQTABLE_H
#define PNLFREQTABLE_H

//(*Headers(pnlFreqTable)
#include <wx/panel.h>
class wxGridEvent;
class wxFlexGridSizer;
class wxSpinEvent;
class wxSpinCtrl;
class wxGrid;
class wxStaticText;
//*)
#include <vector>
using namespace std;

class pnlFreqTable: public wxPanel
{
	public:

		pnlFreqTable(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int style = 0, wxString name = "");
		virtual ~pnlFreqTable();

        void Initialize(const char *title, const vector<double> &freqs);
        vector<double> GetFrequencies() const;

		//(*Declarations(pnlFreqTable)
		wxStaticText* StaticText1;
		wxSpinCtrl* spinValueCount;
		wxGrid* gridValues;
		wxStaticText* txtTitle;
		//*)

	protected:
		//(*Identifiers(pnlFreqTable)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_SPINCTRL1;
		static const long ID_GRID1;
		//*)

	private:
		//(*Handlers(pnlFreqTable)
		void OnspinValueCountChange(wxSpinEvent& event);
		//*)

	protected:

		void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);

		DECLARE_EVENT_TABLE()
};

#endif
