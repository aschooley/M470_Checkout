//---------------------------------------------------------------------------
// Copyright (C) 2000 Dallas Semiconductor Corporation, All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY,  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL DALLAS SEMICONDUCTOR BE LIABLE FOR ANY CLAIM, DAMAGES
// OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// Except as contained in this notice, the name of Dallas Semiconductor
// shall not be used except as stated in the Dallas Semiconductor
// Branding Policy.
//---------------------------------------------------------------------------
//
//  TODO.C - COM functions required to communicate with the DS2480 based
//           Universal Serial Adapter 'U'.  Fill in the platform specific code.
//
//  Version: 2.00
//
//  History: 1.00 -> 1.01  Added function msDelay.
//
//           1.01 -> 1.02  Changed to generic OpenCOM/CloseCOM for easier
//                         use with other platforms.
//
//           1.02 -> 1.03  Removed caps in #includes for Linux capatibility
//                         Add function msGettick()
//           1.03 -> 2.00  Changed 'MLan' to 'ow'. Added support for
//                         multiple ports.
//

#include "ow/ownet.h"
#include <driverlib.h>
#include "bsp_pins.h"
#include "bsp_pins_conf.h"

// exportable functions required
SMALLINT OpenCOM (int, char *);
SMALLINT WriteCOM (int, int, uchar *);
void     FlushCOM (int);
int      ReadCOM (int, int, uchar *);
void     BreakCOM (int);
void     SetBaudCOM (int, int);
void     CloseCOM (int);
long     msGettick (void);
void     msDelay (int);
SMALLINT owHasPowerDelivery (int);
SMALLINT owHasOverDrive (int);
SMALLINT owHasProgramPulse (int);
SMALLINT owWriteBytePower (int, SMALLINT);
SMALLINT owReadBitPower (int, SMALLINT);

volatile static struct
{
    char    rx_data[200];
    uint8_t rx_index;
} g;

//---------------------------------------------------------------------------
// Attempt to open a com port.  Keep the handle in ComID.
// Set the starting baud rate to 9600.
//
// 'portnum'   - number 0 to MAX_PORTNUM-1.  This number provided will
//               be used to indicate the port number desired when calling
//               all other functions in this library.
//
// 'port_zstr' - zero terminate port name.  For this platform
//               use format COMX where X is the port number.
//
//
// Returns: TRUE(1)  - success, COM port opened
//          FALSE(0) - failure, could not open specified port
//
SMALLINT OpenCOM(int portnum, char * port_zstr)
{
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
    EUSCI_A_UART_init(EUSCI_A0_BASE, &uart_a0_param);
    EUSCI_A_UART_enable(EUSCI_A0_BASE);
    EUSCI_A_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);    // Enable interrupt
    __enable_interrupt();

    // bsp_pin_digital_write(&pins.uart_1w_sd_sel, HIGH);

    return 1;
}

//---------------------------------------------------------------------------
// Closes the connection to the port.
//
// 'portnum'  - number 0 to MAX_PORTNUM-1.  This number was provided to
//              OpenCOM to indicate the port number.
//
void CloseCOM(int portnum)
{
    EUSCI_A_UART_disable(EUSCI_A0_BASE);
// @todo, fix link file
    //bsp_pin_digital_write(&pins.uart_1w_sd_sel, LOW);
}

//---------------------------------------------------------------------------
// Flush the rx and tx buffers
//
// 'portnum'  - number 0 to MAX_PORTNUM-1.  This number was provided to
//              OpenCOM to indicate the port number.
//
void FlushCOM(int portnum)
{
    flush_data_buffer();
}

//--------------------------------------------------------------------------
// Write an array of bytes to the COM port, verify that it was
// sent out.  Assume that baud rate has been set.
//
// 'portnum'  - number 0 to MAX_PORTNUM-1.  This number was provided to
//              OpenCOM to indicate the port number.
// 'outlen'   - number of bytes to write to COM port
// 'outbuf'   - pointer ot an array of bytes to write
//
// Returns:  TRUE(1)  - success
//           FALSE(0) - failure
//
SMALLINT WriteCOM(int portnum, int outlen, uchar * outbuf)
{
    uint16_t i;

    for (i = 0; i < outlen; i++)
    {
        // Wait for the peripherial to be available
        while (!EUSCI_A_UART_getInterruptStatus(EUSCI_A0_BASE,
                                                EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG))
        {
            ;                                                                                                //while(!(UCA1IFG&UCTXIFG));
        }
        // Stuff byte into the tx reg
        EUSCI_A_UART_transmitData(EUSCI_A0_BASE, outbuf[i]);       //UCA1TXBUF = (unsigned char) _ptr[i];
    }

    return 1;
}

//--------------------------------------------------------------------------
// Read an array of bytes to the COM port, verify that it was
// sent out.  Assume that baud rate has been set.
//
// 'portnum'  - number 0 to MAX_PORTNUM-1.  This number was provided to
//               OpenCOM to indicate the port number.
// 'inlen'     - number of bytes to read from COM port
// 'inbuf'     - pointer to a buffer to hold the incomming bytes
//
// Returns: number of characters read
//
int ReadCOM(int portnum, int inlen, uchar * inbuf)
{
    uint16_t timeout = 65535;
    int      retval  = 0;

    while (data_msg_size() < inlen && 0 < timeout)
    {
        volatile uint16_t i = 65535;

        for (; i > 0; i--)
        {
            ;
        }
        timeout--;
    }

    if (0 < timeout)
    {
        read_data_msg(inbuf, inlen);
        retval = inlen;
    }

    return (retval);

//    while (g.rx_index < inlen)
//    {
//        ;
//    }
//
//
//    uint16_t i;
//
//    for (i = 0; i < inlen; i++)
//    {
//        inbuf[i] = g.rx_data[i];
//    }
//    g.rx_index = 0;
//    return i;
}



//--------------------------------------------------------------------------
// Send a break on the com port for at least 2 ms
//
// 'portnum'  - number 0 to MAX_PORTNUM-1.  This number was provided to
//               OpenCOM to indicate the port number.
//
void BreakCOM(int portnum)
{
    EUSCI_A_UART_transmitBreak(EUSCI_A0_BASE);
}

//--------------------------------------------------------------------------
// Set the baud rate on the com port.
//
// 'portnum'   - number 0 to MAX_PORTNUM-1.  This number was provided to
//               OpenCOM to indicate the port number.
// 'new_baud'  - new baud rate defined as
//                PARMSET_9600     0x00
//                PARMSET_19200    0x02
//                PARMSET_57600    0x04
//                PARMSET_115200   0x06
//
void SetBaudCOM(int portnum, int new_baud)
{
    // add platform specific code here
}

//--------------------------------------------------------------------------
//  Description:
//     Delay for at least 'len' ms
//
void msDelay(int len)
{
    int i = len;

    for (; i > 0; i--)
    {
        int j = 65535;

        for (; j > 0; j--)
        {

        }
    }
    // add platform specific code here
}

//--------------------------------------------------------------------------
// Get the current millisecond tick count.  Does not have to represent
// an actual time, it just needs to be an incrementing timer.
//
long msGettick(void)
{
    static long tick = 0;
    return ++tick;
}

//--------------------------------------------------------------------------
// This procedure indicates wether the adapter can deliver power.
//
// 'portnum'  - number 0 to MAX_PORTNUM-1.  This number was provided to
//              OpenCOM to indicate the port number.
//
// Returns:  TRUE  if adapter is capable of delivering power.
//
#if 0
SMALLINT owHasPowerDelivery(int portnum)
{
    // add adapter specific code here
    return TRUE;
}
#endif
//--------------------------------------------------------------------------
// This procedure indicates wether the adapter can deliver power.
//
// 'portnum'  - number 0 to MAX_PORTNUM-1.  This number was provided to
//              OpenCOM to indicate the port number.
//
// Returns:  TRUE  if adapter is capable of over drive.
//
#if 0
SMALLINT owHasOverDrive(int portnum)
{
    // add adapter specific code here
    return TRUE;
}
#endif
//--------------------------------------------------------------------------
// This procedure creates a fixed 480 microseconds 12 volt pulse
// on the 1-Wire Net for programming EPROM iButtons.
//
// 'portnum'  - number 0 to MAX_PORTNUM-1.  This number was provided to
//              OpenCOM to indicate the port number.
//
// Returns:  TRUE  program volatage available
//           FALSE program voltage not available
#if 0
SMALLINT owHasProgramPulse(int portnum)
{
    // add adapter specific code here
    return TRUE;
}
#endif
//--------------------------------------------------------------------------
// Send 8 bits of communication to the 1-Wire Net and verify that the
// 8 bits read from the 1-Wire Net is the same (write operation).
// The parameter 'sendbyte' least significant 8 bits are used.  After the
// 8 bits are sent change the level of the 1-Wire net.
//
// 'portnum'  - number 0 to MAX_PORTNUM-1.  This number was provided to
//              OpenCOM to indicate the port number.
// 'sendbyte' - 8 bits to send (least significant byte)
//
// Returns:  TRUE: bytes written and echo was the same
//           FALSE: echo was not the same
//
#if 0
SMALLINT owWriteBytePower(int portnum, SMALLINT sendbyte)
{
    // replace if platform has better implementation (faster response)
    if (!hasPowerDelivery(portnum))
    {
        return FALSE;
    }

    if (owTouchByte(portnum, sendbyte) != sendbyte)
    {
        return FALSE;
    }

    if (owLevel(portnum, MODE_STRONG5) != MODE_STRONG5)
    {
        return FALSE;
    }

    return TRUE;
}
#endif

//--------------------------------------------------------------------------
// Send 1 bit of communication to the 1-Wire Net and verify that the
// response matches the 'applyPowerResponse' bit and apply power delivery
// to the 1-Wire net.  Note that some implementations may apply the power
// first and then turn it off if the response is incorrect.
//
// 'portnum'  - number 0 to MAX_PORTNUM-1.  This number was provided to
//              OpenCOM to indicate the port number.
// 'applyPowerResponse' - 1 bit response to check, if correct then start
//                        power delivery
//
// Returns:  TRUE: bit written and response correct, strong pullup now on
//           FALSE: response incorrect
//
#if 0
SMALLINT owReadBitPower(int portnum, SMALLINT applyPowerResponse)
{
    // replace if platform has better implementation (faster response)
    if (!hasPowerDelivery(portnum))
    {
        return FALSE;
    }

    if (owTouchBit(portnum, 0x01) != applyPowerResponse)
    {
        return FALSE;
    }

    if (owLevel(portnum, MODE_STRONG5) != MODE_STRONG5)
    {
        return FALSE;
    }

    return TRUE;
}
#endif
