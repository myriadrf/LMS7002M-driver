///
/// \file LMS7002M_time.c
///
/// Time and sleep functions for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

//TODO ifdef this for time on other platforms

#include <LMS7002M/LMS7002M_time.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>

long long LMS7_time_tps(void)
{
    return 1000000;
}

long long LMS7_time_now(void)
{
    struct timeval now_tv;
    gettimeofday(&now_tv, NULL);
    return (LMS7_time_tps()*now_tv.tv_sec) + now_tv.tv_usec;
}

void LMS7_sleep_for(const long long ticks)
{
    LMS7_sleep_until(LMS7_time_now() + ticks);
}

void LMS7_sleep_until(const long long ticks)
{
    //we must loop in case of spurious wake-ups
    while (true)
    {
        const long long left = ticks - LMS7_time_now();
        if (left < 0) break; //time expired -> done here

        //otherwise sleep for the time left
        struct timeval tv;
        tv.tv_sec = left/LMS7_time_tps();
        tv.tv_usec = left%LMS7_time_tps();
        select(1, NULL, NULL, NULL, &tv);
    }
}
