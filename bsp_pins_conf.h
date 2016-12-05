#ifndef BSP_PINS_CONF_H
#define BSP_PINS_CONF_H

/**
 * @file bsp_pins_conf.h
 * @brief Implemntation specific pin mappings.
 * @details Contains both the hardware mappings and the logical mappings.
 * Hardware mapping correlates a pin number to a port and bit.  Logical mapping
 * is used to equate that hardware pin to a pcb function.  In addidtion to the
 * mapping information about how to setup and use the pins is included such as
 * input/output, State to set at boot up and what logic level is enabled.
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
#include <msp430.h>
// Standard library header files
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// *****************************************************************************
// Public macro definitions
// *****************************************************************************

// Specific to the MSP430FR6989

#define PIN_1   {1,  PORT_4,  BIT_3}
#define PIN_2   {2,  PORT_1,  BIT_4}
#define PIN_3   {3,  PORT_1,  BIT_5}
#define PIN_4   {4,  PORT_1,  BIT_6}
#define PIN_5   {5,  PORT_1,  BIT_7}
#define PIN_6   {6,  PORT_NA, BIT_NA} // LCDCAP
#define PIN_7   {7,  PORT_6,  BIT_0}
#define PIN_8   {8,  PORT_6,  BIT_1}
#define PIN_9   {9,  PORT_6,  BIT_2}
#define PIN_10  {10, PORT_6,  BIT_3}
#define PIN_11  {11, PORT_6,  BIT_4}
#define PIN_12  {12, PORT_6,  BIT_5}
#define PIN_13  {13, PORT_6,  BIT_6}
#define PIN_14  {14, PORT_2,  BIT_4}
#define PIN_15  {15, PORT_2,  BIT_5}
#define PIN_16  {16, PORT_2,  BIT_6}
#define PIN_17  {17, PORT_2,  BIT_7}
#define PIN_18  {18, PORT_10, BIT_2}
#define PIN_19  {19, PORT_5,  BIT_0}
#define PIN_20  {20, PORT_5,  BIT_1}
#define PIN_21  {21, PORT_5,  BIT_2}
#define PIN_22  {22, PORT_5,  BIT_3}
#define PIN_23  {23, PORT_3,  BIT_0}
#define PIN_24  {24, PORT_3,  BIT_1}
#define PIN_25  {25, PORT_3,  BIT_2}
#define PIN_26  {26, PORT_NA, BIT_NA} // DVSS1
#define PIN_27  {27, PORT_NA, BIT_NA} // DVCC1
#define PIN_28  {28, PORT_NA, BIT_NA} // TEST
#define PIN_29  {29, PORT_NA, BIT_NA} // RST
#define PIN_30  {30, PORT_NA, BIT_NA} // TDO
#define PIN_31  {31, PORT_NA, BIT_NA} // TDI
#define PIN_32  {32, PORT_NA, BIT_NA} // ACLK
#define PIN_33  {33, PORT_NA, BIT_NA} // TCK
#define PIN_34  {34, PORT_6,  BIT_7}
#define PIN_35  {35, PORT_7,  BIT_5}
#define PIN_36  {36, PORT_7,  BIT_6}
#define PIN_37  {37, PORT_10, BIT_1}
#define PIN_38  {38, PORT_7,  BIT_7}
#define PIN_39  {39, PORT_3,  BIT_3}
#define PIN_40  {40, PORT_3,  BIT_4}
#define PIN_41  {41, PORT_3,  BIT_5}
#define PIN_42  {42, PORT_3,  BIT_6}
#define PIN_43  {43, PORT_3,  BIT_7}
#define PIN_44  {44, PORT_8,  BIT_0}
#define PIN_45  {45, PORT_8,  BIT_1}
#define PIN_46  {46, PORT_8,  BIT_2}
#define PIN_47  {47, PORT_8,  BIT_3}
#define PIN_48  {48, PORT_2,  BIT_3}
#define PIN_49  {49, PORT_2,  BIT_2}
#define PIN_50  {50, PORT_2,  BIT_1}
#define PIN_51  {51, PORT_2,  BIT_0}
#define PIN_52  {52, PORT_7,  BIT_0}
#define PIN_53  {53, PORT_7,  BIT_1}
#define PIN_54  {54, PORT_7,  BIT_2}
#define PIN_55  {55, PORT_7,  BIT_3}
#define PIN_56  {56, PORT_7,  BIT_4}
#define PIN_57  {57, PORT_NA, BIT_NA} // DVSS2
#define PIN_58  {58, PORT_NA, BIT_NA} // DVCC2
#define PIN_59  {59, PORT_8,  BIT_4}
#define PIN_60  {60, PORT_8,  BIT_5}
#define PIN_61  {61, PORT_8,  BIT_6}
#define PIN_62  {62, PORT_8,  BIT_7}
#define PIN_63  {63, PORT_1,  BIT_3}
#define PIN_64  {64, PORT_1,  BIT_2}
#define PIN_65  {65, PORT_1,  BIT_1}
#define PIN_66  {66, PORT_1,  BIT_0}
#define PIN_67  {67, PORT_9,  BIT_0}
#define PIN_68  {68, PORT_9,  BIT_1}
#define PIN_69  {69, PORT_9,  BIT_2}
#define PIN_70  {70, PORT_9,  BIT_3}
#define PIN_71  {71, PORT_9,  BIT_4}
#define PIN_72  {72, PORT_9,  BIT_5}
#define PIN_73  {73, PORT_9,  BIT_6}
#define PIN_74  {74, PORT_9,  BIT_7}
#define PIN_75  {75, PORT_NA, BIT_NA} // ESIDVCC
#define PIN_76  {76, PORT_NA, BIT_NA} // ESIDVCC
#define PIN_77  {77, PORT_NA, BIT_NA} // ESICI
#define PIN_78  {78, PORT_NA, BIT_NA} // ESICOM
#define PIN_79  {79, PORT_NA, BIT_NA} // AVCC1
#define PIN_80  {80, PORT_NA, BIT_NA} // AVSS3
#define PIN_81  {81, PORT_NA, BIT_NA} // HFXOUT
#define PIN_82  {82, PORT_NA, BIT_NA} // HFXIN
#define PIN_83  {83, PORT_NA, BIT_NA} // AVSS1
#define PIN_84  {84, PORT_NA, BIT_NA} // LFXIN  UPDATE LATER PJ.4
#define PIN_85  {85, PORT_NA, BIT_NA} // LFXOUT UPDATE LATER PJ.5
#define PIN_86  {86, PORT_NA, BIT_NA} // AVSS2
#define PIN_87  {87, PORT_5,  BIT_4}
#define PIN_88  {88, PORT_5,  BIT_5}
#define PIN_89  {89, PORT_5,  BIT_6}
#define PIN_90  {90, PORT_5,  BIT_7}
#define PIN_91  {91, PORT_4,  BIT_4}
#define PIN_92  {92, PORT_4,  BIT_5}
#define PIN_93  {93, PORT_4,  BIT_6}
#define PIN_94  {94, PORT_4,  BIT_7}
#define PIN_95  {95, PORT_10, BIT_0}
#define PIN_96  {96, PORT_4,  BIT_0}
#define PIN_97  {97, PORT_4,  BIT_1}
#define PIN_98  {98, PORT_NA, BIT_NA} // DVSS3
#define PIN_99  {99, PORT_NA, BIT_NA} // AVCC3
#define PIN_100 {100,PORT_4,  BIT_2}

	//				name    		pin		type	default		enabled	alt_fcn
/*
#define pin_table \
	pin_table_entry(led_1, 			PIN_91,	OUTPUT,	DISABLED,	HIGH,	IO)	\
	pin_table_entry(led_2, 			PIN_92,	OUTPUT,	DISABLED,	HIGH,	IO)	\
	pin_table_entry(led_3, 			PIN_93,	OUTPUT,	DISABLED,	HIGH,	IO)	\
	pin_table_entry(led_4, 			PIN_94,	OUTPUT,	DISABLED,	HIGH,	IO)	\
	pin_table_entry(led_power_en, 	PIN_7, 	OUTPUT, DISABLED, 	LOW,	IO)	\
	pin_table_entry(power_down, 	PIN_64, INPUT, 	NONE, 		LOW,	IO)	\
	pin_table_entry(sda, 			PIN_96, OUTPUT, HIGH, 		NONE,	SECONDARY)	\
	pin_table_entry(scl,			PIN_97,	OUTPUT,	HIGH,		NONE,	SECONDARY)	\
	pin_table_entry(spi_clk,		PIN_2,	OUTPUT,	LOW,		NONE,	PRIMARY)	\
	pin_table_entry(spi_mosi,		PIN_4,	OUTPUT,	LOW,		NONE,	PRIMARY)	\
	pin_table_entry(spi_miso,		PIN_5,	INPUT,	NONE,		NONE,	PRIMARY)	\
	pin_table_entry(msp_uart_a_tx, 	PIN_100,OUTPUT,	HIGH,		NONE,	PRIMARY)	\
	pin_table_entry(msp_uart_a_rx,	PIN_1,	INPUT,	NONE,		NONE,	PRIMARY)	\
	pin_table_entry(msp_uart_b_tx,	PIN_40,	OUTPUT,	HIGH,		NONE,	PRIMARY)	\
	pin_table_entry(msp_uart_b_rx,	PIN_41,	INPUT,	NONE,		NONE,	PRIMARY)	\
	pin_table_entry(exp_addr1,		PIN_51,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(exp_addr2,		PIN_50,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(exp_addr3,		PIN_49,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(exp_addr4,		PIN_48,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(sd_cs,			PIN_14,	OUTPUT, DISABLED,	LOW,	IO)	\
	pin_table_entry(rtc_rst,		PIN_42,	OUTPUT,	DISABLED,	LOW,	IO)	\
	pin_table_entry(rtc_cs,			PIN_43,	OUTPUT,	DISABLED,	LOW,	IO)	\
	pin_table_entry(sd_pwr_en,		PIN_9,	OUTPUT,	DISABLED,	HIGH,	IO)	\
	pin_table_entry(logger_rst,		PIN_11,	OUTPUT,	ENABLED,	LOW,	IO)	\
	pin_table_entry(htr_power_en,	PIN_34,	OUTPUT,	DISABLED,	HIGH,	IO)	\
	pin_table_entry(uart_1w_sd_sel,	PIN_52,	OUTPUT, HIGH,		NONE,	IO)	\
	pin_table_entry(ow_slpz_sleep,	PIN_53,	OUTPUT,	ENABLED,	LOW,	IO)	\
	pin_table_entry(handshake_in,	PIN_35,	INPUT,	NONE,		LOW,	IO)	\
	pin_table_entry(handshake_out,	PIN_36,	OUTPUT,	DISABLED,	HIGH,	IO)	\
	pin_table_entry(rtd_drdy,		PIN_44,	INPUT,	NONE,		LOW,	IO)	\
	pin_table_entry(rtd_spi_cs,		PIN_45,	OUTPUT,	DISABLED,	LOW,	IO)	\
	pin_table_entry(rtc_start,		PIN_46,	OUTPUT,	DISABLED,	LOW,	IO)	\
	pin_table_entry(rtd_rst,		PIN_47, OUTPUT, DISABLED,	LOW,	IO)	\
	pin_table_entry(stack_power_en,	PIN_95,	OUTPUT,	DISABLED,	HIGH,	IO)	\
	pin_table_entry(avss,			PIN_66,	ANALOG,	NONE,		NONE,	IO)	\
	pin_table_entry(rev_2048,		PIN_66,	ANALOG,	NONE,		NONE,	IO)	\
	pin_table_entry(taos_data_out,	PIN_63,	INPUT,	NONE,		NONE,	PRIMARY)	\
	pin_table_entry(analog_reg_1, 	PIN_62,	ANALOG,	NONE,		NONE,	IO)	\
	pin_table_entry(analog_reg_2,	PIN_61,	ANALOG,	NONE,		NONE,	IO)	\
	pin_table_entry(analog_led_i,	PIN_60,	ANALOG,	NONE,		NONE,	IO)	\
	pin_table_entry(analog_htr_i,	PIN_59,	ANALOG,	NONE,		NONE,	IO)	\
	pin_table_entry(data0,			PIN_67,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(data1,			PIN_68,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(data2,			PIN_69,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(data3,			PIN_70,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(data4,			PIN_71,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(data5,			PIN_72,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(taos_out_en,	PIN_73,	OUTPUT,	DISABLED,	LOW,	IO)	\
	pin_table_entry(unused_1,		PIN_15,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_2,		PIN_16,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_3,		PIN_17,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_4,		PIN_23,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_5,		PIN_24,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_6,		PIN_25,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_7,		PIN_39,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_8,		PIN_19,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_9,		PIN_20,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_10,		PIN_21,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_11,		PIN_22,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_12,		PIN_87,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_13,		PIN_88,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_14,		PIN_89,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_15,		PIN_90,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_16,		PIN_8,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_17,		PIN_10,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_18,		PIN_12,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_19,		PIN_13,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_20,		PIN_54,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_21,		PIN_55,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_22,		PIN_56,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_23,		PIN_38,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_24,		PIN_37,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_25,		PIN_18,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_26,		PIN_74,	OUTPUT,	LOW,		NONE,	IO)	\
	*/



//				name    		pin		type	default		enabled	alt_fcn
#define pin_table \
	pin_table_entry(fluidics_en_latch_bag_1,	PIN_51,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(heater_en_latch_bag_1, 		PIN_50,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(spi_cs_latch_bag_1, 		PIN_49,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(fluidics_en_latch_mani_1, 	PIN_48,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(fluidics_en_latch_bag_2,	PIN_52,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(heater_en_latch_bag_2, 		PIN_53,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(spi_cs_latch_bag_2, 		PIN_54,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(fluidics_en_latch_mani_2, 	PIN_55,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(card_en_latch_2, 			PIN_56,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(rtd_start, 					PIN_35,	OUTPUT,	DISABLED,	HIGH,	IO)	\
	pin_table_entry(spi_cs_latch_mani_2, 		PIN_36,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(heater_en_latch_mani2, 		PIN_38,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(cs_latch_clr, 				PIN_44,	OUTPUT,	DISABLED,	LOW,	IO)	\
	pin_table_entry(card_en_latch_1, 			PIN_45,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(heater_en_latch_mani_1, 	PIN_46,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(spi_cs_latch_mani_1, 		PIN_47,	OUTPUT,	ENABLED,	HIGH,	IO)	\
	pin_table_entry(sda, 			PIN_96, OUTPUT, HIGH, 		NONE,	SECONDARY)	\
	pin_table_entry(scl,			PIN_97,	OUTPUT,	HIGH,		NONE,	SECONDARY)	\
	pin_table_entry(spi_clk,		PIN_2,	OUTPUT,	LOW,		NONE,	PRIMARY)	\
	pin_table_entry(spi_mosi,		PIN_4,	OUTPUT,	LOW,		NONE,	PRIMARY)	\
	pin_table_entry(spi_miso,		PIN_5,	INPUT,	NONE,		NONE,	PRIMARY)	\
	pin_table_entry(msp_uart_a_tx, 	PIN_100,OUTPUT,	HIGH,		NONE,	PRIMARY)	\
	pin_table_entry(msp_uart_a_rx,	PIN_1,	INPUT,	NONE,		NONE,	PRIMARY)	\
	pin_table_entry(msp_uart_b_tx,	PIN_40,	OUTPUT,	HIGH,		NONE,	PRIMARY)	\
	pin_table_entry(msp_uart_b_rx,	PIN_41,	INPUT,	NONE,		NONE,	PRIMARY)	\
	pin_table_entry(avss,			PIN_66,	ANALOG,	NONE,		NONE,	IO)	\
	pin_table_entry(rev_2048,		PIN_65,	ANALOG,	NONE,		NONE,	IO)	\
	pin_table_entry(taos_data_out,	PIN_63,	INPUT,	NONE,		NONE,	PRIMARY)	\
	pin_table_entry(analog_vbus,	PIN_61,	ANALOG,	NONE,		NONE,	IO)	\
	pin_table_entry(analog_3_3v,	PIN_60,	ANALOG,	NONE,		NONE,	IO)	\
	pin_table_entry(analog_6v,		PIN_59,	ANALOG,	NONE,		NONE,	IO)	\
	pin_table_entry(data0,			PIN_67,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(data1,			PIN_68,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(data2,			PIN_69,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(data3,			PIN_70,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(data4,			PIN_71,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(data5,			PIN_72,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(taos_out_en,	PIN_73,	OUTPUT,	DISABLED,	LOW,	IO)	\
	pin_table_entry(unused_1,		PIN_3,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_2,		PIN_64,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_3,		PIN_62,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_4,		PIN_74,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_5,		PIN_14,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_6,		PIN_15,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_7,		PIN_16,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_8,		PIN_17,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_9,		PIN_23,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_10,		PIN_24,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_11,		PIN_25,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_12,		PIN_39,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_13,		PIN_42,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_14,		PIN_43,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_15,		PIN_91,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_16,		PIN_92,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_17,		PIN_93,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_18,		PIN_94,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_19,		PIN_19,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_20,		PIN_20,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_21,		PIN_21,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_22,		PIN_22,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_23,		PIN_87,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_24,		PIN_88,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_25,		PIN_89,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_26,		PIN_90,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_27,		PIN_7,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_28,		PIN_8,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_29,		PIN_9,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_30,		PIN_10,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_31,		PIN_11,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_32,		PIN_12,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_33,		PIN_13,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_34,		PIN_34,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_35,		PIN_95,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_36,		PIN_37,	OUTPUT,	LOW,		NONE,	IO)	\
	pin_table_entry(unused_37,		PIN_18,	OUTPUT,	LOW,		NONE,	IO)	\




// *****************************************************************************
// Public data type definitions (enum, struct, typedef, union)
// *****************************************************************************

// *****************************************************************************
// Public constant definitions
// *****************************************************************************

/**
 * Struct to hold info about all of the port pins.  This is created with the
 * help of a xmacro.
 */
static const struct
{
#define pin_table_entry(a,b,c,d,e,f) pin_t a;
	pin_table
#undef pin_table_entry
}pins = {
#define pin_table_entry(a,b,c,d,e,f) {b,c,d,e,f},
		pin_table
#undef pin_table_entry
};

/**
 * Array of stringified names for each pin.  Name index matches the pin table
 * entry thanks to xmacro.
 */
static const char* const pin_names[]={
#define pin_table_entry(a,b,c,d,e,f) #a,
		pin_table
#undef pin_table_entry
};
// *****************************************************************************
// Public function prototypes
// *****************************************************************************

// *****************************************************************************
// Public inline function definitions
// *****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // BSP_PINS_CONF_H
