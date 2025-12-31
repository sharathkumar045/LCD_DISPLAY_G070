/*
 * EEPROM_I2C_App_Variables.h
 *
 *  Created on: 28 May 2020
 *      Author: G SK Reddy
 */

#ifndef EEPROM_APP_LIB_EEPROM_APP_VARIABLES_H_
#define EEPROM_APP_LIB_EEPROM_APP_VARIABLES_H_

#include "main.h"

#define EEPROM_App_Settings_Start_Addr 0
#define EEPROM_App_Settings_Arr_Len 80

#define EEPROM_App_Metering_Start_Addr 128
#define EEPROM_App_Metering_Arr_Len 8

#define EEPROM_App_Metering_Cntr_Start_Addr 100


struct EEPROM_App_Flag{
	volatile unsigned Read_Settings_Req : 1;
	volatile unsigned Write_Settings_Req : 1;

	volatile unsigned Read_Metering_Req : 1;
	volatile unsigned Write_Metering_Req : 1;
	volatile unsigned Read_Error : 1;
};

extern struct EEPROM_App_Flag EEPROM_App_Flags;

struct EEPROM_App_Variables{
	volatile uint8_t EEPROM_CRC;
	__IO uint8_t Mtrng_Energy_Cntr;
};

extern struct EEPROM_App_Variables EEPROM_App_Var;

#endif /* EEPROM_APP_LIB_EEPROM_APP_VARIABLES_H_ */
