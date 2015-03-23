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
    //Current Amplifier Low Section Verification.
    //TSTIN_TBB == 0 & PD_LPFH_TBB == 0  &  LOOPB_TBB<1:0> == 1 & (PD_LPFS5_TBB == 0 OR PD_LPFLAD_TBB == 0) (Digital Pre-Emphasis = OFF)
    //INPUT_CTL_PGA_RBB == 3 & PD_LPFL_RBB == 1 & PD_LPFH_RBB == 1 & PD_TIA_RFE == 1 & OSW_PGA_RBB ==0.
    if (path == 1)
    {
        self->regs.reg_0x010a_tstin_tbb = 0;
        self->regs.reg_0x0105_pd_lpfh_tbb = 0;
        self->regs.reg_0x0105_loopb_tbb = 1;
        self->regs.reg_0x0105_pd_lpfs5_tbb = 0; //OR...
        self->regs.reg_0x0105_pd_lpflad_tbb = 0;

        self->regs.reg_0x0118_input_ctl_pga_rbb = 3;
        self->regs.reg_0x0115_pd_lpfl_rbb = 1;
        self->regs.reg_0x0115_pd_lpfh_rbb = 1;
        self->regs.reg_0x010c_pd_tia_rfe = 1;
        self->regs.reg_0x0119_osw_pga_rbb = 0;
    }

    //Current Amplifier High Section testing.
    //TSTIN_TBB == 0  & PD_LPFH_TBB == 1 &  LOOPB_TBB<1:0> == 1 & (PD_LPFS5_TBB == 1 & PD_LPFLAD_TBB == 1) (Digital Pre-Emphasis = OFF)
    //INPUT_CTL_PGA_RBB == 3 & PD_LPFL_RBB == 1 & PD_LPFH_RBB == 1 & PD_TIA_RFE == 1 & OSW_PGA_RBB ==0.
    if (path == 2)
    {
        self->regs.reg_0x010a_tstin_tbb = 0;
        self->regs.reg_0x0105_pd_lpfh_tbb = 1;
        self->regs.reg_0x0105_loopb_tbb = 1;
        self->regs.reg_0x0105_pd_lpfs5_tbb = 1;
        self->regs.reg_0x0105_pd_lpflad_tbb = 1;

        self->regs.reg_0x0118_input_ctl_pga_rbb = 3;
        self->regs.reg_0x0115_pd_lpfl_rbb = 1;
        self->regs.reg_0x0115_pd_lpfh_rbb = 1;
        self->regs.reg_0x010c_pd_tia_rfe = 1;
        self->regs.reg_0x0119_osw_pga_rbb = 0;
    }

    //Current Amplifier High Section testing.
    //TSTIN_TBB == 0 & PD_LPFH_TBB == 1 & LOOPB_TBB<1:0> == 2 & PD_LPFS5_TBB == 1 & PD_LPFLAB _TBB == 0 & BYPLADDER_TBB == 0  (Digital Pre-Emphasis = OFF)
    //INPUT_CTL_PGA_RBB == 3 & PD_LPFL_RBB == 1 & PD_LPFH_RBB == 1 & PD_TIA_RFE == 1 & OSW_PGA_RBB ==0. 
    if (path == 3)
    {
        self->regs.reg_0x010a_tstin_tbb = 0;
        self->regs.reg_0x0105_pd_lpfh_tbb = 1;
        self->regs.reg_0x0105_loopb_tbb = 2;
        self->regs.reg_0x0105_pd_lpfs5_tbb = 1;
        self->regs.reg_0x0105_pd_lpflad_tbb = 0;
        self->regs.reg_0x010a_bypladder_tbb = 0;

        self->regs.reg_0x0118_input_ctl_pga_rbb = 3;
        self->regs.reg_0x0115_pd_lpfl_rbb = 1;
        self->regs.reg_0x0115_pd_lpfh_rbb = 1;
        self->regs.reg_0x010c_pd_tia_rfe = 1;
        self->regs.reg_0x0119_osw_pga_rbb = 0;
    }

    //TX REALPOLE Low Section testing
    //TSTIN_TBB == 0 & PD_LPFH_TBB == 1 & LOOPB_TBB<1:0> == 3 & PD_LPFS5_TBB == 0 & PD_LPFLAB _TBB == 1 & BYPLADDER_TBB == 1 (Digital Pre-Emphasis = ON)
    //INPUT_CTL_PGA_RBB == 3 & PD_LPFL_RBB == 1 & PD_LPFH_RBB == 1 & PD_TIA_RFE == 1 & OSW_PGA_RBB ==0.
    if (path == 4)
    {
        self->regs.reg_0x010a_tstin_tbb = 0;
        self->regs.reg_0x0105_pd_lpfh_tbb = 1;
        self->regs.reg_0x0105_loopb_tbb = 3;
        self->regs.reg_0x0105_pd_lpfs5_tbb = 0;
        self->regs.reg_0x0105_pd_lpflad_tbb = 1;
        self->regs.reg_0x010a_bypladder_tbb = 1;

        self->regs.reg_0x0118_input_ctl_pga_rbb = 3;
        self->regs.reg_0x0115_pd_lpfl_rbb = 1;
        self->regs.reg_0x0115_pd_lpfh_rbb = 1;
        self->regs.reg_0x010c_pd_tia_rfe = 1;
        self->regs.reg_0x0119_osw_pga_rbb = 0;
    }

    //TX REALPOLE Low Section testing
    //TSTIN_TBB == 0 & PD_LPFH_TBB == 1 & LOOPB_TBB<1:0> == 3 & PD_LPFS5_TBB == 0 & PD_LPFLAB _TBB == 0 & BYPLADDER_TBB == 0  (Digital Pre-Emphasis = ON)
    //INPUT_CTL_PGA_RBB == 3 & PD_LPFL_RBB == 1 & PD_LPFH_RBB == 1 & PD_TIA_RFE == 1 & OSW_PGA_RBB ==0.
    if (path == 5)
    {
        self->regs.reg_0x010a_tstin_tbb = 0;
        self->regs.reg_0x0105_pd_lpfh_tbb = 1;
        self->regs.reg_0x0105_loopb_tbb = 3;
        self->regs.reg_0x0105_pd_lpfs5_tbb = 0;
        self->regs.reg_0x0105_pd_lpflad_tbb = 0;
        self->regs.reg_0x010a_bypladder_tbb = 0;

        self->regs.reg_0x0118_input_ctl_pga_rbb = 3;
        self->regs.reg_0x0115_pd_lpfl_rbb = 1;
        self->regs.reg_0x0115_pd_lpfh_rbb = 1;
        self->regs.reg_0x010c_pd_tia_rfe = 1;
        self->regs.reg_0x0119_osw_pga_rbb = 0;
    }

    //TX BIQUAD High Section testing
    //TSTIN_TBB == 0 & PD_LPFH_TBB == 0 & LOOPB_TBB<1:0> == 3 & PD_LPFS5_TBB == 1 & PD_LPFLAD_TBB == 1 & BYPLADDER_TBB == 0 (Digital Pre-Emphasis = OFF)
    //INPUT_CTL_PGA_RBB == 3 & PD_LPFL_RBB == 1 & PD_LPFH_RBB == 1 & PD_TIA_RFE == 1 & OSW_PGA_RBB ==0.
    if (path == 6)
    {
        self->regs.reg_0x010a_tstin_tbb = 0;
        self->regs.reg_0x0105_pd_lpfh_tbb = 0;
        self->regs.reg_0x0105_loopb_tbb = 3;
        self->regs.reg_0x0105_pd_lpfs5_tbb = 1;
        self->regs.reg_0x0105_pd_lpflad_tbb = 1;
        self->regs.reg_0x010a_bypladder_tbb = 0;

        self->regs.reg_0x0118_input_ctl_pga_rbb = 3;
        self->regs.reg_0x0115_pd_lpfl_rbb = 1;
        self->regs.reg_0x0115_pd_lpfh_rbb = 1;
        self->regs.reg_0x010c_pd_tia_rfe = 1;
        self->regs.reg_0x0119_osw_pga_rbb = 0;
    }

    //TX BIQUAD High Section testing
    //TSTIN_TBB == 0 & PD_LPFH_TBB == 0  &  LOOPB_TBB<1:0> == 1 & (PD_LPFS5_TBB == 0 OR PD_LPFLAD_TBB == 0)  (pre-emphasis OFF)
    //PD_TIA_RFE == 1 & PD_LPFH_RBB == 1 & PD_LPFL_RBB == 0 & EN_LB_LPFH_RBB == 0 & EN_LB_LPFL_RBB == 1 & INPUT_CTL_PGA_RBB == 0 & OSW_PGA_RBB == 1
    if (path == 7)
    {
        self->regs.reg_0x010a_tstin_tbb = 0;
        self->regs.reg_0x0105_pd_lpfh_tbb = 0;
        self->regs.reg_0x0105_loopb_tbb = 1;
        self->regs.reg_0x0105_pd_lpfs5_tbb = 0; //OR...
        self->regs.reg_0x0105_pd_lpflad_tbb = 0;

        self->regs.reg_0x010c_pd_tia_rfe = 1;
        self->regs.reg_0x0115_pd_lpfh_rbb = 1;
        self->regs.reg_0x0115_pd_lpfl_rbb = 0;
        self->regs.reg_0x0115_en_lb_lpfh_rbb = 0;
        self->regs.reg_0x0115_en_lb_lpfl_rbb = 1;
        self->regs.reg_0x0118_input_ctl_pga_rbb = 0;
        self->regs.reg_0x0119_osw_pga_rbb = 1;
    }

    //RX  LPF High Section Verification
    //TSTIN_TBB == 0 & PD_LPFH_TBB == 0  &  LOOPB_TBB<1:0> == 1 & (PD_LPFS5_TBB == 0 OR PD_LPFLAD_TBB == 0) (pre-emphasis OFF)
    //PD_TIA_RFE == 1 & PD_LPFH_RBB == 0 & PD_LPFL_RBB == 1 & EN_LB_LPFH_RBB == 1 & EN_LB_LPFL_RBB == 0 & INPUT_CTL_PGA_RBB == 1 & OSW_PGA_RBB == 1
    if (path == 8)
    {
        self->regs.reg_0x010a_tstin_tbb = 0;
        self->regs.reg_0x0105_pd_lpfh_tbb = 0;
        self->regs.reg_0x0105_loopb_tbb = 1;
        self->regs.reg_0x0105_pd_lpfs5_tbb = 0; //OR...
        self->regs.reg_0x0105_pd_lpflad_tbb = 0;

        self->regs.reg_0x010c_pd_tia_rfe = 1;
        self->regs.reg_0x0115_pd_lpfh_rbb = 0;
        self->regs.reg_0x0115_pd_lpfl_rbb = 1;
        self->regs.reg_0x0115_en_lb_lpfh_rbb = 1;
        self->regs.reg_0x0115_en_lb_lpfl_rbb = 0;
        self->regs.reg_0x0118_input_ctl_pga_rbb = 1;
        self->regs.reg_0x0119_osw_pga_rbb = 1;
    }

    LMS7002M_regs_spi_write(self, 0x010a);
    LMS7002M_regs_spi_write(self, 0x0105);
    LMS7002M_regs_spi_write(self, 0x0118);
    LMS7002M_regs_spi_write(self, 0x0115);
    LMS7002M_regs_spi_write(self, 0x010c);
    LMS7002M_regs_spi_write(self, 0x0119);
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

    //apply new value to the local register struct
    LMS7002M_regs_set(&self->regs, addr, newReg);
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
