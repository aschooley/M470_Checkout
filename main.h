#ifndef MAIN_H
#define MAIN_H

/**
 * @file main.h
 * @brief The entry point of the application.
 * @details Function main() is called by the C runtime code in assembly-language
 * source file "crt0.a" every time power is first applied to the microcontroller
 * or a reset has occurred.
 *
 * For testing purposes, it is desirable to put as little code as possible in
 * the module that contains function main(). The reason is that no code in this
 * module can be linked with a test suite that has a different function main().
 * Thus, there is no public API for this module.
 * @copyright COPYRIGHT NOTICE: (c) 2016 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 TI 4.4.5
 * $Id$
 */


/**
 * @mainpage M906 V1
 * Software description
 *
 * @section Add a section
 */

/**
 * @page Add a page
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

#endif // MAIN_H
