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

LMS7002M_API void LMS7002M_tbb_enable_loopback(LMS7002M_t *self, const LMS7002M_chan_t channel, const int mode, const bool swap)
{
    LMS7002M_set_mac_ch(self, channel);

    self->regs.reg_0x0105_loopb_tbb = mode;
    self->regs.reg_0x0105_loopb_tbb |= swap?0:(1 << 2);

    LMS7002M_regs_spi_write(self, 0x0105);
}

#ifdef __cplusplus
}
#endif
