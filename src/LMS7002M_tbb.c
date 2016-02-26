///
/// \file LMS7002M_tbb.c
///
/// TX baseband controls for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2016 Fairwaves, Inc.
/// Copyright (c) 2015-2016 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_impl.h"
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
