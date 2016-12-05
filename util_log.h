#ifndef UTIL_LOG_H
#define UTIL_LOG_H

/**
 * @file util_log.h
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2012 NASA Ames Research Center
 * @note ROM: SporeSat Bus
 * @note Processor: PIC32MX795F512L
 * @note Compiler: MPLAB XC32 V1.11
 * $Id: util_log.h 5246 2015-04-20 21:11:39Z asweet $
 */

// Application header files
// Internal library header files
// Third-party library header files
// Standard library header files
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Public macro definitions
// *****************************************************************************

/**
 * Logs a message at the specified level.
 * @param level the level at which to log
 * @param format the message to log
 */
#define log(level, format) \
    { util_log(level, __FILE__, __LINE__, format, ""); }

/**
 * Formats a message and logs it at the specified level.
 * @param level the level at which to log
 * @param format a C format sring (i.e. printf format string)
 */
#define logf(level, format, ...) \
    { util_log(level, __FILE__, __LINE__, format, __VA_ARGS__); }

/**
 * Logs a 'complete' message.
 * @param msg the msg to log
 * @param arg an argument to append to the end of the message
 */
#define trace(msg, arg) \
    { logf(TRACE, "%s , %d", msg, arg); }

// *****************************************************************************
// Public data type definitions (enum, struct, typedef, union)
// *****************************************************************************

/**
 * The type of log level for which to log.
 */
typedef enum
{
    ERROR = 0,
    INFO,
    TRACE,
    LOG_LEVEL_COUNT
} util_log_level_t;

/**
 * A function for logging.
 */
typedef void (*util_log_function_t)(const char *);

/**
 * A function for getting the time.
 */
typedef void (*get_time_function_t)(char * const, const uint8_t);

// *****************************************************************************
// Public constant definitions
// *****************************************************************************

// *****************************************************************************
// Public function prototypes
// *****************************************************************************

/**
 * Initializes util_log.
 * @param level the default log level
 * @param host_name the name of this executable (e.g. bus or payload)
 * @param error_log_function the function to call for logging errors
 * @param trace_log_function the function to call for general-purpose logging
 * @param get_time_function the function to call to get the time
 */
void util_log_init (util_log_level_t const level, const char * const host_name,
                    util_log_function_t const error_log_function,
                    util_log_function_t const info_log_function,
                    util_log_function_t const trace_log_function,
                    get_time_function_t const get_time_function);

/**
 * Logs a message.
 * @param level the level at which to log the message
 * @param file the source file that logged the message
 * @param line the source line that logged the message
 * @param format the message to log
 */
void util_log (util_log_level_t const level,
               const char * const file,
               uint32_t const line,
               const char * const format, ...);

/**
 * Returns the number of errors that have been logged since the last time this
 * function was called.
 * @return the count
 */
size_t util_log_poll_error_count (void);

// *****************************************************************************
// Public inline function definitions
// *****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // UTIL_LOG_H
