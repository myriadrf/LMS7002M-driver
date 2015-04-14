/**
@file	pnlLDO.cpp
@author	Lime Microsystems
@brief	LDO module panel
*/

#include "pnlLDO.h"
#include <iostream>
#include "ComboBoxMap.h"
#include "LMS7002_MainControl.h"
//(*InternalHeaders(pnlLDO)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/combobox.h>
//*)
//(*IdInit(pnlLDO)
const long pnlLDO::ID_EN_G_LDOP = wxNewId();
const long pnlLDO::ID_EN_G_LDO = wxNewId();
const long pnlLDO::ID_EN_LDO_DIVGN = wxNewId();
const long pnlLDO::ID_EN_LDO_DIGGN = wxNewId();
const long pnlLDO::ID_EN_LDO_CPGN = wxNewId();
const long pnlLDO::ID_EN_LDO_VCOGN = wxNewId();
const long pnlLDO::ID_EN_LDO_MXRFE = wxNewId();
const long pnlLDO::ID_EN_LDO_LNA14 = wxNewId();
const long pnlLDO::ID_EN_LDO_LNA12 = wxNewId();
const long pnlLDO::ID_EN_LDO_TIA14 = wxNewId();
const long pnlLDO::ID_EN_LDO_DIVSXT = wxNewId();
const long pnlLDO::ID_EN_LDO_DIGSXT = wxNewId();
const long pnlLDO::ID_EN_LDO_CPSXT = wxNewId();
const long pnlLDO::ID_EN_LDO_VCOSXT = wxNewId();
const long pnlLDO::ID_EN_LDO_DIVSXR = wxNewId();
const long pnlLDO::ID_EN_LDO_DIGSXR = wxNewId();
const long pnlLDO::ID_EN_LDO_CPSXR = wxNewId();
const long pnlLDO::ID_EN_LDO_VCOSXR = wxNewId();
const long pnlLDO::ID_PD_LDO_DIGIp1 = wxNewId();
const long pnlLDO::ID_PD_LDO_DIGIp2 = wxNewId();
const long pnlLDO::ID_EN_LDO_TXBUF = wxNewId();
const long pnlLDO::ID_EN_LDO_RXBUF = wxNewId();
const long pnlLDO::ID_EN_LDO_AFE = wxNewId();
const long pnlLDO::ID_PD_LDO_SPIBUF = wxNewId();
const long pnlLDO::ID_EN_LDO_TBB = wxNewId();
const long pnlLDO::ID_EN_LDO_RBB = wxNewId();
const long pnlLDO::ID_EN_LDO_TIA12 = wxNewId();
const long pnlLDO::ID_EN_LDO_TPAD = wxNewId();
const long pnlLDO::ID_EN_LDO_TLOB = wxNewId();
const long pnlLDO::ID_EN_LDO_DIG = wxNewId();
const long pnlLDO::ID_BYP_LDO_TBB = wxNewId();
const long pnlLDO::ID_BYP_LDO_TIA12 = wxNewId();
const long pnlLDO::ID_BYP_LDO_TIA14 = wxNewId();
const long pnlLDO::ID_BYP_LDO_TLOB = wxNewId();
const long pnlLDO::ID_BYP_LDO_TPAD = wxNewId();
const long pnlLDO::ID_BYP_LDO_TXBUF = wxNewId();
const long pnlLDO::ID_BYP_LDO_VCOGN = wxNewId();
const long pnlLDO::ID_BYP_LDO_VCOSXR = wxNewId();
const long pnlLDO::ID_BYP_LDO_VCOSXT = wxNewId();
const long pnlLDO::ID_BYP_LDO_AFE = wxNewId();
const long pnlLDO::ID_BYP_LDO_CPGN = wxNewId();
const long pnlLDO::ID_BYP_LDO_CPSXR = wxNewId();
const long pnlLDO::ID_BYP_LDO_CPSXT = wxNewId();
const long pnlLDO::ID_BYP_LDO_DIG = wxNewId();
const long pnlLDO::ID_BYP_LDO_DIGGN = wxNewId();
const long pnlLDO::ID_BYP_LDO_DIGSXR = wxNewId();
const long pnlLDO::ID_BYP_LDO_DIGSXT = wxNewId();
const long pnlLDO::ID_BYP_LDO_DIVGN = wxNewId();
const long pnlLDO::ID_BYP_LDO_DIVSXR = wxNewId();
const long pnlLDO::ID_BYP_LDO_DIVSXT = wxNewId();
const long pnlLDO::ID_BYP_LDO_LNA12 = wxNewId();
const long pnlLDO::ID_BYP_LDO_LNA14 = wxNewId();
const long pnlLDO::ID_BYP_LDO_MXRFE = wxNewId();
const long pnlLDO::ID_BYP_LDO_RBB = wxNewId();
const long pnlLDO::ID_BYP_LDO_RXBUF = wxNewId();
const long pnlLDO::ID_BYP_LDO_SPIBUF = wxNewId();
const long pnlLDO::ID_BYP_LDO_DIGIp2 = wxNewId();
const long pnlLDO::ID_BYP_LDO_DIGIp1 = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_TBB = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_TIA12 = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_TIA14 = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_TLOB = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_TPAD = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_TXBUF = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_VCOGN = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_DIVSXR = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_DIVSXT = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_AFE = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_CPGN = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_VCOSXR = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_VCOSXT = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_DIG = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_DIGGN = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_DIGSXR = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_DIGSXT = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_DIVGN = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_CPSXR = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_CPSXT = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_LNA12 = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_LNA14 = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_MXRFE = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_RBB = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_RXBUF = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_SPIBUF = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_DIGIp2 = wxNewId();
const long pnlLDO::ID_SPDUP_LDO_DIGIp1 = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_TBB = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_TIA12 = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_TIA14 = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_TLOB = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_TPAD = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_TXBUF = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_VCOGN = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_VCOSXR = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_VCOSXT = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_AFE = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_CPGN = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_DIVSXR = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_DIVSXT = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_DIG = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_DIGGN = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_DIGSXR = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_DIGSXT = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_DIVGN = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_CPSXR = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_CPSXT = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_LNA12 = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_LNA14 = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_MXRFE = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_RBB = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_RXBUF = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_SPIBUF = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_DIGIp2 = wxNewId();
const long pnlLDO::ID_EN_LOADIMP_LDO_DIGIp1 = wxNewId();
const long pnlLDO::ID_PANEL3 = wxNewId();
const long pnlLDO::ID_STATICTEXT1 = wxNewId();
const long pnlLDO::ID_RDIV_VCOSXR = wxNewId();
const long pnlLDO::ID_STATICTEXT2 = wxNewId();
const long pnlLDO::ID_RDIV_VCOSXT = wxNewId();
const long pnlLDO::ID_STATICTEXT3 = wxNewId();
const long pnlLDO::ID_RDIV_TXBUF = wxNewId();
const long pnlLDO::ID_STATICTEXT4 = wxNewId();
const long pnlLDO::ID_RDIV_VCOGN = wxNewId();
const long pnlLDO::ID_STATICTEXT5 = wxNewId();
const long pnlLDO::ID_RDIV_TLOB = wxNewId();
const long pnlLDO::ID_STATICTEXT6 = wxNewId();
const long pnlLDO::ID_RDIV_TPAD = wxNewId();
const long pnlLDO::ID_STATICTEXT7 = wxNewId();
const long pnlLDO::ID_RDIV_TIA12 = wxNewId();
const long pnlLDO::ID_STATICTEXT8 = wxNewId();
const long pnlLDO::ID_RDIV_TIA14 = wxNewId();
const long pnlLDO::ID_STATICTEXT9 = wxNewId();
const long pnlLDO::ID_RDIV_RXBUF = wxNewId();
const long pnlLDO::ID_STATICTEXT10 = wxNewId();
const long pnlLDO::ID_RDIV_TBB = wxNewId();
const long pnlLDO::ID_STATICTEXT11 = wxNewId();
const long pnlLDO::ID_RDIV_MXRFE = wxNewId();
const long pnlLDO::ID_STATICTEXT12 = wxNewId();
const long pnlLDO::ID_RDIV_RBB = wxNewId();
const long pnlLDO::ID_STATICTEXT13 = wxNewId();
const long pnlLDO::ID_RDIV_LNA12 = wxNewId();
const long pnlLDO::ID_STATICTEXT14 = wxNewId();
const long pnlLDO::ID_RDIV_LNA14 = wxNewId();
const long pnlLDO::ID_STATICTEXT15 = wxNewId();
const long pnlLDO::ID_RDIV_DIVSXR = wxNewId();
const long pnlLDO::ID_STATICTEXT16 = wxNewId();
const long pnlLDO::ID_RDIV_DIVSXT = wxNewId();
const long pnlLDO::ID_STATICTEXT17 = wxNewId();
const long pnlLDO::ID_RDIV_DIGSXT = wxNewId();
const long pnlLDO::ID_STATICTEXT18 = wxNewId();
const long pnlLDO::ID_RDIV_DIVGN = wxNewId();
const long pnlLDO::ID_STATICTEXT19 = wxNewId();
const long pnlLDO::ID_RDIV_DIGGN = wxNewId();
const long pnlLDO::ID_STATICTEXT20 = wxNewId();
const long pnlLDO::ID_RDIV_DIGSXR = wxNewId();
const long pnlLDO::ID_STATICTEXT21 = wxNewId();
const long pnlLDO::ID_RDIV_CPSXT = wxNewId();
const long pnlLDO::ID_STATICTEXT22 = wxNewId();
const long pnlLDO::ID_RDIV_DIG = wxNewId();
const long pnlLDO::ID_STATICTEXT23 = wxNewId();
const long pnlLDO::ID_RDIV_CPGN = wxNewId();
const long pnlLDO::ID_STATICTEXT24 = wxNewId();
const long pnlLDO::ID_RDIV_CPSXR = wxNewId();
const long pnlLDO::ID_STATICTEXT25 = wxNewId();
const long pnlLDO::ID_RDIV_SPIBUF = wxNewId();
const long pnlLDO::ID_STATICTEXT26 = wxNewId();
const long pnlLDO::ID_RDIV_AFE = wxNewId();
const long pnlLDO::ID_STATICTEXT27 = wxNewId();
const long pnlLDO::ID_RDIV_DIGIp2 = wxNewId();
const long pnlLDO::ID_STATICTEXT28 = wxNewId();
const long pnlLDO::ID_RDIV_DIGIp1 = wxNewId();
const long pnlLDO::ID_PANEL2 = wxNewId();
const long pnlLDO::ID_NOTEBOOK1 = wxNewId();
//*)
BEGIN_EVENT_TABLE(pnlLDO,wxPanel)
//(*EventTable(pnlLDO)
//*)
END_EVENT_TABLE()

void pnlLDO::AssignEnumsToIds()
{
    wndId2Enum[ID_BYP_LDO_AFE] = BYP_LDO_AFE;
    wndId2Enum[ID_BYP_LDO_CPGN] = BYP_LDO_CPGN;
    wndId2Enum[ID_BYP_LDO_CPSXR] = BYP_LDO_CPSXR;
    wndId2Enum[ID_BYP_LDO_CPSXT] = BYP_LDO_CPSXT;
    wndId2Enum[ID_BYP_LDO_DIG] = BYP_LDO_DIG;
    wndId2Enum[ID_BYP_LDO_DIGGN] = BYP_LDO_DIGGN;
    wndId2Enum[ID_BYP_LDO_DIGIp1] = BYP_LDO_DIGIp1;
    wndId2Enum[ID_BYP_LDO_DIGIp2] = BYP_LDO_DIGIp2;
    wndId2Enum[ID_BYP_LDO_DIGSXR] = BYP_LDO_DIGSXR;
    wndId2Enum[ID_BYP_LDO_DIGSXT] = BYP_LDO_DIGSXT;
    wndId2Enum[ID_BYP_LDO_DIVGN] = BYP_LDO_DIVGN;
    wndId2Enum[ID_BYP_LDO_DIVSXR] = BYP_LDO_DIVSXR;
    wndId2Enum[ID_BYP_LDO_DIVSXT] = BYP_LDO_DIVSXT;
    wndId2Enum[ID_BYP_LDO_LNA12] = BYP_LDO_LNA12;
    wndId2Enum[ID_BYP_LDO_LNA14] = BYP_LDO_LNA14;
    wndId2Enum[ID_BYP_LDO_MXRFE] = BYP_LDO_MXRFE;
    wndId2Enum[ID_BYP_LDO_RBB] = BYP_LDO_RBB;
    wndId2Enum[ID_BYP_LDO_RXBUF] = BYP_LDO_RXBUF;
    wndId2Enum[ID_BYP_LDO_SPIBUF] = BYP_LDO_SPIBUF;
    wndId2Enum[ID_BYP_LDO_TBB] = BYP_LDO_TBB;
    wndId2Enum[ID_BYP_LDO_TIA12] = BYP_LDO_TIA12;
    wndId2Enum[ID_BYP_LDO_TIA14] = BYP_LDO_TIA14;
    wndId2Enum[ID_BYP_LDO_TLOB] = BYP_LDO_TLOB;
    wndId2Enum[ID_BYP_LDO_TPAD] = BYP_LDO_TPAD;
    wndId2Enum[ID_BYP_LDO_TXBUF] = BYP_LDO_TXBUF;
    wndId2Enum[ID_BYP_LDO_VCOGN] = BYP_LDO_VCOGN;
    wndId2Enum[ID_BYP_LDO_VCOSXR] = BYP_LDO_VCOSXR;
    wndId2Enum[ID_BYP_LDO_VCOSXT] = BYP_LDO_VCOSXT;
    wndId2Enum[ID_EN_G_LDO] = EN_G_LDO;
    wndId2Enum[ID_EN_G_LDOP] = EN_G_LDOP;
    wndId2Enum[ID_EN_LDO_AFE] = EN_LDO_AFE;
    wndId2Enum[ID_EN_LDO_CPGN] = EN_LDO_CPGN;
    wndId2Enum[ID_EN_LDO_CPSXR] = EN_LDO_CPSXR;
    wndId2Enum[ID_EN_LDO_CPSXT] = EN_LDO_CPSXT;
    wndId2Enum[ID_EN_LDO_DIG] = EN_LDO_DIG;
    wndId2Enum[ID_EN_LDO_DIGGN] = EN_LDO_DIGGN;
    wndId2Enum[ID_PD_LDO_DIGIp1] = PD_LDO_DIGIp1;
    wndId2Enum[ID_PD_LDO_DIGIp2] = PD_LDO_DIGIp2;
    wndId2Enum[ID_EN_LDO_DIGSXR] = EN_LDO_DIGSXR;
    wndId2Enum[ID_EN_LDO_DIGSXT] = EN_LDO_DIGSXT;
    wndId2Enum[ID_EN_LDO_DIVGN] = EN_LDO_DIVGN;
    wndId2Enum[ID_EN_LDO_DIVSXR] = EN_LDO_DIVSXR;
    wndId2Enum[ID_EN_LDO_DIVSXT] = EN_LDO_DIVSXT;
    wndId2Enum[ID_EN_LDO_LNA12] = EN_LDO_LNA12;
    wndId2Enum[ID_EN_LDO_LNA14] = EN_LDO_LNA14;
    wndId2Enum[ID_EN_LDO_MXRFE] = EN_LDO_MXRFE;
    wndId2Enum[ID_EN_LDO_RBB] = EN_LDO_RBB;
    wndId2Enum[ID_EN_LDO_RXBUF] = EN_LDO_RXBUF;
    wndId2Enum[ID_PD_LDO_SPIBUF] = PD_LDO_SPIBUF;
    wndId2Enum[ID_EN_LDO_TBB] = EN_LDO_TBB;
    wndId2Enum[ID_EN_LDO_TIA12] = EN_LDO_TIA12;
    wndId2Enum[ID_EN_LDO_TIA14] = EN_LDO_TIA14;
    wndId2Enum[ID_EN_LDO_TLOB] = EN_LDO_TLOB;
    wndId2Enum[ID_EN_LDO_TPAD] = EN_LDO_TPAD;
    wndId2Enum[ID_EN_LDO_TXBUF] = EN_LDO_TXBUF;
    wndId2Enum[ID_EN_LDO_VCOGN] = EN_LDO_VCOGN;
    wndId2Enum[ID_EN_LDO_VCOSXR] = EN_LDO_VCOSXR;
    wndId2Enum[ID_EN_LDO_VCOSXT] = EN_LDO_VCOSXT;
    wndId2Enum[ID_EN_LOADIMP_LDO_AFE] = EN_LOADIMP_LDO_AFE;
    wndId2Enum[ID_EN_LOADIMP_LDO_CPGN] = EN_LOADIMP_LDO_CPGN;
    wndId2Enum[ID_EN_LOADIMP_LDO_CPSXR] = EN_LOADIMP_LDO_CPSXR;
    wndId2Enum[ID_EN_LOADIMP_LDO_CPSXT] = EN_LOADIMP_LDO_CPSXT;
    wndId2Enum[ID_EN_LOADIMP_LDO_DIG] = EN_LOADIMP_LDO_DIG;
    wndId2Enum[ID_EN_LOADIMP_LDO_DIGGN] = EN_LOADIMP_LDO_DIGGN;
    wndId2Enum[ID_EN_LOADIMP_LDO_DIGIp1] = EN_LOADIMP_LDO_DIGIp1;
    wndId2Enum[ID_EN_LOADIMP_LDO_DIGIp2] = EN_LOADIMP_LDO_DIGIp2;
    wndId2Enum[ID_EN_LOADIMP_LDO_DIGSXR] = EN_LOADIMP_LDO_DIGSXR;
    wndId2Enum[ID_EN_LOADIMP_LDO_DIGSXT] = EN_LOADIMP_LDO_DIGSXT;
    wndId2Enum[ID_EN_LOADIMP_LDO_DIVGN] = EN_LOADIMP_LDO_DIVGN;
    wndId2Enum[ID_EN_LOADIMP_LDO_DIVSXR] = EN_LOADIMP_LDO_DIVSXR;
    wndId2Enum[ID_EN_LOADIMP_LDO_DIVSXT] = EN_LOADIMP_LDO_DIVSXT;
    wndId2Enum[ID_EN_LOADIMP_LDO_LNA12] = EN_LOADIMP_LDO_LNA12;
    wndId2Enum[ID_EN_LOADIMP_LDO_LNA14] = EN_LOADIMP_LDO_LNA14;
    wndId2Enum[ID_EN_LOADIMP_LDO_MXRFE] = EN_LOADIMP_LDO_MXRFE;
    wndId2Enum[ID_EN_LOADIMP_LDO_RBB] = EN_LOADIMP_LDO_RBB;
    wndId2Enum[ID_EN_LOADIMP_LDO_RXBUF] = EN_LOADIMP_LDO_RXBUF;
    wndId2Enum[ID_EN_LOADIMP_LDO_SPIBUF] = EN_LOADIMP_LDO_SPIBUF;
    wndId2Enum[ID_EN_LOADIMP_LDO_TBB] = EN_LOADIMP_LDO_TBB;
    wndId2Enum[ID_EN_LOADIMP_LDO_TIA12] = EN_LOADIMP_LDO_TIA12;
    wndId2Enum[ID_EN_LOADIMP_LDO_TIA14] = EN_LOADIMP_LDO_TIA14;
    wndId2Enum[ID_EN_LOADIMP_LDO_TLOB] = EN_LOADIMP_LDO_TLOB;
    wndId2Enum[ID_EN_LOADIMP_LDO_TPAD] = EN_LOADIMP_LDO_TPAD;
    wndId2Enum[ID_EN_LOADIMP_LDO_TXBUF] = EN_LOADIMP_LDO_TXBUF;
    wndId2Enum[ID_EN_LOADIMP_LDO_VCOGN] = EN_LOADIMP_LDO_VCOGN;
    wndId2Enum[ID_EN_LOADIMP_LDO_VCOSXR] = EN_LOADIMP_LDO_VCOSXR;
    wndId2Enum[ID_EN_LOADIMP_LDO_VCOSXT] = EN_LOADIMP_LDO_VCOSXT;
    wndId2Enum[ID_RDIV_AFE] = RDIV_AFE;
    wndId2Enum[ID_RDIV_CPGN] = RDIV_CPGN;
    wndId2Enum[ID_RDIV_CPSXR] = RDIV_CPSXR;
    wndId2Enum[ID_RDIV_CPSXT] = RDIV_CPSXT;
    wndId2Enum[ID_RDIV_DIG] = RDIV_DIG;
    wndId2Enum[ID_RDIV_DIGGN] = RDIV_DIGGN;
    wndId2Enum[ID_RDIV_DIGIp1] = RDIV_DIGIp1;
    wndId2Enum[ID_RDIV_DIGIp2] = RDIV_DIGIp2;
    wndId2Enum[ID_RDIV_DIGSXR] = RDIV_DIGSXR;
    wndId2Enum[ID_RDIV_DIGSXT] = RDIV_DIGSXT;
    wndId2Enum[ID_RDIV_DIVGN] = RDIV_DIVGN;
    wndId2Enum[ID_RDIV_DIVSXR] = RDIV_DIVSXR;
    wndId2Enum[ID_RDIV_DIVSXT] = RDIV_DIVSXT;
    wndId2Enum[ID_RDIV_LNA12] = RDIV_LNA12;
    wndId2Enum[ID_RDIV_LNA14] = RDIV_LNA14;
    wndId2Enum[ID_RDIV_MXRFE] = RDIV_MXRFE;
    wndId2Enum[ID_RDIV_RBB] = RDIV_RBB;
    wndId2Enum[ID_RDIV_RXBUF] = RDIV_RXBUF;
    wndId2Enum[ID_RDIV_SPIBUF] = RDIV_SPIBUF;
    wndId2Enum[ID_RDIV_TBB] = RDIV_TBB;
    wndId2Enum[ID_RDIV_TIA12] = RDIV_TIA12;
    wndId2Enum[ID_RDIV_TIA14] = RDIV_TIA14;
    wndId2Enum[ID_RDIV_TLOB] = RDIV_TLOB;
    wndId2Enum[ID_RDIV_TPAD] = RDIV_TPAD;
    wndId2Enum[ID_RDIV_TXBUF] = RDIV_TXBUF;
    wndId2Enum[ID_RDIV_VCOGN] = RDIV_VCOGN;
    wndId2Enum[ID_RDIV_VCOSXR] = RDIV_VCOSXR;
    wndId2Enum[ID_RDIV_VCOSXT] = RDIV_VCOSXT;
    wndId2Enum[ID_SPDUP_LDO_AFE] = SPDUP_LDO_AFE;
    wndId2Enum[ID_SPDUP_LDO_CPGN] = SPDUP_LDO_CPGN;
    wndId2Enum[ID_SPDUP_LDO_CPSXR] = SPDUP_LDO_CPSXR;
    wndId2Enum[ID_SPDUP_LDO_CPSXT] = SPDUP_LDO_CPSXT;
    wndId2Enum[ID_SPDUP_LDO_DIG] = SPDUP_LDO_DIG;
    wndId2Enum[ID_SPDUP_LDO_DIGGN] = SPDUP_LDO_DIGGN;
    wndId2Enum[ID_SPDUP_LDO_DIGIp1] = SPDUP_LDO_DIGIp1;
    wndId2Enum[ID_SPDUP_LDO_DIGIp2] = SPDUP_LDO_DIGIp2;
    wndId2Enum[ID_SPDUP_LDO_DIGSXR] = SPDUP_LDO_DIGSXR;
    wndId2Enum[ID_SPDUP_LDO_DIGSXT] = SPDUP_LDO_DIGSXT;
    wndId2Enum[ID_SPDUP_LDO_DIVGN] = SPDUP_LDO_DIVGN;
    wndId2Enum[ID_SPDUP_LDO_DIVSXR] = SPDUP_LDO_DIVSXR;
    wndId2Enum[ID_SPDUP_LDO_DIVSXT] = SPDUP_LDO_DIVSXT;
    wndId2Enum[ID_SPDUP_LDO_LNA12] = SPDUP_LDO_LNA12;
    wndId2Enum[ID_SPDUP_LDO_LNA14] = SPDUP_LDO_LNA14;
    wndId2Enum[ID_SPDUP_LDO_MXRFE] = SPDUP_LDO_MXRFE;
    wndId2Enum[ID_SPDUP_LDO_RBB] = SPDUP_LDO_RBB;
    wndId2Enum[ID_SPDUP_LDO_RXBUF] = SPDUP_LDO_RXBUF;
    wndId2Enum[ID_SPDUP_LDO_SPIBUF] = SPDUP_LDO_SPIBUF;
    wndId2Enum[ID_SPDUP_LDO_TBB] = SPDUP_LDO_TBB;
    wndId2Enum[ID_SPDUP_LDO_TIA12] = SPDUP_LDO_TIA12;
    wndId2Enum[ID_SPDUP_LDO_TIA14] = SPDUP_LDO_TIA14;
    wndId2Enum[ID_SPDUP_LDO_TLOB] = SPDUP_LDO_TLOB;
    wndId2Enum[ID_SPDUP_LDO_TPAD] = SPDUP_LDO_TPAD;
    wndId2Enum[ID_SPDUP_LDO_TXBUF] = SPDUP_LDO_TXBUF;
    wndId2Enum[ID_SPDUP_LDO_VCOGN] = SPDUP_LDO_VCOGN;
    wndId2Enum[ID_SPDUP_LDO_VCOSXR] = SPDUP_LDO_VCOSXR;
    wndId2Enum[ID_SPDUP_LDO_VCOSXT] = SPDUP_LDO_VCOSXT;
}

pnlLDO::pnlLDO(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int style, wxString name)
{
    lmsControl = NULL;
    BuildContent(parent,id,pos,size);
    AssignEnumsToIds();
}
void pnlLDO::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
//(*Initialize(pnlLDO)
wxStaticBoxSizer* StaticBoxSizer2;
wxFlexGridSizer* Bias5Sizer;
wxStaticBoxSizer* StaticBoxSizer12;
wxStaticBoxSizer* StaticBoxSizer4;
wxFlexGridSizer* FlexGridSizer3;
wxFlexGridSizer* Powercontrols1Sizer;
wxStaticBoxSizer* ShortnoisefilterresistorSizer;
wxStaticBoxSizer* StaticBoxSizer9;
wxFlexGridSizer* Outputvoltage2Sizer;
wxStaticBoxSizer* StaticBoxSizer7;
wxFlexGridSizer* Bypass3Sizer;
wxStaticBoxSizer* StaticBoxSizer13;
wxFlexGridSizer* Shortnoisefilterresistor4Sizer;
wxStaticBoxSizer* StaticBoxSizer10;
wxStaticBoxSizer* StaticBoxSizer8;
wxStaticBoxSizer* StaticBoxSizer3;
wxStaticBoxSizer* StaticBoxSizer6;
wxStaticBoxSizer* StaticBoxSizer11;
wxStaticBoxSizer* BiasSizer;
wxStaticBoxSizer* OutputvoltageSizer;
wxStaticBoxSizer* StaticBoxSizer1;
wxFlexGridSizer* FlexGridSizer1;
wxStaticBoxSizer* StaticBoxSizer5;
wxStaticBoxSizer* PowercontrolsSizer;

Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
FlexGridSizer1 = new wxFlexGridSizer(0, 4, 0, 0);
Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
FlexGridSizer4 = new wxFlexGridSizer(0, 4, 0, 0);
PowercontrolsSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel3, _("Power controls"));
Powercontrols1Sizer = new wxFlexGridSizer(0, 2, 2, 5);
chkEN_G_LDOP = new wxCheckBox(Panel3, ID_EN_G_LDOP, _("Enable LDO digital module"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_G_LDOP"));
chkEN_G_LDOP->SetValue(false);
chkEN_G_LDOP->SetToolTip(_("Enable control for all the LDO power downs"));
Powercontrols1Sizer->Add(chkEN_G_LDOP, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_G_LDO = new wxCheckBox(Panel3, ID_EN_G_LDO, _("Enable LDO analog module"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_G_LDO"));
chkEN_G_LDO->SetValue(false);
chkEN_G_LDO->SetToolTip(_("Enable control for all the LDO power downs"));
Powercontrols1Sizer->Add(chkEN_G_LDO, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, Panel3, _("CLKGEN"));
chkEN_LDO_DIVGN = new wxCheckBox(Panel3, ID_EN_LDO_DIVGN, _("EN_LDO_DIVGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_DIVGN"));
chkEN_LDO_DIVGN->SetValue(false);
chkEN_LDO_DIVGN->SetToolTip(_("Enables the LDO"));
StaticBoxSizer1->Add(chkEN_LDO_DIVGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_DIGGN = new wxCheckBox(Panel3, ID_EN_LDO_DIGGN, _("EN_LDO_DIGGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_DIGGN"));
chkEN_LDO_DIGGN->SetValue(false);
chkEN_LDO_DIGGN->SetToolTip(_("Enables the LDO"));
StaticBoxSizer1->Add(chkEN_LDO_DIGGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_CPGN = new wxCheckBox(Panel3, ID_EN_LDO_CPGN, _("EN_LDO_CPGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_CPGN"));
chkEN_LDO_CPGN->SetValue(false);
chkEN_LDO_CPGN->SetToolTip(_("Enables the LDO"));
StaticBoxSizer1->Add(chkEN_LDO_CPGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_VCOGN = new wxCheckBox(Panel3, ID_EN_LDO_VCOGN, _("EN_LDO_VCOGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_VCOGN"));
chkEN_LDO_VCOGN->SetValue(false);
chkEN_LDO_VCOGN->SetToolTip(_("Enables the LDO"));
StaticBoxSizer1->Add(chkEN_LDO_VCOGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, Panel3, _("RX RF"));
chkEN_LDO_MXRFE = new wxCheckBox(Panel3, ID_EN_LDO_MXRFE, _("EN_LDO_MXRFE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_MXRFE"));
chkEN_LDO_MXRFE->SetValue(false);
chkEN_LDO_MXRFE->SetToolTip(_("Enables the LDO"));
StaticBoxSizer2->Add(chkEN_LDO_MXRFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_LNA14 = new wxCheckBox(Panel3, ID_EN_LDO_LNA14, _("EN_LDO_LNA14"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_LNA14"));
chkEN_LDO_LNA14->SetValue(false);
chkEN_LDO_LNA14->SetToolTip(_("Enables the LDO"));
StaticBoxSizer2->Add(chkEN_LDO_LNA14, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_LNA12 = new wxCheckBox(Panel3, ID_EN_LDO_LNA12, _("EN_LDO_LNA12"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_LNA12"));
chkEN_LDO_LNA12->SetValue(false);
chkEN_LDO_LNA12->SetToolTip(_("Enables the LDO"));
StaticBoxSizer2->Add(chkEN_LDO_LNA12, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_TIA14 = new wxCheckBox(Panel3, ID_EN_LDO_TIA14, _("EN_LDO_TIA14"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_TIA14"));
chkEN_LDO_TIA14->SetValue(false);
chkEN_LDO_TIA14->SetToolTip(_("Enables the LDO"));
StaticBoxSizer2->Add(chkEN_LDO_TIA14, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, Panel3, _("SX TX"));
chkEN_LDO_DIVSXT = new wxCheckBox(Panel3, ID_EN_LDO_DIVSXT, _("EN_LDO_DIVSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_DIVSXT"));
chkEN_LDO_DIVSXT->SetValue(false);
chkEN_LDO_DIVSXT->SetToolTip(_("Enables the LDO"));
StaticBoxSizer3->Add(chkEN_LDO_DIVSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_DIGSXT = new wxCheckBox(Panel3, ID_EN_LDO_DIGSXT, _("EN_LDO_DIGSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_DIGSXT"));
chkEN_LDO_DIGSXT->SetValue(false);
chkEN_LDO_DIGSXT->SetToolTip(_("Enables the LDO"));
StaticBoxSizer3->Add(chkEN_LDO_DIGSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_CPSXT = new wxCheckBox(Panel3, ID_EN_LDO_CPSXT, _("EN_LDO_CPSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_CPSXT"));
chkEN_LDO_CPSXT->SetValue(false);
chkEN_LDO_CPSXT->SetToolTip(_("Enables the LDO"));
StaticBoxSizer3->Add(chkEN_LDO_CPSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_VCOSXT = new wxCheckBox(Panel3, ID_EN_LDO_VCOSXT, _("EN_LDO_VCOSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_VCOSXT"));
chkEN_LDO_VCOSXT->SetValue(false);
chkEN_LDO_VCOSXT->SetToolTip(_("Enables the LDO"));
StaticBoxSizer3->Add(chkEN_LDO_VCOSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer4 = new wxStaticBoxSizer(wxVERTICAL, Panel3, _("SX RX"));
chkEN_LDO_DIVSXR = new wxCheckBox(Panel3, ID_EN_LDO_DIVSXR, _("EN_LDO_DIVSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_DIVSXR"));
chkEN_LDO_DIVSXR->SetValue(false);
chkEN_LDO_DIVSXR->SetToolTip(_("Enables the LDO"));
StaticBoxSizer4->Add(chkEN_LDO_DIVSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_DIGSXR = new wxCheckBox(Panel3, ID_EN_LDO_DIGSXR, _("EN_LDO_DIGSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_DIGSXR"));
chkEN_LDO_DIGSXR->SetValue(false);
chkEN_LDO_DIGSXR->SetToolTip(_("Enables the LDO"));
StaticBoxSizer4->Add(chkEN_LDO_DIGSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_CPSXR = new wxCheckBox(Panel3, ID_EN_LDO_CPSXR, _("EN_LDO_CPSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_CPSXR"));
chkEN_LDO_CPSXR->SetValue(false);
chkEN_LDO_CPSXR->SetToolTip(_("Enables the LDO"));
StaticBoxSizer4->Add(chkEN_LDO_CPSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_VCOSXR = new wxCheckBox(Panel3, ID_EN_LDO_VCOSXR, _("EN_LDO_VCOSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_VCOSXR"));
chkEN_LDO_VCOSXR->SetValue(false);
chkEN_LDO_VCOSXR->SetToolTip(_("Enables the LDO"));
StaticBoxSizer4->Add(chkEN_LDO_VCOSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer4, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer5 = new wxStaticBoxSizer(wxVERTICAL, Panel3, _("Digital Blocks"));
chkPD_LDO_DIGIp1 = new wxCheckBox(Panel3, ID_PD_LDO_DIGIp1, _("PD_LDO_DIGIp1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_LDO_DIGIp1"));
chkPD_LDO_DIGIp1->SetValue(false);
chkPD_LDO_DIGIp1->SetToolTip(_("Enables the LDO"));
StaticBoxSizer5->Add(chkPD_LDO_DIGIp1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkPD_LDO_DIGIp2 = new wxCheckBox(Panel3, ID_PD_LDO_DIGIp2, _("PD_LDO_DIGIp2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_LDO_DIGIp2"));
chkPD_LDO_DIGIp2->SetValue(false);
chkPD_LDO_DIGIp2->SetToolTip(_("Enables the LDO"));
StaticBoxSizer5->Add(chkPD_LDO_DIGIp2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer5, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer6 = new wxStaticBoxSizer(wxVERTICAL, Panel3, _("XBUF"));
chkEN_LDO_TXBUF = new wxCheckBox(Panel3, ID_EN_LDO_TXBUF, _("EN_LDO_TXBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_TXBUF"));
chkEN_LDO_TXBUF->SetValue(false);
chkEN_LDO_TXBUF->SetToolTip(_("Enables the LDO"));
StaticBoxSizer6->Add(chkEN_LDO_TXBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_RXBUF = new wxCheckBox(Panel3, ID_EN_LDO_RXBUF, _("EN_LDO_RXBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_RXBUF"));
chkEN_LDO_RXBUF->SetValue(false);
chkEN_LDO_RXBUF->SetToolTip(_("Enables the LDO"));
StaticBoxSizer6->Add(chkEN_LDO_RXBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer6, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, Panel3, _("AFE"));
chkEN_LDO_AFE = new wxCheckBox(Panel3, ID_EN_LDO_AFE, _("EN_LDO_AFE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_AFE"));
chkEN_LDO_AFE->SetValue(false);
chkEN_LDO_AFE->SetToolTip(_("Enables the LDO"));
StaticBoxSizer7->Add(chkEN_LDO_AFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer7, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer8 = new wxStaticBoxSizer(wxHORIZONTAL, Panel3, _("SPI Buffer to analog blocks"));
chkPD_LDO_SPIBUF = new wxCheckBox(Panel3, ID_PD_LDO_SPIBUF, _("PD_LDO_SPIBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_PD_LDO_SPIBUF"));
chkPD_LDO_SPIBUF->SetValue(false);
chkPD_LDO_SPIBUF->SetToolTip(_("Enables the LDO"));
StaticBoxSizer8->Add(chkPD_LDO_SPIBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer8, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer9 = new wxStaticBoxSizer(wxHORIZONTAL, Panel3, _("Tx BB"));
chkEN_LDO_TBB = new wxCheckBox(Panel3, ID_EN_LDO_TBB, _("EN_LDO_TBB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_TBB"));
chkEN_LDO_TBB->SetValue(false);
chkEN_LDO_TBB->SetToolTip(_("Enables the LDO"));
StaticBoxSizer9->Add(chkEN_LDO_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer9, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer10 = new wxStaticBoxSizer(wxHORIZONTAL, Panel3, _("Rx RBB"));
chkEN_LDO_RBB = new wxCheckBox(Panel3, ID_EN_LDO_RBB, _("EN_LDO_RBB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_RBB"));
chkEN_LDO_RBB->SetValue(false);
chkEN_LDO_RBB->SetToolTip(_("Enables the LDO"));
StaticBoxSizer10->Add(chkEN_LDO_RBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer10, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer11 = new wxStaticBoxSizer(wxHORIZONTAL, Panel3, _("Rx RF+ Rx RBB"));
chkEN_LDO_TIA12 = new wxCheckBox(Panel3, ID_EN_LDO_TIA12, _("EN_LDO_TIA12"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_TIA12"));
chkEN_LDO_TIA12->SetValue(false);
chkEN_LDO_TIA12->SetToolTip(_("Enables the LDO"));
StaticBoxSizer11->Add(chkEN_LDO_TIA12, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer11, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer12 = new wxStaticBoxSizer(wxVERTICAL, Panel3, _("Tx RF"));
chkEN_LDO_TPAD = new wxCheckBox(Panel3, ID_EN_LDO_TPAD, _("EN_LDO_TPAD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_TPAD"));
chkEN_LDO_TPAD->SetValue(false);
chkEN_LDO_TPAD->SetToolTip(_("Enables the LDO"));
StaticBoxSizer12->Add(chkEN_LDO_TPAD, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LDO_TLOB = new wxCheckBox(Panel3, ID_EN_LDO_TLOB, _("EN_LDO_TLOB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_TLOB"));
chkEN_LDO_TLOB->SetValue(false);
chkEN_LDO_TLOB->SetToolTip(_("Enables the LDO"));
StaticBoxSizer12->Add(chkEN_LDO_TLOB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer12, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
StaticBoxSizer13 = new wxStaticBoxSizer(wxHORIZONTAL, Panel3, _("Misc"));
chkEN_LDO_DIG = new wxCheckBox(Panel3, ID_EN_LDO_DIG, _("EN_LDO_DIG"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LDO_DIG"));
chkEN_LDO_DIG->SetValue(false);
chkEN_LDO_DIG->SetToolTip(_("Enables the LDO"));
StaticBoxSizer13->Add(chkEN_LDO_DIG, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
Powercontrols1Sizer->Add(StaticBoxSizer13, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
PowercontrolsSizer->Add(Powercontrols1Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 0);
FlexGridSizer4->Add(PowercontrolsSizer, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
BypassSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel3, _("Bypass"));
Bypass3Sizer = new wxFlexGridSizer(0, 1, 0, 0);
chkBYP_LDO_TBB = new wxCheckBox(Panel3, ID_BYP_LDO_TBB, _("BYP_LDO_TBB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_TBB"));
chkBYP_LDO_TBB->SetValue(false);
chkBYP_LDO_TBB->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_TIA12 = new wxCheckBox(Panel3, ID_BYP_LDO_TIA12, _("BYP_LDO_TIA12"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_TIA12"));
chkBYP_LDO_TIA12->SetValue(false);
chkBYP_LDO_TIA12->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_TIA12, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_TIA14 = new wxCheckBox(Panel3, ID_BYP_LDO_TIA14, _("BYP_LDO_TIA14"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_TIA14"));
chkBYP_LDO_TIA14->SetValue(false);
chkBYP_LDO_TIA14->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_TIA14, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_TLOB = new wxCheckBox(Panel3, ID_BYP_LDO_TLOB, _("BYP_LDO_TLOB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_TLOB"));
chkBYP_LDO_TLOB->SetValue(false);
chkBYP_LDO_TLOB->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_TLOB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_TPAD = new wxCheckBox(Panel3, ID_BYP_LDO_TPAD, _("BYP_LDO_TPAD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_TPAD"));
chkBYP_LDO_TPAD->SetValue(false);
chkBYP_LDO_TPAD->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_TPAD, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_TXBUF = new wxCheckBox(Panel3, ID_BYP_LDO_TXBUF, _("BYP_LDO_TXBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_TXBUF"));
chkBYP_LDO_TXBUF->SetValue(false);
chkBYP_LDO_TXBUF->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_TXBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_VCOGN = new wxCheckBox(Panel3, ID_BYP_LDO_VCOGN, _("BYP_LDO_VCOGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_VCOGN"));
chkBYP_LDO_VCOGN->SetValue(false);
chkBYP_LDO_VCOGN->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_VCOGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_VCOSXR = new wxCheckBox(Panel3, ID_BYP_LDO_VCOSXR, _("BYP_LDO_VCOSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_VCOSXR"));
chkBYP_LDO_VCOSXR->SetValue(false);
chkBYP_LDO_VCOSXR->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_VCOSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_VCOSXT = new wxCheckBox(Panel3, ID_BYP_LDO_VCOSXT, _("BYP_LDO_VCOSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_VCOSXT"));
chkBYP_LDO_VCOSXT->SetValue(false);
chkBYP_LDO_VCOSXT->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_VCOSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_AFE = new wxCheckBox(Panel3, ID_BYP_LDO_AFE, _("BYP_LDO_AFE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_AFE"));
chkBYP_LDO_AFE->SetValue(false);
chkBYP_LDO_AFE->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_AFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_CPGN = new wxCheckBox(Panel3, ID_BYP_LDO_CPGN, _("BYP_LDO_CPGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_CPGN"));
chkBYP_LDO_CPGN->SetValue(false);
chkBYP_LDO_CPGN->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_CPGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_CPSXR = new wxCheckBox(Panel3, ID_BYP_LDO_CPSXR, _("BYP_LDO_CPSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_CPSXR"));
chkBYP_LDO_CPSXR->SetValue(false);
chkBYP_LDO_CPSXR->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_CPSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_CPSXT = new wxCheckBox(Panel3, ID_BYP_LDO_CPSXT, _("BYP_LDO_CPSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_CPSXT"));
chkBYP_LDO_CPSXT->SetValue(false);
chkBYP_LDO_CPSXT->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_CPSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_DIG = new wxCheckBox(Panel3, ID_BYP_LDO_DIG, _("BYP_LDO_DIG"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_DIG"));
chkBYP_LDO_DIG->SetValue(false);
chkBYP_LDO_DIG->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_DIG, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_DIGGN = new wxCheckBox(Panel3, ID_BYP_LDO_DIGGN, _("BYP_LDO_DIGGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_DIGGN"));
chkBYP_LDO_DIGGN->SetValue(false);
chkBYP_LDO_DIGGN->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_DIGGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_DIGSXR = new wxCheckBox(Panel3, ID_BYP_LDO_DIGSXR, _("BYP_LDO_DIGSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_DIGSXR"));
chkBYP_LDO_DIGSXR->SetValue(false);
chkBYP_LDO_DIGSXR->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_DIGSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_DIGSXT = new wxCheckBox(Panel3, ID_BYP_LDO_DIGSXT, _("BYP_LDO_DIGSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_DIGSXT"));
chkBYP_LDO_DIGSXT->SetValue(false);
chkBYP_LDO_DIGSXT->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_DIGSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_DIVGN = new wxCheckBox(Panel3, ID_BYP_LDO_DIVGN, _("BYP_LDO_DIVGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_DIVGN"));
chkBYP_LDO_DIVGN->SetValue(false);
chkBYP_LDO_DIVGN->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_DIVGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_DIVSXR = new wxCheckBox(Panel3, ID_BYP_LDO_DIVSXR, _("BYP_LDO_DIVSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_DIVSXR"));
chkBYP_LDO_DIVSXR->SetValue(false);
chkBYP_LDO_DIVSXR->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_DIVSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_DIVSXT = new wxCheckBox(Panel3, ID_BYP_LDO_DIVSXT, _("BYP_LDO_DIVSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_DIVSXT"));
chkBYP_LDO_DIVSXT->SetValue(false);
chkBYP_LDO_DIVSXT->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_DIVSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_LNA12 = new wxCheckBox(Panel3, ID_BYP_LDO_LNA12, _("BYP_LDO_LNA12"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_LNA12"));
chkBYP_LDO_LNA12->SetValue(false);
chkBYP_LDO_LNA12->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_LNA12, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_LNA14 = new wxCheckBox(Panel3, ID_BYP_LDO_LNA14, _("BYP_LDO_LNA14"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_LNA14"));
chkBYP_LDO_LNA14->SetValue(false);
chkBYP_LDO_LNA14->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_LNA14, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_MXRFE = new wxCheckBox(Panel3, ID_BYP_LDO_MXRFE, _("BYP_LDO_MXRFE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_MXRFE"));
chkBYP_LDO_MXRFE->SetValue(false);
chkBYP_LDO_MXRFE->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_MXRFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_RBB = new wxCheckBox(Panel3, ID_BYP_LDO_RBB, _("BYP_LDO_RBB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_RBB"));
chkBYP_LDO_RBB->SetValue(false);
chkBYP_LDO_RBB->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_RBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_RXBUF = new wxCheckBox(Panel3, ID_BYP_LDO_RXBUF, _("BYP_LDO_RXBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_RXBUF"));
chkBYP_LDO_RXBUF->SetValue(false);
chkBYP_LDO_RXBUF->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_RXBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_SPIBUF = new wxCheckBox(Panel3, ID_BYP_LDO_SPIBUF, _("BYP_LDO_SPIBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_SPIBUF"));
chkBYP_LDO_SPIBUF->SetValue(false);
chkBYP_LDO_SPIBUF->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_SPIBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_DIGIp2 = new wxCheckBox(Panel3, ID_BYP_LDO_DIGIp2, _("BYP_LDO_DIGIp2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_DIGIp2"));
chkBYP_LDO_DIGIp2->SetValue(false);
chkBYP_LDO_DIGIp2->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_DIGIp2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkBYP_LDO_DIGIp1 = new wxCheckBox(Panel3, ID_BYP_LDO_DIGIp1, _("BYP_LDO_DIGIp1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BYP_LDO_DIGIp1"));
chkBYP_LDO_DIGIp1->SetValue(false);
chkBYP_LDO_DIGIp1->SetToolTip(_("Bypass signal for the LDO"));
Bypass3Sizer->Add(chkBYP_LDO_DIGIp1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
BypassSizer->Add(Bypass3Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer4->Add(BypassSizer, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
ShortnoisefilterresistorSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel3, _("Short noise filter resistor"));
Shortnoisefilterresistor4Sizer = new wxFlexGridSizer(0, 1, 0, 0);
chkSPDUP_LDO_TBB = new wxCheckBox(Panel3, ID_SPDUP_LDO_TBB, _("SPDUP_LDO_TBB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_TBB"));
chkSPDUP_LDO_TBB->SetValue(false);
chkSPDUP_LDO_TBB->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_TIA12 = new wxCheckBox(Panel3, ID_SPDUP_LDO_TIA12, _("SPDUP_LDO_TIA12"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_TIA12"));
chkSPDUP_LDO_TIA12->SetValue(false);
chkSPDUP_LDO_TIA12->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_TIA12, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_TIA14 = new wxCheckBox(Panel3, ID_SPDUP_LDO_TIA14, _("SPDUP_LDO_TIA14"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_TIA14"));
chkSPDUP_LDO_TIA14->SetValue(false);
chkSPDUP_LDO_TIA14->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_TIA14, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_TLOB = new wxCheckBox(Panel3, ID_SPDUP_LDO_TLOB, _("SPDUP_LDO_TLOB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_TLOB"));
chkSPDUP_LDO_TLOB->SetValue(false);
chkSPDUP_LDO_TLOB->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_TLOB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_TPAD = new wxCheckBox(Panel3, ID_SPDUP_LDO_TPAD, _("SPDUP_LDO_TPAD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_TPAD"));
chkSPDUP_LDO_TPAD->SetValue(false);
chkSPDUP_LDO_TPAD->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_TPAD, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_TXBUF = new wxCheckBox(Panel3, ID_SPDUP_LDO_TXBUF, _("SPDUP_LDO_TXBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_TXBUF"));
chkSPDUP_LDO_TXBUF->SetValue(false);
chkSPDUP_LDO_TXBUF->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_TXBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_VCOGN = new wxCheckBox(Panel3, ID_SPDUP_LDO_VCOGN, _("SPDUP_LDO_VCOGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_VCOGN"));
chkSPDUP_LDO_VCOGN->SetValue(false);
chkSPDUP_LDO_VCOGN->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_VCOGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_DIVSXR = new wxCheckBox(Panel3, ID_SPDUP_LDO_DIVSXR, _("SPDUP_LDO_DIVSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_DIVSXR"));
chkSPDUP_LDO_DIVSXR->SetValue(false);
chkSPDUP_LDO_DIVSXR->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_DIVSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_DIVSXT = new wxCheckBox(Panel3, ID_SPDUP_LDO_DIVSXT, _("SPDUP_LDO_DIVSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_DIVSXT"));
chkSPDUP_LDO_DIVSXT->SetValue(false);
chkSPDUP_LDO_DIVSXT->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_DIVSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_AFE = new wxCheckBox(Panel3, ID_SPDUP_LDO_AFE, _("SPDUP_LDO_AFE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_AFE"));
chkSPDUP_LDO_AFE->SetValue(false);
chkSPDUP_LDO_AFE->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_AFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_CPGN = new wxCheckBox(Panel3, ID_SPDUP_LDO_CPGN, _("SPDUP_LDO_CPGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_CPGN"));
chkSPDUP_LDO_CPGN->SetValue(false);
chkSPDUP_LDO_CPGN->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_CPGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_VCOSXR = new wxCheckBox(Panel3, ID_SPDUP_LDO_VCOSXR, _("SPDUP_LDO_VCOSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_VCOSXR"));
chkSPDUP_LDO_VCOSXR->SetValue(false);
chkSPDUP_LDO_VCOSXR->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_VCOSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_VCOSXT = new wxCheckBox(Panel3, ID_SPDUP_LDO_VCOSXT, _("SPDUP_LDO_VCOSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_VCOSXT"));
chkSPDUP_LDO_VCOSXT->SetValue(false);
chkSPDUP_LDO_VCOSXT->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_VCOSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_DIG = new wxCheckBox(Panel3, ID_SPDUP_LDO_DIG, _("SPDUP_LDO_DIG"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_DIG"));
chkSPDUP_LDO_DIG->SetValue(false);
chkSPDUP_LDO_DIG->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_DIG, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_DIGGN = new wxCheckBox(Panel3, ID_SPDUP_LDO_DIGGN, _("SPDUP_LDO_DIGGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_DIGGN"));
chkSPDUP_LDO_DIGGN->SetValue(false);
chkSPDUP_LDO_DIGGN->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_DIGGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_DIGSXR = new wxCheckBox(Panel3, ID_SPDUP_LDO_DIGSXR, _("SPDUP_LDO_DIGSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_DIGSXR"));
chkSPDUP_LDO_DIGSXR->SetValue(false);
chkSPDUP_LDO_DIGSXR->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_DIGSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_DIGSXT = new wxCheckBox(Panel3, ID_SPDUP_LDO_DIGSXT, _("SPDUP_LDO_DIGSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_DIGSXT"));
chkSPDUP_LDO_DIGSXT->SetValue(false);
chkSPDUP_LDO_DIGSXT->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_DIGSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_DIVGN = new wxCheckBox(Panel3, ID_SPDUP_LDO_DIVGN, _("SPDUP_LDO_DIVGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_DIVGN"));
chkSPDUP_LDO_DIVGN->SetValue(false);
chkSPDUP_LDO_DIVGN->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_DIVGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_CPSXR = new wxCheckBox(Panel3, ID_SPDUP_LDO_CPSXR, _("SPDUP_LDO_CPSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_CPSXR"));
chkSPDUP_LDO_CPSXR->SetValue(false);
chkSPDUP_LDO_CPSXR->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_CPSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_CPSXT = new wxCheckBox(Panel3, ID_SPDUP_LDO_CPSXT, _("SPDUP_LDO_CPSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_CPSXT"));
chkSPDUP_LDO_CPSXT->SetValue(false);
chkSPDUP_LDO_CPSXT->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_CPSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_LNA12 = new wxCheckBox(Panel3, ID_SPDUP_LDO_LNA12, _("SPDUP_LDO_LNA12"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_LNA12"));
chkSPDUP_LDO_LNA12->SetValue(false);
chkSPDUP_LDO_LNA12->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_LNA12, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_LNA14 = new wxCheckBox(Panel3, ID_SPDUP_LDO_LNA14, _("SPDUP_LDO_LNA14"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_LNA14"));
chkSPDUP_LDO_LNA14->SetValue(false);
chkSPDUP_LDO_LNA14->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_LNA14, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_MXRFE = new wxCheckBox(Panel3, ID_SPDUP_LDO_MXRFE, _("SPDUP_LDO_MXRFE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_MXRFE"));
chkSPDUP_LDO_MXRFE->SetValue(false);
chkSPDUP_LDO_MXRFE->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_MXRFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_RBB = new wxCheckBox(Panel3, ID_SPDUP_LDO_RBB, _("SPDUP_LDO_RBB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_RBB"));
chkSPDUP_LDO_RBB->SetValue(false);
chkSPDUP_LDO_RBB->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_RBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_RXBUF = new wxCheckBox(Panel3, ID_SPDUP_LDO_RXBUF, _("SPDUP_LDO_RXBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_RXBUF"));
chkSPDUP_LDO_RXBUF->SetValue(false);
chkSPDUP_LDO_RXBUF->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_RXBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_SPIBUF = new wxCheckBox(Panel3, ID_SPDUP_LDO_SPIBUF, _("SPDUP_LDO_SPIBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_SPIBUF"));
chkSPDUP_LDO_SPIBUF->SetValue(false);
chkSPDUP_LDO_SPIBUF->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_SPIBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_DIGIp2 = new wxCheckBox(Panel3, ID_SPDUP_LDO_DIGIp2, _("SPDUP_LDO_DIGIp2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_DIGIp2"));
chkSPDUP_LDO_DIGIp2->SetValue(false);
chkSPDUP_LDO_DIGIp2->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_DIGIp2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkSPDUP_LDO_DIGIp1 = new wxCheckBox(Panel3, ID_SPDUP_LDO_DIGIp1, _("SPDUP_LDO_DIGIp1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SPDUP_LDO_DIGIp1"));
chkSPDUP_LDO_DIGIp1->SetValue(false);
chkSPDUP_LDO_DIGIp1->SetToolTip(_("Short the noise filter resistor to speed up the settling time"));
Shortnoisefilterresistor4Sizer->Add(chkSPDUP_LDO_DIGIp1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
ShortnoisefilterresistorSizer->Add(Shortnoisefilterresistor4Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer4->Add(ShortnoisefilterresistorSizer, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
BiasSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel3, _("Bias"));
Bias5Sizer = new wxFlexGridSizer(0, 1, 0, 0);
chkEN_LOADIMP_LDO_TBB = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_TBB, _("EN_LOADIMP_LDO_TBB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_TBB"));
chkEN_LOADIMP_LDO_TBB->SetValue(false);
chkEN_LOADIMP_LDO_TBB->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_TIA12 = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_TIA12, _("EN_LOADIMP_LDO_TIA12"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_TIA12"));
chkEN_LOADIMP_LDO_TIA12->SetValue(false);
chkEN_LOADIMP_LDO_TIA12->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_TIA12, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_TIA14 = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_TIA14, _("EN_LOADIMP_LDO_TIA14"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_TIA14"));
chkEN_LOADIMP_LDO_TIA14->SetValue(false);
chkEN_LOADIMP_LDO_TIA14->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_TIA14, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_TLOB = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_TLOB, _("EN_LOADIMP_LDO_TLOB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_TLOB"));
chkEN_LOADIMP_LDO_TLOB->SetValue(false);
chkEN_LOADIMP_LDO_TLOB->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_TLOB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_TPAD = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_TPAD, _("EN_LOADIMP_LDO_TPAD"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_TPAD"));
chkEN_LOADIMP_LDO_TPAD->SetValue(false);
chkEN_LOADIMP_LDO_TPAD->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_TPAD, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_TXBUF = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_TXBUF, _("EN_LOADIMP_LDO_TXBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_TXBUF"));
chkEN_LOADIMP_LDO_TXBUF->SetValue(false);
chkEN_LOADIMP_LDO_TXBUF->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_TXBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_VCOGN = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_VCOGN, _("EN_LOADIMP_LDO_VCOGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_VCOGN"));
chkEN_LOADIMP_LDO_VCOGN->SetValue(false);
chkEN_LOADIMP_LDO_VCOGN->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_VCOGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_VCOSXR = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_VCOSXR, _("EN_LOADIMP_LDO_VCOSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_VCOSXR"));
chkEN_LOADIMP_LDO_VCOSXR->SetValue(false);
chkEN_LOADIMP_LDO_VCOSXR->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_VCOSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_VCOSXT = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_VCOSXT, _("EN_LOADIMP_LDO_VCOSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_VCOSXT"));
chkEN_LOADIMP_LDO_VCOSXT->SetValue(false);
chkEN_LOADIMP_LDO_VCOSXT->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_VCOSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_AFE = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_AFE, _("EN_LOADIMP_LDO_AFE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_AFE"));
chkEN_LOADIMP_LDO_AFE->SetValue(false);
chkEN_LOADIMP_LDO_AFE->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_AFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_CPGN = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_CPGN, _("EN_LOADIMP_LDO_CPGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_CPGN"));
chkEN_LOADIMP_LDO_CPGN->SetValue(false);
chkEN_LOADIMP_LDO_CPGN->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_CPGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_DIVSXR = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_DIVSXR, _("EN_LOADIMP_LDO_DIVSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_DIVSXR"));
chkEN_LOADIMP_LDO_DIVSXR->SetValue(false);
chkEN_LOADIMP_LDO_DIVSXR->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_DIVSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_DIVSXT = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_DIVSXT, _("EN_LOADIMP_LDO_DIVSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_DIVSXT"));
chkEN_LOADIMP_LDO_DIVSXT->SetValue(false);
chkEN_LOADIMP_LDO_DIVSXT->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_DIVSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_DIG = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_DIG, _("EN_LOADIMP_LDO_DIG"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_DIG"));
chkEN_LOADIMP_LDO_DIG->SetValue(false);
chkEN_LOADIMP_LDO_DIG->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_DIG, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_DIGGN = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_DIGGN, _("EN_LOADIMP_LDO_DIGGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_DIGGN"));
chkEN_LOADIMP_LDO_DIGGN->SetValue(false);
chkEN_LOADIMP_LDO_DIGGN->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_DIGGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_DIGSXR = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_DIGSXR, _("EN_LOADIMP_LDO_DIGSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_DIGSXR"));
chkEN_LOADIMP_LDO_DIGSXR->SetValue(false);
chkEN_LOADIMP_LDO_DIGSXR->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_DIGSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_DIGSXT = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_DIGSXT, _("EN_LOADIMP_LDO_DIGSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_DIGSXT"));
chkEN_LOADIMP_LDO_DIGSXT->SetValue(false);
chkEN_LOADIMP_LDO_DIGSXT->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_DIGSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_DIVGN = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_DIVGN, _("EN_LOADIMP_LDO_DIVGN"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_DIVGN"));
chkEN_LOADIMP_LDO_DIVGN->SetValue(false);
chkEN_LOADIMP_LDO_DIVGN->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_DIVGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_CPSXR = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_CPSXR, _("EN_LOADIMP_LDO_CPSXR"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_CPSXR"));
chkEN_LOADIMP_LDO_CPSXR->SetValue(false);
chkEN_LOADIMP_LDO_CPSXR->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_CPSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_CPSXT = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_CPSXT, _("EN_LOADIMP_LDO_CPSXT"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_CPSXT"));
chkEN_LOADIMP_LDO_CPSXT->SetValue(false);
chkEN_LOADIMP_LDO_CPSXT->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_CPSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_LNA12 = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_LNA12, _("EN_LOADIMP_LDO_LNA12"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_LNA12"));
chkEN_LOADIMP_LDO_LNA12->SetValue(false);
chkEN_LOADIMP_LDO_LNA12->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_LNA12, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_LNA14 = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_LNA14, _("EN_LOADIMP_LDO_LNA14"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_LNA14"));
chkEN_LOADIMP_LDO_LNA14->SetValue(false);
chkEN_LOADIMP_LDO_LNA14->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_LNA14, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_MXRFE = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_MXRFE, _("EN_LOADIMP_LDO_MXRFE"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_MXRFE"));
chkEN_LOADIMP_LDO_MXRFE->SetValue(false);
chkEN_LOADIMP_LDO_MXRFE->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_MXRFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_RBB = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_RBB, _("EN_LOADIMP_LDO_RBB"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_RBB"));
chkEN_LOADIMP_LDO_RBB->SetValue(false);
chkEN_LOADIMP_LDO_RBB->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_RBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_RXBUF = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_RXBUF, _("EN_LOADIMP_LDO_RXBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_RXBUF"));
chkEN_LOADIMP_LDO_RXBUF->SetValue(false);
chkEN_LOADIMP_LDO_RXBUF->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_RXBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_SPIBUF = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_SPIBUF, _("EN_LOADIMP_LDO_SPIBUF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_SPIBUF"));
chkEN_LOADIMP_LDO_SPIBUF->SetValue(false);
chkEN_LOADIMP_LDO_SPIBUF->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_SPIBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_DIGIp2 = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_DIGIp2, _("EN_LOADIMP_LDO_DIGIp2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_DIGIp2"));
chkEN_LOADIMP_LDO_DIGIp2->SetValue(false);
chkEN_LOADIMP_LDO_DIGIp2->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_DIGIp2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
chkEN_LOADIMP_LDO_DIGIp1 = new wxCheckBox(Panel3, ID_EN_LOADIMP_LDO_DIGIp1, _("EN_LOADIMP_LDO_DIGIp1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EN_LOADIMP_LDO_DIGIp1"));
chkEN_LOADIMP_LDO_DIGIp1->SetValue(false);
chkEN_LOADIMP_LDO_DIGIp1->SetToolTip(_("Enables the load dependent bias to optimize the load regulation"));
Bias5Sizer->Add(chkEN_LOADIMP_LDO_DIGIp1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
BiasSizer->Add(Bias5Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer4->Add(BiasSizer, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_TOP, 5);
Panel3->SetSizer(FlexGridSizer4);
FlexGridSizer4->Fit(Panel3);
FlexGridSizer4->SetSizeHints(Panel3);
Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
OutputvoltageSizer = new wxStaticBoxSizer(wxHORIZONTAL, Panel2, _("Output voltage"));
Outputvoltage2Sizer = new wxFlexGridSizer(0, 4, 0, 5);
StaticText0 = new wxStaticText(Panel2, ID_STATICTEXT1, _("RDIV_VCOSXR"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
Outputvoltage2Sizer->Add(StaticText0, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_VCOSXR = new ComboBoxMap(Panel2, ID_RDIV_VCOSXR, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_VCOSXR"));
cmbRDIV_VCOSXR->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_VCOSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText1 = new wxStaticText(Panel2, ID_STATICTEXT2, _("RDIV_VCOSXT"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
Outputvoltage2Sizer->Add(StaticText1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_VCOSXT = new ComboBoxMap(Panel2, ID_RDIV_VCOSXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_VCOSXT"));
cmbRDIV_VCOSXT->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_VCOSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText2 = new wxStaticText(Panel2, ID_STATICTEXT3, _("RDIV_TXBUF"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
Outputvoltage2Sizer->Add(StaticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_TXBUF = new ComboBoxMap(Panel2, ID_RDIV_TXBUF, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_TXBUF"));
cmbRDIV_TXBUF->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_TXBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText3 = new wxStaticText(Panel2, ID_STATICTEXT4, _("RDIV_VCOGN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
Outputvoltage2Sizer->Add(StaticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_VCOGN = new ComboBoxMap(Panel2, ID_RDIV_VCOGN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_VCOGN"));
cmbRDIV_VCOGN->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_VCOGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText4 = new wxStaticText(Panel2, ID_STATICTEXT5, _("RDIV_TLOB"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
Outputvoltage2Sizer->Add(StaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_TLOB = new ComboBoxMap(Panel2, ID_RDIV_TLOB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_TLOB"));
cmbRDIV_TLOB->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_TLOB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText5 = new wxStaticText(Panel2, ID_STATICTEXT6, _("RDIV_TPAD"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
Outputvoltage2Sizer->Add(StaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_TPAD = new ComboBoxMap(Panel2, ID_RDIV_TPAD, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_TPAD"));
cmbRDIV_TPAD->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_TPAD, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText6 = new wxStaticText(Panel2, ID_STATICTEXT7, _("RDIV_TIA12"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
Outputvoltage2Sizer->Add(StaticText6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_TIA12 = new ComboBoxMap(Panel2, ID_RDIV_TIA12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_TIA12"));
cmbRDIV_TIA12->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_TIA12, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText7 = new wxStaticText(Panel2, ID_STATICTEXT8, _("RDIV_TIA14"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
Outputvoltage2Sizer->Add(StaticText7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_TIA14 = new ComboBoxMap(Panel2, ID_RDIV_TIA14, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_TIA14"));
cmbRDIV_TIA14->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_TIA14, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText8 = new wxStaticText(Panel2, ID_STATICTEXT9, _("RDIV_RXBUF"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
Outputvoltage2Sizer->Add(StaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_RXBUF = new ComboBoxMap(Panel2, ID_RDIV_RXBUF, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_RXBUF"));
cmbRDIV_RXBUF->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_RXBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText9 = new wxStaticText(Panel2, ID_STATICTEXT10, _("RDIV_TBB"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
Outputvoltage2Sizer->Add(StaticText9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_TBB = new ComboBoxMap(Panel2, ID_RDIV_TBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_TBB"));
cmbRDIV_TBB->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_TBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText10 = new wxStaticText(Panel2, ID_STATICTEXT11, _("RDIV_MXRFE"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
Outputvoltage2Sizer->Add(StaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_MXRFE = new ComboBoxMap(Panel2, ID_RDIV_MXRFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_MXRFE"));
cmbRDIV_MXRFE->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_MXRFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText11 = new wxStaticText(Panel2, ID_STATICTEXT12, _("RDIV_RBB"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT12"));
Outputvoltage2Sizer->Add(StaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_RBB = new ComboBoxMap(Panel2, ID_RDIV_RBB, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_RBB"));
cmbRDIV_RBB->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_RBB, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText12 = new wxStaticText(Panel2, ID_STATICTEXT13, _("RDIV_LNA12"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT13"));
Outputvoltage2Sizer->Add(StaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_LNA12 = new ComboBoxMap(Panel2, ID_RDIV_LNA12, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_LNA12"));
cmbRDIV_LNA12->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_LNA12, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText13 = new wxStaticText(Panel2, ID_STATICTEXT14, _("RDIV_LNA14"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT14"));
Outputvoltage2Sizer->Add(StaticText13, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_LNA14 = new ComboBoxMap(Panel2, ID_RDIV_LNA14, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_LNA14"));
cmbRDIV_LNA14->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_LNA14, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText14 = new wxStaticText(Panel2, ID_STATICTEXT15, _("RDIV_DIVSXR"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
Outputvoltage2Sizer->Add(StaticText14, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_DIVSXR = new ComboBoxMap(Panel2, ID_RDIV_DIVSXR, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_DIVSXR"));
cmbRDIV_DIVSXR->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_DIVSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText15 = new wxStaticText(Panel2, ID_STATICTEXT16, _("RDIV_DIVSXT"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT16"));
Outputvoltage2Sizer->Add(StaticText15, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_DIVSXT = new ComboBoxMap(Panel2, ID_RDIV_DIVSXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_DIVSXT"));
cmbRDIV_DIVSXT->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_DIVSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText16 = new wxStaticText(Panel2, ID_STATICTEXT17, _("RDIV_DIGSXT"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT17"));
Outputvoltage2Sizer->Add(StaticText16, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_DIGSXT = new ComboBoxMap(Panel2, ID_RDIV_DIGSXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_DIGSXT"));
cmbRDIV_DIGSXT->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_DIGSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText17 = new wxStaticText(Panel2, ID_STATICTEXT18, _("RDIV_DIVGN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT18"));
Outputvoltage2Sizer->Add(StaticText17, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_DIVGN = new ComboBoxMap(Panel2, ID_RDIV_DIVGN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_DIVGN"));
cmbRDIV_DIVGN->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_DIVGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText18 = new wxStaticText(Panel2, ID_STATICTEXT19, _("RDIV_DIGGN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT19"));
Outputvoltage2Sizer->Add(StaticText18, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_DIGGN = new ComboBoxMap(Panel2, ID_RDIV_DIGGN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_DIGGN"));
cmbRDIV_DIGGN->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_DIGGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText19 = new wxStaticText(Panel2, ID_STATICTEXT20, _("RDIV_DIGSXR"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT20"));
Outputvoltage2Sizer->Add(StaticText19, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_DIGSXR = new ComboBoxMap(Panel2, ID_RDIV_DIGSXR, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_DIGSXR"));
cmbRDIV_DIGSXR->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_DIGSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText20 = new wxStaticText(Panel2, ID_STATICTEXT21, _("RDIV_CPSXT"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT21"));
Outputvoltage2Sizer->Add(StaticText20, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_CPSXT = new ComboBoxMap(Panel2, ID_RDIV_CPSXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_CPSXT"));
cmbRDIV_CPSXT->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_CPSXT, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText21 = new wxStaticText(Panel2, ID_STATICTEXT22, _("RDIV_DIG"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT22"));
Outputvoltage2Sizer->Add(StaticText21, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_DIG = new ComboBoxMap(Panel2, ID_RDIV_DIG, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_DIG"));
cmbRDIV_DIG->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_DIG, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText22 = new wxStaticText(Panel2, ID_STATICTEXT23, _("RDIV_CPGN"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT23"));
Outputvoltage2Sizer->Add(StaticText22, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_CPGN = new ComboBoxMap(Panel2, ID_RDIV_CPGN, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_CPGN"));
cmbRDIV_CPGN->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_CPGN, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText23 = new wxStaticText(Panel2, ID_STATICTEXT24, _("RDIV_CPSXR"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT24"));
Outputvoltage2Sizer->Add(StaticText23, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_CPSXR = new ComboBoxMap(Panel2, ID_RDIV_CPSXR, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_CPSXR"));
cmbRDIV_CPSXR->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_CPSXR, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText24 = new wxStaticText(Panel2, ID_STATICTEXT25, _("RDIV_SPIBUF"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT25"));
Outputvoltage2Sizer->Add(StaticText24, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_SPIBUF = new ComboBoxMap(Panel2, ID_RDIV_SPIBUF, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_SPIBUF"));
cmbRDIV_SPIBUF->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_SPIBUF, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText25 = new wxStaticText(Panel2, ID_STATICTEXT26, _("RDIV_AFE"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT26"));
Outputvoltage2Sizer->Add(StaticText25, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_AFE = new ComboBoxMap(Panel2, ID_RDIV_AFE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_AFE"));
cmbRDIV_AFE->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_AFE, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText26 = new wxStaticText(Panel2, ID_STATICTEXT27, _("RDIV_DIGIp2"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT27"));
Outputvoltage2Sizer->Add(StaticText26, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_DIGIp2 = new ComboBoxMap(Panel2, ID_RDIV_DIGIp2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_DIGIp2"));
cmbRDIV_DIGIp2->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_DIGIp2, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
StaticText27 = new wxStaticText(Panel2, ID_STATICTEXT28, _("RDIV_DIGIp1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT28"));
Outputvoltage2Sizer->Add(StaticText27, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
cmbRDIV_DIGIp1 = new ComboBoxMap(Panel2, ID_RDIV_DIGIp1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_RDIV_DIGIp1"));
cmbRDIV_DIGIp1->SetToolTip(_("Controls the output voltage of the LDO by setting the resistive voltage divider ratio"));
Outputvoltage2Sizer->Add(cmbRDIV_DIGIp1, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
OutputvoltageSizer->Add(Outputvoltage2Sizer, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 0);
FlexGridSizer3->Add(OutputvoltageSizer, 1, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
Panel2->SetSizer(FlexGridSizer3);
FlexGridSizer3->Fit(Panel2);
FlexGridSizer3->SetSizeHints(Panel2);
Notebook1->AddPage(Panel3, _("Bypass && Bias && Noise filter"), false);
Notebook1->AddPage(Panel2, _("Voltage"), false);
FlexGridSizer1->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
SetSizer(FlexGridSizer1);
FlexGridSizer1->Fit(this);
FlexGridSizer1->SetSizeHints(this);

Connect(ID_EN_G_LDOP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_G_LDO,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_DIVGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_DIGGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_CPGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_VCOGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_MXRFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_LNA14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_LNA12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_TIA14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_DIVSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_DIGSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_CPSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_VCOSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_DIVSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_DIGSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_CPSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_VCOSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_PD_LDO_DIGIp1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_PD_LDO_DIGIp2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_TXBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_RXBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_AFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_PD_LDO_SPIBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_TBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_RBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_TIA12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_TPAD,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_TLOB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LDO_DIG,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_TBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_TIA12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_TIA14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_TLOB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_TPAD,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_TXBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_VCOGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_VCOSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_VCOSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_AFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_CPGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_CPSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_CPSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_DIG,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_DIGGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_DIGSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_DIGSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_DIVGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_DIVSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_DIVSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_LNA12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_LNA14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_MXRFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_RBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_RXBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_SPIBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_DIGIp2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_BYP_LDO_DIGIp1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_TBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_TIA12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_TIA14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_TLOB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_TPAD,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_TXBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_VCOGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_DIVSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_DIVSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_AFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_CPGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_VCOSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_VCOSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_DIG,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_DIGGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_DIGSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_DIGSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_DIVGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_CPSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_CPSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_LNA12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_LNA14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_MXRFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_RBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_RXBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_SPIBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_DIGIp2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_SPDUP_LDO_DIGIp1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_TBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_TIA12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_TIA14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_TLOB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_TPAD,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_TXBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_VCOGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_VCOSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_VCOSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_AFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_CPGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_DIVSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_DIVSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_DIG,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_DIGGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_DIGSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_DIGSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_DIVGN,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_CPSXR,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_CPSXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_LNA12,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_LNA14,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_MXRFE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_RBB,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_RXBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_SPIBUF,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_DIGIp2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_EN_LOADIMP_LDO_DIGIp1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_VCOSXR,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_VCOSXT,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_TXBUF,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_VCOGN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_TLOB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_TPAD,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_TIA12,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_TIA14,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_RXBUF,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_TBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_MXRFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_RBB,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_LNA12,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_LNA14,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_DIVSXR,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_DIVSXT,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_DIGSXT,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_DIVGN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_DIGGN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_DIGSXR,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_CPSXT,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_DIG,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_CPGN,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_CPSXR,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_SPIBUF,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_AFE,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_DIGIp2,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
Connect(ID_RDIV_DIGIp1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&pnlLDO::ParameterChangeHandler);
//*)
//Hide LDO bypass fields
BypassSizer->Show(false);
FlexGridSizer4->Remove(1);
FlexGridSizer4->Layout();

}
pnlLDO::~pnlLDO()
{
//(*Destroy(pnlLDO)
//*)
}
void pnlLDO::ParameterChangeHandler(wxCommandEvent& event)
{
    if(lmsControl == NULL)
    {
        std::cout << "pnlLDO panel don't have control module assigned" << std::endl;
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

void pnlLDO::Initialize(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    char ctemp[80];
    vector<string> temp;

    temp.clear();
    for(int i=0; i<256; ++i)
        {sprintf(ctemp, "%.3f V", (860.0+3.92*i)/1000.0); temp.push_back(ctemp);}
    cmbRDIV_AFE->Clear();
    cmbRDIV_AFE->Append(temp);
    cmbRDIV_AFE->SetSelection( lmsControl->GetParam(RDIV_AFE));

    cmbRDIV_CPGN->Clear();
    cmbRDIV_CPGN->Append(temp);
    cmbRDIV_CPGN->SetSelection( lmsControl->GetParam(RDIV_CPGN));

    cmbRDIV_CPSXR->Clear();
    cmbRDIV_CPSXR->Append(temp);
    cmbRDIV_CPSXR->SetSelection( lmsControl->GetParam(RDIV_CPSXR));

    cmbRDIV_CPSXT->Clear();
    cmbRDIV_CPSXT->Append(temp);
    cmbRDIV_CPSXT->SetSelection( lmsControl->GetParam(RDIV_CPSXT));

    cmbRDIV_DIG->Clear();
    cmbRDIV_DIG->Append(temp);
    cmbRDIV_DIG->SetSelection( lmsControl->GetParam(RDIV_DIG));

    cmbRDIV_DIGGN->Clear();
    cmbRDIV_DIGGN->Append(temp);
    cmbRDIV_DIGGN->SetSelection( lmsControl->GetParam(RDIV_DIGGN));

    cmbRDIV_DIGIp1->Clear();
    cmbRDIV_DIGIp1->Append(temp);
    cmbRDIV_DIGIp1->SetSelection( lmsControl->GetParam(RDIV_DIGIp1));

    cmbRDIV_DIGIp2->Clear();
    cmbRDIV_DIGIp2->Append(temp);
    cmbRDIV_DIGIp2->SetSelection( lmsControl->GetParam(RDIV_DIGIp2));

    cmbRDIV_DIGSXR->Clear();
    cmbRDIV_DIGSXR->Append(temp);
    cmbRDIV_DIGSXR->SetSelection( lmsControl->GetParam(RDIV_DIGSXR));

    cmbRDIV_DIGSXT->Clear();
    cmbRDIV_DIGSXT->Append(temp);
    cmbRDIV_DIGSXT->SetSelection( lmsControl->GetParam(RDIV_DIGSXT));

    cmbRDIV_DIVGN->Clear();
    cmbRDIV_DIVGN->Append(temp);
    cmbRDIV_DIVGN->SetSelection( lmsControl->GetParam(RDIV_DIVGN));

    cmbRDIV_DIVSXR->Clear();
    cmbRDIV_DIVSXR->Append(temp);
    cmbRDIV_DIVSXR->SetSelection( lmsControl->GetParam(RDIV_DIVSXR));

    cmbRDIV_DIVSXT->Clear();
    cmbRDIV_DIVSXT->Append(temp);
    cmbRDIV_DIVSXT->SetSelection( lmsControl->GetParam(RDIV_DIVSXT));

    cmbRDIV_LNA12->Clear();
    cmbRDIV_LNA12->Append(temp);
    cmbRDIV_LNA12->SetSelection( lmsControl->GetParam(RDIV_LNA12));

    cmbRDIV_LNA14->Clear();
    cmbRDIV_LNA14->Append(temp);
    cmbRDIV_LNA14->SetSelection( lmsControl->GetParam(RDIV_LNA14));

    cmbRDIV_MXRFE->Clear();
    cmbRDIV_MXRFE->Append(temp);
    cmbRDIV_MXRFE->SetSelection( lmsControl->GetParam(RDIV_MXRFE));

    cmbRDIV_RBB->Clear();
    cmbRDIV_RBB->Append(temp);
    cmbRDIV_RBB->SetSelection( lmsControl->GetParam(RDIV_RBB));

    cmbRDIV_RXBUF->Clear();
    cmbRDIV_RXBUF->Append(temp);
    cmbRDIV_RXBUF->SetSelection( lmsControl->GetParam(RDIV_RXBUF));

    cmbRDIV_SPIBUF->Clear();
    cmbRDIV_SPIBUF->Append(temp);
    cmbRDIV_SPIBUF->SetSelection( lmsControl->GetParam(RDIV_SPIBUF));

    cmbRDIV_TBB->Clear();
    cmbRDIV_TBB->Append(temp);
    cmbRDIV_TBB->SetSelection( lmsControl->GetParam(RDIV_TBB));

    cmbRDIV_TIA12->Clear();
    cmbRDIV_TIA12->Append(temp);
    cmbRDIV_TIA12->SetSelection( lmsControl->GetParam(RDIV_TIA12));

    cmbRDIV_TIA14->Clear();
    cmbRDIV_TIA14->Append(temp);
    cmbRDIV_TIA14->SetSelection( lmsControl->GetParam(RDIV_TIA14));

    cmbRDIV_TLOB->Clear();
    cmbRDIV_TLOB->Append(temp);
    cmbRDIV_TLOB->SetSelection( lmsControl->GetParam(RDIV_TLOB));

    cmbRDIV_TPAD->Clear();
    cmbRDIV_TPAD->Append(temp);
    cmbRDIV_TPAD->SetSelection( lmsControl->GetParam(RDIV_TPAD));

    cmbRDIV_TXBUF->Clear();
    cmbRDIV_TXBUF->Append(temp);
    cmbRDIV_TXBUF->SetSelection( lmsControl->GetParam(RDIV_TXBUF));

    cmbRDIV_VCOGN->Clear();
    cmbRDIV_VCOGN->Append(temp);
    cmbRDIV_VCOGN->SetSelection( lmsControl->GetParam(RDIV_VCOGN));

    cmbRDIV_VCOSXR->Clear();
    cmbRDIV_VCOSXR->Append(temp);
    cmbRDIV_VCOSXR->SetSelection( lmsControl->GetParam(RDIV_VCOSXR));

    cmbRDIV_VCOSXT->Clear();
    cmbRDIV_VCOSXT->Append(temp);
    cmbRDIV_VCOSXT->SetSelection( lmsControl->GetParam(RDIV_VCOSXT));
    UpdateTooltips(this);
}

void pnlLDO::UpdateGUI()
{
    //GetParent()->Freeze();
    long value = 0;
    value = lmsControl->GetParam(BYP_LDO_AFE);
    chkBYP_LDO_AFE->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_CPGN);
    chkBYP_LDO_CPGN->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_CPSXR);
    chkBYP_LDO_CPSXR->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_CPSXT);
    chkBYP_LDO_CPSXT->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_DIG);
    chkBYP_LDO_DIG->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_DIGGN);
    chkBYP_LDO_DIGGN->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_DIGIp1);
    chkBYP_LDO_DIGIp1->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_DIGIp2);
    chkBYP_LDO_DIGIp2->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_DIGSXR);
    chkBYP_LDO_DIGSXR->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_DIGSXT);
    chkBYP_LDO_DIGSXT->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_DIVGN);
    chkBYP_LDO_DIVGN->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_DIVSXR);
    chkBYP_LDO_DIVSXR->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_DIVSXT);
    chkBYP_LDO_DIVSXT->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_LNA12);
    chkBYP_LDO_LNA12->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_LNA14);
    chkBYP_LDO_LNA14->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_MXRFE);
    chkBYP_LDO_MXRFE->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_RBB);
    chkBYP_LDO_RBB->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_RXBUF);
    chkBYP_LDO_RXBUF->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_SPIBUF);
    chkBYP_LDO_SPIBUF->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_TBB);
    chkBYP_LDO_TBB->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_TIA12);
    chkBYP_LDO_TIA12->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_TIA14);
    chkBYP_LDO_TIA14->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_TLOB);
    chkBYP_LDO_TLOB->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_TPAD);
    chkBYP_LDO_TPAD->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_TXBUF);
    chkBYP_LDO_TXBUF->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_VCOGN);
    chkBYP_LDO_VCOGN->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_VCOSXR);
    chkBYP_LDO_VCOSXR->SetValue(value);

    value = lmsControl->GetParam(BYP_LDO_VCOSXT);
    chkBYP_LDO_VCOSXT->SetValue(value);

    value = lmsControl->GetParam(EN_G_LDO);
    chkEN_G_LDO->SetValue(value);

    value = lmsControl->GetParam(EN_G_LDOP);
    chkEN_G_LDOP->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_AFE);
    chkEN_LDO_AFE->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_CPGN);
    chkEN_LDO_CPGN->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_CPSXR);
    chkEN_LDO_CPSXR->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_CPSXT);
    chkEN_LDO_CPSXT->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_DIG);
    chkEN_LDO_DIG->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_DIGGN);
    chkEN_LDO_DIGGN->SetValue(value);

    value = lmsControl->GetParam(PD_LDO_DIGIp1);
    chkPD_LDO_DIGIp1->SetValue(value);

    value = lmsControl->GetParam(PD_LDO_DIGIp2);
    chkPD_LDO_DIGIp2->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_DIGSXR);
    chkEN_LDO_DIGSXR->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_DIGSXT);
    chkEN_LDO_DIGSXT->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_DIVGN);
    chkEN_LDO_DIVGN->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_DIVSXR);
    chkEN_LDO_DIVSXR->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_DIVSXT);
    chkEN_LDO_DIVSXT->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_LNA12);
    chkEN_LDO_LNA12->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_LNA14);
    chkEN_LDO_LNA14->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_MXRFE);
    chkEN_LDO_MXRFE->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_RBB);
    chkEN_LDO_RBB->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_RXBUF);
    chkEN_LDO_RXBUF->SetValue(value);

    value = lmsControl->GetParam(PD_LDO_SPIBUF);
    chkPD_LDO_SPIBUF->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_TBB);
    chkEN_LDO_TBB->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_TIA12);
    chkEN_LDO_TIA12->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_TIA14);
    chkEN_LDO_TIA14->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_TLOB);
    chkEN_LDO_TLOB->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_TPAD);
    chkEN_LDO_TPAD->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_TXBUF);
    chkEN_LDO_TXBUF->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_VCOGN);
    chkEN_LDO_VCOGN->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_VCOSXR);
    chkEN_LDO_VCOSXR->SetValue(value);

    value = lmsControl->GetParam(EN_LDO_VCOSXT);
    chkEN_LDO_VCOSXT->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_AFE);
    chkEN_LOADIMP_LDO_AFE->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_CPGN);
    chkEN_LOADIMP_LDO_CPGN->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_CPSXR);
    chkEN_LOADIMP_LDO_CPSXR->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_CPSXT);
    chkEN_LOADIMP_LDO_CPSXT->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_DIG);
    chkEN_LOADIMP_LDO_DIG->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_DIGGN);
    chkEN_LOADIMP_LDO_DIGGN->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_DIGIp1);
    chkEN_LOADIMP_LDO_DIGIp1->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_DIGIp2);
    chkEN_LOADIMP_LDO_DIGIp2->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_DIGSXR);
    chkEN_LOADIMP_LDO_DIGSXR->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_DIGSXT);
    chkEN_LOADIMP_LDO_DIGSXT->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_DIVGN);
    chkEN_LOADIMP_LDO_DIVGN->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_DIVSXR);
    chkEN_LOADIMP_LDO_DIVSXR->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_DIVSXT);
    chkEN_LOADIMP_LDO_DIVSXT->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_LNA12);
    chkEN_LOADIMP_LDO_LNA12->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_LNA14);
    chkEN_LOADIMP_LDO_LNA14->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_MXRFE);
    chkEN_LOADIMP_LDO_MXRFE->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_RBB);
    chkEN_LOADIMP_LDO_RBB->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_RXBUF);
    chkEN_LOADIMP_LDO_RXBUF->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_SPIBUF);
    chkEN_LOADIMP_LDO_SPIBUF->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_TBB);
    chkEN_LOADIMP_LDO_TBB->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_TIA12);
    chkEN_LOADIMP_LDO_TIA12->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_TIA14);
    chkEN_LOADIMP_LDO_TIA14->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_TLOB);
    chkEN_LOADIMP_LDO_TLOB->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_TPAD);
    chkEN_LOADIMP_LDO_TPAD->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_TXBUF);
    chkEN_LOADIMP_LDO_TXBUF->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_VCOGN);
    chkEN_LOADIMP_LDO_VCOGN->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_VCOSXR);
    chkEN_LOADIMP_LDO_VCOSXR->SetValue(value);

    value = lmsControl->GetParam(EN_LOADIMP_LDO_VCOSXT);
    chkEN_LOADIMP_LDO_VCOSXT->SetValue(value);

    value = lmsControl->GetParam(RDIV_AFE);
    cmbRDIV_AFE->SetSelection(value);

    value = lmsControl->GetParam(RDIV_CPGN);
    cmbRDIV_CPGN->SetSelection(value);

    value = lmsControl->GetParam(RDIV_CPSXR);
    cmbRDIV_CPSXR->SetSelection(value);

    value = lmsControl->GetParam(RDIV_CPSXT);
    cmbRDIV_CPSXT->SetSelection(value);

    value = lmsControl->GetParam(RDIV_DIG);
    cmbRDIV_DIG->SetSelection(value);

    value = lmsControl->GetParam(RDIV_DIGGN);
    cmbRDIV_DIGGN->SetSelection(value);

    value = lmsControl->GetParam(RDIV_DIGIp1);
    cmbRDIV_DIGIp1->SetSelection(value);

    value = lmsControl->GetParam(RDIV_DIGIp2);
    cmbRDIV_DIGIp2->SetSelection(value);

    value = lmsControl->GetParam(RDIV_DIGSXR);
    cmbRDIV_DIGSXR->SetSelection(value);

    value = lmsControl->GetParam(RDIV_DIGSXT);
    cmbRDIV_DIGSXT->SetSelection(value);

    value = lmsControl->GetParam(RDIV_DIVGN);
    cmbRDIV_DIVGN->SetSelection(value);

    value = lmsControl->GetParam(RDIV_DIVSXR);
    cmbRDIV_DIVSXR->SetSelection(value);

    value = lmsControl->GetParam(RDIV_DIVSXT);
    cmbRDIV_DIVSXT->SetSelection(value);

    value = lmsControl->GetParam(RDIV_LNA12);
    cmbRDIV_LNA12->SetSelection(value);

    value = lmsControl->GetParam(RDIV_LNA14);
    cmbRDIV_LNA14->SetSelection(value);

    value = lmsControl->GetParam(RDIV_MXRFE);
    cmbRDIV_MXRFE->SetSelection(value);

    value = lmsControl->GetParam(RDIV_RBB);
    cmbRDIV_RBB->SetSelection(value);

    value = lmsControl->GetParam(RDIV_RXBUF);
    cmbRDIV_RXBUF->SetSelection(value);

    value = lmsControl->GetParam(RDIV_SPIBUF);
    cmbRDIV_SPIBUF->SetSelection(value);

    value = lmsControl->GetParam(RDIV_TBB);
    cmbRDIV_TBB->SetSelection(value);

    value = lmsControl->GetParam(RDIV_TIA12);
    cmbRDIV_TIA12->SetSelection(value);

    value = lmsControl->GetParam(RDIV_TIA14);
    cmbRDIV_TIA14->SetSelection(value);

    value = lmsControl->GetParam(RDIV_TLOB);
    cmbRDIV_TLOB->SetSelection(value);

    value = lmsControl->GetParam(RDIV_TPAD);
    cmbRDIV_TPAD->SetSelection(value);

    value = lmsControl->GetParam(RDIV_TXBUF);
    cmbRDIV_TXBUF->SetSelection(value);

    value = lmsControl->GetParam(RDIV_VCOGN);
    cmbRDIV_VCOGN->SetSelection(value);

    value = lmsControl->GetParam(RDIV_VCOSXR);
    cmbRDIV_VCOSXR->SetSelection(value);

    value = lmsControl->GetParam(RDIV_VCOSXT);
    cmbRDIV_VCOSXT->SetSelection(value);

    value = lmsControl->GetParam(SPDUP_LDO_AFE);
    chkSPDUP_LDO_AFE->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_CPGN);
    chkSPDUP_LDO_CPGN->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_CPSXR);
    chkSPDUP_LDO_CPSXR->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_CPSXT);
    chkSPDUP_LDO_CPSXT->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_DIG);
    chkSPDUP_LDO_DIG->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_DIGGN);
    chkSPDUP_LDO_DIGGN->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_DIGIp1);
    chkSPDUP_LDO_DIGIp1->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_DIGIp2);
    chkSPDUP_LDO_DIGIp2->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_DIGSXR);
    chkSPDUP_LDO_DIGSXR->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_DIGSXT);
    chkSPDUP_LDO_DIGSXT->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_DIVGN);
    chkSPDUP_LDO_DIVGN->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_DIVSXR);
    chkSPDUP_LDO_DIVSXR->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_DIVSXT);
    chkSPDUP_LDO_DIVSXT->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_LNA12);
    chkSPDUP_LDO_LNA12->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_LNA14);
    chkSPDUP_LDO_LNA14->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_MXRFE);
    chkSPDUP_LDO_MXRFE->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_RBB);
    chkSPDUP_LDO_RBB->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_RXBUF);
    chkSPDUP_LDO_RXBUF->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_SPIBUF);
    chkSPDUP_LDO_SPIBUF->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_TBB);
    chkSPDUP_LDO_TBB->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_TIA12);
    chkSPDUP_LDO_TIA12->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_TIA14);
    chkSPDUP_LDO_TIA14->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_TLOB);
    chkSPDUP_LDO_TLOB->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_TPAD);
    chkSPDUP_LDO_TPAD->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_TXBUF);
    chkSPDUP_LDO_TXBUF->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_VCOGN);
    chkSPDUP_LDO_VCOGN->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_VCOSXR);
    chkSPDUP_LDO_VCOSXR->SetValue(value);

    value = lmsControl->GetParam(SPDUP_LDO_VCOSXT);
    chkSPDUP_LDO_VCOSXT->SetValue(value);

    //GetParent()->Thaw();
}

