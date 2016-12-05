/**
 * @file main.c
 * @brief Contains the entry point for the software.
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2016 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 TI 4.4.5
 * $Id$
 */

#include "main.h"
// Application header files
#include "bsp_pins.h"
#include "bsp_pins_conf.h"
#include "bsp_pins_types.h"
#include "drv_logger.h"
#include "drv_ow.h"
#include "util_log.h"
#include "drv_ds3234.h"
#include "bsp_uart.h"
#include "do_stuff.h"
#include "bsp_card.h"
#include "bsp_latches.h"
// Internal library header files
#include "ow/ownet.h"
#include "ow/mbnv.h"
// Third-party library header files
#include <msp430.h>
#include <driverlib.h>
// Standard library header files
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
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

typedef enum
{
    COMM_NOT_INIT,
    SD_NOT_INIT,
    IN_DATA_MODE,
    IN_CMD_MODE,
    STATUS_NO_STATUS
}openlogger_status_t;
// *****************************************************************************
// Private static function and ISR prototypes
// *****************************************************************************

bool openlogger_got_to_cmd_mode (void);
void write_meta_data_file (rtc_t current_time);
bool openlogger_append (char * const file, char * const extension);
bool openlogger_cd (char * const folder);
bool openlogger_md (char * const folder);
openlogger_status_t openlogger_get_startup_msg (void);
// *****************************************************************************
// Private inline function definitions
// *****************************************************************************


/*
 * Clock System Initialization
 */

void Init_Clock()
{
    // Set P4.1 and P4.2 as Secondary Module Function Input, LFXT.
    /* no lfx
	GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_PJ,
        GPIO_PIN4 + GPIO_PIN5,
        GPIO_PRIMARY_MODULE_FUNCTION
        );
    */

    // Set DCO frequency to default 8MHz
    CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_6);

    // Configure MCLK and SMCLK to 8MHz
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    //CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
    //CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

    // Intializes the XT1 crystal oscillator
     CS_turnOnLFXT(CS_LFXT_DRIVE_3);
}

// *****************************************************************************
// Public function bodies
// *****************************************************************************


/*
void check_for_trace_msg(void)
{
    // Check if a msg was recieved on the trace port.
    uint8_t got_msg = trace_msg_recieved();

    // If a message came in handle it.
    if (0 != got_msg)
    {
        uint8_t tmp_buf[100];
        read_trace_msg(tmp_buf, 100);
        logf(TRACE, "string rx: %s", tmp_buf);

        // 't' is used to set the time, format t y mo d h mi s \r\n
        if ('t' == tmp_buf[0])
        {
            rtc_t set_time;
            sscanf(
                tmp_buf,
                "%*s %" SCNu8 "%" SCNu8 "%" SCNu8 "%" SCNu8 "%" SCNu8 "%"
                SCNu8,
                &set_time.year, &set_time.month, &set_time.day,
                &set_time.hour,
                &set_time.minute, &set_time.second );
            drv_rtc_set_time_date(&set_time);
        }
    }
}
*/
void sw_delay(uint32_t num)
{
    for (; num > 0; num--)
    {
        volatile uint16_t i = 50000;                                     // SW Delay

        do
        {
            i--;
        }
        while (i != 0);
    }


}

/*
void openlogger_start(void)
{
    bsp_pin_digital_write(&pins.uart_1w_sd_sel, LOW);
    bsp_pin_digital_write(&pins.sd_pwr_en, ENABLED);
    bsp_pin_digital_write(&pins.logger_rst, DISABLED);
}
*/
/*
void openlogger_stop(void)
{
    // will close out the current file
    openlogger_got_to_cmd_mode();
    sw_delay(10);
    // Shutting down the sd card.
    bsp_pin_digital_write(&pins.logger_rst, ENABLED);
    bsp_pin_digital_write(&pins.sd_pwr_en, DISABLED);
    bsp_pin_digital_write(&pins.uart_1w_sd_sel, HIGH);
}
*/
/*
openlogger_status_t openlogger_get_startup_msg(void)
{
    const uint8_t rx_buff_sz = 40;
    char          rx_buff[rx_buff_sz];
    read_data_msg(rx_buff, rx_buff_sz);
    char                next_char = rx_buff[0];
    openlogger_status_t retval    = STATUS_NO_STATUS;

    if ('1' == next_char && retval == STATUS_NO_STATUS)
    {
        log(TRACE, "Logger comm established.");
        next_char = rx_buff[1];
    }
    else
    {
        retval = COMM_NOT_INIT;
        log(ERROR, "Logger comm not established.");
    }

    if ('2' == next_char && retval == STATUS_NO_STATUS)
    {
        log(TRACE, "Logger card initalized.");
        next_char = rx_buff[2];
    }
    else
    {
        retval = SD_NOT_INIT;
        log(ERROR, "Logger card not initalized.");
    }

    if ('<' == next_char && retval == STATUS_NO_STATUS)
    {
        retval = IN_DATA_MODE;
        log(TRACE, "Logger in data mode.");

        if (openlogger_got_to_cmd_mode())
        {
            retval = IN_CMD_MODE;
        }
    }
    else if ('>' == next_char && retval == STATUS_NO_STATUS)
    {
        retval = IN_CMD_MODE;
        log(TRACE, "Logger in command mode.");
    }
    return (retval);
}
*/
/*
bool openlogger_md(char * const folder)
{

    bool          retval     = true;
    const uint8_t command_sz = 14;
    char          command[command_sz];

    snprintf(command, command_sz, "md %s\r", folder);
    logf(TRACE, "Making directory %s.", folder);
    cout_data_channel(command);

    sw_delay(10);

    while (0 == data_msg_size())
    {
        ;
    }
    const uint8_t rx_buff_sz = 40;
    char          rx_buff[rx_buff_sz];
    read_data_msg(rx_buff, rx_buff_sz );

    strcat(command, "\r\n>");

    if (0 != strcmp(rx_buff, command))
    {
        logf(ERROR, "** Command rejected: tx: %s rx: %s. **",
             command,
             rx_buff);
        retval = false;
    }
    return (retval);

}
*/
/*
bool openlogger_cd(char * const folder)
{
    bool          retval     = true;
    const uint8_t command_sz = 14;
    char          command[command_sz];

    snprintf(command, command_sz, "cd %s\r", folder);
    logf(TRACE, "Changing to directory %s.", folder);
    cout_data_channel(command);

    sw_delay(10);

    while (0 == data_msg_size())
    {
        ;
    }
    const uint8_t rx_buff_sz = 40;
    char          rx_buff[rx_buff_sz];
    read_data_msg(rx_buff, rx_buff_sz );

    strcat(command, "\r\n>");

    if (0 != strcmp(rx_buff, command))
    {
        logf(ERROR, "** Command rejected: tx: %s rx: %s. **",
             command,
             rx_buff);
        retval = false;
    }
    return (retval);

}
*/
/*
bool openlogger_append(char * const file, char * const extension)
{
    bool          retval     = true;
    const uint8_t command_sz = 21;
    char          command[command_sz];

    snprintf(command, command_sz, "append %s%s\r", file, extension);
    logf(TRACE, "Creating file %s%s.", file, extension);
    cout_data_channel(command);

    sw_delay(10);

    while (0 == data_msg_size())
    {
        ;
    }
    const uint8_t rx_buff_sz = 40;
    char          rx_buff[rx_buff_sz];
    read_data_msg(rx_buff, rx_buff_sz );

    strcat(command, "\r\n<");

    if (0 != strcmp(rx_buff, command))
    {
        logf(ERROR, "** Command rejected: tx: %s rx: %s. **",
             command,
             rx_buff);
        retval = false;
    }
    return (retval);

}
*/
/*
void write_meta_data_file(rtc_t current_time)
{
    const uint8_t comm_buff_sz = 130;
    char          comm_buff[comm_buff_sz];
    const uint8_t rx_buff_sz = 40;
    char          rx_buff[rx_buff_sz];


// print creation date
    snprintf(
        comm_buff, comm_buff_sz,
        "File Created y:m:d h:m:s UTC 20%02d:%02d:%02d %02d:%02d:%02d\r\n",
        current_time.year, current_time.month,
        current_time.day, current_time.hour,
        current_time.minute,
        current_time.second);
    cout_data_channel(comm_buff);
// print number of devices
    snprintf(comm_buff, comm_buff_sz,
             "Found %d connected devices.\r\n",
             drv_ow_get_dev_cnt());
    cout_data_channel(comm_buff);

    uint8_t i;

// print device info
    for (i = 0; i < drv_ow_get_dev_cnt(); i++)
    {
        // 8 bytes yields 16 hex digits, plus a NULL terminator
        char          hex_id[17] = "";
        one_wire_id_t id;
        drv_ow_get_id(id, i);
        convert_id_to_string(hex_id, id);

        snprintf(comm_buff, comm_buff_sz,
                 "Device %d: SN# %s : ", i,
                 hex_id);
        cout_data_channel(comm_buff);
        drv_ow_get_contents(comm_buff, comm_buff_sz, i);
        cout_data_channel(comm_buff);
        snprintf(comm_buff, comm_buff_sz, "\r\n");
        cout_data_channel(comm_buff);

    }
}
*/
/*
bool openlogger_got_to_cmd_mode(void)
{
    bool          retval     = true;
    const uint8_t command_sz = 4;
    char          command[command_sz];


    log(TRACE, "Switching to command mode.");

    snprintf(command, command_sz, "%c%c%c", 26, 26, 26);
    cout_data_channel(command);
    sw_delay(10);

    uint16_t timeout = 0;

    while (0 == data_msg_size() && timeout != sizeof(uint16_t))
    {
        timeout++;
    }
    const uint8_t rx_buff_sz = 40;
    char          rx_buff[rx_buff_sz];

    read_data_msg(rx_buff, rx_buff_sz );

    if (rx_buff[0] == '~' && rx_buff[1] == '>')
    {
        retval = true;
        log(TRACE, "Now in command mode.");
    }
    return (retval);
}
*/

int main(void)
{
    WDTCTL   = WDTPW | WDTHOLD;             // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

    __enable_interrupt();

    Init_Clock();
    logger_init();
    bsp_pins_initalize();

    for(;;)
    {
    	card_t card = CARD_1;
    	for (;card < CARD_10;card++)
    	{
    		bsp_set_valve(card,ENABLED);
    		sw_delay(1000);
    		bsp_set_valve(card,DISABLED);
    	}

    }

  /*  drv_rtc_init();

    bsp_pin_digital_write(&pins.led_power_en, ENABLED);

    for (;;)
    {
        static uint8_t running = 2;

        if (pins.power_down.enabled_state ==
            bsp_pin_digital_read(&pins.power_down))
        {
            if (0 != running)
            {
                do_stuff_shutdown();

                openlogger_stop();
                // Indicate that we are all shut down now.
                running = 0;
                // Turn off all lights but #4
                bsp_pin_digital_write(&pins.led_1, DISABLED);
                bsp_pin_digital_write(&pins.led_2, DISABLED);
                bsp_pin_digital_write(&pins.led_3, DISABLED);
                bsp_pin_digital_write(&pins.led_4, ENABLED);
            }
        }
        else
        {
            if (1 != running)
            {
                report_1_wire_devices();

                openlogger_start();

                bsp_pin_digital_write(&pins.led_1, ENABLED);
                bsp_pin_digital_write(&pins.led_2, DISABLED);
                bsp_pin_digital_write(&pins.led_3, DISABLED);
                bsp_pin_digital_write(&pins.led_4, DISABLED);

                sw_delay(10);

                openlogger_status_t startup_mode = openlogger_get_startup_msg();

                if (startup_mode == SD_NOT_INIT)
                {
                    // turn on the third led to indicate a problem.
                    bsp_pin_digital_write(&pins.led_3, ENABLED);
                }

                if (startup_mode == IN_CMD_MODE)
                {


                    //bsp_pin_digital_write(&pins.led_2, ENABLED);


                    rtc_t         current_time = drv_rtc_read_time_date();
                    const uint8_t name_sz      = 9;
                    char          folder_name[name_sz];
                    char          file_name[name_sz];
                    snprintf(folder_name, name_sz, "20%02d%02d%02d",
                             current_time.year, current_time.month,
                             current_time.day);
                    //make sure that the sn is only 2 digits  if it is more then the file won't get made.
                    uint8_t m906_sn = drv_ow_get_m906_sn();
                    m906_sn = (m906_sn > 99) ? 99 : m906_sn;
                    snprintf(file_name, name_sz, "%02d%02d%02d%02d",
                             m906_sn, current_time.hour, current_time.minute,
                             current_time.second);

                    bool success = true;


                    success = openlogger_cd(folder_name);

                    if (!success)
                    {
                        success = openlogger_md(folder_name);

                        success = openlogger_cd(folder_name);
                    }

                    if (success)
                    {
                        success = openlogger_append(file_name, ".txt");
                    }

                    if (success)
                    {
                        write_meta_data_file( current_time);
                    }

                    if (success)
                    {
                        success = openlogger_got_to_cmd_mode();
                    }

                    if (success)
                    {
                        success = openlogger_append(file_name, ".csv");

                        do_stuff_init();
                    }

                    if (success)
                    {
                        // Turn on led 2 to inicate that everything is okay.
                        bsp_pin_digital_write(&pins.led_2, ENABLED);
                    }
                    else // Turn on the third led to indicate a problem.
                    {
                        bsp_pin_digital_write(&pins.led_3, ENABLED);
                        log(ERROR, "File system could not initalize")
                    }
                }
                running = 1;
            }

            if (1 == running)
            {
                const uint8_t comm_buff_sz = 130;
                char          comm_buff[comm_buff_sz];

                do_stuff();


                // Blink to konw we are running
                bsp_pin_digital_toggle(&pins.led_1);

                // Check if any messages came in on the trace port.
                check_for_trace_msg();

                sw_delay(3);
            }

        }
    }
*/
    return 0;
}

// *****************************************************************************
// Private function bodies
// *****************************************************************************

// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************
