/**
@file	pnlSPI.cpp
@author	Lime Microsystems
@brief	panel for direct data writing and reading to SPI
*/

#include "pnlSPI.h"
#include "../CommonUtilities.h"
#include "LMS7002_MainControl.h"
#include "ConnectionManager.h"
#include "RegistersMap.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <wx/filedlg.h>

extern unsigned char bestOfThree(const unsigned char A, const unsigned char B, const unsigned char C);

//(*InternalHeaders(pnlSPI)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(pnlSPI)
const long pnlSPI::ID_STATICTEXT1 = wxNewId();
const long pnlSPI::ID_TEXTCTRL1 = wxNewId();
const long pnlSPI::ID_STATICTEXT9 = wxNewId();
const long pnlSPI::ID_TEXTCTRL3 = wxNewId();
const long pnlSPI::ID_BUTTON1 = wxNewId();
const long pnlSPI::ID_STATICTEXT5 = wxNewId();
const long pnlSPI::ID_STATICTEXT6 = wxNewId();
const long pnlSPI::ID_STATICTEXT2 = wxNewId();
const long pnlSPI::ID_TEXTCTRL2 = wxNewId();
const long pnlSPI::ID_BUTTON2 = wxNewId();
const long pnlSPI::ID_STATICTEXT3 = wxNewId();
const long pnlSPI::ID_STATICTEXT4 = wxNewId();
const long pnlSPI::ID_STATICTEXT7 = wxNewId();
const long pnlSPI::ID_STATICTEXT8 = wxNewId();
const long pnlSPI::ID_BUTTON21 = wxNewId();
const long pnlSPI::ID_STATICTEXT13 = wxNewId();
const long pnlSPI::ID_SPINCTRL1 = wxNewId();
const long pnlSPI::ID_CHECKBOX3 = wxNewId();
const long pnlSPI::ID_BUTTON22 = wxNewId();
const long pnlSPI::ID_CHECKBOX4 = wxNewId();
const long pnlSPI::ID_BUTTON23 = wxNewId();
const long pnlSPI::ID_CHECKBOX5 = wxNewId();
const long pnlSPI::ID_RADIOBOX1 = wxNewId();
const long pnlSPI::ID_STATICTEXT14 = wxNewId();
const long pnlSPI::ID_STATICTEXT10 = wxNewId();
const long pnlSPI::ID_TEXTCTRL4 = wxNewId();
const long pnlSPI::ID_CHECKBOX1 = wxNewId();
const long pnlSPI::ID_CHECKBOX2 = wxNewId();
const long pnlSPI::ID_STATICTEXT11 = wxNewId();
const long pnlSPI::ID_TEXTCTRL5 = wxNewId();
const long pnlSPI::ID_STATICTEXT12 = wxNewId();
const long pnlSPI::ID_TEXTCTRL6 = wxNewId();
const long pnlSPI::ID_BUTTON20 = wxNewId();
const long pnlSPI::ID_BUTTON3 = wxNewId();
const long pnlSPI::ID_BUTTON4 = wxNewId();
const long pnlSPI::ID_BUTTON5 = wxNewId();
const long pnlSPI::ID_BUTTON6 = wxNewId();
const long pnlSPI::ID_BUTTON7 = wxNewId();
const long pnlSPI::ID_BUTTON8 = wxNewId();
const long pnlSPI::ID_BUTTON9 = wxNewId();
const long pnlSPI::ID_BUTTON19 = wxNewId();
const long pnlSPI::ID_BUTTON10 = wxNewId();
const long pnlSPI::ID_BUTTON11 = wxNewId();
const long pnlSPI::ID_BUTTON12 = wxNewId();
const long pnlSPI::ID_BUTTON13 = wxNewId();
const long pnlSPI::ID_BUTTON14 = wxNewId();
const long pnlSPI::ID_BUTTON15 = wxNewId();
const long pnlSPI::ID_BUTTON16 = wxNewId();
const long pnlSPI::ID_BUTTON17 = wxNewId();
const long pnlSPI::ID_BUTTON18 = wxNewId();
const long pnlSPI::ID_RICHTEXTCTRL1 = wxNewId();
const long pnlSPI::ID_STATICTEXT15 = wxNewId();
const long pnlSPI::ID_TEXTCTRL7 = wxNewId();
const long pnlSPI::ID_STATICTEXT16 = wxNewId();
const long pnlSPI::ID_TEXTCTRL8 = wxNewId();
const long pnlSPI::ID_BUTTON24 = wxNewId();
const long pnlSPI::ID_STATICTEXT17 = wxNewId();
const long pnlSPI::ID_STATICTEXT18 = wxNewId();
const long pnlSPI::ID_STATICTEXT19 = wxNewId();
const long pnlSPI::ID_TEXTCTRL9 = wxNewId();
const long pnlSPI::ID_BUTTON25 = wxNewId();
const long pnlSPI::ID_STATICTEXT20 = wxNewId();
const long pnlSPI::ID_STATICTEXT21 = wxNewId();
const long pnlSPI::ID_STATICTEXT22 = wxNewId();
const long pnlSPI::ID_STATICTEXT23 = wxNewId();
const long pnlSPI::ID_STATICTEXT24 = wxNewId();
const long pnlSPI::ID_TEXTCTRL10 = wxNewId();
const long pnlSPI::ID_STATICTEXT25 = wxNewId();
const long pnlSPI::ID_TEXTCTRL11 = wxNewId();
const long pnlSPI::ID_BUTTON26 = wxNewId();
const long pnlSPI::ID_STATICTEXT26 = wxNewId();
const long pnlSPI::ID_STATICTEXT27 = wxNewId();
const long pnlSPI::ID_STATICTEXT28 = wxNewId();
const long pnlSPI::ID_TEXTCTRL12 = wxNewId();
const long pnlSPI::ID_BUTTON27 = wxNewId();
const long pnlSPI::ID_STATICTEXT29 = wxNewId();
const long pnlSPI::ID_STATICTEXT30 = wxNewId();
const long pnlSPI::ID_STATICTEXT31 = wxNewId();
const long pnlSPI::ID_STATICTEXT32 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlSPI,wxPanel)
    //(*EventTable(pnlSPI)
    //*)
END_EVENT_TABLE()

pnlSPI::pnlSPI(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    m_serPort = NULL;
    BuildContent(parent, id);
}

void pnlSPI::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    m_serPort = lmsControl->getSerPort();
}

void pnlSPI::BuildContent(wxWindow* parent, wxWindowID id)
{
    //(*Initialize(pnlSPI)
    wxStaticBoxSizer* StaticBoxSizer2;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer16;
    wxFlexGridSizer* FlexGridSizer19;
    wxStaticBoxSizer* StaticBoxSizer12;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxStaticBoxSizer* StaticBoxSizer9;
    wxFlexGridSizer* FlexGridSizer7;
    wxStaticBoxSizer* StaticBoxSizer7;
    wxStaticBoxSizer* StaticBoxSizer13;
    wxStaticBoxSizer* StaticBoxSizer10;
    wxStaticBoxSizer* StaticBoxSizer8;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer6;
    wxFlexGridSizer* FlexGridSizer15;
    wxFlexGridSizer* FlexGridSizer18;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer21;
    wxFlexGridSizer* FlexGridSizer14;
    wxStaticBoxSizer* StaticBoxSizer11;
    wxFlexGridSizer* FlexGridSizer20;
    wxFlexGridSizer* FlexGridSizer13;
    wxFlexGridSizer* FlexGridSizer12;
    wxFlexGridSizer* FlexGridSizer6;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer11;
    wxFlexGridSizer* FlexGridSizer17;
    wxStaticBoxSizer* StaticBoxSizer5;

    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("LMS Write"));
    FlexGridSizer2 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWriteAddr = new wxTextCtrl(this, ID_TEXTCTRL1, _("FFFF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer2->Add(txtWriteAddr, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT9, _("Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    FlexGridSizer2->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWvalue = new wxTextCtrl(this, ID_TEXTCTRL3, _("FFFF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    FlexGridSizer2->Add(txtWvalue, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnWrite = new wxButton(this, ID_BUTTON1, _("CMD Write"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer2->Add(btnWrite, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer2->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lblWstatus = new wxStaticText(this, ID_STATICTEXT6, _("\?\?\?"), wxDefaultPosition, wxSize(134,13), 0, _T("ID_STATICTEXT6"));
    FlexGridSizer2->Add(lblWstatus, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer1, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("LMS Read"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtReadAddr = new wxTextCtrl(this, ID_TEXTCTRL2, _("FFFF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    FlexGridSizer3->Add(txtReadAddr, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnRead = new wxButton(this, ID_BUTTON2, _("CMD Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer3->Add(btnRead, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Read Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer4->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblReadVal = new wxStaticText(this, ID_STATICTEXT4, _("\?\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer4->Add(lblReadVal, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT7, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer4->Add(StaticText6, 1, wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblRstatus = new wxStaticText(this, ID_STATICTEXT8, _("\?\?\?"), wxDefaultPosition, wxSize(143,13), 0, _T("ID_STATICTEXT8"));
    FlexGridSizer4->Add(lblRstatus, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer4, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer13 = new wxFlexGridSizer(0, 4, 0, 0);
    btnBatchRead = new wxButton(this, ID_BUTTON21, _("Batch Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON21"));
    btnBatchRead->SetToolTip(_("Reads given register address for number of times set in ReadCount"));
    FlexGridSizer13->Add(btnBatchRead, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText10 = new wxStaticText(this, ID_STATICTEXT13, _("ReadCount:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    FlexGridSizer13->Add(StaticText10, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    spinBatchCount = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxSize(48,-1), 0, 0, 2000, 0, _T("ID_SPINCTRL1"));
    spinBatchCount->SetValue(_T("0"));
    FlexGridSizer13->Add(spinBatchCount, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkSaveToFileBatch = new wxCheckBox(this, ID_CHECKBOX3, _("Save to file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    chkSaveToFileBatch->SetValue(false);
    FlexGridSizer13->Add(chkSaveToFileBatch, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    btnWrTester = new wxButton(this, ID_BUTTON22, _("Write Tester"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON22"));
    btnWrTester->SetToolTip(_("Performs write operation given in Write section, and reads back the same address to check if data matches, this operation is repeated for 100 iterations"));
    FlexGridSizer13->Add(btnWrTester, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    chkTripleCheck = new wxCheckBox(this, ID_CHECKBOX4, _("Triple check data"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    chkTripleCheck->SetValue(false);
    chkTripleCheck->SetToolTip(_("When reading, reads the same register three times and uses the most frequent value"));
    FlexGridSizer13->Add(chkTripleCheck, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    btnPurgeCOM = new wxButton(this, ID_BUTTON23, _("PurgeCOM"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON23"));
    btnPurgeCOM->Hide();
    FlexGridSizer13->Add(btnPurgeCOM, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    chkTestWrittenData = new wxCheckBox(this, ID_CHECKBOX5, _("Test written data"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    chkTestWrittenData->SetValue(false);
    chkTestWrittenData->Hide();
    chkTestWrittenData->SetToolTip(_("After writing register, reads back the same register and checks if values match"));
    FlexGridSizer13->Add(chkTestWrittenData, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer13, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer2->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer2, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer14 = new wxFlexGridSizer(0, 3, 0, 0);
    wxString __wxRadioBoxChoices_1[3] =
    {
    	_("A/SXR"),
    	_("B/SXT"),
    	_("Both")
    };
    rgrChannelSelect = new wxRadioBox(this, ID_RADIOBOX1, _("Switch channel"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_1, 3, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
    rgrChannelSelect->SetSelection(2);
    FlexGridSizer14->Add(rgrChannelSelect, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText11 = new wxStaticText(this, ID_STATICTEXT14, _("This switch writes static values(0xFFFD, 0xFFFE, 0xFFFF) to 0x0020 register. It is not synchronized with the rest of control logic"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    FlexGridSizer14->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer14, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    sizerRegistersTest = new wxFlexGridSizer(0, 3, 0, 0);
    groupBoxRegistersTest = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Registers Test"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer7 = new wxFlexGridSizer(0, 9, 0, 0);
    StaticText7 = new wxStaticText(this, ID_STATICTEXT10, _("Test data(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    FlexGridSizer7->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtHexInput = new wxTextCtrl(this, ID_TEXTCTRL4, _("FFFF"), wxDefaultPosition, wxSize(69,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    FlexGridSizer7->Add(txtHexInput, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer12 = new wxFlexGridSizer(0, 1, 0, 0);
    chkBatchWR = new wxCheckBox(this, ID_CHECKBOX1, _("batch writing and reading"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    chkBatchWR->SetValue(true);
    chkBatchWR->SetToolTip(_("when enabled all register values are written together then all values read together.\nwhen disabled each register is written and then read separately."));
    FlexGridSizer12->Add(chkBatchWR, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    chkSaveToFile = new wxCheckBox(this, ID_CHECKBOX2, _("Save to file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    chkSaveToFile->SetValue(true);
    FlexGridSizer12->Add(chkSaveToFile, 1, wxTOP|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer7->Add(FlexGridSizer12, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7->Add(64,20,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(this, ID_STATICTEXT11, _("start addr(hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    FlexGridSizer7->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtStartAddr = new wxTextCtrl(this, ID_TEXTCTRL5, _("0000"), wxDefaultPosition, wxSize(58,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    FlexGridSizer7->Add(txtStartAddr, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(this, ID_STATICTEXT12, _("end addr(hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    FlexGridSizer7->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtEndAddr = new wxTextCtrl(this, ID_TEXTCTRL6, _("0000"), wxDefaultPosition, wxSize(58,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    FlexGridSizer7->Add(txtEndAddr, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestInterval = new wxButton(this, ID_BUTTON20, _("Test Interval"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON20"));
    FlexGridSizer7->Add(btnTestInterval, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(FlexGridSizer7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer9 = new wxFlexGridSizer(0, 5, 0, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Top"));
    FlexGridSizer8 = new wxFlexGridSizer(0, 2, 5, 5);
    btnTestLimeLight = new wxButton(this, ID_BUTTON3, _("Lime Light"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer8->Add(btnTestLimeLight, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestAFE = new wxButton(this, ID_BUTTON4, _("AFE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer8->Add(btnTestAFE, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestBIAS = new wxButton(this, ID_BUTTON5, _("BIAS"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    FlexGridSizer8->Add(btnTestBIAS, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestXBUF = new wxButton(this, ID_BUTTON6, _("XBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    FlexGridSizer8->Add(btnTestXBUF, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestCGEN = new wxButton(this, ID_BUTTON7, _("CGEN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    FlexGridSizer8->Add(btnTestCGEN, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestLDO = new wxButton(this, ID_BUTTON8, _("LDO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
    FlexGridSizer8->Add(btnTestLDO, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestBIST = new wxButton(this, ID_BUTTON9, _("BIST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
    FlexGridSizer8->Add(btnTestBIST, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestCDS = new wxButton(this, ID_BUTTON19, _("CDS"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON19"));
    FlexGridSizer8->Add(btnTestCDS, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer4->Add(FlexGridSizer8, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9->Add(StaticBoxSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("TRX"));
    FlexGridSizer10 = new wxFlexGridSizer(0, 2, 5, 5);
    btnTestTRF = new wxButton(this, ID_BUTTON10, _("TRF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
    FlexGridSizer10->Add(btnTestTRF, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestTBB = new wxButton(this, ID_BUTTON11, _("TBB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    FlexGridSizer10->Add(btnTestTBB, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestRFE = new wxButton(this, ID_BUTTON12, _("RFE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
    FlexGridSizer10->Add(btnTestRFE, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestRBB = new wxButton(this, ID_BUTTON13, _("RBB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON13"));
    FlexGridSizer10->Add(btnTestRBB, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestSXRSXT = new wxButton(this, ID_BUTTON14, _("SXR/SXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON14"));
    FlexGridSizer10->Add(btnTestSXRSXT, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer5->Add(FlexGridSizer10, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9->Add(StaticBoxSizer5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, this, _("Tx"));
    btnTestTxTSP = new wxButton(this, ID_BUTTON15, _("TxTSP"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON15"));
    StaticBoxSizer6->Add(btnTestTxTSP, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestTxNCO = new wxButton(this, ID_BUTTON16, _("TxNCO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON16"));
    StaticBoxSizer6->Add(btnTestTxNCO, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9->Add(StaticBoxSizer6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer7 = new wxStaticBoxSizer(wxVERTICAL, this, _("Rx"));
    btnTestRxTSP = new wxButton(this, ID_BUTTON17, _("RxTSP"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON17"));
    StaticBoxSizer7->Add(btnTestRxTSP, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTestRxNCO = new wxButton(this, ID_BUTTON18, _("RxNCO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON18"));
    StaticBoxSizer7->Add(btnTestRxNCO, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9->Add(StaticBoxSizer7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer11 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticBoxSizer8 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Register test status"));
    txtTestText = new wxRichTextCtrl(this, ID_RICHTEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(300,142), wxRE_MULTILINE|wxRE_READONLY, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
    wxRichTextAttr rchtxtAttr_1;
    rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
    StaticBoxSizer8->Add(txtTestText, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer11->Add(StaticBoxSizer8, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer9->Add(FlexGridSizer11, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer6->Add(FlexGridSizer9, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    groupBoxRegistersTest->Add(FlexGridSizer6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    sizerRegistersTest->Add(groupBoxRegistersTest, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(sizerRegistersTest, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Board SPI"));
    FlexGridSizer5 = new wxFlexGridSizer(0, 1, 5, 0);
    StaticBoxSizer9 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Write"));
    FlexGridSizer15 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText12 = new wxStaticText(this, ID_STATICTEXT15, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    FlexGridSizer15->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWriteAddrBrd = new wxTextCtrl(this, ID_TEXTCTRL7, _("FFFF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    FlexGridSizer15->Add(txtWriteAddrBrd, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText13 = new wxStaticText(this, ID_STATICTEXT16, _("Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
    FlexGridSizer15->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWvalueBrd = new wxTextCtrl(this, ID_TEXTCTRL8, _("FFFF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    FlexGridSizer15->Add(txtWvalueBrd, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnWriteBrd = new wxButton(this, ID_BUTTON24, _("CMD Write"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON24"));
    FlexGridSizer15->Add(btnWriteBrd, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText14 = new wxStaticText(this, ID_STATICTEXT17, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
    FlexGridSizer15->Add(StaticText14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lblWstatusBrd = new wxStaticText(this, ID_STATICTEXT18, _("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT18"));
    FlexGridSizer15->Add(lblWstatusBrd, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer9->Add(FlexGridSizer15, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer5->Add(StaticBoxSizer9, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer10 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Read"));
    FlexGridSizer16 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText15 = new wxStaticText(this, ID_STATICTEXT19, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
    FlexGridSizer16->Add(StaticText15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtReadAddrBrd = new wxTextCtrl(this, ID_TEXTCTRL9, _("FFFF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
    FlexGridSizer16->Add(txtReadAddrBrd, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnReadBrd = new wxButton(this, ID_BUTTON25, _("CMD Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON25"));
    FlexGridSizer16->Add(btnReadBrd, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer17 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText16 = new wxStaticText(this, ID_STATICTEXT20, _("Read Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
    FlexGridSizer17->Add(StaticText16, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblReadValBrd = new wxStaticText(this, ID_STATICTEXT21, _("\?\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
    FlexGridSizer17->Add(lblReadValBrd, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText17 = new wxStaticText(this, ID_STATICTEXT22, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
    FlexGridSizer17->Add(StaticText17, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblRstatusBrd = new wxStaticText(this, ID_STATICTEXT23, _("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT23"));
    FlexGridSizer17->Add(lblRstatusBrd, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer16->Add(FlexGridSizer17, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer10->Add(FlexGridSizer16, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer5->Add(StaticBoxSizer10, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer3->Add(FlexGridSizer5, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer1->Add(StaticBoxSizer3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer11 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("I2C TFP410"));
    FlexGridSizer18 = new wxFlexGridSizer(0, 1, 5, 0);
    StaticBoxSizer12 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Write"));
    FlexGridSizer19 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText18 = new wxStaticText(this, ID_STATICTEXT24, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
    FlexGridSizer19->Add(StaticText18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWriteAddrI2C = new wxTextCtrl(this, ID_TEXTCTRL10, _("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL10"));
    FlexGridSizer19->Add(txtWriteAddrI2C, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText19 = new wxStaticText(this, ID_STATICTEXT25, _("Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
    FlexGridSizer19->Add(StaticText19, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtWvalueI2C = new wxTextCtrl(this, ID_TEXTCTRL11, _("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL11"));
    FlexGridSizer19->Add(txtWvalueI2C, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnWriteI2C = new wxButton(this, ID_BUTTON26, _("CMD Write"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON26"));
    FlexGridSizer19->Add(btnWriteI2C, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText20 = new wxStaticText(this, ID_STATICTEXT26, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
    FlexGridSizer19->Add(StaticText20, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lblWstatusI2C = new wxStaticText(this, ID_STATICTEXT27, _("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT27"));
    FlexGridSizer19->Add(lblWstatusI2C, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer12->Add(FlexGridSizer19, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer18->Add(StaticBoxSizer12, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer13 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Read"));
    FlexGridSizer20 = new wxFlexGridSizer(0, 7, 0, 0);
    StaticText22 = new wxStaticText(this, ID_STATICTEXT28, _("Address(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
    FlexGridSizer20->Add(StaticText22, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtReadAddrI2C = new wxTextCtrl(this, ID_TEXTCTRL12, _("FF"), wxDefaultPosition, wxSize(48,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL12"));
    FlexGridSizer20->Add(txtReadAddrI2C, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnReadI2C = new wxButton(this, ID_BUTTON27, _("CMD Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON27"));
    FlexGridSizer20->Add(btnReadI2C, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer21 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText23 = new wxStaticText(this, ID_STATICTEXT29, _("Read Value(Hex):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
    FlexGridSizer21->Add(StaticText23, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblReadValI2C = new wxStaticText(this, ID_STATICTEXT30, _("\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
    FlexGridSizer21->Add(lblReadValI2C, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText25 = new wxStaticText(this, ID_STATICTEXT31, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
    FlexGridSizer21->Add(StaticText25, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    lblRstatusI2C = new wxStaticText(this, ID_STATICTEXT32, _("\?\?\?"), wxDefaultPosition, wxSize(100,-1), 0, _T("ID_STATICTEXT32"));
    FlexGridSizer21->Add(lblRstatusI2C, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer20->Add(FlexGridSizer21, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer13->Add(FlexGridSizer20, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer18->Add(StaticBoxSizer13, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    StaticBoxSizer11->Add(FlexGridSizer18, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer1->Add(StaticBoxSizer11, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnWriteClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnReadClick);
    Connect(ID_BUTTON21,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnBatchReadClick);
    Connect(ID_BUTTON22,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnWrTesterClick);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSPI::OnchkTripleCheckClick);
    Connect(ID_BUTTON23,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnPurgeCOMClick);
    Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSPI::OnchkTestWrittenDataClick);
    Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlSPI::OnrgrChannelSelectSelect);
    Connect(ID_BUTTON20,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestIntervalClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestLimeLightClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestAFEClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestBIASClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestXBUFClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestCGENClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestLDOClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestBISTClick);
    Connect(ID_BUTTON19,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestCDSClick);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestTRFClick);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestTBBClick);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestRFEClick);
    Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestRBBClick);
    Connect(ID_BUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestSXRSXTClick);
    Connect(ID_BUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestTxTSPClick);
    Connect(ID_BUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestTxNCOClick);
    Connect(ID_BUTTON17,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestRxTSPClick);
    Connect(ID_BUTTON18,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnTestRxNCOClick);
    Connect(ID_BUTTON24,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnWriteBrdClick);
    Connect(ID_BUTTON25,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnReadBrdClick);
    Connect(ID_BUTTON26,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnWriteI2CClick);
    Connect(ID_BUTTON27,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSPI::OnbtnReadI2CClick);
    //*)
#ifndef ENABLE_TESTING_UTILITIES
    sizerRegistersTest->Hide(groupBoxRegistersTest);
#endif
}

pnlSPI::~pnlSPI()
{
    //(*Destroy(pnlSPI)
    //*)
}


void pnlSPI::OnbtnWriteClick(wxCommandEvent& event)
{
    unsigned char outbuffer[64];
    unsigned char inbuffer[64];
    unsigned char status = 0;

    memset(outbuffer, 0, 64);
    memset(inbuffer, 0, 64);

    unsigned int sample = 0;


    string address = txtWriteAddr->GetValue().ToStdString() ;

    sscanf(address.c_str(), "%x", &sample);

    outbuffer[8] = (sample >> 8) & 0xFF;
    outbuffer[9] = (sample) & 0xFF;

    string value = txtWvalue->GetValue().ToStdString() ;

    sscanf(value.c_str(), "%x", &sample);

    outbuffer[10] = (sample >> 8) & 0xFF;
    outbuffer[11] = (sample) & 0xFF;

    outbuffer[0] = CMD_LMS7002_WR;
    outbuffer[2] = 1;


    if( m_serPort->Port_write_direct(outbuffer, 64) )
    {
        long bytesToRead = 64;
        milSleep(25);
        if( m_serPort->Port_read_direct(inbuffer, bytesToRead) )
        {
            status = inbuffer[1];
            switch(status)
            {
            case STATUS_COMPLETED_CMD:
                lblWstatus->SetLabel("CMD_COMPLETE");
                break;
            case STATUS_ERROR_CMD:
                lblWstatus->SetLabel("CMD_ERROR");
                break;
            case STATUS_BUSY_CMD:
                lblWstatus->SetLabel("CMD_BUSY");
                break;
            case STATUS_MANY_BLOCKS_CMD:
                lblWstatus->SetLabel("CMD_MANY_BLOCKS");
                break;
            case STATUS_UNKNOWN_CMD:
                lblWstatus->SetLabel("CMD_UNKNOWN");
                break;
            }
        }
        else
        {
            lblWstatus->SetLabel("Read failed");
        };

    }
    else
    {
      lblWstatus->SetLabel("Write failed");
    };

}

void pnlSPI::OnbtnReadClick(wxCommandEvent& event)
{
    const int readCount = chkTripleCheck->GetValue() == true ? 3 : 1;
    unsigned char outbuffer[64];
    unsigned char inbuffer[3][64];
    unsigned char status = 0;

    memset(outbuffer, 0, 64);
    for(int i=0; i<readCount; ++i)
        memset(inbuffer, 0, 64);

    unsigned int sample = 0;
    stringstream ss;

    ss.str( txtReadAddr->GetValue().ToStdString() );

    string address = txtReadAddr->GetValue().ToStdString() ;

    sscanf(address.c_str(), "%x", &sample);

    outbuffer[8] = (sample >> 8) & 0xFF;
    outbuffer[9] = (sample) & 0xFF;

    outbuffer[0] = CMD_LMS7002_RD;
    outbuffer[2] = 1;

    for(int i=0; i<readCount; ++i)
    {
        if( m_serPort->Port_write_direct(outbuffer, 64) )
        {
            milSleep(25);
            long bytesToRead = 64;
            if(m_serPort->Port_read_direct(inbuffer[i], bytesToRead))
            {
                status = inbuffer[i][1];
                switch(status)
                {
                case STATUS_COMPLETED_CMD:
                    lblRstatus->SetLabel("CMD_COMPLETE");
                    break;
                case STATUS_ERROR_CMD:
                    lblRstatus->SetLabel("CMD_ERROR");
                    break;
                case STATUS_BUSY_CMD:
                    lblRstatus->SetLabel("CMD_BUSY");
                    break;
                case STATUS_MANY_BLOCKS_CMD:
                    lblRstatus->SetLabel("CMD_MANY_BLOCKS");
                    break;
                case STATUS_UNKNOWN_CMD:
                    lblRstatus->SetLabel("CMD_UNKNOWN");
                    break;
                default:
                    lblRstatus->SetLabel("UNDEFINED STATUS");
                }
            }
            else
            {
                lblRstatus->SetLabel("Read failed");
            };
        }
        else
        {
            lblRstatus->SetLabel("Write failed");
        };
    }

    for(int i=0; i<64; ++i)
    {
        if(chkTripleCheck->GetValue() == true)
            inbuffer[0][i] = bestOfThree(inbuffer[0][i],inbuffer[1][i],inbuffer[2][i]);
    }
    wxString txthex = "";
    txthex= wxString::Format("%02X %02X", inbuffer[0][10], inbuffer[0][11]);
    lblReadVal->SetLabel(txthex);
}

void pnlSPI::OnrgrChannelSelectSelect(wxCommandEvent& event)
{
    int selection = event.GetSelection();
    unsigned short addr = 0x0020;
    unsigned short value = 0xFFFF;

    unsigned char outbuffer[64];
    unsigned char inbuffer[64];
    memset(outbuffer, 0, 64);
    memset(inbuffer, 0, 64);

    outbuffer[8] = (addr >> 8) & 0xFF;
    outbuffer[9] = (addr) & 0xFF;

    outbuffer[0] = CMD_LMS7002_WR;
    outbuffer[2] = 1;



    switch(selection)
    {
    case 0: // A
        value = 0xFFFD;
        break;
    case 1: //B
        value = 0xFFFE;
        break;
    case 2: //A and B
        value = 0xFFFF;
        break;
    }

    outbuffer[10] = (value >> 8) & 0xFF;
    outbuffer[11] = (value) & 0xFF;

    long toRead = 64;
    if( m_serPort->Port_write_direct(outbuffer, 64) )
        m_serPort->Port_read_direct(inbuffer, toRead);
}

void pnlSPI::PrintLine(const string msg)
{
    txtTestText->WriteText( msg );
}

int pnlSPI::RunModuleTest(int moduleId, bool customInterval)
{
    if(moduleId < 0 || moduleId >= LMS_MODULES_COUNT)
        return -2;

    string testName;
    unsigned int startAddr;
    unsigned int endAddr;
    bool checkOnlyUsed = true;

    if(customInterval)
    {
        testName = "Custom ";
        string addr = txtStartAddr->GetValue().ToStdString() ;
        sscanf(addr.c_str(), "%x", &startAddr);
        addr = txtEndAddr->GetValue().ToStdString() ;
        sscanf(addr.c_str(), "%x", &endAddr);
        checkOnlyUsed = false;
    }
    else
    {
        testName = lmsControl->getRegistersMap()->m_modulesInfo[moduleId].name;
        startAddr = lmsControl->getRegistersMap()->m_modulesInfo[moduleId].startAddr;
        endAddr = lmsControl->getRegistersMap()->m_modulesInfo[moduleId].endAddr;
        checkOnlyUsed = lmsControl->getRegistersMap()->m_modulesInfo[moduleId].onlyUsedAddresses;
    }

    txtTestText->Clear();

    unsigned int pattern = 0;
    string address = txtHexInput->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &pattern);

    int status;
    if(chkBatchWR->GetValue() == false)
        status = lmsControl->getRegistersMap()->RegisterTestSimple(testName, startAddr, endAddr, pattern, checkOnlyUsed);
    else
        status = lmsControl->getRegistersMap()->RegisterTestBatch(testName, startAddr, endAddr, pattern, checkOnlyUsed);


    if(chkSaveToFile->GetValue() == true)
    {
        wxFileDialog dlg(this, "Save text file", "", "", "Text (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        string filename = testName;
        filename.append("_");
        filename.append(txtHexInput->GetValue().ToStdString());
        /*if(status == 1)
            filename.append("_PASSED");
        else
            filename.append("_FAILED");*/
        dlg.SetFilename(filename);
        if (dlg.ShowModal() == wxID_CANCEL)
            return -2;

        fstream fout;
        fout.open(dlg.GetPath().ToStdString().c_str(), ios::out);
        fout << txtTestText->GetValue() << endl;
        fout.close();
    }

    return status;
}

void pnlSPI::OnbtnTestLimeLightClick(wxCommandEvent& event)
{
    RunModuleTest(LIME_LIGHT);
}

void pnlSPI::OnbtnTestAFEClick(wxCommandEvent& event)
{
    RunModuleTest(AFE);
}

void pnlSPI::OnbtnTestBIASClick(wxCommandEvent& event)
{
    RunModuleTest(BIAS);
}

void pnlSPI::OnbtnTestXBUFClick(wxCommandEvent& event)
{
    RunModuleTest(XBUF);
}

void pnlSPI::OnbtnTestCGENClick(wxCommandEvent& event)
{
    RunModuleTest(CGEN);
}

void pnlSPI::OnbtnTestLDOClick(wxCommandEvent& event)
{
    RunModuleTest(LDO);
}

void pnlSPI::OnbtnTestBISTClick(wxCommandEvent& event)
{
    RunModuleTest(BIST);
}

void pnlSPI::OnbtnTestTRFClick(wxCommandEvent& event)
{
    RunModuleTest(TRF);
}

void pnlSPI::OnbtnTestTBBClick(wxCommandEvent& event)
{
    RunModuleTest(TBB);
}

void pnlSPI::OnbtnTestRFEClick(wxCommandEvent& event)
{
    RunModuleTest(RFE);
}

void pnlSPI::OnbtnTestRBBClick(wxCommandEvent& event)
{
    RunModuleTest(RBB);
}

void pnlSPI::OnbtnTestSXRSXTClick(wxCommandEvent& event)
{
    RunModuleTest(SXRSXT);
}

void pnlSPI::OnbtnTestTxTSPClick(wxCommandEvent& event)
{
    RunModuleTest(TxTSP);
}

void pnlSPI::OnbtnTestTxNCOClick(wxCommandEvent& event)
{
    RunModuleTest(TxNCO);
}

void pnlSPI::OnbtnTestRxTSPClick(wxCommandEvent& event)
{
    RunModuleTest(RxTSP);
}

void pnlSPI::OnbtnTestRxNCOClick(wxCommandEvent& event)
{
    RunModuleTest(RxNCO);
}

void pnlSPI::OnbtnTestCDSClick(wxCommandEvent& event)
{
    RunModuleTest(CDS);
}

void pnlSPI::OnbtnTestIntervalClick(wxCommandEvent& event)
{
    RunModuleTest(0, true);
}

void pnlSPI::OnbtnBatchReadClick(wxCommandEvent& event)
{
    unsigned int readFailures = 0;
    stringstream outToFile;
    long bytesToRead = 64;

    unsigned char outbuffer[64];
    unsigned char inbuffer[64];
    unsigned char status = 0;
    unsigned int sample = 0;
    string address;
    unsigned int rdD0, rdD1, rdD2, rdReal;

    memset(outbuffer, 0, 64);
    memset(inbuffer, 0, 64);
    txtTestText->Clear();

    //Define the command in packet's header
    outbuffer[0] = CMD_LMS7002_RD;  //Command
    outbuffer[2] = 3;               //Block count

    //Define what we want to read
    address = txtReadAddr->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    //We want to read the same address three times
    outbuffer[8] = (sample >> 8) & 0xFF;
    outbuffer[9] = (sample) & 0xFF;
    outbuffer[10] = outbuffer[8];
    outbuffer[11] = outbuffer[9];
    outbuffer[12] = outbuffer[8];
    outbuffer[13] = outbuffer[9];

    outToFile << "Batch reading " << spinBatchCount->GetValue() << " times, address 0x" << txtReadAddr->GetValue().ToStdString() << endl;

    for(int i=0; i<spinBatchCount->GetValue(); i++)
    {
        if( m_serPort->Port_write_direct(outbuffer, 64) )
        {
            milSleep(25); // pause between readings

            outToFile << setw(4) << i+1 << ".  ";
            memset(inbuffer, 0, 64);
            if(m_serPort->Port_read_direct(inbuffer, bytesToRead))
            {
                //Grab the data from the buffer
                rdD0 = inbuffer[10];
                rdD0 = (rdD0 << 8) | inbuffer[11];

                rdD1 = inbuffer[14];
                rdD1 = (rdD1 << 8) | inbuffer[15];

                rdD2 = inbuffer[18];
                rdD2 = (rdD2 << 8) | inbuffer[19];

                //Show the data
                outToFile << wxString::Format("0x%04X ", rdD0);
                outToFile << wxString::Format("0x%04X ", rdD1);
                outToFile << wxString::Format("0x%04X ", rdD2);

                //Compare values and decide for a real one
                rdReal = 0xFF0000;
                if(rdD0 != rdD1) { outToFile << "0!=1 "; readFailures++; }
                else rdReal = rdD0;
                if(rdD0 != rdD2) { outToFile << "0!=2 "; readFailures++; }
                else rdReal = rdD0;
                if(rdD1 != rdD2) { outToFile << "1!=2 "; readFailures++; }
                else rdReal = rdD1;

                //Show the real value
                if(rdReal > 0xFFFF)
                {
                    outToFile << wxString::Format(" Data: DNK ", rdReal);
                    rdReal = rdD0;
                }
                else
                {
                    outToFile << wxString::Format(" Data: 0x%04X ", rdReal);
                };

                //Communication statistics
                status = inbuffer[1];
                switch(status)
                {
                    case STATUS_COMPLETED_CMD:
                        outToFile << "Status: CMD_COMPLETE";
                    break;

                    case STATUS_ERROR_CMD:
                        outToFile << "Status: CMD_ERROR";
                    break;

                    case STATUS_BUSY_CMD:
                        outToFile << "Status: CMD_BUSY";
                    break;

                    case STATUS_MANY_BLOCKS_CMD:
                        outToFile << "Status: CMD_MANY_BLOCKS";
                    break;

                    case STATUS_UNKNOWN_CMD:
                        outToFile << "Status: CMD_UNKNOWN";
                    break;

                    default:
                        outToFile << "Status: UNDEFINED STATUS";
                }

            }
            else
            {
                outToFile << "Read failed";
            };
        }
        else
        {
            outToFile << setw(3) << i << ". " << "Write failed";
        }
        outToFile << endl;
    }
    outToFile << "Read Failures: " << readFailures << endl;

    //Show data on GUI
    txtTestText->WriteText( outToFile.str() );

    //Save to file if desired
    if(chkSaveToFileBatch->GetValue() == true)
    {
        wxFileDialog dlg(this, "Save text file", "", "", "Text (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
        string filename = "BatchRead";
        dlg.SetFilename(filename);
        if (dlg.ShowModal() == wxID_OK)
        {
            fstream fout;
            fout.open(dlg.GetPath().ToStdString().c_str(), ios::out);
            fout << outToFile.rdbuf() << endl;
            fout.close();
        }
    }
}

void pnlSPI::OnbtnWrTesterClick(wxCommandEvent& event)
{
    stringstream outToFile;

    unsigned char outbufferW[64];
    unsigned char outbufferR[64];
    unsigned char inbuffer[64];
    unsigned int sample = 0;
    long bytesToRead = 64;
    int i, j;
    string address;
    string value;

    memset(outbufferW, 0, 64);
    memset(outbufferR, 0, 64);
    memset(inbuffer, 0, 64);
    txtTestText->Clear();

    address = txtReadAddr->GetValue().ToStdString();
    value = txtWvalue->GetValue().ToStdString() ;

    //Prepare Write Command
    sscanf(address.c_str(), "%x", &sample);
    outbufferW[8] = (sample >> 8) & 0xFF;
    outbufferW[9] = (sample) & 0xFF;

    sscanf(value.c_str(), "%x", &sample);
    outbufferW[10] = (sample >> 8) & 0xFF;
    outbufferW[11] = (sample) & 0xFF;

    outbufferW[0] = CMD_LMS7002_WR;
    outbufferW[2] = 1;

    //Prepare Read Command
    sscanf(address.c_str(), "%x", &sample);
    outbufferR[8] = (sample >> 8) & 0xFF;
    outbufferR[9] = (sample) & 0xFF;

    outbufferR[0] = CMD_LMS7002_RD;
    outbufferR[2] = 1;



    outToFile << "Write Tester, address 0x" << txtReadAddr->GetValue().ToStdString() << endl;


    for(i=0; i<100; i++)
    {
        if( m_serPort->Port_write_direct(outbufferW, 64) )
        {
            milSleep(25); // pause between readings
            memset(inbuffer, 0, 64);
            m_serPort->Port_read_direct(inbuffer, bytesToRead);

            for(j=0; j<20; j++)
            {
                m_serPort->Port_write_direct(outbufferR, 64);
                milSleep(25); // pause between readings
                memset(inbuffer, 0, 64);
                m_serPort->Port_read_direct(inbuffer, bytesToRead);

                //Let us check if the read value differs from the first read.
                //Mark it with * if it differs.
                if((outbufferW[10] == inbuffer[10]) && (outbufferW[11] == inbuffer[11]))
                {
                    break;
                };
            };

            //outToFile << "j: " << j << endl;

            if(j == 20)
            {
                outToFile << "PROBLEM, indexes: " << i << ", " << j << endl;
            };
        }
        else
        {
            outToFile << setw(3) << i << ". " << "Write failed" << endl;
        };
        //outToFile << endl;
    }



    txtTestText->WriteText( outToFile.str() );
}

void pnlSPI::OnchkTripleCheckClick(wxCommandEvent& event)
{
    m_serPort->EnableTrippleReadChecking(chkTripleCheck->GetValue());
}

void pnlSPI::OnbtnPurgeCOMClick(wxCommandEvent& event)
{
    //m_serPort->ClearComm();
}

void pnlSPI::OnchkTestWrittenDataClick(wxCommandEvent& event)
{
    m_serPort->EnableTestWrittenData(chkTestWrittenData->GetValue());
}

void pnlSPI::OnbtnWriteBrdClick(wxCommandEvent& event)
{
    unsigned char outbuffer[64];
    unsigned char inbuffer[64];
    unsigned char status = 0;
    memset(outbuffer, 0, 64);
    memset(inbuffer, 0, 64);
    unsigned int sample = 0;
    string address = txtWriteAddrBrd->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    outbuffer[8] = (sample >> 8) & 0xFF;
    outbuffer[9] = (sample) & 0xFF;
    string value = txtWvalueBrd->GetValue().ToStdString() ;
    sscanf(value.c_str(), "%x", &sample);
    outbuffer[10] = (sample >> 8) & 0xFF;
    outbuffer[11] = (sample) & 0xFF;
    outbuffer[0] = CMD_BRDSPI_WR;
    outbuffer[2] = 1;

    if( m_serPort->Port_write_direct(outbuffer, 64) )
    {
        long bytesToRead = 64;
        milSleep(25);
        if( m_serPort->Port_read_direct(inbuffer, bytesToRead) )
        {
            status = inbuffer[1];
            lblWstatusBrd->SetLabel(status2string(status));
        }
        else
            lblWstatusBrd->SetLabel("Read failed");
    }
    else
        lblWstatusBrd->SetLabel("Write failed");
}

void pnlSPI::OnbtnReadBrdClick(wxCommandEvent& event)
{
    unsigned char outbuffer[64];
    unsigned char inbuffer[64];
    unsigned char status = 0;
    memset(outbuffer, 0, 64);
    memset(inbuffer, 0, 64);
    unsigned int sample = 0;
    stringstream ss;
    ss.str( txtReadAddrBrd->GetValue().ToStdString() );
    string address = txtReadAddrBrd->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);

    outbuffer[8] = (sample >> 8) & 0xFF;
    outbuffer[9] = (sample) & 0xFF;
    outbuffer[0] = CMD_BRDSPI_RD;
    outbuffer[2] = 1;

    if( m_serPort->Port_write_direct(outbuffer, 64) )
    {
        milSleep(25);
        long bytesToRead = 64;
        if(m_serPort->Port_read_direct(inbuffer, bytesToRead))
        {
            status = inbuffer[1];
            lblRstatusBrd->SetLabel(status2string(status));
        }
        else
        {
            lblRstatusBrd->SetLabel("Read failed");
        };
    }
    else
    {
        lblRstatusBrd->SetLabel("Write failed");
    };

    wxString txthex = "";
    txthex= wxString::Format("%02X %02X", inbuffer[10], inbuffer[11]);
    lblReadValBrd->SetLabel(txthex);
}

void pnlSPI::OnbtnWriteI2CClick(wxCommandEvent& event)
{
    unsigned char outbuffer[64];
    unsigned char inbuffer[64];
    unsigned char status = 0;
    memset(outbuffer, 0, 64);
    memset(inbuffer, 0, 64);
    unsigned int sample = 0;
    string address = txtWriteAddrI2C->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    outbuffer[8] = (sample) & 0xFF;
    string value = txtWvalueI2C->GetValue().ToStdString() ;
    sscanf(value.c_str(), "%x", &sample);
    outbuffer[9] = (sample) & 0xFF;
    outbuffer[0] = CMD_TFP410_WR;
    outbuffer[2] = 1;

    if( m_serPort->Port_write_direct(outbuffer, 64) )
    {
        long bytesToRead = 64;
        milSleep(25);
        if( m_serPort->Port_read_direct(inbuffer, bytesToRead) )
        {
            status = inbuffer[1];
            lblWstatusI2C->SetLabel(status2string(status));
        }
        else
            lblWstatusI2C->SetLabel("Read failed");
    }
    else
        lblWstatusI2C->SetLabel("Write failed");
}

void pnlSPI::OnbtnReadI2CClick(wxCommandEvent& event)
{
    unsigned char outbuffer[64];
    unsigned char inbuffer[64];
    unsigned char status = 0;
    memset(outbuffer, 0, 64);
    memset(inbuffer, 0, 64);
    unsigned int sample = 0;
    stringstream ss;
    ss.str( txtReadAddrI2C->GetValue().ToStdString() );
    string address = txtReadAddrI2C->GetValue().ToStdString() ;
    sscanf(address.c_str(), "%x", &sample);
    outbuffer[8] = (sample) & 0xFF;
    outbuffer[0] = CMD_TFP410_RD;
    outbuffer[2] = 1;

    if( m_serPort->Port_write_direct(outbuffer, 64) )
    {
        milSleep(25);
        long bytesToRead = 64;
        if(m_serPort->Port_read_direct(inbuffer, bytesToRead))
        {
            status = inbuffer[1];
            lblRstatusI2C->SetLabel(status2string(status));
        }
        else
            lblRstatusI2C->SetLabel("Read failed");
    }
    else
        lblRstatusI2C->SetLabel("Write failed");

    wxString txthex = "";
    txthex = wxString::Format("%02X", inbuffer[9]);
    lblReadValI2C->SetLabel(txthex);
}
