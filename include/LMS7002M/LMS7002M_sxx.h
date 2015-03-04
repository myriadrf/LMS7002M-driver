///
/// \file LMS7002M/LMS7002M_sxx.h
///
/// LO tuning hooks for the LMS7002M C driver.
/// See SXR and SXT sections in the documentation.
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

LMS7002M_API int LMS7002M_set_lo_freq(LMS7002M_t *self, const LMS7002M_dir_t direction, const double fref, const double fout, double *factual)
{
    LMS7002M_set_mac_dir(self, direction);

    //TODO

    //after a successful tune, stash the frequency
    if (direction == LMS_RX) self->sxr_freq = fout;
    if (direction == LMS_TX) self->sxt_freq = fout;
    if (direction == LMS_RX) self->sxr_fref = fref;
    if (direction == LMS_TX) self->sxt_fref = fref;

    *factual = 0.0;
    return 0;
}

#ifdef __cplusplus
}
#endif
