///
/// \file LMS7002M_cal_tbb.c
///
/// TX baseband calibration algorithms for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_cal.h"
#include <LMS7002M/LMS7002M_logger.h>

const float TBB_CalFreq[TBB_ALL] = {18.5, 38.0, 54.0};

/***********************************************************************
 * Dispatch calibration
 **********************************************************************/
void LMS7002M_cal_tbb(LMS7002M_t *self, const LMS7002M_chan_t ch)
{
    self->MIMO_ch = ch; //stash for table storage offset later
    //NOT IMPLEMENTED! Calibration_LowBand_TBB(self, (ch==LMS_CHA)?0:1);
    Calibration_HighBand_TBB(self, (ch==LMS_CHA)?0:1);
}

/***********************************************************************
 * TBB low band calibration
 **********************************************************************/
int Calibration_LowBand_TBB(LMS7002M_t *self, unsigned char ch)
{
    MIMO_Ctrl (self, ch);
    //#warning Not finished!!!
    //not finished!!!!
    LMS7_log(LMS7_WARNING, "Calibration_LowBand_TBB not implemented");
    return -1;
}

/***********************************************************************
 * TBB high band calibration
 **********************************************************************/
int Calibration_HighBand_TBB(LMS7002M_t *self, unsigned char ch)
{
    MIMO_Ctrl (self, ch);

    Set_cal_path_TBB (self, 6); // Set control signals to path 6

    Algorithm_E_TBB (self, TBB_18_5MHZ);// CalibrateByRes the output cutoff frequency (Algorithm E)
    Algorithm_E_TBB (self, TBB_38_0MHZ);// CalibrateByRes the output cutoff frequency (Algorithm E)
    Algorithm_E_TBB (self, TBB_54_0MHZ);// CalibrateByRes the output cutoff frequency (Algorithm E)
    return 0;
}

/***********************************************************************
 * TBB calibration path
 **********************************************************************/
void Set_cal_path_TBB (LMS7002M_t *self, unsigned char path_no)
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
            Modify_SPI_Reg_bits (self, 0x010A, 15, 14, 0); // TSTIN_TBB == 0
            Modify_SPI_Reg_bits (self, 0x0105, 4, 4, 0); // PD_LPFH_TBB == 0
            Modify_SPI_Reg_bits (self, 0x0105, 14, 12, 3); // LOOPB_TBB<1:0> == 3
            Modify_SPI_Reg_bits (self, 0x0105, 1, 1, 1); // PD_LPFS5_TBB == 1
            Modify_SPI_Reg_bits (self, 0x0105, 2, 2, 1); // PD_LPFLAD_TBB == 1
            Modify_SPI_Reg_bits (self, 0x010A, 13, 13, 0); // BYPLADDER_TBB == 0 (Digital Pre-Emphasis = "OFF")
            break;
    }

    //RBB Control Bits
    Modify_SPI_Reg_bits (self, 0x0118, 15, 13, 3); // INPUT_CTL_PGA_RBB == 3
    Modify_SPI_Reg_bits (self, 0x0115, 2, 2, 1); // PD_LPFL_RBB == 1
    Modify_SPI_Reg_bits (self, 0x0115, 3, 3, 1); // PD_LPFH_RBB == 1
    Modify_SPI_Reg_bits (self, 0x010C, 1, 1, 1); // PD_TIA_RFE == 1
    Modify_SPI_Reg_bits (self, 0x0119, 15, 15, 0); // OSW_PGA_RBB ==0
}

/***********************************************************************
 * TBB Algorithm E
 **********************************************************************/
void Algorithm_E_TBB (LMS7002M_t *self, unsigned char Band_id)
{
    unsigned short ADCOUT;
    unsigned short LowFreqAmp;
    unsigned char low_band, CONTROL;

    Set_NCO_Freq (self, TBB_CalFreq[Band_id], self->cgen_freq/1e6, false); // Set CalFreq

    Modify_SPI_Reg_bits (self, 0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode)

    if(Band_id <= TBB_11_0MHZ) //If("CalFreq") <=11MHz, then CONTROL=RCAL_LPFLAD_TBB, else, CONTROL=RCAL_LPFH_TBB
    {
        low_band = 1; // CONTROL=RCAL_LPFLAD_TBB
    }
    else
    {
        low_band = 0; // CONTROL=RCAL_LPFH_TBB
    }

    CONTROL = 0; // Set the CONTROL to zero. This should bring the output cutt-off frequency to minimum.

    if (low_band) Modify_SPI_Reg_bits (self, 0x0109, 7, 0, CONTROL); // write to RCAL_LPFLAD_TBB
        else Modify_SPI_Reg_bits (self, 0x0109, 15, 8, CONTROL); // write to RCAL_LPFH_TBB

    LowFreqAmp = Algorithm_B_TBB (self); // Apply (Algorithm B).
    Set_NCO_Freq (self, TBB_CalFreq[Band_id], self->cgen_freq/1e6, false); // Apply a single tone frequency at "CalFreq".

    while (1)
    {
        if (low_band) Modify_SPI_Reg_bits (self, 0x0117, 10, 0, CONTROL); // write to C_CTL_LPFL_RBB
            else Modify_SPI_Reg_bits (self, 0x0116, 7, 0, CONTROL); // write to C_CTL_LPFH_RBB

        ADCOUT = Get_SPI_Reg_bits(self, 0x040B, 15, 0); //RSSI value // Measure the value of the amplitude at the ADC input. This value should be lower than "LowFreqAmp".

        if (! (ADCOUT < LowFreqAmp)) break; //If it is lower than "LowFreqAmp" repeat cycle
        if (CONTROL == 0xFF) break;
        CONTROL++; // Increase the CONTROL value by one.
    }

    // 8 Return the value of CONTROL.
    self->TBB_RBANK[self->MIMO_ch][Band_id] = CONTROL; // Store RBANK Values
}

/***********************************************************************
 * TBB Algorithm B
 **********************************************************************/
unsigned short Algorithm_B_TBB (LMS7002M_t *self)
{
    //same algorith as rbb???
    //JB: then call B_RBB....
    return 0;
}
