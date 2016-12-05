/**
 * @file util_log.c
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2012 NASA Ames Research Center
 * @note ROM: SporeSat Bus
 * @note Processor: PIC32MX795F512L
 * @note Compiler: MPLAB XC32 V1.11
 * $Id: util_log.c 5246 2015-04-20 21:11:39Z asweet $
 */

#include "util_log.h"
// Application header files
// Internal library header files
// Third-party library header files
// Standard library header files
#include <stdio.h>
#include <string.h>

// *****************************************************************************
// Private macro definitions
// *****************************************************************************

// *****************************************************************************
// Private data type definitions (enum, struct, typedef, union)
// *****************************************************************************

// *****************************************************************************
// Private static constant definitions
// *****************************************************************************

static const char * const LEVEL_STRINGS[LOG_LEVEL_COUNT] = {
    "ERROR",
    "INFO",
    "TRACE"
};

// *****************************************************************************
// Private static data definitions
// *****************************************************************************

/**
 * All state data
 * @private
 */
static struct
{
    /** The highest level of message that will be logged. */
    util_log_level_t level;

    /** The name of this ROM. */
    const char * host_name;

    /** The function that will be called when an error is logged. */
    util_log_function_t error_log_function;

    /** The function that will be called when a trace statement is logged. */
    util_log_function_t trace_log_function;

    /** The function that will be called when a info statement is logged. */
    util_log_function_t info_log_function;

    /** The function that will be called to get the time. */
    get_time_function_t get_time_function;



    /** The number of errors that have been logged. */
    size_t error_count;
} g = {TRACE, NULL, NULL, NULL, NULL, NULL, 0};

// *****************************************************************************
// Private static function and ISR prototypes
// *****************************************************************************

// *****************************************************************************
// Private inline function definitions
// *****************************************************************************

// *****************************************************************************
// Public function bodies
// *****************************************************************************

void util_log_init (util_log_level_t const level, const char * const host_name,
                    util_log_function_t const error_log_function,
                    util_log_function_t const info_log_function,
                    util_log_function_t const trace_log_function,
                    get_time_function_t const get_time_function)
{
    g.level              = level;
    g.host_name          = host_name;
    g.error_log_function = error_log_function;
    g.trace_log_function = trace_log_function;
    g.info_log_function  = info_log_function;
    g.get_time_function  = get_time_function;
    g.error_count        = 0;
}

void util_log(util_log_level_t const level,
              const char * const file,
              uint32_t const line,
              const char * const format, ...)
{
    if ((0 == g.host_name) || (0 == g.error_log_function) ||
        (0 == g.trace_log_function) || (0 == file) || (0 == format))
    {
        // Null pointer; unable to call log function.
    }
    else
    {
        // Keep our own little buffer for the formatted string to save a
        // caller from needing to allocate one. Disadvantage is that we have a
        // max size that the final message can be.
        const uint32_t msg_size = 141;
        char           msg[msg_size];

        //lint -esym(953, "args") 'args' cannot be const.
        va_list args;
        //lint -esym(950, "*to_semi*") We have no control over va_start.
        //lint -e{530} We have no control over va_start.
        va_start(args, format);
        //lint -e{534} The returned value is ignored because there is
        // nothing that can be done from within this function.
        vsnprintf(msg, msg_size, format, args);
        va_end(args);

        if (level <= g.level)
        {
            char time_buff[18];
            g.get_time_function(&time_buff, 18);

            const uint32_t out_msg_size = 255;
            char           out_msg[out_msg_size];
            snprintf(out_msg, out_msg_size,
                     "%s, %s, %s, %s, line %ld, %s \r\n",
                     LEVEL_STRINGS[level],
                     g.host_name,
                     time_buff,
                     file,
                     line,
                     msg);

            if (ERROR == level)
            {
                g.error_count++;
            }

            if (TRACE == level)
            {
                (g.trace_log_function)(out_msg);
            }
            else if (INFO == level)
            {
                (g.info_log_function)(out_msg);
            }
            else
            {
                (g.error_log_function)(out_msg);

            }
        }
    }
}

size_t util_log_poll_error_count(void)
{
    const size_t result = g.error_count;
    g.error_count = 0;

    return result;
}

// *****************************************************************************
// Private function bodies
// *****************************************************************************

// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************
