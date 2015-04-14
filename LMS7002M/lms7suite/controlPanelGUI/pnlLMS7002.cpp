/**
@file	pnlLMS7002.cpp
@author Lime Microsystems
@brief	main panel combining controls of LMS7002
*/
#include "pnlLMS7002.h"

//(*InternalHeaders(pnlLMS7002)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/radiobut.h>
#include <wx/font.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(pnlLMS7002)
const long pnlLMS7002::ID_BUTTON1 = wxNewId();
const long pnlLMS7002::ID_BUTTON2 = wxNewId();
const long pnlLMS7002::ID_BUTTON3 = wxNewId();
const long pnlLMS7002::ID_STATICTEXT1 = wxNewId();
const long pnlLMS7002::ID_BUTTON5 = wxNewId();
const long pnlLMS7002::ID_BUTTON6 = wxNewId();
const long pnlLMS7002::ID_BUTTON8 = wxNewId();
const long pnlLMS7002::ID_CHECKBOX1 = wxNewId();
const long pnlLMS7002::ID_RADIOBUTTON1 = wxNewId();
const long pnlLMS7002::ID_RADIOBUTTON2 = wxNewId();
const long pnlLMS7002::ID_ALGORITHMTAB = wxNewId();
const long pnlLMS7002::ID_TABBOARD = wxNewId();
const long pnlLMS7002::ID_TABBOARD1 = wxNewId();
const long pnlLMS7002::ID_RFE = wxNewId();
const long pnlLMS7002::ID_RBB = wxNewId();
const long pnlLMS7002::ID_TRF = wxNewId();
const long pnlLMS7002::ID_TBB = wxNewId();
const long pnlLMS7002::ID_AFE = wxNewId();
const long pnlLMS7002::ID_BIAS = wxNewId();
const long pnlLMS7002::ID_LDO = wxNewId();
const long pnlLMS7002::ID_XBUF = wxNewId();
const long pnlLMS7002::ID_CLKGEN = wxNewId();
const long pnlLMS7002::ID_SXRSXT = wxNewId();
const long pnlLMS7002::ID_LIMELIGHTPAD = wxNewId();
const long pnlLMS7002::ID_TXTSP = wxNewId();
const long pnlLMS7002::ID_RXTSP = wxNewId();
const long pnlLMS7002::ID_CDS = wxNewId();
const long pnlLMS7002::ID_MCUBD = wxNewId();
const long pnlLMS7002::ID_BIST = wxNewId();
const long pnlLMS7002::ID_SPITAB = wxNewId();
const long pnlLMS7002::ID_NOTEBOOK1 = wxNewId();
const long pnlLMS7002::ID_CONTROL_PANEL_MSG_LOG = wxNewId();
const long pnlLMS7002::ID_BUTTON4 = wxNewId();
const long pnlLMS7002::ID_BUTTON7 = wxNewId();
//*)
const long pnlLMS7002::ID_TABBUFFERSEVB7V2 = wxNewId();
const long pnlLMS7002::ID_TABTESTING = wxNewId();
const long pnlLMS7002::ID_TABSOCKETBOARD = wxNewId();
#include "../version.h"
#include "iniParser.h"
#include <iostream>
#include <vector>
using namespace std;

#include "MessageLog.h"
#include "../CommonUtilities.h"
#include "LMS7002_MainControl.h"
#include "ConnectionManager.h"
#include "pnlSi5351.h"
#include "pnlADF.h"
#include "pnlRFE.h"
#include "pnlRBB.h"
#include "pnlTRF.h"
#include "pnlTBB.h"
#include "pnlAFE.h"
#include "pnlBIAS.h"
#include "pnlLDO.h"
#include "pnlXBUF.h"
#include "pnlCLKGEN.h"
#include "pnlSXT.h"
#include "pnlLimeLightPAD.h"
#include "pnlTxTSP.h"
#include "pnlRxTSP.h"
#include "pnlBIST.h"
#include "pnlCDS.h"
#include "pnlMCU_BD.h"
#include "pnlSPI.h"
#include "pnlBoard.h"
#include "pnlSocketBoard.h"
#include "pnlBuffersEVB7v2.h"
#include "dlgAbout.h"
#include "dlgMessageLog.h"
#include "dlgConnectionManager.h"
#include "dlgRegisterTest.h"
#include <wx/msgdlg.h>
#include <wx/listbox.h>
#include <wx/radiobox.h>
#include "pnlTesting.h"
#include "pnlAlgorithms.h"

BEGIN_EVENT_TABLE(pnlLMS7002,wxPanel)
	//(*EventTable(pnlLMS7002)
	//*)
END_EVENT_TABLE()

pnlLMS7002 *g_pControlPanel = NULL;

const string cWindowTitle = "Control LMS7002";
const int cDeviceInfoCollumn = 1;
const int cDeviceVerRevMaskCollumn = 2;

/** @brief Handles messages coming from control logic
    @param msg message about event
*/
void pnlLMS7002::HandleMessage(const LMS_Message &msg)
{
    string stemp;
    char ctemp[80];
    switch(msg.type)
    {
    case MSG_BOARD_CONNECTED:
        //hide or show tabs depending on board type
        {
            eLMS_DEV boardType = lmsControl->getSerPort()->GetConnectedDeviceType();
            tabBoard->ModifyClocksGUI(boardType);
            if(boardType == LMS_DEV_SOCKETBOARD )
            {
                AddTab(tabSocketBoard, "Socket Board");
                lmsControl->DownloadGPIOStates();
                tabSocketBoard->UpdateGUI();
            }
            else
                RemoveTab(ID_TABSOCKETBOARD);

            if(boardType == LMS_DEV_EVB7V2 )
            {
                tabBuffersEVB7v2->Show();
                lmsControl->DownloadGPIOStates();
                tabBuffersEVB7v2->UpdateGUI();
            }
            else
                tabBuffersEVB7v2->Hide();
            wxCommandEvent evt;
            OnConfiguringChannelsChange(evt);
            UpdateGUI();
        }
        break;
    case MSG_BOARD_DISCONNECTED:
        //SetTitle( cWindowTitle );
        //m_controlStatusbar->SetStatusText("Board disconnected", cDeviceInfoCollumn);
        //m_controlStatusbar->SetStatusText("Ver: ? Rev: ? Mask: ?", cDeviceVerRevMaskCollumn);
        break;
    case MSG_REGISTER_TEST:
        if(tabSPI)
            tabSPI->PrintLine(msg.text);
        break;
    case MSG_PROGRAMMING_PACKET_SENT:
        if(tabMCU_BD)
            tabMCU_BD->SetProgressBar(msg.param1);
        break;
    case MSG_UPDATE_ALL_GUI:
        lmsControl->DownloadAll();
        UpdateGUI();
        break;
    default:
        break;
    }

//    if(msg.type == MSG_CRITICAL_ERROR)
//    {
//        wxMessageDialog dlg(this, msg.text, "Critical error");
//        dlg.ShowModal();
//    }
//    else if(msg.type == MSG_SHOW_WARNING)
//    {
//        wxMessageDialog dlg(this, msg.text, "WARNING");
//        dlg.ShowModal();
//    }
}

pnlLMS7002::pnlLMS7002(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, const wxString name)
    : PluginPanel(this)
{
	mDlgLog = NULL;
    m_overrideChannel = false;
    m_lastUsedChannel = 0;
    m_selectedChannel = 0;
    m_regMapDlg = NULL;
    g_pControlPanel = this;
    long t1 = getMilis();
    lmsControl = new LMS7002_MainControl();
    long t2 = getMilis();
    BuildContent(parent,id,pos,size);
    //SetTitle( cWindowTitle );
    m_selectedTab = m_modulesNotebook->GetSelection();
//    m_controlStatusbar->SetStatusText("Board disconnected", cDeviceInfoCollumn);
//    m_controlStatusbar->SetStatusText("Ver: ? Rev: ? Mask: ?", cDeviceVerRevMaskCollumn);
    cout << "control panel build content " << getMilis()-t2 << " ms" << endl;

    Initialize();
    cout << "control panel created in " << getMilis()-t1 << " ms" << endl;
    MessageLog::getInstance()->registerForNotifications( MessageHandler );

    lmsControl->RegisterForNotifications(this);

    iniParser ini;
    ini.Open("gui_settings.ini");
    if(ini.SelectSection("connection_settings"))
    {
        bool autoConnect = ini.Get("connect_at_startup", false);
        string deviceName = ini.Get("device", "");
        if(autoConnect)
        {
            bool found = false;
            lmsControl->getSerPort()->RefreshDeviceList();
            vector<string> devs = lmsControl->getSerPort()->GetDeviceList();
            for(unsigned i=0; i<devs.size(); ++i)
            {
                if(devs[i] == deviceName)
                {
                    lmsControl->getSerPort()->Open(i);
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                char ctemp[512];
                sprintf(ctemp, "Auto connect: last used device(%s) not found\n", deviceName.c_str());
                MessageLog::getInstance()->write(ctemp, LOG_INFO);
            }
        }
    }
    if(ini.SelectSection("last_used_files"))
    {
        bool loadVCO = ini.Get("load_vco_file", false);
        if(loadVCO)
        {
            string filename = ini.Get("vco_frequencies", "");
            if(filename.length() > 0)
            {
                char ctemp[512];
                if(lmsControl->getPLL_SX()->LoadFromFile(filename.c_str() ) && lmsControl->getPLL_CGEN()->LoadFromFile(filename.c_str() ))
                {
                    sprintf(ctemp, "Loaded VCO frequencies from %s\n", filename.c_str());
                    MessageLog::getInstance()->write(ctemp, LOG_INFO);
                }
                else
                {
                    sprintf(ctemp, "Failed to load VCO frequencies from %s\n", filename.c_str());
                    MessageLog::getInstance()->write(ctemp, LOG_WARNING);
                }
            }
        }
    }
}

void pnlLMS7002::Initialize()
{
    long t1 = getMilis();
    long ti = t1;

    lmsControl->getRegistersMap()->SetAutoUpload(false);
//    tabADF4002->Initialize( lmsControl->getADF() );
//    cout << "ADF4002 initialized in " << getMilis()-ti << " ms" << endl;
//    ti = getMilis();
//    tabSi5351->Initialize( lmsControl->getSi5351() );
//    cout << "Si5356 initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabRFE->Initialize( lmsControl );
    cout << "RFE initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabRBB->Initialize( lmsControl );
    cout << "RBB initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabTRF->Initialize( lmsControl );
    cout << "TRF initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabTBB->Initialize( lmsControl );
    cout << "TBB initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabAFE->Initialize( lmsControl );
    cout << "AFE initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabBIAS->Initialize( lmsControl );
    cout << "BIAS initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabLDO->Initialize( lmsControl );
    cout << "LDO initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabXBUF->Initialize( lmsControl );
    cout << "XBUF initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabCLKGEN->Initialize( lmsControl );
    cout << "CLKGEN initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabSXT->Initialize( lmsControl );
    cout << "SXT initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabLimeLightPAD->Initialize( lmsControl );
    cout << "LIME ligth initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabTxTSP->Initialize( lmsControl );
    cout << "Tx TSP initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabRxTSP->Initialize( lmsControl );
    cout << "Rx TSP initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabBIST->Initialize( lmsControl );
    cout << "BIST initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabCDS->Initialize( lmsControl );
    cout << "CDS initialized in " << getMilis()-ti << " ms" << endl;
    ti = getMilis();
    tabMCU_BD->Initialize(lmsControl);
    cout << "MCU_BD initialized in " << getMilis()-ti << " ms" << endl;

    tabSPI->Initialize(lmsControl);
    cout << "SPI initialized in " << getMilis()-ti << " ms" << endl;
    tabBoard->Initialize(lmsControl->getSi5351(), lmsControl->getADF());
    cout << "Board initialized in " << getMilis()-ti << " ms" << endl;
    tabSocketBoard->Initialize(lmsControl);
    tabBuffersEVB7v2->Initialize(lmsControl);

    tabAlgorithms->Initialize(lmsControl);
    tabAlgorithms->RegisterForNotifications(this);
#ifdef ENABLE_TESTING_UTILITIES
    tabTesting->Initialize(lmsControl);
#endif
    cout << "control panel initialized in " << getMilis()-t1 << " ms" << endl;

    UpdateGUI();
    lmsControl->getRegistersMap()->SetAutoUpload(true);

    m_regMapDlg = new dlgRegisterMap(this);
    m_regMapDlg->Initialize(lmsControl);
    wxCommandEvent evt;
    OnConfiguringChannelsChange(evt);
}

void pnlLMS7002::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlLMS7002)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* controlPanelSizer;
	wxFlexGridSizer* flexgridToolbar;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	controlPanelSizer = new wxFlexGridSizer(3, 1, 0, 0);
	controlPanelSizer->AddGrowableCol(0);
	controlPanelSizer->AddGrowableRow(1);
	flexgridToolbar = new wxFlexGridSizer(0, 7, 0, 5);
	flexgridToolbar->AddGrowableCol(3);
	btnNewProject = new wxButton(this, ID_BUTTON1, _T("New"), wxDefaultPosition, wxSize(50,35), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	flexgridToolbar->Add(btnNewProject, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnOpenProject = new wxButton(this, ID_BUTTON2, _T("Open"), wxDefaultPosition, wxSize(50,35), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	flexgridToolbar->Add(btnOpenProject, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSaveProject = new wxButton(this, ID_BUTTON3, _T("Save"), wxDefaultPosition, wxSize(50,35), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	flexgridToolbar->Add(btnSaveProject, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_channelNameLayout = new wxFlexGridSizer(0, 2, 0, 0);
	m_channelNameLayout->AddGrowableRow(0);
	txtActiveChannel = new wxStaticText(this, ID_STATICTEXT1, _T("Active Ch: A&&B"), wxDefaultPosition, wxSize(327,30), wxALIGN_LEFT, _T("ID_STATICTEXT1"));
	wxFont txtActiveChannelFont(20,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	txtActiveChannel->SetFont(txtActiveChannelFont);
	m_channelNameLayout->Add(txtActiveChannel, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	btnUploadAll = new wxButton(this, ID_BUTTON5, _T("GUI --> Chip"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer4->Add(btnUploadAll, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	btnDownloadAll = new wxButton(this, ID_BUTTON6, _T("Chip --> GUI"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	FlexGridSizer4->Add(btnDownloadAll, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	btnReset = new wxButton(this, ID_BUTTON8, _T("Reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
	FlexGridSizer4->Add(btnReset, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_channelNameLayout->Add(FlexGridSizer4, 1, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	flexgridToolbar->Add(m_channelNameLayout, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Configuring Channels"));
	chkSyncAB = new wxCheckBox(this, ID_CHECKBOX1, _T("Both"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkSyncAB->SetValue(false);
	StaticBoxSizer1->Add(chkSyncAB, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	rbtnEnChannelA = new wxRadioButton(this, ID_RADIOBUTTON1, _T("A/SXR"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	rbtnEnChannelA->SetValue(true);
	StaticBoxSizer1->Add(rbtnEnChannelA, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	rbtnEnChannelB = new wxRadioButton(this, ID_RADIOBUTTON2, _T("B/SXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	StaticBoxSizer1->Add(rbtnEnChannelB, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	flexgridToolbar->Add(StaticBoxSizer1, 1, wxALIGN_RIGHT|wxALIGN_TOP, 5);
	controlPanelSizer->Add(flexgridToolbar, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	m_modulesNotebook = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
	m_modulesNotebook->SetMinSize(wxSize(800,450));
	tabAlgorithms = new pnlAlgorithms(m_modulesNotebook, ID_ALGORITHMTAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_ALGORITHMTAB"));
	tabBoard1 = new wxPanel(m_modulesNotebook, ID_TABBOARD1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TABBOARD1"));
	sizerBoardSetup = new wxFlexGridSizer(0, 3, 0, 0);
	tabBoard = new pnlBoard(tabBoard1, ID_TABBOARD, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TABBOARD"));
	sizerBoardSetup->Add(tabBoard, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	tabBoard1->SetSizer(sizerBoardSetup);
	sizerBoardSetup->Fit(tabBoard1);
	sizerBoardSetup->SetSizeHints(tabBoard1);
	tabRFE = new pnlRFE(m_modulesNotebook, ID_RFE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_RFE"));
	tabRBB = new pnlRBB(m_modulesNotebook, ID_RBB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_RBB"));
	tabTRF = new pnlTRF(m_modulesNotebook, ID_TRF, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TRF"));
	tabTBB = new pnlTBB(m_modulesNotebook, ID_TBB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TBB"));
	tabAFE = new pnlAFE(m_modulesNotebook, ID_AFE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_AFE"));
	tabBIAS = new pnlBIAS(m_modulesNotebook, ID_BIAS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_BIAS"));
	tabLDO = new pnlLDO(m_modulesNotebook, ID_LDO, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_LDO"));
	tabXBUF = new pnlXBUF(m_modulesNotebook, ID_XBUF, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_XBUF"));
	tabCLKGEN = new pnlCLKGEN(m_modulesNotebook, ID_CLKGEN, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_CLKGEN"));
	tabSXT = new pnlSXT(m_modulesNotebook, ID_SXRSXT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_SXRSXT"));
	tabLimeLightPAD = new pnlLimeLightPAD(m_modulesNotebook, ID_LIMELIGHTPAD, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_LIMELIGHTPAD"));
	tabTxTSP = new pnlTxTSP(m_modulesNotebook, ID_TXTSP, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TXTSP"));
	tabRxTSP = new pnlRxTSP(m_modulesNotebook, ID_RXTSP, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_RXTSP"));
	tabCDS = new pnlCDS(m_modulesNotebook, ID_CDS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_CDS"));
	tabMCU_BD = new pnlMCU_BD(m_modulesNotebook, ID_MCUBD, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_MCUBD"));
	tabBIST = new pnlBIST(m_modulesNotebook, ID_BIST, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_BIST"));
	tabSPI = new pnlSPI(m_modulesNotebook, ID_SPITAB, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_SPITAB"));
	m_modulesNotebook->AddPage(tabAlgorithms, _T("Calibrations"), false);
	m_modulesNotebook->AddPage(tabBoard1, _T("Board Setup"), false);
	m_modulesNotebook->AddPage(tabRFE, _T("RFE"), false);
	m_modulesNotebook->AddPage(tabRBB, _T("RBB"), false);
	m_modulesNotebook->AddPage(tabTRF, _T("TRF"), false);
	m_modulesNotebook->AddPage(tabTBB, _T("TBB"), false);
	m_modulesNotebook->AddPage(tabAFE, _T("AFE"), false);
	m_modulesNotebook->AddPage(tabBIAS, _T("BIAS"), false);
	m_modulesNotebook->AddPage(tabLDO, _T("LDO"), false);
	m_modulesNotebook->AddPage(tabXBUF, _T("XBUF"), false);
	m_modulesNotebook->AddPage(tabCLKGEN, _T("CLKGEN"), false);
	m_modulesNotebook->AddPage(tabSXT, _T("SXT/SXR"), false);
	m_modulesNotebook->AddPage(tabLimeLightPAD, _T("LimeLight && PAD"), false);
	m_modulesNotebook->AddPage(tabTxTSP, _T("TxTSP"), false);
	m_modulesNotebook->AddPage(tabRxTSP, _T("RxTSP"), false);
	m_modulesNotebook->AddPage(tabCDS, _T("CDS"), false);
	m_modulesNotebook->AddPage(tabMCU_BD, _T("MCU"), false);
	m_modulesNotebook->AddPage(tabBIST, _T("BIST"), false);
	m_modulesNotebook->AddPage(tabSPI, _T("SPI"), false);
	controlPanelSizer->Add(m_modulesNotebook, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	txtMessageLog = new wxRichTextCtrl(this, ID_CONTROL_PANEL_MSG_LOG, wxEmptyString, wxDefaultPosition, wxSize(-1,20), wxRE_MULTILINE|wxRE_READONLY|wxVSCROLL, wxDefaultValidator, _T("ID_CONTROL_PANEL_MSG_LOG"));
	wxRichTextAttr rchtxtAttr_1;
	rchtxtAttr_1.SetBulletStyle(wxTEXT_ATTR_BULLET_STYLE_ALIGN_LEFT);
	FlexGridSizer1->Add(txtMessageLog, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	btnClearMsgLog = new wxButton(this, ID_BUTTON4, _T("Clear"), wxDefaultPosition, wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer2->Add(btnClearMsgLog, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnShowLog = new wxButton(this, ID_BUTTON7, _T("Log"), wxDefaultPosition, wxSize(40,24), 0, wxDefaultValidator, _T("ID_BUTTON7"));
	FlexGridSizer2->Add(btnShowLog, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	controlPanelSizer->Add(FlexGridSizer1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(controlPanelSizer);
	controlPanelSizer->Fit(this);
	controlPanelSizer->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlLMS7002::OnbtnNewProjectClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlLMS7002::OnbtnOpenProjectClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlLMS7002::OnbtnSaveProjectClick);
	Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlLMS7002::OnbtnUploadAllClick);
	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlLMS7002::OnbtnDownloadAllClick);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlLMS7002::OnbtnResetClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLMS7002::OnConfiguringChannelsChange);
	Connect(ID_RADIOBUTTON1,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&pnlLMS7002::OnConfiguringChannelsChange);
	Connect(ID_RADIOBUTTON2,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&pnlLMS7002::OnConfiguringChannelsChange);
	Connect(ID_NOTEBOOK1,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&pnlLMS7002::Onm_modulesNotebookPageChanged);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlLMS7002::OnbtnClearMsgLogClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlLMS7002::OnbtnShowLogClick);
	//*)
    tabBuffersEVB7v2 = new pnlBuffersEVB7v2(tabBoard1, ID_TABBUFFERSEVB7V2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TABBUFFERSEVB7V2"));
    tabSocketBoard = new pnlSocketBoard(m_modulesNotebook, ID_TABSOCKETBOARD, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TABSOCKETBOARD"));
    tabSocketBoard->Hide();
    sizerBoardSetup->Add(tabBuffersEVB7v2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
    sizerBoardSetup->Layout();
#ifdef ENABLE_TESTING_UTILITIES
    tabTesting = new pnlTesting(m_modulesNotebook, ID_TABTESTING, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_TABTESTING"));
    m_modulesNotebook->AddPage(tabTesting, _("Testing"), false);
#endif
}

pnlLMS7002::~pnlLMS7002()
{
    g_pControlPanel = NULL;
    MessageLog::getInstance()->unregisterFromNotifications( MessageHandler );
    lmsControl->UnregisterFromNotifications(this);
    delete lmsControl;
	//(*Destroy(pnlLMS7002)
	//*)
}

void pnlLMS7002::OnQuit(wxCommandEvent& event)
{
    Close();
}

/** @brief Displays message box with program version and build date
*/
void pnlLMS7002::OnAbout(wxCommandEvent& event)
{
    dlgAbout dlg(this);
    dlg.ShowModal();
}

void pnlLMS7002::OnbtnClearMsgLogClick(wxCommandEvent& event)
{
    txtMessageLog->Clear();
}

void pnlLMS7002::OnbtnFindDevicesClick(wxCommandEvent& event)
{
    lmsControl->FindDevices();
}

void pnlLMS7002::OnmenuConnectionSettingsSelected(wxCommandEvent& event)
{
    dlgConnectionManager *dlg = new dlgConnectionManager(NULL);
    dlg->SetConnectionManager(lmsControl->getSerPort(), NULL);
    dlg->ShowModal();
    delete dlg;
    UpdateStatusBar();
}

void pnlLMS7002::OnbtnNewProjectClick(wxCommandEvent& event)
{
    lmsControl->ResetEverything();
    wxCommandEvent evt;
    OnConfiguringChannelsChange(evt);
    UpdateGUI();
}

void pnlLMS7002::OnbtnUpdateGUIClick(wxCommandEvent& event)
{
    UpdateGUI();
}

void pnlLMS7002::OnbtnOpenProjectClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Open config file"), "", "", "Project-File (*.ini)|*.ini|Project-binary-file (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(dlg.ShowModal() == wxID_CANCEL)
        return;
    lmsControl->LoadFromFile( dlg.GetPath().ToStdString());
    wxCommandEvent tevt;
    OnConfiguringChannelsChange(tevt);
    OnbtnUpdateGUIClick(event);
}

void pnlLMS7002::OnbtnSaveProjectClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Save config file"), "", "", "Project-File (*.ini)|*.ini", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    if(dlg.GetFilterIndex() == 0)
        lmsControl->SaveToFile( dlg.GetPath().ToStdString(), false);
    else
        lmsControl->SaveToFile( dlg.GetPath().ToStdString(), true);
}

void pnlLMS7002::OnbtnUploadAllClick(wxCommandEvent& event)
{
    lmsControl->UploadAll();
    wxCommandEvent evt;
    OnConfiguringChannelsChange(evt);
}

void pnlLMS7002::OnConfiguringChannelsChange(wxCommandEvent& event)
{
    if(rbtnEnChannelA->GetValue() == true)
    {
        SwitchChannel(0, chkSyncAB->GetValue());
    }
    else if(rbtnEnChannelB->GetValue() == true)
    {
        SwitchChannel(1, chkSyncAB->GetValue());
    }
}

void pnlLMS7002::Onmnu_SaveRegistersToFileSelected(wxCommandEvent& event)
{
    OnbtnSaveProjectClick(event);
}

void pnlLMS7002::UpdateGUI()
{
    long t0;
    long t1 = t0 = getMilis();
    long t2 = t1;
        tabRFE->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE RFE " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabRBB->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE RBB " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabTRF->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE TRF " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabTBB->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE TBB " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabAFE->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE AFE " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabLDO->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE LDO " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabBIAS->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE BIAS " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabXBUF->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE XBUF " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabCLKGEN->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE CLKGEN " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabSXT->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE SXT " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabLimeLightPAD->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE LIMELIGHT " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabTxTSP->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE TXTSP " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabRxTSP->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE RXTSP " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabBIST->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE BIST " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabCDS->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE CDS " << t2-t1 << " ms" << endl;
        t1 = t2;
        tabSocketBoard->UpdateGUI();
        tabBuffersEVB7v2->UpdateGUI();
        tabAlgorithms->UpdateGUI();
        //tabTesting->UpdateGUI();
        t2 = getMilis();
        cout << "UPDATE board " << t2-t1 << " ms" << endl;
    wxCommandEvent evt;
    OnConfiguringChannelsChange(evt);
//    int mac = lmsControl->GetParam(MAC, true, true);
//    lmsControl->SelectConfigChannel(mac&0x1?1:0, mac==3);
    cout << "UPDATE GUI " << getMilis()-t0 << " ms" << endl;
}

void pnlLMS7002::MessageHandler(const int signal, const char *msg, const int paraml)
{
    if(g_pControlPanel)
    {
        switch(signal)
        {
        case 1:
            g_pControlPanel->txtMessageLog->AppendText(msg);
            g_pControlPanel->txtMessageLog->ShowPosition(g_pControlPanel->txtMessageLog->GetLastPosition()-1);
            g_pControlPanel->txtMessageLog->Update();
            if(g_pControlPanel->mDlgLog)
                g_pControlPanel->mDlgLog->Write(msg);
            break;
        }
    }
}

void pnlLMS7002::OnbtnDownloadAllClick(wxCommandEvent& event)
{
    lmsControl->DownloadAll();
    wxCommandEvent evt;
    OnConfiguringChannelsChange(evt); //also updates gui
    UpdateGUI();
}

void pnlLMS7002::OnmnuResetChipSelected(wxCommandEvent& event)
{
    lmsControl->ResetChip();
}

void pnlLMS7002::OnbtnShowLogClick(wxCommandEvent& event)
{
    if(mDlgLog == NULL)
        mDlgLog = new dlgMessageLog(this);
    mDlgLog->Show();
}

void pnlLMS7002::OnmnuRegistersTestSelected(wxCommandEvent& event)
{
    dlgRegisterTest dlg(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, lmsControl);
    dlg.ShowModal();
}

void pnlLMS7002::UpdateStatusBar()
{

}

void pnlLMS7002::OnbtnResetClick(wxCommandEvent& event)
{
    lmsControl->ResetChip();
}

void pnlLMS7002::OnmnuReadToHexSelected(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Save config file"), "", "", "Project-binary-file (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    lmsControl->getRegistersMap()->DownloadToHex( dlg.GetPath().ToStdString() );
}

void pnlLMS7002::OnmnuRegistersMapSelected(wxCommandEvent& event)
{
    if(m_regMapDlg)
    {
        m_regMapDlg->Show(true);
        m_regMapDlg->UpdateTables();
    }
}

void pnlLMS7002::SwitchChannel(int channel, bool configBoth)
{
    m_selectedChannel = channel;
    lmsControl->SelectConfigChannel(channel, configBoth);
    chkSyncAB->SetValue(configBoth);

    if(channel == 0)
    {
        rbtnEnChannelA->SetValue(true);
        rbtnEnChannelB->SetValue(false);
    }
    else if(channel == 1)
    {
        rbtnEnChannelA->SetValue(false);
        rbtnEnChannelB->SetValue(true);
    }
    else
    {
        rbtnEnChannelA->SetValue(false);
        rbtnEnChannelB->SetValue(false);
    }
    tabRFE->UpdateGUI();
    tabRBB->UpdateGUI();

    tabTRF->UpdateGUI();

    tabTBB->UpdateGUI();
    tabSXT->UpdateGUI();

    tabTxTSP->UpdateGUI();
    tabRxTSP->UpdateGUI();
    tabAlgorithms->UpdateGUI();

    int pageSel = m_modulesNotebook->GetSelection();
    wxNotebookPage *page = m_modulesNotebook->GetPage(pageSel);
    if(page == NULL)
        return;
    int pageId = page->GetId();

    if(pageId == ID_SXRSXT)
    {
        if(chkSyncAB->GetValue() == true)
        {
            txtActiveChannel->SetLabel("Active Ch: SXR&&SXT");
        }
        else if(m_selectedChannel == 0)
            txtActiveChannel->SetLabel("Active Ch: SXR");
        else if(m_selectedChannel == 1)
            txtActiveChannel->SetLabel("Active Ch: SXT");
    }
    else
    {

    if(configBoth)
    {
        txtActiveChannel->SetLabel("Active Ch: A&&B");
    }
    else if(channel == 0)
        txtActiveChannel->SetLabel("Active Ch: A");
    else if(channel == 1)
        txtActiveChannel->SetLabel("Active Ch: B");
    }
}

void pnlLMS7002::Onm_modulesNotebookPageChanged(wxNotebookEvent& event)
{
    int pageSel = event.GetSelection();
    wxNotebookPage *page = m_modulesNotebook->GetPage(pageSel);

    long pageId = page->GetId();

    if(pageId == tabSXT->GetId())
    {
        if(chkSyncAB->GetValue() == true)
        {
            txtActiveChannel->SetLabel("Active Ch: SXR&&SXT");
        }
        else if(m_selectedChannel == 0)
            txtActiveChannel->SetLabel("Active Ch: SXR");
        else if(m_selectedChannel == 1)
            txtActiveChannel->SetLabel("Active Ch: SXT");
    }
    else
    {

    if(chkSyncAB->GetValue() == true)
    {
        txtActiveChannel->SetLabel("Active Ch: A&&B");
    }
    else if(m_selectedChannel == 0)
        txtActiveChannel->SetLabel("Active Ch: A");
    else if(m_selectedChannel == 1)
        txtActiveChannel->SetLabel("Active Ch: B");
    }

    if(pageId == tabAFE->GetId() || pageId==tabBIAS->GetId() || pageId==tabXBUF->GetId() || pageId == tabCLKGEN->GetId() || pageId==tabLDO->GetId() || pageId==tabBIAS->GetId())
    {
        if(m_overrideChannel == false)
        {
            m_overrideChannel = true;
            m_lastUsedChannel = m_selectedChannel;
        }
        SwitchChannel(0, false);
    }
    else
    {
        if(m_overrideChannel == true)
        {
            m_overrideChannel = false;
            SwitchChannel(m_lastUsedChannel, false);
        }
    }
}

void pnlLMS7002::OnmnuSaveRegistersRVHEXSelected(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Save rv-hex"), "", "", "Registers rv-hex (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if(dlg.ShowModal() == wxID_CANCEL)
        return;
    lmsControl->CreateConfigurationInstructions(dlg.GetPath().ToStdString());
}

void pnlLMS7002::Onmnu_VerifyWrittenDataSelected(wxCommandEvent& event)
{
    //lmsControl->getSerPort()->EnableTestWrittenData(mnu_VerifyWrittenData->IsChecked());
}

void pnlLMS7002::AddTab(wxNotebookPage* tab, wxString title)
{
    if(m_modulesNotebook->FindPage(tab) == wxNOT_FOUND)
        m_modulesNotebook->InsertPage(m_modulesNotebook->GetPageCount(), tab, title);
}

bool pnlLMS7002::RemoveTab(const long windowID)
{
    wxWindow *page;
    for(unsigned int i=0; i<m_modulesNotebook->GetPageCount(); ++i)
    {
        page = m_modulesNotebook->GetPage(i);
        if(page->GetId() == windowID )
        {
            m_modulesNotebook->RemovePage(i);
            return true;
        }
    }
    return false;
}

LMS7002_MainControl* pnlLMS7002::getLMScontrol()
{
    return lmsControl;
}
