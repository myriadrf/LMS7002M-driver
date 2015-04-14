/**
@file	dlgRegisterMap.cpp
@author	Lime Microsystems
@brief	dialog for displaying registers data
*/

#include "dlgRegisterMap.h"

#include "RegistersMap.h"
#include "LMS7002_MainControl.h"
#include "ConnectionManager.h"

#include <iostream>
using namespace std;

//(*InternalHeaders(dlgRegisterMap)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgRegisterMap)
const long dlgRegisterMap::ID_STATICTEXT2 = wxNewId();
const long dlgRegisterMap::ID_STATICTEXT1 = wxNewId();
const long dlgRegisterMap::ID_GRID1 = wxNewId();
const long dlgRegisterMap::ID_GRID2 = wxNewId();
const long dlgRegisterMap::ID_STATICTEXT3 = wxNewId();
const long dlgRegisterMap::ID_STATICTEXT4 = wxNewId();
const long dlgRegisterMap::ID_BUTTON2 = wxNewId();
const long dlgRegisterMap::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgRegisterMap,wxDialog)
    //(*EventTable(dlgRegisterMap)
    //*)
END_EVENT_TABLE()

dlgRegisterMap::dlgRegisterMap(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
}

void dlgRegisterMap::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(dlgRegisterMap)
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, id, _T("Local Registers Map"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX, _T("id"));
    SetClientSize(wxDefaultSize);
    Move(wxDefaultPosition);
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableCol(1);
    FlexGridSizer2->AddGrowableRow(1);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("Channel 0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("Channel 1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    gridCh0 = new wxGrid(this, ID_GRID1, wxDefaultPosition, wxSize(250,400), 0, _T("ID_GRID1"));
    gridCh0->CreateGrid(0,2);
    gridCh0->EnableEditing(true);
    gridCh0->EnableGridLines(true);
    gridCh0->SetColLabelSize(24);
    gridCh0->SetRowLabelSize(48);
    gridCh0->SetDefaultRowSize(24, true);
    gridCh0->SetDefaultColSize(64, true);
    gridCh0->SetColLabelValue(0, _T("Address"));
    gridCh0->SetColLabelValue(1, _T("Value"));
    gridCh0->SetDefaultCellFont( gridCh0->GetFont() );
    gridCh0->SetDefaultCellTextColour( gridCh0->GetForegroundColour() );
    FlexGridSizer2->Add(gridCh0, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    gridCh1 = new wxGrid(this, ID_GRID2, wxDefaultPosition, wxSize(250,400), 0, _T("ID_GRID2"));
    gridCh1->CreateGrid(0,2);
    gridCh1->EnableEditing(true);
    gridCh1->EnableGridLines(true);
    gridCh1->SetColLabelSize(24);
    gridCh1->SetRowLabelSize(48);
    gridCh1->SetDefaultRowSize(24, true);
    gridCh1->SetDefaultColSize(64, true);
    gridCh1->SetColLabelValue(0, _T("Address"));
    gridCh1->SetColLabelValue(1, _T("Value"));
    gridCh1->SetDefaultCellFont( gridCh1->GetFont() );
    gridCh1->SetDefaultCellTextColour( gridCh1->GetForegroundColour() );
    FlexGridSizer2->Add(gridCh1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _T("Action: "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText3->Hide();
    FlexGridSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtAction = new wxStaticText(this, ID_STATICTEXT4, _T("---"), wxDefaultPosition, wxSize(369,13), 0, _T("ID_STATICTEXT4"));
    txtAction->Hide();
    FlexGridSizer4->Add(txtAction, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnForceRefresh = new wxButton(this, ID_BUTTON2, _T("Refresh Now"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer4->Add(btnForceRefresh, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer4, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
    FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
    btnClose = new wxButton(this, ID_BUTTON1, _T("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer3->Add(btnClose, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgRegisterMap::OnbtnForceRefreshClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgRegisterMap::OnbtnCloseClick);
    //*)
}

dlgRegisterMap::~dlgRegisterMap()
{
    //(*Destroy(dlgRegisterMap)
    //*)
    //lmsControl->getSerPort()->UnregisterFromNotifications(this);
}

void dlgRegisterMap::OnbtnCloseClick(wxCommandEvent& event)
{
    Show(false);
}

void dlgRegisterMap::Initialize(LMS7002_MainControl *mainControl)
{
    lmsControl = mainControl;
    lmsControl->getSerPort()->RegisterForNotifications(this);
}

void dlgRegisterMap::HandleMessage(const LMS_Message &msg)
{
    if(msg.type == MSG_REGISTER_VALUE_SET)
    {
        long address = 0;
        for(int i=0; i<gridCh0->GetTable()->GetRowsCount(); ++i)
        {
            gridCh0->GetCellValue(i, 0).ToLong(&address);
            if(address == msg.param1)
            {
                gridCh0->SetCellValue(i, 0, wxString::Format("0x%04X ", msg.param2));
                txtAction->SetLabel( wxString::Format("register 0x%04X value set to 0x%04X", msg.param1, msg.param2));
                break;
            }
        }
    }
}

void dlgRegisterMap::UpdateTables()
{
    if(!lmsControl)
        return;

    RegistersMap *regMap = lmsControl->getRegistersMap();

    wxGrid *grid;

    for(int i=0; i<2; ++i)
    {
        if(i==0)
            grid = gridCh0;
        else
            grid = gridCh1;

        if(grid->GetTable()->GetRowsCount() > 0)
            grid->GetTable()->DeleteRows(0, grid->GetTable()->GetRowsCount());

        grid->SetColLabelValue(0, "Address");
        grid->SetColLabelValue(1, "Value");

        map<unsigned short, unsigned short> regValues = regMap->GetRegistersValues(i);

        for(map<unsigned short, unsigned short>::iterator iter=regValues.begin(); iter!=regValues.end(); ++iter)
        {
            grid->AppendRows(1);
            grid->SetCellValue( grid->GetTable()->GetRowsCount()-1, 0, wxString::Format("0x%04X ", iter->first));
            grid->SetCellValue( grid->GetTable()->GetRowsCount()-1, 1, wxString::Format("0x%04X ", iter->second));
        }
    }
}

void dlgRegisterMap::OnbtnForceRefreshClick(wxCommandEvent& event)
{
    UpdateTables();
}
