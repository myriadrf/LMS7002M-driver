/**
@file	Algorithms.cpp
@author	Lime Microsystems
@brief	calibration algorithms used for LMS7002
*/

#include "Algorithms.h"
#include "ConnectionManager.h"
#include "LMS7002_MainControl.h"
#include "MessageLog.h"
#include "CommonUtilities.h"
#include <stdio.h>
#include <cmath>
#include "RegistersMap.h"
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <wx/wx.h>

#define REF_CLK_MHZ 30.72
float gRefClkTxTSP = 30.72;
float gRefClkRxTSP = 30.72;

#define defSPI_MAC 0x0020,1,0
#define defSPI_EN_DCOFF_RXFE_RFE 0x010D,6,6
#define defSPI_OSW_PGA_RBB 0x0119,15,15
#define defSPI_PD_RX_AFE2 0x0082,3,3

#define defSPI_PD_XBUF_RX 0x0085,2,2
#define defSPI_EN_G_XBUF 0x0085,0,0
#define defSPI_EN_RXTSP 0x0400,0,0
#define defSPI_DCOFFI_RFE 0x010E,13,7
#define defSPI_DCOFFQ_RFE 0x010E,6,0
#define defSPI_CAPTURE 0x0400,15,15
#define defSPI_HBD_OVR 0x0403,14,12
#define defSPI_AGC_MODE_RXTSP 0x040A,13,12
#define defSPI_CAPSEL 0x0400,14,13
#define defSPI_EN_DCOFF_RXFE_RFE 0x010D,6,6
#define defSPI_CLKH_OV_CLKL_CGEN 0x0089,12,11
#define defSPI_EN_ADCCLKH_CLKGN 0x0086,11,11
#define defSPI_DCCORRI_TXTSP 0x0204,15,8
#define defSPI_DCCORRQ_TXTSP 0x0204,7,0
#define defSPI_DC_BYP_TXTSP 0x0208,3,3

#define defSPI_PD_RLOOPB_1_RFE 0x010C,6,6
#define defSPI_PD_RLOOPB_2_RFE 0x010C,5,5
#define defSPI_SEL_PATH_RFE 0x010D,8,7
#define defSPI_EN_INSHSW_LB1 0x010D,4,4
#define defSPI_EN_INSHSW_LB2 0x010D,3,3
#define defSPI_EN_NEXTTX_RFE 0x010D,0,0
#define defSPI_G_RXLOOPB_RFE 0x0113,5,2
#define defSPI_CCOMP_TIA_RFE 0x0112,15,12
#define defSPI_CFB_TIA_RFE 0x0112,11,0
#define defSPI_INPUT_CTL_PGA_RBB 0x0118,15,13
#define defSPI_RCC_CTL_LPFH_RBB 0x0116,10,8
#define defSPI_RCC_CTL_LPFL_RBB 0x0117,13,11
#define defSPI_C_CTL_LPFH_RBB 0x0116,7,0
#define defSPI_C_CTL_LPFL_RBB 0x0117,10,0
#define defSPI_G_PGA_RBB 0x0119,4,0
#define defSPI_L_LOOPB_TXPAD_TRF 0x0101,12,11
#define defSPI_EN_LOOPB_TXPAD_TRF 0x0101,0,0
#define defSPI_EN_G_TRF 0x0100,0,0
#define defSPI_EN_NEXTTX_TRF 0x0100,14,14
#define defSPI_LOSS_LIN_TXPAD_TRF 0x0101,10,6
#define defSPI_LOSS_MAIN_TXPAD_TRF 0x0101,5,1
#define defSPI_CG_IAMP_TBB 0x0108,15,10
#define defSPI_ICT_IAMP_FRP_TBB 0x0108,9,5
#define defSPI_ICT_IAMP_GG_FRP_TBB 0x0108,4,0
#define defSPI_RCAL_LPFH_TBB 0x0109,15,8
#define defSPI_PD_TX_AFE2 0x0082,1,1
#define defSPI_PD_RX_AFE2 0x0082,3,3
#define defSPI_PD_LOCH_t2RBUF 0x011C,6,6
#define defSPI_DC_REG_TXTSP 0x020C,15,0
#define defSPI_TSGDCLDI_TXTSP 0x0200,5,5
#define defSPI_TSGDCLDQ_TXTSP 0x0200,6,6
#define defSPI_AGC_MODE 0x040A,13,12
#define defSPI_GCORRQ_TXTSP 0x0201,10,0
#define defSPI_GCORRI_TXTSP 0x0202,10,0
#define defSPI_IQCORR_TXTSP 0x0203,11,0
#define defSPI_AGC_AVG 0x040A,2,0
#define defSPI_CMIX_GAIN_RXTSP 0x040C,15,14
#define defSPI_GCORRI_RXTSP 0x0402,10,0
#define defSPI_GCORRQ_RXTSP 0x0401,10,0
#define defSPI_IQCORR_RXTSP 0x0403,11,0

#define xdata
#define SPI_write m_serPort->mSPI_write
#define SPI_read m_serPort->mSPI_read

const float cgen_freq = 122.88;

#define RFE_ADDRESSES 0x010C, 0x0114
#define RBB_ADDRESSES 0x0115, 0x011A
#define AFE_ADDRESSES 0x0082, 0x0082
#define CGEN_ADDRESSES 0x0086, 0x008C
#define SXR_ADDRESSES 0x011C, 0x0124
#define BIAS_ADDRESSES 0x0084, 0x0084
xdata const unsigned short moduleAddresses[]={0x0082, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x010C, 0x010D, 0x010E, 0x010F, 0x0110, 0x0111, 0x0112, 0x0113, 0x0111, 0x0115, 0x0116, 0x0117, 0x0118, 0x0119, 0x011A, 0x011C, 0x011D, 0x011E, 0x011F, 0x0120, 0x0121, 0x0122, 0x0123, 0x0124};
xdata const unsigned short defaultValues[] = {0x800B, 0x4905, 0x0400, 0x0780, 0x0020, 0x0514, 0x1900, 0x067B, 0x88FD, 0x009E, 0x2040, 0x318C, 0x0994, 0x0083, 0xC0E6, 0x03C3, 0x009D, 0x0009, 0x8100, 0x280C, 0x018C, 0x18CB, 0x2E02, 0xAD43, 0x0400, 0x0780, 0x3640, 0xB980, 0x8404, 0x0514, 0x067B, 0x0000};

void Algorithms::SetDefaults(unsigned short sAddr, unsigned short eAddr)
{
	int i;
	for(i=0; i<sizeof(moduleAddresses)/2; ++i)
	{
		if(moduleAddresses[i] >= sAddr && moduleAddresses[i] <= eAddr)
		{
		 	//Modify_SPI_Reg_bits(moduleAddresses[i], 7, 0, defaultValues[i]);
			SPI_write(moduleAddresses[i], defaultValues[i]); //write modified data back to SPI reg
		}
	}
}

#include <set>
using namespace std;
set<unsigned short> modifiedRegs;
void printRegs(const string title)
{
    cout << title << endl;
    for(set<unsigned short>::iterator iter=modifiedRegs.begin(); iter!=modifiedRegs.end(); ++iter)
    {
        char ctemp[512];
        sprintf(ctemp, "0x%04X", *iter);
        cout << ctemp << endl;
    }
    cout << endl;
}

void Algorithms::BackupRegisters(const unsigned short *addrs, unsigned short *values, unsigned char start, unsigned char stop)
{
	while(start<=stop)
	{
		values[start] = SPI_read(addrs[start]);
		++start;
	}
}

void Algorithms::RestoreRegisters(const unsigned short *addrs, unsigned short *values, unsigned char start, unsigned char stop)
{
	while(start<=stop)
	{
		SPI_write(addrs[start], values[start]);
		++start;
	}
}

void Algorithms::flipCapture()
{
 	Modify_SPI_Reg_bits(defSPI_CAPTURE, 0);
    Modify_SPI_Reg_bits(defSPI_CAPTURE, 1);
}

/** @brief Assigns connection manager for data transmission
*/
Algorithms::Algorithms(LMS7002_MainControl *pControl)
{
    lmsControl = pControl;
    m_serPort = lmsControl->getSerPort();
}

Algorithms::~Algorithms()
{
}

/**
Function which replaces requested bits range in SPI register with given data.
    @param SPI_reg_addr: SPI register address
    @param MSB_bit range index
    @param LSB_bit range index
    @param new_bits_data new bits data which will be replace old data
*/

void Algorithms::Modify_SPI_Reg_bits (unsigned short SPI_reg_addr, unsigned char MSB_bit, unsigned char LSB_bit, unsigned short new_bits_data)
{
	unsigned short mask, SPI_reg_data;
	unsigned char bits_number;

	bits_number = MSB_bit - LSB_bit + 1;

	mask = 0xFFFF;

	//removing unnecessary bits from mask
	mask = mask << (16 - bits_number);
	mask = mask >> (16 - bits_number);

	new_bits_data &= mask; //mask new data

	new_bits_data = new_bits_data << LSB_bit; //shift new data

	mask = mask << LSB_bit; //shift mask
	mask =~ mask;//invert mask

	SPI_reg_data = m_serPort->mSPI_read (SPI_reg_addr); //read current SPI reg data

	SPI_reg_data &= mask;//clear bits
	SPI_reg_data |= new_bits_data; //set bits with new data

	m_serPort->mSPI_write(SPI_reg_addr, SPI_reg_data); //write modified data back to SPI reg

    modifiedRegs.insert(SPI_reg_addr);
}

/**
Function, which returns requested bits range value from SPI register.

    @param SPI_reg_addr SPI register address
    @param MSB_bit range index
    @param LSB_bit range index
    @return Returned bits are placed from LSB.
*/
unsigned short Algorithms::Get_SPI_Reg_bits (unsigned short SPI_reg_addr, unsigned char MSB_bit, unsigned char LSB_bit)
{
	unsigned short bits, mask;
	unsigned char bits_number;

	bits_number = MSB_bit - LSB_bit + 1;

	mask = 0xFFFF;

	//removing unnecessary bits from mask
	mask = mask << (16 - bits_number);
	mask = mask >> (16 - bits_number);

	bits = m_serPort->mSPI_read (SPI_reg_addr); //read current data

	bits = bits >> LSB_bit; //shift bits to LSB

	bits &= mask; //mask bits

	return bits;
   /*unsigned short mask;
	unsigned char bits_number;

	bits_number = MSB_bit - LSB_bit + 1;
	mask = 0xFFFF;

	//removing unnecessary bits from mask
	mask = mask << (16 - bits_number);
	mask = mask >> (16 - bits_number);

	 //read current data
	return (SPI_read(SPI_reg_addr) >> LSB_bit) & mask;*/
}

void Algorithms::Modify_SPI_Reg_mask(const unsigned short *addr, const unsigned short *masks, const unsigned short *values, unsigned char start, unsigned char stop)
{
    unsigned short reg_data;
    unsigned short data_reg;
    vector<unsigned short> data;
    while(start<=stop)
    {
		data_reg = SPI_read(addr[start]); //read current SPI reg data
        reg_data = data_reg;
        reg_data &= ~masks[start];//clear bits
        reg_data |= (values[start] & masks[start]);
        //SPI_write(addr[start], reg_data); //write modified data back to SPI reg
        //modifiedRegs.insert(addr[start]);
        data.push_back(addr[start]);
        data.push_back(reg_data);
		++start;
    }
    lmsControl->getSerPort()->SendData(CMD_LMS7002_WR, (const unsigned char*)&data[0], sizeof(unsigned short)*data.size());
}

unsigned char MIMO_ch;
const float RBB_CalFreq[RBB_ALL] = {0.7, 1.5 , 2.5, 5.0, 7.5, 10.0, 18.5, 33.0, 54.0}; //half of bandwidth
const float TBB_CalFreq[TBB_ALL] = {18.5, 38.0, 54.0};

float fclk = 27; //pll clk

unsigned short LowFreqAmp;

/**
Selects MIMO channel. Channel have to be selected before calibration procedures starts. Only one channel can be selected at the same time.
    @param ch
        - 0 - A (SXR)
        - 1 - B (SXT)
*/
void Algorithms::MIMO_Ctrl (unsigned char ch)
{

/*
	01 - Channel A accessible only. Valid for SPI read/write
	10 - Channel B accessible only. Valid for SPI read/write
	11 - Channels A and B accessible. SPI write operation only (calibration will not work correctly)
*/
	Modify_SPI_Reg_bits (0x0020, 1, 0, ch + 1);
	MIMO_ch = ch; //save channel
}

/**
Function for SXT SXR VCO Coarse Tuning
Only one module  (SXT or SXR) can be tuned at same time!
    @param Fref_MHz reference frequency in MHz
    @param Fvco_des_MHz desired vco frequency in MHz
    @param ch channel
    @return 0:success
*/
int Algorithms::VCO_CoarseTuning_SXT_SXR (float Fref_MHz, float Fvco_des_MHz, unsigned char ch)
{
    MessageLog::getInstance()->write("VCO Coarse tuning SXT/SXR started\n", LOG_INFO);
	unsigned char i;

	MIMO_Ctrl(ch);//SXT SXR selection

	// Initialization
//	unsigned short reg011C;
//	unsigned short reg011D;
//	reg011C = Get_SPI_Reg_bits(0x011C, 15, 0);
//	reg011D = Get_SPI_Reg_bits(0x011D, 15, 0);

    Modify_SPI_Reg_bits (0x011C, 2, 1, 0); //activate VCO

	Modify_SPI_Reg_bits (0x011C, 12, 12, 1); // 1) EN_COARSEPLL=1, a. VCO control voltage is switched to a DC =VDD/2
	Modify_SPI_Reg_bits (0x0121, 0, 0, 0); // 2) COARSE_START=0
	Modify_SPI_Reg_bits (0x011C, 9, 9, 1); // 3) EN_INTONLY_SDM=1
	Modify_SPI_Reg_bits (0x011C, 14, 14, 1); // 4) SHORT_NOISEFIL=1 SPDUP_VCO_ Short the noise filter resistor to speed up the settling time
	//Nround = (unsigned short)(4*Fvco_des_MHz/Fref_MHz+0.5); // 5)	Nround=round(4*Fvco_des/Fref)
	unsigned iEnDiv2 = Get_SPI_Reg_bits(0x011C, 10, 10);
    unsigned int Nround = int(Fvco_des_MHz/(Fref_MHz * pow(2.0, iEnDiv2)));

    unsigned long frac_LSB = Get_SPI_Reg_bits(0x011D, 15, 0);
    unsigned long frac_MSB = Get_SPI_Reg_bits(0x011E, 3, 0);

	Modify_SPI_Reg_bits (0x011D, 15, 0, 0); // 6) FRAC_SDM=0
	Modify_SPI_Reg_bits (0x011E, 3, 0, 0);
	Modify_SPI_Reg_bits (0x011E, 13, 4, Nround-4); // 7) INT_SDM=Nround-4
	Modify_SPI_Reg_bits (0x0121, 10, 3, 0); // 9)	Set CSW_VCO<7:0>=<00000000>
	i=7;// 10)	i=7

	long t1, t2; // timers to detect lockup
	long timeout_ms = 4000;

    t1 = t2 = getMilis();
	// Loop Section
	while(t2 - t1 < timeout_ms)
	{
	    Modify_SPI_Reg_bits (0x0121, 3 + i, 3 + i, 1); // CSW_VCO<i>=1
		Modify_SPI_Reg_bits (0x0121, 0, 0, 1); // COARSE_START=1

		while ( Get_SPI_Reg_bits(0x0123, 15, 15) != 1 && (t2-t1<timeout_ms)) //wait till COARSE_STEPDONE=1
        {
            t2 = getMilis();
        }

		if ( Get_SPI_Reg_bits(0x0123, 14, 14) == 1) //check CAORSEPLL_COMPO
		{
			Modify_SPI_Reg_bits (0x0121, 3 + i, 3 + i, 0); // CSW_VCO<i>=0
		}

		Modify_SPI_Reg_bits (0x0121, 0, 0, 0); // COARSE_START=0

		if(i==0)
            break;
		i--;
	}
	if((t2-t1>timeout_ms))
    {
        MessageLog::getInstance()->write("VCO Coarse tuning SXT/SXR canceled, took longer than 4 seconds\n", LOG_WARNING);
    }

	Modify_SPI_Reg_bits (0x011C, 12, 12, 0); // EN_COARSEPLL=0
	Modify_SPI_Reg_bits (0x011C, 9, 9, 0); // EN_INTONLY_SDM=0
	Modify_SPI_Reg_bits (0x011C, 14, 14, 0); // SHORT_NOISEFIL=0 SPDUP_VCO_ Short the noise filter resistor to speed up the settling time

	Modify_SPI_Reg_bits(0x011D, 15, 0, frac_LSB); //restore FRAC
    Modify_SPI_Reg_bits(0x011E, 3, 0, frac_MSB);
	char ctemp[128];
	sprintf(ctemp, "CSW_VCO selected %i\n", Get_SPI_Reg_bits(0x0121, 10, 3));
	MessageLog::getInstance()->write(ctemp, LOG_INFO);
	MessageLog::getInstance()->write("VCO Coarse tuning SXT/SXR finished\n", LOG_INFO);
	return 0;
}

/**
Function for SXT SXR VCO Tuning
Only one module  (SXT or SXR) can be tuned at same time!
    @param Fref_MHz reference frequency in MHz
    @param Fvco_des_MHz desired vco frequency in MHz
    @param ch channel
    @return 0:success, 1:failure
*/
int Algorithms::VCO_Tuning_SXT_SXR (bool Rx)
{
    MessageLog::getInstance()->write("VCO Coarse tuning SXT/SXR started\n", LOG_INFO);
    char ch = Get_SPI_Reg_bits(defSPI_MAC);
    unsigned char i;
	MIMO_Ctrl(Rx ? 0 : 1);//SXT SXR selection
	// Initialization
	Modify_SPI_Reg_bits (0x011C, 2, 1, 0); //activate VCO

	Modify_SPI_Reg_bits (0x011C, 14, 14, 1); // 4) SHORT_NOISEFIL=1 SPDUP_VCO_ Short the noise filter resistor to speed up the settling time
	Modify_SPI_Reg_bits (0x0121, 10, 3, 0); // 9)	Set SWC_VCO<7:0>=<00000000>
	i=7;// 10)	i=7
	int cmphl = 0;
	int csw_lowest = -1;
	while(i>=0)
	{
	    Modify_SPI_Reg_bits (0x0121, 3 + i, 3 + i, 1); // CSW_VCO<i>=1
        cmphl = Get_SPI_Reg_bits(0x0123, 13, 12);
		if ( (cmphl&0x01) == 1) // reduce CSW
			Modify_SPI_Reg_bits (0x0121, 3 + i, 3 + i, 0); // CSW_VCO<i>=0
        if( cmphl == 2 && csw_lowest < 0)
            csw_lowest = Get_SPI_Reg_bits(0x0121, 10, 3);

		if(i==0) break;
		i--;
	}
    char ctemp[256];
	if(csw_lowest >= 0)
    {
        int csw_highest = Get_SPI_Reg_bits(0x0121, 10, 3);
        if(csw_lowest == csw_highest)
        {
            while(csw_lowest>=0)
            {
                Modify_SPI_Reg_bits(0x0121, 10, 3, csw_lowest);
                cmphl = Get_SPI_Reg_bits(0x0123, 13, 12);
                if(cmphl == 0)
                    break;

                else
                    --csw_lowest;
            }
            if(csw_lowest < 0)
                csw_lowest = 0;
        }
        csw_lowest += 1;
        sprintf(ctemp, "lowest CSW_VCO %i, highest CSW_VCO %i\n", csw_lowest, csw_highest);
        MessageLog::getInstance()->write(ctemp, LOG_INFO);
        int csw_value = csw_lowest+(csw_highest-csw_lowest)/2;
        Modify_SPI_Reg_bits(0x0121, 10, 3, csw_value);
    }
    Modify_SPI_Reg_bits (0x011C, 14, 14, 0); // SHORT_NOISEFIL=0 SPDUP_VCO_ Short the noise filter resistor to speed up the settling time
	cmphl = Get_SPI_Reg_bits(0x0123, 13, 12);
	if(cmphl == 2)
    {
        sprintf(ctemp, "CSW_VCO selected %i\n", Get_SPI_Reg_bits(0x0121, 10, 3));
        MessageLog::getInstance()->write(ctemp, LOG_INFO);
        Modify_SPI_Reg_bits(defSPI_MAC, ch);
    }
    else
    {
        sprintf(ctemp, "Tune failed, CSW_VCO selected %i\n", Get_SPI_Reg_bits(0x0121, 10, 3));
        MessageLog::getInstance()->write(ctemp, LOG_WARNING);
        //m_serPort->Notify(LMS_Message(MSG_SHOW_WARNING, ctemp, 0,0));
        Modify_SPI_Reg_bits(defSPI_MAC, ch);
        return 1;
    }
	MessageLog::getInstance()->write("VCO tuning SXT/SXR finished\n", LOG_INFO);
	return 0;
}

/**
    @brief Function for CGEN VCO Coarse Tuning
    @param Fref_MHz reference frequency in MHz
    @param Fvco_des_MHz desired vco frequency in MHz
    @return 0:success
*/
int Algorithms::VCO_CoarseTuning_CGEN (float Fref_MHz, float Fvco_des_MHz)
{
    MessageLog::getInstance()->write("VCO Coarse tuning CGEN started\n", LOG_INFO);
	unsigned char i;

	// Initialization
	Modify_SPI_Reg_bits(0x0086, 2, 2, 0); //activate VCO
	Modify_SPI_Reg_bits (0x0086, 10, 10, 1); // 1) EN_COARSE_CKLGEN=1, a. VCO control voltage is switched to a DC =VDD/2
	Modify_SPI_Reg_bits (0x008B, 0, 0, 0); // 2) COARSE_START_CGEN=0
	Modify_SPI_Reg_bits (0x0086, 9, 9, 1); // 3) EN_INTONLY_SDM_CGEN=1
	Modify_SPI_Reg_bits (0x0086, 15, 15, 1); // 4) SHORT_NOISEFIL=1 SPDUP_VCO_CGEN Short the noise filter resistor to speed up the settling time
	//Nround = (unsigned short)(4*Fvco_des_MHz/Fref_MHz+0.5); // 5)	Nround=round(4*Fvco_des/Fref)
	Modify_SPI_Reg_bits (0x0087, 15, 0, 0); // 6) FRAC_SDM_CGEN=0
	Modify_SPI_Reg_bits (0x0088, 3, 0, 0);
	//Modify_SPI_Reg_bits (0x0088, 13, 4, (Nround-4)); // 7) INT_SDM_CGEN =Nround-4
	Modify_SPI_Reg_bits (0x008B, 8, 1, 0); // 9)	Set CSW_VCO_CGEN<7:0>=<00000000>
	i=7;// 10)	i=7

    long t1, t2; // timers to detect lockup
	long timeout_ms = 4000;

    t1 = t2 = getMilis();
	// Loop Section
	while((t2-t1<timeout_ms))
	{
		Modify_SPI_Reg_bits (0x008B, 1 + i, 1 + i, 1); // CSW_VCO_CGEN<i>=1
		Modify_SPI_Reg_bits (0x008B, 0, 0, 1); // COARSE_START_CGEN=1

		while ( Get_SPI_Reg_bits(0x008C, 15, 15) != 1  && (t2-t1<timeout_ms)) //wait till COARSE_STEPDONE_CGEN=1
        {
            t2 = getMilis();
        }

		if ( Get_SPI_Reg_bits(0x008C, 14, 14) == 1) //check COARSEPLL_COMPO_CGEN
		{
			Modify_SPI_Reg_bits (0x008B, 1 + i, 1 + i, 0); // CSW_VCO<i>=0
		}

		Modify_SPI_Reg_bits (0x008B, 0, 0, 0); // 2) COARSE_START_CGEN=0

		if(i==0) break;
		i--;
	}
	if((t2-t1>timeout_ms))
    {
        MessageLog::getInstance()->write("VCO Coarse tuning CGEN canceled, took longer than 4 seconds\n", LOG_WARNING);
    }

	Modify_SPI_Reg_bits (0x0086, 10, 10, 0); // 1) EN_COARSE_CKLGEN=0
	Modify_SPI_Reg_bits (0x0086, 9, 9, 0); // 3) EN_INTONLY_SDM_CGEN=0
	Modify_SPI_Reg_bits (0x0086, 15, 15, 0); // 4) SHORT_NOISEFIL=0 SPDUP_VCO_CGEN Short the noise filter resistor to speed up the settling time
	char ctemp[128];
	sprintf(ctemp, "CSW_VCO_CGEN selected %i\n", Get_SPI_Reg_bits(0x008B, 8, 1));
	MessageLog::getInstance()->write(ctemp, LOG_INFO);
	MessageLog::getInstance()->write("VCO Coarse tuning CGEN finished\n", LOG_INFO);
    return 0;
}

/**
    @brief Function for CGEN VCO Tuning
    @param Fref_MHz reference frequency in MHz
    @param Fvco_des_MHz desired vco frequency in MHz
    @return 0:success
*/
int Algorithms::VCO_Tuning_CGEN ()
{
    MessageLog::getInstance()->write("VCO tuning CGEN started\n", LOG_INFO);
	unsigned char i;

	// Initialization
	Modify_SPI_Reg_bits(0x0086, 2, 2, 0); //activate VCO
	Modify_SPI_Reg_bits (0x0086, 15, 15, 1); // 4) SHORT_NOISEFIL=1 SPDUP_VCO_CGEN Short the noise filter resistor to speed up the settling time
	Modify_SPI_Reg_bits (0x008B, 8, 1, 0); // 9)	Set CSW_VCO_CGEN<7:0>=<00000000>
	i=7;// 10)	i=7
    int cmphl = 0;
    int csw_lowest = -1;
	while(i>=0)
	{
		Modify_SPI_Reg_bits (0x008B, 1 + i, 1 + i, 1); // CSW_VCO_CGEN<i>=1
        cmphl = Get_SPI_Reg_bits(0x008C, 13, 12);
		if( (cmphl&0x01) == 1)
			Modify_SPI_Reg_bits (0x008B, 1 + i, 1 + i, 0); // CSW_VCO<i>=0
		if( cmphl == 2 && csw_lowest < 0)
			csw_lowest = Get_SPI_Reg_bits(0x008B, 8, 1);

		if(i==0) break;
		i--;
	}
	char ctemp[256];
	if(csw_lowest >= 0)
    {
        int csw_highest = Get_SPI_Reg_bits(0x008B, 8, 1);
        if(csw_lowest == csw_highest)
        {
            while(csw_lowest>=0)
            {
                Modify_SPI_Reg_bits(0x008B, 8, 1, csw_lowest);
                cmphl = Get_SPI_Reg_bits(0x008C, 13, 12);
                if(cmphl == 0)
                    break;
                else
                    --csw_lowest;
            }
        }
        sprintf(ctemp, "lowest CSW_VCO_CGEN %i, highest CSW_VCO_CGEN %i\n", csw_lowest, csw_highest);
        MessageLog::getInstance()->write(ctemp, LOG_INFO);
        int csw_value = csw_lowest+(csw_highest-csw_lowest)/2;
        Modify_SPI_Reg_bits(0x008B, 8, 1, csw_value);
    }
    Modify_SPI_Reg_bits (0x0086, 15, 15, 0); // 4) SHORT_NOISEFIL=0 SPDUP_VCO_CGEN Short the noise filter resistor to speed up the settling time
	cmphl = Get_SPI_Reg_bits(0x008C, 13, 12);
	if(cmphl == 2)
    {
        sprintf(ctemp, "CSW_VCO_CGEN selected %i\n", Get_SPI_Reg_bits(0x008B, 8, 1));
        MessageLog::getInstance()->write(ctemp, LOG_INFO);
    }
    else
    {
        sprintf(ctemp, "Tune failed, CSW_VCO_CGEN selected %i\n", Get_SPI_Reg_bits(0x008B, 8, 1));
        MessageLog::getInstance()->write(ctemp, LOG_WARNING);
        m_serPort->Notify(LMS_Message(MSG_WARNING, ctemp, 0,0));
    }
	MessageLog::getInstance()->write("VCO Coarse tuning CGEN finished\n", LOG_INFO);
    return 0;
}

float Algorithms::Resistor_calibration ()
{
    MessageLog::getInstance()->write("Resistor calibration started\n", LOG_INFO);
	unsigned char RP_CALIB_BIAS, RP_CALIB_BIAS_cal;
	unsigned short BestValue, ADCOUT;
	float ratio;

	RP_CALIB_BIAS_cal = 16;
	RP_CALIB_BIAS = 0;
	Modify_SPI_Reg_bits (0x0084, 10, 6, RP_CALIB_BIAS); // write RP_CALIB_BIAS value
	Modify_SPI_Reg_bits (0x0084, 12, 11, 1); // MUX_BIAS_OUT = 1
	Modify_SPI_Reg_bits (0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode)
	Modify_SPI_Reg_bits(0x0400, 15, 15, 0); //Capture 0
	Modify_SPI_Reg_bits(0x0400, 14, 13, 0); //Capsel 0 - RSSI

	while (RP_CALIB_BIAS <= 31)
	{
	    Modify_SPI_Reg_bits(0x0400, 15, 15, 0); //Capture 0
	    Modify_SPI_Reg_bits(0x0400, 15, 15, 1); //Capture 1
		ADCOUT = (Get_SPI_Reg_bits(0x040F, 15, 0) << 2) | Get_SPI_Reg_bits(0x040E, 1, 0); //RSSI value

		if(RP_CALIB_BIAS == 0)
		{
			BestValue = ADCOUT;
		}

		if ( ADCOUT < BestValue )
		{
			BestValue = ADCOUT;
			RP_CALIB_BIAS_cal = RP_CALIB_BIAS; //store calibrated value
		}

		RP_CALIB_BIAS++;
		Modify_SPI_Reg_bits (0x0084, 10, 6, RP_CALIB_BIAS); // write RP_CALIB_BIAS value
	}
    Modify_SPI_Reg_bits(0x0400, 15, 15, 0); //Capture 0
	Modify_SPI_Reg_bits (0x0084, 10, 6, RP_CALIB_BIAS_cal); // set the control RP_CAL_BIAS to stored calibrated value
	ratio = 16/RP_CALIB_BIAS_cal; //calculate ratio
    MessageLog::getInstance()->write("Resistor calibration finished\n", LOG_INFO);
	return ratio;
}

// RBB
void Algorithms::Set_NCO_Freq (float Freq_MHz, float refClk_MHz, bool Rx)
{
	unsigned long fcw = (Freq_MHz/refClk_MHz)*pow(2.0, 32);
    if(Rx)
    {
        Modify_SPI_Reg_bits (0x0440, 4, 0, 0); //TX SEL[3:0] = 0 & MODE = 0
        Modify_SPI_Reg_bits (0x0442, 15, 0, (fcw >> 16)); //FCW0[31:16]: NCO frequency control word register 0. MSB part.
        Modify_SPI_Reg_bits (0x0443, 15, 0, fcw); //FCW0[15:0]: NCO frequency control word register 0. LSB part.
    }
    else
    {
        Modify_SPI_Reg_bits (0x0240, 4, 0, 0); //TX SEL[3:0] = 0 & MODE = 0
        Modify_SPI_Reg_bits (0x0242, 15, 0, (fcw >> 16)); //FCW0[31:16]: NCO frequency control word register 0. MSB part.
        Modify_SPI_Reg_bits (0x0243, 15, 0, fcw); //FCW0[15:0]: NCO frequency control word register 0. LSB part.
    }
}

void Algorithms::Algorithm_A_RBB ()
{
	unsigned char R_CTL_LPF_RBB;

	R_CTL_LPF_RBB = 16; // default control value
	R_CTL_LPF_RBB = (unsigned char)(R_CTL_LPF_RBB * Resistor_calibration ()); // Multiply by ratio

	Modify_SPI_Reg_bits (0x0116, 15, 11, R_CTL_LPF_RBB);
	RBB_RBANK[MIMO_ch] = R_CTL_LPF_RBB; // Store RBANK Values (R_CTL_LPF_RBB)
}

unsigned short Algorithms::Algorithm_B_RBB ()
{
	unsigned short ADCOUT;
	unsigned char CG_IAMP_TBB, gain_inc;

	Set_NCO_Freq (0.1, fclk, false); // Set DAC output to 100kHz (0.1MHz) single tone.

	CG_IAMP_TBB = 24; //set nominal CG_IAMP_TBB value
	Modify_SPI_Reg_bits (0x0108, 15, 10, CG_IAMP_TBB);

	Modify_SPI_Reg_bits (0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode)
	ADCOUT = Get_SPI_Reg_bits(0x040B, 15, 0); //RSSI value // Measure the output level at the ADC input

	if(ADCOUT < 52428) gain_inc = 1; //is it less then 80% of full scale swing (52428 (80% of 16 bits))
		else gain_inc = 0;

	while (1)
	{
		ADCOUT = Get_SPI_Reg_bits(0x040B, 15, 0); //RSSI value // Measure the output level at the ADC input

		if (gain_inc)
		{
			if(ADCOUT >= 52428) break;
		}
		else
		{
			if(ADCOUT <= 52428) break;
		}

		if( (CG_IAMP_TBB == 0) || (CG_IAMP_TBB == 63)) break; //gain limit reached

		if(gain_inc) CG_IAMP_TBB++;
			else CG_IAMP_TBB--;

		Modify_SPI_Reg_bits (0x0108, 15, 10, CG_IAMP_TBB); //write val to reg
	}

	return ADCOUT; // Record the exact value of the amplitude in “LowFreqAmp” for later on comparison.
}

void Algorithms::Algorithm_F_RBB (unsigned char Band_id)
{
	unsigned short ADCOUT, CONTROL;
	unsigned short LowFreqAmp;
	unsigned char low_band;

	Modify_SPI_Reg_bits (0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode)

	if(Band_id <= RBB_20MHZ)
	{
		low_band = 1; // CONTROL=C_CTL_LPFL_RBB
		CONTROL = 0xFF; // Set the CONTROL to maximum value. This should bring the output cutt-off frequency to minimum.
	}
	else
	{
		low_band = 0; // CONTROL=C_CTL_LPFH_RBB
		CONTROL = 0x7FF; // Set the CONTROL to maximum value. This should bring the output cutt-off frequency to minimum.
	}

	if (low_band) Modify_SPI_Reg_bits (0x0117, 10, 0, CONTROL); // write to C_CTL_LPFL_RBB
		else Modify_SPI_Reg_bits (0x0116, 7, 0, CONTROL); // write to C_CTL_LPFH_RBB

	LowFreqAmp = Algorithm_B_RBB (); // Apply (Algorithm B).
	Set_NCO_Freq (RBB_CalFreq[Band_id], fclk, false); // Apply a single tone frequency at “CalFreq”.

	while (1)
	{
		if (low_band) Modify_SPI_Reg_bits (0x0117, 10, 0, CONTROL); // write to C_CTL_LPFL_RBB
			else Modify_SPI_Reg_bits (0x0116, 7, 0, CONTROL); // write to C_CTL_LPFH_RBB

		ADCOUT = Get_SPI_Reg_bits(0x040B, 15, 0); //RSSI value // Measure the value of the amplitude at the ADC input. This value should be lower than “LowFreqAmp”.

		if (! (ADCOUT < LowFreqAmp)) break; //If it is lower than “LowFreqAmp” repeat cycle
		if (CONTROL == 0) break;
		CONTROL--; // Decrease the CONTROL value by one.
	}

	RBB_CBANK[MIMO_ch][Band_id] = CONTROL; // Store CBANK Values
}

void Algorithms::Set_cal_path_RBB (unsigned char path_no)
{
	switch (path_no)
	{
		case 7: // RX  LPF Low Section Verification
			// RBB Control Bits
			Modify_SPI_Reg_bits (0x010C, 1, 1, 1);//PD_TIA_RFE == 1
			Modify_SPI_Reg_bits (0x0115, 3, 3, 1);//PD_LPFH_RBB == 1
			Modify_SPI_Reg_bits (0x0115, 2, 2, 0);//PD_LPFL_RBB == 0
			Modify_SPI_Reg_bits (0x0115, 15, 15, 0);//EN_LB_LPFH_RBB == 0
			Modify_SPI_Reg_bits (0x0115, 14, 14, 1);//EN_LB_LPFL_RBB == 1
			Modify_SPI_Reg_bits (0x0118, 15, 13, 0);//INPUT_CTL_PGA_RBB == 0
			Modify_SPI_Reg_bits (0x0119, 15, 15, 1);//OSW_PGA_RBB == 1
			break;

		case 8: // RX  LPF High Section Verification
			// RBB Control Bits
			Modify_SPI_Reg_bits (0x010C, 1, 1, 1);//PD_TIA_RFE == 1
			Modify_SPI_Reg_bits (0x0115, 3, 3, 0);//PD_LPFH_RBB == 0
			Modify_SPI_Reg_bits (0x0115, 2, 2, 1);//PD_LPFL_RBB == 1
			Modify_SPI_Reg_bits (0x0115, 15, 15, 1);//EN_LB_LPFH_RBB == 1
			Modify_SPI_Reg_bits (0x0115, 14, 14, 0);//EN_LB_LPFL_RBB == 0
			Modify_SPI_Reg_bits (0x0118, 15, 13, 1);//INPUT_CTL_PGA_RBB == 1
			Modify_SPI_Reg_bits (0x0119, 15, 15, 1);//OSW_PGA_RBB == 1
			break;
	}

	// TBB Control Bits
	Modify_SPI_Reg_bits (0x010A, 15, 14, 0);//TSTIN_TBB == 0
	Modify_SPI_Reg_bits (0x0105, 4, 4, 0);//PD_LPFH_TBB == 0
	Modify_SPI_Reg_bits (0x0105, 14, 12, 1);//LOOPB_TBB<1:0> == 1
	Modify_SPI_Reg_bits (0x0105, 1, 1, 0);//(PD_LPFS5_TBB == 0 OR PD_LPFLAD_TBB == 0)  (pre-emphasis OFF)
}

int Algorithms::Calibration_LowBand_RBB (unsigned char ch)
{
	MIMO_Ctrl (ch);

	Algorithm_A_RBB (); // Aproximate resistor value for RBB RBANKS (Algorithm A)

	Set_cal_path_RBB (7); // Set control signals to path 7 (RX LowBand)

	Algorithm_B_RBB (); // Calibrate and Record the low frequency output amplitude (Algorithm B)

	Algorithm_F_RBB (RBB_1_4MHZ);// CalibrateByCap the output cuttoff frequency at 0,7 MHz and store
	Algorithm_F_RBB (RBB_3_0MHZ);// CalibrateByCap the output cuttoff frequency at 1,5 MHz MHz and store
	Algorithm_F_RBB (RBB_5_0MHZ);// CalibrateByCap the output cuttoff frequency at 2,5 MHz MHz and store
	Algorithm_F_RBB (RBB_10_0MHZ);// CalibrateByCap the output cuttoff frequency at 5 MHz MHz and store
	Algorithm_F_RBB (RBB_15_0MHZ);// CalibrateByCap the output cuttoff frequency at 7,5 MHz and store
	Algorithm_F_RBB (RBB_20MHZ);// CalibrateByCap the output cuttoff frequency at 10 MHz MHz and store
	return 0;
}

int Algorithms::Calibration_HighBand_RBB (unsigned char ch)
{
	MIMO_Ctrl (ch);

	Set_cal_path_RBB (8); //Set control signals to path 8 (RX HighBand)

	Algorithm_B_RBB (); //Calibrate and Record the low frequency output amplitude (Algorithm B)

	Algorithm_F_RBB (RBB_37_0MHZ);// CalibrateByCap the output cuttoff frequency at 18,5 MHz MHz and store
	Algorithm_F_RBB (RBB_66_0MHZ);// CalibrateByCap the output cuttoff frequency at 33 MHz MHz and store
	Algorithm_F_RBB (RBB_108_0MHZ);// CalibrateByCap the output cuttoff frequency at 54 MHz MHz and store
	return 0;
}

// TBB

void Algorithms::Algorithm_A_TBB ()
{
	unsigned char RCAL_LPFLAD_TBB;

	RCAL_LPFLAD_TBB = 193; // default control value 193 - when 11MHz
	RCAL_LPFLAD_TBB = (unsigned char)(RCAL_LPFLAD_TBB * Resistor_calibration ()); // Multiply by ratio

	Modify_SPI_Reg_bits (0x0109, 7, 0, RCAL_LPFLAD_TBB);
	///TBB_RBANK = RCAL_LPFLAD_TBB; // Store RBANK Values (RCAL_LPFLAD_TBB) ???
	//Return the result of the multiplication. ????kam
}

unsigned short Algorithms::Algorithm_B_TBB ()
{
	//same algorith as rbb???
	return 0;
}

void Algorithms::Algorithm_C_TBB (unsigned char Band_id)
{
	unsigned short ADCOUT, LowFreqAmp;
	unsigned char CCAL_LPFLAD_TBB;

	Modify_SPI_Reg_bits (0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode)

	Set_NCO_Freq (TBB_CalFreq[Band_id], fclk, false); // 1 Apply a single tone frequency at “CalFreq”.

	CCAL_LPFLAD_TBB = 31;
	Modify_SPI_Reg_bits (0x010A, 12, 8, CCAL_LPFLAD_TBB); // 2 Set the “CCAL_LPFLAD_TBB” to maximum value.

	LowFreqAmp = Algorithm_B_RBB (); // Apply (Algorithm B).

	while (1)
	{
		Modify_SPI_Reg_bits (0x010A, 12, 8, CCAL_LPFLAD_TBB);

		ADCOUT = Get_SPI_Reg_bits(0x040B, 15, 0); //RSSI value // Measure the value of the amplitude at the ADC input. This value should be lower than “LowFreqAmp”.

		if (! (ADCOUT < LowFreqAmp)) break; //If amplitude is lower than “LowFreqAmp” repeat cycle
		if (CCAL_LPFLAD_TBB == 0) break;
		CCAL_LPFLAD_TBB--; // Decrease the control value “CCAL_LPFLAD_TBB” by one step.
	}

	TBB_CBANK[MIMO_ch] = CCAL_LPFLAD_TBB;
	// 6 Return the value of “CCAL_LPFLAD_TBB” as the calibrated CBANK value of TBB.
}

int Algorithms::Algorithm_D_TBB (unsigned char Band_id)
{
	unsigned short ADCOUT;
	unsigned char inc, Zero_Freq = 127;

	Set_NCO_Freq (TBB_CalFreq[Band_id], fclk, false); // 1 Apply a single tone at frequency equal to “CalFreq”

	ADCOUT = Get_SPI_Reg_bits(0x040B, 15, 0); //RSSI value

	if(ADCOUT > LowFreqAmp) inc = 0; //If greater, then the pre-emphasis zero is faster than the real pole
		else inc = 1;

	while (1)
	{
		ADCOUT = Get_SPI_Reg_bits(0x040B, 15, 0); //RSSI value // Measure the output level at the ADC input

		if (inc)
		{
			if(ADCOUT >= 52428) break;
		}
		else
		{
			if(ADCOUT <= 52428) break;
		}

		if( (Zero_Freq == 0) || (Zero_Freq == 255))  //gain limit reached
		{
			return 0;
			break;
		}

		if(inc) Zero_Freq++;
			else Zero_Freq--;

	}

}

void Algorithms::Algorithm_E_TBB (unsigned char Band_id)
{
	unsigned short ADCOUT;
	unsigned short LowFreqAmp;
	unsigned char low_band, CONTROL;

	Set_NCO_Freq (TBB_CalFreq[Band_id], fclk, false); // Set CalFreq

	Modify_SPI_Reg_bits (0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode)

	if(Band_id <= TBB_11_0MHZ) //If(“CalFreq”) <=11MHz, then CONTROL=RCAL_LPFLAD_TBB, else, CONTROL=RCAL_LPFH_TBB
	{
		low_band = 1; // CONTROL=RCAL_LPFLAD_TBB
	}
	else
	{
		low_band = 0; // CONTROL=RCAL_LPFH_TBB
	}

	CONTROL = 0; // Set the CONTROL to zero. This should bring the output cutt-off frequency to minimum.

	if (low_band) Modify_SPI_Reg_bits (0x0109, 7, 0, CONTROL); // write to RCAL_LPFLAD_TBB
		else Modify_SPI_Reg_bits (0x0109, 15, 8, CONTROL); // write to RCAL_LPFH_TBB

	LowFreqAmp = Algorithm_B_TBB (); // Apply (Algorithm B).
	Set_NCO_Freq (TBB_CalFreq[Band_id], fclk, false); // Apply a single tone frequency at “CalFreq”.

	while (1)
	{
		if (low_band) Modify_SPI_Reg_bits (0x0117, 10, 0, CONTROL); // write to C_CTL_LPFL_RBB
			else Modify_SPI_Reg_bits (0x0116, 7, 0, CONTROL); // write to C_CTL_LPFH_RBB

		ADCOUT = Get_SPI_Reg_bits(0x040B, 15, 0); //RSSI value // Measure the value of the amplitude at the ADC input. This value should be lower than “LowFreqAmp”.

		if (! (ADCOUT < LowFreqAmp)) break; //If it is lower than “LowFreqAmp” repeat cycle
		if (CONTROL == 0xFF) break;
		CONTROL++; // Increase the CONTROL value by one.
	}

	// 8 Return the value of CONTROL.
	TBB_RBANK[MIMO_ch][Band_id] = CONTROL; // Store RBANK Values
}

void Algorithms::Set_cal_path_TBB (unsigned char path_no)
{
	switch (path_no)
	{
		case 1: // Current Amplifier Low Section Verification.
			break;

		case 2: // Current Amplifier High Section testing.
			break;

		case 3: // TX LPFLADDER Low Section testing.
			break;

		case 4: // TX REALPOLE Low Section testing
			break;

		case 5: // TX Lowband testing
			break;

		case 6: // TX BIQUAD High Section testing
			Modify_SPI_Reg_bits (0x010A, 15, 14, 0); // TSTIN_TBB == 0
			Modify_SPI_Reg_bits (0x0105, 4, 4, 0); // PD_LPFH_TBB == 0
			Modify_SPI_Reg_bits (0x0105, 14, 12, 3); // LOOPB_TBB<1:0> == 3
			Modify_SPI_Reg_bits (0x0105, 1, 1, 1); // PD_LPFS5_TBB == 1
			Modify_SPI_Reg_bits (0x0105, 2, 2, 1); // PD_LPFLAD_TBB == 1
			Modify_SPI_Reg_bits (0x010A, 13, 13, 0); // BYPLADDER_TBB == 0 (Digital Pre-Emphasis = “OFF”)
			break;
	}

	//RBB Control Bits
	Modify_SPI_Reg_bits (0x0118, 15, 13, 3); // INPUT_CTL_PGA_RBB == 3
	Modify_SPI_Reg_bits (0x0115, 2, 2, 1); // PD_LPFL_RBB == 1
	Modify_SPI_Reg_bits (0x0115, 3, 3, 1); // PD_LPFH_RBB == 1
	Modify_SPI_Reg_bits (0x010C, 1, 1, 1); // PD_TIA_RFE == 1
	Modify_SPI_Reg_bits (0x0119, 15, 15, 0); // OSW_PGA_RBB ==0
}

int Algorithms::Calibration_LowBand_TBB (unsigned char ch)
{
	MIMO_Ctrl (ch);
//#warning Not finished!!!
	//not finished!!!!
	MessageLog::getInstance()->write("Calibration_LowBand_TBB not implemented\n", LOG_WARNING);
	return -1;
}

int Algorithms::Calibration_HighBand_TBB (unsigned char ch)
{
	MIMO_Ctrl (ch);

	Set_cal_path_TBB (6); // Set control signals to path 6

	Algorithm_E_TBB (TBB_18_5MHZ);// CalibrateByRes the output cutoff frequency (Algorithm E)
	Algorithm_E_TBB (TBB_38_0MHZ);// CalibrateByRes the output cutoff frequency (Algorithm E)
	Algorithm_E_TBB (TBB_54_0MHZ);// CalibrateByRes the output cutoff frequency (Algorithm E)
	return 0;
}

#define dcrxBACKUP_REG_COUNT 19
xdata unsigned short dcrx_backupRegs[dcrxBACKUP_REG_COUNT] = {0x010D,0x0119,0x0082,0x0084,0x0085,0x010D,0x0086,0x0087,0x0088,0x0089,0x008A,0x008B,0x008C,0x0400,0x010E,0x0403,0x040A,0x040C,0x010D};
xdata unsigned short dcrx_backupData[dcrxBACKUP_REG_COUNT];
/** @brief Performs RX DC calibration
    @return 0: success, -1: failed
*/

#define dcrxN 32
void Algorithms::Set_DCOFF(char offsetI, char offsetQ)
{
	unsigned short valToSend = 0;
    if(offsetI < 0)
        valToSend |= 0x40;
    valToSend |= labs(offsetI);
	valToSend = valToSend << 7;
	if(offsetQ < 0)
        valToSend |= 0x40;
    valToSend |= labs(offsetQ);
	SPI_write(0x010E, valToSend);
}

int Algorithms::DCCalibrationRX(char config, int *resultI, int *resultQ)
{
    //for redboard
    //Modify_SPI_Reg_bits(0x0093, 6, 6, 1);
    //Modify_SPI_Reg_bits(0x0092, 9, 9, 1);
    modifiedRegs.clear();

    int i;
    int avgI;
    int avgQ;
    xdata short value;
    xdata short offsetI = 0;
    xdata short offsetQ = 0;
    xdata char iteration;
    xdata long sumI;
    xdata long sumQ;
    xdata int capd;
	///xdata int minDCOFF[2];
	//xdata int rssiField[9];
	//xdata int minRSSIindex;
	xdata const unsigned short addrs[] =  {0x010D, 0x0119, 0x0082, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x0400, 0x010E, 0x0400, 0x0403, 0x040A, 0x040C };
	xdata const unsigned short masks[] =  {0x0040, 0x8000, 0xFFFF, 0x001F, 0x0005, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xE001, 0x1FFF, 0x6001, 0x7000, 0x3000, 0x00BF };
	xdata const unsigned short values[] = {0x0040, 0x0000, 0x800B, 0x0000, 0x0001, 0x4905, 0x0400, 0x0780, 0x0020, 0x0514, 0x1900, 0x067B, 0x2001, 0x0000, 0x0001, 0x7000, 0x2000, 0x00BF };
    //Stage 1

    if(config)
    {

	//BackupRegisters(dcrx_backupRegs, dcrx_backupData, 0, dcrxBACKUP_REG_COUNT-1);
    //Stage 2
    //Modify_SPI_Reg_bits(defSPI_MAC, 1);
	Modify_SPI_Reg_mask(addrs, masks, values, 0, 13);
	if(SetFrequencyCGEN(REF_CLK_MHZ, cgen_freq) != 0)	//comparators are being checked
	{
		RestoreRegisters(dcrx_backupRegs, dcrx_backupData, 0, dcrxBACKUP_REG_COUNT-1);
		return -3;
	}

    }

    bool DoneI = false;
    bool DoneQ = false;
    Modify_SPI_Reg_bits(defSPI_CAPSEL, 1);
    Modify_SPI_Reg_bits(defSPI_EN_DCOFF_RXFE_RFE, 1);
    for(iteration=0; iteration < 64 && (!DoneI || !DoneQ); ++iteration)
    {
        Set_DCOFF(offsetI,offsetQ);
        DoneI = false;
        DoneQ = false;
        printf("\rIteration %4i\n", iteration);
        //1. Read ADCI, ADCQ value N time, N > 100, average them
        sumI = 0;
        sumQ = 0;
        for(i=0; i<dcrxN; ++i)
        {
            //pulse CAPTURE
            flipCapture();
            capd = Get_SPI_Reg_bits(0x040E, 15, 0);
            value = (capd&0x3FF) << 6;
            sumI += value >> 6;
            capd = Get_SPI_Reg_bits(0x040F, 15, 0);
            value = (capd&0x3FF) << 6;
            sumQ += value >> 6;
        }
        avgI = sumI/dcrxN;
        avgQ = sumQ/dcrxN;

        char ctemp[512];
        sprintf(ctemp, "Rx: AvgI: %4i OffsetI: %3i    AvgQ: %4i OffsetQ: %3i\n", avgI, offsetI, avgQ, offsetQ);
        cout << "I: " << avgI << " Q: " << avgQ << endl;
        cout << "Off:" << offsetI << " Off:" << offsetQ << endl;
        MessageLog::getInstance()->write(ctemp, LOG_INFO);


        if(avgI > 0)
            --offsetI;
        else if(avgI < 0)
            ++offsetI;
        else
            DoneI = true;


        if(avgQ > 0)
            --offsetQ;
        else if(avgQ < 0)
            ++offsetQ;
        else
            DoneQ = true;
    }
    //Stage 4
//    if(config)
//        RestoreRegisters(dcrx_backupRegs, dcrx_backupData, 0, dcrxBACKUP_REG_COUNT-1);
    Modify_SPI_Reg_bits(defSPI_EN_DCOFF_RXFE_RFE, 1);
    Set_DCOFF(offsetI,offsetQ);
    if(resultI)
        *resultI = offsetI;
    if(resultQ)
        *resultQ = offsetQ;
    MessageLog::getInstance()->write("Rx DC calibration finished\n", LOG_INFO);

    printRegs("RX DC CALIBRATION REGISTERS");

    return 0x0;
}

xdata unsigned short dcrxrssi_backupRegs[] = {0x0082,0x0084,0x0085,0x0086,0x0087,0x0088,0x0089,0x008A,0x008B,0x008C,0x010D,0x010E,0x0119,0x0400,0x040A,0x040C};
#define dcrxrssiBACKUP_REG_COUNT sizeof(dcrxrssi_backupRegs)/sizeof(unsigned short)
xdata unsigned short dcrxrssi_backupData[dcrxrssiBACKUP_REG_COUNT];
/*int Algorithms::DCCalibrationRX_RSSI(char config, int *resultI, int *resultQ)
{
    unsigned long t1 = getMilis();
    //for redboard
    //Modify_SPI_Reg_bits(0x0093, 6, 6, 1);
    //Modify_SPI_Reg_bits(0x0092, 9, 9, 1);
    xdata int globMinI;
    xdata int globMinQ;
    xdata unsigned long minRSSI = ~0;
    xdata unsigned long newRSSI = 0;
    xdata int offsetI = 0;
    xdata int offsetQ = 0;
//	xdata const unsigned short addrs[] =  {0x010D, 0x0119, 0x0082, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x0400, 0x010E, 0x0400, 0x0403, 0x040A, 0x040C };
//	xdata const unsigned short masks[] =  {0x0040, 0x8000, 0xFFFF, 0x001F, 0x0005, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xE001, 0x1FFF, 0x6001, 0x7000, 0x3000, 0x00BF };
//	xdata const unsigned short values[] = {0x0040, 0x0000, 0x8001, 0x0000, 0x0001, 0x4905, 0x0400, 0x0780, 0x0020, 0x0514, 0x1900, 0x067B, 0x2001, 0x0000, 0x0001, 0x7000, 0x2000, 0x00BF };
	bool iqselect = 0;
    //Stage 1
    if(config)
    {
        BackupRegisters(dcrxrssi_backupRegs, dcrxrssi_backupData, 0, dcrxrssiBACKUP_REG_COUNT-1);
        //Stage 2
        //Modify_SPI_Reg_mask(addrs, masks, values, 0, 13);

        //RFE
        Modify_SPI_Reg_bits(0x010D, 6, 6, 1);
        Modify_SPI_Reg_bits(0x010D, 4, 1, 0xFF);

        //RBB
        Modify_SPI_Reg_bits(0x0115, 15, 14, 0);
        Modify_SPI_Reg_bits(0x0119, 15, 15, 0);

        //AFE
        for(int addr=0x0082; addr<=0x0082; ++addr)
        {
            int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
            Modify_SPI_Reg_bits(addr, 15, 0, defVal);
        }
        //if(ch == 2) must be on for FFT
            Modify_SPI_Reg_bits(0x0082, 3, 3, 0);

        //BIAS
        //Modify_SPI_Reg_bits(0x0084, 4, 0, 0);
        //BIAS
        unsigned short backup = Get_SPI_Reg_bits(0x0084, 10, 6);
        for(int addr=0x0083; addr<=0x0084; ++addr)
        {
            int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
            Modify_SPI_Reg_bits(addr, 15, 0, defVal);
        }
        Modify_SPI_Reg_bits(0x0084, 10, 6, backup); //RP_CALIB_BIAS

        //XBUF
        Modify_SPI_Reg_bits(0x0085, 2, 2, 0);
        Modify_SPI_Reg_bits(0x0085, 1, 1, 0);

        //clkgen
        //reset CGEN to defaults
        for(int addr=0x0086; addr<=0x008C; ++addr)
        {
            int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
            Modify_SPI_Reg_bits(addr, 15, 0, defVal);
        }
        //power up VCO
        Modify_SPI_Reg_bits(0x0086, 2, 2, 0);
        if(SetFrequencyCGEN(REF_CLK_MHZ, cgen_freq) != 0)	//comparators are being checked
        {
            RestoreRegisters(dcrxrssi_backupRegs, dcrxrssi_backupData, 0, dcrxrssiBACKUP_REG_COUNT-1);
            return -3;
        }

        //RXTSP
        Modify_SPI_Reg_bits(0x0400, 0, 0, 1); //EN_RXTSP 1
        Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1); //AGC_MODE 1
        Modify_SPI_Reg_bits(0x040C, 7, 7, 0x1); //CMIX_BYP 1
        Modify_SPI_Reg_bits(0x040C, 6, 6, 0x0); //AGC_BYP 0
        Modify_SPI_Reg_bits(0x040C, 5, 5, 1); //
        Modify_SPI_Reg_bits(0x040C, 4, 4, 1); //
        Modify_SPI_Reg_bits(0x040C, 3, 3, 1); //
        Modify_SPI_Reg_bits(0x040C, 2, 2, 1); // DC_BYP
        Modify_SPI_Reg_bits(0x040C, 1, 1, 0); //
        Modify_SPI_Reg_bits(0x040C, 0, 0, 1); //

        Modify_SPI_Reg_bits(defSPI_CAPSEL, 0);

        Modify_SPI_Reg_bits(defSPI_AGC_AVG, 0x7); //agc_avg iq corr
    }
    xdata unsigned short requiredRegs[] = {0x0400, 0x040A, 0x010D, 0x040C};
    xdata unsigned short requiredMask[] = {0x6000, 0x3007, 0x0040, 0x00FF};
    xdata unsigned short requiredValue[] ={0x0000, 0x1007, 0x0040, 0x00BD};
    Modify_SPI_Reg_mask(requiredRegs, requiredMask, requiredValue, 0, 3);
    //Modify_SPI_Reg_bits(defSPI_CAPSEL, 0); //capsel rssi
    //Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1); //agc mode RSSI
    //Modify_SPI_Reg_bits(0x040C, 7, 0, 0xBF); //GFIR, DC, PHASE, CMIX bypass

    //Modify_SPI_Reg_bits(defSPI_AGC_AVG, 0x7);
    //Modify_SPI_Reg_bits(defSPI_EN_DCOFF_RXFE_RFE, 1);

    //Set_DCOFF(offsetI,offsetQ);
    for(int i=0; i<6; ++i)
    {
        newRSSI = FindMinRSSI(defSPI_DCOFFI_RFE, offsetI, &offsetI, 3, 2, 32>>i);
        newRSSI = FindMinRSSI(defSPI_DCOFFQ_RFE, offsetQ, &offsetQ, 3, 2, 32>>i);
    }

    globMinI = offsetI;
    globMinQ = offsetQ;
    char ctemp[256];
    //Stage 4
    if(config)
    {
        RestoreRegisters(dcrxrssi_backupRegs, dcrxrssi_backupData, 0, dcrxrssiBACKUP_REG_COUNT-1);
        Modify_SPI_Reg_bits(defSPI_EN_DCOFF_RXFE_RFE, 1);
    }
    Modify_SPI_Reg_bits(defSPI_EN_DCOFF_RXFE_RFE, 1);
    Set_DCOFF(globMinI,globMinQ);
    Modify_SPI_Reg_bits(0x040C, 2, 2, 0); // DC_BYP
    if(resultI)
        *resultI = globMinI;
    if(resultQ)
        *resultQ = globMinQ;
    cout << "\t\tRX DC TIME: " << getMilis()-t1 << " ms" << endl;
    sprintf(ctemp, "0x%06X", minRSSI);
    cout << "RX DC calibration step: " << 0 << "  offsetI: " << offsetI << "  offsetQ: " << offsetQ << "  RSSI: " << ctemp << endl;
    MessageLog::getInstance()->write("Rx DC calibration finished\n", LOG_INFO);

    return 0x0;
}*/

int Algorithms::DCCalibrationRX_RSSI(char config)
{
    unsigned long t1 = getMilis();
	xdata int i;
	xdata unsigned short backup;
    xdata int offsetI = 0;
    xdata int offsetQ = 0;
	xdata unsigned short requiredRegs[] = {0x0400, 0x040A, 0x010D, 0x040C};
    xdata unsigned short requiredMask[] = {0x6000, 0x3007, 0x0040, 0x00FF}; //CAPSEL, AGC_MODE, AGC_AVG, EN_DCOFF, Bypasses
    xdata unsigned short requiredValue[] ={0x0000, 0x1007, 0x0040, 0x00BD};
    //Stage 1
    if(config)
    {
        BackupRegisters(dcrxrssi_backupRegs, dcrxrssi_backupData, 0, dcrxrssiBACKUP_REG_COUNT-1);
        //Stage 2
        //RFE
        Modify_SPI_Reg_bits(0x010D, 6, 6, 1);
        Modify_SPI_Reg_bits(0x010D, 4, 1, 0xF);

        //RBB
        Modify_SPI_Reg_bits(0x0115, 15, 14, 0);
        Modify_SPI_Reg_bits(0x0119, 15, 15, 0);

        //AFE
		SetDefaults(AFE_ADDRESSES);
        //if(ch == 2) must be on for FFT
            Modify_SPI_Reg_bits(0x0082, 3, 3, 0);

        //BIAS
        backup = Get_SPI_Reg_bits(0x0084, 10, 6);
		SetDefaults(BIAS_ADDRESSES);
        Modify_SPI_Reg_bits(0x0084, 10, 6, backup); //RP_CALIB_BIAS

        //XBUF
        Modify_SPI_Reg_bits(0x0085, 2, 1, 0);

        //clkgen
        //reset CGEN to defaults
		SetDefaults(CGEN_ADDRESSES);

        //RXTSP
        Modify_SPI_Reg_bits(0x0400, 0, 0, 1); //EN_RXTSP 1
        Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1); //AGC_MODE 1
		Modify_SPI_Reg_bits(0x040C, 7, 0, 0xBD); // CMIX_BYP 1, AGC_BYP 0, DC_BYP 1, GFIR_BYP 1, GC_BYP 0...

        Modify_SPI_Reg_bits(defSPI_CAPSEL, 0);
        Modify_SPI_Reg_bits(defSPI_AGC_AVG, 0x7); //agc_avg iq corr

		if(SetFrequencyCGEN(REF_CLK_MHZ, cgen_freq) != 0)	//comparators are being checked
        {
            RestoreRegisters(dcrxrssi_backupRegs, dcrxrssi_backupData, 0, dcrxrssiBACKUP_REG_COUNT-1);
            return -3;
        }
    }
    Modify_SPI_Reg_mask(requiredRegs, requiredMask, requiredValue, 0, 3);
    for(i=0; i<6; ++i)
    {
        FindMinRSSI(defSPI_DCOFFI_RFE, offsetI, &offsetI, 3, 2, 32>>i);
        FindMinRSSI(defSPI_DCOFFQ_RFE, offsetQ, &offsetQ, 3, 2, 32>>i);
    }

    //Stage 4
    if(config)
        RestoreRegisters(dcrxrssi_backupRegs, dcrxrssi_backupData, 0, dcrxrssiBACKUP_REG_COUNT-1);

    Modify_SPI_Reg_bits(defSPI_EN_DCOFF_RXFE_RFE, 1);
    Set_DCOFF(offsetI,offsetQ);
    Modify_SPI_Reg_bits(0x040C, 2, 2, 0); // DC_BYP
    cout << "\t\tRX DC TIME: " << getMilis()-t1 << " ms" << endl;
    MessageLog::getInstance()->write("Rx DC calibration finished\n", LOG_INFO);
    return 0x0;
}



void Algorithms::ReadRSSIField(int minI, int maxI, int stepI, int minQ, int maxQ, int stepQ, int avgCnt)
{
    fstream *foutStep = new fstream[avgCnt];
    fstream fout;
    fstream foutHex;
    fout.open("txRSSIavg.txt", ios::out);
    foutHex.open("txRSSIavgHex.txt", ios::out);
    for(int i=0; i<avgCnt; ++i)
    {
        char ctemp[512];
        sprintf(ctemp, "txRSSI%i.txt", i);
        foutStep[i].open(ctemp, ios::out);
    }
    int progress = 0;
    int steps = ((maxI-minI)/stepI)*((maxQ-minQ)/stepQ);
    Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1);
    Modify_SPI_Reg_bits(defSPI_CAPTURE, 0);
    Modify_SPI_Reg_bits(defSPI_CAPSEL, 0);
    for(int i=minI; i<=maxI; i+=stepI)
    {
        for(int j=minQ; j<maxQ; j+=stepQ)
        {
            short currentValue = i;
            Modify_SPI_Reg_bits(defSPI_DCCORRI_TXTSP, currentValue);
            //set Q
            currentValue = j;
            Modify_SPI_Reg_bits(defSPI_DCCORRQ_TXTSP, currentValue);

            float sum = 0;
            for(int j=0; j<avgCnt; ++j)
            {
                Modify_SPI_Reg_bits(defSPI_CAPTURE, 1);
                Modify_SPI_Reg_bits(defSPI_CAPTURE, 0);
                int rssi = (Get_SPI_Reg_bits(0x040F, 15, 0) << 2) | Get_SPI_Reg_bits(0x040E, 1, 0);
                foutStep[j] << rssi << "\t";
                sum += rssi;
            }
            fout << sum/avgCnt << "\t";
            char ctemp[512];
            sprintf(ctemp, "0x%05X\t", (((int)sum)/avgCnt));
            foutHex << ctemp;
            ++progress;

            if((progress & 0x1F) == 0)
            {
                char ctemp[512];
                sprintf(ctemp, "RSSI Field: %i/%i\n", progress,steps);
                MessageLog::getInstance()->write(ctemp, LOG_INFO);
            }
        }
        fout << endl;
        foutHex << endl;
        for(int j=0; j<avgCnt; ++j)
            foutStep[j] << endl;
    }
    for(int i=0; i<avgCnt; ++i)
        foutStep[i].close();
    MessageLog::getInstance()->write("RSSI Field: finished\n", LOG_INFO);
    fout.close();
    foutHex.close();
	delete []foutStep;
}

const short rfe_beg = 0x010C;
const short rfe_end = 0x0114;

int Algorithms::TXIQCalibration_setup()
{
    //for redboard
    //Modify_SPI_Reg_bits(0x0093, 6, 6, 1);
    //Modify_SPI_Reg_bits(0x0092, 9, 9, 1);
    //Stage 2
    int ch = Get_SPI_Reg_bits(defSPI_MAC);
    int sel_band1_trf = Get_SPI_Reg_bits(0x0103, 11, 11);
    int sel_band2_trf = Get_SPI_Reg_bits(0x0103, 10, 10);

    //rfe
    //set defaults
    //reset RFE to defaults



    for(int addr=rfe_beg; addr<=rfe_end; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }

    if(sel_band1_trf == 1)
        Modify_SPI_Reg_bits(defSPI_SEL_PATH_RFE, 3); //SEL_PATH_RFE 3
    else if(sel_band2_trf == 1)
        Modify_SPI_Reg_bits(defSPI_SEL_PATH_RFE, 2);

    if(ch == 2)
        Modify_SPI_Reg_bits(defSPI_EN_NEXTTX_RFE, 1); // EN_NEXTTX_RFE 0

    Modify_SPI_Reg_bits(defSPI_G_RXLOOPB_RFE, 15); //G_RXLOOPB_RFE 15
    Modify_SPI_Reg_bits(0x010C, 4, 3, 0); //PD_MXLOBUF_RFE 0, PD_QGEN_RFE 0
    Modify_SPI_Reg_bits(defSPI_CCOMP_TIA_RFE, 6); //CCOMP_TIA_RFE 3
    Modify_SPI_Reg_bits(defSPI_CFB_TIA_RFE, 510); //CFB_TIA_RFE 246
    Modify_SPI_Reg_bits(0x0110, 4, 0, 31); //ICT_LO_RFE 31

    //RBB
    //reset RBB to defaults
    for(int addr=0x0115; addr<=0x011A; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }

    //Modify_SPI_Reg_bits(0x0115, 3, 3, 1); //PD_LPFH_RBB 1
    Modify_SPI_Reg_bits(0x0115, 2, 2, 0); //PD_LPFL_RBB 0
    //Modify_SPI_Reg_bits(defSPI_INPUT_CTL_PGA_RBB, 0); //INPUT_CTL_PGA_RBB 1
    //Modify_SPI_Reg_bits(defSPI_RCC_CTL_LPFH_RBB, 1); //RCC_CTL_LPFH_RBB 1
    Modify_SPI_Reg_bits(defSPI_RCC_CTL_LPFL_RBB, 3); //RCC_CTL_LPFL_RBB 4
    //Modify_SPI_Reg_bits(defSPI_C_CTL_LPFH_RBB, 111); //C_CTL_LPFH_RBB 111
    Modify_SPI_Reg_bits(defSPI_C_CTL_LPFL_RBB, 224); //C_CTL_LPFL_RBB 61
    Modify_SPI_Reg_bits(defSPI_G_PGA_RBB, 31); //G_PGA_RBB 22

    //TRF
    //reset TRF to defaults
//    for(int addr=0x0100; addr<=0x0104; ++addr)
//    {
//        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
//        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
//    }
    Modify_SPI_Reg_bits(defSPI_L_LOOPB_TXPAD_TRF, 0); //L_LOOPB_TXPAD_TRF 0 //!!!
    Modify_SPI_Reg_bits(defSPI_EN_LOOPB_TXPAD_TRF, 1); //EN_LOOPB_TXPAD_TRF 1
    Modify_SPI_Reg_bits(defSPI_EN_G_TRF, 0); //EN_G_TRF 0
    if(ch == 2)
        Modify_SPI_Reg_bits(defSPI_EN_NEXTTX_TRF, 1); //EN_NEXTTX_TRF 1
    Modify_SPI_Reg_bits(defSPI_LOSS_LIN_TXPAD_TRF, 0); //LOSS_LIN_TXPAD_TRF 5
    Modify_SPI_Reg_bits(defSPI_LOSS_MAIN_TXPAD_TRF, 0); //LOSS_MAIN_TXPAD_TRF 5

    //TBB
    //reset TBB to defaults
/*    for(int addr=0x0105; addr<=0x010A; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    Modify_SPI_Reg_bits(defSPI_CG_IAMP_TBB, 9); //CG_IAMP_TBB 9
    Modify_SPI_Reg_bits(defSPI_ICT_IAMP_FRP_TBB, 1); //ICT_IAMP_FRP_TBB 1
    Modify_SPI_Reg_bits(defSPI_ICT_IAMP_GG_FRP_TBB, 6); //ICT_IAMP_GG_FRP_TBB 6
    Modify_SPI_Reg_bits(defSPI_RCAL_LPFH_TBB, 125); //RCAL_LPFH_TBB 0
*/
    //AFE
    //reset AFE to defaults
    int isel_dac_afe = Get_SPI_Reg_bits(0x0082, 15, 13);
    for(int addr=0x0082; addr<=0x0082; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    Modify_SPI_Reg_bits(0x0082, 3, 3, 0); //PD_RX_AFE2 0
    Modify_SPI_Reg_bits(0x0082, 15, 13, isel_dac_afe);

    if(ch == 2)
    {
        Modify_SPI_Reg_bits(defSPI_PD_TX_AFE2, 0);
    }
    //BIAS
    unsigned short backup = Get_SPI_Reg_bits(0x0084, 10, 6);
    for(int addr=0x0083; addr<=0x0084; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    Modify_SPI_Reg_bits(0x0084, 10, 6, backup); //RP_CALIB_BIAS

    //XBUF
    Modify_SPI_Reg_bits(0x0085, 2, 0, 1); //PD_XBUF_RX 0, PD_XBUF_TX 0, EN_G_XBUF 1

    //CGEN
    //reset CGEN to defaults
    for(int addr=0x0086; addr<=0x008C; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    //power up VCO
    Modify_SPI_Reg_bits(0x0086, 2, 2, 0);

    if(SetFrequencyCGEN(REF_CLK_MHZ, cgen_freq) != 0)
        return -1;

    //SXR
    Modify_SPI_Reg_bits(defSPI_MAC, 1);
    for(int addr=0x011C; addr<=0x0124; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    float SXTfreqMHz = GetFrequencySX(false);

    float freqDiff = 4;

    float sxrFreq = SXTfreqMHz-freqDiff;
    if(SetFrequency(true, REF_CLK_MHZ, sxrFreq) != 0)
        return -1;

    //SXT
    Modify_SPI_Reg_bits(defSPI_MAC, 2);
    Modify_SPI_Reg_bits(defSPI_PD_LOCH_t2RBUF, 1); //PD_LOCH_t2RBUF 1
    if(SetFrequency(false, REF_CLK_MHZ, SXTfreqMHz) != 0)
        return -1;
    Modify_SPI_Reg_bits(defSPI_MAC, ch);

    //TXTSP
    for(int addr=0x0200; addr<=0x020C; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    Modify_SPI_Reg_bits(0x0200, 3, 2, 0x3); //TSGMODE 1, INSEL 1
    //Modify_SPI_Reg_bits(0x0208, 6, 4, 0xFFFF); //GFIR3_BYP 1, GFIR2_BYP 1, GFIR1_BYP 1
    Modify_SPI_Reg_bits(0x0208, 6, 6, 1); //GFIR3_BYP 1, GFIR2_BYP 1, GFIR1_BYP 1
    Modify_SPI_Reg_bits(0x0208, 5, 5, 1); //GFIR3_BYP 1, GFIR2_BYP 1, GFIR1_BYP 1
    Modify_SPI_Reg_bits(0x0208, 4, 4, 1); //GFIR3_BYP 1, GFIR2_BYP 1, GFIR1_BYP 1
    Modify_SPI_Reg_bits(defSPI_DC_REG_TXTSP, 0x0);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDI_TXTSP, 0);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDI_TXTSP, 1);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDI_TXTSP, 0);
    Modify_SPI_Reg_bits(defSPI_DC_REG_TXTSP, 0x0);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDQ_TXTSP, 0);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDQ_TXTSP, 1);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDQ_TXTSP, 0);
    Set_NCO_Freq(5, gRefClkTxTSP, false);

    //RXTSP
    for(int addr=0x0400; addr<=0x040C; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1); //AGC_MODE 1
    Modify_SPI_Reg_bits(0x040C, 7, 7, 0x1); //CMIX_BYP 1
    Modify_SPI_Reg_bits(0x040C, 6, 6, 0x0); //AGC_BYP 0
    Modify_SPI_Reg_bits(0x040C, 5, 5, 1); //
    Modify_SPI_Reg_bits(0x040C, 4, 4, 1); //
    Modify_SPI_Reg_bits(0x040C, 3, 3, 1); //
    Modify_SPI_Reg_bits(0x040C, 2, 2, 1); // DC_BYP
    Modify_SPI_Reg_bits(0x040C, 1, 1, 1); //
    Modify_SPI_Reg_bits(0x040C, 0, 0, 1); //

    Modify_SPI_Reg_bits(defSPI_CAPSEL, 0);
    Modify_SPI_Reg_bits(0x0403, 14, 12, 0); //Decimation HBD ratio

    Modify_SPI_Reg_bits(defSPI_AGC_AVG, 0x7); //agc_avg iq corr


    return 0;
}

//#define USE_MCU

int Algorithms::TXIQCalibration()
{
    unsigned long t1 = getMilis();
    map<unsigned short, MemoryRegister> registersStash[2];
    registersStash[0] = lmsControl->getRegistersMap()->StashRegisters(0);
    registersStash[1] = lmsControl->getRegistersMap()->StashRegisters(1);

    int iqcorr = 0;
    int gcorrq = 0;
    int gcorri = 0;

    int ch = Get_SPI_Reg_bits(defSPI_MAC);
    //Stage 1
    int sel_band1_trf = Get_SPI_Reg_bits(0x0103, 11, 11);
    int sel_band2_trf = Get_SPI_Reg_bits(0x0103, 10, 10);
    bool config = true;
    if(config)
        if(TXIQCalibration_setup())
            return -1;

    Modify_SPI_Reg_bits(0x0208, 6, 4, 0xF);
    Modify_SPI_Reg_bits(0x040C, 5,0, 0xFF);

    bool skip = false;
    if(skip)
        return 0;

    //Stage 3
    //A
#ifdef USE_MCU
    CallMCU(1);
    if(WaitForMCU() != 0)
        return -4;
#else
    DCCalibrationRX_RSSI(false);
    sel_band1_trf = Get_SPI_Reg_bits(0x0103, 11, 11);
    sel_band2_trf = Get_SPI_Reg_bits(0x0103, 10, 10);
    //DCCalibrationRX(false);
#endif
    if(skip)
        return 0;

    Modify_SPI_Reg_bits(0x010D, 6, 6, 1); //EN_DCOFF_RXFE
    Modify_SPI_Reg_bits(0x040c, 2, 2, 0); //DC_BYP
    //B
    Modify_SPI_Reg_bits(0x0100, 0, 0, 1); //EN_G_TRF 1
    if(sel_band1_trf == 1)
        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_1_RFE, 0); //PD_RLOOPB_1_RFE 0

    if(sel_band2_trf == 1)
        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_2_RFE, 0); //PD_RLOOPB_2_RFE 0


    if(sel_band1_trf == 1)
        Modify_SPI_Reg_bits(defSPI_EN_INSHSW_LB1, 0); //EN_INSHSW_LB1 0

    if(sel_band2_trf == 1)
        Modify_SPI_Reg_bits(defSPI_EN_INSHSW_LB2, 0); // EN_INSHSW_LB2 0


    //Modify_SPI_Reg_bits(defSPI_AGC_AVG, 0); //agc_avg iq corr
    //C
#ifdef USE_MCU
    CallMCU(2);
    if(WaitForMCU() != 0)
        return -5;
#else
    //C
    Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1);
    Modify_SPI_Reg_bits(defSPI_CAPSEL, 0);
    if(skip)
        return 0;

   //Modify_SPI_Reg_bits(defSPI_AGC_AVG, 7); //AGC_AVG iq corr
    int rxstatus = FixRXSaturation();
    DCCalibrationTX_RFLOOP(false);
    unsigned int dccorri = Get_SPI_Reg_bits(defSPI_DCCORRI_TXTSP);
    unsigned int dccorrq = Get_SPI_Reg_bits(defSPI_DCCORRQ_TXTSP);
   // Modify_SPI_Reg_bits(defSPI_AGC_AVG, 0); //AGC_AVG iq corr
#endif // USE_MCU

    if(skip)
        return 0;

    //D
    float ncofreq = 5.0;
    Set_NCO_Freq(ncofreq, gRefClkTxTSP, false);
    Modify_SPI_Reg_bits(0x020C, 15, 0, 0x7FFF);
    Modify_SPI_Reg_bits(0x0200, 5, 5, 0);
    Modify_SPI_Reg_bits(0x0200, 5, 5, 1);
    Modify_SPI_Reg_bits(0x0200, 5, 5, 0);
    Modify_SPI_Reg_bits(0x020C, 15, 0, 0x8000);
    Modify_SPI_Reg_bits(0x0200, 6, 6, 0);
    Modify_SPI_Reg_bits(0x0200, 6, 6, 1);
    Modify_SPI_Reg_bits(0x0200, 6, 6, 0);
    Modify_SPI_Reg_bits(0x0200, 2, 2, 1); //INSEL 1

    float SXTfreqMHz = GetFrequencySX(false);

    float freqDiff2 = 6;

    double sxrFreq = SXTfreqMHz-freqDiff2;
    if(SetFrequency(true, REF_CLK_MHZ, sxrFreq) != 0)
        return -1;

    //Modify_SPI_Reg_bits(defSPI_CCOMP_TIA_RFE, 2); //CCOMP_TIA_RFE 2
    //Modify_SPI_Reg_bits(defSPI_CFB_TIA_RFE, 66); //CFB_TIA_RFE 66
    //Modify_SPI_Reg_bits(0x0115, 3, 2, 1); //PD_LPFH_RBB 0, PD_LPFL_RBB 1
    //Modify_SPI_Reg_bits(defSPI_INPUT_CTL_PGA_RBB, 1); //INPUT_CTL_PGA_RBB 1
    //Modify_SPI_Reg_bits(defSPI_LOSS_LIN_TXPAD_TRF, 0); //LOSS_LIN_TXPAD_TRF 1
    //Modify_SPI_Reg_bits(defSPI_LOSS_MAIN_TXPAD_TRF, 0); //LOSS_MAIN_TXPAD_TRF 1

    //E
    /*Modify_SPI_Reg_bits(defSPI_EN_G_TRF, 0); //EN_G_TRF 0
    Modify_SPI_Reg_bits(0x040c, 2, 2, 1); //DC_BYP
    Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_1_RFE, 1); //PD_RLOOPB_1_RFE 1
    Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_2_RFE, 1); //PD_RLOOPB_2_RFE 1
    if(skip)
        return 0;
        */

    //F
#ifdef USE_MCU
    CallMCU(1);
    if(WaitForMCU() != 0)
        return -4;
#else
    //DCCalibrationRX_RSSI(false);
    //DCCalibrationRX(false);
#endif
    //Modify_SPI_Reg_bits(0x010D, 6, 6, 1); //EN_DCOFF_RXFE 1
    //Modify_SPI_Reg_bits(0x040c, 2, 2, 0); //DC_BYP
    //G
    //Modify_SPI_Reg_bits(defSPI_EN_G_TRF, 1); //EN_G_TRF 1
//    if(sel_band1_trf == 1)
//        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_1_RFE, 0); //PD_RLOOPB_1_RFE 0
//
//    if(sel_band2_trf == 1)
//        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_2_RFE, 0); //PD_RLOOPB_2_RFE 0

    if(skip)
        return 0;
    //H.a

    //H.c

    rxstatus = FixRXSaturation();

    //Modify_SPI_Reg_bits(defSPI_L_LOOPB_TXPAD_TRF, 0); //L_LOOPB_TXPAD_TRF 0
    //Modify_SPI_Reg_bits(defSPI_AGC_AVG, 7); //AGC_AVG iq corr

    Modify_SPI_Reg_bits(defSPI_GCORRI_TXTSP, 2047);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_TXTSP, 2047);

    //cout << "IQ CORR:  PHASE" << endl;
    //MessageLog::getInstance()->write("IQ correction: phase\n", LOG_INFO);
    iqcorr = 0;
    unsigned long minRSSI = ~0;
    int miniqcorr = 0;
    iqcorr = miniqcorr;
    unsigned long minRSSI_iq = ~0-1;

    Modify_SPI_Reg_bits(defSPI_IQCORR_TXTSP, iqcorr);

    minRSSI = ~0;
    int mingcorri = 2047;
    gcorri = mingcorri-512;
    unsigned long minRSSI_i = ~0-1;
    cout << "TX IQ CORRR:  I GAIN" << endl;
    MessageLog::getInstance()->write("IQ correction: I gain\n", LOG_INFO);
    for(int i=0; i<9; ++i)
    {
        minRSSI_i = FindMinRSSI(defSPI_GCORRI_TXTSP, gcorri, &gcorri, 3, 0, 256>>i);
    }

    Modify_SPI_Reg_bits(defSPI_GCORRI_TXTSP, 2047);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_TXTSP, 2047);

    cout << "TX IQ CORR:  Q GAIN" << endl;
    MessageLog::getInstance()->write("IQ correction: Q gain\n", LOG_INFO);
    minRSSI = ~0;
    int mingcorrq = 2047-512;
    gcorrq = mingcorrq;
    unsigned long minRSSI_q = ~0-1;
    for(int i=0; i<9; ++i)
    {
        minRSSI_q = FindMinRSSI(defSPI_GCORRQ_TXTSP, gcorrq, &gcorrq, 3, 0, 256>>i);
    }

    if(minRSSI_i < minRSSI_q)
        gcorrq = 2047;
    else
        gcorri = 2047;


    Modify_SPI_Reg_bits(defSPI_GCORRI_TXTSP, gcorri);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_TXTSP, gcorrq);

    cout << "TX IQ CORR:  PHASE" << endl;
    MessageLog::getInstance()->write("IQ correction: phase\n", LOG_INFO);
    minRSSI = ~0;
    iqcorr = miniqcorr;
    for(int i=0; i<9; ++i)
    {
        minRSSI_iq = FindMinRSSI(defSPI_IQCORR_TXTSP, iqcorr, &iqcorr, 3, 1, 256>>i);
    }

    Modify_SPI_Reg_bits(defSPI_GCORRI_TXTSP, gcorri);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_TXTSP, gcorrq);
    Modify_SPI_Reg_bits(defSPI_IQCORR_TXTSP, iqcorr);

//    // Stage 4
    lmsControl->getRegistersMap()->RestoreRegisters(0, registersStash[0]);
    lmsControl->getRegistersMap()->RestoreRegisters(1, registersStash[1]);
    lmsControl->getRegistersMap()->UploadAll();
    lmsControl->UploadAll();

    Modify_SPI_Reg_bits(defSPI_MAC, ch);
    Modify_SPI_Reg_bits(defSPI_DCCORRI_TXTSP, dccorri);
    Modify_SPI_Reg_bits(defSPI_DCCORRQ_TXTSP, dccorrq);
    Modify_SPI_Reg_bits(defSPI_GCORRI_TXTSP, gcorri);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_TXTSP, gcorrq);
    Modify_SPI_Reg_bits(defSPI_IQCORR_TXTSP, iqcorr);

    Modify_SPI_Reg_bits(0x0208, 3, 3, 0); //DC_BYP
    Modify_SPI_Reg_bits(0x0208, 1, 0, 0); //GC_BYP PH_BYP

    cout << "TX/RX IQ correction TIME: " << getMilis()-t1 << " ms" << endl;

    return 0;
}

/** @brief Performs Gradient search for minimum RSSI while changing two parameters
    @return minimal found RSSI value

    parameters are treated as two's complement
*/
unsigned long Algorithms::FindMinRSSI2(const unsigned short adr1, const char msb1, const char lsb1, const unsigned short adr2, const char msb2, const char lsb2, int &result1, int &result2)
{
    unsigned int minRSSI = ~0;
    int avgCount = 8;
    const int stepCount = 5;
    const int rssiCount = 2*stepCount+1;
    unsigned int rssiField[rssiCount];
    int minRSSIindex = 0;
    int iteration = 0;

    Modify_SPI_Reg_bits(adr1, msb1, lsb1, 0);
    Modify_SPI_Reg_bits(adr2, msb2, lsb2, 0);

    int maxVal1 = (~(~0x0 << (msb1-lsb1+1)))/2;
    int minVal1 = -(~(~0x0 << (msb1-lsb1+1)))/2-1;
    int maxVal2 = (~(~0x0 << (msb2-lsb2+1)))/2;
    int minVal2 = -(~(~0x0 << (msb2-lsb2+1)))/2-1;

    int prevMin[2];
    prevMin[0] = 0;
    prevMin[1] = 0;
    int globMin[2];
    globMin[0] = 0;
    globMin[1] = 0;
    int min[2];
    min[0] = 0;
    min[1] = 0;

    stringstream ss;
    char ctemp[1024];
    bool iqSelect = false;
    int staleCounter = 0;
    int staleLimit = 4;
    do
    {
        ss.clear();
        ss.str(string());
        ss << endl;
        minRSSIindex = 0;
        while(minRSSIindex != rssiCount/2 && iteration < 256)
        {
            for(int i=0; i<rssiCount; ++i)
            {
                if(iqSelect == false) // I
                {
                    short currentValueI = min[0]+i-rssiCount/2;
                    if(currentValueI < minVal1)
                        currentValueI = minVal1;
                    else if(currentValueI > maxVal1)
                        currentValueI = maxVal1;
                    Modify_SPI_Reg_bits(adr1, msb1, lsb1, currentValueI);
                    ss << "I: " << currentValueI << "  Q: " << min[1];
                }
                else //Q
                {
                    short currentValueQ = min[1]+i-rssiCount/2;
                    if(currentValueQ < minVal2)
                        currentValueQ = minVal2;
                    else if(currentValueQ > maxVal2)
                        currentValueQ = maxVal2;
                    Modify_SPI_Reg_bits(adr2, msb2, lsb2, currentValueQ);
                    ss << "Q: " << currentValueQ << "  I: " << min[0];
                }

                int sum = 0;
                for(int j=0; j<avgCount; ++j)
                {
                    Modify_SPI_Reg_bits(0x0400, 15, 15, 1);
                    Modify_SPI_Reg_bits(0x0400, 15, 15, 0);
                    int rssi = (Get_SPI_Reg_bits(0x040F, 15, 0) << 2) | Get_SPI_Reg_bits(0x040E, 1, 0);
                    sum += rssi;
                }
                rssiField[i] = sum/avgCount;
                sprintf(ctemp, "  RSSI: 0x%05X", rssiField[i]);
                ss << ctemp << endl;
            }
            ss << endl;
            int minI = min[0];
            int minQ = min[1];
            MessageLog::getInstance()->write(ss.str().c_str(), LOG_INFO);
            cout << ss.str();
            ss.str(string());
            ss.clear();


            minRSSIindex = 0;
            bool minFound = false;
            for(int i=0; i<rssiCount; ++i)
                if(rssiField[i] < minRSSI)
                {
                    minRSSI = rssiField[i];
                    minRSSIindex = i;
                    if(iqSelect == false)
                        minI = min[0]+i-rssiCount/2;
                    else
                        minQ = min[1]+i-rssiCount/2;
                    globMin[0] = minI;
                    globMin[1] = minQ;
                    minFound = true;
                }
            min[0] = minI;
            min[1] = minQ;

            Modify_SPI_Reg_bits(adr1, msb1, lsb1, minI);
            Modify_SPI_Reg_bits(adr2, msb2, lsb2, minQ);
            ++iteration;
            if((iteration & 0x11) == 0)
            {
                wxYield();
                cout << "yield()" << endl;
            }

            if(minRSSIindex == rssiCount/2 || !minFound)
            {
                minRSSIindex = rssiCount/2;
                break;
            }
        }
        sprintf(ctemp, "step: %3i/256  Tx: OffsetI: %4i  OffsetQ: %4i  RSSI: 0x%05X\n", iteration, min[0], min[1], rssiField[minRSSIindex]);
        MessageLog::getInstance()->write(ctemp, LOG_INFO);
        cout << ctemp;
        sprintf(ctemp, "global Min was Tx: OffsetI: %4i  OffsetQ: %4i  RSSI: 0x%05X\n", globMin[0], globMin[1], minRSSI);
        MessageLog::getInstance()->write(ctemp, LOG_INFO);
        cout << ctemp;

        iqSelect = !iqSelect;
        if(prevMin[0] == min[0] && prevMin[1] == min[1])
            ++staleCounter;
        else
            staleCounter = 0;
        prevMin[0] = min[0];
        prevMin[1] = min[1];
        ++iteration;
    }while(iteration <= 256 && staleCounter < staleLimit);

    result1 = min[0];
    result2 = min[1];
    return minRSSI;
}

/**
* @param refClk_MHz reference clock, MHz
* @param dDF Desireg frequency, MHz
* @param Nint Integer division ratio (INT_SDM)
* @param Nfrac Fractional division ratio (FRAC_SDM)
* @param iVCO VCO index (SEL_VCO)
* @param Fvco VCO frequency, MHz
* @param iDInd Divider (real divider is 2^(iDInd+1)), (DIV_LOCH)
* @param iEnDiv2 Additional prescaler control (EN_DIV2_DIVPROG)
  @return
    - -2 frequency out of available range
    - -1 cannot deliver requested frequency
    - 0 success
*/
#define sxVCO_N 2
#define m_dThrF 5500
int Algorithms::SetFrequency(char Rx, float refClk_MHz, float freq_MHz)
{
	static xdata const float m_pdVCO[3][sxVCO_N] = {{3800, 5222}, {4961, 6754}, {6306, 7714}};
	xdata unsigned char ch = Get_SPI_Reg_bits(defSPI_MAC);
	xdata char i; //iDInd
	long lint, lfrac;

    xdata char dMul;
    xdata char iVCO;
    xdata float dFvco;

    //VCO selection
    //High VCO
	for(iVCO=2; iVCO>=0; --iVCO)
		for(i=6; i>=0; --i)
	        if((freq_MHz >= m_pdVCO[iVCO][0]/(1<<(i+1))) && (freq_MHz <= (m_pdVCO[iVCO][sxVCO_N-1]/(1<<(i+1)))))
	        {
	            dMul = 1<<(i+1);
				goto vco_found;
	        }
    vco_found:
    if(iVCO < 0)
        return -1;

    //Calculate VCO frequency
    dFvco = dMul * freq_MHz;
    //Additional presaler control
    lint = dFvco/(refClk_MHz * (1 << (dFvco > m_dThrF))) - 4;
    lfrac = (dFvco/(refClk_MHz * (1 << (dFvco > m_dThrF))) - (unsigned long)(dFvco/(refClk_MHz * (1 << (dFvco > m_dThrF))))) * (1 << 20);

    Modify_SPI_Reg_bits(defSPI_MAC, Rx ? 1 : 2);
    Modify_SPI_Reg_bits(0x0121, 2, 1, iVCO); //SEL_VCO
    Modify_SPI_Reg_bits(0x011E, 13, 4, lint); //INT_SDM
    Modify_SPI_Reg_bits(0x011D, 15, 0, lfrac & 0xFFFF); //FRAC_SDM[15:0]
    Modify_SPI_Reg_bits(0x011E, 3, 0, (lfrac >> 16)); //FRAC_SDM[19:16]
    Modify_SPI_Reg_bits(0x011F, 8, 6, i); //DIV_LOCH
    Modify_SPI_Reg_bits(0x011C, 10, 10, (dFvco > m_dThrF)); //EN_DIV2_DIVPROG
    Modify_SPI_Reg_bits(defSPI_MAC, ch);
    VCO_Tuning(Rx?1:2);
    return 0;
}

/**
* Calculates CGEN PLL parameters according to desired frequency.
* iHDiv is set to 1000 if it is not possible to deliver required frequency.
*
* @param[in] dDFH Desireg frequency, MHz
* @param[in] rdRF Real frequency according to parameters calculated, MHz
* @param[in] Nint Integer division ratio (INT_SDM)
* @param[in] Nfrac Fractional division ratio (FRAC_SDM)
* @param[in] Fvco VCO frequency, MHz
* @param[in] iHDiv Divider (real divider is 2^(DIV_OUTCH_CGEN+1)), (DIV_OUTCH_CGEN)
  @return
    - -1 cannot deliver requested frequency
    - 0 success
    - 1 requested frequency out of range, changed to closest available frequency
*/
#define cgenVCOn 2
const float cgenVCO[cgenVCOn] = {2000, 2700}; //CGEN VCO frequencies, MHz
int Algorithms::SetFrequencyCGEN(float refClk_MHz, float freq_MHz, unsigned long *Nint, unsigned long *Nfrac, char *pHdiv)
{
    xdata float dFvco;
    xdata float dFrac;
    xdata char canDeliver = 0;

    xdata unsigned long lfrac;
    xdata unsigned long lint;
    xdata short iHdiv;
	xdata float clkDAC = 0;
    xdata float clkADC = 0;
	xdata float realFreq_MHz;
	xdata float clklfreq;

    if (freq_MHz > cgenVCO[cgenVCOn-1]/2.0 || freq_MHz < cgenVCO[0]/512.0)
    {
        return -1;
    }

    //VCO frequency selection according to F_CLKH
    //Start from high dividers
    for(iHdiv=255; iHdiv>=0; --iHdiv)
    {
        //Calculate VCO frequency according to the divider
        dFvco = 2*(iHdiv+1) * freq_MHz;
        if ( (dFvco >= cgenVCO[0]) && (dFvco <= cgenVCO[cgenVCOn-1]) )
        {
            canDeliver = 1;
            break;
        }
    }

    //Check if it is possible to deliver required frequency
    if(canDeliver == 0)
        return -1;

    //Integer division
    lint = dFvco/refClk_MHz - 1;

    //Fractional division
    dFrac = dFvco/refClk_MHz - (unsigned long)(dFvco/refClk_MHz);
    lfrac = dFrac * (1 << 20);

    Modify_SPI_Reg_bits(0x0088, 13, 4, lint); //INT_SDM_CGEN
    Modify_SPI_Reg_bits(0x0087, 15, 0, lfrac&0xFFFF); //INT_SDM_CGEN[15:0]
    Modify_SPI_Reg_bits(0x0088, 3, 0, lfrac>>16); //INT_SDM_CGEN[19:16]
    Modify_SPI_Reg_bits(0x0089, 10, 3, iHdiv); //DIV_OUTCH_CGEN

    if(VCO_Tuning_CGEN() != 0)
		return -2;

    realFreq_MHz = GetFrequencyCGEN();
	clklfreq = realFreq_MHz/(1 << Get_SPI_Reg_bits(defSPI_CLKH_OV_CLKL_CGEN));
    //update TSP reference clocks
    if(Get_SPI_Reg_bits(defSPI_EN_ADCCLKH_CLKGN) == 0)
    {
        clkDAC = clklfreq;
        clkADC = realFreq_MHz;
    }
    else
    {
        clkDAC = realFreq_MHz;
        clkADC = clklfreq;
    }
    gRefClkTxTSP = clkDAC;
    gRefClkRxTSP = clkADC/4.0;

    return 0;
};

float Algorithms::GetFrequencySX(bool Rx)
{
    int ch = Get_SPI_Reg_bits(defSPI_MAC);
    Modify_SPI_Reg_bits(defSPI_MAC, Rx ? 1 : 2);
    unsigned long Nint, Nfrac;
    char div_loch = Get_SPI_Reg_bits(0x011F, 8, 6);
    char en_div2_divProg = Get_SPI_Reg_bits(0x011C, 10, 10);
    Nint = Get_SPI_Reg_bits(0x011E, 13, 4);
    Nfrac = Get_SPI_Reg_bits(0x011D, 15, 0);
    Nfrac |= Get_SPI_Reg_bits(0x011E, 3, 0) << 16;
    Modify_SPI_Reg_bits(defSPI_MAC, ch);

    float dMul = 1 << (div_loch+1);
    //Calculate real frequency according to the calculated parameters
    return REF_CLK_MHZ * (1.0/dMul) * (((double)Nint + (double)Nfrac/(double)(1 << 20)) + 4.0) * (double)(1 << en_div2_divProg);

}

float Algorithms::GetFrequencyCGEN()
{
    int dMul = 2*(Get_SPI_Reg_bits(0x0089, 10, 3)+1); //DIV_OUTCH_CGEN
    unsigned long Nint, Nfrac;
    Nint = Get_SPI_Reg_bits(0x0088, 13, 4);
    Nfrac = Get_SPI_Reg_bits(0x0087, 15, 0);
    Nfrac |= Get_SPI_Reg_bits(0x0088, 3, 0) << 16;
    //Calculate real frequency according to the calculated parameters
    float freq = REF_CLK_MHZ * (1.0/dMul) * (((double)Nint + (double)Nfrac/(double)pow(2, 20)) + 1.0);
    return freq;
}


/** @brief Searches for minimal RSSI value while changing given address bits
    @param startValue initial value where to start search
    @param result found minimal parameter value will be set here
    @param staleLimit number of iterations to confirm minimal value
    @param twoCompl varying parameter value is treated as two's complement
    @return found minimal RSSI value
*/


#define minRSSIstepSize 15
#define minRSSIcount 31
unsigned long Algorithms::FindMinRSSI(const unsigned short addr, const char msb, const char lsb, const int startValue, int *result, const char scanWidth, const char twoCompl, int stepMult)
{
    if(scanWidth < 1)
        return ~0;
	xdata int minI;
	xdata int min = startValue;
    xdata int globMin = 0;
    xdata unsigned long minRSSI = ~0;
    xdata unsigned int *rssiField = new unsigned int[scanWidth];
    xdata int minRSSIindex;
    xdata int i;
    xdata int maxVal;
    xdata int minVal = 0;
    if(twoCompl)
    {
        maxVal = (~(~0x0 << (msb-lsb+1)))/2;
        minVal = -(~(~0x0 << (msb-lsb+1)))/2-1;
    }
    else
        maxVal = (~(~0x0 << (msb-lsb+1)));

    Modify_SPI_Reg_bits(addr, msb, lsb, startValue);

    stringstream ss;
    char ctemp[1024];
    Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1);
    Modify_SPI_Reg_bits(defSPI_CAPSEL, 0);

    ss.clear();
    ss.str(string());
    ss << endl;
    minRSSIindex = 0;
    for(i=0; i<scanWidth; ++i)
    {
        short currentValue = min+(i-scanWidth/2)*stepMult;
        if(currentValue < minVal)
            currentValue = minVal;
        else if(currentValue > maxVal)
            currentValue = maxVal;
        if(twoCompl==2)
        {
            unsigned short valToSend = 0;
            if(currentValue < 0)
                valToSend |= 0x40;
            valToSend |= labs(currentValue);
            Modify_SPI_Reg_bits(addr, msb, lsb, valToSend);
        }
        else
            Modify_SPI_Reg_bits(addr, msb, lsb, currentValue);
        ss << "value: " << currentValue;

        flipCapture();
        rssiField[i] = (Get_SPI_Reg_bits(0x040F, 15, 0) << 2) | Get_SPI_Reg_bits(0x040E, 1, 0);
        //sprintf(ctemp, "  RSSI: 0x%05X", rssiField[i]);
        //ss << ctemp << endl;
    }
    //ss << endl;
    //MessageLog::getInstance()->write(ss.str().c_str(), LOG_INFO);
    //cout << ss.str();
    //ss.str(string());
    //ss.clear();

    minI = min;
    minRSSIindex = 0;
    for(i=0; i<scanWidth; ++i)
        if(rssiField[i] < minRSSI)
        {
            minRSSI = rssiField[i];
            minRSSIindex = i;
            minI = min+(i-scanWidth/2)*stepMult;
            if(minI > maxVal)
                minI = maxVal;
            else if(minI < minVal)
                minI = minVal;
            globMin = minI;
        }
    min = minI;

    Modify_SPI_Reg_bits(addr, msb, lsb, min);

//    sprintf(ctemp, "value: %4i  RSSI: 0x%05X \n", min, rssiField[minRSSIindex]);
//    MessageLog::getInstance()->write(ctemp, LOG_INFO);
//    cout << ctemp;
//    sprintf(ctemp, "global Min was at value: %4i  RSSI: 0x%05X\n", globMin, minRSSI);
//    MessageLog::getInstance()->write(ctemp, LOG_INFO);
//    cout << ctemp;

    *result = min;
    return minRSSI;
}

int Algorithms::DCCalibrationTX_PDET_config()
{
	xdata const unsigned short addrs[] =  {0x010C, 0x0115, 0x0118, 0x0119, 0x0100, 0x0082, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x0200, 0x0208, 0x020C, 0x0200, 0x0200, 0x0200, 0x0400, 0x0403, 0x040A, 0x040C/*ch2*/,0x0100, 0x0082};
	xdata const unsigned short masks[] =  {0x009B, 0x000F, 0xE000, 0x801F, 0x300F, 0x1FFF, 0x001F, 0x0007, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x000D, 0x0008, 0xFFFF, 0x0060, 0x0060, 0x0060, 0x6001, 0x7000, 0x3000, 0x00FF/*ch2*/,0x4000, 0x000A};
	xdata const unsigned short values[] = {0x009B, 0x000D, 0x8000, 0x000C, 0x3001, 0x800B, 0x0000, 0x0001, 0x4905, 0x0400, 0x0780, 0x0020, 0x0514, 0x1900, 0x067B, 0x000D, 0x0000, 0x0000, 0x0000, 0x0060, 0x0000, 0x0001, 0x7000, 0x1000, 0x00BF/*ch2*/,0x4000, 0x0000};
	xdata int status =0;
	char ch = Get_SPI_Reg_bits(defSPI_MAC);
	if(ch == 1)
        Modify_SPI_Reg_mask(addrs, masks, values, 0, 24);
    else if(ch == 2)
        Modify_SPI_Reg_mask(addrs, masks, values, 0, 26);

	status = SetFrequencyCGEN(REF_CLK_MHZ, cgen_freq); //comparators are being checked
	if(status != 0)
		return status;

//    if(Get_SPI_Reg_bits(0x008C, 13, 12) != 2)
//        return 0xAA;
    return 0;
}


#define txdcpdetBACKUP_REG_COUNT 22
int Algorithms::DCCalibrationTX_PDET()
{
	xdata unsigned short txpdet_backupRegs[] = {0x010C, 0x0115, 0x0118, 0x0119, 0x0100, 0x0082, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x0200, 0x0208, 0x020C, 0x0400, 0x0403, 0x040A, 0x040C};
	xdata unsigned short txpdet_backupData[txdcpdetBACKUP_REG_COUNT];
    xdata unsigned long minRSSI = ~0;
    xdata int corrI = 0;
    xdata int corrQ = 0;
    xdata int globMinI;
    xdata int globMinQ;
    xdata int staleCounter;
    xdata const int staleLimit = 4;
    xdata unsigned long newRSSI;
    xdata char iqselect = 0;
	xdata int status = 0;
	Modify_SPI_Reg_bits(0x0020, 1, 0, 1);
    //Stage 1
	BackupRegisters(txpdet_backupRegs, txpdet_backupData, 0, txdcpdetBACKUP_REG_COUNT-1);

    //Stage 2
	status = DCCalibrationTX_PDET_config();
    if(status != 0)
    {
		RestoreRegisters(txpdet_backupRegs, txpdet_backupData, 0, txdcpdetBACKUP_REG_COUNT-1);
     	return status;
    }

    //Modify_SPI_Reg_bits(defSPI_CAPSEL, 0);
    //flipCapture();

    int iteration = 0;
    while(staleCounter < staleLimit || (iteration % 2 !=0))
    {
        cout << "\nTX DC : " << (iqselect ? "Q" : "I" );
        if(iqselect == 0)
            newRSSI = FindMinRSSI(defSPI_DCCORRI_TXTSP, corrI, &corrI, 1, 1);
        else
            newRSSI = FindMinRSSI(defSPI_DCCORRQ_TXTSP, corrQ, &corrQ, 1, 1);
        if(newRSSI < minRSSI)
        {
            globMinI = corrI;
            globMinQ = corrQ;
            minRSSI = newRSSI;
            staleCounter = 0;
            //Modify_SPI_Reg_bits(defSPI_DCCORRI_TXTSP, globMinI);
            //Modify_SPI_Reg_bits(defSPI_DCCORRQ_TXTSP, globMinQ);
            char ctemp[512];
            sprintf(ctemp, "0x%06X", newRSSI);
            cout << "TX DC   " << "offsetI: " << corrI << "   offset Q: " << corrQ << "  RSSI: " << ctemp << endl;

        }
        else
            ++staleCounter;
        iqselect = !iqselect;
        iteration++;
    }



	/*staleCounter = 0;
    while(staleCounter < staleLimit)
    {
        if(iqselect == 0)
            newRSSI = FindMinRSSI(defSPI_DCCORRI_TXTSP, corrI, &corrI, 1, 1);
        else
            newRSSI = FindMinRSSI(defSPI_DCCORRQ_TXTSP, corrQ, &corrQ, 1, 1);

        if(newRSSI < minRSSI)
        {
            globMinI = corrI;
            globMinQ = corrQ;
            minRSSI = newRSSI;
            staleCounter = 0;
        }
        else
            ++staleCounter;
        iqselect = !iqselect;
    }*/
    RestoreRegisters(txpdet_backupRegs, txpdet_backupData, 0, txdcpdetBACKUP_REG_COUNT-1);

    Modify_SPI_Reg_bits(defSPI_DC_BYP_TXTSP, 0);
    Modify_SPI_Reg_bits(defSPI_DCCORRI_TXTSP, globMinI);
    Modify_SPI_Reg_bits(defSPI_DCCORRQ_TXTSP, globMinQ);
    return 0;
}

void Algorithms::LoadDCIQ(unsigned short I, unsigned short Q)
{
	Modify_SPI_Reg_bits(defSPI_DC_REG_TXTSP, I);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDI_TXTSP, 0);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDI_TXTSP, 1);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDI_TXTSP, 0);
    Modify_SPI_Reg_bits(defSPI_DC_REG_TXTSP, Q);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDQ_TXTSP, 0);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDQ_TXTSP, 1);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDQ_TXTSP, 0);
    Modify_SPI_Reg_bits(0x0208, 3, 3, 0);
}

#define txdcrflBACKUP_REG_COUNT sizeof(txrfl_backupRegs)/sizeof(unsigned short)
int Algorithms::DCCalibrationTX_RFLOOP(char config)
{
	//unsigned long t1 = getMilis();
    xdata unsigned short txrfl_backupRegs[] =
{
0x0082,
0x0084,
0x0085,
0x0086,
0x0087,
0x0088,
0x0089,
0x008A,
0x008B,
0x008C,
0x0100,
0x0101,
0x010C,
0x010D,
0x010E,
0x010F,
0x0110,
0x0111,
0x0112,
0x0113,
0x0114,
0x0115,
0x0116,
0x0117,
0x0118,
0x0119,
0x011A,
0x011C,
0x011D,
0x011E,
0x011F,
0x0120,
0x0121,
0x0122,
0x0123,
0x0124,
0x0200,
0x0204,
0x0208,
0x020C,
0x0400,
0x0403,
0x040A,
0x040C
};
	xdata unsigned short txrfl_backupData[txdcrflBACKUP_REG_COUNT];
	unsigned short tempRegData;
	char ch = Get_SPI_Reg_bits(0x0020, 1, 0);
	xdata char sel_band = Get_SPI_Reg_bits(0x0103, 11, 10);
	xdata int corrI = 0;
    xdata int corrQ = 0;
	xdata char i;

	if(config)
    {
        BackupRegisters(txrfl_backupRegs, txrfl_backupData, 0, txdcrflBACKUP_REG_COUNT-1);
        //RFE
        //reset RFE to defaults
        SetDefaults(RFE_ADDRESSES);

        if(sel_band == 1) //sel_band2 active
            Modify_SPI_Reg_bits(defSPI_SEL_PATH_RFE, 2);
		else
			Modify_SPI_Reg_bits(defSPI_SEL_PATH_RFE, 3);

        Modify_SPI_Reg_bits(defSPI_EN_NEXTTX_RFE, ch == 2);

        Modify_SPI_Reg_bits(defSPI_G_RXLOOPB_RFE, 15);
        Modify_SPI_Reg_bits(0x010C, 4, 3, 0); // PD_MXLOBUF, PD_QGEN
        Modify_SPI_Reg_bits(defSPI_CCOMP_TIA_RFE, 6); //6
        Modify_SPI_Reg_bits(defSPI_CFB_TIA_RFE, 510); //510
        Modify_SPI_Reg_bits(0x0110, 4, 0, 31); //ICT_LODC_RFE

        //RBB
        //reset RBB to defaults
        SetDefaults(RBB_ADDRESSES);

        Modify_SPI_Reg_bits(defSPI_RCC_CTL_LPFL_RBB, 3); //3
        Modify_SPI_Reg_bits(defSPI_C_CTL_LPFL_RBB, 224); //224
        Modify_SPI_Reg_bits(defSPI_G_PGA_RBB, 31);

        //TRF
        Modify_SPI_Reg_bits(defSPI_L_LOOPB_TXPAD_TRF, 0);
        Modify_SPI_Reg_bits(defSPI_EN_LOOPB_TXPAD_TRF, 1);
        Modify_SPI_Reg_bits(0x0100, 2, 0, 0); //PD_TLOBUF, PD_TXPAD, EN_G_TRF
        Modify_SPI_Reg_bits(defSPI_EN_NEXTTX_RFE, ch == 2);

        //AFE
        tempRegData = Get_SPI_Reg_bits(0x0082, 15, 13); //isel_dac_afe
        SetDefaults(AFE_ADDRESSES);
        Modify_SPI_Reg_bits(0x0082, 3, 3, 0); //PD_RX_AFE2 0
        Modify_SPI_Reg_bits(0x0082, 15, 13, tempRegData);

        if(ch == 2)
        {
            Modify_SPI_Reg_bits(defSPI_PD_TX_AFE2, 0);
        }

        //BIAS
        Modify_SPI_Reg_bits(0x0084, 4, 0, 0);

        //XBUF
        Modify_SPI_Reg_bits(0x0085, 2, 0, 1);

        //CLKGEN
        //reset CGEN to defaults
     	SetDefaults(CGEN_ADDRESSES);
        if(SetFrequencyCGEN(REF_CLK_MHZ, cgen_freq) != 0)	//comparators are being checked
        {
            RestoreRegisters(txrfl_backupRegs, txrfl_backupData, 0, txdcrflBACKUP_REG_COUNT-1);
            return -3;
        }

        //SXR
		Modify_SPI_Reg_bits(0x0020, 1, 0, 1);	//SXR channel
        SetDefaults(SXR_ADDRESSES);
        if(SetFrequency(1, REF_CLK_MHZ, GetFrequencySX(0)-4) != 0)
        {
            RestoreRegisters(txrfl_backupRegs, txrfl_backupData, 0, txdcrflBACKUP_REG_COUNT-1);
            return -4;
        }

        Modify_SPI_Reg_bits(0x0020, 1, 0, ch);

        //TXTSP
        Modify_SPI_Reg_bits(0x0200, 3, 2, 0x3); //TSGMODE 1, INSEL 1
        Modify_SPI_Reg_bits(0x0200, 0, 0, 1);  //EN_TXTSP
        Modify_SPI_Reg_bits(0x0208, 3, 3, 0);  //DC_BYP

        LoadDCIQ(0, 0);

        //RXTSP
        Modify_SPI_Reg_bits(defSPI_EN_RXTSP, 1);
        Modify_SPI_Reg_bits(defSPI_HBD_OVR, 0);
        Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1); //AGC_MODE 1, AGC_AVG 7
		Modify_SPI_Reg_bits(defSPI_AGC_AVG, 7);
        Modify_SPI_Reg_bits(0x040C, 7, 0, 0xBF);

        //Stage 3
        //A
        DCCalibrationRX_RSSI(1);
        //B
        Modify_SPI_Reg_bits(defSPI_EN_G_TRF, 1);
		if(sel_band == 1)
		{
			Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_2_RFE, 0);
            Modify_SPI_Reg_bits(defSPI_EN_INSHSW_LB2, 0);
		}
        else
        {
            Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_1_RFE, 0);
            Modify_SPI_Reg_bits(defSPI_EN_INSHSW_LB1, 0);
        }
    }

    Modify_SPI_Reg_bits(0x400, 14, 13, 0); //CAPSEL
    Modify_SPI_Reg_bits(0x40A, 13, 12, 1); //AGC_MODE
    //Modify_SPI_Reg_bits(defSPI_AGC_AVG, 7); //AGC_AVG

    bool skip = false;
    if(skip)
        return 0;

    for(i=0; i<7; ++i)
    {
        FindMinRSSI(defSPI_DCCORRI_TXTSP, corrI, &corrI, 3, 1, 64>>i);
        FindMinRSSI(defSPI_DCCORRQ_TXTSP, corrQ, &corrQ, 3, 1, 64>>i);
    }

    if(config)
    {
        //stage 4
        RestoreRegisters(txrfl_backupRegs, txrfl_backupData, 0, txdcrflBACKUP_REG_COUNT-1);

        //#warning problem with 0x0200 register, values needs toggling to take effect
        tempRegData = Get_SPI_Reg_bits(0x0200, 3, 3);
        Modify_SPI_Reg_bits(0x0200, 3, 3, !tempRegData);
        Modify_SPI_Reg_bits(0x0200, 3, 3, tempRegData);

		LoadDCIQ(0x7FFF, 0x8000); // also disables DC_BYP
    }
    Modify_SPI_Reg_bits(defSPI_DCCORRI_TXTSP, corrI);
    Modify_SPI_Reg_bits(defSPI_DCCORRQ_TXTSP, corrQ);

    //cout << "TX DC CALIBRATION TIME: " << getMilis()-t1 << " ms" << endl;

    return 0;
}

/** @brief Starts algorithm in MCU
*/
void Algorithms::CallMCU(int data)
{
    if(data != 0)
        lmsControl->getSerPort()->mSPI_write(0x0006, 1);
    else
        lmsControl->getSerPort()->mSPI_write(0x0006, 0);
    lmsControl->getSerPort()->mSPI_write(0, data);
}

/** @brief Waits for MCU to finish executing program
    @return 0 success, 255 idle, 244 running, else algorithm status
*/
int Algorithms::WaitForMCU()
{
    long t1 = getMilis();
    long t2 = getMilis();
    unsigned short value = 0;
    while((t2 - t1)<5000)
    {
        value = lmsControl->getSerPort()->mSPI_read(0x0001);
        if(value == 0)
            break;
//        else if(value == 0xFF && (t2-t1 > 1000))
//           break;
        else if(value > 0 && value < 0xFE)
        {
            break;
        }

        milSleep(10);
        t2 = getMilis();
    }
    lmsControl->getSerPort()->mSPI_write(0x0006, 0);
    printf("MCU algorithm time: %i\n", t2-t1);
    return value;
}

#define txdcrflBACKUP_REG_COUNT 22
int Algorithms::DCCalibrationTX_RFLOOP_MCU(char config)
{
    xdata unsigned short txrfl_backupRegs[] = {0x010C, 0x0115, 0x0118, 0x0119, 0x0100, 0x0082, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x0200, 0x0208, 0x020C, 0x0400, 0x0403, 0x040A, 0x040C};
	xdata unsigned short txrfl_backupData[txdcrflBACKUP_REG_COUNT];
    BackupRegisters(txrfl_backupRegs, txrfl_backupData, 0, txdcrflBACKUP_REG_COUNT-1);

    char ch = Get_SPI_Reg_bits(0x0020, 1, 0);
xdata unsigned short addrs[] =  {0x010C, 0x010D, 0x010E, 0x010F, 0x0110, 0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116, 0x0117, 0x0118, 0x0119, 0x011A, 0x0101, 0x0100, 0x0082, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x0200, 0x0208, 0x020C, 0x0200, 0x0200, 0x0200, 0x0400, 0x0403, 0x040A, 0x040C};
xdata unsigned short masks[] =  {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1801, 0x0007, 0x1FFF, 0x001F, 0x0007, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x000F, 0x0008, 0x0000, 0x0060, 0x0060, 0x0060, 0x0001, 0x7000, 0x3000, 0x00FF};
xdata unsigned short values[] = {0x88E5, 0x009E, 0x2040, 0x318C, 0x0994, 0x0083, 0x51BA, 0x03FF, 0x009D, 0x0009, 0x8100, 0x18A9, 0x018C, 0x1816, 0x2E02, 0x0001, 0x0000, 0x800B, 0x0000, 0x0001, 0x4905, 0x0400, 0x0780, 0x0020, 0x0514, 0x1900, 0x067B, 0x000D, 0x0000, 0x0000, 0x0000, 0x0060, 0x0000, 0x0001, 0x7000, 0x1000, 0x00BF};


    //RFE
	int sel_band1 = Get_SPI_Reg_bits(0x0103, 11, 11);
    int sel_band2 = Get_SPI_Reg_bits(0x0103, 10, 10);

	Modify_SPI_Reg_mask(addrs, masks, values, 0, 36);

	if(sel_band1)
    {
        Modify_SPI_Reg_bits(defSPI_SEL_PATH_RFE, 3);
        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_1_RFE, 0);
        Modify_SPI_Reg_bits(defSPI_EN_INSHSW_LB1, 0);
    }

    if(sel_band2)
    {
        Modify_SPI_Reg_bits(defSPI_SEL_PATH_RFE, 2);
        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_2_RFE, 0);
        Modify_SPI_Reg_bits(defSPI_EN_INSHSW_LB2, 0);
    }

	if(ch == 2)
    {
        Modify_SPI_Reg_bits(defSPI_PD_TX_AFE2, 0);
        Modify_SPI_Reg_bits(defSPI_PD_RX_AFE2, 0);
		Modify_SPI_Reg_bits(defSPI_EN_NEXTTX_RFE, 1);
    }

	if(SetFrequencyCGEN(REF_CLK_MHZ, cgen_freq) != 0)	//comparators are being checked
	{
		//RestoreRegisters(txrfl_backupRegs, txrfl_backupData, 0, txdcrflBACKUP_REG_COUNT-1);
		return -3;
	}

	//SXR
	Modify_SPI_Reg_bits(0x0020, 1, 0, 1);

	xdata const unsigned short sxrDefaddrs[] = {0x011C, 0x011D, 0x011E, 0x011F, 0x0120, 0x0121, 0x0122, 0x0123, 0x0124};
	//xdata unsigned short sxrDefMasks[] = 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
	xdata const unsigned short sxrDefValues[] = {0xAD43, 0x0400, 0x0780, 0x3640, 0xB980, 0x8404, 0x0514, 0x067B, 0x0000};

	Modify_SPI_Reg_mask(sxrDefaddrs, masks, sxrDefValues, 0, 8);

	float sxtFreq_mhz = GetFrequencySX(false);
	if(SetFrequency(true, REF_CLK_MHZ, sxtFreq_mhz-5) != 0)
        return -4;

    Modify_SPI_Reg_bits(0x0020, 1, 0, ch);

    bool skip = false;
    if(skip)
        return 0;

    //Stage 3
    //A
    DCCalibrationRX_RSSI(true);

    //B
    Modify_SPI_Reg_bits(defSPI_EN_G_TRF, 1);

    //C
    Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1);
    Modify_SPI_Reg_bits(defSPI_CAPSEL, 0);

    //D,E,F
    xdata int corrI = 0;
    xdata int corrQ = 0;
    xdata int globMinI;
    xdata int globMinQ;
    int staleLimit = 4;
    int staleCounter = 0;
    unsigned long minRSSI = ~0;
    unsigned long newRSSI = 0;
    bool iqselect = 0;

    while(staleCounter < staleLimit)
    {
        if(iqselect == 0)
            newRSSI = FindMinRSSI(defSPI_DCCORRI_TXTSP, corrI, &corrI, 1, 1);
        else
            newRSSI = FindMinRSSI(defSPI_DCCORRQ_TXTSP, corrQ, &corrQ, 1, 1);

        if(newRSSI < minRSSI)
        {
            globMinI = corrI;
            globMinQ = corrQ;
            minRSSI = newRSSI;
            staleCounter = 0;
        }
        else
            ++staleCounter;
        iqselect = !iqselect;
    }

    //stage 4
    RestoreRegisters(txrfl_backupRegs, txrfl_backupData, 0, txdcrflBACKUP_REG_COUNT-1);
    Modify_SPI_Reg_bits(0x0208, 3, 3, 0);
    Modify_SPI_Reg_bits(defSPI_DCCORRI_TXTSP, globMinI);
    Modify_SPI_Reg_bits(defSPI_DCCORRQ_TXTSP, globMinQ);
    return 0;
}

/** @brief Checks for RX saturation
    @return 0-status OK, 1-saturated
*/
int Algorithms::DetectRXSaturation()
{
    Modify_SPI_Reg_bits(defSPI_CAPSEL, 0);
    flipCapture();
    unsigned long rssi = (Get_SPI_Reg_bits(0x040F, 15, 0) << 2) | Get_SPI_Reg_bits(0x040E, 1, 0);
    if(rssi > 0x8000)
    {
        char ctemp[512];
        sprintf(ctemp, "RX SATURATED  - RSSI: 0x%05X", rssi);
        return 1;
    }
    return 0;
}

int Algorithms::FixRXSaturation()
{
    char g_rxloopb = 15;
    bool needToLower = false;
    while(DetectRXSaturation() != 0 && g_rxloopb > 0)
    {
        g_rxloopb -= 1;
        Modify_SPI_Reg_bits(defSPI_G_RXLOOPB_RFE, g_rxloopb);
        needToLower = true;
    }
    if(needToLower)
        Modify_SPI_Reg_bits(defSPI_G_RXLOOPB_RFE, g_rxloopb-1);
    return DetectRXSaturation();
}

map<unsigned short, MemoryRegister> demoregistersStash[2];
unsigned long minRSSI = ~0;
int miniqcorr = 0;
unsigned long minRSSI_i = ~0-1;
unsigned long minRSSI_q = ~0-1;
int gcorrq_rx = 2047-512;
int gcorri_rx = 2047-512;
int iqcorr_rx = 0;
unsigned int dccorri;
unsigned int dccorrq;
int gcorrq = 0;
int gcorri = 0;
int iqcorr = 0;
unsigned int rxdcoffseti;
unsigned int rxdcoffsetq;
int Algorithms::DemoCalibration(int stage)
{
    unsigned long t1 = getMilis();
    if(stage == 0)
    {
        demoregistersStash[0] = lmsControl->getRegistersMap()->StashRegisters(0);
        demoregistersStash[1] = lmsControl->getRegistersMap()->StashRegisters(1);
    }


    int ch = Get_SPI_Reg_bits(defSPI_MAC);
    //Stage 1
    int sel_band1_trf = Get_SPI_Reg_bits(0x0103, 11, 11);
    int sel_band2_trf = Get_SPI_Reg_bits(0x0103, 10, 10);

    if(stage == 1)
    {
        iqcorr = 0;
        gcorrq = 0;
        gcorri = 0;
        bool config = true;
        if(config)
            if(TXIQCalibration_setup())
                return -1;
    }

    //Stage 3
    //A
    if(stage == 2)
    {
    #ifdef USE_MCU
        CallMCU(1);
        if(WaitForMCU() != 0)
            return -4;
    #else
        DCCalibrationRX_RSSI(false);
        //DCCalibrationRX(false);
    #endif

    Modify_SPI_Reg_bits(0x010D, 6, 6, 1); //EN_DCOFF_RXFE
    Modify_SPI_Reg_bits(0x040c, 2, 2, 0); //DC_BYP
    }
    if(stage == 3)
    {
    //B
    Modify_SPI_Reg_bits(0x0100, 0, 0, 1); //EN_G_TRF 1
    if(sel_band1_trf == 1)
        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_1_RFE, 0); //PD_RLOOPB_1_RFE 0

    if(sel_band2_trf == 1)
        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_2_RFE, 0); //PD_RLOOPB_2_RFE 0


    if(sel_band1_trf == 1)
        Modify_SPI_Reg_bits(defSPI_EN_INSHSW_LB1, 0); //EN_INSHSW_LB1 0

    if(sel_band2_trf == 1)
        Modify_SPI_Reg_bits(defSPI_EN_INSHSW_LB2, 0); // EN_INSHSW_LB2 0


    //Modify_SPI_Reg_bits(defSPI_AGC_AVG, 0); //agc_avg iq corr
    //C
#ifdef USE_MCU
    CallMCU(2);
    if(WaitForMCU() != 0)
        return -5;
#else
    //C
    Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1);
    Modify_SPI_Reg_bits(defSPI_CAPSEL, 0);

   //Modify_SPI_Reg_bits(defSPI_AGC_AVG, 7); //AGC_AVG iq corr

    int rxstatus = FixRXSaturation();
    DCCalibrationTX_RFLOOP(false);
   // Modify_SPI_Reg_bits(defSPI_AGC_AVG, 0); //AGC_AVG iq corr
#endif // USE_MCU
    }

    if(stage == 4)
    {
    //D
    float ncofreq = 5.0;
    Set_NCO_Freq(ncofreq, gRefClkTxTSP, false);
    Modify_SPI_Reg_bits(0x020C, 15, 0, 0x7FFF);
    Modify_SPI_Reg_bits(0x0200, 5, 5, 0);
    Modify_SPI_Reg_bits(0x0200, 5, 5, 1);
    Modify_SPI_Reg_bits(0x0200, 5, 5, 0);
    Modify_SPI_Reg_bits(0x020C, 15, 0, 0x8000);
    Modify_SPI_Reg_bits(0x0200, 6, 6, 0);
    Modify_SPI_Reg_bits(0x0200, 6, 6, 1);
    Modify_SPI_Reg_bits(0x0200, 6, 6, 0);
    Modify_SPI_Reg_bits(0x0200, 2, 2, 1); //INSEL 1

    float SXTfreqMHz = GetFrequencySX(false);

    float freqDiff2 = 6;

    double sxrFreq = SXTfreqMHz-freqDiff2;
    if(SetFrequency(true, REF_CLK_MHZ, sxrFreq) != 0)
        return -1;

    //G
    //Modify_SPI_Reg_bits(defSPI_EN_G_TRF, 1); //EN_G_TRF 1
//    if(sel_band1_trf == 1)
//        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_1_RFE, 0); //PD_RLOOPB_1_RFE 0
//
//    if(sel_band2_trf == 1)
//        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_2_RFE, 0); //PD_RLOOPB_2_RFE 0

    //H.a
    }

    if(stage == 5)
    {
    FixRXSaturation();
    Modify_SPI_Reg_bits(defSPI_GCORRI_TXTSP, 2047);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_TXTSP, 2047);

    iqcorr = 0;
    Modify_SPI_Reg_bits(defSPI_IQCORR_TXTSP, iqcorr);
    gcorri = 2047-512;

    cout << "TX IQ CORRR:  I GAIN" << endl;
    MessageLog::getInstance()->write("IQ correction: I gain\n", LOG_INFO);
    for(int i=0; i<9; ++i)
    {
        minRSSI_i = FindMinRSSI(defSPI_GCORRI_TXTSP, gcorri, &gcorri, 3, 0, 256>>i);
    }

    Modify_SPI_Reg_bits(defSPI_GCORRI_TXTSP, 2047);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_TXTSP, 2047);

    cout << "TX IQ CORR:  Q GAIN" << endl;
    MessageLog::getInstance()->write("IQ correction: Q gain\n", LOG_INFO);
    minRSSI = ~0;
    gcorrq = 2047-512;

    for(int i=0; i<9; ++i)
    {
        minRSSI_q = FindMinRSSI(defSPI_GCORRQ_TXTSP, gcorrq, &gcorrq, 3, 0, 256>>i);
    }

    if(minRSSI_i < minRSSI_q)
        gcorrq = 2047;
    else
        gcorri = 2047;


    Modify_SPI_Reg_bits(defSPI_GCORRI_TXTSP, gcorri);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_TXTSP, gcorrq);

    }

    if(stage == 6)
    {
    cout << "TX IQ CORR:  PHASE" << endl;
    MessageLog::getInstance()->write("IQ correction: phase\n", LOG_INFO);
    minRSSI = ~0;
    iqcorr = miniqcorr;
    for(int i=0; i<9; ++i)
    {
        FindMinRSSI(defSPI_IQCORR_TXTSP, iqcorr, &iqcorr, 3, 1, 256>>i);
    }

    Modify_SPI_Reg_bits(defSPI_GCORRI_TXTSP, gcorri);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_TXTSP, gcorrq);
    Modify_SPI_Reg_bits(defSPI_IQCORR_TXTSP, iqcorr);

    }

    if(stage == 7)
    {
    //Modify_SPI_Reg_bits(defSPI_L_LOOPB_TXPAD_TRF, 0); //L_LOOPB_TXPAD_TRF 0 //!!!
    //I
    Modify_SPI_Reg_bits(0x040C, 7, 7, 0); //CMIX_BYP 0
    Modify_SPI_Reg_bits(0x040C, 2, 0, 0); //DC_BYP 0, GC_BYP 0, PH_BYP 0
    Modify_SPI_Reg_bits(defSPI_CMIX_GAIN_RXTSP, 1); //CMIX_GAIN 1  +6 db
    Modify_SPI_Reg_bits(0x040C, 13, 13, 1); //CMIX_SC 1

    //J
    Set_NCO_Freq(8, gRefClkRxTSP, true);
    Modify_SPI_Reg_bits(defSPI_GCORRI_RXTSP, 2047);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_RXTSP, 2047);

//    int gcorri_tx_2 = Get_SPI_Reg_bits(defSPI_GCORRI_TXTSP);
//    int gcorrq_tx_2 = Get_SPI_Reg_bits(defSPI_GCORRQ_TXTSP);
//    int iqcorr_tx_2 = Get_SPI_Reg_bits(defSPI_IQCORR_TXTSP);


    Modify_SPI_Reg_bits(defSPI_CCOMP_TIA_RFE, 3); //CCOMP_TIA_RFE 3
    Modify_SPI_Reg_bits(defSPI_CFB_TIA_RFE, 246); //CFB_TIA_RFE 246

   Modify_SPI_Reg_bits(defSPI_RCC_CTL_LPFL_RBB, 4); //RCC_CTL_LPFL_RBB 4
   Modify_SPI_Reg_bits(defSPI_C_CTL_LPFL_RBB, 61); //C_CTL_LPFL_RBB 61

    iqcorr_rx = 0;
    minRSSI = ~0;
    miniqcorr = 0;
    iqcorr_rx = miniqcorr;
    Modify_SPI_Reg_bits(defSPI_IQCORR_RXTSP, iqcorr_rx);

    minRSSI = ~0;
    gcorri_rx = 2047-512;
    minRSSI_i = ~0-1;
    cout << "RX IQ CORRR:  I GAIN" << endl;
    MessageLog::getInstance()->write("IQ correction: I gain\n", LOG_INFO);
    for(int i=0; i<9; ++i)
    {
        minRSSI_i = FindMinRSSI(defSPI_GCORRI_RXTSP, gcorri_rx, &gcorri_rx, 3, 0, 256>>i);
    }

    Modify_SPI_Reg_bits(defSPI_GCORRI_RXTSP, 2047);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_RXTSP, 2047);

    cout << "RX IQ CORR:  Q GAIN" << endl;
    MessageLog::getInstance()->write("IQ correction: Q gain\n", LOG_INFO);
    minRSSI = ~0;
    gcorrq_rx = 2047-512;
    minRSSI_q = ~0-1;
    for(int i=0; i<9; ++i)
    {
        minRSSI_i = FindMinRSSI(defSPI_GCORRQ_RXTSP, gcorrq_rx, &gcorrq_rx, 3, 0, 256>>i);
    }

    if(minRSSI_i < minRSSI_q)
        gcorrq_rx = 2047;
    else
        gcorri_rx = 2047;

    Modify_SPI_Reg_bits(defSPI_GCORRI_RXTSP, gcorri_rx);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_RXTSP, gcorrq_rx);

    }

    if(stage == 8)
    {

    cout << "RX IQ CORR:  PHASE" << endl;
    MessageLog::getInstance()->write("IQ correction: phase\n", LOG_INFO);
    minRSSI = ~0;
    iqcorr_rx = miniqcorr;
    for(int i=0; i<9; ++i)
    {
        FindMinRSSI(defSPI_IQCORR_RXTSP, iqcorr_rx, &iqcorr_rx, 3, 1, 256>>i);
    }

    Modify_SPI_Reg_bits(defSPI_IQCORR_RXTSP, iqcorr_rx);
    }

    if(stage == 9)
    {

    dccorri = Get_SPI_Reg_bits(defSPI_DCCORRI_TXTSP);
    dccorrq = Get_SPI_Reg_bits(defSPI_DCCORRQ_TXTSP);
    rxdcoffseti = Get_SPI_Reg_bits(defSPI_DCOFFI_RFE);
    rxdcoffsetq = Get_SPI_Reg_bits(defSPI_DCOFFQ_RFE);
//    // Stage 4
    lmsControl->getRegistersMap()->RestoreRegisters(0, demoregistersStash[0]);
    lmsControl->getRegistersMap()->RestoreRegisters(1, demoregistersStash[1]);
    lmsControl->getRegistersMap()->UploadAll();
    lmsControl->UploadAll();
    }
    if(stage == 10)
    {

//#warning serious problem with 0x0200 register, values needs toggling to take effect
//    unsigned short regVal = Get_SPI_Reg_bits(0x0200, 3, 3);
//    Modify_SPI_Reg_bits(0x0200, 3, 3, !regVal);
//    Modify_SPI_Reg_bits(0x0200, 3, 3, regVal); //!!!

//    lmsControl->SelectConfigChannel(1, false);
//    Modify_SPI_Reg_bits(0x011F, 14, 12, pw_div2_loch);
//    Modify_SPI_Reg_bits(0x011F, 11, 9, pw_div4_loch);

    Modify_SPI_Reg_bits(defSPI_MAC, ch);
    //Modify_SPI_Reg_bits(0x0104, 7, 4, cdc_i_trf);
    //Modify_SPI_Reg_bits(0x0104, 3, 0, cdc_q_trf);
    Set_DCOFF(rxdcoffseti, rxdcoffsetq);
    Modify_SPI_Reg_bits(defSPI_EN_DCOFF_RXFE_RFE, 1);
    Modify_SPI_Reg_bits(defSPI_DCCORRI_TXTSP, dccorri);
    Modify_SPI_Reg_bits(defSPI_DCCORRQ_TXTSP, dccorrq);
    Modify_SPI_Reg_bits(defSPI_GCORRI_TXTSP, gcorri);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_TXTSP, gcorrq);
    Modify_SPI_Reg_bits(defSPI_IQCORR_TXTSP, iqcorr);

    Modify_SPI_Reg_bits(defSPI_GCORRI_RXTSP, gcorri_rx);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_RXTSP, gcorrq_rx);
    Modify_SPI_Reg_bits(defSPI_IQCORR_RXTSP, iqcorr_rx);

    Modify_SPI_Reg_bits(0x040C, 2, 0, 0); //DC_BYP 0, GC_BYP 0, PH_BYP 0
    Modify_SPI_Reg_bits(0x0208, 3, 3, 0); //DC_BYP
    Modify_SPI_Reg_bits(0x0208, 1, 0, 0); //GC_BYP PH_BYP
    }




    cout << "TX/RX IQ correction TIME: " << getMilis()-t1 << " ms" << endl;

    return 0;
}

int Algorithms::RXIQCalibration_setup()
{
        //for redboard
    //Modify_SPI_Reg_bits(0x0093, 6, 6, 1);
    //Modify_SPI_Reg_bits(0x0092, 9, 9, 1);
    //Stage 2
    int ch = Get_SPI_Reg_bits(defSPI_MAC);
    int sel_band1_trf = Get_SPI_Reg_bits(0x0103, 11, 11);
    int sel_band2_trf = Get_SPI_Reg_bits(0x0103, 10, 10);

    //rfe
    if(ch == 2)
        Modify_SPI_Reg_bits(defSPI_EN_NEXTTX_RFE, 1); // EN_NEXTTX_RFE 0

    Modify_SPI_Reg_bits(defSPI_G_RXLOOPB_RFE, 15); //G_RXLOOPB_RFE 15
    Modify_SPI_Reg_bits(0x010C, 4, 3, 0); //PD_MXLOBUF_RFE 0, PD_QGEN_RFE 0
    Modify_SPI_Reg_bits(0x010C, 1, 1, 0); //PD_TIA 0
    Modify_SPI_Reg_bits(0x010C, 7, 7, 1); //PD_LNA 1
//
//    Modify_SPI_Reg_bits(defSPI_CCOMP_TIA_RFE, 6); //CCOMP_TIA_RFE 3
//    Modify_SPI_Reg_bits(defSPI_CFB_TIA_RFE, 510); //CFB_TIA_RFE 246
    Modify_SPI_Reg_bits(0x0110, 4, 0, 31); //ICT_LO_RFE 31
    Modify_SPI_Reg_bits(0x010D, 4, 1, 0xFF); // all short switches are enabled

    //RBB
//    Modify_SPI_Reg_bits(0x0115, 3, 3, 1); //PD_LPFH_RBB 1
//    Modify_SPI_Reg_bits(0x0115, 2, 2, 0); //PD_LPFL_RBB 0
//    Modify_SPI_Reg_bits(defSPI_INPUT_CTL_PGA_RBB, 0); //INPUT_CTL_PGA_RBB 1
//    Modify_SPI_Reg_bits(defSPI_RCC_CTL_LPFH_RBB, 1); //RCC_CTL_LPFH_RBB 1
//    Modify_SPI_Reg_bits(defSPI_RCC_CTL_LPFL_RBB, 3); //RCC_CTL_LPFL_RBB 4
//    //Modify_SPI_Reg_bits(defSPI_C_CTL_LPFH_RBB, 111); //C_CTL_LPFH_RBB 111
//    Modify_SPI_Reg_bits(defSPI_C_CTL_LPFL_RBB, 224); //C_CTL_LPFL_RBB 61
//    Modify_SPI_Reg_bits(defSPI_G_PGA_RBB, 31); //G_PGA_RBB 22
    Modify_SPI_Reg_bits(0x0115, 15, 14, 0); //Loopback switches disable
    Modify_SPI_Reg_bits(0x0119, 15, 15, 0); //OSW_PGA 0

    //TRF
    //reset TRF to defaults
    for(int addr=0x0100; addr<=0x0104; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    Modify_SPI_Reg_bits(defSPI_L_LOOPB_TXPAD_TRF, 0); //L_LOOPB_TXPAD_TRF 0 //!!!
    Modify_SPI_Reg_bits(defSPI_EN_LOOPB_TXPAD_TRF, 1); //EN_LOOPB_TXPAD_TRF 1
    Modify_SPI_Reg_bits(defSPI_EN_G_TRF, 0); //EN_G_TRF 0
    if(ch == 2)
        Modify_SPI_Reg_bits(defSPI_EN_NEXTTX_TRF, 1); //EN_NEXTTX_TRF 1
    Modify_SPI_Reg_bits(defSPI_LOSS_LIN_TXPAD_TRF, 0); //LOSS_LIN_TXPAD_TRF 5
    Modify_SPI_Reg_bits(defSPI_LOSS_MAIN_TXPAD_TRF, 0); //LOSS_MAIN_TXPAD_TRF 5

    //TBB
    //reset TBB to defaults
    for(int addr=0x0105; addr<=0x010A; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    Modify_SPI_Reg_bits(defSPI_CG_IAMP_TBB, 9); //CG_IAMP_TBB 9
    Modify_SPI_Reg_bits(defSPI_ICT_IAMP_FRP_TBB, 1); //ICT_IAMP_FRP_TBB 1
    Modify_SPI_Reg_bits(defSPI_ICT_IAMP_GG_FRP_TBB, 6); //ICT_IAMP_GG_FRP_TBB 6

    //AFE
    //reset AFE to defaults
    for(int addr=0x0082; addr<=0x0082; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    Modify_SPI_Reg_bits(defSPI_PD_RX_AFE2, 0); //PD_RX_AFE2
    if(ch == 2)
    {
        Modify_SPI_Reg_bits(defSPI_PD_TX_AFE2, 0); //PD_TX_AFE2
    }
    //BIAS
    unsigned short backup = Get_SPI_Reg_bits(0x0084, 10, 6);
    for(int addr=0x0083; addr<=0x0084; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    Modify_SPI_Reg_bits(0x0084, 10, 6, backup); //RP_CALIB_BIAS

    //XBUF
    Modify_SPI_Reg_bits(0x0085, 2, 0, 1); //PD_XBUF_RX 0, PD_XBUF_TX 0, EN_G_XBUF 1

    //CGEN
    //reset CGEN to defaults
    for(int addr=0x0086; addr<=0x008C; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    //power up VCO
    Modify_SPI_Reg_bits(0x0086, 2, 2, 0);

    if(SetFrequencyCGEN(REF_CLK_MHZ, cgen_freq) != 0)
        return -1;

//    //SXR
    Modify_SPI_Reg_bits(defSPI_MAC, 1);
//    for(int addr=0x011C; addr<=0x0124; ++addr)
//    {
//        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
//        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
//    }
    float SXRfreqMHz = GetFrequencySX(true);

    //SXT
    Modify_SPI_Reg_bits(defSPI_MAC, 2);
    Modify_SPI_Reg_bits(defSPI_PD_LOCH_t2RBUF, 1); //PD_LOCH_t2RBUF 1
    if(SetFrequency(false, REF_CLK_MHZ, SXRfreqMHz+5) != 0)
        return -1;
    Modify_SPI_Reg_bits(defSPI_MAC, ch);

    //TXTSP
    for(int addr=0x0200; addr<=0x020C; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    Modify_SPI_Reg_bits(0x0200, 3, 2, 0x3); //TSGMODE 1, INSEL 1
    //Modify_SPI_Reg_bits(0x0208, 6, 4, 0xFFFF); //GFIR3_BYP 1, GFIR2_BYP 1, GFIR1_BYP 1
    Modify_SPI_Reg_bits(0x0208, 6, 6, 1); //GFIR3_BYP 1, GFIR2_BYP 1, GFIR1_BYP 1
    Modify_SPI_Reg_bits(0x0208, 5, 5, 1); //GFIR3_BYP 1, GFIR2_BYP 1, GFIR1_BYP 1
    Modify_SPI_Reg_bits(0x0208, 4, 4, 1); //GFIR3_BYP 1, GFIR2_BYP 1, GFIR1_BYP 1
    Modify_SPI_Reg_bits(defSPI_DC_REG_TXTSP, 0x7FFF);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDI_TXTSP, 0);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDI_TXTSP, 1);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDI_TXTSP, 0);
    Modify_SPI_Reg_bits(defSPI_DC_REG_TXTSP, 0x8000);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDQ_TXTSP, 0);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDQ_TXTSP, 1);
    Modify_SPI_Reg_bits(defSPI_TSGDCLDQ_TXTSP, 0);
    Set_NCO_Freq(0, gRefClkTxTSP, false);

    //RXTSP
    for(int addr=0x0400; addr<=0x040C; ++addr)
    {
        int defVal = lmsControl->getRegistersMap()->getRegisterInfo(0, addr).defaultValue;
        Modify_SPI_Reg_bits(addr, 15, 0, defVal);
    }
    Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1); //AGC_MODE 1
    Modify_SPI_Reg_bits(0x040C, 7, 7, 0x1); //CMIX_BYP 1
    Modify_SPI_Reg_bits(0x040C, 6, 6, 0x0); //AGC_BYP 0
    Modify_SPI_Reg_bits(0x040C, 5, 5, 1); //
    Modify_SPI_Reg_bits(0x040C, 4, 4, 1); //
    Modify_SPI_Reg_bits(0x040C, 3, 3, 1); //
    Modify_SPI_Reg_bits(0x040C, 2, 2, 1); // DC_BYP
    Modify_SPI_Reg_bits(0x040C, 1, 1, 1); //
    Modify_SPI_Reg_bits(0x040C, 0, 0, 1); //

    Modify_SPI_Reg_bits(defSPI_AGC_MODE, 1);
    Modify_SPI_Reg_bits(defSPI_CAPSEL, 0);
    Modify_SPI_Reg_bits(0x0403, 14, 12, 0); //Decimation HBD ratio

    Modify_SPI_Reg_bits(defSPI_AGC_AVG, 0x7); //agc_avg iq corr
    return 0;
}


int Algorithms::RXIQCalibration()
{
    int ch = Get_SPI_Reg_bits(defSPI_MAC);
    unsigned long t1 = getMilis();
    map<unsigned short, MemoryRegister> registersStash[2];
    registersStash[0] = lmsControl->getRegistersMap()->StashRegisters(0);
    registersStash[1] = lmsControl->getRegistersMap()->StashRegisters(1);

    int sel_path_rfe = Get_SPI_Reg_bits(0x010D, 8, 7);
    if(sel_path_rfe == 1 || sel_path_rfe == 0)
        return -1;

    RXIQCalibration_setup();

    DCCalibrationRX_RSSI(false);
    int dcoffi = Get_SPI_Reg_bits(defSPI_DCOFFI_RFE);
    int dcoffq = Get_SPI_Reg_bits(defSPI_DCOFFQ_RFE);
    Modify_SPI_Reg_bits(defSPI_EN_G_TRF, 1);

    if(sel_path_rfe == 2)
    {
        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_2_RFE, 0);
        Modify_SPI_Reg_bits(0x0103, 10, 10, 1);
        Modify_SPI_Reg_bits(defSPI_EN_INSHSW_LB2, 0);
    }
    if(sel_path_rfe == 3)
    {
        Modify_SPI_Reg_bits(defSPI_PD_RLOOPB_1_RFE, 0);
        Modify_SPI_Reg_bits(0x0103, 11, 11, 1);
        Modify_SPI_Reg_bits(defSPI_EN_INSHSW_LB1, 0);
    }

    Modify_SPI_Reg_bits(0x040C, 7, 7, 0); //CMIX_BYP 0
    Modify_SPI_Reg_bits(0x040C, 2, 0, 0); //DC_BYP 0, GC_BYP 0, PH_BYP 0
    Modify_SPI_Reg_bits(defSPI_CMIX_GAIN_RXTSP, 1); //CMIX_GAIN 1  +6 db
    Modify_SPI_Reg_bits(0x040C, 13, 13, 1); //CMIX_SC 1

    Set_NCO_Freq(6, gRefClkRxTSP, true);
    Modify_SPI_Reg_bits(defSPI_GCORRI_RXTSP, 2047);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_RXTSP, 2047);

    bool skip = false;
    if(skip)
        return 0;

    int iqcorr_rx = 0;
    minRSSI = ~0;
    miniqcorr = 0;
    iqcorr_rx = miniqcorr;
    unsigned long minRSSI_iq = ~0-1;
    Modify_SPI_Reg_bits(defSPI_IQCORR_RXTSP, iqcorr_rx);

    minRSSI = ~0;
    unsigned long mingcorri = 2047;
    int gcorri_rx = mingcorri-512;
    minRSSI_i = ~0-1;
    cout << "RX IQ CORRR:  I GAIN" << endl;
    MessageLog::getInstance()->write("IQ correction: I gain\n", LOG_INFO);
    for(int i=0; i<9; ++i)
    {
        minRSSI_i = FindMinRSSI(defSPI_GCORRI_RXTSP, gcorri_rx, &gcorri_rx, 3, 0, 256>>i);
    }


    Modify_SPI_Reg_bits(defSPI_GCORRI_RXTSP, 2047);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_RXTSP, 2047);

    cout << "RX IQ CORR:  Q GAIN" << endl;
    MessageLog::getInstance()->write("IQ correction: Q gain\n", LOG_INFO);
    minRSSI = ~0;
    unsigned long mingcorrq = 2047;
    int gcorrq_rx = mingcorrq-512;
    minRSSI_q = ~0-1;
    for(int i=0; i<9; ++i)
    {
        minRSSI_i = FindMinRSSI(defSPI_GCORRQ_RXTSP, gcorrq_rx, &gcorrq_rx, 3, 0, 256>>i);
    }

    if(minRSSI_i < minRSSI_q)
        gcorrq_rx = 2047;
    else
        gcorri_rx = 2047;

    cout << "RX IQ CORR:  PHASE" << endl;
    MessageLog::getInstance()->write("IQ correction: phase\n", LOG_INFO);
    minRSSI = ~0;
    iqcorr_rx = miniqcorr;
    for(int i=0; i<9; ++i)
    {
        minRSSI_iq = FindMinRSSI(defSPI_IQCORR_RXTSP, iqcorr_rx, &iqcorr_rx, 3, 1, 256>>i);
    }

    Modify_SPI_Reg_bits(defSPI_IQCORR_RXTSP, iqcorr_rx);

    if(minRSSI_i < minRSSI_q)
        gcorrq_rx = 2047;
    else
        gcorri_rx = 2047;


    Modify_SPI_Reg_bits(defSPI_GCORRI_RXTSP, gcorri_rx);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_RXTSP, gcorrq_rx);
    Modify_SPI_Reg_bits(defSPI_IQCORR_RXTSP, iqcorr_rx);

    lmsControl->getRegistersMap()->RestoreRegisters(0, registersStash[0]);
    lmsControl->getRegistersMap()->RestoreRegisters(1, registersStash[1]);
    lmsControl->getRegistersMap()->UploadAll();
    lmsControl->UploadAll();

//#warning serious problem with 0x0200 register, values needs toggling to take effect
//    unsigned short regVal = Get_SPI_Reg_bits(0x0200, 3, 3);
//    Modify_SPI_Reg_bits(0x0200, 3, 3, !regVal);
//    Modify_SPI_Reg_bits(0x0200, 3, 3, regVal); //!!!

//    lmsControl->SelectConfigChannel(1, false);
//    Modify_SPI_Reg_bits(0x011F, 14, 12, pw_div2_loch);
//    Modify_SPI_Reg_bits(0x011F, 11, 9, pw_div4_loch);
    Modify_SPI_Reg_bits(defSPI_MAC, ch);
    Modify_SPI_Reg_bits(defSPI_EN_DCOFF_RXFE_RFE, 1);
    //Modify_SPI_Reg_bits(0x0104, 7, 4, cdc_i_trf);
    //Modify_SPI_Reg_bits(0x0104, 3, 0, cdc_q_trf);

    Set_DCOFF(dcoffi, dcoffq);
    Modify_SPI_Reg_bits(defSPI_GCORRI_RXTSP, gcorri_rx);
    Modify_SPI_Reg_bits(defSPI_GCORRQ_RXTSP, gcorrq_rx);
    Modify_SPI_Reg_bits(defSPI_IQCORR_RXTSP, iqcorr_rx);
    Modify_SPI_Reg_bits(0x040C, 2, 0, 0); //DC_BYP 0, GC_BYP 0, PH_BYP 0
    Modify_SPI_Reg_bits(0x0110, 4, 0, 31); //ICT_LO_RFE 31
    return 0;
}

int Algorithms::VCO_Tuning(char module) // 0-cgen, 1-SXR, 2-SXT
{
	xdata char i;
	xdata unsigned char cmphl = 0;
	xdata short csw_lowest = -1;
	xdata unsigned short addrVCOpd;
	xdata unsigned short addrSWC_VCO;
	xdata unsigned short addrCMP;
	xdata unsigned char lsb;
	xdata unsigned char msb;

	unsigned char ch = Get_SPI_Reg_bits(0x0020, 1, 0);

	if(module > 0)
	{
		Modify_SPI_Reg_bits (0x0020, 1, 0, module);
		addrVCOpd = 0x011C;
		addrSWC_VCO = 0x0121;
		lsb = 3;
		msb = 10;
		addrCMP = 0x0123;
	}
	else
	{
		addrVCOpd = 0x0086;
		addrSWC_VCO = 0x008B;
		lsb = 1;
		msb = 8;
		addrCMP = 0x008C;
	}
	// Initialization
	Modify_SPI_Reg_bits (addrVCOpd, 2, 1, 0); //activate VCO
	Modify_SPI_Reg_bits (addrVCOpd, 14+(module==0), 14+(module==0), 1); // 4) SHORT_NOISEFIL=1 SPDUP_VCO_ Short the noise filter resistor to speed up the settling time
	Modify_SPI_Reg_bits (addrSWC_VCO , msb, lsb , 0); // 9)	Set SWC_VCO<7:0>=<00000000>

	i=7;// 10)	i=7
	while(i>=0)
	{
        Modify_SPI_Reg_bits (addrSWC_VCO, lsb + i, lsb + i, 1); // CSW_VCO<i>=1
        cmphl = Get_SPI_Reg_bits(addrCMP, 13, 12);
        if ( (cmphl&0x01) == 1) // reduce CSW
            Modify_SPI_Reg_bits (addrSWC_VCO, lsb + i, lsb + i, 0); // CSW_VCO<i>=0
        if( cmphl == 2 && csw_lowest < 0)
            csw_lowest = Get_SPI_Reg_bits(addrSWC_VCO, msb, lsb);
		i--;
	}
    //char ctemp[256];
	if(csw_lowest >= 0)
    {
        unsigned short csw_highest = Get_SPI_Reg_bits(addrSWC_VCO, msb, lsb);
        if(csw_lowest == csw_highest)
        {
            while(csw_lowest>=0)
            {
                Modify_SPI_Reg_bits(addrSWC_VCO, msb, lsb, csw_lowest);
                if(Get_SPI_Reg_bits(addrCMP, 13, 12) == 0)
                    break;
                else
                    --csw_lowest;
            }
        }
        //sprintf(ctemp, "lowest CSW_VCO %i, highest CSW_VCO %i\n", csw_lowest, csw_highest);
        //MessageLog::getInstance()->write(ctemp, LOG_INFO);
        Modify_SPI_Reg_bits(addrSWC_VCO, msb, lsb, csw_lowest+(csw_highest-csw_lowest)/2);
    }
    Modify_SPI_Reg_bits (addrVCOpd, 14+(module==0), 14+(module==0), 0); // SHORT_NOISEFIL=0 SPDUP_VCO_ Short the noise filter resistor to speed up the settling time
	if(Get_SPI_Reg_bits(addrCMP, 13, 12) != 2)
	{
        Modify_SPI_Reg_bits(defSPI_MAC, ch);
        return 1;
    }
	Modify_SPI_Reg_bits(defSPI_MAC, ch);
	//MessageLog::getInstance()->write("VCO tuning SXT/SXR finished\n", LOG_INFO);
	return 0;
}
