///
/// \file LMS7002M_rbb.c
///
/// RX baseband controls for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_impl.h"
#include "LMS7002M_ported.h"
#include <math.h> //pow
#include <LMS7002M/LMS7002M_logger.h>

void LMS7002M_rbb_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs->reg_0x0124_en_dir_rbb = 1;
    LMS7002M_regs_spi_write(self, 0x0124);

    self->regs->reg_0x0115_en_g_rbb = enable?1:0;
    self->regs->reg_0x0115_pd_pga_rbb = 0;

    LMS7002M_regs_spi_write(self, 0x0115);
}

void LMS7002M_rbb_set_path(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs->reg_0x0115_pd_lpfh_rbb = 1;
    self->regs->reg_0x0115_pd_lpfl_rbb = 1;
    self->regs->reg_0x0115_en_lb_lpfh_rbb = 0;
    self->regs->reg_0x0115_en_lb_lpfl_rbb = 0;

    switch (path)
    {
    case LMS7002M_RBB_BYP:
        self->regs->reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_BYPASS;
        break;

    case LMS7002M_RBB_LBF:
        self->regs->reg_0x0115_pd_lpfl_rbb = 0;
        self->regs->reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_LPFL;
        break;

    case LMS7002M_RBB_HBF:
        self->regs->reg_0x0115_pd_lpfh_rbb = 0;
        self->regs->reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_LPFH;
        break;

    case LMS7002M_RBB_LB_BYP:
        self->regs->reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_TBB;
        break;

    case LMS7002M_RBB_LB_LBF:
        self->regs->reg_0x0115_pd_lpfl_rbb = 0;
        self->regs->reg_0x0115_en_lb_lpfl_rbb = 1;
        self->regs->reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_LPFL;
        break;

    case LMS7002M_RBB_LB_HBF:
        self->regs->reg_0x0115_pd_lpfh_rbb = 0;
        self->regs->reg_0x0115_en_lb_lpfh_rbb = 1;
        self->regs->reg_0x0118_input_ctl_pga_rbb = REG_0X0118_INPUT_CTL_PGA_RBB_LPFH;
        break;
    }

    LMS7002M_regs_spi_write(self, 0x0115);
    LMS7002M_regs_spi_write(self, 0x0118);
}

void LMS7002M_rbb_set_test_out(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs->reg_0x0119_osw_pga_rbb = enable?1:0;

    LMS7002M_regs_spi_write(self, 0x0119);
}

double LMS7002M_rbb_set_pga(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain)
{
    LMS7002M_set_mac_ch(self, channel);

    int G_PGA_RBB = (int)(gain + 12.5);
    if (G_PGA_RBB > 0x1f) G_PGA_RBB = 0x1f;
    if (G_PGA_RBB < 0) G_PGA_RBB = 0;
    self->regs->reg_0x0119_g_pga_rbb = G_PGA_RBB;

    self->regs->reg_0x011a_rcc_ctl_pga_rbb = (430.0*pow(0.65, (G_PGA_RBB/10.0))-110.35)/20.4516 + 16;

    if (0 <= G_PGA_RBB && G_PGA_RBB < 8) self->regs->reg_0x011a_c_ctl_pga_rbb = 3;
    if (8 <= G_PGA_RBB && G_PGA_RBB < 13) self->regs->reg_0x011a_c_ctl_pga_rbb = 2;
    if (13 <= G_PGA_RBB && G_PGA_RBB < 21) self->regs->reg_0x011a_c_ctl_pga_rbb = 1;
    if (21 <= G_PGA_RBB) self->regs->reg_0x011a_c_ctl_pga_rbb = 0;

    LMS7002M_regs_spi_write(self, 0x0119);
    LMS7002M_regs_spi_write(self, 0x011A);

    return G_PGA_RBB - 12.0;
}

double LMS7002M_rbb_set_filter_bw(LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw)
{
    LMS7002M_set_mac_ch(self, channel);

    int val = 0;
    double actual = bw;
    bool bypass = false;
    const bool hb = bw >= 37.0e6;

    if (bw <= 1.4e6) val = 0, actual = 1.4e6;
    else if (bw <= 3.0e6) val = 1, actual = 3.0e6;
    else if (bw <= 5.0e6) val = 2, actual = 5.0e6;
    else if (bw <= 10.0e6) val = 3, actual = 10.0e6;
    else if (bw <= 15.0e6) val = 4, actual = 15.0e6;
    else if (bw <= 20.0e6) val = 5, actual = 20.0e6;
    else if (bw <= 37.0e6) val = 1, actual = 37.0e6;
    else if (bw <= 66.0e6) val = 4, actual = 66.0e6;
    else if (bw <= 108.0e6) val = 7, actual = 108.0e6;
    else bypass = true;

    //only one filter is actually used
    self->regs->reg_0x0117_rcc_ctl_lpfl_rbb = val;
    self->regs->reg_0x0116_rcc_ctl_lpfh_rbb = val;
    LMS7002M_regs_spi_write(self, 0x0116);
    LMS7002M_regs_spi_write(self, 0x0117);

    //set path
    if (bypass) LMS7002M_rbb_set_path(self, channel, LMS7002M_RBB_BYP);
    else if (hb) LMS7002M_rbb_set_path(self, channel, LMS7002M_RBB_HBF);
    else LMS7002M_rbb_set_path(self, channel, LMS7002M_RBB_LBF);

    //run the calibration for this bandwidth setting
    LMS7_logf(LMS7_DEBUG, "CalibrateRx(%f MHz)", bw/1e6);
    liblms7_status status = CalibrateRx(self, bw/1e6);
    if (!bypass && status == LIBLMS7_SUCCESS)
    {
        LMS7_log(LMS7_DEBUG, "TuneRxFilter");
        status = TuneRxFilter(self, hb?RX_LPF_HIGHBAND:RX_LPF_LOWBAND, bw/1e6);
    }
    if (status == LIBLMS7_SUCCESS)
    {
        LMS7_log(LMS7_DEBUG, "TuneRxFilter(RX_TIA)");
        status = TuneRxFilter(self, RX_TIA, bw/1e6);
    }
    if (status != LIBLMS7_SUCCESS)
    {
        LMS7_logf(LMS7_ERROR, "CalibrateRx(%f MHz) Fail - %s", bw/1e6, liblms7_status_strings[status]);
    }
    else
    {
        //if (self->sxr_freq != 0.0) LMS7002M_set_lo_freq(self, LMS_RX, self->sxr_fref, self->sxr_freq, NULL);
    }

    return actual;
}
