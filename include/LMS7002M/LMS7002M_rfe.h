///
/// \file LMS7002M/LMS7002M_rfe.h
///
/// RX RF frontend controls for the LMS7002M C driver.
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

LMS7002M_API void LMS7002M_rfe_set_lna(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain)
{
    LMS7002M_set_mac_ch(self, channel);
    const double val = gain - 30;
    if (val >= 0) self->regs.reg_0x0113_g_lna_rfe = 15;
    else if (val >= -1) self->regs.reg_0x0113_g_lna_rfe = 14;
    else if (val >= -2) self->regs.reg_0x0113_g_lna_rfe = 13;
    else if (val >= -3) self->regs.reg_0x0113_g_lna_rfe = 12;
    else if (val >= -4) self->regs.reg_0x0113_g_lna_rfe = 11;
    else if (val >= -5) self->regs.reg_0x0113_g_lna_rfe = 10;
    else if (val >= -6) self->regs.reg_0x0113_g_lna_rfe = 9;
    else if (val >= -9) self->regs.reg_0x0113_g_lna_rfe = 8;
    else if (val >= -12) self->regs.reg_0x0113_g_lna_rfe = 7;
    else if (val >= -15) self->regs.reg_0x0113_g_lna_rfe = 6;
    else if (val >= -18) self->regs.reg_0x0113_g_lna_rfe = 5;
    else if (val >= -21) self->regs.reg_0x0113_g_lna_rfe = 4;
    else if (val >= -24) self->regs.reg_0x0113_g_lna_rfe = 3;
    else if (val >= -27) self->regs.reg_0x0113_g_lna_rfe = 2;
    else self->regs.reg_0x0113_g_lna_rfe = 1;

    LMS7002M_regs_spi_write(self, 0x0113);
}

LMS7002M_API void LMS7002M_rfe_set_loopback_lna(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain)
{
    LMS7002M_set_mac_ch(self, channel);
    const double val = gain - 40;
    if (val >= 0) self->regs.reg_0x0113_g_rxloopb_rfe = 15;
    else if (val >= -0.5) self->regs.reg_0x0113_g_rxloopb_rfe = 14;
    else if (val >= -1) self->regs.reg_0x0113_g_rxloopb_rfe = 13;
    else if (val >= -1.6) self->regs.reg_0x0113_g_rxloopb_rfe = 12;
    else if (val >= -2.4) self->regs.reg_0x0113_g_rxloopb_rfe = 11;
    else if (val >= -3) self->regs.reg_0x0113_g_rxloopb_rfe = 10;
    else if (val >= -4) self->regs.reg_0x0113_g_rxloopb_rfe = 9;
    else if (val >= -5) self->regs.reg_0x0113_g_rxloopb_rfe = 8;
    else if (val >= -6.2) self->regs.reg_0x0113_g_rxloopb_rfe = 7;
    else if (val >= -7.5) self->regs.reg_0x0113_g_rxloopb_rfe = 6;
    else if (val >= -9) self->regs.reg_0x0113_g_rxloopb_rfe = 5;
    else if (val >= -11) self->regs.reg_0x0113_g_rxloopb_rfe = 4;
    else if (val >= -14) self->regs.reg_0x0113_g_rxloopb_rfe = 3;
    else if (val >= -17) self->regs.reg_0x0113_g_rxloopb_rfe = 2;
    else if (val >= -24) self->regs.reg_0x0113_g_rxloopb_rfe = 1;
    else self->regs.reg_0x0113_g_rxloopb_rfe = 0;

    LMS7002M_regs_spi_write(self, 0x0113);
}

#ifdef __cplusplus
}
#endif
