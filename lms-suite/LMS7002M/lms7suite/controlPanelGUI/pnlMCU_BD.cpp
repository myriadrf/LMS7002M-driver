/**
@file 	pnlMCU_BD.cpp
@author Lime Microsystems
@brief	panel for controlling on board MCU
*/

#include "pnlMCU_BD.h"
#include "LMS7002_MainControl.h"

#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/valtext.h>
#include "dlgViewSFR.h"
#include "dlgViewIRAM.h"

//(*InternalHeaders(pnlMCU_BD)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/radiobut.h>
#include <wx/choice.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/gauge.h>
//*)

//(*IdInit(pnlMCU_BD)
const long pnlMCU_BD::ID_STATICTEXT1 = wxNewId();
const long pnlMCU_BD::ID_BUTTON_LOADHEX = wxNewId();
const long pnlMCU_BD::ID_CHECKBOX_RESETMCU = wxNewId();
const long pnlMCU_BD::ID_RADIOBOX1 = wxNewId();
const long pnlMCU_BD::ID_BUTTON_STARTPROG = wxNewId();
const long pnlMCU_BD::ID_S_PROGFINISHED = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT3 = wxNewId();
const long pnlMCU_BD::ID_BUTTON1 = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT4 = wxNewId();
const long pnlMCU_BD::ID_TESTNO = wxNewId();
const long pnlMCU_BD::ID_BUTTON3 = wxNewId();
const long pnlMCU_BD::ID_DEBUGMODE = wxNewId();
const long pnlMCU_BD::ID_RUNINSTR = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT6 = wxNewId();
const long pnlMCU_BD::ID_INSTRNO = wxNewId();
const long pnlMCU_BD::ID_RESETPC = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT7 = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT8 = wxNewId();
const long pnlMCU_BD::ID_VIEWSFRS = wxNewId();
const long pnlMCU_BD::ID_VIEWIRAM = wxNewId();
const long pnlMCU_BD::ID_ERASEIRAM = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT10 = wxNewId();
const long pnlMCU_BD::ID_SELDIV = wxNewId();
const long pnlMCU_BD::ID_RADIOBUTTON4 = wxNewId();
const long pnlMCU_BD::ID_RADIOBUTTON5 = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT5 = wxNewId();
const long pnlMCU_BD::ID_CHOICE1 = wxNewId();
const long pnlMCU_BD::ID_RADIOBUTTON7 = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT11 = wxNewId();
const long pnlMCU_BD::ID_TEXTCTRL1 = wxNewId();
const long pnlMCU_BD::ID_RADIOBUTTON6 = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT9 = wxNewId();
const long pnlMCU_BD::ID_BUTTON2 = wxNewId();
const long pnlMCU_BD::ID_BUTTON4 = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT14 = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT15 = wxNewId();
const long pnlMCU_BD::ID_BUTTON5 = wxNewId();
const long pnlMCU_BD::ID_BUTTON6 = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT2 = wxNewId();
const long pnlMCU_BD::ID_GAUGE1 = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT12 = wxNewId();
const long pnlMCU_BD::ID_STATICTEXT13 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlMCU_BD,wxPanel)
    //(*EventTable(pnlMCU_BD)
    //*)
END_EVENT_TABLE()

//pnlMCU_BD::pnlMCU_BD(wxWindow* parent,wxWindowID id)
pnlMCU_BD::pnlMCU_BD(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
//   lmsControl = NULL;
//   BuildContent(parent,id,pos,size);
//    AssignEnumsToIds();
    m_iRegAddress = 0;
    m_iTestNo=0;

    //pMCU= new MCU_BD();
    //(*Initialize(pnlMCU_BD)
    wxStaticBoxSizer* DebugModeStaticBoxSizer;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxFlexGridSizer* FlexGridSizer4;
    wxRadioButton* m_cCtrlBaseband;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxStaticBoxSizer* StaticBoxSizer9;
    wxFlexGridSizer* FlexGridSizer7;
    wxStaticBoxSizer* StaticBoxSizer7;
    wxStaticBoxSizer* StaticBoxSizer8;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxGridSizer* GridSizer1;
    wxStaticBoxSizer* StaticBoxSizer6;
    wxFlexGridSizer* FlexGridSizer15;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer14;
    wxBoxSizer* BoxSizer1;
    wxFlexGridSizer* FlexGridSizer13;
    wxFlexGridSizer* FlexGridSizer12;
    wxFlexGridSizer* FlexGridSizer6;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer11;
    wxStaticBoxSizer* StaticBoxSizer5;

    Create(parent, wxID_ANY, wxDefaultPosition, wxSize(131,117), wxTAB_TRAVERSAL, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 5);
    FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Load .hex file:"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Select the file:"), wxDefaultPosition, wxSize(76,13), 0, _T("ID_STATICTEXT1"));
    BoxSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button_LOADHEX = new wxButton(this, ID_BUTTON_LOADHEX, _("Load .hex"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOADHEX"));
    BoxSizer1->Add(Button_LOADHEX, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer7->Add(BoxSizer1, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(StaticBoxSizer7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Programming options"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
    chkReset = new wxCheckBox(this, ID_CHECKBOX_RESETMCU, _("Reset MCU"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RESETMCU"));
    chkReset->SetValue(true);
    FlexGridSizer6->Add(chkReset, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wxString __wxRadioBoxChoices_1[3] =
    {
    	_("Send program to SRAM and EEPROM"),
    	_("Send program to SRAM"),
    	_("Boot MCU from EEPROM")
    };
    rgrMode = new wxRadioBox(this, ID_RADIOBOX1, _("MCU\'s programming mode:"), wxDefaultPosition, wxDefaultSize, 3, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_RADIOBOX1"));
    rgrMode->Disable();
    FlexGridSizer6->Add(rgrMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnStartProgramming = new wxButton(this, ID_BUTTON_STARTPROG, _("Send command"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_STARTPROG"));
    btnStartProgramming->Disable();
    FlexGridSizer6->Add(btnStartProgramming, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    m_sProgFinished = new wxStaticText(this, ID_S_PROGFINISHED, _("Proggramming finished"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_S_PROGFINISHED"));
    FlexGridSizer6->Add(m_sProgFinished, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6->Add(FlexGridSizer6, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(StaticBoxSizer6, 1, wxEXPAND|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Testing options"));
    FlexGridSizer8 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Load test results file:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    FlexGridSizer8->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    btnLoadTestFile = new wxButton(this, ID_BUTTON1, _("Load file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer8->Add(btnLoadTestFile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Select test no. (1-14):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer8->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_sTestNo = new wxTextCtrl(this, ID_TESTNO, _("1"), wxDefaultPosition, wxSize(73,-1), 0, wxTextValidator(wxFILTER_NUMERIC), _T("ID_TESTNO"));
    FlexGridSizer8->Add(m_sTestNo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnRunTest = new wxButton(this, ID_BUTTON3, _("Run test"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer8->Add(btnRunTest, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer5->Add(FlexGridSizer8, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(StaticBoxSizer5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizer4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DebugModeStaticBoxSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("MCU\'s Debug mode options"));
    FlexGridSizer3 = new wxFlexGridSizer(7, 1, 0, 0);
    DebugMode = new wxCheckBox(this, ID_DEBUGMODE, _("Select Debug mode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DEBUGMODE"));
    DebugMode->SetValue(false);
    FlexGridSizer3->Add(DebugMode, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Execution control"));
    FlexGridSizer5 = new wxFlexGridSizer(2, 3, 0, 0);
    RunInstr = new wxButton(this, ID_RUNINSTR, _("Run instr."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RUNINSTR"));
    FlexGridSizer5->Add(RunInstr, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("No. (1-100)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    FlexGridSizer5->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    InstrNo = new wxTextCtrl(this, ID_INSTRNO, _("1"), wxDefaultPosition, wxSize(68,-1), 0, wxDefaultValidator, _T("ID_INSTRNO"));
    FlexGridSizer5->Add(InstrNo, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ResetPC = new wxButton(this, ID_RESETPC, _("Reset PC"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RESETPC"));
    FlexGridSizer5->Add(ResetPC, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    P = new wxStaticText(this, ID_STATICTEXT7, _("PC value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    FlexGridSizer5->Add(P, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PCValue = new wxStaticText(this, ID_STATICTEXT8, _("PCVAL"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    FlexGridSizer5->Add(PCValue, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(FlexGridSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(StaticBoxSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("SFR and IRAM options "));
    FlexGridSizer10 = new wxFlexGridSizer(0, 1, 0, 0);
    ViewSFRs = new wxButton(this, ID_VIEWSFRS, _("View SFRs"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_VIEWSFRS"));
    FlexGridSizer10->Add(ViewSFRs, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ViewIRAM = new wxButton(this, ID_VIEWIRAM, _("View IRAM"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_VIEWIRAM"));
    FlexGridSizer10->Add(ViewIRAM, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    EraseIRAM = new wxButton(this, ID_ERASEIRAM, _("Erase IRAM"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ERASEIRAM"));
    FlexGridSizer10->Add(EraseIRAM, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(FlexGridSizer10, 1, wxALL|wxEXPAND|wxSHAPED|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("MCU\'s clock divider"));
    FlexGridSizer9 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Select MCU\'s clock divider value:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    FlexGridSizer9->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SelDiv = new wxChoice(this, ID_SELDIV, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_SELDIV"));
    SelDiv->Append(_("1"));
    SelDiv->Append(_("2"));
    SelDiv->Append(_("4"));
    SelDiv->Append(_("8"));
    SelDiv->Append(_("16"));
    SelDiv->Append(_("32"));
    FlexGridSizer9->Add(SelDiv, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3->Add(FlexGridSizer9, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DebugModeStaticBoxSizer->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(DebugModeStaticBoxSizer, 1, wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
    StaticBoxSizer8 = new wxStaticBoxSizer(wxVERTICAL, this, _("SPI switch tranceiver control"));
    m_cCtrlBaseband = new wxRadioButton(this, ID_RADIOBUTTON4, _("Transceiver controlled by Baseband"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP, wxDefaultValidator, _T("ID_RADIOBUTTON4"));
    m_cCtrlBaseband->SetValue(true);
    StaticBoxSizer8->Add(m_cCtrlBaseband, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_cCtrlMCU_BD = new wxRadioButton(this, ID_RADIOBUTTON5, _("Transceiver controlled by MCU_BD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON5"));
    StaticBoxSizer8->Add(m_cCtrlMCU_BD, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7->Add(StaticBoxSizer8, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer9 = new wxStaticBoxSizer(wxVERTICAL, this, _("Read/write registers REG0-REG6"));
    FlexGridSizer11 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Address:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    FlexGridSizer11->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice1 = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->SetSelection( Choice1->Append(_("REG0")) );
    Choice1->Append(_("REG1"));
    Choice1->Append(_("REG2"));
    Choice1->Append(_("REG3"));
    Choice1->Append(_("REG4"));
    Choice1->Append(_("REG5"));
    Choice1->Append(_("REG6"));
    FlexGridSizer11->Add(Choice1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer9->Add(FlexGridSizer11, 0, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer12 = new wxFlexGridSizer(0, 3, 0, 0);
    RadioButton7 = new wxRadioButton(this, ID_RADIOBUTTON7, _("Write"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP, wxDefaultValidator, _T("ID_RADIOBUTTON7"));
    RadioButton7->SetValue(true);
    FlexGridSizer12->Add(RadioButton7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(this, ID_STATICTEXT11, _("Data (0-255):"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    FlexGridSizer12->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("0"), wxDefaultPosition, wxSize(65,-1), 0, wxTextValidator(wxFILTER_NUMERIC), _T("ID_TEXTCTRL1"));
    FlexGridSizer12->Add(TextCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RadioButton6 = new wxRadioButton(this, ID_RADIOBUTTON6, _("Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON6"));
    FlexGridSizer12->Add(RadioButton6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ReadResult = new wxStaticText(this, ID_STATICTEXT9, _("Result is:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    FlexGridSizer12->Add(ReadResult, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer12->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer9->Add(FlexGridSizer12, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button4 = new wxButton(this, ID_BUTTON2, _("Read/Write"), wxDefaultPosition, wxSize(105,36), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    StaticBoxSizer9->Add(Button4, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7->Add(StaticBoxSizer9, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Algorithms"));
    FlexGridSizer14 = new wxFlexGridSizer(0, 2, 0, 0);
    btnRxDC = new wxButton(this, ID_BUTTON4, _("Rx DC"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    btnRxDC->Disable();
    FlexGridSizer14->Add(btnRxDC, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer15 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText7 = new wxStaticText(this, ID_STATICTEXT14, _("Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
    FlexGridSizer15->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lblAlgorithmStatus = new wxStaticText(this, ID_STATICTEXT15, _("0x00"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    FlexGridSizer15->Add(lblAlgorithmStatus, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer14->Add(FlexGridSizer15, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTxDC = new wxButton(this, ID_BUTTON5, _("Tx DC"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    btnTxDC->Disable();
    FlexGridSizer14->Add(btnTxDC, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer14->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTxIQ = new wxButton(this, ID_BUTTON6, _("Tx IQ"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
    btnTxIQ->Disable();
    FlexGridSizer14->Add(btnTxIQ, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer4->Add(FlexGridSizer14, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer7->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer2->Add(FlexGridSizer7, 1, wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer13 = new wxFlexGridSizer(0, 3, 0, 0);
    FlexGridSizer13->AddGrowableCol(1);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Progress:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer13->Add(StaticText2, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    gaugeProgress = new wxGauge(this, ID_GAUGE1, 255, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL, wxDefaultValidator, _T("ID_GAUGE1"));
    FlexGridSizer13->Add(gaugeProgress, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer13, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    GridSizer1 = new wxGridSizer(0, 1, 0, 0);
    ProgCodeFile = new wxStaticText(this, ID_STATICTEXT12, _("Program code file:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
    GridSizer1->Add(ProgCodeFile, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TestResultsFile = new wxStaticText(this, ID_STATICTEXT13, _("Test results file:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
    GridSizer1->Add(TestResultsFile, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(GridSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    SetSizer(FlexGridSizer1);
    SetSizer(FlexGridSizer1);
    Layout();

    Connect(ID_BUTTON_LOADHEX,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnButton_LOADHEXClick);
    Connect(ID_CHECKBOX_RESETMCU,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnchkResetClick);
    Connect(ID_BUTTON_STARTPROG,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnbtnStartProgrammingClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnbtnLoadTestFileClick);
    Connect(ID_TESTNO,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&pnlMCU_BD::Onm_sTestNoText);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnbtnRunTestClick);
    Connect(ID_DEBUGMODE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnDebugModeClick);
    Connect(ID_RUNINSTR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnButton4Click);
    Connect(ID_INSTRNO,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&pnlMCU_BD::OnInstrNoText);
    Connect(ID_RESETPC,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnResetPCClick);
    Connect(ID_VIEWSFRS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnViewSFRsClick);
    Connect(ID_VIEWIRAM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnViewIRAMClick);
    Connect(ID_ERASEIRAM,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnEraseIRAMClick);
    Connect(ID_SELDIV,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&pnlMCU_BD::OnSelDivSelect);
    Connect(ID_RADIOBUTTON4,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&pnlMCU_BD::Onm_cCtrlBasebandSelect);
    Connect(ID_RADIOBUTTON5,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&pnlMCU_BD::Onm_cCtrlMCU_BDSelect);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&pnlMCU_BD::OnChoice1Select);
    Connect(ID_RADIOBUTTON7,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&pnlMCU_BD::OnRadioButton7Select);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&pnlMCU_BD::OnTextCtrl1Text);
    Connect(ID_RADIOBUTTON6,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&pnlMCU_BD::OnRadioButton6Select);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnButton4Click1);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnbtnRxDCClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnbtnTxDCClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlMCU_BD::OnbtnTxIQClick);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&pnlMCU_BD::OnPaint);
    //*)

    InitDialog();
}

void pnlMCU_BD::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
}

pnlMCU_BD::~pnlMCU_BD()
{
    //(*Destroy(pnlMCU_BD)
    //*)
}


void pnlMCU_BD::OnPaint(wxPaintEvent& event)
{
}

void pnlMCU_BD::InitDialog()
{
    m_iDebug=0;
    m_iPCvalue=0;
    m_iTestNo=1;
    m_iInstrNo=1;

    RunInstr->Enable(false);
    ResetPC->Enable(false);
    InstrNo->Enable(false);
    ViewSFRs->Enable(false);
    ViewIRAM->Enable(false);
    EraseIRAM->Enable(false);
    SelDiv->Enable(false);
    SelDiv->SetSelection(0);
    Choice1->SetSelection(0);

    wxString temps;
    temps.Printf(_("0x%04x"),m_iPCvalue);
    PCValue->SetLabel(temps);

    InstrNo->SetLabel("1");
    m_sTestNo->SetLabel("1");
}

void pnlMCU_BD::OnButton4Click(wxCommandEvent& event)
{
    wxString m_sPCVal;
    //temps<<"Test number is: "<<m_iTestNo;
    int i=0;
    int retval=0;
    unsigned short m_iPC=0;

    if  ((m_iInstrNo <1)||(m_iInstrNo>100))
    {
        m_iInstrNo=0; // default TestNo.
        InstrNo->SetValue(_("0"));
        wxMessageBox(_("Number of instructions must be in the range [1-100]!"));
    }
    else
    {
        for (i=0; i<m_iInstrNo; i++)
        {
            retval=lmsControl->getMCU_BD()->RunInstr_MCU(&m_iPC);
            if (retval==-1)
            {
                i=m_iInstrNo; // end loop
                m_iPCvalue=0;
            }
            else
            {
                m_iPCvalue=m_iPC;
            }
        }
        m_sPCVal.Printf(_("0x%04x"),m_iPCvalue);
        PCValue->SetLabel(m_sPCVal);
    }

}

void pnlMCU_BD::OnchkResetClick(wxCommandEvent& event)
{
    if(chkReset->IsChecked())
    {
        // MODE=0
        // RESET
        lmsControl->getMCU_BD()->Reset_MCU();
        rgrMode->Enable(false);
        btnStartProgramming->Enable(false);
        DebugMode->SetValue(false);
    }
    else
    {
        rgrMode->Enable(true);
        btnStartProgramming->Enable(true);
    }
}

void pnlMCU_BD::Onm_sTestNoText(wxCommandEvent& event)
{

    wxString text1 = m_sTestNo->GetValue();
    m_iTestNo = wxAtoi(text1);
    //
}

void pnlMCU_BD::OnDebugModeClick(wxCommandEvent& event)
{
    int mode = rgrMode->GetSelection()+1;
    int iMode0 = mode & 0x01;
    int iMode1 = (mode>>1) & 0x01;

    if(DebugMode->IsChecked())
    {
        RunInstr->Enable(true);
        ResetPC->Enable(true);
        InstrNo->Enable(true);
        ViewSFRs->Enable(true);
        ViewIRAM->Enable(true);
        EraseIRAM->Enable(true);
        SelDiv->Enable(true);

        m_iDebug=1;

        lmsControl->getMCU_BD()->DebugModeSet_MCU(iMode1, iMode0);
    }
    else
    {
        RunInstr->Enable(false);
        ResetPC->Enable(false);
        InstrNo->Enable(false);
        ViewSFRs->Enable(false);
        ViewIRAM->Enable(false);
        EraseIRAM->Enable(false);
        SelDiv->Enable(false);

        m_iDebug=0;
        lmsControl->getMCU_BD()->DebugModeExit_MCU(iMode1, iMode0);
    }
}

void pnlMCU_BD::OnInstrNoText(wxCommandEvent& event)
{
    wxString text1 = InstrNo->GetValue();
    m_iInstrNo = wxAtoi(text1);
}

void pnlMCU_BD::OnResetPCClick(wxCommandEvent& event)
{
    int retval=lmsControl->getMCU_BD()->ResetPC_MCU();
    if (retval==-1) wxMessageBox(_("Unable to reset MCU's Program Counter"));

}

void pnlMCU_BD::OnViewSFRsClick(wxCommandEvent& event)
{

    int retval=0;
    retval=lmsControl->getMCU_BD()->Read_SFR();
    if (retval==-1) wxMessageBox(_("Unable to read SFRs"));

    dlgViewSFR dlg(this);
    if (dlg.ShowModal() == wxID_OK);

}

void pnlMCU_BD::OnViewIRAMClick(wxCommandEvent& event)
{
    gaugeProgress->SetValue(0);
    int retval=0;
    retval=lmsControl->getMCU_BD()->Read_IRAM();
    if (retval==-1) wxMessageBox(_("Unable to read IRAM"));

    dlgViewIRAM dlg(this);
    if (dlg.ShowModal() == wxID_OK);
}

void pnlMCU_BD::OnEraseIRAMClick(wxCommandEvent& event)
{
    int retval=0;
    retval=lmsControl->getMCU_BD()->Erase_IRAM();
    if (retval==-1) wxMessageBox(_("Unable to erase IRAM content"));
}

void pnlMCU_BD::OnSelDivSelect(wxCommandEvent& event)
{
    int retval=0;
    int tempi=0;

    tempi=SelDiv->GetSelection();
    retval=lmsControl->getMCU_BD()->Change_MCUFrequency(tempi);
    wxString temps;
    temps.Printf(_T("Current selection: %s"), SelDiv->GetString(tempi));
    if (retval==-1) wxMessageBox("Cannot set the MCU's frequency");
    else wxMessageBox(temps);

}

void pnlMCU_BD::Onm_cCtrlBasebandSelect(wxCommandEvent& event)
{
    lmsControl->getMCU_BD()->mSPI_write(0x0006,0x0000); //REG6 write
}

void pnlMCU_BD::Onm_cCtrlMCU_BDSelect(wxCommandEvent& event)
{
    lmsControl->getMCU_BD()->mSPI_write(0x0006,0x0001); //REG6 write
}

void pnlMCU_BD::OnChoice1Select(wxCommandEvent& event)
{
    int tempi=0;
    tempi=Choice1->GetSelection();
    m_iRegAddress=(unsigned short) tempi;
}

void pnlMCU_BD::OnRadioButton7Select(wxCommandEvent& event)
{
    m_iRegRead=0;
}

void pnlMCU_BD::OnRadioButton6Select(wxCommandEvent& event)
{
    m_iRegRead=1;
}

void pnlMCU_BD::OnTextCtrl1Text(wxCommandEvent& event)
{
    wxString text1 = TextCtrl1->GetValue();
    m_iRegData = (unsigned short) wxAtoi(text1);
    if (m_iRegData>255)
    {
        m_iRegData=0;
        TextCtrl1->SetValue(_("0"));
    }
}

void pnlMCU_BD::OnButton4Click1(wxCommandEvent& event)
{
    unsigned short retval=0;
    unsigned short tempi=0x8000;

    tempi=tempi+m_iRegAddress;
    wxString temps;

    // if (retval==-1) wxMessageBox("Cannot set the MCU_BD Transceiver control");
    if (m_iRegRead==0)
        lmsControl->getMCU_BD()->mSPI_write(tempi,m_iRegData); //REG write
    else
    {
        retval=lmsControl->getMCU_BD()->mSPI_read(m_iRegAddress); //REG read
        cout << "retval = " << retval << endl;
        temps = wxString::Format("Result is: 0x%02x",retval);
        cout << "Result: " << temps << endl;
        ReadResult->SetLabel(temps);
    }
}

void pnlMCU_BD::OnbtnStartProgrammingClick(wxCommandEvent& event)
{
    gaugeProgress->SetValue(0);
    DebugMode->SetValue(false);
    int mode = rgrMode->GetSelection()+1;
    int iMode0 = mode & 0x01;
    int iMode1 = (mode>>1) & 0x01;

    if ((iMode1==0) && (iMode0==0))
    {
        wxMessageBox("Turn off reset.");
        return;
    }

    int retval=0;
    retval=lmsControl->getMCU_BD()->Program_MCU(iMode1, iMode0);
    if (retval==-1) wxMessageBox("Unable to program the MCU");
}


void pnlMCU_BD::OnButton_LOADHEXClick(wxCommandEvent& event)
{
    //int temp;
    wxFileDialog dlg(this, _("Open hex file"), "hex", "*.hex", "HEX Files (*.hex)|*.hex|BIN Files (*.bin)|*.bin|All Files (*.*)|*.*||", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_CANCEL) return;

    wxString m_sHexFileName=dlg.GetPath();
    std::string inFileName = std::string(m_sHexFileName.mb_str());

    if(dlg.GetFilterIndex() == 0)
        lmsControl->getMCU_BD()->GetProgramCode(inFileName, false);
    else
        lmsControl->getMCU_BD()->GetProgramCode(inFileName, true);
    //ProgCodeFile->SetLabel(m_sHexFileName);

    wxString temps;
    temps=_(".hex file: ");
    temps=temps<<m_sHexFileName;
    ProgCodeFile->SetLabel(temps);

}

void pnlMCU_BD::OnbtnLoadTestFileClick(wxCommandEvent& event)
{
    int  test_code=0;
    int  address=0;
    int  value=0;
    int i=0;
    //int temp;
    wxFileDialog dlg(this, _("Open txt file"), "txt", "*.txt", "TXT Files (*.txt)|*.txt|TXT Files (*.txt)|*.txt |All Files (*.*)|*.*||", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_CANCEL) return;

    wxString m_sTxtFileName=dlg.GetPath();
    wxString temps;
    temps=_("Test results file: ");
    temps=temps<<m_sTxtFileName;
    TestResultsFile->SetLabel(temps);
    //std::string inFileName = std::string();

    FILE * inFile=NULL;
    inFile = fopen(m_sTxtFileName.mb_str(), "r");

    if (inFile != NULL)
    {
        m_iTestResultFileLine=0;
        for (i=0; i<256; i++)
        {
            TestResultArray_code[i]=0;
            TestResultArray_address[i]=0;
            TestResultArray_value[i]=0;
        }
        while (!feof(inFile))
        {
            fscanf(inFile, "%d %d %d", &test_code, &address, &value);
            TestResultArray_code[m_iTestResultFileLine]=(unsigned char)(test_code);
            TestResultArray_address[m_iTestResultFileLine]=(unsigned char)(address);
            TestResultArray_value[m_iTestResultFileLine]=(unsigned char)(value);
            m_iTestResultFileLine++;
        }
    }
    fclose(inFile);
    //lmsControl->getMCU_BD()->GetProgramCode(inFileName);

}

void pnlMCU_BD::OnbtnRunTestClick(wxCommandEvent& event)
{
    int mode = rgrMode->GetSelection()+1;
    int iMode0 = mode & 0x01;
    int iMode1 = (mode>>1) & 0x01;

    int retval=0;
    int m_iError=0;

    if  ((m_iTestNo <0)||(m_iTestNo>14))
    {
        m_iTestNo=0;
        // default TestNo.
        m_sTestNo->SetValue(_("0"));
    }
    else
    {
        lmsControl->getMCU_BD()->RunTest_MCU(iMode1,iMode0,m_iTestNo,m_iDebug);
    }
    wxString temps;

    if  ((m_iTestNo >=1)&&(m_iTestNo<=14))
    {
        if   (retval==-1)  temps<<"Bad communication!";
        else if (m_iError==1)  temps<<"Test number "<<m_iTestNo<<" failed!";
        else temps<<"Test number "<<m_iTestNo<<" passed.";
        wxMessageBox(temps);
    }
}

void pnlMCU_BD::SetProgressBar(int i)
{
    gaugeProgress->SetValue(i);
}


void pnlMCU_BD::OnbtnRxDCClick(wxCommandEvent& event)
{
    lblAlgorithmStatus->SetLabel("------");
    lmsControl->algorithms->CallMCU(1);
    int status = lmsControl->algorithms->WaitForMCU();
    lblAlgorithmStatus->SetLabel(wxString::Format("0x%04X", status));
    lmsControl->algorithms->CallMCU(0);
}

void pnlMCU_BD::OnbtnTxDCClick(wxCommandEvent& event)
{
    lblAlgorithmStatus->SetLabel("------");
    lmsControl->algorithms->CallMCU(2);
    int status = lmsControl->algorithms->WaitForMCU();
    lblAlgorithmStatus->SetLabel(wxString::Format("0x%04X", status));
    lmsControl->algorithms->CallMCU(0);
}

void pnlMCU_BD::OnbtnTxIQClick(wxCommandEvent& event)
{
    lblAlgorithmStatus->SetLabel("------");
    lmsControl->algorithms->CallMCU(3);
    int status = lmsControl->algorithms->WaitForMCU();
    lblAlgorithmStatus->SetLabel(wxString::Format("0x%04X", status));
    lmsControl->algorithms->CallMCU(0);
}
