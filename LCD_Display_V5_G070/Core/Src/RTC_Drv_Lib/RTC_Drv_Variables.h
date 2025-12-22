/*
 * RTC_Drv_Variables.h
 *
 *  Created on: 28 May 2020
 *      Author: G SK Reddy
 */

#ifndef RTC_DRV_LIB_RTC_DRV_VARIABLES_H_
#define RTC_DRV_LIB_RTC_DRV_VARIABLES_H_

#include "i2c.h"

#define RTC_Device_Addr 0b0110010<<1

#define RTC_Alarm_Flag (RTC->ICSR & RTC_ICSR_ALRAWF)
#define RTC_Alarm_Clr_Flag (RTC->ICSR &= ~RTC_ICSR_ALRAWF)

#define RTC_Alarm_Hour 0x12
#define RTC_Alram_Min  0x36

#define RTC_Reg_Min_Addr 0x10
#define RTC_Reg_Hour_Addr 0x20
#define RTC_Reg_Day_Addr 0x40
#define RTC_Reg_Month_Addr 0x50
#define RTC_Reg_Year_Addr 0x60

struct RTC_Drv_Variables{
		volatile uint8_t Device_Addr;
		volatile uint8_t Meomry_Addr_to_Write;  //WRITING : addr must be in multiples of PAGE_SIZE //READING: any random addr is valied
		volatile uint16_t Delay;
		volatile uint16_t Delay_Limit;
		volatile uint8_t Cntr;
		volatile uint8_t Cntr_Limit;
		I2C_TypeDef* I2Cx;

};

extern struct RTC_Drv_Variables RTC_Drv_Var;

struct RTC_Registers{
	volatile uint8_t Second_Cntr;
	volatile uint8_t Minute_Cntr;
	volatile uint8_t Hour_Cntr;
	volatile uint8_t Week_Cntr;
	volatile uint8_t Day_Cntr;
	volatile uint8_t Month_Cntr;
	volatile uint8_t Year_Cntr;
	volatile uint8_t Time_Trim_Reg;
	volatile uint8_t Alarm_A_Min_Reg;
	volatile uint8_t Alarm_A_Hour_Reg;
	volatile uint8_t Alarm_A_Day_of_Week_Reg;
	volatile uint8_t Alarm_B_Min_Reg;
	volatile uint8_t Alarm_B_Hour_Reg;
	volatile uint8_t Alarm_B_Day_of_Week_Reg;
	volatile uint8_t CR1;
	volatile uint8_t CR2;
};

extern struct RTC_Registers RTC_Ext_Reg;

struct RTC_Drv_Time{

	volatile uint8_t Seconds;
	volatile uint8_t Minutes;
	volatile uint8_t Hours;
	volatile uint8_t Week;
	volatile uint8_t Day;
	volatile uint8_t Month;
	volatile uint16_t Year;
};

extern struct RTC_Drv_Time RTC_Drv_Intrnl_Time, RTC_Drv_Ext_Time;

//extern const uint8_t RTC_Reg_Val_Arr[100];

#endif /* RTC_DRV_LIB_RTC_DRV_VARIABLES_H_ */
