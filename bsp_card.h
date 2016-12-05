#ifndef BSP_CARD_H
#define BSP_CARD_H

/**
 * @file bsp_card.h
 * @brief
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

typedef enum
{
	CARD_BANK_1,
	CARD_BANK_2,
	CARD_BANK_COUNT
} card_bank_t;

typedef struct
{
	card_bank_t bank;
	card_t card;
} card_manifold_address_t;

// *****************************************************************************
// Public constant definitions
// *****************************************************************************

// *****************************************************************************
// Public function prototypes
// *****************************************************************************

card_manifold_address_t bsp_card_get_bank(card_t card);

// *****************************************************************************
// Public inline function definitions
// *****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // BSP_CARD_H

