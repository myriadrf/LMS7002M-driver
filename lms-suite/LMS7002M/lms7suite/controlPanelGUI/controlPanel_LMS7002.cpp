/**
@file	controlPanel_LMS7002.cpp
@author	Lime Microsystems
@brief	main program window
*/

#include "controlPanel_LMS7002.h"
#include "../version.h"
#include "iniParser.h"
#include <iostream>
#include <vector>
using namespace std;

#include "MessageLog.h"
#include "../CommonUtilities.h"
#include "pnlLMS7002.h"
#include "ConnectionManager.h"
#include "LMS7002_MainControl.h"
#include "ControlParameters.h"
#include "pnlFFTviewer.h"
#include "pnlFPGAControls.h"
#include "pnlProgramming.h"
#include "dlgAbout.h"
#include "dlgConnectionManager.h"
#include "pnlSi5351.h"
#include "streamFPGA.h"
//(*InternalHeaders(controlPanel_LMS7002)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/aui/aui.h>
#include <wx/panel.h>
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/combobox.h>
#include <wx/statusbr.h>
//*)

//(*IdInit(controlPanel_LMS7002)
const long controlPanel_LMS7002::ID_STATICTEXT1 = wxNewId();
const long controlPanel_LMS7002::ID_COMBOBOX1 = wxNewId();
const long controlPanel_LMS7002::ID_PANEL1 = wxNewId();
const long controlPanel_LMS7002::ID_CONTROL_STATUSBAR = wxNewId();
const long controlPanel_LMS7002::ID_MENUITEM1 = wxNewId();
const long controlPanel_LMS7002::ID_MENUITEM2 = wxNewId();
const long controlPanel_LMS7002::ID_MENUITEM3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(controlPanel_LMS7002,wxFrame)
    //(*EventTable(controlPanel_LMS7002)
    //*)
END_EVENT_TABLE()

const wxString applicationName = "LMS 7 Suite";

controlPanel_LMS7002::controlPanel_LMS7002(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    BuildContent(parent,id,pos,size);
    SetTitle( applicationName );
}

void controlPanel_LMS7002::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(controlPanel_LMS7002)
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, wxID_ANY, _("LMS_7002M control panel"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxDEFAULT_FRAME_STYLE|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxCLIP_CHILDREN, _T("wxID_ANY"));
    SetClientSize(wxSize(1024,650));
    SetMinSize(wxSize(1000,690));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(1);
    FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Modules collection:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText1->Hide();
    FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    cmbPluginsConfig = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    cmbPluginsConfig->SetSelection( cmbPluginsConfig->Append(_("EVB7")) );
    cmbPluginsConfig->Hide();
    FlexGridSizer2->Add(cmbPluginsConfig, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    panelsManager = new wxAuiManager(Panel1, wxAUI_MGR_DEFAULT);
    FlexGridSizer1->Add(Panel1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    m_controlStatusbar = new wxStatusBar(this, ID_CONTROL_STATUSBAR, 0, _T("ID_CONTROL_STATUSBAR"));
    int __wxStatusBarWidths_1[4] = { 64, -64, -64, -64 };
    int __wxStatusBarStyles_1[4] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    m_controlStatusbar->SetFieldsCount(4,__wxStatusBarWidths_1);
    m_controlStatusbar->SetStatusStyles(4,__wxStatusBarStyles_1);
    SetStatusBar(m_controlStatusbar);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Quit"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, ID_MENUITEM2, _("Connection Settings"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Options"));
    menuModules = new wxMenu();
    MenuBar1->Append(menuModules, _("Modules"));
    Menu4 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu4, ID_MENUITEM3, _("About"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem3);
    MenuBar1->Append(Menu4, _("Help"));
    SetMenuBar(MenuBar1);
    SetSizer(FlexGridSizer1);
    Layout();
    Center();

    Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&controlPanel_LMS7002::OncmbPluginsConfigSelected);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&controlPanel_LMS7002::OnQuit);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&controlPanel_LMS7002::OnmenuConnectionSettingsSelected);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&controlPanel_LMS7002::OnAbout);
    //*)
    m_pluginsConfiguration = PLUGINS_ALL;

    pnl_lms7ctrl = new pnlLMS7002(Panel1, wxNewId());
    pnl_lms7ctrl->AssignToConfigurations(PLUGINS_DIGIGREEN|PLUGINS_DIGIRED|PLUGINS_EVB6|PLUGINS_ZIPPER|PLUGINS_NOVENA|PLUGINS_STREAM);
    plugins.push_back(pnl_lms7ctrl);
    panelsManager->AddPane(pnl_lms7ctrl, wxAuiPaneInfo().Name("LMS7002").Caption("LMS7002").Center().Dock().Show().BestSize(pnl_lms7ctrl->GetSize()).MinSize(pnl_lms7ctrl->GetSize()).CaptionVisible(false));

	lmsControl = pnl_lms7ctrl->getLMScontrol();
    m_controlPort = lmsControl->getSerPort();
    m_controlPort->RegisterForNotifications(this);
	lmsControl->RegisterForNotifications(this);

    m_dataPort = new ConnectionManager(true);
    m_dataPort->RegisterForNotifications(this);

    pnlfft = NULL;
    pnlfft = new pnlFFTviewer(m_controlPort, m_dataPort, Panel1, wxNewId());
    pnlfft->SetSize(wxSize(800, 600));
    pnlfft->AssignControl(lmsControl);
    lmsControl->RegisterForNotifications(pnlfft);

    myriad7 = new pnlMyriad7(Panel1, wxNewId());
    myriad7 ->AssignToConfigurations(PLUGINS_ZIPPER|PLUGINS_STREAM);
    myriad7->Initialize(pnl_lms7ctrl->getLMScontrol());
    plugins.push_back(myriad7);
    panelsManager->AddPane(myriad7, wxAuiPaneInfo().Name("Myriad7").Caption("Myriad7").Bottom().Dock().Hide());

    pnlFPGA = new pnlFPGAControls(m_dataPort, Panel1, wxNewId());
    pnlFPGA ->AssignToConfigurations(PLUGINS_DIGIGREEN|PLUGINS_STREAM);
    plugins.push_back(pnlFPGA );
    panelsManager->AddPane(pnlFPGA , wxAuiPaneInfo().Name("FPGAControls").Caption("FPGA Controls").Bottom().Dock().Hide());

    pnlProg = new pnlProgramming(m_dataPort, Panel1, wxNewId());
    pnlProg->AssignToConfigurations(PLUGINS_DIGIGREEN|PLUGINS_STREAM);
    plugins.push_back(pnlProg);
    panelsManager->AddPane(pnlProg, wxAuiPaneInfo().Name("Programming").Caption("Programming").Bottom().Dock().Hide());

    si5351 = new pnlSi5351(Panel1, wxNewId());
    si5351->AssignToConfigurations(PLUGINS_STREAM);
    plugins.push_back(si5351);
    panelsManager->AddPane(si5351, wxAuiPaneInfo().Name("Si5351C").Caption("Si5351C").Left().Float().Hide());
    si5351->Initialize(lmsControl->getSi5351());

    panelsManager->Update();

    //pnl_lms7ctrl->UpdateAllPages();
    //minCtrl->UpdateGUI();
    Layout();
    SetAvailableModules(PLUGINS_ALL);
}

controlPanel_LMS7002::~controlPanel_LMS7002()
{
    panelsManager->UnInit();
    m_controlPort->UnregisterFromNotifications(this);
    //(*Destroy(controlPanel_LMS7002)
    //*)
}

void controlPanel_LMS7002::OnQuit(wxCommandEvent& event)
{
    Close();
}

void controlPanel_LMS7002::OnAbout(wxCommandEvent& event)
{
    dlgAbout dlg(this);
    dlg.ShowModal();
}

void controlPanel_LMS7002::OnmenuConnectionSettingsSelected(wxCommandEvent& event)
{
    if(pnlfft)
        pnlfft->StopCapturing();
    dlgConnectionManager dlg(this);
    dlg.SetConnectionManager(m_controlPort, m_dataPort);
    dlg.ShowModal();
}

void controlPanel_LMS7002::OnShowModule(wxCommandEvent& event)
{
    wxWindow *item = NULL;
    item = FindWindowById(event.GetId());
    if(item)
    {
        if(item == pnlfft)
        {

           //panelsManager->GetPane(item).Center().Dock();

        }
        if(item == pnl_lms7ctrl)
        {

           panelsManager->GetPane(item).Center().Dock();
        }
        panelsManager->GetPane(item).Show();
        panelsManager->Update();
    }
}

void controlPanel_LMS7002::HandleMessage(const LMS_Message &msg)
{
    switch(msg.type)
    {
		case MSG_CGEN_FREQUENCY_CHANGED:
		{
			if (m_dataPort->IsOpen())
			{
				int status = ConfigurePLL(m_dataPort, lmsControl->GetReferenceFrequencyNCO(false), lmsControl->GetReferenceFrequencyNCO(true), 90);
				stringstream ss;
				ss << "Configured FPGA PLL: TxPLL " << lmsControl->GetReferenceFrequencyNCO(false) << " MHz , RxPLL " << lmsControl->GetReferenceFrequencyNCO(true) << " MHz ";
				if (status != 0)
				{
					ss << "FAILED" << endl;
					MessageLog::getInstance()->write(ss.str(), LOG_ERROR);
					if (status == -2)
						wxMessageBox("Failed to send data", "");
					if (status == -1)
						wxMessageBox("Frequency out of VCO bounds", "");
				}
				else
				{
					ss << endl;
					MessageLog::getInstance()->write(ss.str(), LOG_INFO);
				}
				break;
			}
		}			
        case MSG_BOARD_DISCONNECTED:
        case MSG_BOARD_CONNECTED:
		{
			const int controlCollumn = 2;
			const int dataCollumn = 3;
            myriad7->UpdatePanel();
			wxString stemp = applicationName;
			stemp.append("  ");			

			unsigned char outBuffer[64];
			memset(outBuffer, 0, 64);
			unsigned char inBuffer[64];
			memset(inBuffer, 0, 64);
			if (m_controlPort->IsOpen())
			{ 
				wxString controlDev = m_controlPort->GetConnectedDeviceName();
				if (controlDev.size() > 0)
					stemp.append("Control port: " + controlDev);

				unsigned long bToRead = 56;
				m_controlPort->SendReadData(CMD_GET_INFO, outBuffer, 56, inBuffer, bToRead);
				wxString text = "Control: ";
				unsigned char fw_ver, hw_ver, protocol, devType;
				fw_ver = inBuffer[0];
				devType = inBuffer[1];
				protocol = inBuffer[2];
				hw_ver = inBuffer[3];

				if (devType < LMS_DEV_COUNT)
					text.Append(LMS_DEV_NAMES[devType]);
				else
					text.Append("Unknown device");
				text.Append(wxString::Format("  FW:%i HW:%i Protocol:%i", (int) fw_ver, (int) hw_ver, (int) protocol));
				m_controlStatusbar->SetStatusText(text, controlCollumn);
			}
			else
				m_controlStatusbar->SetStatusText("Control: Not Connected", controlCollumn);
			if (m_dataPort->IsOpen())
			{
				wxString streamDev = m_dataPort->GetConnectedDeviceName();
				if (streamDev.size() > 0)
					stemp.append(" Data port: " + streamDev);

				unsigned long bToRead = 56;
				m_dataPort->SendReadData(CMD_GET_INFO, outBuffer, 56, inBuffer, bToRead);
				wxString text = "Data: ";
				unsigned char fw_ver, hw_ver, protocol, devType;
				fw_ver = inBuffer[0];
				devType = inBuffer[1];
				protocol = inBuffer[2];
				hw_ver = inBuffer[3];

				if (devType < LMS_DEV_COUNT)
					text.Append(LMS_DEV_NAMES[devType]);
				else
					text.Append("Unknown device");
				text.Append(wxString::Format("  FW:%i HW:%i Protocol:%i", (int)fw_ver, (int)hw_ver, (int)protocol));
				m_controlStatusbar->SetStatusText(text, dataCollumn);
			}
			else
				m_controlStatusbar->SetStatusText("Data: Not Connected", dataCollumn);
			SetTitle(stemp);			
		}
        break;
        default:
            break;
    }
}

int controlPanel_LMS7002::SetAvailableModules(unsigned long ePluginsConfiguration_flags)
{
    wxMenuItemList itemList = menuModules->GetMenuItems();
    wxMenuItemList::iterator iter;
    for(iter = itemList.begin(); iter!=itemList.end(); ++iter)
    {
        wxMenuItem *item = *iter;
        menuModules->Destroy(item);
    }
    m_pluginsConfiguration = ePluginsConfiguration_flags;
    for(unsigned i=0; i<plugins.size(); ++i)
    {
        unsigned long flags = plugins[i]->GetAssignedConfigurations();
        if( (flags & m_pluginsConfiguration) == false)
        {
            wxAuiPaneInfo *pnl = &panelsManager->GetPane(plugins[i]->GetPluginWindow());
            pnl->Hide();
        }
        else
        {
            wxAuiPaneInfo *pnl = &panelsManager->GetPane(plugins[i]->GetPluginWindow());
            int mnu_id = pnl->window->GetId();
            wxMenuItem *item = new wxMenuItem(menuModules, mnu_id, _(pnl->name), wxEmptyString, wxITEM_NORMAL);
            menuModules->Append(item);
            Connect(mnu_id,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&controlPanel_LMS7002::OnShowModule);
        }
    }
    int fftid = wxNewId();
    wxMenuItem *item = new wxMenuItem(menuModules, fftid, "FFTviewer", wxEmptyString, wxITEM_NORMAL);
    menuModules->Append(item);
    Connect(fftid,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&controlPanel_LMS7002::OnShowFFT);
    panelsManager->Update();
    return 0;
}

void controlPanel_LMS7002::OncmbPluginsConfigSelected(wxCommandEvent& event)
{
    long selection = cmbPluginsConfig->GetSelection()-1;
    if(selection == -1)
        SetAvailableModules(PLUGINS_ALL);
    else
    {
        SetAvailableModules( pow(2.0, selection) );
    }
}

void controlPanel_LMS7002::OnShowFFT(wxCommandEvent& event)
{
    if(pnlfft != NULL)
        pnlfft->Show();
}
