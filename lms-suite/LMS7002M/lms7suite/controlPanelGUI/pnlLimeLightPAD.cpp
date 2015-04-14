/**
@file	pnlLimeLightPAD.cpp
@author	Lime Microsystems
@brief	Lime Light and PAD modules panel
*/

#include "pnlLimeLightPAD.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "LMS7002_MainControl.h"
//(*InternalHeaders(pnlLimeLightPAD)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/statline.h>
#include <wx/intl.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)
//(*IdInit(pnlLimeLightPAD)
const long pnlLimeLightPAD::ID_TX_CLK_PE = wxNewId();
const long pnlLimeLightPAD::ID_RX_CLK_PE = wxNewId();
const long pnlLimeLightPAD::ID_SDA_PE = wxNewId();
const long pnlLimeLightPAD::ID_SCL_PE = wxNewId();
const long pnlLimeLightPAD::ID_SDIO_PE = wxNewId();
const long pnlLimeLightPAD::ID_SDO_PE = wxNewId();
const long pnlLimeLightPAD::ID_SCLK_PE = wxNewId();
const long pnlLimeLightPAD::ID_SEN_PE = wxNewId();
const long pnlLimeLightPAD::ID_DIQ2_PE = wxNewId();
const long pnlLimeLightPAD::ID_IQ_SEL_EN_2_PE = wxNewId();
const long pnlLimeLightPAD::ID_TXNRX2_PE = wxNewId();
const long pnlLimeLightPAD::ID_FCLK2_PE = wxNewId();
const long pnlLimeLightPAD::ID_MCLK2_PE = wxNewId();
const long pnlLimeLightPAD::ID_DIQ1_PE = wxNewId();
const long pnlLimeLightPAD::ID_IQ_SEL_EN_1_PE = wxNewId();
const long pnlLimeLightPAD::ID_TXNRX1_PE = wxNewId();
const long pnlLimeLightPAD::ID_FCLK1_PE = wxNewId();
const long pnlLimeLightPAD::ID_MCLK1_PE = wxNewId();
const long pnlLimeLightPAD::ID_MOD_EN = wxNewId();
const long pnlLimeLightPAD::ID_STATICLINE1 = wxNewId();
const long pnlLimeLightPAD::ID_LML_FIDM1 = wxNewId();
const long pnlLimeLightPAD::ID_LML_FIDM2 = wxNewId();
const long pnlLimeLightPAD::ID_LML_MODE1 = wxNewId();
const long pnlLimeLightPAD::ID_LML_MODE2 = wxNewId();
const long pnlLimeLightPAD::ID_LML_TXNRXIQ1 = wxNewId();
const long pnlLimeLightPAD::ID_LML_TXNRXIQ2 = wxNewId();
const long pnlLimeLightPAD::ID_LRST_TX_B = wxNewId();
const long pnlLimeLightPAD::ID_MRST_TX_B = wxNewId();
const long pnlLimeLightPAD::ID_LRST_TX_A = wxNewId();
const long pnlLimeLightPAD::ID_MRST_TX_A = wxNewId();
const long pnlLimeLightPAD::ID_LRST_RX_B = wxNewId();
const long pnlLimeLightPAD::ID_MRST_RX_B = wxNewId();
const long pnlLimeLightPAD::ID_LRST_RX_A = wxNewId();
const long pnlLimeLightPAD::ID_MRST_RX_A = wxNewId();
const long pnlLimeLightPAD::ID_SRST_RXFIFO = wxNewId();
const long pnlLimeLightPAD::ID_SRST_TXFIFO = wxNewId();
const long pnlLimeLightPAD::ID_SDA_DS = wxNewId();
const long pnlLimeLightPAD::ID_SCL_DS = wxNewId();
const long pnlLimeLightPAD::ID_SDIO_DS = wxNewId();
const long pnlLimeLightPAD::ID_DIQ2_DS = wxNewId();
const long pnlLimeLightPAD::ID_DIQ1_DS = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT33 = wxNewId();
const long pnlLimeLightPAD::ID_RX_MUX = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT34 = wxNewId();
const long pnlLimeLightPAD::ID_TX_MUX = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT35 = wxNewId();
const long pnlLimeLightPAD::ID_MIMO_SISO = wxNewId();
const long pnlLimeLightPAD::ID_SPIMODE = wxNewId();
const long pnlLimeLightPAD::ID_MAC = wxNewId();
const long pnlLimeLightPAD::ID_RXEN_B = wxNewId();
const long pnlLimeLightPAD::ID_RXEN_A = wxNewId();
const long pnlLimeLightPAD::ID_TXEN_B = wxNewId();
const long pnlLimeLightPAD::ID_TXEN_A = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT36 = wxNewId();
const long pnlLimeLightPAD::ID_VER = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT38 = wxNewId();
const long pnlLimeLightPAD::ID_REV = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT40 = wxNewId();
const long pnlLimeLightPAD::ID_MASK = wxNewId();
const long pnlLimeLightPAD::ID_BUTTON1 = wxNewId();
const long pnlLimeLightPAD::ID_PANEL1 = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT1 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_S3S = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT2 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_S2S = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT3 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_S1S = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT4 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_S0S = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT5 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_BQP = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT6 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_BIP = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT7 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_AQP = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT8 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_AIP = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT9 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_S3S = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT10 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_S2S = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT11 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_S1S = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT12 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_S0S = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT13 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_BQP = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT14 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_BIP = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT15 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_AQP = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT16 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_AIP = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT25 = wxNewId();
const long pnlLimeLightPAD::ID_TXRDCLK_MUX = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT26 = wxNewId();
const long pnlLimeLightPAD::ID_TXWRCLK_MUX = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT27 = wxNewId();
const long pnlLimeLightPAD::ID_RXRDCLK_MUX = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT28 = wxNewId();
const long pnlLimeLightPAD::ID_RXWRCLK_MUX = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT29 = wxNewId();
const long pnlLimeLightPAD::ID_MCLK2SRC = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT30 = wxNewId();
const long pnlLimeLightPAD::ID_MCLK1SRC = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT31 = wxNewId();
const long pnlLimeLightPAD::ID_TXTSPCLKA_DIV = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT32 = wxNewId();
const long pnlLimeLightPAD::ID_RXTSPCLKA_DIV = wxNewId();
const long pnlLimeLightPAD::ID_TXDIVEN = wxNewId();
const long pnlLimeLightPAD::ID_RXDIVEN = wxNewId();
const long pnlLimeLightPAD::ID_FCLK1_INV = wxNewId();
const long pnlLimeLightPAD::ID_FCLK2_INV = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT37 = wxNewId();
const long pnlLimeLightPAD::ID_MCLK1DLY = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT39 = wxNewId();
const long pnlLimeLightPAD::ID_MCLK2DLY = wxNewId();
const long pnlLimeLightPAD::ID_DIQDIRCTR2 = wxNewId();
const long pnlLimeLightPAD::ID_DIQDIRCTR1 = wxNewId();
const long pnlLimeLightPAD::ID_DIQDIR2 = wxNewId();
const long pnlLimeLightPAD::ID_DIQDIR1 = wxNewId();
const long pnlLimeLightPAD::ID_ENABLEDIRCTR2 = wxNewId();
const long pnlLimeLightPAD::ID_ENABLEDIRCTR1 = wxNewId();
const long pnlLimeLightPAD::ID_ENABLEDIR2 = wxNewId();
const long pnlLimeLightPAD::ID_ENABLEDIR1 = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT17 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_TX_PST = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT18 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_TX_PRE = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT19 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_RX_PST = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT20 = wxNewId();
const long pnlLimeLightPAD::ID_LML1_RX_PRE = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT21 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_TX_PST = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT22 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_TX_PRE = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT23 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_RX_PST = wxNewId();
const long pnlLimeLightPAD::ID_STATICTEXT24 = wxNewId();
const long pnlLimeLightPAD::ID_LML2_RX_PRE = wxNewId();
const long pnlLimeLightPAD::ID_PANEL2 = wxNewId();
const long pnlLimeLightPAD::ID_NOTEBOOK1 = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlLimeLightPAD,wxPanel)
//(*EventTable(pnlLimeLightPAD)
//*)
END_EVENT_TABLE()

void pnlLimeLightPAD::AssignEnumsToIds()
{
    wndId2Enum[ID_DIQ1_DS] = DIQ1_DS;
    wndId2Enum[ID_DIQ1_PE] = DIQ1_PE;
    wndId2Enum[ID_DIQ2_DS] = DIQ2_DS;
    wndId2Enum[ID_DIQ2_PE] = DIQ2_PE;
    wndId2Enum[ID_RX_MUX] = RX_MUX;
    wndId2Enum[ID_FCLK1_PE] = FCLK1_PE;
    wndId2Enum[ID_FCLK2_PE] = FCLK2_PE;
    wndId2Enum[ID_IQ_SEL_EN_1_PE] = IQ_SEL_EN_1_PE;
    wndId2Enum[ID_IQ_SEL_EN_2_PE] = IQ_SEL_EN_2_PE;
    wndId2Enum[ID_LML1_AIP] = LML1_AIP;
    wndId2Enum[ID_LML1_AQP] = LML1_AQP;
    wndId2Enum[ID_LML1_BIP] = LML1_BIP;
    wndId2Enum[ID_LML1_BQP] = LML1_BQP;
    wndId2Enum[ID_LML1_RX_PRE] = LML1_RF2BB_PRE;
    wndId2Enum[ID_LML1_RX_PST] = LML1_RF2BB_PST;
    wndId2Enum[ID_LML1_S0S] = LML1_S0S;
    wndId2Enum[ID_LML1_S1S] = LML1_S1S;
    wndId2Enum[ID_LML1_S2S] = LML1_S2S;
    wndId2Enum[ID_LML1_S3S] = LML1_S3S;
    wndId2Enum[ID_LML1_TX_PRE] = LML1_BB2RF_PRE;
    wndId2Enum[ID_LML1_TX_PST] = LML1_BB2RF_PST;
    wndId2Enum[ID_LML2_AIP] = LML2_AIP;
    wndId2Enum[ID_LML2_AQP] = LML2_AQP;
    wndId2Enum[ID_LML2_BIP] = LML2_BIP;
    wndId2Enum[ID_LML2_BQP] = LML2_BQP;
    wndId2Enum[ID_LML2_RX_PRE] = LML2_RF2BB_PRE;
    wndId2Enum[ID_LML2_RX_PST] = LML2_RF2BB_PST;
    wndId2Enum[ID_LML2_S0S] = LML2_S0S;
    wndId2Enum[ID_LML2_S1S] = LML2_S1S;
    wndId2Enum[ID_LML2_S2S] = LML2_S2S;
    wndId2Enum[ID_LML2_S3S] = LML2_S3S;
    wndId2Enum[ID_LML2_TX_PRE] = LML2_BB2RF_PRE;
    wndId2Enum[ID_LML2_TX_PST] = LML2_BB2RF_PST;
    wndId2Enum[ID_LML_MODE1] = LML1_MODE;
    wndId2Enum[ID_LML_MODE2] = LML2_MODE;
    wndId2Enum[ID_LML_TXNRXIQ1] = LML1_TXNRXIQ;
    wndId2Enum[ID_LML_TXNRXIQ2] = LML2_TXNRXIQ;
    wndId2Enum[ID_LRST_RX_A] = LRST_RX_A;
    wndId2Enum[ID_LRST_RX_B] = LRST_RX_B;
    wndId2Enum[ID_LRST_TX_A] = LRST_TX_A;
    wndId2Enum[ID_LRST_TX_B] = LRST_TX_B;
    wndId2Enum[ID_MAC] = MAC;
    wndId2Enum[ID_MCLK1SRC] = MCLK1SRC;
    wndId2Enum[ID_RXTSPCLKA_DIV] = RXTSPCLKA_DIV;
    wndId2Enum[ID_MCLK1_PE] = MCLK1_PE;
    wndId2Enum[ID_MCLK2SRC] = MCLK2SRC;
    wndId2Enum[ID_TXTSPCLKA_DIV] = TXTSPCLKA_DIV;
    wndId2Enum[ID_MCLK2_PE] = MCLK2_PE;
    wndId2Enum[ID_MIMO_SISO] = MIMO_SISO;
    wndId2Enum[ID_MOD_EN] = MOD_EN;
    wndId2Enum[ID_MRST_RX_A] = MRST_RX_A;
    wndId2Enum[ID_MRST_RX_B] = MRST_RX_B;
    wndId2Enum[ID_MRST_TX_A] = MRST_TX_A;
    wndId2Enum[ID_MRST_TX_B] = MRST_TX_B;
    wndId2Enum[ID_RXDIVEN] = RXDIVEN;
    wndId2Enum[ID_RXEN_A] = RXEN_A;
    wndId2Enum[ID_RXEN_B] = RXEN_B;
    wndId2Enum[ID_RXRDCLK_MUX] = RXRDCLK_MUX;
    wndId2Enum[ID_RXWRCLK_MUX] = RXWRCLK_MUX;
    wndId2Enum[ID_RX_CLK_PE] = RX_CLK_PE;
    wndId2Enum[ID_SCLK_PE] = SCLK_PE;
    wndId2Enum[ID_SCL_DS] = SCL_DS;
    wndId2Enum[ID_SCL_PE] = SCL_PE;
    wndId2Enum[ID_SDA_DS] = SDA_DS;
    wndId2Enum[ID_SDA_PE] = SDA_PE;
    wndId2Enum[ID_SDIO_DS] = SDIO_DS;
    wndId2Enum[ID_SDIO_PE] = SDIO_PE;
    wndId2Enum[ID_SDO_PE] = SDO_PE;
    wndId2Enum[ID_SEN_PE] = SEN_PE;
    wndId2Enum[ID_SPIMODE] = SPIMODE;
    wndId2Enum[ID_SRST_RXFIFO] = SRST_RXFIFO;
    wndId2Enum[ID_SRST_TXFIFO] = SRST_TXFIFO;
    wndId2Enum[ID_TXDIVEN] = TXDIVEN;
    wndId2Enum[ID_TXEN_A] = TXEN_A;
    wndId2Enum[ID_TXEN_B] = TXEN_B;
    wndId2Enum[ID_TX_MUX] = TX_MUX;
    wndId2Enum[ID_TXNRX1_PE] = TXNRX1_PE;
    wndId2Enum[ID_TXNRX2_PE] = TXNRX2_PE;
    wndId2Enum[ID_TXRDCLK_MUX] = TXRDCLK_MUX;
    wndId2Enum[ID_TXWRCLK_MUX] = TXWRCLK_MUX;
    wndId2Enum[ID_TX_CLK_PE] = TX_CLK_PE;
    wndId2Enum[ID_LML_FIDM1] = LML1_FIDM;
    wndId2Enum[ID_LML_FIDM2] = LML2_FIDM;
    wndId2Enum[ID_FCLK1_INV] = FCLK1_INV;
    wndId2Enum[ID_FCLK2_INV] = FCLK2_INV;
    wndId2Enum[ID_MCLK1DLY] = MCLK1DLY;
    wndId2Enum[ID_MCLK2DLY] = MCLK2DLY;
    wndId2Enum[ID_DIQDIRCTR2] = DIQDIRCTR2;
    wndId2Enum[ID_DIQDIR2] = DIQDIR2;
    wndId2Enum[ID_DIQDIRCTR1] = DIQDIRCTR1;
    wndId2Enum[ID_DIQDIR1] = DIQDIR1;
    wndId2Enum[ID_ENABLEDIRCTR2] = ENABLEDIRCTR2;
    wndId2Enum[ID_ENABLEDIR2] = ENABLEDIR2;
    wndId2Enum[ID_ENABLEDIRCTR1] = ENABLEDIRCTR1;
    wndId2Enum[ID_ENABLEDIR1] = ENABLEDIR1;
}

pnlLimeLightPAD::pnlLimeLightPAD(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlLimeLightPAD::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlLimeLightPAD)
wxFlexGridSizer* SamplesourcewhenPort2isTx6Sizer;
wxStaticBoxSizer* SamplepositionswhenPort2isRxSizer;
wxFlexGridSizer* FlexGridSizer4;
wxFlexGridSizer* Driverstrength2Sizer;
wxFlexGridSizer* SamplesourcewhenPort1isTx4Sizer;
wxFlexGridSizer* LML29Sizer;
wxStaticBoxSizer* PowerControlSizer;
wxFlexGridSizer* LimeLightmodes12Sizer;
wxStaticBoxSizer* PullupcontrolSizer;
wxFlexGridSizer* UNGROUPED13Sizer;
wxStaticBoxSizer* LimeLightmodesSizer;
wxFlexGridSizer* FlexGridSizer3;
wxStaticBoxSizer* SamplesourcewhenPort1isTxSizer;
wxStaticBoxSizer* SamplepositionswhenPort1isRxSizer;
wxFlexGridSizer* FlexGridSizer5;
wxStaticBoxSizer* ClockcontrolsSizer;
wxFlexGridSizer* FlexGridSizer9;
wxStaticBoxSizer* DriverstrengthSizer;
wxFlexGridSizer* SamplepositionswhenPort1isRx5Sizer;
wxFlexGridSizer* FlexGridSizer2;
wxFlexGridSizer* FlexGridSizer7;
wxFlexGridSizer* Resetsignals10Sizer;
wxFlexGridSizer* PowerControl1Sizer;
wxStaticBoxSizer* UNGROUPEDSizer;
wxFlexGridSizer* FlexGridSizer8;
wxFlexGridSizer* LML18Sizer;
wxStaticBoxSizer* LML2Sizer;
wxStaticBoxSizer* ResetsignalsSizer;
wxStaticBoxSizer* LML1Sizer;
wxFlexGridSizer* FlexGridSizer6;
wxStaticBoxSizer* StaticBoxSizer1;
wxFlexGridSizer* SamplepositionswhenPort2isRx7Sizer;
wxFlexGridSizer* FlexGridSizer1;
wxStaticBoxSizer* SamplesourcewhenPort2isTxSizer;
wxFlexGridSizer* Clockcontrols11Sizer;
wxFlexGridSizer* Pullupcontrol3Sizer;

Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
PullupcontrolSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Pull up control"));
Pullupcontrol3Sizer = new wxFlexGridSizer(0, 2, 0, 0);
chkTX_CLK_PE = new wxCheckBox(Panel1, ID_TX_CLK_PE, _("Engage pull up of TX_CLK pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TX_CLK_PE"));
chkTX_CLK_PE->SetValue(false);
chkTX_CLK_PE->SetToolTip(_("Pull up control of TX_CLK pad"));
Pullupcontrol3Sizer->Add(chkTX_CLK_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkRX_CLK_PE = new wxCheckBox(Panel1, ID_RX_CLK_PE, _("Engage pull up of RX_CLK pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RX_CLK_PE"));
chkRX_CLK_PE->SetValue(false);
chkRX_CLK_PE->SetToolTip(_("Pull up control of RX_CLK pad"));
Pullupcontrol3Sizer->Add(chkRX_CLK_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSDA_PE = new wxCheckBox(Panel1, ID_SDA_PE, _("Engage pull up of SDA pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SDA_PE"));
chkSDA_PE->SetValue(false);
chkSDA_PE->SetToolTip(_("Pull up control of SDA pad"));
Pullupcontrol3Sizer->Add(chkSDA_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSCL_PE = new wxCheckBox(Panel1, ID_SCL_PE, _("Engage pull up of SCL pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SCL_PE"));
chkSCL_PE->SetValue(false);
chkSCL_PE->SetToolTip(_("Pull up control of SCL pad"));
Pullupcontrol3Sizer->Add(chkSCL_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSDIO_PE = new wxCheckBox(Panel1, ID_SDIO_PE, _("Engage pull up of SDIO pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SDIO_PE"));
chkSDIO_PE->SetValue(false);
chkSDIO_PE->SetToolTip(_("Pull up control of SDIO pad"));
Pullupcontrol3Sizer->Add(chkSDIO_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSDO_PE = new wxCheckBox(Panel1, ID_SDO_PE, _("Engage pull up of SDO pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SDO_PE"));
chkSDO_PE->SetValue(false);
chkSDO_PE->SetToolTip(_("Pull up control of SDO pad"));
Pullupcontrol3Sizer->Add(chkSDO_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSCLK_PE = new wxCheckBox(Panel1, ID_SCLK_PE, _("Engage pull up of SCLK pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SCLK_PE"));
chkSCLK_PE->SetValue(false);
chkSCLK_PE->SetToolTip(_("Pull up control of SCLK pad"));
Pullupcontrol3Sizer->Add(chkSCLK_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSEN_PE = new wxCheckBox(Panel1, ID_SEN_PE, _("Engage pull up of SEN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SEN_PE"));
chkSEN_PE->SetValue(false);
chkSEN_PE->SetToolTip(_("Pull up control of SEN pad"));
Pullupcontrol3Sizer->Add(chkSEN_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkDIQ2_PE = new wxCheckBox(Panel1, ID_DIQ2_PE, _("Engage pull up of DIQ2 pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DIQ2_PE"));
chkDIQ2_PE->SetValue(false);
chkDIQ2_PE->SetToolTip(_("Pull up control of DIQ2 pad"));
Pullupcontrol3Sizer->Add(chkDIQ2_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkIQ_SEL_EN_2_PE = new wxCheckBox(Panel1, ID_IQ_SEL_EN_2_PE, _("Engage pull up of IQ_SEL_EN_2 pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_IQ_SEL_EN_2_PE"));
chkIQ_SEL_EN_2_PE->SetValue(false);
chkIQ_SEL_EN_2_PE->SetToolTip(_("Pull up control of IQ_SEL_EN_2 pad"));
Pullupcontrol3Sizer->Add(chkIQ_SEL_EN_2_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkTXNRX2_PE = new wxCheckBox(Panel1, ID_TXNRX2_PE, _("Engage pull up of TXNRX2 pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXNRX2_PE"));
chkTXNRX2_PE->SetValue(false);
chkTXNRX2_PE->SetToolTip(_("Pull up control of TXNRX2 pad"));
Pullupcontrol3Sizer->Add(chkTXNRX2_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkFCLK2_PE = new wxCheckBox(Panel1, ID_FCLK2_PE, _("Engage pull up of FCLK2 pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FCLK2_PE"));
chkFCLK2_PE->SetValue(false);
chkFCLK2_PE->SetToolTip(_("Pull up control of FCLK2 pad"));
Pullupcontrol3Sizer->Add(chkFCLK2_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkMCLK2_PE = new wxCheckBox(Panel1, ID_MCLK2_PE, _("Engage pull up of MCLK2 pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MCLK2_PE"));
chkMCLK2_PE->SetValue(false);
chkMCLK2_PE->SetToolTip(_("Pull up control of MCLK2 pad"));
Pullupcontrol3Sizer->Add(chkMCLK2_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkDIQ1_PE = new wxCheckBox(Panel1, ID_DIQ1_PE, _("Engage pull up of DIQ1 pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DIQ1_PE"));
chkDIQ1_PE->SetValue(false);
chkDIQ1_PE->SetToolTip(_("Pull up control of DIQ1 pad"));
Pullupcontrol3Sizer->Add(chkDIQ1_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkIQ_SEL_EN_1_PE = new wxCheckBox(Panel1, ID_IQ_SEL_EN_1_PE, _("Engage pull up of IQ_SEL_EN_1 pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_IQ_SEL_EN_1_PE"));
chkIQ_SEL_EN_1_PE->SetValue(false);
chkIQ_SEL_EN_1_PE->SetToolTip(_("Pull up control of IQ_SEL_EN_1 pad"));
Pullupcontrol3Sizer->Add(chkIQ_SEL_EN_1_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkTXNRX1_PE = new wxCheckBox(Panel1, ID_TXNRX1_PE, _("Engage pull up of TXNRX1 pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXNRX1_PE"));
chkTXNRX1_PE->SetValue(false);
chkTXNRX1_PE->SetToolTip(_("Pull up control of TXNRX1 pad"));
Pullupcontrol3Sizer->Add(chkTXNRX1_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkFCLK1_PE = new wxCheckBox(Panel1, ID_FCLK1_PE, _("Engage pull up of FCLK1 pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FCLK1_PE"));
chkFCLK1_PE->SetValue(false);
chkFCLK1_PE->SetToolTip(_("Pull up control of FCLK1 pad"));
Pullupcontrol3Sizer->Add(chkFCLK1_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkMCLK1_PE = new wxCheckBox(Panel1, ID_MCLK1_PE, _("Engage pull up of MCLK1 pad"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MCLK1_PE"));
chkMCLK1_PE->SetValue(false);
chkMCLK1_PE->SetToolTip(_("Pull up control of MCLK1 pad"));
Pullupcontrol3Sizer->Add(chkMCLK1_PE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
PullupcontrolSizer->Add(Pullupcontrol3Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(PullupcontrolSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
LimeLightmodesSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("LimeLight modes"));
LimeLightmodes12Sizer = new wxFlexGridSizer(0, 2, 0, 0);
chkMOD_EN = new wxCheckBox(Panel1, ID_MOD_EN, _("Enable LimeLight interface"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MOD_EN"));
chkMOD_EN->SetValue(false);
chkMOD_EN->SetToolTip(_("LimeLight interface enable"));
LimeLightmodes12Sizer->Add(chkMOD_EN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticLine1 = new wxStaticLine(Panel1, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
StaticLine1->Hide();
LimeLightmodes12Sizer->Add(StaticLine1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
wxString __wxRadioBoxChoices_1[2] =
{
	_("0"),
	_("1")
};
rgrLML_FIDM1 = new wxRadioBox(Panel1, ID_LML_FIDM1, _("Frame start for Port 1"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_1, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_LML_FIDM1"));
rgrLML_FIDM1->SetSelection(0);
rgrLML_FIDM1->SetToolTip(_("Frame start ID selection for Port 1 when LML_MODE1 = 0"));
LimeLightmodes12Sizer->Add(rgrLML_FIDM1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_2[2] =
{
	_("0"),
	_("1")
};
rgrLML_FIDM2 = new wxRadioBox(Panel1, ID_LML_FIDM2, _("Frame start for Port 2"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_2, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_LML_FIDM2"));
rgrLML_FIDM2->SetSelection(0);
rgrLML_FIDM2->SetToolTip(_("Frame start ID selection for Port 2 when LML_MODE2 = 0"));
LimeLightmodes12Sizer->Add(rgrLML_FIDM2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_3[2] =
{
	_("TRXIQ"),
	_("JESD207")
};
rgrLML_MODE1 = new wxRadioBox(Panel1, ID_LML_MODE1, _("LimeLight port 1 mode"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_3, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_LML_MODE1"));
rgrLML_MODE1->SetSelection(0);
rgrLML_MODE1->SetToolTip(_("Mode of LimeLight Port 1"));
LimeLightmodes12Sizer->Add(rgrLML_MODE1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_4[2] =
{
	_("TRXIQ"),
	_("JESD207")
};
rgrLML_MODE2 = new wxRadioBox(Panel1, ID_LML_MODE2, _("LimeLight port 2 mode"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_4, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_LML_MODE2"));
rgrLML_MODE2->SetSelection(0);
rgrLML_MODE2->SetToolTip(_("Mode of LimeLight Port 2"));
LimeLightmodes12Sizer->Add(rgrLML_MODE2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_5[2] =
{
	_("RXIQ"),
	_("TXIQ")
};
rgrLML_TXNRXIQ1 = new wxRadioBox(Panel1, ID_LML_TXNRXIQ1, _("Port 1 mode selection"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_5, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_LML_TXNRXIQ1"));
rgrLML_TXNRXIQ1->SetSelection(0);
rgrLML_TXNRXIQ1->SetToolTip(_("TXIQ/RXIQ mode selection for Port 1 when LML_MODE1 = 0"));
LimeLightmodes12Sizer->Add(rgrLML_TXNRXIQ1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_6[2] =
{
	_("RXIQ"),
	_("TXIQ")
};
rgrLML_TXNRXIQ2 = new wxRadioBox(Panel1, ID_LML_TXNRXIQ2, _("Port 2 mode selection"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_6, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_LML_TXNRXIQ2"));
rgrLML_TXNRXIQ2->SetSelection(0);
rgrLML_TXNRXIQ2->SetToolTip(_("TXIQ/RXIQ mode selection for Port 2 when LML_MODE2 = 0"));
LimeLightmodes12Sizer->Add(rgrLML_TXNRXIQ2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
LimeLightmodesSizer->Add(LimeLightmodes12Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(LimeLightmodesSizer, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
ResetsignalsSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Reset signals"));
Resetsignals10Sizer = new wxFlexGridSizer(0, 2, 0, 0);
chkLRST_TX_B = new wxCheckBox(Panel1, ID_LRST_TX_B, _("logic registers Tx MIMO ch. B"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_LRST_TX_B"));
chkLRST_TX_B->SetValue(false);
chkLRST_TX_B->SetToolTip(_("Resets all the logic registers to the default state for Tx MIMO channel B"));
Resetsignals10Sizer->Add(chkLRST_TX_B, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkMRST_TX_B = new wxCheckBox(Panel1, ID_MRST_TX_B, _("configuration memory Tx MIMO ch. B"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MRST_TX_B"));
chkMRST_TX_B->SetValue(false);
chkMRST_TX_B->SetToolTip(_("Resets all the configuration memory to the default state for Tx MIMO channel B"));
Resetsignals10Sizer->Add(chkMRST_TX_B, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkLRST_TX_A = new wxCheckBox(Panel1, ID_LRST_TX_A, _("logic registers Tx MIMO ch. A"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_LRST_TX_A"));
chkLRST_TX_A->SetValue(false);
chkLRST_TX_A->SetToolTip(_("Resets all the logic registers to the default state for Tx MIMO channel A"));
Resetsignals10Sizer->Add(chkLRST_TX_A, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkMRST_TX_A = new wxCheckBox(Panel1, ID_MRST_TX_A, _("configuration memory Tx MIMO ch. A"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MRST_TX_A"));
chkMRST_TX_A->SetValue(false);
chkMRST_TX_A->SetToolTip(_("Resets all the configuration memory to the default state for Tx MIMO channel A"));
Resetsignals10Sizer->Add(chkMRST_TX_A, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkLRST_RX_B = new wxCheckBox(Panel1, ID_LRST_RX_B, _("logic registers Rx MIMO ch. B"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_LRST_RX_B"));
chkLRST_RX_B->SetValue(false);
chkLRST_RX_B->SetToolTip(_("Resets all the logic registers to the default state for Rx MIMO channel B"));
Resetsignals10Sizer->Add(chkLRST_RX_B, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkMRST_RX_B = new wxCheckBox(Panel1, ID_MRST_RX_B, _("configuration memory Rx MIMO ch. B"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MRST_RX_B"));
chkMRST_RX_B->SetValue(false);
chkMRST_RX_B->SetToolTip(_("Resets all the configuration memory to the default state for Rx MIMO channel B"));
Resetsignals10Sizer->Add(chkMRST_RX_B, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkLRST_RX_A = new wxCheckBox(Panel1, ID_LRST_RX_A, _("logic registers Rx MIMO ch. A"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_LRST_RX_A"));
chkLRST_RX_A->SetValue(false);
chkLRST_RX_A->SetToolTip(_("Resets all the logic registers to the default state for Rx MIMO channel A"));
Resetsignals10Sizer->Add(chkLRST_RX_A, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkMRST_RX_A = new wxCheckBox(Panel1, ID_MRST_RX_A, _("configuration memory Rx MIMO ch. A"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MRST_RX_A"));
chkMRST_RX_A->SetValue(false);
chkMRST_RX_A->SetToolTip(_("Resets all the configuration memory to the default state for Rx MIMO channel A"));
Resetsignals10Sizer->Add(chkMRST_RX_A, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSRST_RXFIFO = new wxCheckBox(Panel1, ID_SRST_RXFIFO, _("Rx FIFO soft reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SRST_RXFIFO"));
chkSRST_RXFIFO->SetValue(false);
chkSRST_RXFIFO->SetToolTip(_("RX FIFO soft reset (LimeLight Interface)"));
Resetsignals10Sizer->Add(chkSRST_RXFIFO, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSRST_TXFIFO = new wxCheckBox(Panel1, ID_SRST_TXFIFO, _("Tx FIFO soft reset"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SRST_TXFIFO"));
chkSRST_TXFIFO->SetValue(false);
chkSRST_TXFIFO->SetToolTip(_("TX FIFO soft reset (LimeLight Interface)"));
Resetsignals10Sizer->Add(chkSRST_TXFIFO, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
ResetsignalsSizer->Add(Resetsignals10Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer7->Add(ResetsignalsSizer, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
DriverstrengthSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Driver strength"));
Driverstrength2Sizer = new wxFlexGridSizer(0, 5, 0, 0);
wxString __wxRadioBoxChoices_7[2] =
{
	_("4 mA"),
	_("8 mA")
};
rgrSDA_DS = new wxRadioBox(Panel1, ID_SDA_DS, _("SDA pad"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_7, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_SDA_DS"));
rgrSDA_DS->SetSelection(0);
rgrSDA_DS->SetToolTip(_("Driver strength of SDA pad"));
Driverstrength2Sizer->Add(rgrSDA_DS, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_8[2] =
{
	_("4 mA"),
	_("8 mA")
};
rgrSCL_DS = new wxRadioBox(Panel1, ID_SCL_DS, _("SCL pad"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_8, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_SCL_DS"));
rgrSCL_DS->SetSelection(0);
rgrSCL_DS->SetToolTip(_("Driver strength of SCL pad"));
Driverstrength2Sizer->Add(rgrSCL_DS, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_9[2] =
{
	_("4 mA"),
	_("8 mA")
};
rgrSDIO_DS = new wxRadioBox(Panel1, ID_SDIO_DS, _("SDIO pad"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_9, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_SDIO_DS"));
rgrSDIO_DS->SetSelection(0);
rgrSDIO_DS->SetToolTip(_("Driver strength of SDIO pad"));
Driverstrength2Sizer->Add(rgrSDIO_DS, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_10[2] =
{
	_("4 mA"),
	_("8 mA")
};
rgrDIQ2_DS = new wxRadioBox(Panel1, ID_DIQ2_DS, _("DIQ2 pad"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_10, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DIQ2_DS"));
rgrDIQ2_DS->SetSelection(0);
rgrDIQ2_DS->SetToolTip(_("Driver strength of DIQ2 pad"));
Driverstrength2Sizer->Add(rgrDIQ2_DS, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
wxString __wxRadioBoxChoices_11[2] =
{
	_("4 mA"),
	_("8 mA")
};
rgrDIQ1_DS = new wxRadioBox(Panel1, ID_DIQ1_DS, _("DIQ1 pad"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_11, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DIQ1_DS"));
rgrDIQ1_DS->SetSelection(0);
rgrDIQ1_DS->SetToolTip(_("Pull up control of MCLK2 pad"));
Driverstrength2Sizer->Add(rgrDIQ1_DS, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
DriverstrengthSizer->Add(Driverstrength2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer7->Add(DriverstrengthSizer, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer2->Add(FlexGridSizer7, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
UNGROUPEDSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("UNGROUPED"));
UNGROUPED13Sizer = new wxFlexGridSizer(0, 2, 0, 0);
StaticText33 = new wxStaticText(Panel1, ID_STATICTEXT33, _("RxFIFO data source"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT33"));
UNGROUPED13Sizer->Add(StaticText33, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRX_MUX = new ComboBoxMap(Panel1, ID_RX_MUX, wxEmptyString, wxDefaultPosition, wxSize(205,-1), 0, 0, 0, wxDefaultValidator, _T("ID_RX_MUX"));
cmbRX_MUX->SetToolTip(_("RxFIFO data source selection"));
UNGROUPED13Sizer->Add(cmbRX_MUX, 0, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText34 = new wxStaticText(Panel1, ID_STATICTEXT34, _("Data transmit port to TSP"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT34"));
UNGROUPED13Sizer->Add(StaticText34, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbTX_MUX = new ComboBoxMap(Panel1, ID_TX_MUX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_TX_MUX"));
cmbTX_MUX->SetToolTip(_("Port selection for data transmit to TSP"));
UNGROUPED13Sizer->Add(cmbTX_MUX, 0, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText35 = new wxStaticText(Panel1, ID_STATICTEXT35, _("Disable MIMO channel B"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT35"));
UNGROUPED13Sizer->Add(StaticText35, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbMIMO_SISO = new ComboBoxMap(Panel1, ID_MIMO_SISO, wxEmptyString, wxDefaultPosition, wxSize(175,-1), 0, 0, 0, wxDefaultValidator, _T("ID_MIMO_SISO"));
cmbMIMO_SISO->SetToolTip(_("MIMO channel B enable control"));
UNGROUPED13Sizer->Add(cmbMIMO_SISO, 0, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
wxString __wxRadioBoxChoices_12[2] =
{
	_("3 wire mode"),
	_("4 wire mode")
};
rgrSPIMODE = new wxRadioBox(Panel1, ID_SPIMODE, _("SPI mode"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_12, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_SPIMODE"));
rgrSPIMODE->SetSelection(0);
rgrSPIMODE->SetToolTip(_("SPI communication mode"));
UNGROUPED13Sizer->Add(rgrSPIMODE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
wxString __wxRadioBoxChoices_13[4] =
{
	_("None"),
	_("A"),
	_("B"),
	_("A and B")
};
rgrMAC = new wxRadioBox(Panel1, ID_MAC, _("MIMO access control"), wxDefaultPosition, wxDefaultSize, 4, __wxRadioBoxChoices_13, 2, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_MAC"));
rgrMAC->SetSelection(0);
rgrMAC->SetToolTip(_("Selects MIMO channel for communication"));
UNGROUPED13Sizer->Add(rgrMAC, 0, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
UNGROUPEDSizer->Add(UNGROUPED13Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(UNGROUPEDSizer, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
PowerControlSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Power Control"));
PowerControl1Sizer = new wxFlexGridSizer(0, 2, 0, 0);
chkRXEN_B = new wxCheckBox(Panel1, ID_RXEN_B, _("Enable Rx MIMO ch. B"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RXEN_B"));
chkRXEN_B->SetValue(false);
chkRXEN_B->SetToolTip(_("Power control for Rx MIMO channel B"));
PowerControl1Sizer->Add(chkRXEN_B, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkRXEN_A = new wxCheckBox(Panel1, ID_RXEN_A, _("Enable Rx MIMO ch. A"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RXEN_A"));
chkRXEN_A->SetValue(false);
chkRXEN_A->SetToolTip(_("Power control for Rx MIMO channel A"));
PowerControl1Sizer->Add(chkRXEN_A, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkTXEN_B = new wxCheckBox(Panel1, ID_TXEN_B, _("Enable Tx MIMO ch. B"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXEN_B"));
chkTXEN_B->SetValue(false);
chkTXEN_B->SetToolTip(_("Power control for Tx MIMO channel B"));
PowerControl1Sizer->Add(chkTXEN_B, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkTXEN_A = new wxCheckBox(Panel1, ID_TXEN_A, _("Enable Tx MIMO ch. A"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXEN_A"));
chkTXEN_A->SetValue(false);
chkTXEN_A->SetToolTip(_("Power control for Tx MIMO channel A"));
PowerControl1Sizer->Add(chkTXEN_A, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
PowerControlSizer->Add(PowerControl1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer2->Add(PowerControlSizer, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer8 = new wxFlexGridSizer(0, 7, 0, 0);
StaticText36 = new wxStaticText(Panel1, ID_STATICTEXT36, _("Ver:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT36"));
FlexGridSizer8->Add(StaticText36, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
lblVER = new wxStaticText(Panel1, ID_VER, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_VER"));
FlexGridSizer8->Add(lblVER, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText38 = new wxStaticText(Panel1, ID_STATICTEXT38, _("Rev:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT38"));
FlexGridSizer8->Add(StaticText38, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
lblREV = new wxStaticText(Panel1, ID_REV, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_REV"));
FlexGridSizer8->Add(lblREV, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticText40 = new wxStaticText(Panel1, ID_STATICTEXT40, _("Mask:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT40"));
FlexGridSizer8->Add(StaticText40, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
lblMASK = new wxStaticText(Panel1, ID_MASK, _("\?\?\?"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MASK"));
FlexGridSizer8->Add(lblMASK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
btnReadVerRevMask = new wxButton(Panel1, ID_BUTTON1, _("Read"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
FlexGridSizer8->Add(btnReadVerRevMask, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer2->Add(FlexGridSizer8, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
Panel1->SetSizer(FlexGridSizer2);
FlexGridSizer2->Fit(Panel1);
FlexGridSizer2->SetSizeHints(Panel1);
Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
FlexGridSizer4 = new wxFlexGridSizer(0, 3, 5, 5);
FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
SamplesourcewhenPort1isTxSizer = new wxStaticBoxSizer(wxVERTICAL, Panel2, _("Sample source when Port 1 is RF2BB"));
SamplesourcewhenPort1isTx4Sizer = new wxFlexGridSizer(0, 2, 0, 5);
SamplesourcewhenPort1isTx4Sizer->AddGrowableCol(1);
StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT1, _("Position 3"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
SamplesourcewhenPort1isTx4Sizer->Add(StaticText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_S3S = new ComboBoxMap(Panel2, ID_LML1_S3S, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML1_S3S"));
cmbLML1_S3S->SetToolTip(_("Sample source in position 3, when Port 1 is RF2BB"));
SamplesourcewhenPort1isTx4Sizer->Add(cmbLML1_S3S, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT2, _("Position 2"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
SamplesourcewhenPort1isTx4Sizer->Add(StaticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_S2S = new ComboBoxMap(Panel2, ID_LML1_S2S, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML1_S2S"));
cmbLML1_S2S->SetToolTip(_("Sample source in position 2, when Port 1 is RF2BB"));
SamplesourcewhenPort1isTx4Sizer->Add(cmbLML1_S2S, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText3 = new wxStaticText(Panel2, ID_STATICTEXT3, _("Position 1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
SamplesourcewhenPort1isTx4Sizer->Add(StaticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_S1S = new ComboBoxMap(Panel2, ID_LML1_S1S, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML1_S1S"));
cmbLML1_S1S->SetToolTip(_("Sample source in position 1, when Port 1 is RF2BB"));
SamplesourcewhenPort1isTx4Sizer->Add(cmbLML1_S1S, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText4 = new wxStaticText(Panel2, ID_STATICTEXT4, _("Position 0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
SamplesourcewhenPort1isTx4Sizer->Add(StaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_S0S = new ComboBoxMap(Panel2, ID_LML1_S0S, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML1_S0S"));
cmbLML1_S0S->SetToolTip(_("Sample source in position 0, when Port 1 is RF2BB"));
SamplesourcewhenPort1isTx4Sizer->Add(cmbLML1_S0S, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
SamplesourcewhenPort1isTxSizer->Add(SamplesourcewhenPort1isTx4Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer5->Add(SamplesourcewhenPort1isTxSizer, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
SamplepositionswhenPort1isRxSizer = new wxStaticBoxSizer(wxVERTICAL, Panel2, _("Sample positions when Port 1 is BB2RF"));
SamplepositionswhenPort1isRx5Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText5 = new wxStaticText(Panel2, ID_STATICTEXT5, _("BQ sample position"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
SamplepositionswhenPort1isRx5Sizer->Add(StaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_BQP = new ComboBoxMap(Panel2, ID_LML1_BQP, wxEmptyString, wxDefaultPosition, wxSize(100,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML1_BQP"));
cmbLML1_BQP->SetToolTip(_("BQ sample position in frame, when Port 1 is BB2RF"));
SamplepositionswhenPort1isRx5Sizer->Add(cmbLML1_BQP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText6 = new wxStaticText(Panel2, ID_STATICTEXT6, _("BI sample position"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
SamplepositionswhenPort1isRx5Sizer->Add(StaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_BIP = new ComboBoxMap(Panel2, ID_LML1_BIP, wxEmptyString, wxDefaultPosition, wxSize(85,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML1_BIP"));
cmbLML1_BIP->SetToolTip(_("BI sample position in frame, when Port 1 is BB2RF"));
SamplepositionswhenPort1isRx5Sizer->Add(cmbLML1_BIP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText7 = new wxStaticText(Panel2, ID_STATICTEXT7, _("AQ sample position"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
SamplepositionswhenPort1isRx5Sizer->Add(StaticText7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_AQP = new ComboBoxMap(Panel2, ID_LML1_AQP, wxEmptyString, wxDefaultPosition, wxSize(85,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML1_AQP"));
cmbLML1_AQP->SetToolTip(_("AQ sample position in frame, when Port 1 is BB2RF"));
SamplepositionswhenPort1isRx5Sizer->Add(cmbLML1_AQP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText8 = new wxStaticText(Panel2, ID_STATICTEXT8, _("AI sample position"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
SamplepositionswhenPort1isRx5Sizer->Add(StaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_AIP = new ComboBoxMap(Panel2, ID_LML1_AIP, wxEmptyString, wxDefaultPosition, wxSize(85,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML1_AIP"));
cmbLML1_AIP->SetToolTip(_("AI sample position in frame, when Port 1 is BB2RF"));
SamplepositionswhenPort1isRx5Sizer->Add(cmbLML1_AIP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
SamplepositionswhenPort1isRxSizer->Add(SamplepositionswhenPort1isRx5Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer5->Add(SamplepositionswhenPort1isRxSizer, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
SamplesourcewhenPort2isTxSizer = new wxStaticBoxSizer(wxVERTICAL, Panel2, _("Sample source when Port 2 is RF2BB"));
SamplesourcewhenPort2isTx6Sizer = new wxFlexGridSizer(0, 2, 0, 5);
SamplesourcewhenPort2isTx6Sizer->AddGrowableCol(1);
StaticText9 = new wxStaticText(Panel2, ID_STATICTEXT9, _("Position 3"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
SamplesourcewhenPort2isTx6Sizer->Add(StaticText9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_S3S = new ComboBoxMap(Panel2, ID_LML2_S3S, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML2_S3S"));
cmbLML2_S3S->SetToolTip(_("Sample source in position 3, when Port 2 is RF2BB"));
SamplesourcewhenPort2isTx6Sizer->Add(cmbLML2_S3S, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText10 = new wxStaticText(Panel2, ID_STATICTEXT10, _("Position 2"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
SamplesourcewhenPort2isTx6Sizer->Add(StaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_S2S = new ComboBoxMap(Panel2, ID_LML2_S2S, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML2_S2S"));
cmbLML2_S2S->SetToolTip(_("Sample source in position 2, when Port 2 is RF2BB"));
SamplesourcewhenPort2isTx6Sizer->Add(cmbLML2_S2S, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText11 = new wxStaticText(Panel2, ID_STATICTEXT11, _("Position 1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
SamplesourcewhenPort2isTx6Sizer->Add(StaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_S1S = new ComboBoxMap(Panel2, ID_LML2_S1S, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML2_S1S"));
cmbLML2_S1S->SetToolTip(_("Sample source in position 1, when Port 2 is RF2BB"));
SamplesourcewhenPort2isTx6Sizer->Add(cmbLML2_S1S, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText12 = new wxStaticText(Panel2, ID_STATICTEXT12, _("Position 0"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
SamplesourcewhenPort2isTx6Sizer->Add(StaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_S0S = new ComboBoxMap(Panel2, ID_LML2_S0S, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML2_S0S"));
cmbLML2_S0S->SetToolTip(_("Sample source in position 0, when Port 2 is RF2BB"));
SamplesourcewhenPort2isTx6Sizer->Add(cmbLML2_S0S, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
SamplesourcewhenPort2isTxSizer->Add(SamplesourcewhenPort2isTx6Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer5->Add(SamplesourcewhenPort2isTxSizer, 1, wxLEFT|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
SamplepositionswhenPort2isRxSizer = new wxStaticBoxSizer(wxVERTICAL, Panel2, _("Sample positions when Port 2 is BB2RF"));
SamplepositionswhenPort2isRx7Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText13 = new wxStaticText(Panel2, ID_STATICTEXT13, _("BQ sample position"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
SamplepositionswhenPort2isRx7Sizer->Add(StaticText13, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_BQP = new ComboBoxMap(Panel2, ID_LML2_BQP, wxEmptyString, wxDefaultPosition, wxSize(100,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML2_BQP"));
cmbLML2_BQP->SetToolTip(_("BQ sample position in frame, when Port 2 is BB2RF"));
SamplepositionswhenPort2isRx7Sizer->Add(cmbLML2_BQP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText14 = new wxStaticText(Panel2, ID_STATICTEXT14, _("BI sample position"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
SamplepositionswhenPort2isRx7Sizer->Add(StaticText14, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_BIP = new ComboBoxMap(Panel2, ID_LML2_BIP, wxEmptyString, wxDefaultPosition, wxSize(85,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML2_BIP"));
cmbLML2_BIP->SetToolTip(_("BI sample position in frame, when Port 2 is BB2RF"));
SamplepositionswhenPort2isRx7Sizer->Add(cmbLML2_BIP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText15 = new wxStaticText(Panel2, ID_STATICTEXT15, _("AQ sample position"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
SamplepositionswhenPort2isRx7Sizer->Add(StaticText15, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_AQP = new ComboBoxMap(Panel2, ID_LML2_AQP, wxEmptyString, wxDefaultPosition, wxSize(85,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML2_AQP"));
cmbLML2_AQP->SetToolTip(_("AQ sample position in frame, when Port 2 is BB2RF"));
SamplepositionswhenPort2isRx7Sizer->Add(cmbLML2_AQP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText16 = new wxStaticText(Panel2, ID_STATICTEXT16, _("AI sample position"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
SamplepositionswhenPort2isRx7Sizer->Add(StaticText16, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_AIP = new ComboBoxMap(Panel2, ID_LML2_AIP, wxEmptyString, wxDefaultPosition, wxSize(85,-1), 0, 0, 0, wxDefaultValidator, _T("ID_LML2_AIP"));
cmbLML2_AIP->SetToolTip(_("AI sample position in frame, when Port 2 is BB2RF"));
SamplepositionswhenPort2isRx7Sizer->Add(cmbLML2_AIP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
SamplepositionswhenPort2isRxSizer->Add(SamplepositionswhenPort2isRx7Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer5->Add(SamplepositionswhenPort2isRxSizer, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer4->Add(FlexGridSizer5, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
ClockcontrolsSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("Clock controls"));
Clockcontrols11Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText25 = new wxStaticText(Panel2, ID_STATICTEXT25, _("TX FIFO read clock source"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
Clockcontrols11Sizer->Add(StaticText25, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbTXRDCLK_MUX = new ComboBoxMap(Panel2, ID_TXRDCLK_MUX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_TXRDCLK_MUX"));
cmbTXRDCLK_MUX->SetToolTip(_("TX FIFO read clock selection"));
Clockcontrols11Sizer->Add(cmbTXRDCLK_MUX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText26 = new wxStaticText(Panel2, ID_STATICTEXT26, _("Tx FIFO write clock source"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
Clockcontrols11Sizer->Add(StaticText26, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbTXWRCLK_MUX = new ComboBoxMap(Panel2, ID_TXWRCLK_MUX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_TXWRCLK_MUX"));
cmbTXWRCLK_MUX->SetToolTip(_("TX FIFO write clock selection"));
Clockcontrols11Sizer->Add(cmbTXWRCLK_MUX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText27 = new wxStaticText(Panel2, ID_STATICTEXT27, _("Rx FIFO read clock source"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
Clockcontrols11Sizer->Add(StaticText27, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRXRDCLK_MUX = new ComboBoxMap(Panel2, ID_RXRDCLK_MUX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RXRDCLK_MUX"));
cmbRXRDCLK_MUX->SetToolTip(_("RX FIFO read clock selection"));
Clockcontrols11Sizer->Add(cmbRXRDCLK_MUX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText28 = new wxStaticText(Panel2, ID_STATICTEXT28, _("Rx FIFO write clock source"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
Clockcontrols11Sizer->Add(StaticText28, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRXWRCLK_MUX = new ComboBoxMap(Panel2, ID_RXWRCLK_MUX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RXWRCLK_MUX"));
cmbRXWRCLK_MUX->SetToolTip(_("RX FIFO write clock selection"));
Clockcontrols11Sizer->Add(cmbRXWRCLK_MUX, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText29 = new wxStaticText(Panel2, ID_STATICTEXT29, _("MCLK2 clock source"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT29"));
Clockcontrols11Sizer->Add(StaticText29, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbMCLK2SRC = new ComboBoxMap(Panel2, ID_MCLK2SRC, wxEmptyString, wxDefaultPosition, wxSize(154,-1), 0, 0, 0, wxDefaultValidator, _T("ID_MCLK2SRC"));
cmbMCLK2SRC->SetToolTip(_("MCLK2 clock source"));
Clockcontrols11Sizer->Add(cmbMCLK2SRC, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText30 = new wxStaticText(Panel2, ID_STATICTEXT30, _("MCLK1 clock source"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT30"));
Clockcontrols11Sizer->Add(StaticText30, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbMCLK1SRC = new ComboBoxMap(Panel2, ID_MCLK1SRC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_MCLK1SRC"));
cmbMCLK1SRC->SetToolTip(_("MCLK1 clock source"));
Clockcontrols11Sizer->Add(cmbMCLK1SRC, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText31 = new wxStaticText(Panel2, ID_STATICTEXT31, _("TxTSPCLKA clock divider"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT31"));
Clockcontrols11Sizer->Add(StaticText31, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbTXTSPCLKA_DIV = new ComboBoxMap(Panel2, ID_TXTSPCLKA_DIV, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_TXTSPCLKA_DIV"));
cmbTXTSPCLKA_DIV->SetToolTip(_("TxTSP clock divider, used to produce MCLK(1/2).\nClock division ratio is 2(TXTSPCLKA_DIV + 1)"));
Clockcontrols11Sizer->Add(cmbTXTSPCLKA_DIV, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText32 = new wxStaticText(Panel2, ID_STATICTEXT32, _("RxTSPCLKA clock divider"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT32"));
Clockcontrols11Sizer->Add(StaticText32, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRXTSPCLKA_DIV = new ComboBoxMap(Panel2, ID_RXTSPCLKA_DIV, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RXTSPCLKA_DIV"));
cmbRXTSPCLKA_DIV->SetToolTip(_("RxTSP clock divider, used to produce MCLK(1/2).\nClock division ratio is 2(RXTSPCLKA_DIV + 1)"));
Clockcontrols11Sizer->Add(cmbRXTSPCLKA_DIV, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkTXDIVEN = new wxCheckBox(Panel2, ID_TXDIVEN, _("Enable Tx clock divider"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXDIVEN"));
chkTXDIVEN->SetValue(false);
chkTXDIVEN->SetToolTip(_("TX clock divider enable"));
Clockcontrols11Sizer->Add(chkTXDIVEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkRXDIVEN = new wxCheckBox(Panel2, ID_RXDIVEN, _("Enable Rx clock divider"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_RXDIVEN"));
chkRXDIVEN->SetValue(false);
chkRXDIVEN->SetToolTip(_("RX clock divider enable"));
Clockcontrols11Sizer->Add(chkRXDIVEN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkFCLK1_INV = new wxCheckBox(Panel2, ID_FCLK1_INV, _("FCLK1 invert"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FCLK1_INV"));
chkFCLK1_INV->SetValue(false);
chkFCLK1_INV->SetToolTip(_("FCLK1 clock inversion"));
Clockcontrols11Sizer->Add(chkFCLK1_INV, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
chkFCLK2_INV = new wxCheckBox(Panel2, ID_FCLK2_INV, _("FCLK2 invert"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FCLK2_INV"));
chkFCLK2_INV->SetValue(false);
chkFCLK2_INV->SetToolTip(_("FCLK2 clock inversion"));
Clockcontrols11Sizer->Add(chkFCLK2_INV, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
StaticText37 = new wxStaticText(Panel2, ID_STATICTEXT37, _("MCLK1DLY"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT37"));
Clockcontrols11Sizer->Add(StaticText37, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
cmbMCLK1DLY = new ComboBoxMap(Panel2, ID_MCLK1DLY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_MCLK1DLY"));
cmbMCLK1DLY->SetToolTip(_("MCLK1 clock internal delay"));
Clockcontrols11Sizer->Add(cmbMCLK1DLY, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
StaticText39 = new wxStaticText(Panel2, ID_STATICTEXT39, _("MCLK2DLY"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT39"));
Clockcontrols11Sizer->Add(StaticText39, 1, wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
cmbMCLK2DLY = new ComboBoxMap(Panel2, ID_MCLK2DLY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_MCLK2DLY"));
cmbMCLK2DLY->SetToolTip(_("MCLK2 clock internal delay"));
Clockcontrols11Sizer->Add(cmbMCLK2DLY, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
ClockcontrolsSizer->Add(Clockcontrols11Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer4->Add(ClockcontrolsSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, Panel2, _("Direction controls"));
FlexGridSizer9 = new wxFlexGridSizer(0, 2, 0, 5);
wxString __wxRadioBoxChoices_14[2] =
{
	_("Automatic"),
	_("Manual")
};
rgrDIQDIRCTR2 = new wxRadioBox(Panel2, ID_DIQDIRCTR2, _("DIQ2 mode"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_14, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DIQDIRCTR2"));
rgrDIQDIRCTR2->SetToolTip(_("DIQ2 direction control mode"));
FlexGridSizer9->Add(rgrDIQDIRCTR2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_15[2] =
{
	_("Automatic"),
	_("Manual")
};
rgrDIQDIRCTR1 = new wxRadioBox(Panel2, ID_DIQDIRCTR1, _("DIQ1 mode"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_15, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DIQDIRCTR1"));
rgrDIQDIRCTR1->SetToolTip(_("DIQ1 direction control mode"));
FlexGridSizer9->Add(rgrDIQDIRCTR1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_16[2] =
{
	_("Output"),
	_("Input")
};
rgrDIQDIR2 = new wxRadioBox(Panel2, ID_DIQDIR2, _("DIQ2 direction"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_16, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DIQDIR2"));
rgrDIQDIR2->SetToolTip(_("DIQ2 direction"));
FlexGridSizer9->Add(rgrDIQDIR2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_17[2] =
{
	_("Output"),
	_("Input")
};
rgrDIQDIR1 = new wxRadioBox(Panel2, ID_DIQDIR1, _("DIQ1 direction"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_17, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_DIQDIR1"));
rgrDIQDIR1->SetToolTip(_("DIQ1 direction"));
FlexGridSizer9->Add(rgrDIQDIR1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_18[2] =
{
	_("Automatic"),
	_("Manual")
};
rgrENABLEDIRCTR2 = new wxRadioBox(Panel2, ID_ENABLEDIRCTR2, _("ENABLE2 mode"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_18, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_ENABLEDIRCTR2"));
rgrENABLEDIRCTR2->SetToolTip(_("ENABLE2 direction control mode"));
FlexGridSizer9->Add(rgrENABLEDIRCTR2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_19[2] =
{
	_("Automatic"),
	_("Manual")
};
rgrENABLEDIRCTR1 = new wxRadioBox(Panel2, ID_ENABLEDIRCTR1, _("ENABLE1 mode"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_19, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_ENABLEDIRCTR1"));
rgrENABLEDIRCTR1->SetToolTip(_("ENABLE1 direction control mode"));
FlexGridSizer9->Add(rgrENABLEDIRCTR1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_20[2] =
{
	_("Output"),
	_("Input")
};
rgrENABLEDIR2 = new wxRadioBox(Panel2, ID_ENABLEDIR2, _("ENABLE2 direction"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_20, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_ENABLEDIR2"));
rgrENABLEDIR2->SetToolTip(_("ENABLE2 direction"));
FlexGridSizer9->Add(rgrENABLEDIR2, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
wxString __wxRadioBoxChoices_21[2] =
{
	_("Output"),
	_("Input")
};
rgrENABLEDIR1 = new wxRadioBox(Panel2, ID_ENABLEDIR1, _("ENABLE1 direction"), wxDefaultPosition, wxDefaultSize, 2, __wxRadioBoxChoices_21, 1, wxRA_SPECIFY_COLS, wxDefaultValidator, _T("ID_ENABLEDIR1"));
rgrENABLEDIR1->SetToolTip(_("ENABLE1 direction."));
FlexGridSizer9->Add(rgrENABLEDIR1, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
StaticBoxSizer1->Add(FlexGridSizer9, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer4->Add(StaticBoxSizer1, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer3->Add(FlexGridSizer4, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
LML1Sizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("LML1"));
LML18Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText17 = new wxStaticText(Panel2, ID_STATICTEXT17, _("Clock cycles to wait before data drive stop"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
LML18Sizer->Add(StaticText17, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_TX_PST = new ComboBoxMap(Panel2, ID_LML1_TX_PST, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LML1_TX_PST"));
cmbLML1_TX_PST->SetToolTip(_("Number of clock cycles to wait before data drive stop after burst stop is detected in JESD207 mode on Port 1 and Port 1 BB2RF"));
LML18Sizer->Add(cmbLML1_TX_PST, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText18 = new wxStaticText(Panel2, ID_STATICTEXT18, _("Clock cycles to wait before data drive start"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
LML18Sizer->Add(StaticText18, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_TX_PRE = new ComboBoxMap(Panel2, ID_LML1_TX_PRE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LML1_TX_PRE"));
cmbLML1_TX_PRE->SetToolTip(_("Number of clock cycles to wait before data drive start after burst start is detected in JESD207 mode on Port 1 and Port 1 BB2RF"));
LML18Sizer->Add(cmbLML1_TX_PRE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText19 = new wxStaticText(Panel2, ID_STATICTEXT19, _("Clock cycles to wait before data capture stop"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
LML18Sizer->Add(StaticText19, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_RX_PST = new ComboBoxMap(Panel2, ID_LML1_RX_PST, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LML1_RX_PST"));
cmbLML1_RX_PST->SetToolTip(_("Number of clock cycles to wait before data capture stop after burst stop is detected in JESD207 mode on Port 1 and Port 1 is RF2BB"));
LML18Sizer->Add(cmbLML1_RX_PST, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText20 = new wxStaticText(Panel2, ID_STATICTEXT20, _("Clock cycles to wait before data capture start"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
LML18Sizer->Add(StaticText20, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML1_RX_PRE = new ComboBoxMap(Panel2, ID_LML1_RX_PRE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LML1_RX_PRE"));
cmbLML1_RX_PRE->SetToolTip(_("Number of clock cycles to wait before data capture start after burst start is detected in JESD207 mode on Port 1 and Port 1 RF2BB"));
LML18Sizer->Add(cmbLML1_RX_PRE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
LML1Sizer->Add(LML18Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer6->Add(LML1Sizer, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
LML2Sizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("LML2"));
LML29Sizer = new wxFlexGridSizer(0, 2, 0, 5);
StaticText21 = new wxStaticText(Panel2, ID_STATICTEXT21, _("Clock cycles to wait before data drive stop"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
LML29Sizer->Add(StaticText21, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_TX_PST = new ComboBoxMap(Panel2, ID_LML2_TX_PST, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LML2_TX_PST"));
cmbLML2_TX_PST->SetToolTip(_("Number of clock cycles to wait before data drive stop after burst stop is detected in JESD207 mode on Port 2 and Port 2 BB2RF"));
LML29Sizer->Add(cmbLML2_TX_PST, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText22 = new wxStaticText(Panel2, ID_STATICTEXT22, _("Clock cycles to wait before data drive start"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
LML29Sizer->Add(StaticText22, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_TX_PRE = new ComboBoxMap(Panel2, ID_LML2_TX_PRE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LML2_TX_PRE"));
cmbLML2_TX_PRE->SetToolTip(_("Number of clock cycles to wait before data drive start after burst start is detected in JESD207 mode on Port 2 and Port 2 BB2RF"));
LML29Sizer->Add(cmbLML2_TX_PRE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText23 = new wxStaticText(Panel2, ID_STATICTEXT23, _("Clock cycles to wait before data capture stop"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
LML29Sizer->Add(StaticText23, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_RX_PST = new ComboBoxMap(Panel2, ID_LML2_RX_PST, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LML2_RX_PST"));
cmbLML2_RX_PST->SetToolTip(_("Number of clock cycles to wait before data capture stop after burst stop is detected in JESD207 mode on Port 2 and Port 2 RF2BB"));
LML29Sizer->Add(cmbLML2_RX_PST, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText24 = new wxStaticText(Panel2, ID_STATICTEXT24, _("Clock cycles to wait before data capture start"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
LML29Sizer->Add(StaticText24, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbLML2_RX_PRE = new ComboBoxMap(Panel2, ID_LML2_RX_PRE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LML2_RX_PRE"));
cmbLML2_RX_PRE->SetToolTip(_("Number of clock cycles to wait before data capture start after burst start is detected in JESD207 mode on Port 2 and Port 2 RF2BB"));
LML29Sizer->Add(cmbLML2_RX_PRE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
LML2Sizer->Add(LML29Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer6->Add(LML2Sizer, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
FlexGridSizer3->Add(FlexGridSizer6, 1, wxALIGN_LEFT|wxALIGN_TOP, 5);
Panel2->SetSizer(FlexGridSizer3);
FlexGridSizer3->Fit(Panel2);
FlexGridSizer3->SetSizeHints(Panel2);
Notebook1->AddPage(Panel1, _("Modes"), false);
Notebook1->AddPage(Panel2, _("Sample position && Clock"), false);
FlexGridSizer1->Add(Notebook1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_TX_CLK_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_RX_CLK_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SDA_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SCL_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SDIO_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SDO_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SCLK_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SEN_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_DIQ2_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_IQ_SEL_EN_2_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_TXNRX2_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_FCLK2_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MCLK2_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_DIQ1_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_IQ_SEL_EN_1_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_TXNRX1_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_FCLK1_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MCLK1_PE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MOD_EN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML_FIDM1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML_FIDM2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML_MODE1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML_MODE2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML_TXNRXIQ1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML_TXNRXIQ2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LRST_TX_B,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MRST_TX_B,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LRST_TX_A,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MRST_TX_A,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LRST_RX_B,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MRST_RX_B,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LRST_RX_A,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MRST_RX_A,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SRST_RXFIFO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SRST_TXFIFO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SDA_DS,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SCL_DS,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SDIO_DS,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_DIQ2_DS,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_DIQ1_DS,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_RX_MUX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_TX_MUX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MIMO_SISO,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_SPIMODE,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MAC,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_RXEN_B,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_RXEN_A,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_TXEN_B,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_TXEN_A,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::OnbtnReadVerRevMaskClick);
Connect(ID_LML1_S3S,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML1_S2S,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML1_S1S,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML1_S0S,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML1_BQP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML1_BIP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML1_AQP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML1_AIP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_S3S,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_S2S,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_S1S,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_S0S,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_BQP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_BIP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_AQP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_AIP,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_TXRDCLK_MUX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_TXWRCLK_MUX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_RXRDCLK_MUX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_RXWRCLK_MUX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MCLK2SRC,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MCLK1SRC,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_TXTSPCLKA_DIV,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_RXTSPCLKA_DIV,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_TXDIVEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_RXDIVEN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_FCLK1_INV,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_FCLK2_INV,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MCLK1DLY,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_MCLK2DLY,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_DIQDIRCTR2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_DIQDIRCTR1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_DIQDIR2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_DIQDIR1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_ENABLEDIRCTR2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_ENABLEDIRCTR1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_ENABLEDIR2,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_ENABLEDIR1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML1_TX_PST,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML1_TX_PRE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML1_RX_PST,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML1_RX_PRE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_TX_PST,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_TX_PRE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_RX_PST,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
Connect(ID_LML2_RX_PRE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLimeLightPAD::ParameterChangeHandler);
//*)
}
pnlLimeLightPAD::~pnlLimeLightPAD()
{
//(*Destroy(pnlLimeLightPAD)
//*)
}
void pnlLimeLightPAD::ParameterChangeHandler(wxCommandEvent& event)
{
    unsigned long value = event.GetInt();
    if(lmsControl == NULL)
    {
        std::cout << "pnlLimeLightPAD panel don't have control module assigned" << std::endl;
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
    case LRST_RX_A:
    case LRST_RX_B:
    case LRST_TX_A:
    case LRST_TX_B:
    case MRST_RX_A:
    case MRST_RX_B:
    case MRST_TX_A:
    case MRST_TX_B:
    case SRST_RXFIFO:
    case SRST_TXFIFO:
        value = !(bool)value;
    default:
        lmsControl->SetParam( parameter, value);
    }
}

void pnlLimeLightPAD::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    char ctemp[80];
    vector<string> temp;
    temp.clear();
    temp.push_back("RxTSP");
    temp.push_back("TxFIFO");
    temp.push_back("LFSR");
    cmbRX_MUX->Clear();
    cmbRX_MUX->Append(temp);
    cmbRX_MUX->SetSelection( lmsControl->GetParam(RX_MUX));

    temp.clear();
    temp.push_back("position 0");
    temp.push_back("position 1");
    temp.push_back("position 2");
    temp.push_back("position 3");
    cmbLML1_AIP->Clear();
    cmbLML1_AIP->Append(temp);
    cmbLML1_AIP->SetSelection( lmsControl->GetParam(LML1_AIP));

    temp.clear();
    temp.push_back("position 0");
    temp.push_back("position 1");
    temp.push_back("position 2");
    temp.push_back("position 3");
    cmbLML1_AQP->Clear();
    cmbLML1_AQP->Append(temp);
    cmbLML1_AQP->SetSelection( lmsControl->GetParam(LML1_AQP));

    temp.clear();
    temp.push_back("position 0");
    temp.push_back("position 1");
    temp.push_back("position 2");
    temp.push_back("position 3");
    cmbLML1_BIP->Clear();
    cmbLML1_BIP->Append(temp);
    cmbLML1_BIP->SetSelection( lmsControl->GetParam(LML1_BIP));

    temp.clear();
    temp.push_back("position 0");
    temp.push_back("position 1");
    temp.push_back("position 2");
    temp.push_back("position 3");
    cmbLML1_BQP->Clear();
    cmbLML1_BQP->Append(temp);
    cmbLML1_BQP->SetSelection( lmsControl->GetParam(LML1_BQP));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbLML1_RX_PRE->Clear();
    cmbLML1_RX_PRE->Append(temp);
    cmbLML1_RX_PRE->SetSelection( lmsControl->GetParam(LML1_RF2BB_PRE));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbLML1_RX_PST->Clear();
    cmbLML1_RX_PST->Append(temp);
    cmbLML1_RX_PST->SetSelection( lmsControl->GetParam(LML1_RF2BB_PST));

    temp.clear();
    temp.push_back("AI");
    temp.push_back("AQ");
    temp.push_back("BI");
    temp.push_back("BQ");
    cmbLML1_S0S->Clear();
    cmbLML1_S0S->Append(temp);
    cmbLML1_S0S->SetSelection( lmsControl->GetParam(LML1_S0S));

    temp.clear();
    temp.push_back("AI");
    temp.push_back("AQ");
    temp.push_back("BI");
    temp.push_back("BQ");
    cmbLML1_S1S->Clear();
    cmbLML1_S1S->Append(temp);
    cmbLML1_S1S->SetSelection( lmsControl->GetParam(LML1_S1S));

    temp.clear();
    temp.push_back("AI");
    temp.push_back("AQ");
    temp.push_back("BI");
    temp.push_back("BQ");
    cmbLML1_S2S->Clear();
    cmbLML1_S2S->Append(temp);
    cmbLML1_S2S->SetSelection( lmsControl->GetParam(LML1_S2S));

    temp.clear();
    temp.push_back("AI");
    temp.push_back("AQ");
    temp.push_back("BI");
    temp.push_back("BQ");
    cmbLML1_S3S->Clear();
    cmbLML1_S3S->Append(temp);
    cmbLML1_S3S->SetSelection( lmsControl->GetParam(LML1_S3S));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbLML1_TX_PRE->Clear();
    cmbLML1_TX_PRE->Append(temp);
    cmbLML1_TX_PRE->SetSelection( lmsControl->GetParam(LML1_BB2RF_PRE));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbLML1_TX_PST->Clear();
    cmbLML1_TX_PST->Append(temp);
    cmbLML1_TX_PST->SetSelection( lmsControl->GetParam(LML1_BB2RF_PST));

    temp.clear();
    temp.push_back("position 0");
    temp.push_back("position 1");
    temp.push_back("position 2");
    temp.push_back("position 3");
    cmbLML2_AIP->Clear();
    cmbLML2_AIP->Append(temp);
    cmbLML2_AIP->SetSelection( lmsControl->GetParam(LML2_AIP));

    temp.clear();
    temp.push_back("position 0");
    temp.push_back("position 1");
    temp.push_back("position 2");
    temp.push_back("position 3");
    cmbLML2_AQP->Clear();
    cmbLML2_AQP->Append(temp);
    cmbLML2_AQP->SetSelection( lmsControl->GetParam(LML2_AQP));

    temp.clear();
    temp.push_back("position 0");
    temp.push_back("position 1");
    temp.push_back("position 2");
    temp.push_back("position 3");
    cmbLML2_BIP->Clear();
    cmbLML2_BIP->Append(temp);
    cmbLML2_BIP->SetSelection( lmsControl->GetParam(LML2_BIP));

    temp.clear();
    temp.push_back("position 0");
    temp.push_back("position 1");
    temp.push_back("position 2");
    temp.push_back("position 3");
    cmbLML2_BQP->Clear();
    cmbLML2_BQP->Append(temp);
    cmbLML2_BQP->SetSelection( lmsControl->GetParam(LML2_BQP));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbLML2_RX_PRE->Clear();
    cmbLML2_RX_PRE->Append(temp);
    cmbLML2_RX_PRE->SetSelection( lmsControl->GetParam(LML2_RF2BB_PRE));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbLML2_RX_PST->Clear();
    cmbLML2_RX_PST->Append(temp);
    cmbLML2_RX_PST->SetSelection( lmsControl->GetParam(LML2_RF2BB_PST));

    temp.clear();
    temp.push_back("AI");
    temp.push_back("AQ");
    temp.push_back("BI");
    temp.push_back("BQ");
    cmbLML2_S0S->Clear();
    cmbLML2_S0S->Append(temp);
    cmbLML2_S0S->SetSelection( lmsControl->GetParam(LML2_S0S));

    temp.clear();
    temp.push_back("AI");
    temp.push_back("AQ");
    temp.push_back("BI");
    temp.push_back("BQ");
    cmbLML2_S1S->Clear();
    cmbLML2_S1S->Append(temp);
    cmbLML2_S1S->SetSelection( lmsControl->GetParam(LML2_S1S));

    temp.clear();
    temp.push_back("AI");
    temp.push_back("AQ");
    temp.push_back("BI");
    temp.push_back("BQ");
    cmbLML2_S2S->Clear();
    cmbLML2_S2S->Append(temp);
    cmbLML2_S2S->SetSelection( lmsControl->GetParam(LML2_S2S));

    temp.clear();
    temp.push_back("AI");
    temp.push_back("AQ");
    temp.push_back("BI");
    temp.push_back("BQ");
    cmbLML2_S3S->Clear();
    cmbLML2_S3S->Append(temp);
    cmbLML2_S3S->SetSelection( lmsControl->GetParam(LML2_S3S));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbLML2_TX_PRE->Clear();
    cmbLML2_TX_PRE->Append(temp);
    cmbLML2_TX_PRE->SetSelection( lmsControl->GetParam(LML2_BB2RF_PRE));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbLML2_TX_PST->Clear();
    cmbLML2_TX_PST->Append(temp);
    cmbLML2_TX_PST->SetSelection( lmsControl->GetParam(LML2_BB2RF_PST));

    temp.clear();
    temp.push_back("TxTSPCLKA after divider");
    temp.push_back("RxTSPCLKA after divider");
    temp.push_back("TxTSPCLKA");
    temp.push_back("RxTSPCLKA");
    cmbMCLK1SRC->Clear();
    cmbMCLK1SRC->Append(temp);
    cmbMCLK1SRC->SetSelection( lmsControl->GetParam(MCLK1SRC));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbRXTSPCLKA_DIV->Clear();
    cmbRXTSPCLKA_DIV->Append(temp);
    cmbRXTSPCLKA_DIV->SetSelection( lmsControl->GetParam(RXTSPCLKA_DIV));

    temp.clear();
    temp.push_back("TxTSPCLKA after divider");
    temp.push_back("RxTSPCLKA after divider");
    temp.push_back("TxTSPCLKA");
    temp.push_back("RxTSPCLKA");

    cmbMCLK2SRC->Clear();
    cmbMCLK2SRC->Append(temp);
    cmbMCLK2SRC->SetSelection( lmsControl->GetParam(MCLK2SRC));

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%i", i); temp.push_back(ctemp);}
    cmbTXTSPCLKA_DIV->Clear();
    cmbTXTSPCLKA_DIV->Append(temp);
    cmbTXTSPCLKA_DIV->SetSelection( lmsControl->GetParam(TXTSPCLKA_DIV));

    temp.clear();
    temp.push_back("Enables MIMO channel B, when SISO_ID (from pad) is 0");
    temp.push_back("Disables MIMO channel B, when SISO_ID (from pad) is 1");
    cmbMIMO_SISO->Clear();
    cmbMIMO_SISO->Append(temp);
    cmbMIMO_SISO->SetSelection( lmsControl->GetParam(MIMO_SISO));

    temp.clear();
    temp.push_back("MCLK1");
    temp.push_back("MCLK2");
    temp.push_back("FCLK1");
    temp.push_back("FCLK2");
    cmbRXRDCLK_MUX->Clear();
    cmbRXRDCLK_MUX->Append(temp);
    cmbRXRDCLK_MUX->SetSelection( lmsControl->GetParam(RXRDCLK_MUX));

    temp.clear();
    temp.push_back("FCLK1");
    temp.push_back("FCLK2");
    temp.push_back("RxTSPCLK");
    cmbRXWRCLK_MUX->Clear();
    cmbRXWRCLK_MUX->Append(temp);
    cmbRXWRCLK_MUX->SetSelection( lmsControl->GetParam(RXWRCLK_MUX));

    temp.clear();
    temp.push_back("Port 1");
    temp.push_back("Port 2");
    temp.push_back("RxTSP");
    cmbTX_MUX->Clear();
    cmbTX_MUX->Append(temp);
    cmbTX_MUX->SetSelection( lmsControl->GetParam(TX_MUX));

    temp.clear();
    temp.push_back("FCLK1");
    temp.push_back("FCLK2");
    temp.push_back("TxTSPCLK");
    cmbTXRDCLK_MUX->Clear();
    cmbTXRDCLK_MUX->Append(temp);
    cmbTXRDCLK_MUX->SetSelection( lmsControl->GetParam(TXRDCLK_MUX));

    temp.clear();
    temp.push_back("FCLK1");
    temp.push_back("FCLK2");
    temp.push_back("RxTSPCLK");
    cmbTXWRCLK_MUX->Clear();
    cmbTXWRCLK_MUX->Append(temp);
    cmbTXWRCLK_MUX->SetSelection( lmsControl->GetParam(TXWRCLK_MUX));

    temp.clear();
    temp.push_back("No delay");
    temp.push_back("1x delay");
    temp.push_back("2x delay");
    temp.push_back("3x delay");
    cmbMCLK1DLY->Clear();
    cmbMCLK1DLY->Append(temp);
    cmbMCLK1DLY->SetSelection( lmsControl->GetParam(MCLK1DLY));
    cmbMCLK2DLY->Clear();
    cmbMCLK2DLY->Append(temp);
    cmbMCLK2DLY->SetSelection( lmsControl->GetParam(MCLK2DLY));
    UpdateTooltips(this);
}

void pnlLimeLightPAD::UpdateGUI()
{    
    long value = 0;
    value = lmsControl->GetParam(DIQ1_DS);
    rgrDIQ1_DS->SetSelection(value);

    value = lmsControl->GetParam(DIQ1_PE);
    chkDIQ1_PE->SetValue(value);

    value = lmsControl->GetParam(DIQ2_DS);
    rgrDIQ2_DS->SetSelection(value);

    value = lmsControl->GetParam(DIQ2_PE);
    chkDIQ2_PE->SetValue(value);

    value = lmsControl->GetParam(RX_MUX);
    cmbRX_MUX->SetSelection(value);

    value = lmsControl->GetParam(FCLK1_PE);
    chkFCLK1_PE->SetValue(value);

    value = lmsControl->GetParam(FCLK2_PE);
    chkFCLK2_PE->SetValue(value);

    value = lmsControl->GetParam(IQ_SEL_EN_1_PE);
    chkIQ_SEL_EN_1_PE->SetValue(value);

    value = lmsControl->GetParam(IQ_SEL_EN_2_PE);
    chkIQ_SEL_EN_2_PE->SetValue(value);

    value = lmsControl->GetParam(LML1_AIP);
    cmbLML1_AIP->SetSelection(value);

    value = lmsControl->GetParam(LML1_AQP);
    cmbLML1_AQP->SetSelection(value);

    value = lmsControl->GetParam(LML1_BIP);
    cmbLML1_BIP->SetSelection(value);

    value = lmsControl->GetParam(LML1_BQP);
    cmbLML1_BQP->SetSelection(value);

    value = lmsControl->GetParam(LML1_RF2BB_PRE);
    cmbLML1_RX_PRE->SetSelection(value);

    value = lmsControl->GetParam(LML1_RF2BB_PST);
    cmbLML1_RX_PST->SetSelection(value);

    value = lmsControl->GetParam(LML1_S0S);
    cmbLML1_S0S->SetSelection(value);

    value = lmsControl->GetParam(LML1_S1S);
    cmbLML1_S1S->SetSelection(value);

    value = lmsControl->GetParam(LML1_S2S);
    cmbLML1_S2S->SetSelection(value);

    value = lmsControl->GetParam(LML1_S3S);
    cmbLML1_S3S->SetSelection(value);

    value = lmsControl->GetParam(LML1_BB2RF_PRE);
    cmbLML1_TX_PRE->SetSelection(value);

    value = lmsControl->GetParam(LML1_BB2RF_PST);
    cmbLML1_TX_PST->SetSelection(value);

    value = lmsControl->GetParam(LML2_AIP);
    cmbLML2_AIP->SetSelection(value);

    value = lmsControl->GetParam(LML2_AQP);
    cmbLML2_AQP->SetSelection(value);

    value = lmsControl->GetParam(LML2_BIP);
    cmbLML2_BIP->SetSelection(value);

    value = lmsControl->GetParam(LML2_BQP);
    cmbLML2_BQP->SetSelection(value);

    value = lmsControl->GetParam(LML2_RF2BB_PRE);
    cmbLML2_RX_PRE->SetSelection(value);

    value = lmsControl->GetParam(LML2_RF2BB_PST);
    cmbLML2_RX_PST->SetSelection(value);

    value = lmsControl->GetParam(LML2_S0S);
    cmbLML2_S0S->SetSelection(value);

    value = lmsControl->GetParam(LML2_S1S);
    cmbLML2_S1S->SetSelection(value);

    value = lmsControl->GetParam(LML2_S2S);
    cmbLML2_S2S->SetSelection(value);

    value = lmsControl->GetParam(LML2_S3S);
    cmbLML2_S3S->SetSelection(value);

    value = lmsControl->GetParam(LML2_BB2RF_PRE);
    cmbLML2_TX_PRE->SetSelection(value);

    value = lmsControl->GetParam(LML2_BB2RF_PST);
    cmbLML2_TX_PST->SetSelection(value);

    value = lmsControl->GetParam(LML1_MODE);
    rgrLML_MODE1->SetSelection(value);

    value = lmsControl->GetParam(LML2_MODE);
    rgrLML_MODE2->SetSelection(value);

    value = lmsControl->GetParam(LML1_TXNRXIQ);
    rgrLML_TXNRXIQ1->SetSelection(value);

    value = lmsControl->GetParam(LML2_TXNRXIQ);
    rgrLML_TXNRXIQ2->SetSelection(value);

    value = lmsControl->GetParam(LRST_RX_A);
    chkLRST_RX_A->SetValue(!value);

    value = lmsControl->GetParam(LRST_RX_B);
    chkLRST_RX_B->SetValue(!value);

    value = lmsControl->GetParam(LRST_TX_A);
    chkLRST_TX_A->SetValue(!value);

    value = lmsControl->GetParam(LRST_TX_B);
    chkLRST_TX_B->SetValue(!value);

    value = lmsControl->GetParam(MAC);
    rgrMAC->SetSelection(value);

    value = lmsControl->GetParam(MCLK1SRC);
    cmbMCLK1SRC->SetSelection(value);

    value = lmsControl->GetParam(RXTSPCLKA_DIV);
    cmbRXTSPCLKA_DIV->SetSelection(value);

    value = lmsControl->GetParam(MCLK1_PE);
    chkMCLK1_PE->SetValue(value);

    value = lmsControl->GetParam(MCLK2SRC);
    cmbMCLK2SRC->SetSelection(value);

    value = lmsControl->GetParam(TXTSPCLKA_DIV);
    cmbTXTSPCLKA_DIV->SetSelection(value);

    value = lmsControl->GetParam(MCLK2_PE);
    chkMCLK2_PE->SetValue(value);

    value = lmsControl->GetParam(MIMO_SISO);
    cmbMIMO_SISO->SetSelection(value);

    value = lmsControl->GetParam(MOD_EN);
    chkMOD_EN->SetValue(value);

    value = lmsControl->GetParam(MRST_RX_A);
    chkMRST_RX_A->SetValue(!value);

    value = lmsControl->GetParam(MRST_RX_B);
    chkMRST_RX_B->SetValue(!value);

    value = lmsControl->GetParam(MRST_TX_A);
    chkMRST_TX_A->SetValue(!value);

    value = lmsControl->GetParam(MRST_TX_B);
    chkMRST_TX_B->SetValue(!value);

    value = lmsControl->GetParam(RXDIVEN);
    chkRXDIVEN->SetValue(value);

    value = lmsControl->GetParam(RXEN_A);
    chkRXEN_A->SetValue(value);

    value = lmsControl->GetParam(RXEN_B);
    chkRXEN_B->SetValue(value);

    value = lmsControl->GetParam(RXRDCLK_MUX);
    cmbRXRDCLK_MUX->SetSelection(value);

    value = lmsControl->GetParam(RXWRCLK_MUX);
    cmbRXWRCLK_MUX->SetSelection(value);

    value = lmsControl->GetParam(RX_CLK_PE);
    chkRX_CLK_PE->SetValue(value);

    value = lmsControl->GetParam(SCLK_PE);
    chkSCLK_PE->SetValue(value);

    value = lmsControl->GetParam(SCL_DS);
    rgrSCL_DS->SetSelection(value);

    value = lmsControl->GetParam(SCL_PE);
    chkSCL_PE->SetValue(value);

    value = lmsControl->GetParam(SDA_DS);
    rgrSDA_DS->SetSelection(value);

    value = lmsControl->GetParam(SDA_PE);
    chkSDA_PE->SetValue(value);

    value = lmsControl->GetParam(SDIO_DS);
    rgrSDIO_DS->SetSelection(value);

    value = lmsControl->GetParam(SDIO_PE);
    chkSDIO_PE->SetValue(value);

    value = lmsControl->GetParam(SDO_PE);
    chkSDO_PE->SetValue(value);

    value = lmsControl->GetParam(SEN_PE);
    chkSEN_PE->SetValue(value);

    value = lmsControl->GetParam(SPIMODE);
    rgrSPIMODE->SetSelection(value);

    value = lmsControl->GetParam(SRST_RXFIFO);
    chkSRST_RXFIFO->SetValue(!value);

    value = lmsControl->GetParam(SRST_TXFIFO);
    chkSRST_TXFIFO->SetValue(!value);

    value = lmsControl->GetParam(TXDIVEN);
    chkTXDIVEN->SetValue(value);

    value = lmsControl->GetParam(TXEN_A);
    chkTXEN_A->SetValue(value);

    value = lmsControl->GetParam(TXEN_B);
    chkTXEN_B->SetValue(value);

    value = lmsControl->GetParam(TX_MUX);
    cmbTX_MUX->SetSelection(value);

    value = lmsControl->GetParam(TXNRX1_PE);
    chkTXNRX1_PE->SetValue(value);

    value = lmsControl->GetParam(TXNRX2_PE);
    chkTXNRX2_PE->SetValue(value);

    value = lmsControl->GetParam(TXRDCLK_MUX);
    cmbTXRDCLK_MUX->SetSelection(value);

    value = lmsControl->GetParam(TXWRCLK_MUX);
    cmbTXWRCLK_MUX->SetSelection(value);

    value = lmsControl->GetParam(TX_CLK_PE);
    chkTX_CLK_PE->SetValue(value);

    value = lmsControl->GetParam(VER, true);
    lblVER->SetLabel( wxString::Format("%li", value));

    value = lmsControl->GetParam(REV, true);
    lblREV->SetLabel( wxString::Format("%li", value));

    value = lmsControl->GetParam(MASK, true);
    lblMASK->SetLabel( wxString::Format("%li", value));

    value = lmsControl->GetParam(MCLK1DLY);
    cmbMCLK1DLY->SetSelection(value);
    value = lmsControl->GetParam(MCLK2DLY);
    cmbMCLK2DLY->SetSelection(value);

    value = lmsControl->GetParam(FCLK1_INV);
    chkFCLK1_INV->SetValue(value);

    value = lmsControl->GetParam(FCLK2_INV);
    chkFCLK2_INV->SetValue(value);

    value = lmsControl->GetParam(DIQDIRCTR2);
    rgrDIQDIRCTR2->SetSelection(value);
    value = lmsControl->GetParam(DIQDIRCTR1);
    rgrDIQDIRCTR1->SetSelection(value);
    value = lmsControl->GetParam(DIQDIR2);
    rgrDIQDIR2->SetSelection(value);
    value = lmsControl->GetParam(DIQDIR1);
    rgrDIQDIR1->SetSelection(value);
    value = lmsControl->GetParam(ENABLEDIRCTR2);
    rgrENABLEDIRCTR2->SetSelection(value);
    value = lmsControl->GetParam(ENABLEDIRCTR1);
    rgrENABLEDIRCTR1->SetSelection(value);
    value = lmsControl->GetParam(ENABLEDIR2);
    rgrENABLEDIR2->SetSelection(value);
    value = lmsControl->GetParam(ENABLEDIR1);
    rgrENABLEDIR1->SetSelection(value);    
}


void pnlLimeLightPAD::OnbtnReadVerRevMaskClick(wxCommandEvent& event)
{
    int value = 0;
    value = lmsControl->GetParam(VER, true);
    lblVER->SetLabel( wxString::Format("%i", value));

    value = lmsControl->GetParam(REV, true);
    lblREV->SetLabel( wxString::Format("%i", value));

    value = lmsControl->GetParam(MASK, true);
    lblMASK->SetLabel( wxString::Format("%i", value));
}
