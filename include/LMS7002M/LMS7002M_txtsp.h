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

#ifdef __cplusplus
}
#endif
