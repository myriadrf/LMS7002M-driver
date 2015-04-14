/**
@file	pnlFreqTable.cpp
@author	Lime Microsystems
@brief	table for displaying vco frequencies
*/

#include "pnlFreqTable.h"

//(*InternalHeaders(pnlFreqTable)
#include <wx/grid.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/string.h>
#include <wx/stattext.h>
//*)

//(*IdInit(pnlFreqTable)
const long pnlFreqTable::ID_STATICTEXT1 = wxNewId();
const long pnlFreqTable::ID_STATICTEXT2 = wxNewId();
const long pnlFreqTable::ID_SPINCTRL1 = wxNewId();
const long pnlFreqTable::ID_GRID1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlFreqTable,wxPanel)
	//(*EventTable(pnlFreqTable)
	//*)
END_EVENT_TABLE()

pnlFreqTable::pnlFreqTable(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
	BuildContent(parent,id,pos,size);
}

void pnlFreqTable::Initialize(const char *title, const vector<double> &freqs)
{
    txtTitle->SetLabel(title);
    if(gridValues->GetTable()->GetRowsCount() > 0)
        gridValues->GetTable()->DeleteRows(0, gridValues->GetTable()->GetRowsCount());
    gridValues->AppendRows(freqs.size());
    for(unsigned i = 0; i<freqs.size(); ++i)
    {
        gridValues->SetCellValue(i, 0, wxString::Format("%f", freqs[i]));
    }
    spinValueCount->SetValue(freqs.size());
}

void pnlFreqTable::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlFreqTable)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer3;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(2);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	txtTitle = new wxStaticText(this, ID_STATICTEXT1, _T("VCO"), wxDefaultPosition, wxSize(160,13), wxALIGN_CENTRE, _T("ID_STATICTEXT1"));
	FlexGridSizer3->Add(txtTitle, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _T("Value count:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText1, 1, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	spinValueCount = new wxSpinCtrl(this, ID_SPINCTRL1, _T("2"), wxDefaultPosition, wxSize(48,-1), 0, 0, 128, 2, _T("ID_SPINCTRL1"));
	spinValueCount->SetValue(_T("2"));
	FlexGridSizer2->Add(spinValueCount, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	gridValues = new wxGrid(this, ID_GRID1, wxDefaultPosition, wxSize(180,200), 0, _T("ID_GRID1"));
	gridValues->CreateGrid(0,1);
	gridValues->EnableEditing(true);
	gridValues->EnableGridLines(true);
	gridValues->SetRowLabelSize(32);
	gridValues->SetDefaultColSize(128, true);
	gridValues->SetColLabelValue(0, _T("Frequency(GHz)"));
	gridValues->SetDefaultCellFont( gridValues->GetFont() );
	gridValues->SetDefaultCellTextColour( gridValues->GetForegroundColour() );
	FlexGridSizer1->Add(gridValues, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&pnlFreqTable::OnspinValueCountChange);
	//*)
}

pnlFreqTable::~pnlFreqTable()
{
	//(*Destroy(pnlFreqTable)
	//*)
}


void pnlFreqTable::OnspinValueCountChange(wxSpinEvent& event)
{
    if(spinValueCount->GetValue() < gridValues->GetTable()->GetRowsCount())
        gridValues->GetTable()->DeleteRows(spinValueCount->GetValue(), gridValues->GetTable()->GetRowsCount()-spinValueCount->GetValue());
    else
        gridValues->GetTable()->AppendRows( spinValueCount->GetValue()-gridValues->GetTable()->GetRowsCount());
}

vector<double> pnlFreqTable::GetFrequencies() const
{
    vector<double> temp;
    double dtemp = 0;
    for(int i=0; i<spinValueCount->GetValue(); ++i)
    {
        dtemp = 0;
        gridValues->GetCellValue(i, 0).ToDouble(&dtemp);
        temp.push_back(dtemp);
    }
    return temp;
}
