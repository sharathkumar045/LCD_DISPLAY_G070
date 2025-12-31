/*
 * RTC_Drv_Functions.h
 *
 *  Created on: 28 May 2020
 *      Author: G SK Reddy
 */

#ifndef RTC_DRV_LIB_RTC_DRV_FUNCTIONS_H_
#define RTC_DRV_LIB_RTC_DRV_FUNCTIONS_H_

void RTC_Drv_Init(I2C_TypeDef* I2CX, uint8_t Device_Address);

void RTC_Drv_Get_Ext_Date_Time(void);

void RTC_Drv_Set_Ext_Date_Time(void);

void RTC_Drv_Ext_Write_Byte(volatile uint8_t Mem_Addr, volatile uint8_t Data);

void RTC_Drv_Set_Intrnl_From_Ext(void);

void RTC_Drv_Get_Intrnl_Date_Time(void);

void RTC_Drv_Intrnl_Alarm_Init(void);

#endif /* RTC_DRV_LIB_RTC_DRV_FUNCTIONS_H_ */
