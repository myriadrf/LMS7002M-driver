///
/// \file LMS7002M_gfir.c
///
/// FIR filter config for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <stdlib.h>
#include "LMS7002M_impl.h"

int LMS7002M_set_gfir_taps(
    LMS7002M_t *self,
    const LMS7002M_dir_t direction,
    const LMS7002M_chan_t channel,
    const int which,
    const short *taps,
    const size_t ntaps)
{
    LMS7002M_set_mac_ch(self, channel);

    //bypass the filter for null/empty filter taps
    const bool bypass = (taps == NULL) || (ntaps == 0);

    

    return 0; //OK
}
