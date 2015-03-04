///
/// \file LMS7002M/LMS7002M_trf.h
///
/// TX RF frontend controls for the LMS7002M C driver.
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

LMS7002M_API void LMS7002M_trf_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs.reg_0x0124_en_dir_trf = 1;
    LMS7002M_regs_spi_write(self, 0x0124);

    self->regs.reg_0x0100_en_g_trf = enable?1:0;
    self->regs.reg_0x0100_pd_tlobuf_trf = 0;
    self->regs.reg_0x0100_pd_txpad_trf = 0;
    LMS7002M_regs_spi_write(self, 0x0100);
}

LMS7002M_API void LMS7002M_trf_select_band(LMS7002M_t *self, const LMS7002M_chan_t channel, const int band)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs.reg_0x0103_sel_band1_trf = (band == 1)?1:0;
    self->regs.reg_0x0103_sel_band2_trf = (band == 2)?1:0;
    LMS7002M_regs_spi_write(self, 0x0103);
}

LMS7002M_API void LMS7002M_trf_enable_loopback(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs.reg_0x0101_en_loopb_txpad_trf = enable?0:1;
    LMS7002M_regs_spi_write(self, 0x0101);
}

#ifdef __cplusplus
}
#endif
