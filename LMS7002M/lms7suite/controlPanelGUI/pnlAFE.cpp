/**
@file	pnlAFE.cpp
@author	Lime Microsystems
@brief	AFE module panel
*/

#include "pnlAFE.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "LMS7002_MainControl.h"
//(*InternalHeaders(pnlAFE)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)
//(*IdInit(pnlAFE)
const long pnlAFE::ID_STATICTEXT1 = wxNewId();
const long pnlAFE::ID_ISEL_DAC_AFE = wxNewId();
const long pnlAFE::ID_STATICTEXT2 = wxNewId();
const long pnlAFE::ID_MUX_AFE_1 = wxNewId();
const long pnlAFE::ID_STATICTEXT3 = wxNewId();
const long pnlAFE::ID_MUX_AFE_2 = wxNewId();
const long pnlAFE::ID_MODE_INTERLEAVE_AFE = wxNewId();
const long pnlAFE::ID_PD_AFE = wxNewId();
const long pnlAFE::ID_PD_RX_AFE1 = wxNewId();
const long pnlAFE::ID_PD_RX_AFE2 = wxNewId();
const long pnlAFE::ID_PD_TX_AFE1 = wxNewId();
const long pnlAFE::ID_PD_TX_AFE2 = wxNewId();
const long pnlAFE::ID_EN_G_AFE = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlAFE,wxPanel)
//(*EventTable(pnlAFE)
//*)
END_EVENT_TABLE()

void pnlAFE::AssignEnumsToIds()
{
    wndId2Enum[ID_EN_G_AFE] = EN_G_AFE;
    wndId2Enum[ID_ISEL_DAC_AFE] = ISEL_DAC_AFE;
    wndId2Enum[ID_MODE_INTERLEAVE_AFE] = MODE_INTERLEAVE_AFE;
    wndId2Enum[ID_MUX_AFE_1] = MUX_AFE_1;
    wndId2Enum[ID_MUX_AFE_2] = MUX_AFE_2;
    wndId2Enum[ID_PD_AFE] = PD_AFE;
    wndId2Enum[ID_PD_RX_AFE1] = PD_RX_AFE1;
    wndId2Enum[ID_PD_RX_AFE2] = PD_RX_AFE2;
    wndId2Enum[ID_PD_TX_AFE1] = PD_TX_AFE1;
    wndId2Enum[ID_PD_TX_AFE2] = PD_TX_AFE2;
}

pnlAFE::pnlAFE(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlAFE::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlAFE)
wxFlexGridSizer* Powerdowncontrols2Sizer;
wxFlexGridSizer* AFE1Sizer;
wxStaticBoxSizer* AFESizer;
wxStaticBoxSizer* PowerdowncontrolsSizer;
wxFlexGridSizer* FlexGridSizer1;

Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 5);
AFESizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("AFE"));
AFE1Sizer = new wxFlexGridSizer(0, 2, 0, 0);
StaticText0 = new wxStaticText(this, ID_STATICTEXT1, _("Peak current of DAC"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
AFE1Sizer->Add(StaticText0, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbISEL_DAC_AFE = new ComboBoxMap(this, ID_ISEL_DAC_AFE, wxEmptyString, wxDefaultPosition, wxSize(162,-1), 0, 0, 0, wxDefaultValidator, _T("ID_ISEL_DAC_AFE"));
cmbISEL_DAC_AFE->SetToolTip(_("Controls the peak current of the DAC output current"));
AFE1Sizer->Add(cmbISEL_DAC_AFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText1 = new wxStaticText(this, ID_STATICTEXT2, _("MUX input of ADC ch.1 "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
AFE1Sizer->Add(StaticText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbMUX_AFE_1 = new ComboBoxMap(this, ID_MUX_AFE_1, wxEmptyString, wxDefaultPosition, wxSize(315,-1), 0, 0, 0, wxDefaultValidator, _T("ID_MUX_AFE_1"));
cmbMUX_AFE_1->SetToolTip(_("Controls the MUX at the input of the ADC channel 1"));
AFE1Sizer->Add(cmbMUX_AFE_1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText2 = new wxStaticText(this, ID_STATICTEXT3, _("MUX input of ADC ch.2"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
AFE1Sizer->Add(StaticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbMUX_AFE_2 = new ComboBoxMap(this, ID_MUX_AFE_2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_MUX_AFE_2"));
cmbMUX_AFE_2->SetToolTip(_("Controls the MUX at the input of the ADC channel 2"));
AFE1Sizer->Add(cmbMUX_AFE_2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_1[2] =
{
	_("Two ADCs"),
	_("Interleaved")
};
rgrMODE_INTERLEAVE_AFE = new wxRadioBox(this, ID_MODE_INTERLEAVE_AFE, _("Time interleave two ADCs into one ADC"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_MODE_INTERLEAVE_AFE"));
rgrMODE_INTERLEAVE_AFE->SetSelection(0);
rgrMODE_INTERLEAVE_AFE->SetToolTip(_("time interleaves the two ADCs into one ADC"));
AFE1Sizer->Add(rgrMODE_INTERLEAVE_AFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
AFESizer->Add(AFE1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(AFESizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
PowerdowncontrolsSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Power down controls"));
Powerdowncontrols2Sizer = new wxFlexGridSizer(0, 1, 0, 0);
chkPD_AFE = new wxCheckBox(this, ID_PD_AFE, _("AFE current mirror in BIAS_TOP"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_AFE"));
chkPD_AFE->SetValue(false);
chkPD_AFE->SetToolTip(_("Power down control for the AFE current mirror in BIAS_TOP"));
Powerdowncontrols2Sizer->Add(chkPD_AFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_RX_AFE1 = new wxCheckBox(this, ID_PD_RX_AFE1, _("ADC ch. 1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_RX_AFE1"));
chkPD_RX_AFE1->SetValue(false);
chkPD_RX_AFE1->SetToolTip(_("Power down control for the ADC of  channel 1"));
Powerdowncontrols2Sizer->Add(chkPD_RX_AFE1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_RX_AFE2 = new wxCheckBox(this, ID_PD_RX_AFE2, _("ADC ch. 2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_RX_AFE2"));
chkPD_RX_AFE2->SetValue(false);
chkPD_RX_AFE2->SetToolTip(_("Power down control for the ADC of channel 2"));
Powerdowncontrols2Sizer->Add(chkPD_RX_AFE2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_TX_AFE1 = new wxCheckBox(this, ID_PD_TX_AFE1, _("DAC ch. 1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_TX_AFE1"));
chkPD_TX_AFE1->SetValue(false);
chkPD_TX_AFE1->SetToolTip(_("Power down control for the DAC of channel 1"));
Powerdowncontrols2Sizer->Add(chkPD_TX_AFE1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_TX_AFE2 = new wxCheckBox(this, ID_PD_TX_AFE2, _("DAC ch. 2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_TX_AFE2"));
chkPD_TX_AFE2->SetValue(false);
chkPD_TX_AFE2->SetToolTip(_("Power down control for the DAC of channel 2"));
Powerdowncontrols2Sizer->Add(chkPD_TX_AFE2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_G_AFE = new wxCheckBox(this, ID_EN_G_AFE, _("Enable AFE module"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_G_AFE"));
chkEN_G_AFE->SetValue(false);
chkEN_G_AFE->SetToolTip(_("Enable control for all the AFE power downs"));
Powerdowncontrols2Sizer->Add(chkEN_G_AFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
PowerdowncontrolsSizer->Add(Powerdowncontrols2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer1->Add(PowerdowncontrolsSizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_ISEL_DAC_AFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAFE::ParameterChangeHandler);
Connect(ID_MUX_AFE_1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAFE::ParameterChangeHandler);
Connect(ID_MUX_AFE_2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlAFE::ParameterChangeHandler);
Connect(ID_MODE_INTERLEAVE_AFE,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlAFE::ParameterChangeHandler);
Connect(ID_PD_AFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlAFE::ParameterChangeHandler);
Connect(ID_PD_RX_AFE1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlAFE::ParameterChangeHandler);
Connect(ID_PD_RX_AFE2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlAFE::ParameterChangeHandler);
Connect(ID_PD_TX_AFE1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlAFE::ParameterChangeHandler);
Connect(ID_PD_TX_AFE2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlAFE::ParameterChangeHandler);
Connect(ID_EN_G_AFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlAFE::ParameterChangeHandler);
//*)
}

pnlAFE::~pnlAFE()
{
//(*Destroy(pnlAFE)
//*)
}
void pnlAFE::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlAFE panel don't have control module assigned" << std::endl;
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

void pnlAFE::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    char ctemp[80];
    vector<string> temp;
    temp.clear();
    for(int i=0; i<8; ++i)
    {
        sprintf(ctemp, "%i uA", 325+i*75); temp.push_back( ctemp ); //nominal 625uA
    }
    cmbISEL_DAC_AFE->Clear();
    cmbISEL_DAC_AFE->Append(temp);
    cmbISEL_DAC_AFE->SetSelection( lmsControl->GetParam(ISEL_DAC_AFE));

    temp.clear();
    temp.push_back("PGA output is connected to ADC input");
    temp.push_back("pdet_1 is connected to ADC ch. 1");
    temp.push_back("BIAS_TOP test outputs will be connected to ADC ch.1 input");
    temp.push_back("RSSI 1 output will be connected to ADC 1 input");
    cmbMUX_AFE_1->Clear();
    cmbMUX_AFE_1->Append(temp);
    cmbMUX_AFE_1->SetSelection( lmsControl->GetParam(MUX_AFE_1));

    temp.clear();
    temp.push_back("PGA output is connected to ADC input");
    temp.push_back("pdet_2 is connected to ADC channel 2");
    temp.push_back("RSSI 1 output will be connected to ADC 2 input");
    temp.push_back("RSSI 2 output will be connected to ADC 2 input");
    cmbMUX_AFE_2->Clear();
    cmbMUX_AFE_2->Append(temp);
    cmbMUX_AFE_2->SetSelection( lmsControl->GetParam(MUX_AFE_2));

    //write register names and addresses to tooltips
    UpdateTooltips(this);
}

void pnlAFE::UpdateGUI()
{
    //GetParent()->Freeze();
    long value = 0;
    value = lmsControl->GetParam(EN_G_AFE);
    chkEN_G_AFE->SetValue(value);

    value = lmsControl->GetParam(ISEL_DAC_AFE);
    cmbISEL_DAC_AFE->SetSelection(value);

    value = lmsControl->GetParam(MODE_INTERLEAVE_AFE);
    rgrMODE_INTERLEAVE_AFE->SetSelection(value);

    value = lmsControl->GetParam(MUX_AFE_1);
    cmbMUX_AFE_1->SetSelection(value);

    value = lmsControl->GetParam(MUX_AFE_2);
    cmbMUX_AFE_2->SetSelection(value);

    value = lmsControl->GetParam(PD_AFE);
    chkPD_AFE->SetValue(value);

    value = lmsControl->GetParam(PD_RX_AFE1);
    chkPD_RX_AFE1->SetValue(value);

    value = lmsControl->GetParam(PD_RX_AFE2);
    chkPD_RX_AFE2->SetValue(value);

    value = lmsControl->GetParam(PD_TX_AFE1);
    chkPD_TX_AFE1->SetValue(value);

    value = lmsControl->GetParam(PD_TX_AFE2);
    chkPD_TX_AFE2->SetValue(value);

    //GetParent()->Thaw();
}

