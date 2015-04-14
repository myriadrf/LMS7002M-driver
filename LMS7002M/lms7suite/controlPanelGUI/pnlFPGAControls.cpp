/**
@file pnlFPGAControls.cpp
@author Lime Microsystems
@brief panel combining controls for on board FPGA
*/
#include "pnlFPGAControls.h"

//(*InternalHeaders(pnlFPGAControls)
#include <wx/sizer.h>
#include <wx/string.h>
//*)

#include "ConnectionManager.h"
#include "pnlWFMLoader.h"

//(*IdInit(pnlFPGAControls)
//*)

BEGIN_EVENT_TABLE(pnlFPGAControls,wxPanel)
	//(*EventTable(pnlFPGAControls)
	//*)
END_EVENT_TABLE()

pnlFPGAControls::pnlFPGAControls(ConnectionManager* pSerPort, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    : PluginPanel(this)
{
    m_serPort = pSerPort;
	BuildContent(parent,id,pos,size);
	mWFM = new pnlWFMLoader(m_serPort, this, wxNewId());
	mPanelContainer->Add(mWFM, 1, wxFIXED_MINSIZE|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	mPanelContainer->Fit(this);
	mPanelContainer->SetSizeHints(this);
}

void pnlFPGAControls::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlFPGAControls)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	mPanelContainer = new wxFlexGridSizer(0, 1, 0, 0);
	mPanelContainer->AddGrowableCol(0);
	SetSizer(mPanelContainer);
	mPanelContainer->Fit(this);
	mPanelContainer->SetSizeHints(this);
	//*)
}

pnlFPGAControls::~pnlFPGAControls()
{
    mWFM->Destroy();
	//(*Destroy(pnlFPGAControls)
	//*)
}

