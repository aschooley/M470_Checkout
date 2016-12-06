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

// *****************************************************************************
// Private macro definitions 
// *****************************************************************************

// *****************************************************************************
// Private data type definitions (enum, struct, typedef, union)
// *****************************************************************************

typedef enum
{
	VALVE_CARD_1 = 0,
	VALVE_CARD_2,
	VALVE_CARD_3,
	VALVE_CARD_4,
	VALVE_CARD_5,
	VALVE_CARD_6,
	VALVE_CARD_7,
	VALVE_CARD_8,
	VALVE_CARD_9,
	VALVE_CARD_10,
	VALVE_CARD_11,
	VALVE_CARD_12,
	VALVE_CARD_13,
	VALVE_CARD_14,
	VALVE_CARD_15,
	VALVE_CARD_16,
	VALVE_CARD_17,
	VALVE_CARD_18,
	VALVE_MEDIA_1,
	VALVE_MEDIA_2,
	VALVE_PUMP_1,
	VALVE_PUMP_2,
	VALVE_AB_1,
	VALVE_AB_2,
	VALVE_COUNT
} valve_t;


// *****************************************************************************
// Private static constant definitions
// *****************************************************************************

// *****************************************************************************
// Private static data definitions
// *****************************************************************************

// *****************************************************************************
// Private static function and ISR prototypes
// *****************************************************************************

static void send_address(uint16_t addr);

// *****************************************************************************
// Private inline function definitions
// *****************************************************************************

static inline uint16_t create_valve_address(card_t card)
{
	// initalize it to 1, this is valve 1
	uint16_t bit_map = 1;
	// shift the 1 over card number of spaces, if valve one is addressed it will
	// be shifted zero bits and essentially falls through.
	bit_map = bit_map << card;
	return bit_map;
}


// *****************************************************************************
// Public function bodies
// *****************************************************************************

void bsp_set_valve(card_t card, valve_state_t state){

	card_manifold_address_t card_address = bsp_card_get_bank(card);
	uint16_t address_bit_map = create_valve_address(card_address.card);

	if(CARD_BANK_1 == card_address.bank)
	{
		bsp_pin_digital_write(&pins.fluidics_en_latch_mani_1,DISABLED);
		send_address(address_bit_map);
		bsp_pin_digital_write(&pins.fluidics_en_latch_mani_1,ENABLED);
	}
	else if(CARD_BANK_2 == card_address.bank)
	{
		bsp_pin_digital_write(&pins.fluidics_en_latch_mani_2,DISABLED);
		send_address(address_bit_map);
		bsp_pin_digital_write(&pins.fluidics_en_latch_mani_2,ENABLED);
	}
	else
	{
		logf(ERROR,"invalid card address returned %d",card_address.bank);
	}



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
        8000000,
        EUSCI_B_SPI_MSB_FIRST,
		EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW,
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
}

// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************
