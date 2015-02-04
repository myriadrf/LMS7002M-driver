///
/// \file LMS7002M/LMS7002M_txtsp.h
///
/// TX DSP chain config for the LMS7002M C driver.
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

LMS7002M_API void LMS7002M_txtsp_init(LMS7002M_t *self, const LMS7002M_chan_t channel)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs.reg_0x0200_en = 1;
    self->regs.reg_0x0200_bstart = 0;
    self->regs.reg_0x0200_insel = REG_0X0200_INSEL_LML;
    LMS7002M_regs_spi_write(self, 0x0200);

    self->regs.reg_0x0203_hbi_ovr = REG_0X0203_HBI_OVR_BYPASS;

    self->regs.reg_0x0208_cmix_byp = 1;
    self->regs.reg_0x0208_isinc_byp = 1;
    self->regs.reg_0x0208_gfir3_byp = 1;
    self->regs.reg_0x0208_gfir2_byp = 1;
    self->regs.reg_0x0208_gfir1_byp = 1;
    self->regs.reg_0x0208_dc_byp = 1;
    self->regs.reg_0x0208_gc_byp = 1;
    self->regs.reg_0x0208_ph_byp = 1;

    LMS7002M_regs_spi_write(self, 0x0200);
    LMS7002M_regs_spi_write(self, 0x0203);
    LMS7002M_regs_spi_write(self, 0x0208);
}

LMS7002M_API void LMS7002M_txtsp_set_interp(LMS7002M_t *self, const LMS7002M_chan_t channel, const size_t interp)
{
    LMS7002M_set_mac_ch(self, channel);

    if (interp == 1) self->regs.reg_0x0203_hbi_ovr = REG_0X0203_HBI_OVR_BYPASS;
    if (interp == 2) self->regs.reg_0x0203_hbi_ovr = 0;
    if (interp == 4) self->regs.reg_0x0203_hbi_ovr = 1;
    if (interp == 8) self->regs.reg_0x0203_hbi_ovr = 2;
    if (interp == 16) self->regs.reg_0x0203_hbi_ovr = 3;
    if (interp == 32) self->regs.reg_0x0203_hbi_ovr = 4;

    LMS7002M_regs_spi_write(self, 0x0203);
}

LMS7002M_API void LMS7002M_txtsp_set_freq(LMS7002M_t *self, const LMS7002M_chan_t channel, const double freqRel)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs.reg_0x0208_cmix_byp = 0;
    LMS7002M_regs_spi_write(self, 0x0208);
    LMS7002M_set_nco_freq(self, LMS_TX, channel, freqRel);
}

#ifdef __cplusplus
}
#endif
