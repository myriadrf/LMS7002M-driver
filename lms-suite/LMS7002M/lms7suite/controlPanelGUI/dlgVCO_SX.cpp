/**
@file dlgVCO_SX.cpp
@author Lime Microsystems
@brief dialog for displaying VCO frequency data
*/

#include "dlgVCO_SX.h"
#include "PLL_SX.h"
#include "PLL_CGEN.h"
#include <vector>
#include <wx/filedlg.h>
#include <fstream>
#include "iniParser.h"
//(*InternalHeaders(dlgVCO_SX)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/string.h>
//*)

//(*IdInit(dlgVCO_SX)
const long dlgVCO_SX::ID_PANEL1 = wxNewId();
const long dlgVCO_SX::ID_PANEL2 = wxNewId();
const long dlgVCO_SX::ID_PANEL3 = wxNewId();
const long dlgVCO_SX::ID_PANEL4 = wxNewId();
const long dlgVCO_SX::ID_BUTTON1 = wxNewId();
const long dlgVCO_SX::ID_BUTTON2 = wxNewId();
const long dlgVCO_SX::ID_BUTTON3 = wxNewId();
const long dlgVCO_SX::ID_BUTTON4 = wxNewId();
const long dlgVCO_SX::ID_CHECKBOX1 = wxNewId();
const long dlgVCO_SX::ID_STATICTEXT1 = wxNewId();
const long dlgVCO_SX::ID_STATICTEXT2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dlgVCO_SX,wxDialog)
	//(*EventTable(dlgVCO_SX)
	//*)
END_EVENT_TABLE()

dlgVCO_SX::dlgVCO_SX( PLL_SX *data, PLL_CGEN *data_cgen, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    pll_data = data;
    pll_data_cgen = data_cgen;
	BuildContent(parent,id,pos,size);
}

void dlgVCO_SX::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(dlgVCO_SX)
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _T("VCO Frequencies"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 4, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(0);
	pnlVCOH = new pnlFreqTable(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer2->Add(pnlVCOH, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pnlVCOM = new pnlFreqTable(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer2->Add(pnlVCOM, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pnlVCOL = new pnlFreqTable(this, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	FlexGridSizer2->Add(pnlVCOL, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pnlVCO_CGEN = new pnlFreqTable(this, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	FlexGridSizer2->Add(pnlVCO_CGEN, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 6, 0, 0);
	btnOK = new wxButton(this, ID_BUTTON1, _T("Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(btnOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnCancel = new wxButton(this, ID_BUTTON2, _T("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer3->Add(btnCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnLoad = new wxButton(this, ID_BUTTON3, _T("Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer3->Add(btnLoad, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btnSave = new wxButton(this, ID_BUTTON4, _T("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer3->Add(btnSave, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	chkLoadFileOnStartup = new wxCheckBox(this, ID_CHECKBOX1, _T("Load file on startup"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	chkLoadFileOnStartup->SetValue(false);
	FlexGridSizer4->Add(chkLoadFileOnStartup, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("File:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer4->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblFilename = new wxStaticText(this, ID_STATICTEXT2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer4->Add(lblFilename, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer4, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgVCO_SX::OnbtnOKClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgVCO_SX::OnbtnCancelClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgVCO_SX::OnbtnLoadClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dlgVCO_SX::OnbtnSaveClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dlgVCO_SX::OnchkLoadFileOnStartupClick);
	Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&dlgVCO_SX::OnInit);
	//*)
}

dlgVCO_SX::~dlgVCO_SX()
{
	//(*Destroy(dlgVCO_SX)
	//*)
}


void dlgVCO_SX::OnInit(wxInitDialogEvent& event)
{
    vector<double> freqs;
    freqs = pll_data->GetVCOHFrequencies();
    for(unsigned i=0; i<freqs.size(); ++i)
        freqs[i] = freqs[i]/1000; // convert from MHz to GHz
    pnlVCOH->Initialize("VCOH SXR/SXT", freqs);

    freqs = pll_data->GetVCOMFrequencies();
    for(unsigned i=0; i<freqs.size(); ++i)
        freqs[i] = freqs[i]/1000; // convert from MHz to GHz
    pnlVCOM->Initialize("VCOM SXR/SXT", freqs);

    freqs = pll_data->GetVCOLFrequencies();
    for(unsigned i=0; i<freqs.size(); ++i)
        freqs[i] = freqs[i]/1000; // convert from MHz to GHz
    pnlVCOL->Initialize("VCOL SXR/SXT", freqs);

    freqs = pll_data_cgen->GetVCOFrequencies();
    for(unsigned i=0; i<freqs.size(); ++i)
        freqs[i] = freqs[i]/1000; // convert from MHz to GHz
    pnlVCO_CGEN->Initialize("VCO_CGEN", freqs);

    iniParser ini;
    ini.Open("gui_settings.ini");
    if(ini.SelectSection("last_used_files"))
    {
        bool loadVCO = ini.Get("load_vco_file", false);
        chkLoadFileOnStartup->SetValue(loadVCO);
        string filename = ini.Get("vco_frequencies", "");
        lblFilename->SetLabel(filename);
    }
}

void dlgVCO_SX::OnbtnOKClick(wxCommandEvent& event)
{
    vector<double> freqs;
    freqs.clear();
    freqs = pnlVCOH->GetFrequencies();
    for(unsigned i=0; i<freqs.size(); ++i)
        freqs[i] = freqs[i]*1000; // convert from GHz to MHz
    pll_data->SetVCOHFrequencies(&freqs[0], freqs.size());

    freqs.clear();
    freqs = pnlVCOM->GetFrequencies();
    for(unsigned i=0; i<freqs.size(); ++i)
        freqs[i] = freqs[i]*1000; // convert from GHz to MHz
    pll_data->SetVCOMFrequencies(&freqs[0], freqs.size());

    freqs.clear();
    freqs = pnlVCOL->GetFrequencies();
    for(unsigned i=0; i<freqs.size(); ++i)
        freqs[i] = freqs[i]*1000; // convert from GHz to MHz
    pll_data->SetVCOLFrequencies(&freqs[0], freqs.size());

    freqs.clear();
    freqs = pnlVCO_CGEN->GetFrequencies();
    for(unsigned i=0; i<freqs.size(); ++i)
        freqs[i] = freqs[i]*1000; // convert from GHz to MHz
    pll_data_cgen->SetVCOFrequencies(&freqs[0], freqs.size());

    SaveConfig();
    EndModal(wxID_OK);
}

void dlgVCO_SX::OnbtnCancelClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

void dlgVCO_SX::OnbtnLoadClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Open vco file"), "", "", "text (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(dlg.ShowModal() == wxID_CANCEL)
        return;
    fstream fin;
    fin.open(dlg.GetPath().ToStdString().c_str(), ios::in);

    char cline[128];
    int lineLen = 128;

    char vconame[80];
    char ctemp[80];
    double freq = 0;
    int freqCount = 0;

    vector<double> frequencies;

    while(!fin.eof())
    {
        freqCount = 0;
        fin.getline(cline, lineLen);
        //find name and frequency count
        sscanf(cline, "%s %s %i", vconame, ctemp, &freqCount);
        if(strcmp(vconame, "[VCOH]") == 0)
        {
            frequencies.clear();
            for(int i=0; i<freqCount; ++i)
            {
                fin.getline(cline, lineLen);
                sscanf(cline, "%lf %s", &freq, ctemp);
                frequencies.push_back(freq);
            }
            pnlVCOH->Initialize("VCOH", frequencies);
        }
        if(strcmp(vconame, "[VCOM]") == 0)
        {
            frequencies.clear();
            for(int i=0; i<freqCount; ++i)
            {
                fin.getline(cline, lineLen);
                sscanf(cline, "%lf %s", &freq, ctemp);
                frequencies.push_back(freq);
            }
            pnlVCOM->Initialize("VCOM", frequencies);
        }
        if(strcmp(vconame, "[VCOL]") == 0)
        {
            frequencies.clear();
            for(int i=0; i<freqCount; ++i)
            {
                fin.getline(cline, lineLen);
                sscanf(cline, "%lf %s", &freq, ctemp);
                frequencies.push_back(freq);
            }
            pnlVCOL->Initialize("VCOL", frequencies);
        }
        if(strcmp(vconame, "[VCO_CGEN]") == 0)
        {
            frequencies.clear();
            for(int i=0; i<freqCount; ++i)
            {
                fin.getline(cline, lineLen);
                sscanf(cline, "%lf %s", &freq, ctemp);
                frequencies.push_back(freq);
            }
            pnlVCO_CGEN->Initialize("VCO_CGEN", frequencies);
        }
        vconame[0] = 0;
    }
    fin.close();
    lblFilename->SetLabel(dlg.GetPath());
}

void dlgVCO_SX::OnbtnSaveClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Save vco file"), "", "", "text (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if(dlg.ShowModal() == wxID_CANCEL)
        return;
    fstream fout;
    fout.open(dlg.GetPath().ToStdString().c_str(), ios::out);

    vector<double> freqs;
    freqs.clear();
    freqs = pnlVCOH->GetFrequencies();
    fout << "[VCOH] count: " << freqs.size() << "," << endl;
    for(unsigned i=0; i<freqs.size(); ++i)
        fout << freqs[i] << ' ' << "GHz," << endl;

    freqs.clear();
    freqs = pnlVCOM->GetFrequencies();
    fout << "[VCOM] count: " << freqs.size() << ","  << endl;
    for(unsigned i=0; i<freqs.size(); ++i)
        fout << freqs[i] << ' ' << "GHz," << endl;

    freqs.clear();
    freqs = pnlVCOL->GetFrequencies();
    fout << "[VCOL] count: " << freqs.size() << ","  << endl;
    for(unsigned i=0; i<freqs.size(); ++i)
        fout << freqs[i] << ' ' << "GHz," << endl;

    freqs.clear();
    freqs = pnlVCO_CGEN->GetFrequencies();
    fout << "[VCO_CGEN] count: " << freqs.size() << ","  << endl;
    for(unsigned i=0; i<freqs.size(); ++i)
        fout << freqs[i] << ' ' << "GHz," << endl;

    fout.close();
}

void dlgVCO_SX::OnchkLoadFileOnStartupClick(wxCommandEvent& event)
{
    SaveConfig();
}

void dlgVCO_SX::SaveConfig()
{
    iniParser ini;
    ini.Open("gui_settings.ini");
    if(ini.SelectSection("last_used_files"))
    {
        ini.Set("load_vco_file", chkLoadFileOnStartup->GetValue());
        ini.Set("vco_frequencies", lblFilename->GetLabel().ToStdString().c_str());
    }
    ini.Save();
}
