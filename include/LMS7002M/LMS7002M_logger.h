///
/// \file LMS7002M/LMS7002M_logger.h
///
/// Logging facility for the LMS7002M C driver.
///
/// \copyright
/// Copyright (c) 2015-2015 Fairwaves, Inc.
/// Copyright (c) 2015-2015 Rice University
/// SPDX-License-Identifier: Apache-2.0
/// http://www.apache.org/licenses/LICENSE-2.0
///

#pragma once

#include <LMS7002M/LMS7002M_config.h>
#include <stdarg.h>

typedef enum
{
    LMS7_FATAL    = 1, //!< A fatal error. The application will most likely terminate. This is the highest priority.
    LMS7_CRITICAL = 2, //!< A critical error. The application might not be able to continue running successfully.
    LMS7_ERROR    = 3, //!< An error. An operation did not complete successfully, but the application as a whole is not affected.
    LMS7_WARNING  = 4, //!< A warning. An operation completed with an unexpected result.
    LMS7_NOTICE   = 5, //!< A notice, which is an information with just a higher priority.
    LMS7_INFO     = 6, //!< An informational message, usually denoting the successful completion of an operation.
    LMS7_DEBUG    = 7, //!< A debugging message.
    LMS7_TRACE    = 8, //!< A tracing message. This is the lowest priority.
} LMS7_log_level_t;

/*!
 * Set module/process-wide logger level.
 * Anything above this level will be discarded.
 * \param level a possible logging level
 */
LMS7002M_API void LMS7_set_log_level(const LMS7_log_level_t level);

/*!
 * Send a message to the registered logger.
 * \param level a possible logging level
 * \param message a logger message string
 */
LMS7002M_API void LMS7_log(const LMS7_log_level_t level, const char *message);

/*!
 * Send a message to the registered logger.
 * \param level a possible logging level
 * \param format a printf style format string
 * \param args an argument list for the formatter
 */
LMS7002M_API void LMS7_vlogf(const LMS7_log_level_t level, const char *format, va_list args);

/*!
 * Send a message to the registered logger.
 * \param level a possible logging level
 * \param format a printf style format string
 */
static inline void LMS7_logf(const LMS7_log_level_t level, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    LMS7_vlogf(level, format, args);
    va_end(args);
}

/*!
 * Typedef for a user specified log handler function.
 */
typedef void (*LMS7_log_handler_t)(const LMS7_log_level_t logLevel, const char *message);

/*!
 * Register a new system log handler.
 * Platforms should call this to replace the default handler.
 */
LMS7002M_API void LMS7_set_log_handler(const LMS7_log_handler_t handler);
