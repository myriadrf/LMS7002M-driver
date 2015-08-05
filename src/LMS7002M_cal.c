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
#include <LMS7002M/LMS7002M_logger.h>

/***********************************************************************
 * Mimo control wrapper
 **********************************************************************/
void MIMO_Ctrl (LMS7002M_t *self, unsigned char ch)
{
    LMS7002M_set_mac_ch(self, (ch == 0)?LMS_CHA:LMS_CHB);
}

/***********************************************************************
 * NCO for test signal
 **********************************************************************/
void Set_NCO_Freq (LMS7002M_t *self, float Freq_MHz, float refClk_MHz, bool Rx)
{
    unsigned long fcw = (Freq_MHz/refClk_MHz)*(4294967296.0);//pow(2.0, 32);
    if(Rx)
    {
        Modify_SPI_Reg_bits (self, 0x0440, 4, 0, 0); //TX SEL[3:0] = 0 & MODE = 0
        Modify_SPI_Reg_bits (self, 0x0442, 15, 0, (fcw >> 16)); //FCW0[31:16]: NCO frequency control word register 0. MSB part.
        Modify_SPI_Reg_bits (self, 0x0443, 15, 0, fcw); //FCW0[15:0]: NCO frequency control word register 0. LSB part.
    }
    else
    {
        Modify_SPI_Reg_bits (self, 0x0240, 4, 0, 0); //TX SEL[3:0] = 0 & MODE = 0
        Modify_SPI_Reg_bits (self, 0x0242, 15, 0, (fcw >> 16)); //FCW0[31:16]: NCO frequency control word register 0. MSB part.
        Modify_SPI_Reg_bits (self, 0x0243, 15, 0, fcw); //FCW0[15:0]: NCO frequency control word register 0. LSB part.
    }
}

/***********************************************************************
 * spi access for cal algorithms
 **********************************************************************/
/*
void Modify_SPI_Reg_bits (LMS7002M_t *self, unsigned short SPI_reg_addr, unsigned char MSB_bit, unsigned char LSB_bit, unsigned short new_bits_data)
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

    SPI_reg_data = LMS7002M_spi_read(self, SPI_reg_addr); //read current SPI reg data

    SPI_reg_data &= mask;//clear bits
    SPI_reg_data |= new_bits_data; //set bits with new data

    LMS7002M_spi_write(self, SPI_reg_addr, SPI_reg_data); //write modified data back to SPI reg

    //for debug purposes to track regs touched by cal
    //modifiedRegs.insert(SPI_reg_addr);

    //apply new value to the local register struct
    LMS7002M_regs_set(self->regs, SPI_reg_addr, SPI_reg_data);
}

unsigned short Get_SPI_Reg_bits (LMS7002M_t *self, unsigned short SPI_reg_addr, unsigned char MSB_bit, unsigned char LSB_bit)
{
    unsigned short bits, mask;
    unsigned char bits_number;

    bits_number = MSB_bit - LSB_bit + 1;

    mask = 0xFFFF;

    //removing unnecessary bits from mask
    mask = mask << (16 - bits_number);
    mask = mask >> (16 - bits_number);

    bits = LMS7002M_spi_read(self, SPI_reg_addr); //read current data

    bits = bits >> LSB_bit; //shift bits to LSB

    bits &= mask; //mask bits

    return bits;
}
*/

/***********************************************************************
 * resistor calibration
 **********************************************************************/
float Resistor_calibration (LMS7002M_t *self)
{
    LMS7_log(LMS7_DEBUG, "Resistor calibration started");
    unsigned char RP_CALIB_BIAS, RP_CALIB_BIAS_cal;
    unsigned short BestValue, ADCOUT;
    float ratio;

    //bypass mode disabled -- required for RSSI readback
    self->regs->reg_0x040c_agc_byp = 0;
    LMS7002M_regs_spi_write(self, 0x040c);

    RP_CALIB_BIAS_cal = 16;
    RP_CALIB_BIAS = 0;
    Modify_SPI_Reg_bits (self, 0x0084, 10, 6, RP_CALIB_BIAS); // write RP_CALIB_BIAS value
    Modify_SPI_Reg_bits (self, 0x0084, 12, 11, 1); // MUX_BIAS_OUT = 1
    Modify_SPI_Reg_bits (self, 0x040A, 13, 12, 1); // AGC Mode = 1 (RSSI mode)
    Modify_SPI_Reg_bits(self, 0x0400, 15, 15, 0); //Capture 0
    Modify_SPI_Reg_bits(self, 0x0400, 14, 13, 0); //Capsel 0 - RSSI

    while (RP_CALIB_BIAS <= 31)
    {
        Modify_SPI_Reg_bits(self, 0x0400, 15, 15, 0); //Capture 0
        Modify_SPI_Reg_bits(self, 0x0400, 15, 15, 1); //Capture 1
        ADCOUT = (Get_SPI_Reg_bits(self, 0x040F, 15, 0) << 2) | Get_SPI_Reg_bits(self, 0x040E, 1, 0); //RSSI value

        //REG: debug
        unsigned long capd_lo = LMS7002M_spi_read(self, 0x40E);
        unsigned long capd_hi = LMS7002M_spi_read(self, 0x40F);
        LMS7_logf(LMS7_TRACE, "%s: RP_CALIB_BIAS = %d, ADCOUT, = %d, CAPD = %X.%X", __FUNCTION__, RP_CALIB_BIAS, ADCOUT, capd_hi, capd_lo);

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
        Modify_SPI_Reg_bits (self, 0x0084, 10, 6, RP_CALIB_BIAS); // write RP_CALIB_BIAS value
    }
    Modify_SPI_Reg_bits(self, 0x0400, 15, 15, 0); //Capture 0
    Modify_SPI_Reg_bits (self, 0x0084, 10, 6, RP_CALIB_BIAS_cal); // set the control RP_CAL_BIAS to stored calibrated value
    ratio = 16.0/RP_CALIB_BIAS_cal; //calculate ratio
    LMS7_logf(LMS7_DEBUG, "%s: Resistor calibration finished = %f", __FUNCTION__, ratio);
    return ratio;
}
