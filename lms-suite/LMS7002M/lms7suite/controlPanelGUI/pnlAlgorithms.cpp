/**
@file	pnlAlgorithms.cpp
@author Lime Microsystems
@brief	panel for calibration algorithms
*/
#include "pnlAlgorithms.h"

//(*InternalHeaders(pnlAlgorithms)
#include <wx/string.h>
//*)

//(*IdInit(pnlAlgorithms)
const long pnlAlgorithms::ID_STATICTEXT3 = wxNewId();
const long pnlAlgorithms::ID_GCORRQ_RXTSP = wxNewId();
const long pnlAlgorithms::ID_STATICTEXT10 = wxNewId();
const long pnlAlgorithms::ID_GCORRI_RXTSP = wxNewId();
const long pnlAlgorithms::ID_STATICTEXT11 = wxNewId();
const long pnlAlgorithms::ID_IQCORR_RXTSP = wxNewId();
const long pnlAlgorithms::ID_STATICTEXT6 = wxNewId();
const long pnlAlgorithms::ID_DCOFFI_RFE = wxNewId();
const long pnlAlgorithms::ID_STATICTEXT7 = wxNewId();
const long pnlAlgorithms::ID_DCOFFQ_RFE = wxNewId();
const long pnlAlgorithms::ID_EN_DCOFF_RXFE_RFE = wxNewId();
const long pnlAlgorithms::ID_BUTTON1 = wxNewId();
const long pnlAlgorithms::ID_STATICTEXT4 = wxNewId();
const long pnlAlgorithms::ID_GCORRQ_TXTSP = wxNewId();
const long pnlAlgorithms::ID_STATICTEXT5 = wxNewId();
const long pnlAlgorithms::ID_GCORRI_TXTSP = wxNewId();
const long pnlAlgorithms::ID_STATICTEXT2 = wxNewId();
const long pnlAlgorithms::ID_IQCORR_TXTSP = wxNewId();
const long pnlAlgorithms::ID_STATICTEXT1 = wxNewId();
const long pnlAlgorithms::ID_DCCORRI_TXTSP = wxNewId();
const long pnlAlgorithms::ID_STATICTEXT9 = wxNewId();
const long pnlAlgorithms::ID_DCCORRQ_TXTSP = wxNewId();
const long pnlAlgorithms::ID_BUTTON10 = wxNewId();
const long pnlAlgorithms::ID_BUTTON3 = wxNewId();
const long pnlAlgorithms::ID_BUTTON4 = wxNewId();
const long pnlAlgorithms::ID_BUTTON5 = wxNewId();
const long pnlAlgorithms::ID_BUTTON6 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlAlgorithms,wxPanel)
	//(*EventTable(pnlAlgorithms)
	//*)
END_EVENT_TABLE()

void pnlAlgorithms::AssignEnumsToIds()
{
    //RX DC
    wndId2Enum[ID_DCOFFI_RFE] = DCOFFI_RFE;
    wndId2Enum[ID_DCOFFQ_RFE] = DCOFFQ_RFE;
    wndId2Enum[ID_EN_DCOFF_RXFE_RFE] = EN_DCOFF_RXFE_RFE;

    //TX DC
    wndId2Enum[ID_DCCORRI_TXTSP] = DCCORRI_TXTSP;
    wndId2Enum[ID_DCCORRQ_TXTSP] = DCCORRQ_TXTSP;

    //TX IQ
    wndId2Enum[ID_GCORRI_TXTSP] = GCORRI_TXTSP;
    wndId2Enum[ID_GCORRQ_TXTSP] = GCORRQ_TXTSP;
    wndId2Enum[ID_IQCORR_TXTSP] = IQCORR_TXTSP;

    //RX IQ
    wndId2Enum[ID_GCORRI_RXTSP] = GCORRI_RXTSP;
    wndId2Enum[ID_GCORRQ_RXTSP] = GCORRQ_RXTSP;
    wndId2Enum[ID_IQCORR_RXTSP] = IQCORR_RXTSP;

}

pnlAlgorithms::pnlAlgorithms(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
	BuildContent(parent,id,pos,size);
	AssignEnumsToIds();
}

void pnlAlgorithms::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlAlgorithms)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* DC3Sizer;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* IQCorrectorSizer;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* IQCorrector2Sizer;
	wxFlexGridSizer* FlexGridSizer8;
	wxStaticBoxSizer* DCCorrectorSizer;
	wxFlexGridSizer* DCCorrector4Sizer;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStaticBoxSizer* DCSizer;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Receiver"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _T("RX IQ Corrector"));
	FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 5);
	FlexGridSizer5->AddGrowableCol(1);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT3, _T("Gain ch. Q"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer5->Add(StaticText9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	cmbGCORRQ_RXTSP = new ComboBoxMap(this, ID_GCORRQ_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GCORRQ_RXTSP"));
	cmbGCORRQ_RXTSP->SetToolTip(_T("corrector value, channel Q Unsigned integer"));
	FlexGridSizer5->Add(cmbGCORRQ_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _T("Gain ch. I"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer5->Add(StaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	cmbGCORRI_RXTSP = new ComboBoxMap(this, ID_GCORRI_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_GCORRI_RXTSP"));
	cmbGCORRI_RXTSP->SetToolTip(_T("corrector value, channel I Unsigned integer"));
	FlexGridSizer5->Add(cmbGCORRI_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText11 = new wxStaticText(this, ID_STATICTEXT11, _T("Phase corrector"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer5->Add(StaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	cmbIQCORR_RXTSP = new ComboBoxMap(this, ID_IQCORR_RXTSP, wxEmptyString, wxDefaultPosition, wxSize(64,-1), 0, 0, 0, wxDefaultValidator, _T("ID_IQCORR_RXTSP"));
	cmbIQCORR_RXTSP->SetToolTip(_T("Phase corrector value (tan(Alpha/2)). Integer, 2\'s complement"));
	FlexGridSizer5->Add(cmbIQCORR_RXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticBoxSizer3->Add(FlexGridSizer5, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer3->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	DCSizer = new wxStaticBoxSizer(wxVERTICAL, this, _T("RX DC"));
	DC3Sizer = new wxFlexGridSizer(0, 2, 0, 5);
	DC3Sizer->AddGrowableCol(1);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT6, _T("Offset I side"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	DC3Sizer->Add(StaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	cmbDCOFFI_RFE = new ComboBoxMap(this, ID_DCOFFI_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DCOFFI_RFE"));
	cmbDCOFFI_RFE->SetToolTip(_T("Controls DC offset at the output of the TIA by injecting current to the input of the TIA (I side)"));
	DC3Sizer->Add(cmbDCOFFI_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT7, _T("Offset Q side"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	DC3Sizer->Add(StaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	cmbDCOFFQ_RFE = new ComboBoxMap(this, ID_DCOFFQ_RFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DCOFFQ_RFE"));
	cmbDCOFFQ_RFE->SetToolTip(_T("Controls DC offset at the output of the TIA by injecting current to the input of the TIA (Q side)"));
	DC3Sizer->Add(cmbDCOFFQ_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	chkEN_DCOFF_RXFE_RFE = new wxCheckBox(this, ID_EN_DCOFF_RXFE_RFE, _T("DCOFFSET"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_DCOFF_RXFE_RFE"));
	chkEN_DCOFF_RXFE_RFE->SetValue(false);
	chkEN_DCOFF_RXFE_RFE->SetToolTip(_T("Enables the DCOFFSET block for the RXFE"));
	DC3Sizer->Add(chkEN_DCOFF_RXFE_RFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	DCSizer->Add(DC3Sizer, 0, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
	FlexGridSizer3->Add(DCSizer, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnCalibrateRXIQ = new wxButton(this, ID_BUTTON1, _T("Calibrate RX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(btnCalibrateRXIQ, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	StaticBoxSizer1->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Transmitter"));
	FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
	IQCorrectorSizer = new wxStaticBoxSizer(wxVERTICAL, this, _T("TX IQ Corrector"));
	IQCorrector2Sizer = new wxFlexGridSizer(0, 2, 0, 5);
	IQCorrector2Sizer->AddGrowableCol(0);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT4, _T("Gain ch. Q"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	IQCorrector2Sizer->Add(StaticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	cmbGCORRQ_TXTSP = new ComboBoxMap(this, ID_GCORRQ_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GCORRQ_TXTSP"));
	cmbGCORRQ_TXTSP->SetToolTip(_T("corrector value, channel Q Unsigned integer"));
	IQCorrector2Sizer->Add(cmbGCORRQ_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _T("Gain ch. I"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	IQCorrector2Sizer->Add(StaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	cmbGCORRI_TXTSP = new ComboBoxMap(this, ID_GCORRI_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GCORRI_TXTSP"));
	cmbGCORRI_TXTSP->SetToolTip(_T("corrector value, channel I Unsigned integer"));
	IQCorrector2Sizer->Add(cmbGCORRI_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("Phase corrector"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	IQCorrector2Sizer->Add(StaticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	cmbIQCORR_TXTSP = new ComboBoxMap(this, ID_IQCORR_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_IQCORR_TXTSP"));
	cmbIQCORR_TXTSP->SetToolTip(_T("Phase corrector value (tan(Alpha/2)). Integer, 2\'s complement"));
	IQCorrector2Sizer->Add(cmbIQCORR_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	IQCorrectorSizer->Add(IQCorrector2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(IQCorrectorSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	DCCorrectorSizer = new wxStaticBoxSizer(wxVERTICAL, this, _T("TX DC"));
	DCCorrector4Sizer = new wxFlexGridSizer(0, 2, 0, 5);
	DCCorrector4Sizer->AddGrowableCol(0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("DC ch. I"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	DCCorrector4Sizer->Add(StaticText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	cmbDCCORRI_TXTSP = new ComboBoxMap(this, ID_DCCORRI_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DCCORRI_TXTSP"));
	cmbDCCORRI_TXTSP->SetToolTip(_T("DC corrector value, channel I. Integer, 2\'s complement"));
	DCCorrector4Sizer->Add(cmbDCCORRI_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT9, _T("DC ch. Q"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	DCCorrector4Sizer->Add(StaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	cmbDCCORRQ_TXTSP = new ComboBoxMap(this, ID_DCCORRQ_TXTSP, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_DCCORRQ_TXTSP"));
	cmbDCCORRQ_TXTSP->SetToolTip(_T("DC corrector value, channel Q. Integer, 2\'s complement"));
	DCCorrector4Sizer->Add(cmbDCCORRQ_TXTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	DCCorrectorSizer->Add(DCCorrector4Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer4->Add(DCCorrectorSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnCalibrateTXIQ = new wxButton(this, ID_BUTTON10, _T("Calibrate TX"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
	FlexGridSizer4->Add(btnCalibrateTXIQ, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	StaticBoxSizer2->Add(FlexGridSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Full calibration"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
	btnCalibrateAll = new wxButton(this, ID_BUTTON3, _T("Calibrate ALL"), wxDefaultPosition, wxSize(150,50), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer6->Add(btnCalibrateAll, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer8 = new wxFlexGridSizer(0, 3, 0, 0);
	btnResetDemo = new wxButton(this, ID_BUTTON4, _T("Reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer8->Add(btnResetDemo, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	btnRepeatDemo = new wxButton(this, ID_BUTTON5, _T("Repeat"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer8->Add(btnRepeatDemo, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	btnNextDemo = new wxButton(this, ID_BUTTON6, _T("Next"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	FlexGridSizer8->Add(btnNextDemo, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	FlexGridSizer7->Add(FlexGridSizer8, 1, wxALL|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	sizerStages = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer7->Add(sizerStages, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	FlexGridSizer6->Add(FlexGridSizer7, 1, wxALL|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	StaticBoxSizer4->Add(FlexGridSizer6, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	FlexGridSizer1->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_GCORRQ_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAlgorithms::ParameterChangeHandler);
	Connect(ID_GCORRI_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAlgorithms::ParameterChangeHandler);
	Connect(ID_IQCORR_RXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAlgorithms::ParameterChangeHandler);
	Connect(ID_DCOFFI_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAlgorithms::ParameterChangeHandler);
	Connect(ID_DCOFFQ_RFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAlgorithms::ParameterChangeHandler);
	Connect(ID_EN_DCOFF_RXFE_RFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlAlgorithms::ParameterChangeHandler);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlAlgorithms::OnbtnCalibrateRXIQClick);
	Connect(ID_GCORRQ_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAlgorithms::ParameterChangeHandler);
	Connect(ID_GCORRI_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAlgorithms::ParameterChangeHandler);
	Connect(ID_IQCORR_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAlgorithms::ParameterChangeHandler);
	Connect(ID_DCCORRI_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAlgorithms::ParameterChangeHandler);
	Connect(ID_DCCORRQ_TXTSP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAlgorithms::ParameterChangeHandler);
	Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlAlgorithms::OnbtnCalibrateTXIQClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlAlgorithms::OnbtnCalibrateAllClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlAlgorithms::OnbtnResetDemoClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlAlgorithms::OnbtnRepeatDemoClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlAlgorithms::OnbtnNextDemoClick);
	//*)
}

pnlAlgorithms::~pnlAlgorithms()
{
	//(*Destroy(pnlAlgorithms)
	//*)
}

void pnlAlgorithms::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlRFE panel don't have control module assigned" << std::endl;
        return;
    }

    LMS7002_Parameter parameter;
    try
    {
        parameter = wndId2Enum.at(event.GetId());
    }
    catch( std::exception & e )
    {
        std::cout << "Control element(ID = " << event.GetId() << ") don't have assigned LMS parameter enumeration." << std::endl;
        return;
    }
    int evtint;
    float atangent;
    float angle;

    switch(parameter)
    {
    case IQCORR_TXTSP: // when changed recalculate alpha text field
        evtint = event.GetInt();
        atangent = atan( evtint/2048.0 );
        angle = atangent * 180/3.141596 * 2;
        //txtPhaseAlphaTx->SetLabel( wxString::Format("%f", angle));
        lmsControl->SetParam( parameter, event.GetInt());
        break;
    case IQCORR_RXTSP: // when changed recalculate alpha text field
        evtint = event.GetInt();
        atangent = atan( evtint/2048.0 );
        angle = atangent * 180/3.141596 * 2;
        //txtPhaseAlphaRx->SetLabel( wxString::Format("%f", angle));
        lmsControl->SetParam( parameter, event.GetInt());
        break;
    default:
        lmsControl->SetParam( parameter, event.GetInt());
        //std::cout << "control id " << event.GetId() << " value " << event.GetInt() << std::endl;
    }
}

void pnlAlgorithms::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;

    vector<string> temp;
    vector<cmbKeyValuePair> keyvalues;
    keyvalues.clear();
    char ctemp[1024];
    for(int i=63; i>=0; --i)
    {
        sprintf(ctemp, "%i", -i);
        keyvalues.push_back(cmbKeyValuePair(i|0x40,ctemp));
    }
    for(int i=0; i<64; ++i)
    {
        sprintf(ctemp, "%i", i);
        keyvalues.push_back(cmbKeyValuePair(i,ctemp));
    }
    cmbDCOFFI_RFE->Clear();
    cmbDCOFFI_RFE->Set(keyvalues);
    cmbDCOFFI_RFE->SetSelection( lmsControl->GetParam(DCOFFI_RFE));
    cmbDCOFFQ_RFE->Clear();
    cmbDCOFFQ_RFE->Set(keyvalues);
    cmbDCOFFQ_RFE->SetSelection( lmsControl->GetParam(DCOFFQ_RFE));

    keyvalues.clear();
    for(int i=-128; i<=127; ++i)
    {
        sprintf(ctemp, "%i", i);
        keyvalues.push_back(cmbKeyValuePair(i, ctemp));
    }
    cmbDCCORRI_TXTSP->Clear();
    cmbDCCORRI_TXTSP->Set(keyvalues);
    cmbDCCORRQ_TXTSP->Clear();
    cmbDCCORRQ_TXTSP->Set(keyvalues);

    keyvalues.clear();
    for(int i=-2048; i<2048; ++i)
    {
        sprintf(ctemp, "%i", i);
        keyvalues.push_back(cmbKeyValuePair(i, ctemp));
    }
    cmbIQCORR_TXTSP->Clear();
    cmbIQCORR_TXTSP->Set(keyvalues);
    cmbIQCORR_RXTSP->Clear();
    cmbIQCORR_RXTSP->Set(keyvalues);

    temp.clear();
    for(int i=0; i<2048; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGCORRI_TXTSP->Clear();
    cmbGCORRI_TXTSP->Append(temp);
    cmbGCORRI_RXTSP->Append(temp);
    //cmbGCORRI_TXTSP->SetSelection( lmsControl->GetParam(GCORRI_TXTSP));

    temp.clear();
    for(int i=0; i<2048; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbGCORRQ_TXTSP->Clear();
    cmbGCORRQ_TXTSP->Append(temp);
    cmbGCORRQ_RXTSP->Append(temp);

    InitDemoStages();
}

void pnlAlgorithms::UpdateGUI()
{
    unsigned long value;
    value = lmsControl->GetParam(DCOFFI_RFE, true, false);
    cmbDCOFFI_RFE->SetSelection(value);
    value = lmsControl->GetParam(DCOFFQ_RFE, true, false);
    cmbDCOFFQ_RFE->SetSelection(value);

    value = lmsControl->GetParam(EN_DCOFF_RXFE_RFE, true, false);
    chkEN_DCOFF_RXFE_RFE->SetValue(value);

    value = lmsControl->GetParam(DCCORRI_TXTSP, true, false);
    cmbDCCORRI_TXTSP->SetSelection( (char)value);
    value = lmsControl->GetParam(DCCORRQ_TXTSP, true, false);
    cmbDCCORRQ_TXTSP->SetSelection( (char)value);

    value = lmsControl->GetParam(GCORRI_TXTSP, true, false);
    cmbGCORRI_TXTSP->SetSelection(value);
    value = lmsControl->GetParam(GCORRQ_TXTSP, true, false);
    cmbGCORRQ_TXTSP->SetSelection(value);

    value = lmsControl->GetParam(GCORRI_RXTSP, true, false);
    cmbGCORRI_RXTSP->SetSelection(value);
    value = lmsControl->GetParam(GCORRQ_RXTSP, true, false);
    cmbGCORRQ_RXTSP->SetSelection(value);

    value = lmsControl->GetParam(IQCORR_TXTSP, true, false);
    short iqcorr_val = value;
    iqcorr_val = (iqcorr_val & 0x800) ? iqcorr_val|0xF000 : iqcorr_val;
    cmbIQCORR_TXTSP->SetSelection(iqcorr_val);

    value = lmsControl->GetParam(IQCORR_RXTSP, true, false);
    iqcorr_val = value;
    iqcorr_val = (iqcorr_val & 0x800) ? iqcorr_val|0xF000 : iqcorr_val;
    cmbIQCORR_RXTSP->SetSelection(iqcorr_val);
}

void pnlAlgorithms::OnbtnCalibrateRXDCClick(wxCommandEvent& event)
{
    if(lmsControl->algorithms->DCCalibrationRX_RSSI(true) != 0)
        wxMessageBox(_("DC Calibration failed"),_("Error"),wxCLOSE,this);
    else
        wxMessageBox(_("DC Calibration Finished"),_("Info"),wxOK,this);
    lmsControl->DownloadAll();
    UpdateGUI();
}

void pnlAlgorithms::HandleMessage(const LMS_Message &msg)
{

}

void pnlAlgorithms::OnbtnCalibrateRXDCClick1(wxCommandEvent& event)
{
}

void pnlAlgorithms::OnbtnCalibrateDC_RFLOOPClick(wxCommandEvent& event)
{
    if(lmsControl->algorithms->DCCalibrationTX_RFLOOP(true) != 0)
        wxMessageBox(_("TX DC Calibration failed"),_("Error"),wxCLOSE,this);
    else
        wxMessageBox(_("TX DC Calibration Finished"),_("Info"),wxOK,this);
    lmsControl->DownloadAll();
    UpdateGUI();
    Notify(LMS_Message(MSG_UPDATE_ALL_GUI, "", 0, 0));
}

void pnlAlgorithms::OnbtnCalibrateRXIQClick(wxCommandEvent& event)
{
    if(lmsControl->algorithms->RXIQCalibration() != 0)
        wxMessageBox(_("IQ Calibration failed"),_("Error"),wxCLOSE,this);
    else
        wxMessageBox(_("IQ Calibration Finished"),_("Info"),wxOK,this);
    Notify(LMS_Message(MSG_UPDATE_ALL_GUI, "", 0, 0));
}

void pnlAlgorithms::OnbtnCalibrateTXIQClick(wxCommandEvent& event)
{
    if(lmsControl->algorithms->TXIQCalibration() != 0)
        wxMessageBox(_("IQ Calibration failed"),_("Error"),wxCLOSE,this);
    else
        wxMessageBox(_("IQ Calibration Finished"),_("Info"),wxOK,this);
    Notify(LMS_Message(MSG_UPDATE_ALL_GUI, "", 0, 0));
}

int stageCounter = 0;
void pnlAlgorithms::OnbtnCalibrateAllClick(wxCommandEvent& event)
{
    wxCommandEvent evt;
    if(stageCounter > 0)
        OnbtnResetDemoClick(evt);
    for(int i=0; i<11; ++i)
    {
        if(stageCounter == 0)
        btnResetDemo->Enable(true);

        lmsControl->algorithms->DemoCalibration(stageCounter++);
        ActivateStageName(stageCounter);
        if(stageCounter == 11)
            btnNextDemo->Enable(false);

        wxYield();
    }
    ActivateStageName(stageCounter+1);
    wxMessageBox(_("Calibration Finished"),_("Info"),wxOK,this);
    Notify(LMS_Message(MSG_UPDATE_ALL_GUI, "", 0, 0));
}

void pnlAlgorithms::OnbtnResetDemoClick(wxCommandEvent& event)
{
    if(stageCounter < 11)
        lmsControl->algorithms->DemoCalibration(9);
    btnResetDemo->Enable(false);
    btnNextDemo->Enable(true);
    ActivateStageName(0);
    stageCounter = 0;
}

void pnlAlgorithms::OnbtnRepeatDemoClick(wxCommandEvent& event)
{
    lmsControl->algorithms->DemoCalibration(stageCounter-1);
}

void pnlAlgorithms::OnbtnNextDemoClick(wxCommandEvent& event)
{
    if(stageCounter == 0)
        btnResetDemo->Enable(true);

    lmsControl->algorithms->DemoCalibration(stageCounter++);
    ActivateStageName(stageCounter);
    if(stageCounter == 11)
        btnNextDemo->Enable(false);
}

void pnlAlgorithms::InitDemoStages()
{
    vector<string> stages;
    stages.push_back("Save initial settings");
    stages.push_back("Setup parameters");
    stages.push_back("RX DC Calibration");
    stages.push_back("TX LO Calibration");
    stages.push_back("Reconfig");
    stages.push_back("TX IQ Gain");
    stages.push_back("TX IQ Phase");
    stages.push_back("RX IQ Gain");
    stages.push_back("RX IQ Phase");
    stages.push_back("Restore initial settings");
    stages.push_back("Load calibration values");
    for(int i=0; i<stages.size(); ++i)
    {
        mStageNames.push_back(new wxStaticText(this, wxID_ANY, wxString::Format("%i. %s", i+1, stages[i].c_str())));
        mStageNames[i]->Enable(false);
        sizerStages->Add(mStageNames[i], 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
    }
    btnResetDemo->Enable(false);
}

int pnlAlgorithms::ActivateStageName(int i)
{
    for(int j=0; j<mStageNames.size(); ++j)
        mStageNames[j]->Enable(false);
    for(int j=0; j<i && j < mStageNames.size(); ++j)
        mStageNames[j]->Enable(true);
	return 0;
}
