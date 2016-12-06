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

/**
 * Possible power states.
 */
typedef enum
{
    OFF = 0,
    ON
} power_state_t;

/**
 * Fluidics items, three valves and a pump
 * @note These arranged in the oder that they arranged in the shift register.
 */
typedef enum
{
    FLUIDICS_VALVE_PUMP_SAFETY,
    FLUIDICS_VALVE_MEDIA,
    FLUIDICS_VALVE_AB,
    FLUIDICS_PUMP,
    FLUIDICS_COUNT
} fluidics_t;

/**
 * Types of Cal Cells associated with each card.  Each card will have one of
 * each type assigned to it dependingon which bank it is in.
 * @note These arranged in the oder that they arranged in the shift register.
 */
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

/**
 * Turns on or off the power to a valve.
 * @note Only one valve can be on at a time.
 * @param[in] card that is associated with the valve.
 * @param[in] state that you want to set the valve to.
 * @retval true operation completed sucessfully
 * @retval false operation failed, will fail if previous on operation is not
 * closed with a off command.
 */
bool bsp_set_valve_power (card_t card, power_state_t state);

/**
 * Turns on or off the power to a card.
 * @note Only one card can be on at a time.
 * @note This shares hardware with the cal cell too. Only one can be on at a
 * time
 * @param[in] card to manipulate.
 * @param[in] state that you want to set the card power to.
 * @retval true operation completed sucessfully
 * @retval false operation failed, will fail if previous on operation is not
 * closed with a off command.
 */
bool bsp_set_card_power (card_t card, power_state_t state);

/**
 * Turns on or off the power to a cal cell.
 * @note Only one cal cell can be on at a time.
 * @note This shares hardware with the cards too. Only one can be on at a
 * time
 * @param[in] card associated with the call cell.
 * @param[in] state that you want to set the call cell power to.
 * @retval true operation completed sucessfully
 * @retval false operation failed, will fail if previous on operation is not
 * closed with a off command.
 */
bool bsp_set_cal_cell_power (card_t card, cal_cell_t cal_cell_type,
                             power_state_t state);

/**
 * Turns on or off a fluidics object, such as a pump or valve in the bag box.
 * @note Only one card can be operated on at a time.
 * @param[in] card associated with the fluidics operation.
 * @param[in] state that you want to set the fluidic objects power to.
 * @retval true operation completed sucessfully
 * @retval false operation failed, will fail if operations to a cards fluidics
 * are not all shut down.
 */
bool bsp_set_fluidics_power (card_t card, fluidics_t fluidics_object,
                             power_state_t state);

/**
 * Turns on or off a heater.
 * @note Does not block the number of heaters that can be on.  Be sure not to
 * exceed power limits.
 * @param[in] zone to turn control
 * @param[in] state that you want to set the heater power power to.
 * @retval true operation completed sucessfully, currently only reuturn value.
 */
bool bsp_set_heater_power (thermal_zone_t zone, power_state_t state);

// *****************************************************************************
// Public inline function definitions
// *****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // BSP_LATCHES_H
