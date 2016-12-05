#ifndef DRV_OW_H
#define DRV_OW_H

/**
 * @file drv_ow.h
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
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Public macro definitions
// *****************************************************************************

// *****************************************************************************
// Public data type definitions (enum, struct, typedef, union)
// *****************************************************************************

/** A 1-wire ID is an array of 8 bytes. */
typedef uint8_t one_wire_id_t[8];

// *****************************************************************************
// Public constant definitions
// *****************************************************************************

// *****************************************************************************
// Public function prototypes
// *****************************************************************************


void convert_id_to_string (char * buff, one_wire_id_t id);

void report_1_wire_devices (void);

uint8_t drv_ow_get_dev_cnt (void);


uint8_t drv_ow_get_dev_cnt (void);

bool drv_ow_get_id ( one_wire_id_t * id, uint8_t dev);
bool drv_ow_get_contents (char * buff, uint8_t buff_sz, uint8_t dev);
uint8_t drv_ow_get_m906_sn (void);
// *****************************************************************************
// Public inline function definitions
// *****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // DRV_OW_H
