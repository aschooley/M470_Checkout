/**
 * @file bsp_latches.c
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2015 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 GCC 4.9.1
 * $Id$
 */

#include "bsp_latches.h"
#include "bsp_card.h"
// Application header files
#include "bsp_pins.h"
#include "bsp_pins_conf.h"
#include "util_log.h"
// Internal library header files
#include <driverlib.h>
// Third-party library header files
// Standard library header files
#include <stdbool.h>

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

static void send_address (uint16_t addr);

static void modify_bitfield (uint16_t * bitfield, uint16_t modifier,
                             power_state_t operation);

// *****************************************************************************
// Private inline function definitions
// *****************************************************************************

static inline uint16_t create_bitmask(uint8_t value)
{
    // initalize it to 1, this is valve 1
    uint16_t bitmap = 1;
    // shift the 1 over card number of spaces, if valve one is addressed it will
    // be shifted zero bits and essentially falls through.
    bitmap = bitmap << value;
    return bitmap;
}


// *****************************************************************************
// Public function bodies
// *****************************************************************************

bool bsp_set_valve_power(card_t card, power_state_t state)
{
    // Initalize the static varible to an out of bounds value.
    static card_t card_in_use = CARD_COUNT;
    // Initalize success to false.
    bool success = false;

    // Arguably the below conditinos could be put into only a success = true
    // if statent and let the initization condition of false fall through.
    // I chose to enumerate all conditions to help identify any possible
    // logic error on my part.

    // If no card is active you can turn one on.
    if (CARD_COUNT == card_in_use && ON == state)
    {
        success = true;
    }
    // If a card is active you can not turn one on.
    else if (CARD_COUNT != card_in_use && ON == state)
    {
        success = false;
    }
    // If a card is active you can only turn that one off.
    else if (card == card_in_use && OFF == state)
    {
        success = true;
    }
    // You can not turn off any card but the on that is on.
    else if (card != card_in_use && OFF == state)
    {
        success = false;
    }
    // If we got here something went wrong, above cases should have handled it.
    else
    {
        log(ERROR, "valve power logic condition not accounted for, pgm error!");
    }

    // only do stuff if we in one of the two possible go conditions are met.
    if (success)
    {
        card_manifold_address_t card_address = bsp_card_get_card_location(
            card);
        uint16_t address_bitmask = create_bitmask(
            card_address.index);
        uint16_t latch_state = 0;
        modify_bitfield(&latch_state, address_bitmask, state);

        if (CARD_BANK_1 == card_address.bank)
        {
            bsp_pin_digital_write(&pins.fluidics_en_latch_mani_1, DISABLED);
            send_address(latch_state);
            bsp_pin_digital_write(&pins.fluidics_en_latch_mani_1, ENABLED);
        }
        else if (CARD_BANK_2 == card_address.bank)
        {
            bsp_pin_digital_write(&pins.fluidics_en_latch_mani_2, DISABLED);
            send_address(latch_state);
            bsp_pin_digital_write(&pins.fluidics_en_latch_mani_2, ENABLED);
        }
        else
        {
            success = false;
            logf(ERROR, "Invalid card bank. Bank = %d", card_address.bank);
        }
    }

    // if the above operations succeded, update our state.
    if (success)
    {
        if (ON == state)
        {
            card_in_use = card;
        }
        else
        {
            card_in_use = CARD_COUNT;
        }
    }
    return success;
}


bool bsp_set_card_power(card_t card, power_state_t state)
{

    card_manifold_address_t card_address    = bsp_card_get_card_location(card);
    uint16_t                address_bitmask = create_bitmask(card_address.index);
    uint16_t                latch_state     = 0;
    modify_bitfield(&latch_state, address_bitmask, state);

    if (CARD_BANK_1 == card_address.bank)
    {
        bsp_pin_digital_write(&pins.card_en_latch_1, DISABLED);
        send_address(latch_state);
        bsp_pin_digital_write(&pins.card_en_latch_1, ENABLED);
    }
    else if (CARD_BANK_2 == card_address.bank)
    {
        bsp_pin_digital_write(&pins.card_en_latch_2, DISABLED);
        send_address(latch_state);
        bsp_pin_digital_write(&pins.card_en_latch_2, ENABLED);
    }
    else
    {
        logf(ERROR, "Invalid card bank. Bank = %d", card_address.bank);
    }

}

bool bsp_set_cal_cell_power(card_t card, cal_cell_t cal_cell_type,
                            power_state_t state)
{
    // All we need is the bank.
    card_manifold_address_t card_address = bsp_card_get_card_location(card);
    uint16_t                address_bitmask;
    uint16_t                latch_state = 0;

    if (CAL_CELL_MANIFOLD == cal_cell_type || CAL_CELL_BAG == cal_cell_type)
    {
        address_bitmask = create_bitmask(cal_cell_type);
    }
    else
    {
        logf(ERROR, "Invalid cal cell type.  Type = &d", cal_cell_type);
    }

    modify_bitfield(&latch_state, address_bitmask, state);

    if (CARD_BANK_1 == card_address.bank)
    {
        bsp_pin_digital_write(&pins.card_en_latch_1, DISABLED);
        send_address(latch_state);
        bsp_pin_digital_write(&pins.card_en_latch_1, ENABLED);
    }
    else if (CARD_BANK_2 == card_address.bank)
    {
        bsp_pin_digital_write(&pins.card_en_latch_2, DISABLED);
        send_address(latch_state);
        bsp_pin_digital_write(&pins.card_en_latch_2, ENABLED);
    }
    else
    {
        logf(ERROR, "Invalid card bank. Bank = %d", card_address.bank);
    }
}


bool bsp_set_fluidics_power(card_t card, fluidics_t fluidics_object,
                            power_state_t state)
{

    // All we care about is which bank it is in.
    card_manifold_address_t card_address = bsp_card_get_card_location(card);

    uint16_t address_bitmask = 0;

    if (FLUIDICS_COUNT >= fluidics_object)
    {
        address_bitmask = create_bitmask(fluidics_object);
    }
    else
    {
        logf(ERROR, "Invalid fluidics object. Object = %d", fluidics_object);
    }

    uint16_t      retrieved_latch_state = 0;
    const pin_t * pin;

    if (CARD_BANK_1 == card_address.bank)
    {
        // Initalize memory for this latch, it will not be reinitalized since it is static.
        static uint16_t latch_state = 0;
        // Update the saved latch state with the modificaiton.
        modify_bitfield(&latch_state, address_bitmask, state);
        // Return the new latch state.
        retrieved_latch_state = latch_state;
        // Return the correct pin to use.
        pin = &pins.fluidics_en_latch_bag_1;
    }
    else if (CARD_BANK_2 == card_address.bank)
    {

        // Initalize memory for this latch, it will not be reinitalized since it is static.
        static uint16_t latch_state = 0;
        // Update the saved latch state with the modificaiton.
        modify_bitfield(&latch_state, address_bitmask, state);
        // Return the new latch state.
        retrieved_latch_state = latch_state;
        // Return the correct pin to use.
        pin = &pins.fluidics_en_latch_bag_2;
    }
    else
    {
        logf(ERROR, "Invalid card bank. Bank = %d", card_address.bank);
    }
    // Do the operation.
    bsp_pin_digital_write(pin, DISABLED);
    send_address(retrieved_latch_state);
    bsp_pin_digital_write(pin, ENABLED);
}

bool bsp_set_heater_power(thermal_zone_t zone, power_state_t state)
{

    card_manifold_address_t zone_address = bsp_card_get_thermal_location(zone);

    uint16_t      address_bitmask       = create_bitmask(zone_address.index);
    uint16_t      retrieved_latch_state = 0;
    const pin_t * pin;

    if ((CARD_BANK_1 == zone_address.bank) && (BOX_CARD == zone_address.box))
    {
        // Initalize memory for this latch, it will not be reinitalized since it is static.
        static uint16_t latch_state = 0;
        // Update the saved latch state with the modificaiton.
        modify_bitfield(&latch_state, address_bitmask, state);
        // Return the new latch state.
        retrieved_latch_state = latch_state;
        // Return the correct pin to use.
        pin = &pins.heater_en_latch_mani_1;
    }
    else if ((CARD_BANK_1 == zone_address.bank) && (BOX_BAG == zone_address.box))
    {
        // Initalize memory for this latch, it will not be reinitalized since it is static.
        static uint16_t latch_state = 0;
        // Update the saved latch state with the modificaiton.
        modify_bitfield(&latch_state, address_bitmask, state);
        // Return the new latch state.
        retrieved_latch_state = latch_state;
        // Return the correct pin to use.
        pin = &pins.heater_en_latch_bag_1;
    }
    else if ((CARD_BANK_2 == zone_address.bank) &&
             (BOX_CARD == zone_address.box))
    {
        // Initalize memory for this latch, it will not be reinitalized since it is static.
        static uint16_t latch_state = 0;
        // Update the saved latch state with the modificaiton.
        modify_bitfield(&latch_state, address_bitmask, state);
        // Return the new latch state.
        retrieved_latch_state = latch_state;
        // Return the correct pin to use.
        pin = &pins.heater_en_latch_mani2;
    }
    else if ((CARD_BANK_2 == zone_address.bank) && (BOX_BAG == zone_address.box))
    {
        // Initalize memory for this latch, it will not be reinitalized since it is static.
        static uint16_t latch_state = 0;
        // Update the saved latch state with the modificaiton.
        modify_bitfield(&latch_state, address_bitmask, state);
        // Return the new latch state.
        retrieved_latch_state = latch_state;
        // Return the correct pin to use.
        pin = &pins.heater_en_latch_bag_2;
    }
    else
    {
        logf(ERROR, "Invalid bank or box. Bank = %d Box = %d",
             zone_address.bank,
             zone_address.box);
    }
    // Do the operation.
    bsp_pin_digital_write(pin, DISABLED);
    send_address(retrieved_latch_state);
    bsp_pin_digital_write(pin, ENABLED);
}

// *****************************************************************************
// Private function bodies
// *****************************************************************************

static void send_address(uint16_t addr)
{

    uint8_t MSB = addr >> 8;
    uint8_t LSB = (uint8_t) addr;

    // Structure that holds all the SPI config info
    EUSCI_B_SPI_initMasterParam spi_b0_param =
    {
        EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
        8000000,
        1000000,
        EUSCI_B_SPI_MSB_FIRST,
        EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH,
        EUSCI_B_SPI_3PIN
    };
    // Initalize and enable the SPI port.
    EUSCI_B_SPI_initMaster(EUSCI_B0_BASE, &spi_b0_param);
    EUSCI_B_SPI_enable(EUSCI_B0_BASE);

    // Wait for the SPI port to be available.
    while (EUSCI_B_SPI_isBusy(EUSCI_B0_BASE))
    {
        ;
    }
    // Send MSB
    EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, MSB);

    // Wait for the SPI port to be available.
    while (EUSCI_B_SPI_isBusy(EUSCI_B0_BASE))
    {
        ;
    }
    // Send LSB
    EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, LSB);

    // Wait for the SPI port to be available.
    while (EUSCI_B_SPI_isBusy(EUSCI_B0_BASE))
    {
        ;
    }
}

static void modify_bitfield (uint16_t * bitfield, uint16_t bitmask,
                             power_state_t operation)
{
    if (ON == operation)
    {
        *bitfield |= bitmask;
    }
    else if (OFF == operation)
    {
        *bitfield &= (~bitmask);
    }
    else
    {
        logf(ERROR, "bitmask operation unknown.  Operation = %d", operation);
    }
}

// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************
