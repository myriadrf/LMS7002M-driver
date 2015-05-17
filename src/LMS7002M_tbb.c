///
/// \file LMS7002M_tbb.c
///
/// TX baseband controls for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_impl.h"

void LMS7002M_tbb_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs.reg_0x0124_en_dir_tbb = 1;
    LMS7002M_regs_spi_write(self, 0x0124);

    self->regs.reg_0x0105_en_g_tbb = enable?1:0;
    LMS7002M_tbb_set_test_in(self, channel, LMS7002M_TBB_TSTIN_OFF);
    LMS7002M_tbb_enable_loopback(self, channel, LMS7002M_TBB_LB_DISCONNECTED, false);

    LMS7002M_regs_spi_write(self, 0x0105);
}

void LMS7002M_tbb_set_path(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs.reg_0x0105_pd_lpfh_tbb = 1;
    self->regs.reg_0x0105_pd_lpflad_tbb = 1;
    self->regs.reg_0x0105_pd_lpfs5_tbb = 1;
    self->regs.reg_0x010a_bypladder_tbb = 1;

    switch (path)
    {
    case LMS7002M_TBB_BYP:
        break;

    case LMS7002M_TBB_LBF:
        self->regs.reg_0x010a_bypladder_tbb = 0;
        self->regs.reg_0x0105_pd_lpflad_tbb = 0;
        self->regs.reg_0x0105_pd_lpfs5_tbb = 0;
        break;

    case LMS7002M_TBB_HBF:
        self->regs.reg_0x0105_pd_lpfh_tbb = 0;
        break;
    }

    LMS7002M_regs_spi_write(self, 0x0105);
    LMS7002M_regs_spi_write(self, 0x010A);
}

void LMS7002M_tbb_set_test_in(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs.reg_0x010a_tstin_tbb = path;
    LMS7002M_regs_spi_write(self, 0x010a);
}

void LMS7002M_tbb_enable_loopback(LMS7002M_t *self, const LMS7002M_chan_t channel, const int mode, const bool swap)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs.reg_0x0105_loopb_tbb = mode;
    self->regs.reg_0x0105_loopb_tbb |= swap?0:(1 << 2);

    LMS7002M_regs_spi_write(self, 0x0105);
}

double LMS7002M_tbb_set_filter_bw(LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw)
{
    LMS7002M_set_mac_ch(self, channel);

    int val = 0;
    double actual = bw;
    bool bypass = false;
    const bool hb = bw >= 18.5e6;

    if (bw <= 2.4e6) val = 6, actual = 2.4e6;
    else if (bw <= 2.74e6) val = 19, actual = 2.74e6;
    else if (bw <= 5.5e6) val = 75, actual = 5.5e6;
    else if (bw <= 8.2e6) val = 133, actual = 8.2e6;
    else if (bw <= 11.0e6) val = 193, actual = 11.0e6;
    else if (bw <= 18.5e6) val = 18, actual = 18.5e6;
    else if (bw <= 38.0e6) val = 97, actual = 38.0e6;
    else if (bw <= 54.0e6) val = 163, actual = 54.0e6;
    else bypass = true;

    //only one filter is actually used
    self->regs.reg_0x0109_rcal_lpfh_tbb = val;
    self->regs.reg_0x0109_rcal_lpflad_tbb = val;
    LMS7002M_regs_spi_write(self, 0x0109);

    //set path
    if (bypass) LMS7002M_tbb_set_path(self, channel, LMS7002M_TBB_BYP);
    else if (hb) LMS7002M_tbb_set_path(self, channel, LMS7002M_TBB_HBF);
    else LMS7002M_tbb_set_path(self, channel, LMS7002M_TBB_LBF);

    return actual;
}

double LMS7002M_tbb_set_iamp(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain)
{
    LMS7002M_set_mac_ch(self, channel);
    int value = (int)(gain + 0.5);
    if (value < 0) value = 0;
    if (value > 63) value = 63;

    //ensure enabled iamp
    self->regs.reg_0x0105_pd_lpfiamp_tbb = 0;
    LMS7002M_regs_spi_write(self, 0x0105);

    //TODO this may need calibration

    self->regs.reg_0x0108_cg_iamp_tbb = value;

    return gain;
}
