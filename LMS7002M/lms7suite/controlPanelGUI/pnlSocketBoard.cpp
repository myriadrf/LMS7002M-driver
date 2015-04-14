/**
@file 	pnlSocketBoard.cpp
@author Lime Microsystems
@brief	panel for configuring Socket board GPIO
*/
#include "pnlSocketBoard.h"

//(*InternalHeaders(pnlSocketBoard)
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

#include "ConnectionManager.h"

//(*IdInit(pnlSocketBoard)
const long pnlSocketBoard::ID_BUTTON1 = wxNewId();
const long pnlSocketBoard::ID_BUTTON3 = wxNewId();
const long pnlSocketBoard::ID_BUTTON2 = wxNewId();
const long pnlSocketBoard::ID_BUTTON4 = wxNewId();
const long pnlSocketBoard::ID_BUTTON5 = wxNewId();
const long pnlSocketBoard::ID_BUTTON6 = wxNewId();
const long pnlSocketBoard::ID_BUTTON7 = wxNewId();
const long pnlSocketBoard::ID_BUTTON8 = wxNewId();
const long pnlSocketBoard::ID_BUTTON9 = wxNewId();
const long pnlSocketBoard::ID_BUTTON10 = wxNewId();
const long pnlSocketBoard::ID_BUTTON11 = wxNewId();
const long pnlSocketBoard::ID_BUTTON12 = wxNewId();
const long pnlSocketBoard::ID_BUTTON13 = wxNewId();
const long pnlSocketBoard::ID_BUTTON14 = wxNewId();
const long pnlSocketBoard::ID_BUTTON15 = wxNewId();
const long pnlSocketBoard::ID_BUTTON16 = wxNewId();
const long pnlSocketBoard::ID_BUTTON17 = wxNewId();
const long pnlSocketBoard::ID_BUTTON18 = wxNewId();
const long pnlSocketBoard::ID_BUTTON19 = wxNewId();
const long pnlSocketBoard::ID_BUTTON20 = wxNewId();
const long pnlSocketBoard::ID_BUTTON21 = wxNewId();
const long pnlSocketBoard::ID_BUTTON22 = wxNewId();
const long pnlSocketBoard::ID_BUTTON23 = wxNewId();
const long pnlSocketBoard::ID_BUTTON24 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX8 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX9 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX10 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX11 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX12 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX13 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX14 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX15 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX1 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX2 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX3 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX4 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX5 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX6 = wxNewId();
const long pnlSocketBoard::ID_CHECKBOX7 = wxNewId();
const long pnlSocketBoard::ID_TABSOCKETSEVB7V2 = wxNewId();
const long pnlSocketBoard::ID_BUTTON25 = wxNewId();
const long pnlSocketBoard::ID_BUTTON26 = wxNewId();
const long pnlSocketBoard::ID_BUTTON27 = wxNewId();
const long pnlSocketBoard::ID_BUTTON28 = wxNewId();
const long pnlSocketBoard::ID_BUTTON29 = wxNewId();
const long pnlSocketBoard::ID_BUTTON30 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SocketBoardButton,wxButton)
    EVT_PAINT(SocketBoardButton::OnPaint)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(SourceSymbol,wxStaticText)
    EVT_PAINT(SourceSymbol::OnPaint)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(pnlSocketBoard,wxPanel)
	//(*EventTable(pnlSocketBoard)
	//*)
	EVT_PAINT(pnlSocketBoard::OnPaint)
	EVT_ERASE_BACKGROUND(pnlSocketBoard::OnEraseBackground)
END_EVENT_TABLE()

pnlSocketBoard::pnlSocketBoard(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size,int style, wxString name)
{
    gpioStates.resize(56, 0);
	BuildContent(parent,id,pos,size);
}

void pnlSocketBoard::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlSocketBoard)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxSize(800,700), wxTAB_TRAVERSAL, _T("id"));
	btnU38_1 = new SocketBoardButton(this, ID_BUTTON1, _T("LNAW_A"), wxPoint(8,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	btnU38_3 = new SocketBoardButton(this, ID_BUTTON3, _T("LNAL_A"), wxPoint(8,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	btnU38_2 = new SocketBoardButton(this, ID_BUTTON2, _T("LNAH_A"), wxPoint(8,56), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	btnU38_0 = new SocketBoardButton(this, ID_BUTTON4, _T("GND"), wxPoint(8,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	btnU37_0 = new SocketBoardButton(this, ID_BUTTON5, _T("LNAH_B"), wxPoint(8,112), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	btnU37_1 = new SocketBoardButton(this, ID_BUTTON6, _T("GND"), wxPoint(8,136), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	btnU37_2 = new SocketBoardButton(this, ID_BUTTON7, _T("LNAL_B"), wxPoint(8,160), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	btnU37_3 = new SocketBoardButton(this, ID_BUTTON8, _T("LNAW_B"), wxPoint(8,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
	btnU42_0 = new SocketBoardButton(this, ID_BUTTON9, _T("Tx1_A"), wxPoint(112,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON9"));
	btnU42_1 = new SocketBoardButton(this, ID_BUTTON10, _T("TX2_B"), wxPoint(112,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
	btnU42_2 = new SocketBoardButton(this, ID_BUTTON11, _T("TX2_A"), wxPoint(112,56), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
	btnU42_3 = new SocketBoardButton(this, ID_BUTTON12, _T("TX1_B"), wxPoint(112,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
	btnU43_0 = new SocketBoardButton(this, ID_BUTTON13, _T("RXBUFFQ_2"), wxPoint(112,112), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON13"));
	btnU43_1 = new SocketBoardButton(this, ID_BUTTON14, _T("RXBUFFI_2"), wxPoint(112,136), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON14"));
	btnU43_2 = new SocketBoardButton(this, ID_BUTTON15, _T("RXBUFFQ_1"), wxPoint(112,160), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON15"));
	btnU43_3 = new SocketBoardButton(this, ID_BUTTON16, _T("RXBUFFI_1"), wxPoint(112,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON16"));
	btnU47_0 = new SocketBoardButton(this, ID_BUTTON17, _T("TXINIP_1"), wxPoint(216,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON17"));
	btnU47_1 = new SocketBoardButton(this, ID_BUTTON18, _T("TXINIP_2"), wxPoint(216,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON18"));
	btnU44_0 = new SocketBoardButton(this, ID_BUTTON19, _T("TXININ_1"), wxPoint(216,56), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON19"));
	btnU44_1 = new SocketBoardButton(this, ID_BUTTON20, _T("TXININ_2"), wxPoint(216,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON20"));
	btnU41_0 = new SocketBoardButton(this, ID_BUTTON21, _T("TXINQP_1"), wxPoint(216,112), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON21"));
	btnU41_1 = new SocketBoardButton(this, ID_BUTTON22, _T("TXINQP_2"), wxPoint(216,136), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON22"));
	btnU40_0 = new SocketBoardButton(this, ID_BUTTON23, _T("TXINQN_1"), wxPoint(216,160), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON23"));
	btnU40_1 = new SocketBoardButton(this, ID_BUTTON24, _T("TXINQN_2"), wxPoint(216,184), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON24"));
	Panel1 = new wxPanel(this, ID_TABSOCKETSEVB7V2, wxPoint(0,225), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TABSOCKETSEVB7V2"));
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _T("GPIO Controls"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	chkGPIO0 = new wxCheckBox(Panel1, ID_CHECKBOX8, _T("GPIO_0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
	chkGPIO0->SetValue(false);
	chkGPIO0->Disable();
	FlexGridSizer1->Add(chkGPIO0, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkGPIO1 = new wxCheckBox(Panel1, ID_CHECKBOX9, _T("GPIO_1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
	chkGPIO1->SetValue(false);
	chkGPIO1->Disable();
	FlexGridSizer1->Add(chkGPIO1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkGPIO2 = new wxCheckBox(Panel1, ID_CHECKBOX10, _T("GPIO_2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
	chkGPIO2->SetValue(false);
	chkGPIO2->Disable();
	FlexGridSizer1->Add(chkGPIO2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkGPIO3 = new wxCheckBox(Panel1, ID_CHECKBOX11, _T("GPIO_3"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
	chkGPIO3->SetValue(false);
	chkGPIO3->Disable();
	FlexGridSizer1->Add(chkGPIO3, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkGPIO4 = new wxCheckBox(Panel1, ID_CHECKBOX12, _T("GPIO_4"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
	chkGPIO4->SetValue(false);
	chkGPIO4->Disable();
	FlexGridSizer1->Add(chkGPIO4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkGPIO5 = new wxCheckBox(Panel1, ID_CHECKBOX13, _T("GPIO_5"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX13"));
	chkGPIO5->SetValue(false);
	chkGPIO5->Disable();
	FlexGridSizer1->Add(chkGPIO5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkGPIO6 = new wxCheckBox(Panel1, ID_CHECKBOX14, _T("GPIO_6"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX14"));
	chkGPIO6->SetValue(false);
	chkGPIO6->Disable();
	FlexGridSizer1->Add(chkGPIO6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkGPIO7 = new wxCheckBox(Panel1, ID_CHECKBOX15, _T("GPIO_7"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX15"));
	chkGPIO7->SetValue(false);
	chkGPIO7->Disable();
	FlexGridSizer1->Add(chkGPIO7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer1->Add(FlexGridSizer1, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _T("Buffers"));
	chkDIO_DIR_CTRL1 = new wxCheckBox(Panel1, ID_CHECKBOX1, _T("DIO_DIR_CTRL1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkDIO_DIR_CTRL1->SetValue(false);
	StaticBoxSizer2->Add(chkDIO_DIR_CTRL1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkDIO_DIR_CTRL2 = new wxCheckBox(Panel1, ID_CHECKBOX2, _T("DIO_DIR_CTRL2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	chkDIO_DIR_CTRL2->SetValue(false);
	StaticBoxSizer2->Add(chkDIO_DIR_CTRL2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkDIO_BUFF_OE = new wxCheckBox(Panel1, ID_CHECKBOX3, _T("DIO_BUFF_OE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	chkDIO_BUFF_OE->SetValue(false);
	StaticBoxSizer2->Add(chkDIO_BUFF_OE, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkIQSEL1_DIR = new wxCheckBox(Panel1, ID_CHECKBOX4, _T("IQSEL1_DIR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	chkIQSEL1_DIR->SetValue(false);
	StaticBoxSizer2->Add(chkIQSEL1_DIR, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkIQSEL2_DIR = new wxCheckBox(Panel1, ID_CHECKBOX5, _T("IQSEL2_DIR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
	chkIQSEL2_DIR->SetValue(false);
	StaticBoxSizer2->Add(chkIQSEL2_DIR, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkG_PWR_DWN = new wxCheckBox(Panel1, ID_CHECKBOX6, _T("G_PWR_DWN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
	chkG_PWR_DWN->SetValue(false);
	StaticBoxSizer2->Add(chkG_PWR_DWN, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	chkDIG_RST = new wxCheckBox(Panel1, ID_CHECKBOX7, _T("DIG_RST"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
	chkDIG_RST->SetValue(false);
	chkDIG_RST->Hide();
	StaticBoxSizer2->Add(chkDIG_RST, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(StaticBoxSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	Panel1->SetSizer(FlexGridSizer2);
	FlexGridSizer2->Fit(Panel1);
	FlexGridSizer2->SetSizeHints(Panel1);
	btnU45_0 = new SocketBoardButton(this, ID_BUTTON25, _T("->"), wxPoint(312,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON25"));
	btnU45_1 = new SocketBoardButton(this, ID_BUTTON26, _T("->"), wxPoint(312,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON26"));
	btnU48_0 = new SocketBoardButton(this, ID_BUTTON27, _T("->"), wxPoint(312,56), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON27"));
	btnU48_1 = new SocketBoardButton(this, ID_BUTTON28, _T("->"), wxPoint(312,80), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON28"));
	btnU39_0 = new SocketBoardButton(this, ID_BUTTON29, _T("->"), wxPoint(312,112), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON29"));
	btnU39_1 = new SocketBoardButton(this, ID_BUTTON30, _T("->"), wxPoint(312,136), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON30"));

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_1);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_3);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_2);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_0);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_0);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_1);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_2);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_3);
	Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_0);
	Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_1);
	Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_2);
	Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU37_3);
	Connect(ID_BUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU43_0);
	Connect(ID_BUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU43_1);
	Connect(ID_BUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU43_2);
	Connect(ID_BUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU43_3);
	Connect(ID_BUTTON17,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU47_0);
	Connect(ID_BUTTON18,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU47_1);
	Connect(ID_BUTTON19,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU47_0);
	Connect(ID_BUTTON20,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU47_1);
	Connect(ID_BUTTON21,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU47_0);
	Connect(ID_BUTTON22,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU47_1);
	Connect(ID_BUTTON23,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU47_0);
	Connect(ID_BUTTON24,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnU47_1);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnchkDIO_DIR_CTRL1Click);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnchkDIO_DIR_CTRL2Click);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnchkDIO_BUFF_OEClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnchkIQSEL1_DIRClick);
	Connect(ID_CHECKBOX5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnchkIQSEL2_DIRClick);
	Connect(ID_CHECKBOX6,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnchkG_PWR_DWNClick);
	Connect(ID_CHECKBOX7,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnchkDIG_RSTClick);
	Connect(ID_BUTTON25,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnbtnU45_0Click);
	Connect(ID_BUTTON26,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnbtnU45_1Click);
	Connect(ID_BUTTON27,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnbtnU48_0Click);
	Connect(ID_BUTTON28,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnbtnU48_1Click);
	Connect(ID_BUTTON29,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnbtnU39_0Click);
	Connect(ID_BUTTON30,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlSocketBoard::OnbtnU39_1Click);
	//*)
}

pnlSocketBoard::~pnlSocketBoard()
{
	//(*Destroy(pnlSocketBoard)
	//*)
}

void pnlSocketBoard::Initialize(LMS7002_MainControl *pControl)
{
    wxButton *btn = NULL;
    int btnHeight = 0;
    int btnWidth = 0;
    lmsControl = pControl;
    ObjectMux mux;
    mux.controlsCount = 1;
    mux.totalStates = 2;
    mux.mirrored = true;
    mux.name = "U48";
    mux.pos = wxPoint(90, 120);
    muxes[mux.name] = mux;
    btn = btnU48_0;
    btn->SetSize(20, 20);
    btn->SetPosition( muxes[mux.name].GetOutputPos(0)-wxPoint(20, 10));
    btn = btnU48_1;
    btn->SetSize(20, 20);
    btn->SetPosition( muxes[mux.name].GetOutputPos(1)-wxPoint(20, 10));


    mux.name = "U39";
    mux.pos = wxPoint(180, 120);
    mux.mirrored = false;
    muxes[mux.name] = mux;
    btn = btnU39_0;
    btn->SetSize(20, 20);
    btn->SetPosition( muxes[mux.name].GetOutputPos(0)-wxPoint(0, 10));
    btn = btnU39_1;
    btn->SetSize(20, 20);
    btn->SetPosition( muxes[mux.name].GetOutputPos(1)-wxPoint(0, 10));

    mux.pos = wxPoint(325, 180);
    mux.name = "U38";
    mux.totalStates = 4;
    mux.controlsCount = 2;
    muxes[mux.name] = mux;
    btn = btnU38_0;
    btnHeight = btn->GetSize().y;
    btnWidth = btn->GetSize().x;
    btn->SetPosition( muxes[mux.name].GetOutputPos(0)-wxPoint(0, btnHeight/2));
    btn = btnU38_1;
    btn->SetPosition( muxes[mux.name].GetOutputPos(1)-wxPoint(0, btnHeight/2));
    btn = btnU38_2;
    btn->SetPosition( muxes[mux.name].GetOutputPos(2)-wxPoint(0, btnHeight/2));
    btn = btnU38_3;
    btn->SetPosition( muxes[mux.name].GetOutputPos(3)-wxPoint(0, btnHeight/2));

    mux.pos = wxPoint(325, 20);
    mux.name = "U37";
    mux.totalStates = 4;
    mux.controlsCount = 2;
    muxes[mux.name] = mux;
    btn = btnU37_0;
    btn->SetPosition( muxes[mux.name].GetOutputPos(0)-wxPoint(0, btnHeight/2));
    btn = btnU37_1;
    btn->SetPosition( muxes[mux.name].GetOutputPos(1)-wxPoint(0, btnHeight/2));
    btn = btnU37_2;
    btn->SetPosition( muxes[mux.name].GetOutputPos(2)-wxPoint(0, btnHeight/2));
    btn = btnU37_3;
    btn->SetPosition( muxes[mux.name].GetOutputPos(3)-wxPoint(0, btnHeight/2));

    mux.pos = wxPoint(650, 20);
    mux.name = "U42";
    mux.totalStates = 4;
    mux.controlsCount = 2;
    mux.mirrored = true;
    muxes[mux.name] = mux;
    btn = btnU42_0;
    btn->SetPosition( muxes[mux.name].GetOutputPos(0)-wxPoint(btnWidth, btnHeight/2));
    btn = btnU42_1;
    btn->SetPosition( muxes[mux.name].GetOutputPos(1)-wxPoint(btnWidth, btnHeight/2));
    btn = btnU42_2;
    btn->SetPosition( muxes[mux.name].GetOutputPos(2)-wxPoint(btnWidth, btnHeight/2));
    btn = btnU42_3;
    btn->SetPosition( muxes[mux.name].GetOutputPos(3)-wxPoint(btnWidth, btnHeight/2));

    mux.pos = wxPoint(650, 180);
    mux.name = "U43";
    mux.totalStates = 4;
    mux.controlsCount = 2;
    mux.mirrored = true;
    muxes[mux.name] = mux;
    btn = btnU43_0;
    btn->SetPosition( muxes[mux.name].GetOutputPos(0)-wxPoint(btnWidth, btnHeight/2));
    btn = btnU43_1;
    btn->SetPosition( muxes[mux.name].GetOutputPos(1)-wxPoint(btnWidth, btnHeight/2));
    btn = btnU43_2;
    btn->SetPosition( muxes[mux.name].GetOutputPos(2)-wxPoint(btnWidth, btnHeight/2));
    btn = btnU43_3;
    btn->SetPosition( muxes[mux.name].GetOutputPos(3)-wxPoint(btnWidth, btnHeight/2));

    mux.pos = wxPoint(800, 120);
    mux.name = "U45";
    mux.totalStates = 2;
    mux.controlsCount = 1;
    mux.mirrored = true;
    muxes[mux.name] = mux;
    btn = btnU45_0;
    btn->SetSize(20, 20);
    btn->SetPosition( muxes[mux.name].GetOutputPos(0)-wxPoint(20, 10));
    btn = btnU45_1;
    btn->SetSize(20, 20);
    btn->SetPosition( muxes[mux.name].GetOutputPos(1)-wxPoint(20, 10));

    mux.pos = wxPoint(325, 320);
    mux.name = "U47";
    mux.totalStates = 2;
    mux.controlsCount = 1;
    mux.mirrored = true;
    muxes[mux.name] = mux;
    btn = btnU47_0;
    btn->SetPosition( muxes[mux.name].GetOutputPos(0)-wxPoint(btnWidth, btnHeight/2));
    btn = btnU47_1;
    btn->SetPosition( muxes[mux.name].GetOutputPos(1)-wxPoint(btnWidth, btnHeight/2));

    mux.pos = wxPoint(325, 440);
    mux.name = "U44";
    muxes[mux.name] = mux;
    btn = btnU44_0;
    btn->SetPosition( muxes[mux.name].GetOutputPos(0)-wxPoint(btnWidth, btnHeight/2));
    btn = btnU44_1;
    btn->SetPosition( muxes[mux.name].GetOutputPos(1)-wxPoint(btnWidth, btnHeight/2));


    mux.pos = wxPoint(650, 320);
    mux.name = "U41";
    muxes[mux.name] = mux;
    btn = btnU41_0;
    btn->SetPosition( muxes[mux.name].GetOutputPos(0)-wxPoint(btnWidth, btnHeight/2));
    btn = btnU41_1;
    btn->SetPosition( muxes[mux.name].GetOutputPos(1)-wxPoint(btnWidth, btnHeight/2));

    mux.pos = wxPoint(650, 440);
    mux.name = "U40";
    muxes[mux.name] = mux;
    btn = btnU40_0;
    btn->SetPosition( muxes[mux.name].GetOutputPos(0)-wxPoint(btnWidth, btnHeight/2));
    btn = btnU40_1;
    btn->SetPosition( muxes[mux.name].GetOutputPos(1)-wxPoint(btnWidth, btnHeight/2));

    SocketBoardButton *sym = new SocketBoardButton(this, wxNewId(), _T("X9 UFL"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("x9 UFL"));
    sym->SetPosition(muxes["U48"].GetOutputPos(0) - wxPoint(btnWidth, btnHeight/2) );
    sym->type = 1;
    sym->mirrored = true;

    sym = new SocketBoardButton(this, wxNewId(), _T("X2 SMA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("x2 SMA"));
    sym->SetPosition(muxes["U48"].GetOutputPos(1) - wxPoint(btnWidth, btnHeight/2) );
    sym->type = 1;
    sym->mirrored = true;

    sym = new SocketBoardButton(this, wxNewId(), _T("X8 SMA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("x8 SMA"));
    sym->SetPosition(muxes["U47"].GetInputPos() - wxPoint(0, btnHeight/2) );
    sym->type = 1;

    sym = new SocketBoardButton(this, wxNewId(), _T("X4 SMA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("x4 SMA"));
    sym->SetPosition(muxes["U44"].GetInputPos() - wxPoint(0, btnHeight/2) );
    sym->type = 1;

    sym = new SocketBoardButton(this, wxNewId(), _T("X3 SMA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("x3 SMA"));
    sym->SetPosition(muxes["U41"].GetInputPos() - wxPoint(0, btnHeight/2) );
    sym->type = 1;

    sym = new SocketBoardButton(this, wxNewId(), _T("X1 SMA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("x1 SMA"));
    sym->SetPosition(muxes["U40"].GetInputPos() - wxPoint(0, btnHeight/2) );
    sym->type = 1;

    sym = new SocketBoardButton(this, wxNewId(), _T("X5 SMA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("x5 SMA"));
    sym->SetPosition(muxes["U45"].GetInputPos() - wxPoint(0, btnHeight/2) );
    sym->type = 1;

    links.push_back( pair<wxPoint,wxPoint>(muxes["U48"].GetInputPos(), muxes["U39"].GetInputPos()) );
    links.push_back( pair<wxPoint,wxPoint>(muxes["U39"].GetOutputPos(0), muxes["U38"].GetInputPos()) );
    links.push_back( pair<wxPoint,wxPoint>(muxes["U39"].GetOutputPos(1), muxes["U37"].GetInputPos()) );

    links.push_back( pair<wxPoint,wxPoint>(muxes["U42"].GetInputPos(), muxes["U45"].GetOutputPos(0)) );
    links.push_back( pair<wxPoint,wxPoint>(muxes["U43"].GetInputPos(), muxes["U45"].GetOutputPos(1)) );

}

void pnlSocketBoard::UpdateGUI()
{
    ReadbackGPIOStates();
    Refresh();
}

void pnlSocketBoard::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    dc.Clear();
    map< string, ObjectMux >::iterator iter;

    DrawMUX(dc, muxes["U38"], (gpioStates[0] & 0x03));
    DrawMUX(dc, muxes["U37"], (gpioStates[0] & 0x03));
    DrawMUX(dc, muxes["U48"], !((gpioStates[0] >> 7) & 0x01));
    DrawMUX(dc, muxes["U39"], !((gpioStates[0] >> 2) & 0x01));
    DrawMUX(dc, muxes["U42"], (gpioStates[0] & 0x03));
    DrawMUX(dc, muxes["U43"], ((gpioStates[0] >> 3) & 0x03));
    DrawMUX(dc, muxes["U45"], !((gpioStates[0] >> 5) & 0x01));
    DrawMUX(dc, muxes["U47"], !((gpioStates[0] >> 6) & 0x01));
    DrawMUX(dc, muxes["U44"], !((gpioStates[0] >> 6) & 0x01));
    DrawMUX(dc, muxes["U41"], !((gpioStates[0] >> 6) & 0x01));
    DrawMUX(dc, muxes["U40"], !((gpioStates[0] >> 6) & 0x01));

    for(unsigned int i=0; i<links.size(); ++i)
        DrawLink( dc, links[i].first, links[i].second );
}

void pnlSocketBoard::OnEraseBackground(wxEraseEvent& event)
{
}

void pnlSocketBoard::OnbtnGNDClick(wxCommandEvent& event)
{
    gpioStates[0] = 0;
    gpioStates[1] = 0;
    Refresh();
}

void pnlSocketBoard::OnbtnLNAW_A1Click(wxCommandEvent& event)
{
    gpioStates[0] = 1;
    gpioStates[1] = 0;
    Refresh();
}

void pnlSocketBoard::OnbtnLNAW_A2Click(wxCommandEvent& event)
{
    gpioStates[0] = 0;
    gpioStates[1] = 1;
    Refresh();
}

void pnlSocketBoard::OnbtnLNAW_A3Click(wxCommandEvent& event)
{
    gpioStates[0] = 1;
    gpioStates[1] = 1;
    Refresh();
}

void pnlSocketBoard::DrawMUX(wxPaintDC &dc, const ObjectMux &mux, int state)
{
    int pinDistance = mux.pinDistance;
    int pinMarginOffset = mux.pinMarginOffset;
    int pinRadius = mux.pinRadius;
    int width = mux.width;
    int height = (mux.totalStates+1)*pinDistance;
    wxPoint pos = mux.pos;
    dc.DrawRectangle(pos, wxSize(width, height));
    wxSize sztxt = dc.GetTextExtent(mux.name);
    dc.DrawText(mux.name, pos.x, pos.y-sztxt.y);

    wxPoint inputPos;
    if(!mux.mirrored)
    {
    dc.DrawLine(pos.x-pinMarginOffset, pos.y+height/2, pos.x+pinMarginOffset, pos.y+height/2);
    inputPos = wxPoint(pos.x+pinMarginOffset, pos.y+height/2);
    dc.SetBrush(*wxBLACK_BRUSH);
    dc.DrawCircle(inputPos.x, inputPos.y, pinRadius);
    dc.SetBrush(*wxWHITE_BRUSH);
    sztxt = dc.GetTextExtent("RFC");
    dc.DrawText("RFC", inputPos.x-pinMarginOffset, inputPos.y-sztxt.y);
    }
    else
    {
    dc.DrawLine(pos.x+width-pinMarginOffset, pos.y+height/2, pos.x+width+pinMarginOffset, pos.y+height/2);
    inputPos = wxPoint(pos.x+width-pinMarginOffset, pos.y+height/2);
    dc.SetBrush(*wxBLACK_BRUSH);
    dc.DrawCircle(inputPos.x, inputPos.y, pinRadius);
    dc.SetBrush(*wxWHITE_BRUSH);
    wxSize sztxt = dc.GetTextExtent("RFC");
    dc.DrawText("RFC", pos.x+width-sztxt.x, inputPos.y-sztxt.y);
    }

    for(int i=0; i<mux.totalStates; ++i)
    {
        if(mux.mirrored)
        {
        dc.DrawLine(pos.x+pinMarginOffset, pos.y+pinDistance*(i+1),pos.x-pinMarginOffset, pos.y+pinDistance*(i+1));
        wxPoint pinPos(pos.x+pinMarginOffset, pos.y+pinDistance*(i+1));
        dc.SetBrush(*wxBLACK_BRUSH);
        dc.DrawCircle(pinPos.x, pinPos.y , pinRadius);
        dc.SetBrush(*wxWHITE_BRUSH);
        wxString name = wxString::Format("RF%i", i+1);
        wxSize sztxt = dc.GetTextExtent(name);
        dc.DrawText(name, pos.x, pos.y+pinDistance*(i+1)-sztxt.y);
        if(i==state)
            dc.DrawLine(inputPos, pinPos);
        }
        else
        {
        dc.DrawLine(pos.x+width+pinMarginOffset, pos.y+pinDistance*(i+1),pos.x+width-pinMarginOffset, pos.y+pinDistance*(i+1));
        wxPoint pinPos(pos.x+width-pinMarginOffset, pos.y+pinDistance*(i+1));
        dc.SetBrush(*wxBLACK_BRUSH);
        dc.DrawCircle(pinPos.x, pinPos.y , pinRadius);
        dc.SetBrush(*wxWHITE_BRUSH);
        wxString name = wxString::Format("RF%i", i+1);
        wxSize sztxt = dc.GetTextExtent(name);
        dc.DrawText(name, pos.x+width-sztxt.x, pos.y+pinDistance*(i+1)-sztxt.y);
        if(i==state)
            dc.DrawLine(inputPos, pinPos);
        }
    }
}

void pnlSocketBoard::DrawLink(wxPaintDC &dc, wxPoint a, wxPoint b)
{
    dc.DrawLine(a, b);
}

void pnlSocketBoard::OnU37_0(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 0, 0);
    gpioStates[0] = setbit(gpioStates[0], 1, 0);
    SendCommand();
}

void pnlSocketBoard::OnU37_1(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 0, 1);
    gpioStates[0] = setbit(gpioStates[0], 1, 0);
    SendCommand();
}

void pnlSocketBoard::OnU37_2(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 0, 0);
    gpioStates[0] = setbit(gpioStates[0], 1, 1);
    SendCommand();
}

void pnlSocketBoard::OnU37_3(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 0, 1);
    gpioStates[0] = setbit(gpioStates[0], 1, 1);
    SendCommand();
}

void pnlSocketBoard::OnU43_0(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 3, 0);
    gpioStates[0] = setbit(gpioStates[0], 4, 0);
    SendCommand();
}

void pnlSocketBoard::OnU43_1(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 3, 1);
    gpioStates[0] = setbit(gpioStates[0], 4, 0);
    SendCommand();
}

void pnlSocketBoard::OnU43_2(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 3, 0);
    gpioStates[0] = setbit(gpioStates[0], 4, 1);
    SendCommand();
}

void pnlSocketBoard::OnU43_3(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 3, 1);
    gpioStates[0] = setbit(gpioStates[0], 4, 1);
    SendCommand();
}

void pnlSocketBoard::OnU47_0(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 6, 1);
    SendCommand();
}

void pnlSocketBoard::OnU47_1(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 6, 0);
    SendCommand();
}

int pnlSocketBoard::SendCommand()
{
    Refresh();
    int status = lmsControl->SetGPIOStates(gpioStates);
    UpdateGUI();
    return status;
}

int pnlSocketBoard::ReadbackGPIOStates()
{
    lmsControl->GetGPIOStates(gpioStates);
    chkDIG_RST->SetValue(getbit(gpioStates[1], 6));
    chkDIO_BUFF_OE->SetValue(getbit(gpioStates[1], 2));
    chkDIO_DIR_CTRL1->SetValue(getbit(gpioStates[1], 0));
    chkDIO_DIR_CTRL2->SetValue(getbit(gpioStates[1], 1));
    chkIQSEL1_DIR->SetValue(getbit(gpioStates[1], 3));
    chkIQSEL2_DIR->SetValue(getbit(gpioStates[1], 4));
    chkG_PWR_DWN->SetValue(getbit(gpioStates[1], 5));

    chkGPIO0->SetValue(getbit(gpioStates[0], 0));
    chkGPIO1->SetValue(getbit(gpioStates[0], 1));
    chkGPIO2->SetValue(getbit(gpioStates[0], 2));
    chkGPIO3->SetValue(getbit(gpioStates[0], 3));
    chkGPIO4->SetValue(getbit(gpioStates[0], 4));
    chkGPIO5->SetValue(getbit(gpioStates[0], 5));
    chkGPIO6->SetValue(getbit(gpioStates[0], 6));
    chkGPIO7->SetValue(getbit(gpioStates[0], 7));
    Refresh();
    return 0;
}

void pnlSocketBoard::OnchkDIO_DIR_CTRL1Click(wxCommandEvent& event)
{
    gpioStates[1] = setbit(gpioStates[1], 0, chkDIO_DIR_CTRL1->GetValue());
    SendCommand();
}

void pnlSocketBoard::OnchkDIO_DIR_CTRL2Click(wxCommandEvent& event)
{
    gpioStates[1] = setbit(gpioStates[1], 1, chkDIO_DIR_CTRL2->GetValue());
    SendCommand();
}

void pnlSocketBoard::OnchkDIO_BUFF_OEClick(wxCommandEvent& event)
{
    gpioStates[1] = setbit(gpioStates[1], 2, chkDIO_BUFF_OE->GetValue());
    SendCommand();
}

void pnlSocketBoard::OnchkIQSEL1_DIRClick(wxCommandEvent& event)
{
    gpioStates[1] = setbit(gpioStates[1], 3, chkIQSEL1_DIR->GetValue());
    SendCommand();
}

void pnlSocketBoard::OnchkIQSEL2_DIRClick(wxCommandEvent& event)
{
    gpioStates[1] = setbit(gpioStates[1], 4, chkIQSEL2_DIR->GetValue());
    SendCommand();
}

void pnlSocketBoard::OnchkG_PWR_DWNClick(wxCommandEvent& event)
{
    gpioStates[1] = setbit(gpioStates[1], 5, chkG_PWR_DWN->GetValue());
    SendCommand();
}

void pnlSocketBoard::OnchkDIG_RSTClick(wxCommandEvent& event)
{
    gpioStates[1] = setbit(gpioStates[1], 6, chkDIG_RST->GetValue());
    SendCommand();
}

void pnlSocketBoard::OnbtnU45_0Click(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 5, 1);
    SendCommand();
}

void pnlSocketBoard::OnbtnU45_1Click(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 5, 0);
    SendCommand();
}

void pnlSocketBoard::OnbtnU48_0Click(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 7, 1);
    SendCommand();
}

void pnlSocketBoard::OnbtnU48_1Click(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 7, 0);
    SendCommand();
}

void pnlSocketBoard::OnbtnU39_0Click(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 2, 1);
    SendCommand();
}

void pnlSocketBoard::OnbtnU39_1Click(wxCommandEvent& event)
{
    gpioStates[0] = setbit(gpioStates[0], 2, 0);
    SendCommand();
}

unsigned char pnlSocketBoard::setbit(const unsigned char src, const int pos, const bool value)
{
    int val = src;
    val = val & ~(0x1 << pos);
    val |= value << pos;
    return val;
}

bool pnlSocketBoard::getbit(const unsigned char src, const int pos)
{
    return (src >> pos) & 0x01;
}
