/**
 * @file drv_ow.c
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2016 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 TI 4.4.5
 * $Id$
 */

#include "drv_ow.h"
// Application header files
#include "util_log.h"
// Internal library header files
#include "bsp_pins.h"
#include "bsp_pins_conf.h"
#include "ow/ownet.h"
#include "ow/mbnv.h"
// Third-party library header files
#include <driverlib.h>
// Standard library header files
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

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



static const size_t       MAX_ID_COUNT    = 16;
static const size_t       MAX_EEPROM_READ = 20;
static const char * const M906_NAME       = "M906 #";

static struct
{
    size_t count;
    /// the assigned device serial number that is in the eeprom
    uint8_t       M906_dev_num;
    one_wire_id_t device_sn[MAX_ID_COUNT];
    char          device_contents[MAX_ID_COUNT][MAX_EEPROM_READ];
} g;

// *****************************************************************************
// Private static function and ISR prototypes
// *****************************************************************************


static void drv_ow_init (void);

static size_t abs_1_wire_find_devices (one_wire_id_t FamilySN[],
                                       const size_t max_device_count);

// *****************************************************************************
// Private inline function definitions
// *****************************************************************************

// *****************************************************************************
// Public function bodies
// *****************************************************************************

void convert_id_to_string(char * buff, one_wire_id_t id)
{

    uint8_t b;

    for (b = 0; b < 8; b++)
    {
        // 1 byte yields 2 hex digits, plus a NULL terminator
        char hex_byte[3];
        // Write the byte as a hex digit
        //lint -e{534} Return value is not needed
        sprintf(hex_byte, "%02X", id[b]);
        strncat(buff, hex_byte, 2);
    }
}

static void drv_ow_init(void)
{

    g.count = abs_1_wire_find_devices(&g.device_sn, MAX_ID_COUNT);
    uint8_t i;

    // set it out of bounds
    g.M906_dev_num = 99;

    for (i = 0; i < g.count; i++)
    {
        //       bsp_pin_digital_write(&pins.uart_1w_sd_sel, HIGH);

        readNV(0, 0, g.device_sn[i], 0, 0, &g.device_contents[i], 1);

        const uint8_t record_sz = g.device_contents[i][0] >
                                  MAX_EEPROM_READ ? MAX_EEPROM_READ : g.
                                  device_contents[i][0];

        readNV(0, 0, g.device_sn[i], 1, 0, &g.device_contents[i], record_sz);

        if (0 == strncmp(&g.device_contents[i], M906_NAME, strlen(M906_NAME)))
        {
            char ser_buff[3];
            strncpy(ser_buff, &g.device_contents[i][strlen(M906_NAME)], 2);
            sscanf(ser_buff, "%" SCNu8, &g.M906_dev_num);
        }

        g.device_contents[i][record_sz] = 0;                 //null terminate it

        //   bsp_pin_digital_write(&pins.uart_1w_sd_sel, LOW);

    }
}

uint8_t drv_ow_get_dev_cnt(void)
{
    return g.count;
}

bool drv_ow_get_id( one_wire_id_t * id, uint8_t dev)
{
    bool retval = false;

    if (g.count >= dev)
    {
        memcpy(id, g.device_sn[dev], 8);
        retval = true;
    }
    return (retval);
}
bool drv_ow_get_contents(char * buff, uint8_t buff_sz, uint8_t dev)
{
    bool retval = false;

    if (g.count >= dev)
    {
        strncpy(buff, g.device_contents[dev], MAX_EEPROM_READ);
        retval = true;
    }
    return (retval);
}
uint8_t drv_ow_get_m906_sn(void)
{
    return g.M906_dev_num;
}

void report_1_wire_devices(void)
{
    drv_ow_init();

    logf(TRACE, "%u 1-wire device(s) found", g.count);
    uint8_t i;

    for (i = 0; i < g.count; i++)
    {
        // 8 bytes yields 16 hex digits, plus a NULL terminator
        char hex_id[17] = "";
        convert_id_to_string(hex_id, g.device_sn[i]);

        logf(TRACE, "1-wire device %u: %s : %s", i, hex_id,
             g.device_contents[i] );
    }
    logf(TRACE, "M906 SN: %02d", g.M906_dev_num);

    // bsp_pin_digital_write(&pins.uart_1w_sd_sel, LOW);
}



// *****************************************************************************
// Private function bodies
// *****************************************************************************


static size_t abs_1_wire_find_devices(one_wire_id_t FamilySN[],
                                      const size_t max_device_count)
{
    int portnum    = owAcquire(0, "");
    int NumDevices = 0;

    do
    {
        // perform the search
        if (!owNext(portnum, TRUE, FALSE))
        {
            break;
        }

        owSerialNum(portnum, FamilySN[NumDevices], TRUE);
        NumDevices++;
    }
    while (NumDevices < (max_device_count - 1));
    return NumDevices;

}
// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************
