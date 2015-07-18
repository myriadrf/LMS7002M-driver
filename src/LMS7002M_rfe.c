///
/// \file LMS7002M_rfe.c
///
/// RX RF frontend controls for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_impl.h"

void LMS7002M_rfe_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs->reg_0x0124_en_dir_rfe = 1;
    LMS7002M_regs_spi_write(self, 0x0124);

    self->regs->reg_0x010c_en_g_rfe = enable?1:0;
    self->regs->reg_0x010c_pd_mxlobuf_rfe = 0;
    self->regs->reg_0x010c_pd_qgen_rfe = 0;
    self->regs->reg_0x010c_pd_tia_rfe = 0;
    self->regs->reg_0x010c_pd_lna_rfe = 1;
    self->regs->reg_0x010c_pd_rloopb_1_rfe = 1;
    self->regs->reg_0x010c_pd_rloopb_2_rfe = 1;
    LMS7002M_regs_spi_write(self, 0x010C);
}

void LMS7002M_rfe_set_path(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs->reg_0x010c_pd_lna_rfe = 1;
    self->regs->reg_0x010c_pd_rloopb_1_rfe = 1;
    self->regs->reg_0x010c_pd_rloopb_2_rfe = 1;
    self->regs->reg_0x010d_en_inshsw_l_rfe = 1;
    self->regs->reg_0x010d_en_inshsw_w_rfe = 1;
    self->regs->reg_0x010d_en_inshsw_lb1_rfe = 1;
    self->regs->reg_0x010d_en_inshsw_lb2_rfe = 1;
    self->regs->reg_0x010d_sel_path_rfe = REG_0X010D_SEL_PATH_RFE_NONE;
    bool enb_trf_loopback = false;

    switch (path)
    {
    case LMS7002M_RFE_LB1:
        self->regs->reg_0x010d_sel_path_rfe = REG_0X010D_SEL_PATH_RFE_LNAW;
        self->regs->reg_0x010c_pd_rloopb_1_rfe = 0;
        self->regs->reg_0x010d_en_inshsw_lb1_rfe = 0;
        enb_trf_loopback = true;
        break;

    case LMS7002M_RFE_LB2:
        self->regs->reg_0x010d_sel_path_rfe = REG_0X010D_SEL_PATH_RFE_LNAL;
        self->regs->reg_0x010c_pd_rloopb_2_rfe = 0;
        self->regs->reg_0x010d_en_inshsw_lb2_rfe = 0;
        enb_trf_loopback = true;
        break;

    case LMS7002M_RFE_NONE:
        break;

    case LMS7002M_RFE_LNAH:
        self->regs->reg_0x010d_sel_path_rfe = REG_0X010D_SEL_PATH_RFE_LNAH;
        self->regs->reg_0x010c_pd_lna_rfe = 0;
        break;

    case LMS7002M_RFE_LNAL:
        self->regs->reg_0x010d_sel_path_rfe = REG_0X010D_SEL_PATH_RFE_LNAL;
        self->regs->reg_0x010c_pd_lna_rfe = 0;
        self->regs->reg_0x010d_en_inshsw_l_rfe = 0;
        break;

    case LMS7002M_RFE_LNAW:
        self->regs->reg_0x010d_sel_path_rfe = REG_0X010D_SEL_PATH_RFE_LNAW;
        self->regs->reg_0x010c_pd_lna_rfe = 0;
        self->regs->reg_0x010d_en_inshsw_w_rfe = 0;
        break;
    }

    LMS7002M_regs_spi_write(self, 0x010C);
    LMS7002M_regs_spi_write(self, 0x010D);
    LMS7002M_trf_enable_loopback(self, channel, enb_trf_loopback);
}

double LMS7002M_rfe_set_lna(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain)
{
    const double gmax = 30;
    double val = gain - gmax;

    LMS7002M_set_mac_ch(self, channel);

    if (val >= 0) self->regs->reg_0x0113_g_lna_rfe = 15, val = 0;
    else if (val >= -1) self->regs->reg_0x0113_g_lna_rfe = 14, val = -1;
    else if (val >= -2) self->regs->reg_0x0113_g_lna_rfe = 13, val = -2;
    else if (val >= -3) self->regs->reg_0x0113_g_lna_rfe = 12, val = -3;
    else if (val >= -4) self->regs->reg_0x0113_g_lna_rfe = 11, val = -4;
    else if (val >= -5) self->regs->reg_0x0113_g_lna_rfe = 10, val = -5;
    else if (val >= -6) self->regs->reg_0x0113_g_lna_rfe = 9, val = -6;
    else if (val >= -9) self->regs->reg_0x0113_g_lna_rfe = 8, val = -9;
    else if (val >= -12) self->regs->reg_0x0113_g_lna_rfe = 7, val = -12;
    else if (val >= -15) self->regs->reg_0x0113_g_lna_rfe = 6, val = -15;
    else if (val >= -18) self->regs->reg_0x0113_g_lna_rfe = 5, val = -18;
    else if (val >= -21) self->regs->reg_0x0113_g_lna_rfe = 4, val = -21;
    else if (val >= -24) self->regs->reg_0x0113_g_lna_rfe = 3, val = -24;
    else if (val >= -27) self->regs->reg_0x0113_g_lna_rfe = 2, val = -27;
    else self->regs->reg_0x0113_g_lna_rfe = 1, val = -30;

    LMS7002M_regs_spi_write(self, 0x0113);

    return val + gmax;
}

double LMS7002M_rfe_set_loopback_lna(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain)
{
    const double gmax = 40;
    double val = gain - gmax;

    LMS7002M_set_mac_ch(self, channel);

    if (val >= 0) self->regs->reg_0x0113_g_rxloopb_rfe = 15, val = 0;
    else if (val >= -0.5) self->regs->reg_0x0113_g_rxloopb_rfe = 14, val = -0.5;
    else if (val >= -1) self->regs->reg_0x0113_g_rxloopb_rfe = 13, val = -1;
    else if (val >= -1.6) self->regs->reg_0x0113_g_rxloopb_rfe = 12, val = -1.6;
    else if (val >= -2.4) self->regs->reg_0x0113_g_rxloopb_rfe = 11, val = -2.4;
    else if (val >= -3) self->regs->reg_0x0113_g_rxloopb_rfe = 10, val = -3;
    else if (val >= -4) self->regs->reg_0x0113_g_rxloopb_rfe = 9, val = -4;
    else if (val >= -5) self->regs->reg_0x0113_g_rxloopb_rfe = 8, val = -5;
    else if (val >= -6.2) self->regs->reg_0x0113_g_rxloopb_rfe = 7, val = -6.2;
    else if (val >= -7.5) self->regs->reg_0x0113_g_rxloopb_rfe = 6, val = -7.5;
    else if (val >= -9) self->regs->reg_0x0113_g_rxloopb_rfe = 5, val = -9;
    else if (val >= -11) self->regs->reg_0x0113_g_rxloopb_rfe = 4, val = -11;
    else if (val >= -14) self->regs->reg_0x0113_g_rxloopb_rfe = 3, val = -14;
    else if (val >= -17) self->regs->reg_0x0113_g_rxloopb_rfe = 2, val = -17;
    else if (val >= -24) self->regs->reg_0x0113_g_rxloopb_rfe = 1, val = -24;
    else self->regs->reg_0x0113_g_rxloopb_rfe = 0, val = -40;

    LMS7002M_regs_spi_write(self, 0x0113);

    return val + gmax;
}

double LMS7002M_rfe_set_tia(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain)
{
    const double gmax = 12;
    double val = gain - gmax;

    LMS7002M_set_mac_ch(self, channel);

    if (val >= 0) self->regs->reg_0x0113_g_tia_rfe = 3, val = 0;
    else if (val >= -3) self->regs->reg_0x0113_g_tia_rfe = 2, val = -3;
    else self->regs->reg_0x0113_g_tia_rfe = 1, val = -12;

    LMS7002M_regs_spi_write(self, 0x0113);

    return val + gmax;
}
