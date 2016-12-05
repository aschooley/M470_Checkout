#ifndef BSP_LATCHES_H
#define BSP_LATCHES_H

/**
 * @file bsp_latches.h
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2015 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 GCC 4.9.1
 * $Id$
 */

// Application header files
#include "bsp_card.h"
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

typedef enum
{
	VALVE_DISABLED = 0,
	VALVE_ENABLED
} valve_state_t;

// *****************************************************************************
// Public constant definitions
// *****************************************************************************

// *****************************************************************************
// Public function prototypes
// *****************************************************************************

void bsp_set_valve(card_t card, valve_state_t state);

// *****************************************************************************
// Public inline function definitions
// *****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // BSP_LATCHES_H

