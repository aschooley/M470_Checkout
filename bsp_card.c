/**
 * @file bsp_card.c
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2015 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 GCC 4.9.1
 * $Id$
 */

#include "bsp_card.h"
// Application header files
#include "util_log.h"
// Internal library header files
// Third-party library header files
// Standard library header files

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

// *****************************************************************************
// Private inline function definitions
// *****************************************************************************

// *****************************************************************************
// Public function bodies
// *****************************************************************************

card_manifold_address_t bsp_card_get_card_location(card_t card)
{

    card_manifold_address_t address;
    address.box = BOX_CARD;

    if ( CARD_1 <= card && CARD_9 >= card )
    {
        address.bank  = CARD_BANK_1;
        address.index = card;
    }
    else if (CARD_10 <= card && CARD_18 >= card)
    {
        address.bank  = CARD_BANK_2;
        address.index = card - CARD_10;
    }
    else
    {
        logf(ERROR, "invalid card returned %d", card);
    }
    return address;
}

card_manifold_address_t bsp_card_get_thermal_location(thermal_zone_t zone)
{

    card_manifold_address_t address;

    switch (zone)
    {
        case THERMAL_ZONE_CARD_1: //0
        case THERMAL_ZONE_CARD_2: //1
        case THERMAL_ZONE_CARD_3:
        case THERMAL_ZONE_CARD_4:
        case THERMAL_ZONE_CARD_5:
        case THERMAL_ZONE_CARD_6:
        case THERMAL_ZONE_CARD_7:
        case THERMAL_ZONE_CARD_8:
        case THERMAL_ZONE_CARD_9:
        case THERMAL_ZONE_CAL_CELL_MANIFOLD_1: //9
            address.bank  = CARD_BANK_1;
            address.index = zone;
            address.box   = BOX_CARD;
            break;

        case THERMAL_ZONE_CAL_CELL_BAG_1: // 0
        case THERMAL_ZONE_BAG_1: // 1
            address.bank  = CARD_BANK_1;
            address.index = zone - THERMAL_ZONE_CAL_CELL_BAG_1;
            address.box   = BOX_BAG;
            break;

        case THERMAL_ZONE_CARD_10: //0
        case THERMAL_ZONE_CARD_11: //1
        case THERMAL_ZONE_CARD_12:
        case THERMAL_ZONE_CARD_13:
        case THERMAL_ZONE_CARD_14:
        case THERMAL_ZONE_CARD_15:
        case THERMAL_ZONE_CARD_16:
        case THERMAL_ZONE_CARD_17:
        case THERMAL_ZONE_CARD_18:
        case THERMAL_ZONE_CAL_CELL_MANIFOLD_2: //9
            address.bank  = CARD_BANK_2;
            address.index = zone - THERMAL_ZONE_CARD_10;
            address.box   = BOX_CARD;
            break;

        case THERMAL_ZONE_CAL_CELL_BAG_2: //0
        case THERMAL_ZONE_BAG_2: //1
            address.bank  = CARD_BANK_2;
            address.index = zone - THERMAL_ZONE_CAL_CELL_BAG_2;
            address.box   = BOX_BAG;
            break;

        case THERMAL_ZONE_COUNT:
        default:
            logf(ERROR, "invalid zone entered, zone = %d", zone);
            break;
    }

    return address;
}

// *****************************************************************************
// Private function bodies
// *****************************************************************************

// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************
