/**
 * @file drv_logger.c
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2016 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 TI 4.4.5
 * $Id$
 */

#include "drv_logger.h"
// Application header files
#include "bsp_pins_conf.h"
#include "bsp_pins.h"
#include "bsp_pins_types.h"
#include "util_log.h"
#include "drv_ds3234.h"
// Internal library header files
// Third-party library header files
#include <driverlib.h>
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

// *****************************************************************************
// Private static data definitions
// *****************************************************************************

// *****************************************************************************
// Private static function and ISR prototypes
// *****************************************************************************

/**
 * Get the time from the RTC.
 * @param[out]buffer to hold the time and date in ascii.
 * @param[in] size of the buffer.
 */
void get_time (char * const buffer, const uint8_t buff_sz);

/**
 * On error event print msg to trace port.
 */
void error_logger_log (const char * msg);

/**
 * On trace event printmsg to the trace port.
 */
void trace_logger_log (const char * msg);

/**
 * On info event print msg to the trace port and also to the data port.
 */
void info_logger_log (const char * msg);

// *****************************************************************************
// Private inline function definitions
// *****************************************************************************

// *****************************************************************************
// Public function bodies
// *****************************************************************************

void logger_init(void)
{
    init_uart();
    util_log_init(TRACE, "Optics_Reader", error_logger_log, info_logger_log,
                  trace_logger_log, get_time);
}

// *****************************************************************************
// Private function bodies
// *****************************************************************************

void get_time(char * const buffer, const uint8_t buff_sz)
{
	static uint32_t msg_number = 0;
	snprintf(buffer, buff_sz, "%d",
			msg_number);

}
void error_logger_log (const char * msg)
{
    fputs(msg, 0);
}
void trace_logger_log (const char * msg)
{
    fputs(msg, 0);
}
void info_logger_log (const char * msg)
{
    fputs(msg, 0);
    cout_data_channel(msg);

}



// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************
