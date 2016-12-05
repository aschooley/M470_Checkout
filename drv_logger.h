#ifndef DRV_LOGGER_H
#define DRV_LOGGER_H

/**
 * @file drv_logger.h
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2016 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 TI 4.4.5
 * $Id$
 */

// Application header files
// Internal library header files
// Third-party library header files
// Standard library header files

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Public macro definitions
// *****************************************************************************

// *****************************************************************************
// Public data type definitions (enum, struct, typedef, union)
// *****************************************************************************

// *****************************************************************************
// Public constant definitions
// *****************************************************************************

// *****************************************************************************
// Public function prototypes
// *****************************************************************************

/**
 * Start up the trace logger.  Must be called before any trace calls.
 */
void logger_init (void);

/**
 * Logs a message.
 * @param[in] msg the message to log; OK if NULL
 */
//void trace_logger_log (const char * const msg);

// *****************************************************************************
// Public inline function definitions
// *****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // DRV_LOGGER_H
