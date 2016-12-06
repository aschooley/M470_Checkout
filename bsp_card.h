#ifndef BSP_CARD_H
#define BSP_CARD_H

/**
 * @file bsp_card.h
 * @brief Hardware translation between the logical payload object and their
 * physical addressing inside the hardware.
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2015 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 GCC 4.9.1
 * $Id$
 */

// Application header files
// Internal library header files
// Third-party library header files
// Standard library header files
#include <stdint.h>

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
 * Identify each card in the payload.
 */
typedef enum
{
    CARD_1,
    CARD_2,
    CARD_3,
    CARD_4,
    CARD_5,
    CARD_6,
    CARD_7,
    CARD_8,
    CARD_9,
    CARD_10,
    CARD_11,
    CARD_12,
    CARD_13,
    CARD_14,
    CARD_15,
    CARD_16,
    CARD_17,
    CARD_18,
    CARD_COUNT
} card_t;

/**
 * Identify each thermal heater zone in the payload.
 */
typedef enum
{
    THERMAL_ZONE_CARD_1,
    THERMAL_ZONE_CARD_2,
    THERMAL_ZONE_CARD_3,
    THERMAL_ZONE_CARD_4,
    THERMAL_ZONE_CARD_5,
    THERMAL_ZONE_CARD_6,
    THERMAL_ZONE_CARD_7,
    THERMAL_ZONE_CARD_8,
    THERMAL_ZONE_CARD_9,
    THERMAL_ZONE_CAL_CELL_MANIFOLD_1,
    THERMAL_ZONE_CAL_CELL_BAG_1,
    THERMAL_ZONE_BAG_1,
    THERMAL_ZONE_CARD_10,
    THERMAL_ZONE_CARD_11,
    THERMAL_ZONE_CARD_12,
    THERMAL_ZONE_CARD_13,
    THERMAL_ZONE_CARD_14,
    THERMAL_ZONE_CARD_15,
    THERMAL_ZONE_CARD_16,
    THERMAL_ZONE_CARD_17,
    THERMAL_ZONE_CARD_18,
    THERMAL_ZONE_CAL_CELL_MANIFOLD_2,
    THERMAL_ZONE_CAL_CELL_BAG_2,
    THERMAL_ZONE_BAG_2,
    THERMAL_ZONE_COUNT
} thermal_zone_t;

/**
 * Identify the different manifold halves.
 */
typedef enum
{
    CARD_BANK_1,
    CARD_BANK_2,
    CARD_BANK_COUNT
} card_bank_t;

/**
 * Identify the different pcb locations.
 */
typedef enum
{
    BOX_CARD,
    BOX_BAG,
    BOX_COUNT
} box_t;

/**
 * Everything needed to address a logical object.
 */
typedef struct
{
    /** Which half of the payload it is in. */
    card_bank_t bank;
    /** Which address it is on the shift register. */
    uint8_t index;
    /** Which board it is on. */
    box_t box;
} card_manifold_address_t;

// *****************************************************************************
// Public constant definitions
// *****************************************************************************

// *****************************************************************************
// Public function prototypes
// *****************************************************************************

/**
 * Translates a logcial card to its physical signal address in the hardware.
 * @param[in] card that you want to know the signal address of.
 * @return structure that hold the information to address the card.
 */
card_manifold_address_t bsp_card_get_card_location (card_t card);

/**
 * Translates a logical heater to its physical signal address in the hardware.
 * @param[in] zone that you want to know the signal address of.
 * @return structure that holds the information to address that zone.
 */
card_manifold_address_t bsp_card_get_thermal_location (thermal_zone_t zone);

// *****************************************************************************
// Public inline function definitions
// *****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // BSP_CARD_H
