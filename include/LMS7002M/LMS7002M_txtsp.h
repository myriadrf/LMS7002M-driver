///
/// \file LMS7002M/LMS7002M_txtsp.h
///
/// TX DSP chain config for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2014-2015 Fairwaves, Inc.
/// Copyright (c) 2014-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once
#include <stdlib.h>
#include <LMS7002M/LMS7002M.h>

#ifdef __cplusplus
extern "C" {
#endif

LMS7002M_API void LMS7002M_txtsp_init(LMS7002M_t *self, const LMS7002M_chan_t channel)
{
    LMS7002M_set_mac_ch(self, channel);
    //TODO
}

LMS7002M_API void LMS7002M_txtsp_set_interp(LMS7002M_t *self, const LMS7002M_chan_t channel, const size_t interp)
{
    LMS7002M_set_mac_ch(self, channel);
    //TODO
}

LMS7002M_API void LMS7002M_txtsp_set_freq(LMS7002M_t *self, const LMS7002M_chan_t channel, const double freqRel)
{
    LMS7002M_set_mac_ch(self, channel);
    self->regs.reg_0x0208_cmix_byp = 0;
    LMS7002M_regs_spi_write(self, 0x0208);
    LMS7002M_set_nco_freq(self, LMS_TX, channel, freqRel);
}

#ifdef __cplusplus
}
#endif
