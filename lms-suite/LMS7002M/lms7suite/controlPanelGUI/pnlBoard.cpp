/**
@file 	pnlBoard.cpp
@author Lime Microsystems
@brief	panel combining controls for EVB configuring
*/
#include "pnlBoard.h"
#include "ComboBoxMap.h"
#include "Si5351C.h"
#include "ADF_module.h"
//(*InternalHeaders(pnlBoard)
#include <wx/string.h>
//*)

//(*IdInit(pnlBoard)
const long pnlBoard::ID_STATICTEXT1 = wxNewId();
const long pnlBoard::ID_STATICTEXT2 = wxNewId();
const long pnlBoard::ID_STATICTEXT3 = wxNewId();
const long pnlBoard::ID_COMBOBOX1 = wxNewId();
const long pnlBoard::ID_COMBOBOX2 = wxNewId();
const long pnlBoard::ID_SPINCTRL1 = wxNewId();
const long pnlBoard::ID_STATICTEXT4 = wxNewId();
const long pnlBoard::ID_STATICTEXT5 = wxNewId();
const long pnlBoard::ID_COMBOBOX3 = wxNewId();
const long pnlBoard::ID_SPINCTRL2 = wxNewId();
const long pnlBoard::ID_STATICTEXT6 = wxNewId();
const long pnlBoard::ID_STATICTEXT7 = wxNewId();
const long pnlBoard::ID_COMBOBOX4 = wxNewId();
const long pnlBoard::ID_COMBOBOX5 = wxNewId();
const long pnlBoard::ID_STATICTEXT8 = wxNewId();
const long pnlBoard::ID_STATICTEXT9 = wxNewId();
const long pnlBoard::ID_COMBOBOX6 = wxNewId();
const long pnlBoard::ID_COMBOBOX7 = wxNewId();
const long pnlBoard::ID_STATICTEXT10 = wxNewId();
const long pnlBoard::ID_COMBOBOX8 = wxNewId();
const long pnlBoard::ID_RADIOBOX1 = wxNewId();
const long pnlBoard::ID_RADIOBOX2 = wxNewId();
const long pnlBoard::ID_RADIOBOX3 = wxNewId();
const long pnlBoard::ID_RADIOBOX4 = wxNewId();
const long pnlBoard::ID_RADIOBOX5 = wxNewId();
const long pnlBoard::ID_STATICTEXT17 = wxNewId();
const long pnlBoard::ID_STATICTEXT18 = wxNewId();
const long pnlBoard::ID_COMBOBOX9 = wxNewId();
const long pnlBoard::ID_COMBOBOX10 = wxNewId();
const long pnlBoard::ID_STATICTEXT19 = wxNewId();
const long pnlBoard::ID_STATICTEXT20 = wxNewId();
const long pnlBoard::ID_COMBOBOX11 = wxNewId();
const long pnlBoard::ID_COMBOBOX12 = wxNewId();
const long pnlBoard::ID_STATICTEXT21 = wxNewId();
const long pnlBoard::ID_COMBOBOX13 = wxNewId();
const long pnlBoard::ID_RADIOBOX6 = wxNewId();
const long pnlBoard::ID_RADIOBOX7 = wxNewId();
const long pnlBoard::ID_RADIOBOX8 = wxNewId();
const long pnlBoard::ID_RADIOBOX9 = wxNewId();
const long pnlBoard::ID_RADIOBOX10 = wxNewId();
const long pnlBoard::ID_STATICTEXT11 = wxNewId();
const long pnlBoard::ID_STATICTEXT12 = wxNewId();
const long pnlBoard::ID_TEXTCTRL1 = wxNewId();
const long pnlBoard::ID_TEXTCTRL2 = wxNewId();
const long pnlBoard::ID_STATICTEXT13 = wxNewId();
const long pnlBoard::ID_STATICTEXT14 = wxNewId();
const long pnlBoard::ID_STATICTEXT15 = wxNewId();
const long pnlBoard::ID_STATICTEXT16 = wxNewId();
const long pnlBoard::ID_BUTTON1 = wxNewId();
const long pnlBoard::ID_BUTTON2 = wxNewId();
const long pnlBoard::ID_STATICTEXT22 = wxNewId();
const long pnlBoard::ID_TEXTCTRL3 = wxNewId();
const long pnlBoard::ID_STATICTEXT23 = wxNewId();
const long pnlBoard::ID_STATICTEXT24 = wxNewId();
const long pnlBoard::ID_STATICTEXT25 = wxNewId();
const long pnlBoard::ID_STATICTEXT26 = wxNewId();
const long pnlBoard::ID_STATICTEXT27 = wxNewId();
const long pnlBoard::ID_CHECKBOX1 = wxNewId();
const long pnlBoard::ID_TEXTCTRL4 = wxNewId();
const long pnlBoard::ID_CHECKBOX9 = wxNewId();
const long pnlBoard::ID_STATICTEXT28 = wxNewId();
const long pnlBoard::ID_CHECKBOX2 = wxNewId();
const long pnlBoard::ID_TEXTCTRL5 = wxNewId();
const long pnlBoard::ID_CHECKBOX10 = wxNewId();
const long pnlBoard::ID_STATICTEXT29 = wxNewId();
const long pnlBoard::ID_CHECKBOX3 = wxNewId();
const long pnlBoard::ID_TEXTCTRL6 = wxNewId();
const long pnlBoard::ID_CHECKBOX11 = wxNewId();
const long pnlBoard::ID_STATICTEXT30 = wxNewId();
const long pnlBoard::ID_CHECKBOX4 = wxNewId();
const long pnlBoard::ID_TEXTCTRL7 = wxNewId();
const long pnlBoard::ID_CHECKBOX12 = wxNewId();
const long pnlBoard::ID_STATICTEXT31 = wxNewId();
const long pnlBoard::ID_CHECKBOX5 = wxNewId();
const long pnlBoard::ID_TEXTCTRL8 = wxNewId();
const long pnlBoard::ID_CHECKBOX13 = wxNewId();
const long pnlBoard::ID_STATICTEXT32 = wxNewId();
const long pnlBoard::ID_CHECKBOX6 = wxNewId();
const long pnlBoard::ID_TEXTCTRL9 = wxNewId();
const long pnlBoard::ID_CHECKBOX14 = wxNewId();
const long pnlBoard::ID_STATICTEXT33 = wxNewId();
const long pnlBoard::ID_CHECKBOX7 = wxNewId();
const long pnlBoard::ID_TEXTCTRL10 = wxNewId();
const long pnlBoard::ID_CHECKBOX15 = wxNewId();
const long pnlBoard::ID_STATICTEXT34 = wxNewId();
const long pnlBoard::ID_CHECKBOX8 = wxNewId();
const long pnlBoard::ID_TEXTCTRL11 = wxNewId();
const long pnlBoard::ID_CHECKBOX16 = wxNewId();
const long pnlBoard::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlBoard,wxPanel)
	//(*EventTable(pnlBoard)
	//*)
END_EVENT_TABLE()

pnlBoard::pnlBoard(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int styles, wxString idname)
{
    m_pSi5351C = NULL;
    m_pADF = NULL;
	BuildContent(parent,id,pos,size);
}

void pnlBoard::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlBoard)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer16;
	wxFlexGridSizer* FlexGridSizer19;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer22;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer8;
	wxStaticBoxSizer* StaticBoxSizer6;
	wxFlexGridSizer* FlexGridSizer15;
	wxFlexGridSizer* FlexGridSizer18;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer21;
	wxFlexGridSizer* FlexGridSizer14;
	wxFlexGridSizer* FlexGridSizer20;
	wxFlexGridSizer* FlexGridSizer13;
	wxFlexGridSizer* FlexGridSizer12;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	wxFlexGridSizer* FlexGridSizer17;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("ADF4002"));
	FlexGridSizer3 = new wxFlexGridSizer(3, 1, 0, 0);
	FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 5);
	FlexGridSizer4->AddGrowableCol(0);
	sizerReferenceCounterLatch = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Reference Counter Latch"));
	FlexGridSizer5 = new wxFlexGridSizer(2, 3, 0, 5);
	FlexGridSizer5->AddGrowableCol(0);
	FlexGridSizer5->AddGrowableCol(1);
	FlexGridSizer5->AddGrowableCol(2);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("Lock Detect Precision:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer5->Add(StaticText1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("Anti-Backlash:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer5->Add(StaticText2, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("Reference Counter:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer5->Add(StaticText3, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbLDP = new ComboBoxMap(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	cmbLDP->SetSelection( cmbLDP->Append(_T("Three Cycles")) );
	cmbLDP->Append(_T("Five Cycles"));
	FlexGridSizer5->Add(cmbLDP, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbABW = new ComboBoxMap(this, ID_COMBOBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
	cmbABW->SetSelection( cmbABW->Append(_T("2.9ns")) );
	cmbABW->Append(_T("6.0ns"));
	cmbABW->Append(_T("2.9ns"));
	FlexGridSizer5->Add(cmbABW, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	spinRCnt = new wxSpinCtrl(this, ID_SPINCTRL1, _T("125"), wxDefaultPosition, wxDefaultSize, 0, 0, 16383, 125, _T("ID_SPINCTRL1"));
	spinRCnt->SetValue(_T("125"));
	FlexGridSizer5->Add(spinRCnt, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	sizerReferenceCounterLatch->Add(FlexGridSizer5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(sizerReferenceCounterLatch, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("N Counter Latch"));
	FlexGridSizer6 = new wxFlexGridSizer(2, 2, 0, 5);
	FlexGridSizer6->AddGrowableCol(0);
	FlexGridSizer6->AddGrowableCol(1);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _T("CP Gain:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer6->Add(StaticText4, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _T("N Counter:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer6->Add(StaticText5, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCPG = new ComboBoxMap(this, ID_COMBOBOX3, wxEmptyString, wxDefaultPosition, wxSize(65,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX3"));
	cmbCPG->SetSelection( cmbCPG->Append(_T("0")) );
	cmbCPG->Append(_T("1"));
	FlexGridSizer6->Add(cmbCPG, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	spinNCnt = new wxSpinCtrl(this, ID_SPINCTRL2, _T("384"), wxDefaultPosition, wxSize(70,-1), 0, 0, 8191, 384, _T("ID_SPINCTRL2"));
	spinNCnt->SetValue(_T("384"));
	FlexGridSizer6->Add(spinNCnt, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer4->Add(FlexGridSizer6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	sizerFunctionLatch = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Function Latch"));
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 5);
	FlexGridSizer8 = new wxFlexGridSizer(4, 2, 0, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _T("Current Setting 1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer8->Add(StaticText6, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _T("Timer Counter:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer8->Add(StaticText7, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCS1_f = new ComboBoxMap(this, ID_COMBOBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX4"));
	cmbCS1_f->Append(_T("0"));
	cmbCS1_f->Append(_T("1"));
	cmbCS1_f->Append(_T("2"));
	cmbCS1_f->Append(_T("3"));
	cmbCS1_f->Append(_T("4"));
	cmbCS1_f->Append(_T("5"));
	cmbCS1_f->Append(_T("6"));
	cmbCS1_f->SetSelection( cmbCS1_f->Append(_T("7")) );
	FlexGridSizer8->Add(cmbCS1_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbTC_f = new ComboBoxMap(this, ID_COMBOBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX5"));
	cmbTC_f->SetSelection( cmbTC_f->Append(_T("3")) );
	cmbTC_f->Append(_T("7"));
	cmbTC_f->Append(_T("11"));
	cmbTC_f->Append(_T("15"));
	cmbTC_f->Append(_T("19"));
	cmbTC_f->Append(_T("23"));
	cmbTC_f->Append(_T("27"));
	cmbTC_f->Append(_T("31"));
	cmbTC_f->Append(_T("35"));
	cmbTC_f->Append(_T("39"));
	cmbTC_f->Append(_T("43"));
	cmbTC_f->Append(_T("47"));
	cmbTC_f->Append(_T("51"));
	cmbTC_f->Append(_T("55"));
	cmbTC_f->Append(_T("59"));
	cmbTC_f->Append(_T("63"));
	FlexGridSizer8->Add(cmbTC_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _T("Current Setting 2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer8->Add(StaticText8, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _T("Fastlock:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer8->Add(StaticText9, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCS2_f = new ComboBoxMap(this, ID_COMBOBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX6"));
	cmbCS2_f->Append(_T("0"));
	cmbCS2_f->Append(_T("1"));
	cmbCS2_f->Append(_T("2"));
	cmbCS2_f->Append(_T("3"));
	cmbCS2_f->Append(_T("4"));
	cmbCS2_f->Append(_T("5"));
	cmbCS2_f->Append(_T("6"));
	cmbCS2_f->SetSelection( cmbCS2_f->Append(_T("7")) );
	FlexGridSizer8->Add(cmbCS2_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbFL_f = new ComboBoxMap(this, ID_COMBOBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX7"));
	cmbFL_f->SetSelection( cmbFL_f->Append(_T("Disabled")) );
	cmbFL_f->Append(_T("Mode 1"));
	cmbFL_f->Append(_T("Mode 2"));
	FlexGridSizer8->Add(cmbFL_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer8, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9 = new wxFlexGridSizer(3, 1, 0, 0);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _T("Muxout Control"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer9->Add(StaticText10, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbMOC_f = new ComboBoxMap(this, ID_COMBOBOX8, wxEmptyString, wxDefaultPosition, wxSize(160,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX8"));
	cmbMOC_f->Append(_T("Three-State Output"));
	cmbMOC_f->SetSelection( cmbMOC_f->Append(_T("Digital Lock Detect")) );
	cmbMOC_f->Append(_T("N Divider Output"));
	cmbMOC_f->Append(_T("DVdd"));
	cmbMOC_f->Append(_T("R Divider Output"));
	cmbMOC_f->Append(_T("N-Chan OD Lock Detect"));
	cmbMOC_f->Append(_T("Serial Data Output"));
	cmbMOC_f->Append(_T("DGND"));
	FlexGridSizer9->Add(cmbMOC_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_1[2] =
	{
		_T("Negative"),
		_T("Positive")
	};
	rgrPDP_f = new wxRadioBox(this, ID_RADIOBOX1, _T("PD Polarity"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
	rgrPDP_f->SetSelection(1);
	FlexGridSizer9->Add(rgrPDP_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer9, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer10 = new wxFlexGridSizer(2, 2, 0, 5);
	wxString __wxRadioBoxChoices_2[2] =
	{
		_T("0"),
		_T("1")
	};
	rgrPD1_f = new wxRadioBox(this, ID_RADIOBOX2, _T("PD1"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX2"));
	rgrPD1_f->SetSelection(0);
	FlexGridSizer10->Add(rgrPD1_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_3[2] =
	{
		_T("Normal"),
		_T("R & N Reset")
	};
	rgrCR_f = new wxRadioBox(this, ID_RADIOBOX3, _T("Counter Reset"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_3, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX3"));
	rgrCR_f->SetSelection(0);
	FlexGridSizer10->Add(rgrCR_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_4[2] =
	{
		_T("0"),
		_T("1")
	};
	rgrPD2_f = new wxRadioBox(this, ID_RADIOBOX4, _T("PD2"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_4, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX4"));
	rgrPD2_f->SetSelection(0);
	FlexGridSizer10->Add(rgrPD2_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_5[2] =
	{
		_T("Normal"),
		_T("Three-State")
	};
	rgrCPS_f = new wxRadioBox(this, ID_RADIOBOX5, _T("CP State"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_5, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX5"));
	rgrCPS_f->SetSelection(0);
	FlexGridSizer10->Add(rgrCPS_f, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer7->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	sizerFunctionLatch->Add(FlexGridSizer7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(sizerFunctionLatch, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	sizerInitializationLatch = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Initialization Latch"));
	FlexGridSizer13 = new wxFlexGridSizer(0, 3, 0, 5);
	FlexGridSizer14 = new wxFlexGridSizer(4, 2, 0, 5);
	StaticText14 = new wxStaticText(this, ID_STATICTEXT17, _T("Current Setting 1:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	FlexGridSizer14->Add(StaticText14, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText16 = new wxStaticText(this, ID_STATICTEXT18, _T("Timer Counter:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
	FlexGridSizer14->Add(StaticText16, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCS1_i = new ComboBoxMap(this, ID_COMBOBOX9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX9"));
	cmbCS1_i->Append(_T("0"));
	cmbCS1_i->Append(_T("1"));
	cmbCS1_i->Append(_T("2"));
	cmbCS1_i->Append(_T("3"));
	cmbCS1_i->Append(_T("4"));
	cmbCS1_i->Append(_T("5"));
	cmbCS1_i->Append(_T("6"));
	cmbCS1_i->SetSelection( cmbCS1_i->Append(_T("7")) );
	FlexGridSizer14->Add(cmbCS1_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbTC_i = new ComboBoxMap(this, ID_COMBOBOX10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX10"));
	cmbTC_i->SetSelection( cmbTC_i->Append(_T("3")) );
	cmbTC_i->Append(_T("7"));
	cmbTC_i->Append(_T("11"));
	cmbTC_i->Append(_T("15"));
	cmbTC_i->Append(_T("19"));
	cmbTC_i->Append(_T("23"));
	cmbTC_i->Append(_T("27"));
	cmbTC_i->Append(_T("31"));
	cmbTC_i->Append(_T("35"));
	cmbTC_i->Append(_T("39"));
	cmbTC_i->Append(_T("43"));
	cmbTC_i->Append(_T("47"));
	cmbTC_i->Append(_T("51"));
	cmbTC_i->Append(_T("55"));
	cmbTC_i->Append(_T("59"));
	cmbTC_i->Append(_T("63"));
	FlexGridSizer14->Add(cmbTC_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText17 = new wxStaticText(this, ID_STATICTEXT19, _T("Current Setting 2:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
	FlexGridSizer14->Add(StaticText17, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText18 = new wxStaticText(this, ID_STATICTEXT20, _T("Fastlock:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
	FlexGridSizer14->Add(StaticText18, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbCS2_i = new ComboBoxMap(this, ID_COMBOBOX11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX11"));
	cmbCS2_i->Append(_T("0"));
	cmbCS2_i->Append(_T("1"));
	cmbCS2_i->Append(_T("2"));
	cmbCS2_i->Append(_T("3"));
	cmbCS2_i->Append(_T("4"));
	cmbCS2_i->Append(_T("5"));
	cmbCS2_i->Append(_T("6"));
	cmbCS2_i->SetSelection( cmbCS2_i->Append(_T("7")) );
	FlexGridSizer14->Add(cmbCS2_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbFL_i = new ComboBoxMap(this, ID_COMBOBOX12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX12"));
	cmbFL_i->SetSelection( cmbFL_i->Append(_T("Disabled")) );
	cmbFL_i->Append(_T("Mode 1"));
	cmbFL_i->Append(_T("Mode 2"));
	FlexGridSizer14->Add(cmbFL_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13->Add(FlexGridSizer14, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer15 = new wxFlexGridSizer(3, 1, 0, 0);
	StaticText19 = new wxStaticText(this, ID_STATICTEXT21, _T("Muxout Control"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
	FlexGridSizer15->Add(StaticText19, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	cmbMOC_i = new ComboBoxMap(this, ID_COMBOBOX13, wxEmptyString, wxDefaultPosition, wxSize(160,-1), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX13"));
	cmbMOC_i->Append(_T("Three-State Output"));
	cmbMOC_i->SetSelection( cmbMOC_i->Append(_T("Digital Lock Detect")) );
	cmbMOC_i->Append(_T("N Divider Output"));
	cmbMOC_i->Append(_T("DVdd"));
	cmbMOC_i->Append(_T("R Divider Output"));
	cmbMOC_i->Append(_T("N-Chan OD Lock Detect"));
	cmbMOC_i->Append(_T("Serial Data Output"));
	cmbMOC_i->Append(_T("DGND"));
	FlexGridSizer15->Add(cmbMOC_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_6[2] =
	{
		_T("Negative"),
		_T("Positive")
	};
	rgrPDP_i = new wxRadioBox(this, ID_RADIOBOX6, _T("PD Polarity"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_6, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX6"));
	rgrPDP_i->SetSelection(1);
	FlexGridSizer15->Add(rgrPDP_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13->Add(FlexGridSizer15, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer16 = new wxFlexGridSizer(2, 2, 0, 5);
	wxString __wxRadioBoxChoices_7[2] =
	{
		_T("0"),
		_T("1")
	};
	rgrPD1_i = new wxRadioBox(this, ID_RADIOBOX7, _T("PD1"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_7, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX7"));
	rgrPD1_i->SetSelection(0);
	FlexGridSizer16->Add(rgrPD1_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_8[2] =
	{
		_T("Normal"),
		_T("R & N Reset")
	};
	rgrCR_i = new wxRadioBox(this, ID_RADIOBOX8, _T("Counter Reset"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_8, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX8"));
	rgrCR_i->SetSelection(0);
	FlexGridSizer16->Add(rgrCR_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_9[2] =
	{
		_T("0"),
		_T("1")
	};
	rgrPD2_i = new wxRadioBox(this, ID_RADIOBOX9, _T("PD2"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_9, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX9"));
	rgrPD2_i->SetSelection(0);
	FlexGridSizer16->Add(rgrPD2_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxString __wxRadioBoxChoices_10[2] =
	{
		_T("Normal"),
		_T("Three-State")
	};
	rgrCPS_i = new wxRadioBox(this, ID_RADIOBOX10, _T("CP State"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_10, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX10"));
	rgrCPS_i->SetSelection(0);
	FlexGridSizer16->Add(rgrCPS_i, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer13->Add(FlexGridSizer16, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	sizerInitializationLatch->Add(FlexGridSizer13, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(sizerInitializationLatch, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer11 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, this, _T("Calculation of R && N"));
	FlexGridSizer12 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer17 = new wxFlexGridSizer(0, 2, 0, 5);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _T("Fref, MHz (X18)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer17->Add(StaticText11, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText12 = new wxStaticText(this, ID_STATICTEXT12, _T("Fxo, MHz:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	FlexGridSizer17->Add(StaticText12, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	txtFref = new wxTextCtrl(this, ID_TEXTCTRL1, _T("10"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer17->Add(txtFref, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFvco = new wxTextCtrl(this, ID_TEXTCTRL2, _T("30.72"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer17->Add(txtFvco, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText13 = new wxStaticText(this, ID_STATICTEXT13, _T("Fvco (MHz) ="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	FlexGridSizer17->Add(StaticText13, 1, wxTOP|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblFvco = new wxStaticText(this, ID_STATICTEXT14, _T("Fvco"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
	FlexGridSizer17->Add(lblFvco, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText15 = new wxStaticText(this, ID_STATICTEXT15, _T("LCM ="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	FlexGridSizer17->Add(StaticText15, 1, wxTOP|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	lblFcomp = new wxStaticText(this, ID_STATICTEXT16, _T("Fcomp"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	FlexGridSizer17->Add(lblFcomp, 1, wxTOP|wxBOTTOM|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer12->Add(FlexGridSizer17, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCalcSend = new wxButton(this, ID_BUTTON1, _T("Synchronize"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer12->Add(btnCalcSend, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnUpload = new wxButton(this, ID_BUTTON2, _T("Upload"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	btnUpload->Hide();
	FlexGridSizer12->Add(btnUpload, 1, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer6->Add(FlexGridSizer12, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11->Add(StaticBoxSizer6, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	FlexGridSizer2->Add(FlexGridSizer11, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer8 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Si5351C"));
	FlexGridSizer18 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer19 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer20 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText20 = new wxStaticText(this, ID_STATICTEXT22, _T("CLKIN Frequency (MHz):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
	FlexGridSizer20->Add(StaticText20, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtCLKIN_MHz = new wxTextCtrl(this, ID_TEXTCTRL3, _T("30.72"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer20->Add(txtCLKIN_MHz, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer19->Add(FlexGridSizer20, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer18->Add(FlexGridSizer19, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer21 = new wxFlexGridSizer(0, 5, 0, 0);
	FlexGridSizer22 = new wxFlexGridSizer(0, 4, 0, 0);
	StaticText21 = new wxStaticText(this, ID_STATICTEXT23, _T("Pin Name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
	FlexGridSizer22->Add(StaticText21, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText22 = new wxStaticText(this, ID_STATICTEXT24, _T("Enable channel"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
	FlexGridSizer22->Add(StaticText22, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText23 = new wxStaticText(this, ID_STATICTEXT25, _T("Output frequency (MHz)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
	FlexGridSizer22->Add(StaticText23, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText24 = new wxStaticText(this, ID_STATICTEXT26, _T("Invert output"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
	FlexGridSizer22->Add(StaticText24, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblCLK0 = new wxStaticText(this, ID_STATICTEXT27, _T("SynthCLK1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
	FlexGridSizer22->Add(lblCLK0, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK0 = new wxCheckBox(this, ID_CHECKBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkEN_CLK0->SetValue(true);
	FlexGridSizer22->Add(chkEN_CLK0, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK0 = new wxTextCtrl(this, ID_TEXTCTRL4, _T("27.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	FlexGridSizer22->Add(txtFreq_CLK0, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK0 = new wxCheckBox(this, ID_CHECKBOX9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	chkInvert_CLK0->SetValue(false);
	FlexGridSizer22->Add(chkInvert_CLK0, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblCLK1 = new wxStaticText(this, ID_STATICTEXT28, _T("CLK1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
	FlexGridSizer22->Add(lblCLK1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK1 = new wxCheckBox(this, ID_CHECKBOX2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkEN_CLK1->SetValue(false);
	FlexGridSizer22->Add(chkEN_CLK1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK1 = new wxTextCtrl(this, ID_TEXTCTRL5, _T("27.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	FlexGridSizer22->Add(txtFreq_CLK1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK1 = new wxCheckBox(this, ID_CHECKBOX10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	chkInvert_CLK1->SetValue(false);
	FlexGridSizer22->Add(chkInvert_CLK1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblCLK2 = new wxStaticText(this, ID_STATICTEXT29, _T("SynthCLK2"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
	FlexGridSizer22->Add(lblCLK2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK2 = new wxCheckBox(this, ID_CHECKBOX3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkEN_CLK2->SetValue(true);
	FlexGridSizer22->Add(chkEN_CLK2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK2 = new wxTextCtrl(this, ID_TEXTCTRL6, _T("27.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
	FlexGridSizer22->Add(txtFreq_CLK2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK2 = new wxCheckBox(this, ID_CHECKBOX11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	chkInvert_CLK2->SetValue(false);
	FlexGridSizer22->Add(chkInvert_CLK2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblCLK3 = new wxStaticText(this, ID_STATICTEXT30, _T("CLK3"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
	FlexGridSizer22->Add(lblCLK3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK3 = new wxCheckBox(this, ID_CHECKBOX4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkEN_CLK3->SetValue(false);
	FlexGridSizer22->Add(chkEN_CLK3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK3 = new wxTextCtrl(this, ID_TEXTCTRL7, _T("27.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
	FlexGridSizer22->Add(txtFreq_CLK3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK3 = new wxCheckBox(this, ID_CHECKBOX12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	chkInvert_CLK3->SetValue(false);
	FlexGridSizer22->Add(chkInvert_CLK3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblCLK4 = new wxStaticText(this, ID_STATICTEXT31, _T("TxPLL_CLK"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
	FlexGridSizer22->Add(lblCLK4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK4 = new wxCheckBox(this, ID_CHECKBOX5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkEN_CLK4->SetValue(true);
	FlexGridSizer22->Add(chkEN_CLK4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK4 = new wxTextCtrl(this, ID_TEXTCTRL8, _T("27.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
	FlexGridSizer22->Add(txtFreq_CLK4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK4 = new wxCheckBox(this, ID_CHECKBOX13, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	chkInvert_CLK4->SetValue(false);
	FlexGridSizer22->Add(chkInvert_CLK4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblCLK5 = new wxStaticText(this, ID_STATICTEXT32, _T("CLK5"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
	FlexGridSizer22->Add(lblCLK5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK5 = new wxCheckBox(this, ID_CHECKBOX6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chkEN_CLK5->SetValue(false);
	FlexGridSizer22->Add(chkEN_CLK5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK5 = new wxTextCtrl(this, ID_TEXTCTRL9, _T("27.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
	FlexGridSizer22->Add(txtFreq_CLK5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK5 = new wxCheckBox(this, ID_CHECKBOX14, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	chkInvert_CLK5->SetValue(false);
	FlexGridSizer22->Add(chkInvert_CLK5, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblCLK6 = new wxStaticText(this, ID_STATICTEXT33, _T("RxPLL_CLK"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
	FlexGridSizer22->Add(lblCLK6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK6 = new wxCheckBox(this, ID_CHECKBOX7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chkEN_CLK6->SetValue(true);
	FlexGridSizer22->Add(chkEN_CLK6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK6 = new wxTextCtrl(this, ID_TEXTCTRL10, _T("27.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL10"));
	FlexGridSizer22->Add(txtFreq_CLK6, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK6 = new wxCheckBox(this, ID_CHECKBOX15, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
	chkInvert_CLK6->SetValue(false);
	FlexGridSizer22->Add(chkInvert_CLK6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblCLK7 = new wxStaticText(this, ID_STATICTEXT34, _T("CLK7"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT34"));
	FlexGridSizer22->Add(lblCLK7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	chkEN_CLK7 = new wxCheckBox(this, ID_CHECKBOX8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chkEN_CLK7->SetValue(false);
	FlexGridSizer22->Add(chkEN_CLK7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtFreq_CLK7 = new wxTextCtrl(this, ID_TEXTCTRL11, _T("27.0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL11"));
	FlexGridSizer22->Add(txtFreq_CLK7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkInvert_CLK7 = new wxCheckBox(this, ID_CHECKBOX16, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
	chkInvert_CLK7->SetValue(false);
	FlexGridSizer22->Add(chkInvert_CLK7, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer21->Add(FlexGridSizer22, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnConfigure = new wxButton(this, ID_BUTTON5, _T("Configure Clocks"), wxDefaultPosition, wxSize(113,61), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer21->Add(btnConfigure, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer18->Add(FlexGridSizer21, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer8->Add(FlexGridSizer18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer8, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlBoard::OnbtnSynchronizeClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlBoard::OnbtnSynchronizeClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlBoard::OnbtnConfigureClockClick);
	//*)
	sizerFunctionLatch->Show(false);
	sizerInitializationLatch->Show(false);
	sizerReferenceCounterLatch->Show(false);
	Layout();
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
}

pnlBoard::~pnlBoard()
{
	//(*Destroy(pnlBoard)
	//*)
}

void pnlBoard::Initialize(Si5351C* pSi5351C, ADF_module* pADF)
{
    m_pSi5351C = pSi5351C;
    m_pADF = pADF;
}

void pnlBoard::OnbtnConfigureClockClick(wxCommandEvent& event)
{
    double refFreq;
    double freq;
    if(m_pSi5351C == NULL)
    {
        printf("pnlBoard: Si5351C not initialized\n");
        return;
    }
    txtCLKIN_MHz->GetValue().ToDouble(&refFreq);
    m_pSi5351C->SetPLL(0, refFreq*1000000);
    m_pSi5351C->SetPLL(1, refFreq*1000000);

    txtFreq_CLK0->GetValue().ToDouble(&freq);
    m_pSi5351C->SetClock(0, freq*1000000, chkEN_CLK0->GetValue(), chkInvert_CLK0->GetValue());
    txtFreq_CLK1->GetValue().ToDouble(&freq);
    m_pSi5351C->SetClock(1, freq*1000000, chkEN_CLK1->GetValue(), chkInvert_CLK1->GetValue());
    txtFreq_CLK2->GetValue().ToDouble(&freq);
    m_pSi5351C->SetClock(2, freq*1000000, chkEN_CLK2->GetValue(), chkInvert_CLK2->GetValue());
    txtFreq_CLK3->GetValue().ToDouble(&freq);
    m_pSi5351C->SetClock(3, freq*1000000, chkEN_CLK3->GetValue(), chkInvert_CLK3->GetValue());
    txtFreq_CLK4->GetValue().ToDouble(&freq);
    m_pSi5351C->SetClock(4, freq*1000000, chkEN_CLK4->GetValue(), chkInvert_CLK4->GetValue());
    txtFreq_CLK5->GetValue().ToDouble(&freq);
    m_pSi5351C->SetClock(5, freq*1000000, chkEN_CLK5->GetValue(), chkInvert_CLK5->GetValue());
    txtFreq_CLK6->GetValue().ToDouble(&freq);
    m_pSi5351C->SetClock(6, freq*1000000, chkEN_CLK6->GetValue(), chkInvert_CLK6->GetValue());
    txtFreq_CLK7->GetValue().ToDouble(&freq);
    m_pSi5351C->SetClock(7, freq*1000000, chkEN_CLK7->GetValue(), chkInvert_CLK7->GetValue());

    if( m_pSi5351C->ConfigureClocks() )
        m_pSi5351C->UploadConfiguration();
}

void pnlBoard::OnbtnSynchronizeClick(wxCommandEvent& event)
{
    if(m_pADF == NULL)
    {
        printf("pnlBoard: ADF not initialized\n");
        return;
    }
    //reference counter latch
    int ldp = cmbLDP->GetSelection();
    int abw = cmbABW->GetSelection();
    int rCount = spinRCnt->GetValue();
    m_pADF->SetReferenceCounterLatch(ldp, abw, rCount);

    //n counter latch
    int cpGain = cmbCPG->GetSelection();
    int nCounter = spinNCnt->GetValue();
    m_pADF->SetNCounterLatch(cpGain, nCounter);

    //function latch
    int currSetting1 = cmbCS1_f->GetSelection();
    int currSetting2 = cmbCS2_f->GetSelection();
    int tCounter = cmbTC_f->GetSelection();
    int fastLock = cmbFL_f->GetSelection();
    int muxControl = cmbMOC_f->GetSelection();

    int pdPol = rgrPDP_f->GetSelection();
    int pd1 = rgrPD1_f->GetSelection();
    int pd2 = rgrPD2_f->GetSelection();
    int counterReset = rgrCR_f->GetSelection();
    int cpState = rgrCPS_f->GetSelection();
    m_pADF->SetFunctionLatch(currSetting1, currSetting2, tCounter, fastLock, muxControl);
    m_pADF->SetFunctionLatchRgr(pdPol, pd1,pd2, counterReset, cpState);

    //Initialization latch
    currSetting1 = cmbCS1_i->GetSelection();
    currSetting2 = cmbCS2_i->GetSelection();
    tCounter = cmbTC_i->GetSelection();
    fastLock = cmbFL_i->GetSelection();
    muxControl = cmbMOC_i->GetSelection();

    pdPol = rgrPDP_i->GetSelection();
    pd1 = rgrPD1_i->GetSelection();
    pd2 = rgrPD2_i->GetSelection();
    counterReset = rgrCR_i->GetSelection();
    cpState = rgrCPS_i->GetSelection();
    m_pADF->SetInitializationLatch(currSetting1, currSetting2, tCounter, fastLock, muxControl);
    m_pADF->SetInitializationLatchRgr(pdPol, pd1,pd2, counterReset, cpState);

    double fref = 0;
    txtFref->GetValue().ToDouble(&fref);

    double fvco = 0;
    txtFvco->GetValue().ToDouble(&fvco);
    m_pADF->SetFrefFvco(fref, fvco, rCount, nCounter);
    spinNCnt->SetValue(nCounter);
    spinRCnt->SetValue(rCount);

    lblFcomp->SetLabel( wxString::Format("%f", m_pADF->lblFcomp));
    lblFvco->SetLabel( wxString::Format("%f", m_pADF->lblFvco));

    m_pADF->SendConfig();
}

void pnlBoard::ModifyClocksGUI(eLMS_DEV board)
{
    for(int i=0; i<8; ++i)
        ClockEnable(i, true);
    if(board == LMS_DEV_STREAM)
    {
        lblCLK0->SetLabel(_("CLK0 - CLK_IN"));
        lblCLK1->SetLabel(_("CLK1"));
        ClockEnable(1, false);
        lblCLK2->SetLabel(_("CLK2 - FCLK2"));
        lblCLK3->SetLabel(_("CLK3"));
        ClockEnable(3, false);
        lblCLK4->SetLabel(_("CLK4 - FCLK1"));
        lblCLK5->SetLabel(_("CLK5"));
        ClockEnable(5, false);
        lblCLK6->SetLabel(_("CLK6 - CLK_FPGA0"));
        lblCLK7->SetLabel(_("CLK7 - CLK_FPGA1"));
    }
    else
    {
        lblCLK0->SetLabel(_("CLK0 - PLL CLK"));
        lblCLK1->SetLabel(_("CLK1"));
        ClockEnable(1, false);
        lblCLK2->SetLabel(_("CLK2 - RxCLK"));
        ClockEnable(2, false);
        lblCLK3->SetLabel(_("CLK3 - RxCLK_C"));
        lblCLK4->SetLabel(_("CLK4 - TxCLK"));
        lblCLK5->SetLabel(_("CLK5 - TxCLK_C"));
        lblCLK6->SetLabel(_("CLK6"));
        ClockEnable(6, false);
        lblCLK7->SetLabel(_("CLK7"));
        ClockEnable(7, false);
    }
}

void pnlBoard::ClockEnable(unsigned int i, bool enabled)
{
    switch(i)
    {
    case 0:
        lblCLK0->Enable(enabled);
        chkEN_CLK0->Enable(enabled);
        txtFreq_CLK0->Enable(enabled);
        chkInvert_CLK0->Enable(enabled);
        break;
    case 1:
        lblCLK1->Enable(enabled);
        chkEN_CLK1->Enable(enabled);
        txtFreq_CLK1->Enable(enabled);
        chkInvert_CLK1->Enable(enabled);
        break;
    case 2:
        lblCLK2->Enable(enabled);
        chkEN_CLK2->Enable(enabled);
        txtFreq_CLK2->Enable(enabled);
        chkInvert_CLK2->Enable(enabled);
        break;
    case 3:
        lblCLK3->Enable(enabled);
        chkEN_CLK3->Enable(enabled);
        txtFreq_CLK3->Enable(enabled);
        chkInvert_CLK3->Enable(enabled);
        break;
    case 4:
        lblCLK4->Enable(enabled);
        chkEN_CLK4->Enable(enabled);
        txtFreq_CLK4->Enable(enabled);
        chkInvert_CLK4->Enable(enabled);
        break;
    case 5:
        lblCLK5->Enable(enabled);
        chkEN_CLK5->Enable(enabled);
        txtFreq_CLK5->Enable(enabled);
        chkInvert_CLK5->Enable(enabled);
        break;
    case 6:
        lblCLK6->Enable(enabled);
        chkEN_CLK6->Enable(enabled);
        txtFreq_CLK6->Enable(enabled);
        chkInvert_CLK6->Enable(enabled);
        break;
    case 7:
        lblCLK7->Enable(enabled);
        chkEN_CLK7->Enable(enabled);
        txtFreq_CLK7->Enable(enabled);
        chkInvert_CLK7->Enable(enabled);
        break;
    default:
        break;
    }
}
