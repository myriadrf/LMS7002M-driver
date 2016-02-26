///
/// \file LMS7002M_filter_cal.h
///
/// Common filter calibration functions for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2016-2016 Fairwaves, Inc.
/// Copyright (c) 2016-2016 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#include <LMS7002M/LMS7002M.h>

//! Prevent calibration loops from getting stuck
#define MAX_CAL_LOOP_ITERS 512

//! Read the RSSI from RxTSP with small sleep for settling
uint16_t cal_read_rssi(LMS7002M_t *self, const LMS7002M_chan_t channel);

//! Helper to set a range of addresses to default
void set_addrs_to_default(LMS7002M_t *self, const LMS7002M_chan_t channel, const int start_addr, const int stop_addr);

//! Helper to perform the calibration baseband gain selection
int cal_gain_selection(LMS7002M_t *self, const LMS7002M_chan_t channel);

//! Helper to setup clocking for calibration
int cal_setup_cgen(LMS7002M_t *self, const double bw);
