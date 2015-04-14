/**
@file	dlgViewIRAM.cpp
@author Lime Microsystems
@brief	dialog for viewing MCU IRAM data
*/

#include "dlgViewIRAM.h"

//(*InternalHeaders(dlgViewIRAM)
#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgViewIRAM)
const long dlgViewIRAM::ID_GRID1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgViewIRAM,wxDialog)
	//(*EventTable(dlgViewIRAM)
	//*)
END_EVENT_TABLE()

dlgViewIRAM::dlgViewIRAM(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{

	pPnlMCU_BD=(pnlMCU_BD *)parent;
	//(*Initialize(dlgViewIRAM)
	wxBoxSizer* BoxSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	Grid1 = new wxGrid(this, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
	Grid1->CreateGrid(32,8);
	Grid1->EnableEditing(false);
	Grid1->EnableGridLines(true);
	Grid1->SetDefaultCellFont( Grid1->GetFont() );
	Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );
	BoxSizer1->Add(Grid1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
}

dlgViewIRAM::~dlgViewIRAM()
{
	//(*Destroy(dlgViewIRAM)
	//*)
}

void dlgViewIRAM::InitDialog(){

   	InitGridData();
}

void dlgViewIRAM::InitGridData()
{
	int row=0;
	int col=0;
   	int i=0;
	int j=0;
	int value;
	wxString temps="";

	for (i=0; i<=31; i++){
		temps.Printf(_("Row: 0x%02X"), 0xF8-i*8);
		Grid1->SetRowLabelValue(i, temps);
		//Grid1->SetCellValue(i+1, 0, temps);
	}

	for (j=0; j<8; j++){
        //colums
		temps.Printf(_T("Col.: 0x%02X"), j);
		Grid1->SetColLabelValue(j, temps);
		//CellValue(0, j+1,temps);
	}

	for (i=0x0000; i<=0x00FF; i++) {
        value=pPnlMCU_BD->lmsControl->getMCU_BD()->m_IRAM[i];

		row=(i/8);
		col=(i-row*8);
		row=31-row;
		temps.Printf(_T("0x%02X"), value);
		Grid1->SetCellValue(row,col,temps);
	}
}

