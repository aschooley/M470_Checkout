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

card_manifold_address_t bsp_card_get_bank(card_t card){

	card_manifold_address_t address;

	if( CARD_1 <= card && CARD_9 >= card )
	{
		address.bank = CARD_BANK_1;
		address.card = card;
	}
	else if (CARD_10 <= card && CARD_18 >= card)
	{
		address.bank = CARD_BANK_2;
		address.card = card - CARD_10;
	}
	else
	{
		logf(ERROR,"invalid card returned %d",card);
	}
	return address;
}

// *****************************************************************************
// Private function bodies
// *****************************************************************************

// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************
