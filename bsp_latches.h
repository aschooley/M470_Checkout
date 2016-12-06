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
    OFF = 0,
    ON
} power_state_t;

// these arranged in the oder that they arranged in the shift register
typedef enum
{
    FLUIDICS_VALVE_PUMP_SAFETY,
    FLUIDICS_VALVE_MEDIA,
    FLUIDICS_VALVE_AB,
    FLUIDICS_PUMP,
    FLUIDICS_COUNT
} fluidics_t;

// these arranged in the oder that they arranged in the shift register
typedef enum
{
    CAL_CELL_MANIFOLD = 9,
    CAL_CELL_BAG
} cal_cell_t;

// *****************************************************************************
// Public constant definitions
// *****************************************************************************

// *****************************************************************************
// Public function prototypes
// *****************************************************************************

void bsp_set_valve_power (card_t card, power_state_t state);

void bsp_set_card_power (card_t card, power_state_t state);

void bsp_set_cal_cell_power (card_t card, cal_cell_t cal_cell_type,
                             power_state_t state);

void bsp_set_fluidics_power (card_t card, fluidics_t fluidics_object,
                             power_state_t state);

void bsp_set_heater_power (thermal_zone_t zone, power_state_t state);

// *****************************************************************************
// Public inline function definitions
// *****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // BSP_LATCHES_H
