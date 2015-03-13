///
/// \file LMS7002M/LMS7002M_tbb.h
///
/// TX baseband controls for the LMS7002M C driver.
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

LMS7002M_API void LMS7002M_tbb_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs.reg_0x0124_en_dir_tbb = 1;
    LMS7002M_regs_spi_write(self, 0x0124);

    self->regs.reg_0x0105_en_g_tbb = enable?1:0;
    self->regs.reg_0x0105_pd_lpfh_tbb = 1;
    self->regs.reg_0x0105_pd_lpfiamp_tbb = 0;
    self->regs.reg_0x0105_pd_lpflad_tbb = 1;
    self->regs.reg_0x0105_pd_lpfs5_tbb = 1;

    //bypass for now
    self->regs.reg_0x010a_bypladder_tbb = 1;

    LMS7002M_regs_spi_write(self, 0x0105);
    LMS7002M_regs_spi_write(self, 0x010A);
}

LMS7002M_API void LMS7002M_tbb_enable_loopback(LMS7002M_t *self, const LMS7002M_chan_t channel, const int mode, const bool swap)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs.reg_0x0105_loopb_tbb = mode;
    self->regs.reg_0x0105_loopb_tbb |= swap?0:(1 << 2);

    LMS7002M_regs_spi_write(self, 0x0105);
}

LMS7002M_API double LMS7002M_tbb_set_filter_bw(LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw)
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

    //TODO set path

    return actual;
}

LMS7002M_API double LMS7002M_tbb_set_iamp(LMS7002M_t *self, const LMS7002M_chan_t channel, const double gain)
{
    LMS7002M_set_mac_ch(self, channel);
    int value = (int)(gain + 0.5);
    if (value < 0) value = 0;
    if (value > 63) value = 63;

    //TODO this may need calibration

    self->regs.reg_0x0108_cg_iamp_tbb = value;

    return gain;
}

#ifdef __cplusplus
}
#endif
