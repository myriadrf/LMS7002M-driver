///
/// \file LMS7002M_cal.c
///
/// Calibration algorithms for the LMS7002M C driver.
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

/***********************************************************************
 * channel selection
 **********************************************************************/
void MIMO_Ctrl(LMS7002M_t *self, unsigned char ch)
{
    LMS7002M_set_mac_ch(self, (ch == 0)?LMS_CHA:LMS_CHB);
}

/***********************************************************************
 * Set calibration path
 **********************************************************************/
LMS7002M_API void LMS7002M_cal_set_path(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path)
{
    
}

/***********************************************************************
 * CAL config save/restore
 **********************************************************************/
void Save_config_CAL(LMS7002M_t *self, int *backup)
{
    size_t i = 0;
    for (int addr = 0x0115; addr <= 0x011B; addr++)
    {
        backup[i++] = LMS7002M_spi_read(self, addr);
    }
    for (int addr = 0x0105; addr <= 0x010B; addr++)
    {
        backup[i++] = LMS7002M_spi_read(self, addr);
    }
}

void Restore_config_CAL(LMS7002M_t *self, int *backup)
{
    size_t i = 0;
    for (int addr = 0x0115; addr <= 0x011B; addr++)
    {
        LMS7002M_spi_write(self, addr, backup[i++]);
    }
    for (int addr = 0x0105; addr <= 0x010B; addr++)
    {
        LMS7002M_spi_write(self, addr, backup[i++]);
    }
}

/***********************************************************************
 * spi access for cal algorithms
 **********************************************************************/
int Get_SPI_Reg_bits(LMS7002M_t *self, const int addr, const int bitHigh, const int bitLow)
{
    const int shift = bitLow;
    const int width = (bitHigh - bitLow) + 1;
    const int mask = (1 << width)-1;
    const int val = LMS7002M_spi_read(self, addr);
    return (val >> shift) & mask;
}

void Modify_SPI_Reg_bits(LMS7002M_t *self, const int addr, const int bitHigh, const int bitLow, const int value)
{
    const int shift = bitLow;
    const int width = (bitHigh - bitLow) + 1;
    const int mask = (1 << width)-1;

    int oldReg = LMS7002M_spi_read(self, addr);
    int newReg = ((value & mask) << shift) | (oldReg & ~(mask<<shift));

    LMS7002M_spi_write(self, addr, newReg);
}

/***********************************************************************
 * resistor calibration
 **********************************************************************/
void Resistor_calibration(LMS7002M_t *self, float *ratio)
{
    unsigned char RP_CALIB_BIAS, RP_CALIB_BIAS_cal;
    unsigned short BestValue, ADCOUT;
    RP_CALIB_BIAS_cal = 16;
    RP_CALIB_BIAS = 0;
    Modify_SPI_Reg_bits (self, 0x0084, 10, 6, RP_CALIB_BIAS); // write RP_CALIB_BIAS value
    Modify_SPI_Reg_bits (self, 0x0084, 12, 11, 1); // MUX_BIAS_OUT = 1

    while (RP_CALIB_BIAS <= 31)
    {
        Modify_SPI_Reg_bits (self, 0x0084, 10, 6, RP_CALIB_BIAS); // write RP_CALIB_BIAS value
        ADCOUT = Get_SPI_Reg_bits(self, 0x040B, 15, 0); //RSSI value
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
    }

    Modify_SPI_Reg_bits (self, 0x0084, 10, 6, RP_CALIB_BIAS_cal); // set the control RP_CAL_BIAS to stored calibrated value
    *ratio = (float) 16/RP_CALIB_BIAS_cal; //calculate ratio
}
