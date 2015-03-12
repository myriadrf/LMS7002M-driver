///
/// \file LMS7002M/LMS7002M_cal_tbb.h
///
/// TX baseband calibration algorithms for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once
#include <stdlib.h>
#include <LMS7002M/LMS7002M.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline void Algorithm_A_TBB(LMS7002M_t *self);
static inline unsigned char Algorithm_B_TBB(LMS7002M_t *self, unsigned short *LowFreqAmp)
{
    return Algorithm_B_RBB(self, LowFreqAmp);
}
static inline unsigned char Algorithm_C_TBB(LMS7002M_t *self, unsigned char Band_id, unsigned short LowFreqAmp, unsigned char ch);
static inline unsigned char Algorithm_D_TBB(LMS7002M_t *self, unsigned char Band_id, unsigned short LowFreqAmp);
static inline unsigned char Algorithm_E_TBB(LMS7002M_t *self, unsigned char Band_id, unsigned char MIMO_ch);

#define TBB_11_0MHZ 0
#define TBB_18_5MHZ 0
#define TBB_38_0MHZ 1
#define TBB_54_0MHZ 2

/***********************************************************************
 * TBB config save/restore
 **********************************************************************/
static inline void Save_config_TBB(LMS7002M_t *self, int *backup)
{
    for (size_t i = 0;; i++)
    {
        int addr = 0x0105+i;
        backup[i] = LMS7002M_spi_read(self, addr);
        if (addr == 0x010B) break;
    }
}

static inline void Restore_config_TBB(LMS7002M_t *self, int *backup)
{
    for (size_t i = 0;; i++)
    {
        int addr = 0x0105+i;
        LMS7002M_spi_write(self, addr, backup[i]);
        if (addr == 0x010B) break;
    }
}

/***********************************************************************
 * TBB calibration path
 **********************************************************************/
static inline void Set_cal_path_TBB(LMS7002M_t *self, const int path)
{
    //TODO
    //3
    //6
}

/***********************************************************************
 * TBB low band calibration
 **********************************************************************/
static inline unsigned char Calibration_LowBand_TBB(LMS7002M_t *self, unsigned char ch)
{
    unsigned char result;
    int backup[10];
    Save_config_TBB (self, backup); //save current configuration
    MIMO_Ctrl (self, ch);
    Modify_SPI_Reg_bits (self, 0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode)

    Algorithm_A_TBB(self);

    Set_cal_path_TBB (self, 3); // Set control signals to path 3

    //TODO

    Restore_config_TBB (self, backup);
    //restore configuration
    return 1;
}

/***********************************************************************
 * TBB high band calibration
 **********************************************************************/
static inline unsigned char Calibration_HighBand_TBB(LMS7002M_t *self, unsigned char ch)
{
    unsigned char result;
    int backup[10];
    Save_config_TBB (self, backup); //save current configuration
    MIMO_Ctrl (self, ch);
    Modify_SPI_Reg_bits (self, 0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode)
    Set_cal_path_TBB (self, 6); // Set control signals to path 6
    Algorithm_E_TBB (self, TBB_18_5MHZ, ch);// CalibrateByRes the output cutoff frequency (Algorithm E)
    Algorithm_E_TBB (self, TBB_38_0MHZ, ch);// CalibrateByRes the output cutoff frequency (Algorithm E)
    Algorithm_E_TBB (self, TBB_54_0MHZ, ch);// CalibrateByRes the output cutoff frequency (Algorithm E)
    Restore_config_TBB (self, backup);
    //restore configuration
    return 1;
}

/***********************************************************************
 * TBB Algorithm A
 **********************************************************************/
static inline void Algorithm_A_TBB(LMS7002M_t *self)
{
    unsigned char RCAL_LPFLAD_TBB;
    float ratio;
    Resistor_calibration(self, &ratio);
    RCAL_LPFLAD_TBB = (unsigned char)(193 * ratio); // default control value )193 - when 11MHz) Multiply by ratio
    Modify_SPI_Reg_bits (self, 0x0109, 7, 0, RCAL_LPFLAD_TBB);
}

/***********************************************************************
 * TBB Algorithm C
 **********************************************************************/
static inline unsigned char Algorithm_C_TBB(LMS7002M_t *self, unsigned char Band_id, unsigned short LowFreqAmp, unsigned char MIMO_ch)
{
    unsigned short ADCOUT/*, LowFreqAmp*/;
    unsigned char CONTROL;
    Set_NCO_Freq (self, self->TBB_CalFreq[Band_id]); // 1 Apply a single tone frequency at “CalFreq”.
    CONTROL = 31; // 2 Set the “CCAL_LPFLAD_TBB” to maximum value.
    Modify_SPI_Reg_bits (self, 0x010A, 12, 8, CONTROL);

    while (1)
    {
        ADCOUT = Get_SPI_Reg_bits(self, 0x040B, 15, 0); //RSSI value // Measure the value of the amplitude at the ADC input. This value should be lower

        if (ADCOUT >= LowFreqAmp) break; //If amplitude is lower than LowFreqAmp repeat cycle
        if (CONTROL == 0) return 0;
        CONTROL--; // Decrease the control value CCAL_LPFLAD_TBB by one step.
        Modify_SPI_Reg_bits (self, 0x010A, 12, 8, CONTROL);
    }
    self->TBB_CBANK[MIMO_ch] = CONTROL; // Store the value of CCAL_LPFLAD_TBB as the calibrated CBANK value of TBB.
}

/***********************************************************************
 * TBB Algorithm D
 **********************************************************************/
static inline unsigned char Algorithm_D_TBB(LMS7002M_t *self, unsigned char Band_id, unsigned short LowFreqAmp)
{
    unsigned short ADCOUT;
    unsigned char inc, Zero_Freq = 127;
    Set_NCO_Freq (self, self->TBB_CalFreq[Band_id]); // 1 Apply a single tone at frequency equal to “CalFreq”
    ADCOUT = Get_SPI_Reg_bits(self, 0x040B, 15, 0); //RSSI value
    if(ADCOUT > LowFreqAmp) inc = 0; //If greater, then the pre-emphasis zero is faster than the real pole
    else inc = 1;
    while (1)
    {
        ADCOUT = Get_SPI_Reg_bits(self, 0x040B, 15, 0); //RSSI value // Measure the output level at the ADC input

        if (inc)
        {
            if(ADCOUT >= 52428) break;
        }
        else
        {
            if(ADCOUT <= 52428) break;
        }

        if( (Zero_Freq == 0) || (Zero_Freq == 255)) //gain limit reached
        {
            return 0;
            break;
        }

        if(inc) Zero_Freq++;
        else Zero_Freq--;
    }
}

/***********************************************************************
 * TBB Algorithm E
 **********************************************************************/
static inline unsigned char Algorithm_E_TBB(LMS7002M_t *self, unsigned char Band_id, unsigned char MIMO_ch)
{
    unsigned short ADCOUT, LowFreqAmp;
    unsigned char low_band, CONTROL;
    CONTROL = 0; // Set the CONTROL to zero. This should bring the output cutt-off frequency to minimum.

    if(Band_id <= TBB_11_0MHZ) //If(CalFreq) <=11MHz, then CONTROL=RCAL_LPFLAD_TBB, else, CONTROL=RCAL_LPFH_TBB
    {
        low_band = 1; // CONTROL=RCAL_LPFLAD_TBB
        Modify_SPI_Reg_bits (self, 0x0109, 7, 0, CONTROL); // write to RCAL_LPFLAD_TBB
    }
    else
    {
        low_band = 0; // CONTROL=RCAL_LPFH_TBB
        Modify_SPI_Reg_bits (self, 0x0109, 15, 8, CONTROL); // write to RCAL_LPFH_TBB
    }

    if (Algorithm_B_TBB (self, &LowFreqAmp) != 1) return 0; // Calibrate and Record the low frequency output amplitude (Algorithm B)
    Set_NCO_Freq (self, self->TBB_CalFreq[Band_id]); // Apply a single tone frequency at CalFreq.

    while (1)
    {
        ADCOUT = Get_SPI_Reg_bits(self, 0x040B, 15, 0); //RSSI value // Measure the value of the amplitude at the ADC input. This value should be lower

        if (ADCOUT >= LowFreqAmp) break; //If it is lower than LowFreqAmp repeat cycle
        if (CONTROL == 0xFF) break;
        CONTROL++; // Increase the CONTROL value by one.

        if (low_band) Modify_SPI_Reg_bits (self, 0x0109, 7, 0, CONTROL); // write to RCAL_LPFLAD_TBB
        else Modify_SPI_Reg_bits (self, 0x0109, 15, 8, CONTROL); // write to RCAL_LPFH_TBB
    }

    // 8 Return the value of CONTROL.
    self->TBB_RBANK[MIMO_ch][Band_id] = CONTROL; // Store RBANK Values

    return 1;
}

#ifdef __cplusplus
}
#endif
