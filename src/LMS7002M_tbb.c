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
#include "LMS7002M_ported.h"
#include <LMS7002M/LMS7002M_logger.h>

void LMS7002M_tbb_enable(LMS7002M_t *self, const LMS7002M_chan_t channel, const bool enable)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs->reg_0x0124_en_dir_tbb = 1;
    LMS7002M_regs_spi_write(self, 0x0124);

    self->regs->reg_0x0105_en_g_tbb = enable?1:0;
    LMS7002M_tbb_set_test_in(self, channel, LMS7002M_TBB_TSTIN_OFF);
    LMS7002M_tbb_enable_loopback(self, channel, LMS7002M_TBB_LB_DISCONNECTED, false);

    LMS7002M_regs_spi_write(self, 0x0105);
}

void LMS7002M_tbb_set_path(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs->reg_0x0105_pd_lpfh_tbb = 1;
    self->regs->reg_0x0105_pd_lpflad_tbb = 1;
    self->regs->reg_0x0105_pd_lpfs5_tbb = 1;
    self->regs->reg_0x010a_bypladder_tbb = 1;

    switch (path)
    {
    case LMS7002M_TBB_BYP:
        break;

    case LMS7002M_TBB_S5:
        self->regs->reg_0x0105_pd_lpfs5_tbb = 0;
        break;

    case LMS7002M_TBB_LAD:
        self->regs->reg_0x010a_bypladder_tbb = 0;
        self->regs->reg_0x0105_pd_lpflad_tbb = 0;
        break;

    case LMS7002M_TBB_LBF:
        self->regs->reg_0x010a_bypladder_tbb = 0;
        self->regs->reg_0x0105_pd_lpflad_tbb = 0;
        self->regs->reg_0x0105_pd_lpfs5_tbb = 0;
        break;

    case LMS7002M_TBB_HBF:
        self->regs->reg_0x0105_pd_lpfh_tbb = 0;
        break;
    }

    LMS7002M_regs_spi_write(self, 0x0105);
    LMS7002M_regs_spi_write(self, 0x010A);
}

void LMS7002M_tbb_set_test_in(LMS7002M_t *self, const LMS7002M_chan_t channel, const int path)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs->reg_0x010a_tstin_tbb = path;
    LMS7002M_regs_spi_write(self, 0x010a);
}

void LMS7002M_tbb_enable_loopback(LMS7002M_t *self, const LMS7002M_chan_t channel, const int mode, const bool swap)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs->reg_0x0105_loopb_tbb = mode;
    self->regs->reg_0x0105_loopb_tbb |= swap?0:(1 << 2);

    LMS7002M_regs_spi_write(self, 0x0105);
}

int LMS7002M_tbb_set_filter_bw(LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw, double *bwactual)
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
    if (bwactual != NULL) *bwactual = actual;

    //only one filter is actually used
    self->regs->reg_0x0109_rcal_lpfh_tbb = val;
    self->regs->reg_0x0109_rcal_lpflad_tbb = val;
    LMS7002M_regs_spi_write(self, 0x0109);

    //set path
    if (bypass) LMS7002M_tbb_set_path(self, channel, LMS7002M_TBB_BYP);
    else if (hb) LMS7002M_tbb_set_path(self, channel, LMS7002M_TBB_HBF);
    else LMS7002M_tbb_set_path(self, channel, LMS7002M_TBB_LBF);

    //run the calibration for this bandwidth setting
    LMS7_logf(LMS7_DEBUG, "CalibrateTx(%f MHz)", bw/1e6);
    liblms7_status status = CalibrateTx(self, bw/1e6);
    if (!bypass && status == LIBLMS7_SUCCESS)
    {
        LMS7_log(LMS7_DEBUG, "TuneTxFilter");
        TxFilter filter;
        if (hb) filter = TX_HIGHBAND;
        else if (bw >= 2.4e6) filter = TX_LADDER;
        else filter = TX_REALPOLE;

        status = TuneTxFilter(self, filter, bw/1e6);
    }
    if (status != LIBLMS7_SUCCESS)
    {
        LMS7_logf(LMS7_ERROR, "CalibrateTx(%f MHz) Fail - %s", bw/1e6, liblms7_status_strings[status]);
    }
    else
    {
        //if (self->sxt_freq != 0.0) LMS7002M_set_lo_freq(self, LMS_TX, self->sxt_fref, self->sxt_freq, NULL);
    }

    return (int)status;
}
