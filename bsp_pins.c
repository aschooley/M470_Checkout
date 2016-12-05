/**
 * @file bsp_pins.c
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2016 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 TI 4.4.5
 * $Id$
 */

#include "bsp_pins.h"
// Application header files
#include "bsp_pins_types.h"
#include "bsp_pins_conf.h"
#ifdef PIN_TRACE
    #include "drv_logger.h"
    #include "util_log.h"
#endif
// Internal library header files
// Third-party library header files
#include <msp430.h>
// Standard library header files

#undef PIN_TRACE


// *****************************************************************************
// Private macro definitions
// *****************************************************************************

/**
 * Macro used to populate the pin_mode switch statement.  Used in conjuction
 * with PxX(p,x) etc. macros.
 */
#define pcase_mode(p) \
    case p: \
        if (type == OUTPUT) { PxDIR(p) |= mask; } \
        else{ PxDIR(p) &= ~mask; } \
        break

/**
 * Macro used to poplulate the digital_write switch statement.  Used in conjuction
 * with PxX(p,x) etc. macros.
 */
#define pcase_write(p) \
    case p: \
        if (state == HIGH) { PxOUT(p) |= mask; } \
        else{ PxOUT(p) &= ~mask; } \
        break

/**
 * Macro used to poplulate the digital_toggle switch statement.  Used in conjuction
 * with PxX(p,x) etc. macros.
 */
#define pcase_toggle(p) \
    case p: \
        PxOUT(p) ^= mask; \
        break

/**
 * Macro used to poplulate the digital_read switch statement.  Used in conjuction
 * with PxX(p,x) etc. macros.
 */
#define pcase_read(p) \
    case p: \
        retval = PxIN(p); \
        break

/**
 * Macro used to populate the alternate pin functions switch statement.  Used in
 * conjunction with PxX(p,x) etc. macros.
 */
#define pcase_sel(p) \
    case p: \
        switch (function) \
        { \
            case IO: \
                PxSEL0(p) &= ~mask; \
                PxSEL1(p) &= ~mask; \
                break; \
            case PRIMARY: \
                PxSEL0(p) |= mask; \
                PxSEL1(p) &= ~mask; \
                break; \
            case SECONDARY: \
                PxSEL0(p) &= ~mask; \
                PxSEL1(p) |= mask; \
                break; \
            case TERTIARY: \
                PxSEL0(p) |= mask; \
                PxSEL1(p) |= mask; \
                break; \
        } \
        break \

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

/**
 * Sets the pin direction; input or output and if an output will assign its
 * value high or low according to it's default value in the pin table.
 * @param[in] pin to work on
 */
void bsp_pin_setup (const pin_t * const pin);

// *****************************************************************************
// Private inline function definitions
// *****************************************************************************

// *****************************************************************************
// Public function bodies
// *****************************************************************************

void bsp_pin_set_alt_funct(const pin_t * const pin, pin_alt_function function)
{
    uint8_t mask = 1 << pin->hw.bit;

    switch (pin->hw.port)
    {
        pcase_sel(1);
        pcase_sel(2);
        pcase_sel(3);
        pcase_sel(4);
        pcase_sel(5);
        pcase_sel(6);
        pcase_sel(7);
        pcase_sel(8);
        pcase_sel(9);
        pcase_sel(10);
    }
}

void bsp_pin_set_mode(const pin_t * const pin, pin_type_t type)
{
    uint8_t mask = 1 << pin->hw.bit;

    switch (pin->hw.port)
    {
        pcase_mode(1);
        pcase_mode(2);
        pcase_mode(3);
        pcase_mode(4);
        pcase_mode(5);
        pcase_mode(6);
        pcase_mode(7);
        pcase_mode(8);
        pcase_mode(9);
        pcase_mode(10);
    }
}

void bsp_pin_digital_write(const pin_t * const pin, pin_state_t state)
{
    uint8_t mask = 1 << pin->hw.bit;

    if (state == ENABLED)
    {
        state = pin->enabled_state;
    }

    if (state == DISABLED)
    {
        if (HIGH == pin->enabled_state)
        {
            state = LOW;
        }
        else
        {
            state = HIGH;
        }
    }

    switch (pin->hw.port)
    {
        pcase_write(1);
        pcase_write(2);
        pcase_write(3);
        pcase_write(4);
        pcase_write(5);
        pcase_write(6);
        pcase_write(7);
        pcase_write(8);
        pcase_write(9);
        pcase_write(10);
    }
}

void bsp_pin_digital_toggle(const pin_t * const pin)
{
    uint8_t mask = 1 << pin->hw.bit;

    switch (pin->hw.port)
    {
        pcase_toggle(1);
        pcase_toggle(2);
        pcase_toggle(3);
        pcase_toggle(4);
        pcase_toggle(5);
        pcase_toggle(6);
        pcase_toggle(7);
        pcase_toggle(8);
        pcase_toggle(9);
        pcase_toggle(10);
    }
}

pin_state_t bsp_pin_digital_read(const pin_t * const pin)
{
    uint8_t          mask = 1 << pin->hw.bit;
    volatile uint8_t retval;

    switch (pin->hw.port)
    {
        pcase_read(1);
        pcase_read(2);
        pcase_read(3);
        pcase_read(4);
        pcase_read(5);
        pcase_read(6);
        pcase_read(7);
        pcase_read(8);
        pcase_read(9);
        pcase_read(10);
    }
    retval &= mask;

    if (0 == retval)
    {
        retval = LOW;
    }
    else
    {
        retval = HIGH;
    }
    return (pin_state_t)retval;
}

void bsp_pins_initalize(void)
{

    static const pin_t init_pin_table[] = {
#define pin_table_entry(a, b, c, d, e, f) {b, c, d, e, f \
},
        pin_table
#undef pin_table_entry
    };

    uint8_t pin_table_iterator;

    for (pin_table_iterator = 0;
         pin_table_iterator < sizeof(init_pin_table) / sizeof(init_pin_table[0]);
         pin_table_iterator++)
    {
        bsp_pin_setup(&init_pin_table[pin_table_iterator]);
#ifdef PIN_TRACE
        logf(TRACE, "setup pin: %s", pin_names[pin_table_iterator]);
#endif
    }
}

// *****************************************************************************
// Private function bodies
// *****************************************************************************

void bsp_pin_setup(const pin_t * const pin)
{
    bsp_pin_set_mode(pin, pin->type);

    if (OUTPUT == pin->type)
    {
        bsp_pin_digital_write(pin, pin->default_state);
    }
    bsp_pin_set_alt_funct(pin, pin->alternate_function);
}
// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************
