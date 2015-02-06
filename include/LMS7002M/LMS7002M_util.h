///
/// \file LMS7002M/LMS7002M_util.h
///
/// Misc utility helper functions.
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

#if defined(_WIN32)
  #include <windows.h>
#elif defined(__unix__)
  #include <unistd.h>
#else
#endif

#ifdef __cplusplus
extern "C" {
#endif

static inline int LMS7002M_millisleep(unsigned ms)
{
#if defined(_WIN32)
  SetLastError(0);
  Sleep(ms);
  return GetLastError() ?-1 :0;
#elif defined(__unix__)
  return usleep(1000 * ms);
#else
#error ("no milli sleep available for platform")
  return -1;
#endif
}

#ifdef __cplusplus
}
#endif
