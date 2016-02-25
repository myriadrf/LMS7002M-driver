///
/// \file LMS7002M_tx_filter_cal.c
///
/// Tx filter calibration functions for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2016-2016 Fairwaves, Inc.
/// Copyright (c) 2016-2016 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include "LMS7002M_impl.h"
#include "LMS7002M_filter_cal.h"
#include <LMS7002M/LMS7002M_logger.h>
#include <LMS7002M/LMS7002M_time.h>
#include <string.h> //memcpy

int LMS7002M_tbb_set_filter_bw(LMS7002M_t *self, const LMS7002M_chan_t channel, const double bw, double *bwactual)
{
    if (bwactual != NULL) *bwactual = bw;

    return 0;
}
