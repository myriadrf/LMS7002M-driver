/**
@file streamFPGA.cpp
@author Lime Microsystems
@brief Functions for configuring Stream board
*/

#include "streamFPGA.h"
#include "ConnectionManager.h"
#include <sstream>
#include <fstream>
#include <string.h>
using namespace std;

int ConfigurePLL(ConnectionManager *serPort, const float fOutTx_MHz, const float fOutRx_MHz, const float phaseShift_deg)
{
	fstream fout;
	fout.open("fpgaPLL.txt", ios::out);
	if (serPort == NULL)
		return -3;
	const float vcoLimits_MHz[2] = { 600, 1300 };
	int N, M, C;
	float fVCO_MHz;
	const short bufSize = 64;
	unsigned char outBuffer[bufSize];
	unsigned char inBuffer[bufSize];

	float fOut_MHz = fOutTx_MHz;
	float coef = 0.8*vcoLimits_MHz[1] / fOut_MHz;
	M = C = (int)coef;	
	int chigh = (((int)coef) / 2) + ((int)(coef)%2);
	int clow = ((int)coef)/2;
	if (fOut_MHz*M > vcoLimits_MHz[0] && fOut_MHz*M < vcoLimits_MHz[1])
	{		
		short index = 8;
		memset(outBuffer, 0, bufSize);
		outBuffer[0] = CMD_BRDSPI_WR;
		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x0F;
		outBuffer[index++] = 0x15; //c4-c2_bypassed
		outBuffer[index++] = 0x01 | ((M % 2 != 0) ? 0x08 : 0x00) | ((C % 2 != 0) ? 0x20 : 0x00); //N_bypassed

		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x08;
		outBuffer[index++] = 1; //N_high_cnt
		outBuffer[index++] = 1;//N_low_cnt
		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x09;
		outBuffer[index++] = chigh; //M_high_cnt
		outBuffer[index++] = clow;	 //M_low_cnt
		for (int i = 0; i <= 1; ++i)
		{
			outBuffer[index++] = 0x00;
			outBuffer[index++] = 0x0A + i;
			outBuffer[index++] = chigh; //cX_high_cnt
			outBuffer[index++] = clow;	 //cX_low_cnt
		}

		float Fstep_us = 1 / (8*fOutTx_MHz*C);
		float Fstep_deg = (360 * Fstep_us) / (1 / fOutTx_MHz);
		short nSteps = phaseShift_deg / Fstep_deg;
		unsigned short reg2 = 0x0400 | (nSteps & 0x3FF);
		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x02;
		outBuffer[index++] = (reg2 >> 8);
		outBuffer[index++] = reg2; //phase

		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x03;
		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x01;

		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x03;
		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x00;

		reg2 = reg2 | 0x800;
		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x02;
		outBuffer[index++] = (reg2 >> 8);
		outBuffer[index++] = reg2;
		outBuffer[2] = index / 4;

		fout << "TxPLL: M-" << (int)M << "  C-" << (int)C << " nSteps-" << nSteps << endl;

		serPort->Port_write_direct(outBuffer, bufSize);
		long toRead = bufSize;
		serPort->Port_read_direct(inBuffer, toRead);
		//if (inBuffer[1] != STATUS_COMPLETED_CMD)
			//return -2;
	}
	else
		return -1;

	fOut_MHz = fOutRx_MHz;
	coef = 0.8*vcoLimits_MHz[1] / fOut_MHz;
	M = C = (int)coef;	
	chigh = (((int)coef) / 2) + ((int)(coef) % 2);
	clow = ((int)coef) / 2;
	fout << "RxPLL: M-" << (int)M << "  C-" << (int)C << endl;
	if (fOut_MHz*M > vcoLimits_MHz[0] && fOut_MHz*M < vcoLimits_MHz[1])
	{
		short index = 8;
		memset(outBuffer, 0, bufSize);
		outBuffer[0] = CMD_BRDSPI_WR;
		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x0F;
		outBuffer[index++] = 0x15; //c4-c2_bypassed
		outBuffer[index++] = 0x41 | ((M % 2 != 0) ? 0x08 : 0x00) | ((C % 2 != 0) ? 0x20 : 0x00); //N_bypassed, c1 bypassed

		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x08;
		outBuffer[index++] = 1; //N_high_cnt
		outBuffer[index++] = 1;//N_low_cnt
		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x09;
		outBuffer[index++] = chigh; //M_high_cnt
		outBuffer[index++] = clow;	 //M_low_cnt
		for (int i = 0; i <= 1; ++i)
		{
			outBuffer[index++] = 0x00;
			outBuffer[index++] = 0x0A + i;
			outBuffer[index++] = chigh; //cX_high_cnt
			outBuffer[index++] = clow;	 //cX_low_cnt
		}

		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x03;
		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x02;

		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x03;
		outBuffer[index++] = 0x00;
		outBuffer[index++] = 0x00;

		outBuffer[2] = index / 4;

		serPort->Port_write_direct(outBuffer, bufSize);
		long toRead = bufSize;
		serPort->Port_read_direct(inBuffer, toRead);
		if (inBuffer[1] != STATUS_COMPLETED_CMD)
			return -2;
	}
	else
		return -1;
	return 0;
}
