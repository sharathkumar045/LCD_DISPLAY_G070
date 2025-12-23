/*
 * RTC_Drv_Functions.c
 *
 *  Created on: 28 May 2020
 *      Author: G SK Reddy
 */

#include "i2c.h"

#include "RTC_Drv_Functions.h"
#include "RTC_Drv_Variables.h"

#include "stm32g0xx_ll_rtc.h"



void RTC_Drv_Init(I2C_TypeDef* I2CX, uint8_t Device_Address)
{
	RTC_Drv_Var.I2Cx=I2CX;
	RTC_Drv_Var.Device_Addr = Device_Address;
	RTC_Drv_Var.Delay_Limit = 12000;
	RTC_Drv_Var.Delay = RTC_Drv_Var.Delay_Limit;
	RTC_Drv_Var.Cntr = 0;
	RTC_Drv_Var.Cntr_Limit = 10;

	LL_I2C_DisableAutoEndMode(RTC_Drv_Var.I2Cx);

}

void RTC_Drv_Get_Ext_Date_Time(void)
{
		uint8_t arr[16]={0};
		RTC_Drv_Var.Delay=RTC_Drv_Var.Delay_Limit;
		while(RTC_Drv_Var.Delay--)
		{}


		LL_I2C_SetSlaveAddr(RTC_Drv_Var.I2Cx,RTC_Drv_Var.Device_Addr);
		LL_I2C_SetMasterAddressingMode(RTC_Drv_Var.I2Cx,LL_I2C_ADDRESSING_MODE_7BIT);

//		RTC_Drv_Var.I2Cx->CR2&=(~I2C_CR2_RD_WRN);
//		LL_I2C_SetTransferSize(RTC_Drv_Var.I2Cx,2);
//
//		RTC_Drv_Var.I2Cx->CR2|= I2C_CR2_START;
//
//		RTC_Drv_Var.Cntr = 0;
//		while(LL_I2C_IsActiveFlag_TXE(RTC_Drv_Var.I2Cx)!=1)
//		{
//			RTC_Drv_Var.Cntr_Req = 1;
//			if(RTC_Drv_Var.Cntr>=RTC_Drv_Var.Cntr_Limit)
//				break;
//		}
//		RTC_Drv_Var.Cntr_Req = 0;
//		RTC_Drv_Var.Cntr = 0;
//
//		LL_I2C_TransmitData8(RTC_Drv_Var.I2Cx, RTC_Drv_Var.Memory_Upper_Addr);
//
//		RTC_Drv_Var.Cntr = 0;
//		while(LL_I2C_IsActiveFlag_TXE(RTC_Drv_Var.I2Cx)!=1)
//		{
//			RTC_Drv_Var.Cntr_Req = 1;
//			if(RTC_Drv_Var.Cntr>=RTC_Drv_Var.Cntr_Limit)
//				break;
//		}
//		RTC_Drv_Var.Cntr_Req = 0;
//		RTC_Drv_Var.Cntr = 0;
//
//		LL_I2C_TransmitData8(RTC_Drv_Var.I2Cx, RTC_Drv_Var.Memory_Lower_Addr);

		RTC_Drv_Var.I2Cx->CR2|=I2C_CR2_RD_WRN;
		LL_I2C_SetTransferSize(RTC_Drv_Var.I2Cx,16);


		RTC_Drv_Var.I2Cx->CR2|= I2C_CR2_START;


		for(uint16_t i=0;i<16;i++)
		{
			RTC_Drv_Var.Cntr = 0;
			while(!LL_I2C_IsActiveFlag_RXNE(RTC_Drv_Var.I2Cx))
			{
				if(RTC_Drv_Var.Cntr>=RTC_Drv_Var.Cntr_Limit)
					break;
			}
			RTC_Drv_Var.Cntr = 0;

			arr[i]=LL_I2C_ReceiveData8(RTC_Drv_Var.I2Cx);
		}

		LL_I2C_GenerateStopCondition(RTC_Drv_Var.I2Cx);

		RTC_Ext_Reg.CR2=arr[0];
		RTC_Ext_Reg.Second_Cntr=arr[1];
		RTC_Ext_Reg.Minute_Cntr=arr[2];
		RTC_Ext_Reg.Hour_Cntr=arr[3];
		RTC_Ext_Reg.Week_Cntr=arr[4];
		RTC_Ext_Reg.Day_Cntr=arr[5];
		RTC_Ext_Reg.Month_Cntr=arr[6];
		RTC_Ext_Reg.Year_Cntr=arr[7];
		RTC_Ext_Reg.Time_Trim_Reg=arr[8];
		RTC_Ext_Reg.Alarm_A_Min_Reg=arr[9];
		RTC_Ext_Reg.Alarm_A_Hour_Reg=arr[10];
		RTC_Ext_Reg.Alarm_A_Day_of_Week_Reg=arr[11];
		RTC_Ext_Reg.Alarm_B_Min_Reg=arr[12];
		RTC_Ext_Reg.Alarm_B_Hour_Reg=arr[13];
		RTC_Ext_Reg.Alarm_B_Day_of_Week_Reg=arr[14];
		RTC_Ext_Reg.CR1=arr[15];


		RTC_Drv_Ext_Time.Seconds=__LL_RTC_CONVERT_BCD2BIN(RTC_Ext_Reg.Second_Cntr);
		RTC_Drv_Ext_Time.Minutes=__LL_RTC_CONVERT_BCD2BIN(RTC_Ext_Reg.Minute_Cntr);
		RTC_Drv_Ext_Time.Hours=__LL_RTC_CONVERT_BCD2BIN(RTC_Ext_Reg.Hour_Cntr);
		RTC_Drv_Ext_Time.Week=RTC_Ext_Reg.Week_Cntr;
		RTC_Drv_Ext_Time.Day=__LL_RTC_CONVERT_BCD2BIN(RTC_Ext_Reg.Day_Cntr);
		RTC_Drv_Ext_Time.Month=__LL_RTC_CONVERT_BCD2BIN(RTC_Ext_Reg.Month_Cntr);
		RTC_Drv_Ext_Time.Year=__LL_RTC_CONVERT_BCD2BIN(RTC_Ext_Reg.Year_Cntr);
}

void RTC_Drv_Set_Ext_Date_Time(void)
{
	RTC_Drv_Ext_Write_Byte(RTC_Reg_Min_Addr  , __LL_RTC_CONVERT_BIN2BCD(RTC_Drv_Ext_Time.Minutes));
	RTC_Drv_Ext_Write_Byte(RTC_Reg_Hour_Addr , __LL_RTC_CONVERT_BIN2BCD(RTC_Drv_Ext_Time.Hours));
	RTC_Drv_Ext_Write_Byte(RTC_Reg_Day_Addr  , __LL_RTC_CONVERT_BIN2BCD(RTC_Drv_Ext_Time.Day));
	RTC_Drv_Ext_Write_Byte(RTC_Reg_Month_Addr, __LL_RTC_CONVERT_BIN2BCD(RTC_Drv_Ext_Time.Month));
	RTC_Drv_Ext_Write_Byte(RTC_Reg_Year_Addr , __LL_RTC_CONVERT_BIN2BCD(RTC_Drv_Ext_Time.Year));
}

//addr=0xf0, data=0b00110000
void RTC_Drv_Ext_Write_Byte(volatile uint8_t Mem_Addr, volatile uint8_t Data)
{
		RTC_Drv_Var.Delay=RTC_Drv_Var.Delay_Limit;
		while(RTC_Drv_Var.Delay--)
		{}


		LL_I2C_SetSlaveAddr(RTC_Drv_Var.I2Cx,RTC_Drv_Var.Device_Addr);
		RTC_Drv_Var.I2Cx->CR2&=(~I2C_CR2_RD_WRN);	//Write direction
		LL_I2C_SetMasterAddressingMode(RTC_Drv_Var.I2Cx,LL_I2C_ADDRESSING_MODE_7BIT);
		LL_I2C_SetTransferSize(RTC_Drv_Var.I2Cx,2);

		RTC_Drv_Var.I2Cx->CR2|= I2C_CR2_START;

		RTC_Drv_Var.Cntr = 0;
		while(LL_I2C_IsActiveFlag_TXIS(RTC_Drv_Var.I2Cx)!=1)
		{
			if(RTC_Drv_Var.Cntr>=RTC_Drv_Var.Cntr_Limit)
				break;
		}
		RTC_Drv_Var.Cntr = 0;

		LL_I2C_TransmitData8(RTC_Drv_Var.I2Cx, Mem_Addr);

//		RTC_Drv_Var.Cntr = 0;
//		while(LL_I2C_IsActiveFlag_TXIS(RTC_Drv_Var.I2Cx)!=1)
//		{
//			RTC_Drv_Var.Cntr_Req = 1;
//			if(RTC_Drv_Var.Cntr>=RTC_Drv_Var.Cntr_Limit)
//				break;
//		}
//		RTC_Drv_Var.Cntr_Req = 0;
//		RTC_Drv_Var.Cntr = 0;
//
//		LL_I2C_TransmitData8(RTC_Drv_Var.I2Cx, RTC_Drv_Var.Memory_Lower_Addr);


		RTC_Drv_Var.Cntr = 0;
		while(LL_I2C_IsActiveFlag_TXIS(RTC_Drv_Var.I2Cx)!=1)
		{
			if(RTC_Drv_Var.Cntr>=RTC_Drv_Var.Cntr_Limit)
				break;
		}
		RTC_Drv_Var.Cntr = 0;

		LL_I2C_TransmitData8(RTC_Drv_Var.I2Cx, Data);

		RTC_Drv_Var.Cntr = 0;
		while(LL_I2C_IsActiveFlag_TXE(RTC_Drv_Var.I2Cx)!=1)
		{
			if(RTC_Drv_Var.Cntr>=RTC_Drv_Var.Cntr_Limit)
				break;
		}
		RTC_Drv_Var.Cntr = 0;


		LL_I2C_GenerateStopCondition(RTC_Drv_Var.I2Cx);
}

void RTC_Drv_Set_Intrnl_From_Ext(void)
{
	LL_RTC_TimeTypeDef RTC_TimeStruct = {0};
	LL_RTC_DateTypeDef RTC_DateStruct = {0};

	RTC_Drv_Get_Ext_Date_Time();

	RTC_TimeStruct.Hours = RTC_Ext_Reg.Hour_Cntr;
	RTC_TimeStruct.Minutes = RTC_Ext_Reg.Minute_Cntr;
	RTC_TimeStruct.Seconds = RTC_Ext_Reg.Second_Cntr;
	LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_TimeStruct);

	RTC_DateStruct.Month = RTC_Ext_Reg.Month_Cntr;
	RTC_DateStruct.Year = RTC_Ext_Reg.Year_Cntr;
	RTC_DateStruct.Day=RTC_Ext_Reg.Day_Cntr;
	RTC_DateStruct.WeekDay=RTC_Ext_Reg.Week_Cntr;
	LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_DateStruct);
}

void RTC_Drv_Get_Intrnl_Date_Time(void)
{
	  RTC_Drv_Intrnl_Time.Seconds=__LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetSecond(RTC));

	  RTC_Drv_Intrnl_Time.Minutes=__LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetMinute(RTC));

	  RTC_Drv_Intrnl_Time.Hours=__LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetHour(RTC));

	  RTC_Drv_Intrnl_Time.Day=__LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetDay(RTC));

	  RTC_Drv_Intrnl_Time.Week=__LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetWeekDay(RTC));

	  RTC_Drv_Intrnl_Time.Month=__LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetMonth(RTC));

	  RTC_Drv_Intrnl_Time.Year=__LL_RTC_CONVERT_BCD2BIN(LL_RTC_DATE_GetYear(RTC));
}

void RTC_Drv_Intrnl_Alarm_Init(void)
{
	  /* (1) Write access for RTC registers */
	  /* (2) Disable alarm A to modify it */
	  /* (3) Wait until it is allow to modify alarm A value */
	  /* (4) Modify alarm A mask to have an interrupt each 1Hz */
	  /* (5) Enable alarm A and alarm A interrupt */
	  /* (6) Disable write access */
	  RTC->WPR = 0xCA; /* (1) */
	  RTC->WPR = 0x53; /* (1) */
	  RTC->CR &=~ RTC_CR_ALRAE; /* (2) */
//	  while ((RTC->ISR & RTC_ISR_ALRAWF) != RTC_ISR_ALRAWF) /* (3) */
//	  {
//	  /* add time out here for a robust application */
//	  }
//	  LL_RTC_ALMA_SetMask(RTC,LL_RTC_ALMA_MASK_DATEWEEKDAY);
//
	  LL_RTC_ALMA_ConfigTime(RTC,LL_RTC_ALMA_TIME_FORMAT_AM, RTC_Alarm_Hour, RTC_Alram_Min, 0);

	  RTC->CR = RTC_CR_ALRAIE | RTC_CR_ALRAE; /* (5) */
	  RTC->WPR = 0xFE; /* (6) */
	  RTC->WPR = 0x64; /* (6) */
}
