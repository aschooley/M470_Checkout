/**
 * @file drv_ds3234.c
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2016 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 TI 4.4.5
 * $Id$
 */

#include "drv_ds3234.h"
// Application header files
#include "bsp_pins.h"
#include "bsp_pins_conf.h"
// Internal library header files
// Third-party library header files
#include <driverlib.h>
// Standard library header files
#include <stdint.h>
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

static const uint8_t BCD_ARRAY_SIZE = 7;

// *****************************************************************************
// Private static data definitions
// *****************************************************************************

// *****************************************************************************
// Private static function and ISR prototypes
// *****************************************************************************

/**
 * Unpack a rtc struct into a BCD encoded array.
 * @param[in] structure to convert.
 * @param[out] array to put the values into.
 * @retval[true] array size was large enough, conversion done.
 * @retfal[false] array size was not sufficient, conversion aborted.
 */
bool drv_rtc_convert_struct_to_array (rtc_t * structure, uint8_t * bcd_array,
                                      uint8_t array_sz);

/**
 * Unpack a BCD encoded array into a rtc struct.
 * @param[in] array to convert.
 * @param[out] structure to put the converted values into.
 */
void drv_rtc_convert_array_to_struct (uint8_t * bcd_array, rtc_t * structure);

// *****************************************************************************
// Private inline function definitions
// *****************************************************************************

// *****************************************************************************
// Public function bodies
// *****************************************************************************

void drv_rtc_init(void)
{

    // Structure that holds all the SPI config info
    EUSCI_B_SPI_initMasterParam spi_b0_param =
    {
        EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
        8000000,
        8000000,
        EUSCI_B_SPI_MSB_FIRST,
        EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW,
        EUSCI_B_SPI_3PIN
    };
    // Initalize and enable the SPI port.
    EUSCI_B_SPI_initMaster(EUSCI_B0_BASE, &spi_b0_param);
    EUSCI_B_SPI_enable(EUSCI_B0_BASE);

    // Enable the RTC chip's chip select.
  //  bsp_pin_digital_write(&pins.rtc_cs, ENABLED);

    // Wait for the SPI port to be available.
    while (EUSCI_B_SPI_isBusy(EUSCI_B0_BASE))
    {
        ;
    }
    // Send address to configure.
    EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, 0x8E);

    // Wait for the SPI port to be available.
    while (EUSCI_B_SPI_isBusy(EUSCI_B0_BASE))
    {
        ;
    }
    // Config device to disable Osciallator and Battery SQ wave @1hz, temp
    // compensation, Alarms disabled.
    EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, 0x60);

    // Deselect the RTC chip.
  //  bsp_pin_digital_write(&pins.rtc_cs, DISABLED);

    //delay(10);
}

void drv_rtc_set_time_date(rtc_t * set_time)
{
    uint8_t set_time_array[BCD_ARRAY_SIZE];
    drv_rtc_convert_struct_to_array(set_time, set_time_array, BCD_ARRAY_SIZE);

    // Select the RTC chip on the SPI bus.
  //  bsp_pin_digital_write(&pins.rtc_cs, ENABLED);

    // When the SPI port is available, set the address to write to.
    while (EUSCI_B_SPI_isBusy(EUSCI_B0_BASE))
    {
        ;
    }
    EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, 0x80);

    uint8_t i;

    for ( i = 0; i < BCD_ARRAY_SIZE; i++)
    {
        // When the SPI port is available, write the data.
        while (EUSCI_B_SPI_isBusy(EUSCI_B0_BASE))
        {
            ;
        }
        EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, set_time_array[i]);
    }

    // Deselect the RTC chip.
 //   bsp_pin_digital_write(&pins.rtc_cs, DISABLED);
}

rtc_t drv_rtc_read_time_date(void)
{

    // Create an array to hold the RTC data when read in from the chip.
    uint8_t TimeDate[7];      //second,minute,hour,null,day,month,year

    // Enable the RTC chip on the SPI bus.
  //  bsp_pin_digital_write(&pins.rtc_cs, ENABLED);

    // When the SPI port is available, select the starting address to read.
    while (EUSCI_B_SPI_isBusy(EUSCI_B0_BASE))
    {
        ;
    }
    EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, 0x00);

    // Create an iterator.
    uint8_t i;

    // Loop through the RTC registers and read out the date and time.
    for ( i = 0; i <= 6; i++)
    {
        // When the SPI port is available, shift out don't care bits to shift
        // in the register we want to read.
        while (EUSCI_B_SPI_isBusy(EUSCI_B0_BASE))
        {
            ;
        }
        EUSCI_B_SPI_transmitData(EUSCI_B0_BASE, 0x00);

        // Once the transaction is complete retrieve the value shifted in.
        while (EUSCI_B_SPI_isBusy(EUSCI_B0_BASE))
        {
            ;
        }
        TimeDate[i] = EUSCI_B_SPI_receiveData(EUSCI_B0_BASE);
    }
    // Deselect the RTC chip.
 //   bsp_pin_digital_write(&pins.rtc_cs, DISABLED);

    // Create a RTC struct and stuff it with the converted bytes from the array.
    rtc_t current_time;
    drv_rtc_convert_array_to_struct(TimeDate, &current_time);

    // Return rtc struct
    return (current_time);
}

bool drv_rtc_convert_struct_to_array(rtc_t * structure, uint8_t * bcd_array,
                                     uint8_t array_sz)
{
    bool retval = false;

    if (BCD_ARRAY_SIZE <= array_sz)
    {
        // Create an iterator.
        uint8_t i;

        // Loop through the Array and send them to the RTC chip.
        for (i = 0; i <= 6; i++)
        {
            switch (i)
            {
                case 0:
                    bcd_array[i] = structure->second;
                    break;

                case 1:
                    bcd_array[i] = structure->minute;
                    break;

                case 2:
                    bcd_array[i] = structure->hour;
                    break;

                case 3:
                    bcd_array[i] = 0;
                    break;

                case 4:
                    bcd_array[i] = structure->day;
                    break;

                case 5:
                    bcd_array[i] = structure->month;
                    break;

                case 6:
                    bcd_array[i] = structure->year;
                    break;

                default:
                    break;
            }
            // Convert the number to a BCD.
            uint8_t tens = bcd_array[i] / 10;
            uint8_t ones = bcd_array[i] - tens * 10;

            // If we are setting the hour this loop, handle 24 hours properly.
            if (i == 2)
            {
                if (tens == 2)
                {
                    tens = 0b00000010;
                }
                else if (tens == 1)
                {
                    tens = 0b00000001;
                }
            }
            // Write back the BCD value over the unit8.
            bcd_array[i] = ones + (tens << 4);
        }         // end for loop
        retval = true;
    }
    return (retval);
}

void drv_rtc_convert_array_to_struct(uint8_t * bcd_array, rtc_t * structure)
{
    uint8_t i;

    for ( i = 0; i <= 6; i++)
    {
        // Skip the day of the week register, we don't use it.
        if (i == 3)
        {
            i++;
        }
        // Lets decode the BCD encoded byte we got from the RTC chip.
        // Extract the 10^0 position.
        uint8_t ones = bcd_array[i] & 0b00001111;

        // If this is the time byte.
        if (i == 2)
        {
            // Handle 24 hour mode.
            uint8_t tens = (bcd_array[i] & 0b00110000) >> 4;

            if (tens == 0b00000010)
            {
                tens = 20;
            }
            else if (tens == 0b00000001)
            {
                tens = 10;
            }
            bcd_array[i] = ones + tens;
        }
        // Handle the day.
        else if (i == 4)
        {
            uint8_t tens = (bcd_array[i] & 0b00110000) >> 4;
            bcd_array[i] = ones + tens * 10;
        }
        // Handle the month.
        else if (i == 5)
        {
            uint8_t tens = (bcd_array[i] & 0b00010000) >> 4;
            bcd_array[i] = ones + tens * 10;
        }
        // Handle the year.
        else if (i == 6)
        {
            uint8_t tens = (bcd_array[i] & 0b11110000) >> 4;
            bcd_array[i] = ones + tens * 10;
        }
        // Handle minutes and seconds.
        else
        {
            uint8_t tens = (bcd_array[i] & 0b01110000) >> 4;
            bcd_array[i] = ones + tens * 10;
        }
    }
    structure->second = bcd_array[0];
    structure->minute = bcd_array[1];
    structure->hour   = bcd_array[2];
    structure->day    = bcd_array[4];
    structure->month  = bcd_array[5];
    structure->year   = bcd_array[6];

}

// *****************************************************************************
// Private function bodies
// *****************************************************************************

// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************
