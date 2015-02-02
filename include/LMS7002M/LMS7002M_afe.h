///
/// \file LMS7002M/LMS7002M_afe.h
///
/// ADC and DAC config for the LMS7002M C driver.
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

LMS7002M_API void LMS7002M_afe_enable(LMS7002M_t *self, const LMS7002M_dir_t direction, const LMS7002M_chan_t channel, const bool enable)
{
    //always individual enables and both ADCs
    self->regs.reg_0x0082_en_g_afe = 1;
    self->regs.reg_0x0082_mode_interleave_afe = REG_0X0082_MODE_INTERLEAVE_AFE_2ADCS;
    self->regs.reg_0x0082_pd_afe = 0;

    //conditional power downs
    if (direction == LMS_TX and channel == LMS_CHA) self->regs.reg_0x0082_pd_tx_afe1 = enable?0:1;
    if (direction == LMS_TX and channel == LMS_CHB) self->regs.reg_0x0082_pd_tx_afe2 = enable?0:1;
    if (direction == LMS_RX and channel == LMS_CHA) self->regs.reg_0x0082_pd_rx_afe1 = enable?0:1;
    if (direction == LMS_RX and channel == LMS_CHB) self->regs.reg_0x0082_pd_rx_afe2 = enable?0:1;

    LMS7002M_regs_spi_write(self, 0x0082);
}

#ifdef __cplusplus
}
#endif
