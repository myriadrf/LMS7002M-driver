///
/// \file LMS7002M/LMS7002M_rxtsp.h
///
/// RX DSP chain config for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2014-2015 Fairwaves, Inc.
/// Copyright (c) 2014-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once
#include <stdlib.h>
#include <LMS7002M/LMS7002M.h>

#ifdef __cplusplus
extern "C" {
#endif

LMS7002M_API void LMS7002M_rxtsp_init(LMS7002M_t *self, const LMS7002M_chan_t channel)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs.reg_0x0400_en = 1;
    self->regs.reg_0x0400_bstart = 0;
    self->regs.reg_0x0400_insel = REG_0X0400_INSEL_LML; //r19 regs - probably means baseband input
    LMS7002M_regs_spi_write(self, 0x0400);

    self->regs.reg_0x0403_hbd_ovr = REG_0X0403_HBD_OVR_BYPASS;

    self->regs.reg_0x040a_agc_mode = REG_0X040A_AGC_MODE_BYPASS;

    self->regs.reg_0x040c_cmix_byp = 1;
    self->regs.reg_0x040c_agc_byp = 1;
    self->regs.reg_0x040c_gfir3_byp = 1;
    self->regs.reg_0x040c_gfir2_byp = 1;
    self->regs.reg_0x040c_gfir1_byp = 1;
    self->regs.reg_0x040c_dc_byp = 1;
    self->regs.reg_0x040c_gc_byp = 1;
    self->regs.reg_0x040c_ph_byp = 1;

    LMS7002M_regs_spi_write(self, 0x0400);
    LMS7002M_regs_spi_write(self, 0x0403);
    LMS7002M_regs_spi_write(self, 0x040a);
    LMS7002M_regs_spi_write(self, 0x040c);
}

LMS7002M_API void LMS7002M_rxtsp_tsg_const(LMS7002M_t *self, const LMS7002M_chan_t channel, const int valI, const int valQ)
{
    LMS7002M_set_mac_ch(self, channel);

    //muxes
    self->regs.reg_0x0400_tsgmode = REG_0X0400_TSGMODE_DC;
    self->regs.reg_0x0400_insel = REG_0X0400_INSEL_TEST;
    LMS7002M_regs_spi_write(self, 0x0400);

    //load I
    self->regs.reg_0x040b_dc_reg = valI;
    LMS7002M_regs_spi_write(self, 0x040b);
    self->regs.reg_0x0400_tsgdcldi = 0;
    LMS7002M_regs_spi_write(self, 0x0400);
    self->regs.reg_0x0400_tsgdcldi = 1;
    LMS7002M_regs_spi_write(self, 0x0400);
    self->regs.reg_0x0400_tsgdcldi = 0;
    LMS7002M_regs_spi_write(self, 0x0400);

    //load Q
    self->regs.reg_0x040b_dc_reg = valQ;
    LMS7002M_regs_spi_write(self, 0x040b);
    self->regs.reg_0x0400_tsgdcldq = 0;
    LMS7002M_regs_spi_write(self, 0x0400);
    self->regs.reg_0x0400_tsgdcldq = 1;
    LMS7002M_regs_spi_write(self, 0x0400);
    self->regs.reg_0x0400_tsgdcldq = 0;
    LMS7002M_regs_spi_write(self, 0x0400);
}

LMS7002M_API void LMS7002M_rxtsp_tsg_tone(LMS7002M_t *self, const LMS7002M_chan_t channel)
{
    LMS7002M_set_mac_ch(self, channel);

    //muxes
    self->regs.reg_0x0400_tsgmode = REG_0X0400_TSGMODE_NCO;
    self->regs.reg_0x0400_insel = REG_0X0400_INSEL_TEST;
    LMS7002M_regs_spi_write(self, 0x0400);

    self->regs.reg_0x0400_tsgfcw = REG_0X0400_TSGFCW_DIV8;
    LMS7002M_regs_spi_write(self, 0x0400);
}

#ifdef __cplusplus
}
#endif
