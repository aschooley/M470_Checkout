/**
 * @file bsp_uart.c
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2016 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 TI 4.4.5
 * $Id$
 */

#include "bsp_uart.h"
// Application header files
// Internal library header files
#include "bsp_pins.h"
#include "bsp_pins_conf.h"
#include "util_log.h"
// Third-party library header files
#include <driverlib.h>
// Standard library header files
#include <stdio.h>
#include <string.h>
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

static const RX_DATA_BUFF_SZ = 200;

// *****************************************************************************
// Private static data definitions
// *****************************************************************************

volatile static struct
{
    char    rx_1_data[RX_DATA_BUFF_SZ];
    uint8_t rx_1_index;
    bool    msg_rdy;
    char    rx_0_data[RX_DATA_BUFF_SZ];
    uint8_t rx_0_index;
} g;

// *****************************************************************************
// Private static function and ISR prototypes
// *****************************************************************************

// *****************************************************************************
// Private inline function definitions
// *****************************************************************************

// *****************************************************************************
// Public function bodies
// *****************************************************************************

void init_uart(void)
{
    EUSCI_A_UART_initParam uart_a1_param = {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,
        52,
        1,
        73,
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
    };

    EUSCI_A_UART_initParam uart_a0_param = {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,
        52,
        1,
        73,
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
    };
/*
        GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN5);
        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN4);
        GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN4);

        GPIO_setAsPeripheralModuleFunctionInputPin(
                        GPIO_PORT_P3,
                        GPIO_PIN5,
                        GPIO_PRIMARY_MODULE_FUNCTION
                        );
        GPIO_setAsPeripheralModuleFunctionOutputPin(
                        GPIO_PORT_P3,
                        GPIO_PIN4,
                        GPIO_PRIMARY_MODULE_FUNCTION
                        );
 */
    EUSCI_A_UART_init(EUSCI_A1_BASE, &uart_a1_param);
    EUSCI_A_UART_enable(EUSCI_A1_BASE);
    g.msg_rdy    = false;
    g.rx_1_index = 0;
    EUSCI_A_UART_enableInterrupt(EUSCI_A1_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);    // Enable interrupt
    memset(g.rx_1_data, 0, RX_DATA_BUFF_SZ);


    EUSCI_A_UART_init(EUSCI_A0_BASE, &uart_a0_param);
    EUSCI_A_UART_enable(EUSCI_A0_BASE);
    g.rx_0_index = 0;
    EUSCI_A_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);    // Enable interrupt

    memset(g.rx_0_data, 0, RX_DATA_BUFF_SZ);
}

int cout_data_channel(const char * _ptr)
{

    //   bsp_pin_digital_write(&pins.uart_1w_sd_sel, LOW);

    // Vars to iterate over the string
    uint16_t i, len;

    // Get the length of the string
    len = strlen(_ptr);

    // Loop over each byte of the string
    for (i = 0; i < len; i++)
    {
        // Wait for the peripherial to be available
        while (!EUSCI_A_UART_getInterruptStatus(EUSCI_A0_BASE,
                                                EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
        {
            ;                                                                                                //while(!(UCA1IFG&UCTXIFG));
        }
        // Stuff byte into the tx reg
        EUSCI_A_UART_transmitData(EUSCI_A0_BASE, _ptr[i]);       //UCA1TXBUF = (unsigned char) _ptr[i];
    }


    logf(TRACE, "written to card: %s", _ptr);

    // Return the number of bytes sent
    return len;
}

bool read_data_msg(char * buffer, uint8_t buff_sz)
{
    bool retval = false;
    EUSCI_A_UART_disableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);


    const uint8_t bytes_copied = memcpy(buffer, g.rx_0_data, buff_sz);
    memset(g.rx_0_data, 0, RX_DATA_BUFF_SZ);

    if (g.rx_0_index == bytes_copied)
    {
        retval = true;
    }
    g.rx_0_index = 0;

    EUSCI_A_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    return (retval);
}

void flush_data_buffer(void)
{
    memset(g.rx_0_data, 0, RX_DATA_BUFF_SZ);
    g.rx_0_index = 0;
}
uint8_t data_msg_size(void)
{
    return (g.rx_0_index);
}


uint8_t trace_msg_recieved(void)
{
    uint8_t retval = 0;

    if (g.msg_rdy)
    {
        retval = g.rx_1_index;
    }
    return (retval);
}

bool read_trace_msg(char * buffer, uint8_t buff_sz)
{
    bool retval = false;

    if (g.rx_1_index <= buff_sz)
    {
        const uint8_t bytes_copied = strncpy(buffer, g.rx_1_data,
                                             RX_DATA_BUFF_SZ);

        if (g.rx_1_index == bytes_copied)
        {
            retval = true;
        }
        g.msg_rdy    = false;
        g.rx_1_index = 0;

        EUSCI_A_UART_enableInterrupt(EUSCI_A1_BASE,
                                     EUSCI_A_UART_RECEIVE_INTERRUPT);                       // Enable interrupt
    }
    return (retval);
}

// *****************************************************************************
// Private function bodies
// *****************************************************************************

int fputc(int _c, register FILE * _fp)
{
    // Wait for peripherial to be available
    while (!EUSCI_A_UART_getInterruptStatus(EUSCI_A1_BASE,
                                            EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
    {
        ;                                                                                            //while(!(UCA1IFG&UCTXIFG));
    }
    // Stuff byte into tx reg
    EUSCI_A_UART_transmitData(EUSCI_A1_BASE, _c);   //UCA1TXBUF = (unsigned char) _c;
    // Return tx'd byte, for giggles I suppose
    return ((unsigned char)_c);
}

int fputs(const char * _ptr, register FILE * _fp)
{
    // Vars to iterate over the string
    uint16_t i, len;

    // Get the length of the string
    len = strlen(_ptr);

    // Loop over each byte of the string
    for (i = 0; i < len; i++)
    {
        // Wait for the peripherial to be available
        while (!EUSCI_A_UART_getInterruptStatus(EUSCI_A1_BASE,
                                                EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
        {
            ;                                                                                                //while(!(UCA1IFG&UCTXIFG));
        }
        // Stuff byte into the tx reg
        EUSCI_A_UART_transmitData(EUSCI_A1_BASE, _ptr[i]);       //UCA1TXBUF = (unsigned char) _ptr[i];
    }

    // Return the number of bytes sent
    return len;
}

// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************


#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
    switch (__even_in_range(UCA1IV, USCI_UART_UCTXCPTIFG))
    {
        case USCI_UART_UCRXIFG:
            g.rx_1_data[g.rx_1_index] = EUSCI_A_UART_receiveData(EUSCI_A1_BASE);

            if (10 == g.rx_1_data[g.rx_1_index])
            {
                EUSCI_A_UART_disableInterrupt(EUSCI_A1_BASE,
                                              EUSCI_A_UART_RECEIVE_INTERRUPT);
                g.msg_rdy = true;
                g.rx_1_index++;
                g.rx_1_data[g.rx_1_index] = 0;
            }
            else if (RX_DATA_BUFF_SZ - 1 > g.rx_1_index)
            {
                g.rx_1_index++;
            }
            break;
    }
}
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    switch (__even_in_range(UCA0IV, USCI_UART_UCTXCPTIFG))
    {
        case USCI_UART_UCRXIFG:
            g.rx_0_data[g.rx_0_index] = EUSCI_A_UART_receiveData(EUSCI_A0_BASE);

/*            if (10 == g.rx_0_data[g.rx_0_index])
            {
                EUSCI_A_UART_disableInterrupt(EUSCI_A0_BASE,
                                              EUSCI_A_UART_RECEIVE_INTERRUPT);
                g.msg_rdy = true;
                g.rx_0_index++;
                g.rx_0_data[g.rx_0_index] = 0;
            }
            else*/if (RX_DATA_BUFF_SZ - 1 > g.rx_0_index)
            {
                g.rx_0_index++;
            }
            break;
    }
}
