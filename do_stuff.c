/**
 * @file do_stuff.c
 * @brief
 * @details
 * @copyright COPYRIGHT NOTICE: (c) 2016 NASA Ames Research Center
 * @note ROM: BioSentinel Bio Payload
 * @note Processor: MSP430FR6989
 * @note Compiler: MSP-430 TI 4.4.5
 * $Id$
 */

#include "do_stuff.h"
// Application header files
#include "taos_mode.h"
#include "bsp_uart.h"
#include "util_log.h"
#include "drv_ds3234.h"
#include "bsp_pins.h"
#include "bsp_pins_conf.h"
// Internal library header files
// Third-party library header files
// Standard library header files
#include <driverlib.h>
#include "taos_mode.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"

// *****************************************************************************
// Private macro definitions
// *****************************************************************************

#define DEFAULT_MODE        0
#define SPRINTF_BUFFER_SIZE  255
static const unsigned char SAMPLE_PERIOD_MINUTES = 2;

// *****************************************************************************
// Private data type definitions (enum, struct, typedef, union)
// *****************************************************************************

typedef struct
{
    bool         debounce_b1;
    bool         debounce_b2;
    unsigned int b1_and_b2_holdCount;
}debounce_t;

typedef struct
{
    unsigned int  overflow;
    unsigned char freq_array_index;
    unsigned int  freq_array[20];
}timer_t;

// *****************************************************************************
// Private static constant definitions
// *****************************************************************************

// *****************************************************************************
// Private static data definitions
// *****************************************************************************

static struct
{
    volatile bool          running;
    volatile unsigned char mode;
    volatile debounce_t    buttons;
    volatile timer_t       timer;
    volatile bool          update_display;
    volatile uint32_t      minute_counter;
    volatile bool          abort;
    volatile unsigned int  zero_hz_timeout;
    volatile bool          sample_wells;
    volatile unsigned char lucky_dark_well;
} g =
{true, DEFAULT_MODE,
 {false, false, 0}, {0, false, {}}, false, 0, false, false, 0};


char sprintf_buffer[SPRINTF_BUFFER_SIZE];

// TimerA0 UpMode Configuration Parameter
Timer_A_initUpModeParam initUpParam_A0 =
{
    TIMER_A_CLOCKSOURCE_SMCLK,                  // SMCLK Clock Source
    TIMER_A_CLOCKSOURCE_DIVIDER_1,              // SMCLK/4 = 2MHz
    30000,                                      // 15ms debounce period
    TIMER_A_TAIE_INTERRUPT_DISABLE,             // Disable Timer interrupt
    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,                 // Enable CCR0 interrupt
    TIMER_A_DO_CLEAR,                           // Clear value
    true                                        // Start Timer
};


// TimerA1 UpMode Configuration Parameter
Timer_A_initContinuousModeParam initContinuousParam_A1 =
{
    TIMER_A_CLOCKSOURCE_SMCLK,
    TIMER_A_CLOCKSOURCE_DIVIDER_1,
    TIMER_A_TAIE_INTERRUPT_ENABLE,
    TIMER_A_SKIP_CLEAR,
    false
};
Timer_A_initCaptureModeParam initCaptureParam_A1_2 =
{
    TIMER_A_CAPTURECOMPARE_REGISTER_2,
    TIMER_A_CAPTUREMODE_RISING_EDGE,
    TIMER_A_CAPTURE_INPUTSELECT_CCIxA,
    TIMER_A_CAPTURE_SYNCHRONOUS,
    TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,
    TIMER_A_OUTPUTMODE_OUTBITVALUE
};

Timer_A_initContinuousModeParam initContinuousParam_A2 =
{
    TIMER_A_CLOCKSOURCE_SMCLK,
    TIMER_A_CLOCKSOURCE_DIVIDER_64,
    TIMER_A_TAIE_INTERRUPT_ENABLE,
    TIMER_A_SKIP_CLEAR,
    true
};

// *****************************************************************************
// Private static function and ISR prototypes
// *****************************************************************************

void Init_Timer (void);

//just a stub
void print_to_lcd (char string[]);

void reset_rtc_timer (void);

void init_rtc (void);

void do_good_stuff (unsigned char well);

// *****************************************************************************
// Private inline function definitions
// *****************************************************************************

// *****************************************************************************
// Public function bodies
// *****************************************************************************

void do_stuff_init(void)
{

    Init_Timer();
    init_rtc();
    taos_mode_init();

    // print out the column headers



    log(TRACE, "printing headers");

    sprintf(sprintf_buffer, "Year,Month,Day,Hour,Minute,Second");
    cout_data_channel(sprintf_buffer);
    unsigned char i;

    for (i = 1; i <= taos_max_well_number; i++)
    {
        if (i % 4)
        {
            sprintf(sprintf_buffer, ",%s", taos_translate_well_index(i - 1));
            cout_data_channel(sprintf_buffer);
        }

    }

    for (i = 1; i <= taos_max_well_number; i++)
    {
        if (i % 4)
        {
        }
        else
        {
            sprintf(sprintf_buffer, ",%s", taos_translate_well_index(i - 1));
            cout_data_channel(sprintf_buffer);
        }
    }
    sprintf(sprintf_buffer, "\r\n");
    cout_data_channel(sprintf_buffer);

    g.sample_wells    = true;
    g.lucky_dark_well = 0;


}
void do_stuff_shutdown(void)
{

    RTC_C_holdClock(RTC_C_BASE);
    g.minute_counter = 0;

}
void do_stuff(void)
{

    char sprintf_buffer[SPRINTF_BUFFER_SIZE];

    unsigned char last_minute_counter = 0;

    if (g.minute_counter != last_minute_counter)
    {
        last_minute_counter = g.minute_counter;
    }

    if (g.running == true && g.minute_counter >= SAMPLE_PERIOD_MINUTES)
    {
        g.sample_wells   = true;
        g.minute_counter = 0;
    }

    if (true == g.sample_wells)   //if(g.update_display)
    {
        g.sample_wells = false;
 //       bsp_pin_digital_write(&pins.led_power_en, DISABLED);
 //       bsp_pin_digital_write(&pins.stack_power_en, ENABLED);


        unsigned int i;

        for (i=65535; i>0 ; i--)
        {

        }

        //Calendar run_time = RTC_C_getCalendarTime(RTC_C_BASE);

        //printf("%d,%d,%d",run_time.DayOfWeek,run_time.Hours,run_time.Minutes);

        rtc_t current_time = drv_rtc_read_time_date();
        snprintf(sprintf_buffer, SPRINTF_BUFFER_SIZE,
                 "%02d,%02d,%02d,%02d,%02d,%02d",
                 current_time.year, current_time.month,
                 current_time.day, current_time.hour, current_time.minute,
                 current_time.second);
        cout_data_channel(sprintf_buffer);


        taos_set_current_well(0);


        for (i = 1; i <= taos_max_well_number; i++)
        {
            if (i % 4)
            {
                do_good_stuff(i);
            }

        }

        for (i = 1; i <= taos_max_well_number / 4; i++)
        {
            if (i == (g.lucky_dark_well + 1))
            {
                do_good_stuff((g.lucky_dark_well + 1) * 4);
            }
            else
            {
                sprintf(sprintf_buffer, ",");
                cout_data_channel(sprintf_buffer);
            }
        }
        g.lucky_dark_well++;
        g.lucky_dark_well %= 16;

        sprintf(sprintf_buffer, "\r\n");
        cout_data_channel(sprintf_buffer);

    //    bsp_pin_digital_write(&pins.stack_power_en, DISABLED);
    //    bsp_pin_digital_write(&pins.led_power_en, ENABLED);
    }


}


// *****************************************************************************
// Private function bodies
// *****************************************************************************

void do_good_stuff(unsigned char well)
{

    taos_set_current_well(well - 1);


    Timer_A_disableInterrupt(TIMER_A1_BASE);

    DMA_initParam dma_init = {
        DMA_CHANNEL_0,
        DMA_TRANSFER_SINGLE,
        20,
        DMA_TRIGGERSOURCE_4,
        DMA_SIZE_SRCWORD_DSTWORD,
        DMA_TRIGGER_HIGH
    };

    uint32_t dst_addr = &g.timer.freq_array;
    DMA_init(&dma_init);
    DMA_setDstAddress(DMA_CHANNEL_0, dst_addr, DMA_DIRECTION_INCREMENT);
    DMA_setSrcAddress(DMA_CHANNEL_0, &TA1CCR2, DMA_DIRECTION_UNCHANGED);
    DMA_setTransferSize(DMA_CHANNEL_0, 20);
    //DMA_enableInterrupt(DMA_CHANNEL_0);
    DMA_clearInterrupt(DMA_CHANNEL_0);

    taos_output_enable();


    Init_Timer();
    Timer_A_enableInterrupt(TIMER_A1_BASE);
    Timer_A_clearTimerInterrupt(TIMER_A1_BASE);
    Timer_A_clear(TIMER_A1_BASE);
    //Timer_A_enableCaptureCompareInterrupt(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);
    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_CONTINUOUS_MODE);
    DMA_enableTransfers(DMA_CHANNEL_0);

    while (DMA_INT_INACTIVE == DMA_getInterruptStatus(DMA_CHANNEL_0) &&
           g.abort == false)                                                                                    //while(g.timer.freq_array_index<20)f
    {
    }

    taos_output_disable();
    //		taos_increment_well();
    g.abort = false;
    Timer_A_stop(TIMER_A1_BASE);
    Timer_A_disableCaptureCompareInterrupt(TIMER_A1_BASE,
                                           TIMER_A_CAPTURECOMPARE_REGISTER_2);
    Timer_A_disableInterrupt(TIMER_A1_BASE);
    Timer_A_clear(TIMER_A1_BASE);
    DMA_disableTransfers(DMA_CHANNEL_0);
    DMA_clearInterrupt(DMA_CHANNEL_0);

    //unsigned long avg = (((g.timer.overflow * 0x10000)+ g.timer.freq_array[19]) - g.timer.freq_array[3])>>4;
    unsigned long total =
        ((g.timer.overflow *
          0x10000) + g.timer.freq_array[19]) - g.timer.freq_array[3];

    if (total == 0)                         //if(0==avg)
    {
        sprintf(sprintf_buffer, ",0");
    }
    else
    {
        //sprintf(sprintf_buffer,"%f",8000000.0/(double)avg);
        sprintf(sprintf_buffer, ",%lu", total);
    }

    cout_data_channel(sprintf_buffer);
    //print_to_lcd(&sprintf_buffer);

    Timer_A_stop(TIMER_A1_BASE);
    Timer_A_disableCaptureCompareInterrupt(TIMER_A1_BASE,
                                           TIMER_A_CAPTURECOMPARE_REGISTER_2);
    g.timer.overflow         = 0;
    g.zero_hz_timeout        = 0;
    g.timer.freq_array_index = 0;
}

/*
 * Timer Initialization
 */
void Init_Timer(void)
{
    Timer_A_initCaptureMode(TIMER_A1_BASE, &initCaptureParam_A1_2);
    Timer_A_initContinuousMode(TIMER_A1_BASE, &initContinuousParam_A1);
    //Timer_A_enableCaptureCompareInterrupt(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);
    //Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_CONTINUOUS_MODE);

}
void print_to_lcd(char string[])
{

}
void reset_rtc_timer(void)
{
    volatile Calendar initial_time;

    //Setup Current Time for Calendar
    initial_time.Seconds    = 0x00;
    initial_time.Minutes    = 0x00;
    initial_time.Hours      = 0x00;
    initial_time.DayOfWeek  = 0x00;
    initial_time.DayOfMonth = 0x01;
    initial_time.Month      = 0x00;
    initial_time.Year       = 0x2015;

    RTC_C_initCalendar(RTC_C_BASE, &initial_time, RTC_C_FORMAT_BINARY);
}

void init_rtc(void)
{
    reset_rtc_timer();
    RTC_C_setCalendarEvent(RTC_C_BASE, RTC_C_CALENDAREVENT_MINUTECHANGE);
    RTC_C_enableInterrupt(RTC_C_BASE, RTC_C_TIME_EVENT_INTERRUPT);
    RTC_C_startClock(RTC_C_BASE);
}

// *****************************************************************************
// Interrupt Service Routine bodies
// *****************************************************************************

/*
 * RTC Interrupt Service Routine
 * Wakes up every ~10 milliseconds to update stowatch
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
    #pragma vector=RTC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(RTC_VECTOR)))
#endif
void RTC_ISR(void)
{
    switch (__even_in_range(RTCIV, 16))
    {
        case RTCIV_NONE:
            break;  //No interrupts

        case RTCIV_RTCOFIFG:
            break;  //RTCOFIFG

        case RTCIV_RTCRDYIFG:         //RTCRDYIFG
            break;

        case RTCIV_RTCTEVIFG:         //RTCEVIFG
            //Interrupts every minute
            g.minute_counter++;
            break;

        case RTCIV_RTCAIFG:         //RTCAIFG
            break;

        case RTCIV_RT0PSIFG:
            break; //RT0PSIFG

        case RTCIV_RT1PSIFG:
            break; //RT1PSIFG

        default:
            break;
    }
}

/*
 * Timer A0 Interrupt Service Routine
 * Used as button debounce timer
 */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
{
    // Both button S1 & S2 held down
    if (!(P1IN & BIT1) && !(P1IN & BIT2))
    {
        g.buttons.b1_and_b2_holdCount++;

        if (g.buttons.b1_and_b2_holdCount == 40)
        {
            // Stop Timer A0
            Timer_A_stop(TIMER_A0_BASE);

            // Change mode

            __bic_SR_register_on_exit(LPM3_bits);                // exit LPM3
        }
    }

    // Button S1 released
    if (P1IN & BIT1)
    {
        g.buttons.debounce_b1 = false;                                   // Clear button debounce
        P1OUT                &= ~BIT0;
    }

    // Button S2 released
    if (P1IN & BIT2)
    {
        g.buttons.debounce_b2 = false;                                   // Clear button debounce
        P9OUT                &= ~BIT7;
    }

    // Both button S1 & S2 released
    if ((P1IN & BIT1) && (P1IN & BIT2))
    {
        // Stop timer A0
        Timer_A_stop(TIMER_A0_BASE);
    }

    if (g.mode == DEFAULT_MODE)
    {
        __bic_SR_register_on_exit(LPM3_bits);            // exit LPM3
    }
}

// Timer capture interrupt
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TACCR1_ISR(void)
{

}

// Timer_A3 Interrupt Vector (TA0IV) handler
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TA0IV_ISR(void)
{
    unsigned char TA1IV_save = TA1IV;

    if (TA1IV_save == 0x04)
    {

        g.timer.freq_array[g.timer.freq_array_index] = TA1CCR2;
        g.timer.freq_array_index++;

        if (g.timer.freq_array_index == 20)
        {
            Timer_A_stop(TIMER_A1_BASE);
            Timer_A_disableCaptureCompareInterrupt(
                TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
            Timer_A_disableInterrupt(TIMER_A1_BASE);
            Timer_A_clear(TIMER_A1_BASE);
        }
    }

    // after the counter overflow increment the counter with 65536
    //if(Timer_A_getCaptureCompareInterruptStatus(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,TIMER_A_CAPTURE_OVERFLOW))
    if (TA1IV_save == 0x0E)
    {
        g.zero_hz_timeout++;

        if (g.zero_hz_timeout > 2000)
        {
            int i;

            for (i = 0; i < 20; i++)
            {
                g.timer.freq_array[i] = 0;
            }
            g.timer.overflow         = 0;
            g.zero_hz_timeout        = 0;
            g.timer.freq_array_index = 20;
            g.abort                  = true;
            Timer_A_stop(TIMER_A1_BASE);
            Timer_A_disableCaptureCompareInterrupt(
                TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
            Timer_A_disableInterrupt(TIMER_A1_BASE);
            Timer_A_clear(TIMER_A1_BASE);
        }

        //if(g.timer.freq_array_index>=3){
        if (DMA0SZ <= 16)
        {
            g.timer.overflow++;

            if (g.timer.overflow > 1000)
            {
                int i;

                for (i = 0; i < 20; i++)
                {
                    g.timer.freq_array[i] = 0;
                }
                g.timer.overflow         = 0;
                g.zero_hz_timeout        = 0;
                g.timer.freq_array_index = 20;
                g.abort                  = true;
                Timer_A_stop(TIMER_A1_BASE);
                Timer_A_disableCaptureCompareInterrupt(
                    TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
                Timer_A_disableInterrupt(TIMER_A1_BASE);
                Timer_A_clear(TIMER_A1_BASE);
            }
        }
    }
}
