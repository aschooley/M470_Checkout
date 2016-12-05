#ifndef BSP_PINS_TYPES_H
#define BSP_PINS_TYPES_H

/**
 * @file bsp_pins_types.h
 * @brief Colletion of types used by the pin files.
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2016 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 TI 4.4.5
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
 * Enumeration of all the alternate functions a pin can have.  See data sheet
 * for function assignment.
 */
typedef enum
{
    PRIMARY,
    SECONDARY,
    TERTIARY,
    IO,
}pin_alt_function;

/**
 * Enumeration of all of the ports on the chip.
 */
typedef enum
{
    PORT_1 = 1,
    PORT_2,
    PORT_3,
    PORT_4,
    PORT_5,
    PORT_6,
    PORT_7,
    PORT_8,
    PORT_9,
    PORT_10,
    PORT_J,
    PORT_NA
}pin_port_t;

/**
 * Enumeration of all the pins in a port.
 */
typedef enum
{
    BIT_0 = 0,
    BIT_1,
    BIT_2,
    BIT_3,
    BIT_4,
    BIT_5,
    BIT_6,
    BIT_7,
    BIT_NA
} pin_bit_t;

/**
 * Enumeration of all the states a pin can have, physical and logical.
 */
typedef enum
{
    LOW = 0,
    HIGH,
    ENABLED,
    DISABLED,
    NONE     // for input case
}pin_state_t;

/**
 * Enumeration of different pin types.
 */
typedef enum
{
    INPUT,
    OUTPUT,
    ANALOG
}pin_type_t;

/**
 * The physical pin mapping information.
 */
typedef struct
{
    uint8_t    number;
    pin_port_t port;
    pin_bit_t  bit;
}physical_pin_t;

/**
 * Everything about a pin.  What port and pin, how do set it up at startup,
 * what value is logically 'on'
 */
typedef struct
{
    physical_pin_t   hw;
    pin_type_t       type;
    pin_state_t      default_state;
    pin_state_t      enabled_state;
    pin_alt_function alternate_function;
}pin_t;

// *****************************************************************************
// Public constant definitions
// *****************************************************************************

// *****************************************************************************
// Public function prototypes
// *****************************************************************************

// *****************************************************************************
// Public inline function definitions
// *****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // BSP_PINS_TYPES_H
