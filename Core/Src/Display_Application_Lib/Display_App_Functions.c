/*
 * General_Functions.c
 *
 *  Created on: 15-May-2020
 *      Author: pc
 */
#include "stm32g0xx.h"
#include "main.h"
#include "string.h"

#include "LCD16X2_Driver_Variables.h"
#include "LCD16X2_Driver_Functions.h"

#include "Display_App_Variables.h"
#include "Display_App_Functions.h"

#include "Switch_App_Variables.h"
#include "Switch_App_Functions.h"

#include "Main_Variables.h"
#include "Main_Functions.h"

#include "UART1_Mast_App_Functions.h"
#include "UART1_Mast_App_Variables.h"

//#include "UART1_Master_Functions.h"
//#include "UART1_Master_Var.h"

#include "RTC_Drv_Functions.h"
#include "RTC_Drv_Variables.h"

void Metering_State_Disp_Fn(void)
{
	LCD_Locate(1, 1);
	for(int i = 0; i<8; i++)
	{
		LCDData(Disp_Metering_Name[Disp_Cntrl.Mtrng_Index][i]);
	}
	LCDWriteString(" =");
	if(Disp_Cntrl.Mtrng_Index == 9)
	{
		float temp = (2000000/(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index]*Disp_Metering_Value_Scaler[Disp_Cntrl.Mtrng_Index]));
		if(temp > 44 && temp < 56)
		{
			Printfloat(temp,3, 2);
		}
		else
		{
			temp = 0;
			Printfloat(temp,3, 2);
		}
	}
	else if(Disp_Cntrl.Mtrng_Index == 6)
	{
		if(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index]<V_Mains_L_Cutoff || Disp_Metering_Value[Disp_Cntrl.Mtrng_Index]>V_Mains_H_Cutoff )
		{
			Printfloat(0, 3, 2);
		}
		else
		{
			Printfloat(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index]*Disp_Metering_Value_Scaler[Disp_Cntrl.Mtrng_Index],3, 2);
		}
	}
	else if(Disp_Cntrl.Mtrng_Index == 7)
	{
		if(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index]>I_Inv_Full_Load)
		{
			Printfloat(0, 3, 2);
		}
		else
		{
			Printfloat(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index]*Disp_Metering_Value_Scaler[Disp_Cntrl.Mtrng_Index],3, 2);
		}

	}
	else if(Disp_Cntrl.Mtrng_Index == 10)
	{
		if(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index]>Grid_KVA_Limit)
		{
			Printfloat(0, 3, 2);
		}
		else
		{
			Printfloat(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index]*Disp_Metering_Value_Scaler[Disp_Cntrl.Mtrng_Index],3, 2);
		}

	}

	else
	{
		Printfloat(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index]*Disp_Metering_Value_Scaler[Disp_Cntrl.Mtrng_Index],3, 2);
	}

//-------------------------------------------------------------------------------------------------------------------------------------------
	LCD_Locate(2, 1);
	for(int i = 0; i<8; i++)
	{
		LCDData(Disp_Metering_Name[Disp_Cntrl.Mtrng_Index + 1][i]);
	}
	LCDWriteString(" =");
	if(Disp_Cntrl.Mtrng_Index == 8)
	{
		float temp = (2000000/(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index+1]*Disp_Metering_Value_Scaler[Disp_Cntrl.Mtrng_Index+1]));
		if(temp > 45 && temp < 55)
		{
			Printfloat(temp,3, 2);
		}
		else
		{
			temp = 0;
			Printfloat(temp,3, 2);
		}
	}
	else if(Disp_Cntrl.Mtrng_Index == 5)
	{
		if(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index+1]<V_Mains_L_Cutoff || Disp_Metering_Value[Disp_Cntrl.Mtrng_Index+1]>V_Mains_H_Cutoff )
		{
			Printfloat(0, 3, 2);
		}
		else
		{
			Printfloat(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index+1]*Disp_Metering_Value_Scaler[Disp_Cntrl.Mtrng_Index+1],3, 2);
		}
	}
	else if(Disp_Cntrl.Mtrng_Index == 6)
	{
		if(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index+1]>I_Inv_Full_Load)
		{
			Printfloat(0, 3, 2);
		}
		else
		{
			Printfloat(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index+1]*Disp_Metering_Value_Scaler[Disp_Cntrl.Mtrng_Index+1],3, 2);
		}
	}
	else if(Disp_Cntrl.Mtrng_Index == 9)
	{
		if(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index+1]>Grid_KVA_Limit)
		{
			Printfloat(0, 3, 2);
		}
		else
		{
			Printfloat(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index+1]*Disp_Metering_Value_Scaler[Disp_Cntrl.Mtrng_Index+1],3, 2);
		}

	}

	else
	{
		Printfloat(Disp_Metering_Value[Disp_Cntrl.Mtrng_Index + 1]*Disp_Metering_Value_Scaler[Disp_Cntrl.Mtrng_Index + 1],3, 2);
	}

}

void Metering_Rq_Data_State_Disp_Fn(void)
{
	LCD_Locate(1, 1);
	LCDWriteString("Sync_Complete");
	Delay(1000);

}

void Option_State_Disp_Fn(void)
{
	LCD_Locate(1, 1);
	for(int i = 0; i<8; i++)
	{
		LCDData(Disp_Option_Name[Disp_Cntrl.Optn_Index][i]);
	}

}

void Password_State_Disp_Fn(void)
{
	LCD_Locate(1, 1);
	for(int i = 0; i<8; i++)
	{
		LCDData(Disp_Password_Name[i]);
	}
}

void Calibration_State_Disp_Fn(void)
{
	LCD_Locate(1, 1);
	for(int i = 0; i<8; i++)
	{
		LCDData(Disp_Metrng_Calib_Name[Disp_Cntrl.Calib_Index][i]);
	}
	LCDWriteString(" =");
	Printfloat(Disp_Metrng_Calib_Value[Disp_Cntrl.Calib_Index]*Disp_Calib_Value_Scaler[Disp_Cntrl.Calib_Index],3, 2);

	LCD_Locate(2, 1);
	for(int i = 0; i<8; i++)
	{
		LCDData(Disp_Desired_Metrng_Calib_Name[Disp_Cntrl.Calib_Index][i]);
	}
	LCDWriteString(" =");
	Printfloat(Disp_Desired_Metrng_Calib_Value[Disp_Cntrl.Calib_Index]*Disp_Calib_Value_Scaler[Disp_Cntrl.Calib_Index],3, 2);
}

void CalibRq_Rq_Data_State_Disp_Fn(void)
{

}

void Calib_Send_Data_State_Disp_Fn(void)
{
	LCD_Locate(1, 1);

	LCDWriteString(" =");
}

void Settings_State_Disp_Fn(void)
{
	LCD_Locate(1, 1);
	for(int i = 0; i<15; i++)
	{
		LCDData(Disp_Setting_Name[Disp_Cntrl.Settng_Index][i]);
	}

	LCD_Locate(2, 1);
	LCDWriteString(" =");
	Printfloat(Disp_New_Setting_Value[Disp_Cntrl.Settng_Index]*Disp_Setting_Value_Scaler[Disp_Cntrl.Settng_Index],3, 2);
}

void Settings_Data_Rq_EEPROM_Disp_Fn(void)
{
	LCD_Locate(1, 1);

	LCDWriteString("Syncing..");
}

void Settings_Send_Data_State_Disp_Fn(void)
{
	LCD_Locate(1, 1);

	LCDWriteString("Setting...");

	Delay(1000);

}

void Save_Settings_in_EEPROM_Settings_State_Disp_Fn(void)
{

	LCD_Locate(1, 1);
	LCDWriteString(" Settings Send");
}

void Reset_State_Disp_Fn(void)
{
	LCDWriteString("Energy Data Stored");
}

void Reset_Send_Rq_State_Disp_Fn(void)
{
	LCDWriteString("Reset completed");
	Delay(2000);
}

void External_Set_Time_Date_Disp_Fn(void)
{
	LCD_Locate(1, 1);
	for(int i = 0; i<8; i++)
	{
		LCDData(Disp_RTC_Name[Disp_Cntrl.RTC_Index][i]);
	}
	LCDWriteString(" : ");
	LCDWrite_Unsigned_Int(Disp_RTC_Value[Disp_Cntrl.RTC_Index], 2);
}

void Time_Date_Disp_Fn(void)
{
	LCD_Locate(1, 1);

	LCDWriteString("Time");
	LCDWriteString(" :");
	LCDWrite_Unsigned_Int(Disp_RTC_Value[2], 2);
	LCDWriteString(":");
	LCDWrite_Unsigned_Int(Disp_RTC_Value[1], 2);
	LCDWriteString(":");
	LCDWrite_Unsigned_Int(Disp_RTC_Value[0], 2);

	LCD_Locate(2, 1);

	LCDWriteString("Date");
	LCDWriteString(" :");
	LCDWrite_Unsigned_Int(Disp_RTC_Value[3], 2);
	LCDWriteString(":");
	LCDWrite_Unsigned_Int(Disp_RTC_Value[4], 2);
	LCDWriteString(":");
	LCDWrite_Unsigned_Int(Disp_RTC_Value[5], 2);


}

void Error_State_Disp_Fn(void)
{
	if(U1Mast_App_Send_Flags.Meterng_Communication_eror==1)
	{
		LCD_Locate(1, 1);
		LL_GPIO_TogglePin(GPIOA,LL_GPIO_PIN_6 );
		LCDWriteString("Meterng_Comm._error");
		Delay(2000);
	}
	else if(U1Mast_App_Send_Flags.Setting_Communication_eror==1)
	{
		LCD_Locate(1, 1);

		LCDWriteString("Setting_Comm_error");
		LL_GPIO_TogglePin(GPIOA,LL_GPIO_PIN_6 );
		Delay(2000);
	}
	else if(U1Mast_App_Send_Flags.Calib_Communication_eror == 1)
	{
		LCD_Locate(1, 1);
		LL_GPIO_TogglePin(GPIOA,LL_GPIO_PIN_6 );
		LCDWriteString("Calibration_Comm_error");
		Delay(2000);

	}
}

void Display_Variables_Init()
{
	Disp_Metering_Value_Scaler[0] = 0;// no value
	Disp_Metering_Value_Scaler[1] = 0.26;//DC link voltage
	Disp_Metering_Value_Scaler[2] = 0.18228;//V PV
	Disp_Metering_Value_Scaler[3] = 0.023;//I PV
	Disp_Metering_Value_Scaler[4] = 0.01717;                       //0.00859;                         //PV KW   // changed
	Disp_Metering_Value_Scaler[5] = 0.01;//PV KWH
	Disp_Metering_Value_Scaler[6] = 0.119;//V Mains
	Disp_Metering_Value_Scaler[7] = 0.023;//I Inv Pri
	Disp_Metering_Value_Scaler[8] = 0;//I Mains CT
	Disp_Metering_Value_Scaler[9] = 1;//T Grid
	Disp_Metering_Value_Scaler[10] = 0.011210;                   //0.0056;                               //Grid KVA
	Disp_Metering_Value_Scaler[11] = 0.01;//Export KWH
	Disp_Metering_Value_Scaler[12] = 1;//Import KWH
}
