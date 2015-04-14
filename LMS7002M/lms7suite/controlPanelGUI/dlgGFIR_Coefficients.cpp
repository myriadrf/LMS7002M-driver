/**
@file	dlgGFIR_Coefficients.cpp
@author	Lime Microsystems
@brief	Dialog for modifying GFIR coefficients
*/

#include "dlgGFIR_Coefficients.h"
#include "LMS7002_MainControl.h"
#include <wx/filedlg.h>
#include "CoefficientFileParser.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(dlgGFIR_Coefficients)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgGFIR_Coefficients)
const long dlgGFIR_Coefficients::ID_STATICTEXT1 = wxNewId();
const long dlgGFIR_Coefficients::ID_STATICTEXT2 = wxNewId();
const long dlgGFIR_Coefficients::ID_BUTTON1 = wxNewId();
const long dlgGFIR_Coefficients::ID_BUTTON2 = wxNewId();
const long dlgGFIR_Coefficients::ID_BUTTON3 = wxNewId();
const long dlgGFIR_Coefficients::ID_STATICTEXT3 = wxNewId();
const long dlgGFIR_Coefficients::ID_SPINCTRL1 = wxNewId();
const long dlgGFIR_Coefficients::ID_GRID1 = wxNewId();
const long dlgGFIR_Coefficients::ID_BUTTON4 = wxNewId();
const long dlgGFIR_Coefficients::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgGFIR_Coefficients,wxDialog)
	//(*EventTable(dlgGFIR_Coefficients)
	//*)
END_EVENT_TABLE()

void dlgGFIR_Coefficients::Initialize(LMS7002_MainControl *control, wxString filename, int gfirID, bool Rx)
{
    lmsControl = control;
    m_Rx = Rx;
    m_gfirID = gfirID;
    txtLoadSource->SetLabel("Loaded from file:");
    if(filename != "")
    {
        txtFilename->SetLabel(filename);
    }
    else
    {
        //txtLoadSource->SetLabel("Loaded from table:");
        txtFilename->SetLabel("---");
    }
    vector<short> oldCoefficients;
    oldCoefficients = lmsControl->GetGFIRcoefficients(gfirID-1, Rx);
    spinCoefCount->SetValue(oldCoefficients.size());
    if(gridCoef->GetTable()->GetRowsCount() > 0)
        gridCoef->GetTable()->DeleteRows(0, gridCoef->GetTable()->GetRowsCount());
    gridCoef->GetTable()->AppendRows( oldCoefficients.size());
    for(unsigned i=0; i<oldCoefficients.size(); ++i)
    {
        gridCoef->SetCellValue(i, 0, wxString::Format("%i", oldCoefficients[i]));
    }
}

dlgGFIR_Coefficients::dlgGFIR_Coefficients(wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    lmsControl = NULL;
	BuildContent(id,pos,size);
}

void dlgGFIR_Coefficients::BuildContent(wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgGFIR_Coefficients)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer1;

	Create(0, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	txtLoadSource = new wxStaticText(this, ID_STATICTEXT1, _T("Loaded from table:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(txtLoadSource, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFilename = new wxStaticText(this, ID_STATICTEXT2, _T("---"), wxDefaultPosition, wxSize(289,13), 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(txtFilename, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer5 = new wxFlexGridSizer(0, 5, 0, 0);
	btnLoadFile = new wxButton(this, ID_BUTTON1, _T("Load from file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer5->Add(btnLoadFile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSave = new wxButton(this, ID_BUTTON2, _T("Save to file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer5->Add(btnSave, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnClearTable = new wxButton(this, ID_BUTTON3, _T("Clear table"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer5->Add(btnClearTable, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("Coefficients count:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer5->Add(StaticText3, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	spinCoefCount = new wxSpinCtrl(this, ID_SPINCTRL1, _T("40"), wxDefaultPosition, wxSize(64,-1), 0, 0, 120, 40, _T("ID_SPINCTRL1"));
	spinCoefCount->SetValue(_T("40"));
	FlexGridSizer5->Add(spinCoefCount, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	gridCoef = new wxGrid(this, ID_GRID1, wxDefaultPosition, wxSize(200,400), 0, _T("ID_GRID1"));
	gridCoef->CreateGrid(120,1);
	gridCoef->EnableEditing(true);
	gridCoef->EnableGridLines(true);
	gridCoef->SetRowLabelSize(32);
	gridCoef->SetDefaultCellFont( gridCoef->GetFont() );
	gridCoef->SetDefaultCellTextColour( gridCoef->GetForegroundColour() );
	FlexGridSizer3->Add(gridCoef, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
	btnOK = new wxButton(this, ID_BUTTON4, _T("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer6->Add(btnOK, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCancel = new wxButton(this, ID_BUTTON5, _T("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer6->Add(btnCancel, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgGFIR_Coefficients::OnbtnLoadFileClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgGFIR_Coefficients::OnbtnSaveClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgGFIR_Coefficients::OnbtnClearTableClick);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&dlgGFIR_Coefficients::OnspinCoefCountChange);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgGFIR_Coefficients::OnbtnOKClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgGFIR_Coefficients::OnbtnCancelClick);
	//*)
}

dlgGFIR_Coefficients::~dlgGFIR_Coefficients()
{
	//(*Destroy(dlgGFIR_Coefficients)
	//*)
}


void dlgGFIR_Coefficients::OnbtnLoadFileClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Open coefficients file"), "", "", "FIR Coeffs (*.fir)|*.fir", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(dlg.ShowModal() == wxID_CANCEL)
        return;

    int cbuf[200];
    int iVal = Parser::getcoeffs((const char*)dlg.GetPath().ToStdString().c_str(), cbuf, 200);

    switch(iVal)
    {
    case -2:
        wxMessageDialog(this, "syntax error within the file", "Warning");
        break;
    case -3:
        wxMessageDialog(this, "filename is empty string", "Warning");
        break;
    case -4:
        wxMessageDialog(this, "can not open the file", "Warning");
        break;
    case -5:
        wxMessageDialog(this, "too many coefficients in the file", "Warning");
        break;
    }
    if(iVal < 0)
        return;

    txtFilename->SetLabel(dlg.GetPath());

    spinCoefCount->SetValue(iVal);
    if(gridCoef->GetTable()->GetRowsCount() > 0)
        gridCoef->GetTable()->DeleteRows(0, gridCoef->GetTable()->GetRowsCount());
    gridCoef->GetTable()->AppendRows( spinCoefCount->GetValue());
    for(int i=0; i<iVal; ++i)
    {
        gridCoef->SetCellValue(i, 0, wxString::Format("%i", cbuf[i]));
    }
}

void dlgGFIR_Coefficients::OnspinCoefCountChange(wxSpinEvent& event)
{
    if(spinCoefCount->GetValue() < gridCoef->GetTable()->GetRowsCount())
        gridCoef->GetTable()->DeleteRows(spinCoefCount->GetValue(), gridCoef->GetTable()->GetRowsCount()-spinCoefCount->GetValue());
    else
        gridCoef->GetTable()->AppendRows( spinCoefCount->GetValue()-gridCoef->GetTable()->GetRowsCount());
}

void dlgGFIR_Coefficients::OnbtnClearTableClick(wxCommandEvent& event)
{
    if(gridCoef->GetTable()->GetRowsCount() > 0)
        gridCoef->GetTable()->DeleteRows(0, gridCoef->GetTable()->GetRowsCount());
    gridCoef->GetTable()->AppendRows( spinCoefCount->GetValue());
    for(int i=0; i<spinCoefCount->GetValue(); ++i)
    {
        gridCoef->SetCellValue(i, 0, wxString::Format("%i", 0));
    }
}

void dlgGFIR_Coefficients::OnbtnOKClick(wxCommandEvent& event)
{
    short coefficients[200];
    memset(coefficients, 0, sizeof(short)*200);
    long ltemp;
    for(int i=0; i<spinCoefCount->GetValue(); ++i)
    {
        ltemp = 0;
        gridCoef->GetCellValue(i, 0).ToLong(&ltemp);
        coefficients[i] = ltemp;
    }
    lmsControl->LoadGFIRCoefficients(coefficients, spinCoefCount->GetValue(), m_gfirID, m_Rx);
    //txtFilename->SetLabel("");
    EndModal(wxID_OK);
}

void dlgGFIR_Coefficients::OnbtnCancelClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

void dlgGFIR_Coefficients::OnbtnSaveClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Save coefficients file"), "", "", "FIR Coeffs (*.fir)|*.fir", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if(dlg.ShowModal() == wxID_CANCEL)
        return;
    int coefficients[200];
    memset(coefficients, 0, sizeof(unsigned short)*200);
    long ltemp;
    for(int i=0; i<spinCoefCount->GetValue(); ++i)
    {
        ltemp = 0;
        gridCoef->GetCellValue(i, 0).ToLong(&ltemp);
        coefficients[i] = ltemp;
    }
    Parser::saveToFile((const char*)dlg.GetPath().ToStdString().c_str(), coefficients, spinCoefCount->GetValue());
}
