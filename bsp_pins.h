#ifndef BSP_PINS_H
#define BSP_PINS_H

/**
 * @file bsp_pins.h
 * @brief Methods that can be done to port pins.
 * @details Contains functions that will manipulate port pins, read, write etc.
 * is designed so that pin function names can be used and their logical state,
 * on/off can be used rather than harware logic levels.
 * @copyright COPYRIGHT NOTICE: (c) 2016 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 TI 4.4.5
 * $Id$
 */

// Application header files
#include "bsp_pins_types.h"
// Internal library header files
// Third-party library header files
// Standard library header files

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Public macro definitions
// *****************************************************************************

#define PxX(p, x) P ## p ## x
#define PxOUT(p) PxX(p, OUT)
#define PxDIR(p) PxX(p, DIR)
#define PxIN(p)  PxX(p, IN)
#define PxSEL0(p) PxX(p, SEL0)
#define PxSEL1(p) PxX(p, SEL1)

// *****************************************************************************
// Public data type definitions (enum, struct, typedef, union)
// *****************************************************************************

// *****************************************************************************
// Public constant definitions
// *****************************************************************************

// *****************************************************************************
// Public function prototypes
// *****************************************************************************

/**
 * Sets a pin to one of its alternate functions.
 * @param[in] pin to set.
 * @param[in] function to set it to.
 */
void bsp_pin_set_alt_funct (const pin_t * const pin, pin_alt_function function);

/**
 * Sets a pin to input or output.
 * @param[in] pin to set.
 * @param[in] type what type to set the pin to.
 */
void bsp_pin_set_mode (const pin_t * const pin, pin_type_t type);

/**
 * Sets a digital ouput pin high or low.
 * @param[in] pin to set.
 * @param[in] state to set the pin to.
 */
void bsp_pin_digital_write (const pin_t * const pin, pin_state_t state);

/**
 * Toggles a digial output pin.  Will xor its state.  High -> low, low -> high.
 * @param[in] pin to toggle.
 */
void bsp_pin_digital_toggle (const pin_t * const pin);

/**
 * Reads the value of an input pin.
 * @param[in] pin to read the value of.
 * @retval HIGH the pin is a logic 1.
 * @retval LOW the pin is a logic 0/
 */
pin_state_t bsp_pin_digital_read (const pin_t * const pin);

/**
 * Sets up the pins accodring to the pin table in the bsp_pins_conf.h file
 */
void bsp_pins_initalize (void);

// *****************************************************************************
// Public inline function definitions
// *****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // BSP_PINS_H
