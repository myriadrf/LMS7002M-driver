/**
@file 	dlgExtraControls.cpp
@author Lime Microsystems
@brief	dialog for various extra controls
*/
#include "dlgExtraControls.h"

//(*InternalHeaders(dlgExtraControls)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgExtraControls)
//*)

#include <wx/button.h>

#include "ConnectionManager.h"
#include "SamplesCollector.h"

BEGIN_EVENT_TABLE(dlgExtraControls,wxDialog)
	//(*EventTable(dlgExtraControls)
	//*)
END_EVENT_TABLE()

dlgExtraControls::dlgExtraControls(wxWindow* parent, ConnectionManager *serPort, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_serPort = serPort;
    m_collector = NULL;
	BuildContent(parent,id,pos,size);
}

void dlgExtraControls::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgExtraControls)
	Create(parent, id, _("Extra controls"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxCLOSE_BOX, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	SetMinSize(wxSize(256,256));
	m_controlsSizer = new wxFlexGridSizer(0, 2, 0, 0);
	m_controlsSizer->AddGrowableCol(0);
	m_controlsSizer->AddGrowableCol(1);
	m_controlsSizer->AddGrowableRow(0);
	m_checkboxes = new wxFlexGridSizer(0, 1, 0, 0);
	m_controlsSizer->Add(m_checkboxes, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(m_controlsSizer);
	m_controlsSizer->Fit(this);
	m_controlsSizer->SetSizeHints(this);
	//*)
    //eLMS_DEV devtype = m_serPort->GetConnectedDeviceType();
	createControls(LMS_DEV_DIGIGREEN);
	m_controlsSizer->Fit(this);
}

dlgExtraControls::~dlgExtraControls()
{
	//(*Destroy(dlgExtraControls)
	//*)
}

void dlgExtraControls::createControls(int dev_type)
{
    wxArrayString choices;
    choices.Add("NCO");
    choices.Add("ADC");
    long id = wxNewId();
    rxDataSource = new wxRadioBox(this, id, "Rx Data Source", wxDefaultPosition, wxDefaultSize, choices, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, "Rx Data Source");
    rxDataSource->SetSelection(1);
    m_controlsSizer->Add(rxDataSource, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    Connect(id, wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&dlgExtraControls::onParamChange);

    choices.clear();
    choices.Add("DIQ1");
    choices.Add("DIQ2");
    channel_selection = new wxRadioBox(this, id, "Channel", wxDefaultPosition, wxDefaultSize, choices, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, "channel select");
    channel_selection->SetSelection(1);
    m_controlsSizer->Add(channel_selection, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    Connect(id, wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&dlgExtraControls::onParamChange);

    id = wxNewId();
    chkStream_txen = new wxCheckBox(this, id, "TxEN", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "TxEN");
    chkStream_txen->SetValue(true);
    m_checkboxes->Add(chkStream_txen, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgExtraControls::onParamChange);

    id = wxNewId();
    chkStream_rxen = new wxCheckBox(this, id, "RxEN", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, "RxEN");
    chkStream_rxen->SetValue(true);
    m_checkboxes->Add(chkStream_rxen, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    Connect(id, wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgExtraControls::onParamChange);
}

void dlgExtraControls::SetSamplesCollector(SamplesCollector *pCollector)
{
    m_collector = pCollector;
}

void dlgExtraControls::onParamChange(wxCommandEvent &evt)
{
    unsigned char ctrbuf[64];
    unsigned char inbuf[64];
    memset(ctrbuf, 0, 64);
    ctrbuf[0] = CMD_BRDSPI_RD;
    ctrbuf[1] = 0;
    ctrbuf[2] = 0x01;
    ctrbuf[8] = 0x00;
    ctrbuf[9] = 0x05;
    m_serPort->Port_write_direct(ctrbuf, 64);
    long len = 64;
    m_serPort->Port_read_direct(inbuf, len);
    memset(ctrbuf, 0, 64);
    ctrbuf[0] = CMD_BRDSPI_WR;
    ctrbuf[1] = 0;
    ctrbuf[2] = 0x01;
    ctrbuf[8] = 0x00;
    ctrbuf[9] = 0x05;
    ctrbuf[10] = inbuf[10];
    ctrbuf[11] = inbuf[11] & ~0x1e;
    ctrbuf[11] |= channel_selection->GetSelection() << 4;
    ctrbuf[11] |= rxDataSource->GetSelection() << 3;
    ctrbuf[11] |= chkStream_rxen->IsChecked() << 2;
    ctrbuf[11] |= chkStream_txen->IsChecked() << 1;
    m_serPort->Port_write_direct(ctrbuf, 64);
    len = 64;
    m_serPort->Port_read_direct(inbuf, len);
}
