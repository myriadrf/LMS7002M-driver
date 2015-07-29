///
/// \file LMS7002M_cal_rbb.c
///
/// RX baseband calibration algorithms for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_cal.h"
#include "LMS7002M_impl.h"
#include <LMS7002M/LMS7002M_logger.h>

#define RBB_1_4MHZ 0
#define RBB_3_0MHZ 1
#define RBB_5_0MHZ 2
#define RBB_10_0MHZ 3
#define RBB_15_0MHZ 4
#define RBB_20_0MHZ 5
#define RBB_37_0MHZ 6//1
#define RBB_66_0MHZ 7//4
#define RBB_108_0MHZ 8//7

const float RBB_CalFreq[RBB_ALL] = {0.7, 1.5 , 2.5, 5.0, 7.5, 10.0, 18.5, 33.0, 54.0}; //half of bandwidth


/***********************************************************************
 * Dispatch calibration
 * REG: added to provide a top-level function call for RBB,
 **********************************************************************/
void LMS7002M_cal_rbb(LMS7002M_t *self, const LMS7002M_chan_t ch)
{
    self->MIMO_ch = (ch==LMS_CHA)?0:1; //stash for table storage offset later
    RBB_Calibration_LowBand(self, ch);
    RBB_Calibration_HighBand(self, ch);
}

/***********************************************************************
 * RBB low band calibration
 *
 * REG: taken from A3.3.1 of SPIRegs ver 01, rev 19 and compared with
 * 05/17/2015 version of the LMS suite code. RBB lowband was not
 * implmented at that time.
 **********************************************************************/
unsigned char RBB_Calibration_LowBand(LMS7002M_t *self, const LMS7002M_chan_t ch)
{
    LMS7_logf(LMS7_TRACE, "RBB_Calibration_LowBand ch%c", ch);
    LMS7002M_set_mac_ch(self, ch);
    Modify_SPI_Reg_bits(self, 0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode);

    RBB_Algorithm_A(self); // Aproximate resistor value for RBB RBANKS (Algorithm A)

    RBB_Set_Cal_Path(self, 7); // Set control signals to path 7 (RX LowBand)

    RBB_Algorithm_B(self); // Calibrate and Record the low frequency output amplitude (Algorithm B)

    RBB_Algorithm_F(self, RBB_1_4MHZ);// CalibrateByCap the output cuttoff frequency at 0,7 MHz and store
    RBB_Algorithm_F(self, RBB_3_0MHZ);// CalibrateByCap the output cuttoff frequency at 1,5 MHz MHz and store
    RBB_Algorithm_F(self, RBB_5_0MHZ);// CalibrateByCap the output cuttoff frequency at 2,5 MHz MHz and store
    RBB_Algorithm_F(self, RBB_10_0MHZ);// CalibrateByCap the output cuttoff frequency at 5 MHz MHz and store
    RBB_Algorithm_F(self, RBB_15_0MHZ);// CalibrateByCap the output cuttoff frequency at 7,5 MHz and store
    RBB_Algorithm_F(self, RBB_20_0MHZ);// CalibrateByCap the output cuttoff frequency at 10 MHz MHz and store

    return 0;
}

/***********************************************************************
 * RBB high band calibration
 **********************************************************************/
unsigned char RBB_Calibration_HighBand(LMS7002M_t *self, const LMS7002M_chan_t ch)
{
    LMS7_logf(LMS7_TRACE, "RBB_Calibration_HighBand ch%c", ch);
    LMS7002M_set_mac_ch(self, ch);
    Modify_SPI_Reg_bits (self, 0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode);

    RBB_Algorithm_A(self); // Aproximate resistor value for RBB RBANKS (Algorithm A)

    RBB_Set_Cal_Path(self, 8); // Set control signals to path 7 (RX LowBand)

    RBB_Algorithm_B(self); // Calibrate and Record the low frequency output amplitude (Algorithm B)

    RBB_Algorithm_F(self, RBB_37_0MHZ);// CalibrateByCap the output cuttoff frequency at 0,7 MHz and store
	RBB_Algorithm_F(self, RBB_66_0MHZ);// CalibrateByCap the output cuttoff frequency at 1,5 MHz MHz and store
	RBB_Algorithm_F(self, RBB_108_0MHZ);// CalibrateByCap the output cuttoff frequency at 2,5 MHz MHz and store

    return 0;
}

/***********************************************************************
 * Set calibration paths for RBB calibration
 * REG: ported from lms-suite
 **********************************************************************/
unsigned char RBB_Set_Cal_Path(LMS7002M_t *self, unsigned char path_no)
{
	LMS7_logf(LMS7_TRACE, "RBB_Set_Cal_Path(path=%u)", path_no);
	switch (path_no)
	{
		case 7: // RX  LPF Low Section Verification
			// RBB Control Bits
			Modify_SPI_Reg_bits(self, 0x010C, 1, 1, 1);//PD_TIA_RFE == 1
			Modify_SPI_Reg_bits(self, 0x0115, 3, 3, 1);//PD_LPFH_RBB == 1
			Modify_SPI_Reg_bits(self, 0x0115, 2, 2, 0);//PD_LPFL_RBB == 0
			Modify_SPI_Reg_bits(self, 0x0115, 15, 15, 0);//EN_LB_LPFH_RBB == 0
			Modify_SPI_Reg_bits(self, 0x0115, 14, 14, 1);//EN_LB_LPFL_RBB == 1
			Modify_SPI_Reg_bits(self, 0x0118, 15, 13, 0);//INPUT_CTL_PGA_RBB == 0
			Modify_SPI_Reg_bits(self, 0x0119, 15, 15, 1);//OSW_PGA_RBB == 1
			break;

		case 8: // RX  LPF High Section Verification
			// RBB Control Bits
			Modify_SPI_Reg_bits(self, 0x010C, 1, 1, 1);//PD_TIA_RFE == 1
			Modify_SPI_Reg_bits(self, 0x0115, 3, 3, 0);//PD_LPFH_RBB == 0
			Modify_SPI_Reg_bits(self, 0x0115, 2, 2, 1);//PD_LPFL_RBB == 1
			Modify_SPI_Reg_bits(self, 0x0115, 15, 15, 1);//EN_LB_LPFH_RBB == 1
			Modify_SPI_Reg_bits(self, 0x0115, 14, 14, 0);//EN_LB_LPFL_RBB == 0
			Modify_SPI_Reg_bits(self, 0x0118, 15, 13, 1);//INPUT_CTL_PGA_RBB == 1
			Modify_SPI_Reg_bits(self, 0x0119, 15, 15, 1);//OSW_PGA_RBB == 1
			break;
	}

	// TBB Control Bits
	Modify_SPI_Reg_bits(self, 0x010A, 15, 14, 0);//TSTIN_TBB == 0
	Modify_SPI_Reg_bits(self, 0x0105, 4, 4, 0);//PD_LPFH_TBB == 0
	Modify_SPI_Reg_bits(self, 0x0105, 14, 12, 1);//LOOPB_TBB<1:0> == 1
	Modify_SPI_Reg_bits(self, 0x0105, 1, 1, 0);//(PD_LPFS5_TBB == 0 OR PD_LPFLAD_TBB == 0)  (pre-emphasis OFF)
	LMS7_logf(LMS7_DEBUG, "%s: %d", __FUNCTION__, path_no);
}

/***********************************************************************
 * RBB Algorithm A
 * REG: I touched this. I think it compares well to the LMS suite.
 **********************************************************************/
void RBB_Algorithm_A(LMS7002M_t *self)
{
    LMS7_logf(LMS7_TRACE, "RBB_Algorithm_A");
    unsigned char R_CTL_LPF_RBB;

    R_CTL_LPF_RBB = (unsigned char)(16 * Resistor_calibration(self)); // Default control value multiply by ratio
    Modify_SPI_Reg_bits (self, 0x0116, 15, 11, R_CTL_LPF_RBB);

    self->RBB_RBANK[self->MIMO_ch] = R_CTL_LPF_RBB; // Store RBANK Values (R_CTL_LPF_RBB)

    LMS7_logf(LMS7_DEBUG, "%s: R_CTL_LPF_RBB = %d", __FUNCTION__, R_CTL_LPF_RBB);
}

/***********************************************************************
 * RBB Algorithm B
 * REG: I copied/modified this from lms-suite
 **********************************************************************/
unsigned char RBB_Algorithm_B(LMS7002M_t *self)
{
    unsigned short ADCOUT;
    unsigned char CG_IAMP_TBB, gain_inc;

    // Set DAC output to 100kHz (0.1MHz) single tone.
    Set_NCO_Freq(self, 0.1, self->cgen_freq/1000, false);

    //set nominal CG_IAMP_TBB value
    CG_IAMP_TBB = 24;
    Modify_SPI_Reg_bits(self, 0x0108, 15, 10, CG_IAMP_TBB);
    // AGC Mode = 1 (RSSI mode)
    Modify_SPI_Reg_bits(self, 0x040A, 13, 12, 1);

    //RSSI value // Measure the output level at the ADC input
	ADCOUT = Get_SPI_Reg_bits(self, 0x040B, 15, 0);

	if(ADCOUT < 52428)
	{
		gain_inc = 1; //is it less then 80% of full scale swing (52428 (80% of 16 bits))
	} else {
		gain_inc = 0;
	}

	while (1)
	{
		//RSSI value // Measure the output level at the ADC input
		ADCOUT = Get_SPI_Reg_bits(self, 0x040B, 15, 0);
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

		Modify_SPI_Reg_bits(self, 0x0108, 15, 10, CG_IAMP_TBB); //write val to reg
	}

	LMS7_logf(LMS7_DEBUG, "%s: ADCOUT %d", __FUNCTION__, ADCOUT);

	return ADCOUT; // Record the exact value of the amplitude in for later on comparison.
}

/***********************************************************************
 * RBB Algorithm F
 **********************************************************************/
unsigned char RBB_Algorithm_F(LMS7002M_t *self, unsigned char Band_id)
{
    unsigned short ADCOUT, CONTROL;
    unsigned short LowFreqAmp;
    unsigned char low_band;

    Modify_SPI_Reg_bits (self, 0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode)

    if(Band_id <= RBB_20MHZ) //low band
    {
        low_band = 1; // CONTROL=C_CTL_LPFL_RBB
        CONTROL = 0xFF; // Set the CONTROL to maximum value. This should bring the output cutt-off frequency to minimum.
    }
    else //high band
    {
        low_band = 0; // CONTROL=C_CTL_LPFH_RBB
        CONTROL = 0x7FF; // Set the CONTROL to maximum value. This should bring the output cutt-off frequency to minimum.
    }


	if (low_band) Modify_SPI_Reg_bits(self, 0x0117, 10, 0, CONTROL); // write to C_CTL_LPFL_RBB
		else Modify_SPI_Reg_bits(self, 0x0116, 7, 0, CONTROL); // write to C_CTL_LPFH_RBB

	LowFreqAmp = RBB_Algorithm_B(self); // Apply (Algorithm B).
	Set_NCO_Freq(self, RBB_CalFreq[Band_id], self->cgen_freq/1000, false);
//	Set_NCO_Freq (RBB_CalFreq[Band_id], fclk, false); // Apply a single tone frequency at CalFreq.

	while (1)
	{
		if (low_band) Modify_SPI_Reg_bits(self, 0x0117, 10, 0, CONTROL); // write to C_CTL_LPFL_RBB
			else Modify_SPI_Reg_bits(self, 0x0116, 7, 0, CONTROL); // write to C_CTL_LPFH_RBB

		ADCOUT = Get_SPI_Reg_bits(self, 0x040B, 15, 0); //RSSI value // Measure the value of the amplitude at the ADC input. This value should be lower than LowFreqAmp.

		if (! (ADCOUT < LowFreqAmp)) break; //If it is lower than LowFreqAmp repeat cycle
		if (CONTROL == 0) break;
		CONTROL--; // Decrease the CONTROL value by one.
	}

	self->RBB_CBANK[self->MIMO_ch][Band_id] = CONTROL; // Store CBANK Values

	LMS7_logf(LMS7_DEBUG, "%s: CH %d, Band %d, CONTROL = %d", __FUNCTION__, self->MIMO_ch, Band_id, CONTROL);
}
