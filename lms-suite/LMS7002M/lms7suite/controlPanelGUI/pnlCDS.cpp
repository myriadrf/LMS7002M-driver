/**
@file	pnlCDS.cpp
@author	Lime Microsystems
@brief	CDS module panel
*/

#include "pnlCDS.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "LMS7002_MainControl.h"
//(*InternalHeaders(pnlCDS)
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/radiobox.h>
//*)
//(*IdInit(pnlCDS)
const long pnlCDS::ID_CDSN_TXBTSP = wxNewId();
const long pnlCDS::ID_CDSN_TXATSP = wxNewId();
const long pnlCDS::ID_CDSN_RXBTSP = wxNewId();
const long pnlCDS::ID_CDSN_RXATSP = wxNewId();
const long pnlCDS::ID_CDSN_TXBLML = wxNewId();
const long pnlCDS::ID_CDSN_TXALML = wxNewId();
const long pnlCDS::ID_CDSN_RXBLML = wxNewId();
const long pnlCDS::ID_CDSN_RXALML  = wxNewId();
const long pnlCDS::ID_CDSN_MCLK2 = wxNewId();
const long pnlCDS::ID_CDSN_MCLK1 = wxNewId();
const long pnlCDS::ID_CDS_MCLK2 = wxNewId();
const long pnlCDS::ID_CDS_MCLK1 = wxNewId();
const long pnlCDS::ID_CDS_TXBTSP = wxNewId();
const long pnlCDS::ID_CDS_TXATSP = wxNewId();
const long pnlCDS::ID_CDS_RXBTSP = wxNewId();
const long pnlCDS::ID_CDS_RXATSP = wxNewId();
const long pnlCDS::ID_CDS_TXBLML = wxNewId();
const long pnlCDS::ID_CDS_TXALML = wxNewId();
const long pnlCDS::ID_CDS_RXBLML = wxNewId();
const long pnlCDS::ID_CDS_RXALML = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlCDS,wxPanel)
//(*EventTable(pnlCDS)
//*)
END_EVENT_TABLE()

void pnlCDS::AssignEnumsToIds()
{
    wndId2Enum[ID_CDSN_MCLK1] = CDSN_MCLK1;
    wndId2Enum[ID_CDSN_MCLK2] = CDSN_MCLK2;
    wndId2Enum[ID_CDSN_RXALML] = CDSN_RXALML;
    wndId2Enum[ID_CDSN_RXATSP] = CDSN_RXATSP;
    wndId2Enum[ID_CDSN_RXBLML] = CDSN_RXBLML;
    wndId2Enum[ID_CDSN_RXBTSP] = CDSN_RXBTSP;
    wndId2Enum[ID_CDSN_TXALML] = CDSN_TXALML;
    wndId2Enum[ID_CDSN_TXATSP] = CDSN_TXATSP;
    wndId2Enum[ID_CDSN_TXBLML] = CDSN_TXBLML;
    wndId2Enum[ID_CDSN_TXBTSP] = CDSN_TXBTSP;
    wndId2Enum[ID_CDS_MCLK1] = CDS_MCLK1;
    wndId2Enum[ID_CDS_MCLK2] = CDS_MCLK2;
    wndId2Enum[ID_CDS_RXALML] = CDS_RXALML;
    wndId2Enum[ID_CDS_RXATSP] = CDS_RXATSP;
    wndId2Enum[ID_CDS_RXBLML] = CDS_RXBLML;
    wndId2Enum[ID_CDS_RXBTSP] = CDS_RXBTSP;
    wndId2Enum[ID_CDS_TXALML] = CDS_TXALML;
    wndId2Enum[ID_CDS_TXATSP] = CDS_TXATSP;
    wndId2Enum[ID_CDS_TXBLML] = CDS_TXBLML;
    wndId2Enum[ID_CDS_TXBTSP] = CDS_TXBTSP;
}

pnlCDS::pnlCDS(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlCDS::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlCDS)
wxFlexGridSizer* FlexGridSizer1;
wxFlexGridSizer* Clockinversion1Sizer;
wxFlexGridSizer* Clockdelay2Sizer;
wxStaticBoxSizer* ClockdelaySizer;
wxStaticBoxSizer* ClockinversionSizer;

Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 5);
ClockinversionSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Clock inversion"));
Clockinversion1Sizer = new wxFlexGridSizer(0, 1, 0, 0);
chkCDSN_TXBTSP = new wxCheckBox(this, ID_CDSN_TXBTSP, _("TX TSPB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CDSN_TXBTSP"));
chkCDSN_TXBTSP->SetValue(false);
chkCDSN_TXBTSP->SetToolTip(_("TX TSPB clock inversion control"));
Clockinversion1Sizer->Add(chkCDSN_TXBTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkCDSN_TXATSP = new wxCheckBox(this, ID_CDSN_TXATSP, _("TX TSPA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CDSN_TXATSP"));
chkCDSN_TXATSP->SetValue(false);
chkCDSN_TXATSP->SetToolTip(_("TX TSPA clock inversion control"));
Clockinversion1Sizer->Add(chkCDSN_TXATSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkCDSN_RXBTSP = new wxCheckBox(this, ID_CDSN_RXBTSP, _("RX TSPB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CDSN_RXBTSP"));
chkCDSN_RXBTSP->SetValue(false);
chkCDSN_RXBTSP->SetToolTip(_("RX TSPB clock inversion control"));
Clockinversion1Sizer->Add(chkCDSN_RXBTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkCDSN_RXATSP = new wxCheckBox(this, ID_CDSN_RXATSP, _("RX TSPA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CDSN_RXATSP"));
chkCDSN_RXATSP->SetValue(false);
chkCDSN_RXATSP->SetToolTip(_("RX TSPA clock inversion control"));
Clockinversion1Sizer->Add(chkCDSN_RXATSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkCDSN_TXBLML = new wxCheckBox(this, ID_CDSN_TXBLML, _("TX LMLB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CDSN_TXBLML"));
chkCDSN_TXBLML->SetValue(false);
chkCDSN_TXBLML->SetToolTip(_("TX LMLB clock inversion control"));
Clockinversion1Sizer->Add(chkCDSN_TXBLML, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkCDSN_TXALML = new wxCheckBox(this, ID_CDSN_TXALML, _("TX LMLA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CDSN_TXALML"));
chkCDSN_TXALML->SetValue(false);
chkCDSN_TXALML->SetToolTip(_("TX LMLA clock inversion control"));
Clockinversion1Sizer->Add(chkCDSN_TXALML, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkCDSN_RXBLML = new wxCheckBox(this, ID_CDSN_RXBLML, _("RX LMLB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CDSN_RXBLML"));
chkCDSN_RXBLML->SetValue(false);
chkCDSN_RXBLML->SetToolTip(_("RX LMLB clock inversion control"));
Clockinversion1Sizer->Add(chkCDSN_RXBLML, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkCDSN_RXALML  = new wxCheckBox(this, ID_CDSN_RXALML , _("RX LMLA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CDSN_RXALML "));
chkCDSN_RXALML ->SetValue(false);
chkCDSN_RXALML ->SetToolTip(_("RX LMLA clock inversion control"));
Clockinversion1Sizer->Add(chkCDSN_RXALML , 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkCDSN_MCLK2 = new wxCheckBox(this, ID_CDSN_MCLK2, _("MCLK2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CDSN_MCLK2"));
chkCDSN_MCLK2->SetValue(false);
chkCDSN_MCLK2->SetToolTip(_("MCLK2 clock inversion control"));
Clockinversion1Sizer->Add(chkCDSN_MCLK2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkCDSN_MCLK1 = new wxCheckBox(this, ID_CDSN_MCLK1, _("MCLK1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CDSN_MCLK1"));
chkCDSN_MCLK1->SetValue(false);
chkCDSN_MCLK1->SetToolTip(_("MCLK1 clock inversion control"));
Clockinversion1Sizer->Add(chkCDSN_MCLK1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
ClockinversionSizer->Add(Clockinversion1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(ClockinversionSizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
ClockdelaySizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Clock delay"));
Clockdelay2Sizer = new wxFlexGridSizer(0, 5, 0, 5);
wxString __wxRadioBoxChoices_1[4] =
{
	_("400ps"),
	_("500ps"),
	_("600ps"),
	_("700ps")
};
rgrCDS_MCLK2 = new wxRadioBox(this, ID_CDS_MCLK2, _("MCLK2"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CDS_MCLK2"));
rgrCDS_MCLK2->SetSelection(0);
rgrCDS_MCLK2->SetToolTip(_("MCLK2 clock delay"));
Clockdelay2Sizer->Add(rgrCDS_MCLK2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_2[4] =
{
	_("400ps"),
	_("500ps"),
	_("600ps"),
	_("700ps")
};
rgrCDS_MCLK1 = new wxRadioBox(this, ID_CDS_MCLK1, _("MCLK1"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_2, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CDS_MCLK1"));
rgrCDS_MCLK1->SetSelection(0);
rgrCDS_MCLK1->SetToolTip(_("MCLK1 clock delay"));
Clockdelay2Sizer->Add(rgrCDS_MCLK1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_3[4] =
{
	_("400ps"),
	_("500ps"),
	_("600ps"),
	_("700ps")
};
rgrCDS_TXBTSP = new wxRadioBox(this, ID_CDS_TXBTSP, _("TX TSP B"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_3, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CDS_TXBTSP"));
rgrCDS_TXBTSP->SetSelection(0);
rgrCDS_TXBTSP->SetToolTip(_("TX TSP B clock delay"));
Clockdelay2Sizer->Add(rgrCDS_TXBTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_4[4] =
{
	_("400ps"),
	_("500ps"),
	_("600ps"),
	_("700ps")
};
rgrCDS_TXATSP = new wxRadioBox(this, ID_CDS_TXATSP, _("TX TSP A"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_4, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CDS_TXATSP"));
rgrCDS_TXATSP->SetSelection(0);
rgrCDS_TXATSP->SetToolTip(_("TX TSP A clock delay"));
Clockdelay2Sizer->Add(rgrCDS_TXATSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_5[4] =
{
	_("200ps"),
	_("500ps"),
	_("800ps"),
	_("1100ps")
};
rgrCDS_RXBTSP = new wxRadioBox(this, ID_CDS_RXBTSP, _("RX TSP B"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_5, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CDS_RXBTSP"));
rgrCDS_RXBTSP->SetSelection(0);
rgrCDS_RXBTSP->SetToolTip(_("RX TSP B clock delay"));
Clockdelay2Sizer->Add(rgrCDS_RXBTSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_6[4] =
{
	_("200ps"),
	_("500ps"),
	_("800ps"),
	_("1100ps")
};
rgrCDS_RXATSP = new wxRadioBox(this, ID_CDS_RXATSP, _("RX TSP A"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_6, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CDS_RXATSP"));
rgrCDS_RXATSP->SetSelection(0);
rgrCDS_RXATSP->SetToolTip(_("RX TSP A clock delay"));
Clockdelay2Sizer->Add(rgrCDS_RXATSP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_7[4] =
{
	_("400ps"),
	_("500ps"),
	_("600ps"),
	_("700ps")
};
rgrCDS_TXBLML = new wxRadioBox(this, ID_CDS_TXBLML, _("TX LML B"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_7, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CDS_TXBLML"));
rgrCDS_TXBLML->SetSelection(0);
rgrCDS_TXBLML->SetToolTip(_("TX LML B clock delay"));
Clockdelay2Sizer->Add(rgrCDS_TXBLML, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_8[4] =
{
	_("400ps"),
	_("500ps"),
	_("600ps"),
	_("700ps")
};
rgrCDS_TXALML = new wxRadioBox(this, ID_CDS_TXALML, _("TX LML A"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_8, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CDS_TXALML"));
rgrCDS_TXALML->SetSelection(0);
rgrCDS_TXALML->SetToolTip(_("TX LML A clock delay"));
Clockdelay2Sizer->Add(rgrCDS_TXALML, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_9[4] =
{
	_("200ps"),
	_("500ps"),
	_("800ps"),
	_("1100ps")
};
rgrCDS_RXBLML = new wxRadioBox(this, ID_CDS_RXBLML, _("RX LML B"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_9, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CDS_RXBLML"));
rgrCDS_RXBLML->SetSelection(0);
rgrCDS_RXBLML->SetToolTip(_("RX LML B clock delay"));
Clockdelay2Sizer->Add(rgrCDS_RXBLML, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_10[4] =
{
	_("200ps"),
	_("500ps"),
	_("800ps"),
	_("1100ps")
};
rgrCDS_RXALML = new wxRadioBox(this, ID_CDS_RXALML, _("RX LML A"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_10, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_CDS_RXALML"));
rgrCDS_RXALML->SetSelection(0);
rgrCDS_RXALML->SetToolTip(_("RX LML A clock delay"));
Clockdelay2Sizer->Add(rgrCDS_RXALML, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
ClockdelaySizer->Add(Clockdelay2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(ClockdelaySizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_CDSN_TXBTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDSN_TXATSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDSN_RXBTSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDSN_RXATSP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDSN_TXBLML,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDSN_TXALML,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDSN_RXBLML,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDSN_RXALML ,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDSN_MCLK2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDSN_MCLK1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDS_MCLK2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDS_MCLK1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDS_TXBTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDS_TXATSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDS_RXBTSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDS_RXATSP,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDS_TXBLML,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDS_TXALML,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDS_RXBLML,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
Connect(ID_CDS_RXALML,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlCDS::ParameterChangeHandler);
//*)
}
pnlCDS::~pnlCDS()
{
//(*Destroy(pnlCDS)
//*)
}
void pnlCDS::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlCDS panel don't have control module assigned" << std::endl;
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
    switch(parameter)
    {
    default:
        lmsControl->SetParam( parameter, event.GetInt());
        //std::cout << "control id " << event.GetId() << " value " << event.GetInt() << std::endl;
    }
}

void pnlCDS::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    wxArrayString temp;
    UpdateTooltips(this);
}

void pnlCDS::UpdateGUI()
{
    //GetParent()->Freeze();
    long value = 0;
    value = lmsControl->GetParam(CDSN_MCLK1);
    chkCDSN_MCLK1->SetValue(value);

    value = lmsControl->GetParam(CDSN_MCLK2);
    chkCDSN_MCLK2->SetValue(value);

    value = lmsControl->GetParam(CDSN_RXALML );
    chkCDSN_RXALML ->SetValue(value);

    value = lmsControl->GetParam(CDSN_RXATSP);
    chkCDSN_RXATSP->SetValue(value);

    value = lmsControl->GetParam(CDSN_RXBLML);
    chkCDSN_RXBLML->SetValue(value);

    value = lmsControl->GetParam(CDSN_RXBTSP);
    chkCDSN_RXBTSP->SetValue(value);

    value = lmsControl->GetParam(CDSN_TXALML);
    chkCDSN_TXALML->SetValue(value);

    value = lmsControl->GetParam(CDSN_TXATSP);
    chkCDSN_TXATSP->SetValue(value);

    value = lmsControl->GetParam(CDSN_TXBLML);
    chkCDSN_TXBLML->SetValue(value);

    value = lmsControl->GetParam(CDSN_TXBTSP);
    chkCDSN_TXBTSP->SetValue(value);

    value = lmsControl->GetParam(CDS_MCLK1);
    rgrCDS_MCLK1->SetSelection(value);

    value = lmsControl->GetParam(CDS_MCLK2);
    rgrCDS_MCLK2->SetSelection(value);

    value = lmsControl->GetParam(CDS_RXALML);
    rgrCDS_RXALML->SetSelection(value);

    value = lmsControl->GetParam(CDS_RXATSP);
    rgrCDS_RXATSP->SetSelection(value);

    value = lmsControl->GetParam(CDS_RXBLML);
    rgrCDS_RXBLML->SetSelection(value);

    value = lmsControl->GetParam(CDS_RXBTSP);
    rgrCDS_RXBTSP->SetSelection(value);

    value = lmsControl->GetParam(CDS_TXALML);
    rgrCDS_TXALML->SetSelection(value);

    value = lmsControl->GetParam(CDS_TXATSP);
    rgrCDS_TXATSP->SetSelection(value);

    value = lmsControl->GetParam(CDS_TXBLML);
    rgrCDS_TXBLML->SetSelection(value);

    value = lmsControl->GetParam(CDS_TXBTSP);
    rgrCDS_TXBTSP->SetSelection(value);
}

