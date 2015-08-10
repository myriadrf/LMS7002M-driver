///
/// \file LMS7002M/LMS7002M_time.h
///
/// Time and sleep functions for the LMS7002M C driver.
/// The time calls are intended to be hardware independent.
/// Hardware specific code is in the implementation details.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once
#include <LMS7002M/LMS7002M_config.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Get the number of ticks per second.
 * Use this to convert to and from seconds.
 * \return how many ticks elapse per second
 */
LMS7002M_API long long LMS7_time_tps(void);

/*!
 * Query the current time in tick counts.
 * \return an absolute time in tick counts
 */
LMS7002M_API long long LMS7_time_now(void);

/*!
 * Sleep the caller for the specified number of ticks.
 * \param ticks a time duration in tick counts
 */
LMS7002M_API void LMS7_sleep_for(const long long ticks);

/*!
 * Sleep the caller until the specified time expires..
 * \param ticks an absolute time in tick counts
 */
LMS7002M_API void LMS7_sleep_until(const long long ticks);

#ifdef __cplusplus
}
#endif
