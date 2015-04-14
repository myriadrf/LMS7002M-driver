/**
@file 	pnlWFMLoader.cpp
@author Lime Microsystems
@brief 	panel for uploading WFM files to board
*/
#include "pnlWFMLoader.h"
#include "CommonUtilities.h"
//(*InternalHeaders(pnlWFMLoader)
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/image.h>
#include <wx/string.h>
#include <wx/gauge.h>
//*)

#include <vector>
#include "ConnectionManager.h"
#include <fstream>
#include <wx/ffile.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include "fft/iniParser.h"
//(*IdInit(pnlWFMLoader)
const long pnlWFMLoader::ID_BUTTON6 = wxNewId();
const long pnlWFMLoader::ID_BUTTON7 = wxNewId();
const long pnlWFMLoader::ID_BUTTON8 = wxNewId();
const long pnlWFMLoader::ID_BITMAPBUTTON1 = wxNewId();
const long pnlWFMLoader::ID_STATICTEXT2 = wxNewId();
const long pnlWFMLoader::ID_STATICTEXT5 = wxNewId();
const long pnlWFMLoader::ID_GAUGE1 = wxNewId();
const long pnlWFMLoader::ID_BUTTON3 = wxNewId();
const long pnlWFMLoader::ID_BUTTON4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(pnlWFMLoader,wxPanel)
	//(*EventTable(pnlWFMLoader)
	//*)
END_EVENT_TABLE()

pnlWFMLoader::pnlWFMLoader(ConnectionManager* pSerPort, wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size):
    PluginPanel(this)
{
    m_serPort = pSerPort;
	BuildContent(parent,id,pos,size);
    wxDir dir(wxGetCwd()+"/lms7suite_wfm");
    if ( !dir.IsOpened() )
    {
        dir.Make("lms7suite_wfm");
    }
}

void pnlWFMLoader::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(pnlWFMLoader)
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("WFM loader"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 1, 5, 0);
	FlexGridSizer6->AddGrowableCol(0);
	FlexGridSizer8 = new wxFlexGridSizer(0, 3, 0, 5);
	btnLoadOnetone = new wxButton(this, ID_BUTTON6, _T("Onetone"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON6"));
	btnLoadOnetone->SetToolTip(_T("Loads file named onetone.wfm"));
	FlexGridSizer8->Add(btnLoadOnetone, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnLoadWCDMA = new wxButton(this, ID_BUTTON7, _T("W-CDMA"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	btnLoadWCDMA->SetToolTip(_T("Loads file named wcdma.wfm"));
	FlexGridSizer8->Add(btnLoadWCDMA, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6->Add(FlexGridSizer8, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer10 = new wxFlexGridSizer(0, 3, 0, 5);
	FlexGridSizer10->AddGrowableCol(2);
	btnLoadCustom = new wxButton(this, ID_BUTTON8, _T("Custom"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON8"));
	btnLoadCustom->SetToolTip(_T("Loads user selected custom file"));
	FlexGridSizer10->Add(btnLoadCustom, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnOpenWFM = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	FlexGridSizer10->Add(btnOpenWFM, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	txtFilename = new wxStaticText(this, ID_STATICTEXT2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxST_ELLIPSIZE_START, _T("ID_STATICTEXT2"));
	FlexGridSizer10->Add(txtFilename, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer10, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer3->AddGrowableCol(1);
	lblProgressPercent = new wxStaticText(this, ID_STATICTEXT5, _T("0 %"), wxDefaultPosition, wxSize(32,-1), 0, _T("ID_STATICTEXT5"));
	FlexGridSizer3->Add(lblProgressPercent, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	progressBar = new wxGauge(this, ID_GAUGE1, 100, wxDefaultPosition, wxSize(-1,10), 0, wxDefaultValidator, _T("ID_GAUGE1"));
	FlexGridSizer3->Add(progressBar, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6->Add(FlexGridSizer3, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 5);
	btnPlayWFM = new wxButton(this, ID_BUTTON3, _T("Play >"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer2->Add(btnPlayWFM, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	btnStopWFM = new wxButton(this, ID_BUTTON4, _T("Stop ||"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer2->Add(btnStopWFM, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer6->Add(FlexGridSizer2, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizer3->Add(FlexGridSizer6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
	FlexGridSizer1->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlWFMLoader::OnbtnLoadOnetoneClick);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlWFMLoader::OnbtnLoadWCDMAClick);
	Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlWFMLoader::OnbtnLoadCustomClick);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlWFMLoader::OnbtnOpenFileClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlWFMLoader::OnbtnPlayWFMClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlWFMLoader::OnbtnStopWFMClick);
	//*)
}

pnlWFMLoader::~pnlWFMLoader()
{
	//(*Destroy(pnlWFMLoader)
	//*)
}

int ReadWFM(const wxString filename, const char *file_output, std::vector< std::pair<int, int> > &iq_pairs)
{
	if (filename.length() <= 1)
		return 0;
    wxFFile fpin(filename, "rb");
    //FILE *fpout;				// File pointers
    unsigned char inputBuffer[4];
    unsigned char c1, c2, c3, c4;			// To read Agilent Signal Studio file
    double iin, qin;			// IQ inputs
    int iint, qint;					// IQ integer versions
    int cnt = 0;

    if( fpin.IsOpened() == false)
    {
        printf("WFM Converter: Input file can not be opened.");
        return -1;
    }

    /*if ((fpout = fopen(file_output, "w")) == NULL)
    {
        printf("WFM Converter: Cannot open output file.");
        return -2;
    }*/

    while( fpin.Read(inputBuffer, 4) == 4 )
    {
        c1 = inputBuffer[0];
        c2 = inputBuffer[1];
        c3 = inputBuffer[2];
        c4 = inputBuffer[3];

        cnt++;

        c1 &= 0xFF;
        c2 &= 0xFF;
        c3 &= 0xFF;
        c4 &= 0xFF;

        if( c1&0x80 ) iin = (double)(-1*(1<<15) + ((c1&0x7F)<<8) + c2);
        else iin = (double)(((c1&0x7F)<<8) + c2);

        if( c3&0x80 ) qin = (double)(-1*(1<<15) + ((c3&0x7F)<<8) + c4);
        else qin = (double)(((c3&0x7F)<<8) + c4);

        iint = (int)(iin);
        qint = (int)(qin);

        iint = iint >> 4;
        qint = qint >> 4;

        iq_pairs.push_back( std::pair<int, int>(iint, qint) );
        //fprintf(fpout, "%10d%10d\n", iint, qint);

    };
    //fclose(fpout);
    return 0;
}

void pnlWFMLoader::OnbtnOpenFileClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this, _("Open file"), "", "", "wfm (*.wfm)|*.wfm", wxFD_OPEN);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;
    txtFilename->SetLabelText( dlg.GetPath().c_str() );
    Layout();
}

void pnlWFMLoader::OnbtnMifClick(wxCommandEvent& event)
{
    vector< pair<int,int> > iq_pairs;
    if(txtFilename->GetLabel().size() == 0)
    {
        wxMessageBox("File not selected", "Error");
        return;
    }
    if( ReadWFM(txtFilename->GetLabel(), "output.txt", iq_pairs) < 0)
        return;
    int bufferSize = iq_pairs.size()*2;
    unsigned short *buffer = new unsigned short[bufferSize];
    memset(buffer, 0, bufferSize);
    short ii = 0;
    short qq = 0;

    wxFileDialog dlg(this, _("Save .mif file"), "", "", "mif (*.mif)|*.mif", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;

    ofstream fout;
    fout.open(dlg.GetPath().ToStdString().c_str(), ios::out);
    fout << "WIDTH=13;" << endl;
    fout << "DEPTH=" << iq_pairs.size()*2 << ";" << endl << endl;
    fout << "ADDRESS_RADIX=UNS;" << endl;
    fout << "DATA_RADIX=HEX;" << endl << endl;
    fout << "CONTENT BEGIN" << endl;
    int addr = 0;
    for(unsigned i=0; i<iq_pairs.size(); ++i)
    {
        ii = iq_pairs[i].first;
        qq = iq_pairs[i].second;
        ii = (ii & 0xFFF) | 0x1000;
        fout << "\t" << addr << " : " << uint2hex(ii, 2) << ";" << endl;
        ++addr;
        qq = (qq & 0xFFF);
        fout << "\t" << addr << " : " << uint2hex(qq, 2) << ";" << endl;
        ++addr;
    }
    fout << "END;" << endl;
    fout.close();
    return;
}

void pnlWFMLoader::OnbtnHexClick(wxCommandEvent& event)
{
    vector< pair<int,int> > iq_pairs;
    if(txtFilename->GetLabel().size() == 0)
    {
        wxMessageBox("File not selected", "Error");
        return;
    }
    ReadWFM(txtFilename->GetLabel(), "output.txt", iq_pairs);
    int bufferSize = iq_pairs.size()*2;
    unsigned short *buffer = new unsigned short[bufferSize];
    memset(buffer, 0, bufferSize);
    short ii = 0;
    short qq = 0;

    wxFileDialog dlg(this, _("Save .txt file"), "", "", "txt (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dlg.ShowModal() == wxID_CANCEL)
        return;

    ofstream fout;
    fout.open(dlg.GetPath().ToStdString().c_str(), ios::out);
    int addr = 0;
    for(unsigned i=0; i<iq_pairs.size(); ++i)
    {
        ii = iq_pairs[i].first;
        qq = iq_pairs[i].second;
        ii = (ii & 0xFFF);
        fout << "x" << addr << "\"" << uint2hex(ii, 2) << "\"," << endl;
        ++addr;
        qq = (qq & 0xFFF);
        fout << "x" << addr << "\"" << uint2hex(qq, 2) << "\"," << endl;
        ++addr;
    }
    fout.close();
}

void pnlWFMLoader::OnbtnPlayWFMClick(wxCommandEvent& event)
{
    unsigned char ctrbuf[64];
    unsigned char inbuf[64];
    memset(ctrbuf, 0, 64);
    memset(inbuf, 0, 64);
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
    ctrbuf[11] = inbuf[11] | 0x3;
    m_serPort->Port_write_direct(ctrbuf, 64);
    len = 64;
    m_serPort->Port_read_direct(inbuf, len);
}

void pnlWFMLoader::OnbtnStopWFMClick(wxCommandEvent& event)
{
    unsigned char ctrbuf[64];
    unsigned char inbuf[64];
    memset(ctrbuf, 0, 64);
    memset(inbuf, 0, 64);
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
    ctrbuf[11] = (inbuf[11] & ~0x2) | 0x1;
    m_serPort->Port_write_direct(ctrbuf, 64);
    len = 64;
    m_serPort->Port_read_direct(inbuf, len);
}

int pnlWFMLoader::UploadFile(const char* filename)
{
    if(m_serPort->IsOpen())
    {
        vector< pair<int,int> > iq_pairs;
        if(strlen(filename) == 0)
        {
            wxMessageBox("File not selected", "Error");
            return -1;
        }
        if( ReadWFM(filename, "output.txt", iq_pairs) < 0)
        {
            wxMessageBox("File not found", "Error");
            return -1;
        }
        int bufferSize = iq_pairs.size()*2;
        unsigned short *buffer = new unsigned short[bufferSize];
        memset(buffer, 0, bufferSize);
        int bufPos = 0;
        short ii = 0;
        short qq = 0;
        for(unsigned i=0; i<iq_pairs.size(); ++i)
        {
            ii = iq_pairs[i].first;
            qq = iq_pairs[i].second;
            buffer[bufPos] = (ii & 0xFFF);
            buffer[bufPos+1] = (qq & 0xFFF) | 0x1000;
            bufPos += 2;
        }
        const long outLen = bufPos*2;
        int packetSize = 65536;
        progressBar->SetRange(outLen/packetSize);
        progressBar->SetValue(0);
        int sent = 0;
        bool success = true;

        btnPlayWFM->Enable(false);
        btnStopWFM->Enable(false);

        unsigned char ctrbuf[64];
        unsigned char inbuf[64];
        memset(ctrbuf, 0, 64);
        memset(inbuf, 0, 64);
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
        ctrbuf[11] = inbuf[11] & ~0x7;
        m_serPort->Port_write_direct(ctrbuf, 64);
        len = 64;
        m_serPort->Port_read_direct(inbuf, len);
        while(sent<outLen)
        {
            char *outBuf = (char*)buffer;
            const long toSendBytes = outLen-sent > packetSize ? packetSize : outLen-sent;
            long toSend = toSendBytes;
            int context = m_serPort->BeginDataSending(&outBuf[sent], toSend);
            if(m_serPort->WaitForSending(context, 5000) == false)
            {
                success = false;
                break;
            }
            m_serPort->FinishDataSending(&outBuf[sent], toSend, context);
            sent += toSendBytes;
            progressBar->SetValue(progressBar->GetValue()+1);
            lblProgressPercent->SetLabel(wxString::Format("%3.0f%%", 100.0*sent/outLen));
        }
        progressBar->SetValue(progressBar->GetRange());
        lblProgressPercent->SetLabelText("100%");

        memset(ctrbuf, 0, 64);
        memset(inbuf, 0, 64);
        ctrbuf[0] = CMD_BRDSPI_RD;
        ctrbuf[1] = 0;
        ctrbuf[2] = 0x01;
        ctrbuf[8] = 0x00;
        ctrbuf[9] = 0x05;
        m_serPort->Port_write_direct(ctrbuf, 64);
        len = 64;
        m_serPort->Port_read_direct(inbuf, len);

        memset(ctrbuf, 0, 64);
        ctrbuf[0] = CMD_BRDSPI_WR;
        ctrbuf[1] = 0;
        ctrbuf[2] = 0x01;
        ctrbuf[8] = 0x00;
        ctrbuf[9] = 0x05;
        ctrbuf[10] = inbuf[10];
        ctrbuf[11] = inbuf[11] | 0x3;
        m_serPort->Port_write_direct(ctrbuf, 64);
        len = 64;
        m_serPort->Port_read_direct(inbuf, len);

        btnPlayWFM->Enable(true);
        btnStopWFM->Enable(true);

		if (!success)
		{
			wxMessageBox("Failed to upload WFM file", "Error");
			return -3;
		}
		else
			return 0;
    }
    else
        wxMessageBox("Device not connected", "Error");
	return -2;
}

void pnlWFMLoader::OnbtnLoadOnetoneClick(wxCommandEvent& event)
{
    if( UploadFile("lms7suite_wfm/onetone.wfm") == -1)
        wxMessageBox("File not found onetone.wfm", "Error");
}

void pnlWFMLoader::OnbtnLoadWCDMAClick(wxCommandEvent& event)
{
    if( UploadFile("lms7suite_wfm/wcdma.wfm") == -1)
        wxMessageBox("File not found wcdma.wfm", "Error");
}

void pnlWFMLoader::OnbtnLoadCustomClick(wxCommandEvent& event)
{
    UploadFile(txtFilename->GetLabel());
}
