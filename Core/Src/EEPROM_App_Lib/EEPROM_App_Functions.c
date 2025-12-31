/*
 * EEPROM_I2C_App_Functions.c
 *
 *  Created on: 28 May 2020
 *      Author: G SK Reddy
 */
#include "EEPROM_App_Functions.h"
#include "EEPROM_App_Variables.h"

#include "EEPROM_Drv_Functions.h"
#include "EEPROM_Drv_Variables.h"

#include "UART1_Mast_Drv_Functions.h"


void EEPROM_App_Read_Settings(void)
{
	if(EEPROM_App_Flags.Read_Settings_Req==1)
	{
		EEPROM_App_Flags.Read_Settings_Req=0;
		EEPROM_App_Flags.Read_Error=0;

		EEPROM_Drv_Var.Meomry_Start_Addr_16bit=EEPROM_App_Settings_Start_Addr;
		EEPROM_Drv_Var.Length_to_Read_or_Write=EEPROM_App_Settings_Arr_Len;
		EEPROM_Drv_Read_Array();
		EEPROM_App_Var.EEPROM_CRC=U1Mast_Drv_crcFast(EEPROM_Read_Array,EEPROM_App_Settings_Arr_Len-1);
		if((EEPROM_Read_Array[0]!='S') && (EEPROM_Read_Array[EEPROM_App_Settings_Arr_Len-1]!=EEPROM_App_Var.EEPROM_CRC))
		{
			EEPROM_App_Flags.Read_Error=1;
		}
	}
}

void EEPROM_App_Write_Settings(void)
{
	if(EEPROM_App_Flags.Write_Settings_Req==1)
	{
		EEPROM_App_Flags.Write_Settings_Req=0;
		EEPROM_Drv_Var.Meomry_Start_Addr_16bit=EEPROM_App_Settings_Start_Addr;
		EEPROM_Drv_Var.Length_to_Read_or_Write=EEPROM_App_Settings_Arr_Len;
		EEPROM_Drv_Write_Array();
	}
}


void EEPROM_App_Read_Metering(void)
{
	if(EEPROM_App_Flags.Read_Metering_Req==1)
	{
		EEPROM_App_Flags.Read_Metering_Req=0;
		EEPROM_App_Flags.Read_Error=0;

		EEPROM_Drv_Var.Meomry_Start_Addr_16bit=EEPROM_App_Metering_Start_Addr;
		EEPROM_Drv_Var.Length_to_Read_or_Write=128;
		EEPROM_Drv_Read_Array();
//		EEPROM_App_Var.EEPROM_CRC=U1Mast_Drv_crcFast(EEPROM_Read_Array,EEPROM_App_Metering_Arr_Len-1);
//		if((EEPROM_Read_Array[EEPROM_App_Metering_Arr_Len-1]!=EEPROM_App_Var.EEPROM_CRC))
//		{
//			EEPROM_App_Flags.Read_Error=1;
//		}
	}
}

void EEPROM_App_Write_Metering(void)
{
	if(EEPROM_App_Flags.Write_Metering_Req==1)
	{
		EEPROM_App_Flags.Write_Metering_Req=0;
		EEPROM_Drv_Var.Meomry_Start_Addr_16bit=EEPROM_App_Metering_Start_Addr + (EEPROM_App_Var.Mtrng_Energy_Cntr*EEPROM_App_Metering_Arr_Len);
		EEPROM_Drv_Var.Length_to_Read_or_Write=EEPROM_App_Metering_Arr_Len;
		EEPROM_Drv_Write_Array();
	}
}
