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
    // Create return container.
    card_manifold_address_t address;
    // Fill in the box field, it will always be in the card box.
    address.box = BOX_CARD;

    // If it is in the first 9 cards return bank one and its own index.
    if ( CARD_1 <= card && CARD_9 >= card )
    {
        address.bank  = CARD_BANK_1;
        address.index = card;
    }
    // If it is in the second 9 cards return bank two and mod the index by 9.
    else if (CARD_10 <= card && CARD_18 >= card)
    {
        address.bank  = CARD_BANK_2;
        address.index = card - CARD_10;
    }
    // If we got here something went wrong, send a message to the debug
    // terminal.
    else
    {
        logf(ERROR, "invalid card returned %d", card);
    }
    return address;
}

card_manifold_address_t bsp_card_get_thermal_location(thermal_zone_t zone)
{
    // Create return container.
    card_manifold_address_t address;

    // Switch statement designed to fall through.
    switch (zone)
    {
        // Case 1, items in the card box of bank 1.
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

        // Case 2, items in the bag box of bank 1.
        case THERMAL_ZONE_CAL_CELL_BAG_1: // 0
        case THERMAL_ZONE_BAG_1: // 1
            address.bank  = CARD_BANK_1;
            address.index = zone - THERMAL_ZONE_CAL_CELL_BAG_1;
            address.box   = BOX_BAG;
            break;

        // Case 3, items in the card box of bank 2.
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

        // Case 4. items in the bag box of bank 2.
        case THERMAL_ZONE_CAL_CELL_BAG_2: //0
        case THERMAL_ZONE_BAG_2: //1
            address.bank  = CARD_BANK_2;
            address.index = zone - THERMAL_ZONE_CAL_CELL_BAG_2;
            address.box   = BOX_BAG;
            break;

        // Case 5. something went wrong, shouldn't get here.  Send a message to
        // the debug terminal.
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
