///
/// \file LMS7002M_logger.c
///
/// Logging facilities for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

//TODO ifdef this for printing on other platforms, ex kprintf

#include <LMS7002M/LMS7002M_logger.h>
#include <stdio.h>
#include <stdlib.h>

/***********************************************************************
 * ANSI terminal colors for default logger
 **********************************************************************/
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BOLD    "\x1b[1m"

/***********************************************************************
 * Default log message handler implementation
 **********************************************************************/
void default_handler(const LMS7_log_level_t level, const char *message)
{
    switch (level)
    {
    case LMS7_FATAL:    fprintf(stderr, ANSI_COLOR_BOLD ANSI_COLOR_RED "[FATAL] %s" ANSI_COLOR_RESET "\n", message); break;
    case LMS7_CRITICAL: fprintf(stderr, ANSI_COLOR_BOLD ANSI_COLOR_RED "[CRITICAL] %s" ANSI_COLOR_RESET "\n", message); break;
    case LMS7_ERROR:    fprintf(stderr, ANSI_COLOR_BOLD ANSI_COLOR_RED "[ERROR] %s" ANSI_COLOR_RESET "\n", message); break;
    case LMS7_WARNING:  fprintf(stderr, ANSI_COLOR_BOLD ANSI_COLOR_YELLOW "[WARNING] %s" ANSI_COLOR_RESET "\n", message); break;
    case LMS7_NOTICE:   fprintf(stdout, ANSI_COLOR_GREEN "[NOTICE] %s" ANSI_COLOR_RESET "\n", message); break;
    case LMS7_INFO:     fprintf(stdout, "[INFO] %s\n", message); break;
    case LMS7_DEBUG:    fprintf(stdout, "[DEBUG] %s\n", message); break;
    case LMS7_TRACE:    fprintf(stdout, "[TRACE] %s\n", message); break;
    }
}

/***********************************************************************
 * logging api implementation
 **********************************************************************/
static LMS7_log_level_t _log_level = LMS7_NOTICE;
static LMS7_log_handler_t _log_handler = default_handler;

void LMS7_set_log_level(const LMS7_log_level_t level)
{
    _log_level = level;
}

LMS7002M_API void LMS7_log(const LMS7_log_level_t level, const char *message)
{
    if (level > _log_level) return;
    _log_handler(level, message);
}

void LMS7_vlogf(const LMS7_log_level_t level, const char *format, va_list args)
{
    if (level > _log_level) return;
    char *message;
    vasprintf(&message, format, args);
    LMS7_log(level, message);
    free(message);
}

void LMS7_set_log_handler(const LMS7_log_handler_t handler)
{
    _log_handler = handler;
}


