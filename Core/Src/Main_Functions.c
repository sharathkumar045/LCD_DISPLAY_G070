/*
 * General_Functions.c
 *
 *  Created on: 15-May-2020
 *      Author: pc
 */
#include "main.h"

#include "Main_Variables.h"
#include "Main_Functions.h"

#include "Display_App_Variables.h"
#include "Display_App_Functions.h"

#include "Switch_App_Variables.h"
#include "Switch_App_Functions.h"

#include "LCD16X2_Driver_Variables.h"
#include "LCD16X2_Driver_Functions.h"

#include "EEPROM_App_Functions.h"
#include "EEPROM_App_Variables.h"

#include "EEPROM_Drv_Functions.h"
#include "EEPROM_Drv_Variables.h"

#include "UART1_Mast_App_Functions.h"
#include "UART1_Mast_App_Variables.h"

#include "UART1_Mast_Drv_Functions.h"
#include "UART1_Mast_Drv_Variables.h"

#include "RTC_Drv_Functions.h"
#include "RTC_Drv_Variables.h"


void WhileLoop_Display_Menu_Fns(uint8_t Id)
{
	switch(Id)
	{
	case 1:

		LCDGotoXY(0, 1);
		LCDWriteString("Metering");

		break;

	case 2:

		LCDGotoXY(0, 1);
		LCDWriteString("Metering_Data_Rq");

		break;

	case 3:

		LCDGotoXY(0, 1);
		LCDWriteString("Option");
		break;

	case 4:

		LCDGotoXY(0, 1);
		LCDWriteString("password");
		break;


	case 5:

		LCDGotoXY(0, 1);
		LCDWriteString("calibration");
		break;

	case 6:

		LCDGotoXY(0, 1);
		LCDWriteString("Calib_Update_and_Send");
		break;

	case 7:

		LCDGotoXY(0, 1);
		LCDWriteString("Setting");
		break;

	case 8:

		LCDGotoXY(0, 1);
		LCDWriteString("Setting_Send_Data");
		break;

	case 9:

		LCDGotoXY(0, 1);
		LCDWriteString("Setting_Data_Rq");
		break;

	case 10:

		LCDGotoXY(0, 1);
		LCDWriteString("Save_Setting_in_EEPROM");

		break;

	case 11:

		LCDGotoXY(0, 1);
		LCDWriteString("User_Reset");


		break;

	case 12:

		LCDGotoXY(0, 1);
		LCDWriteString("Daily_Reset");

		break;

	case 13:

		LCDGotoXY(0, 1);
		LCDWriteString("Send_Reset_Rq");

		break;

	case 14:

		LCDGotoXY(0, 1);
		LCDWriteString("Ext_RTC_Set_Time_Date");

		break;

	case 15:

		LCDGotoXY(0, 1);
		LCDWriteString("Error");


		break;
	default:
		LCDGotoXY(0, 1);
		LCDWriteString("Metering");

		break;
	}

}

void Whileloop_State_Fn()
{
	switch(State)
	{
		case Metering :
							Whileloop_Metering_Fn();

			break;

		case Metering_Data_Rq :
							Whileloop_Metering_Data_Rq_Fn();

			break;

		case Option:
							Whileloop_Option_Fn();
			break;

		case Password:
							Whileloop_Password_Fn();

			break;

		case Calibration:
							Whileloop_Calibration_Fn();

			break;

		case Calib_Update_and_Send:
							Whileloop_Calib_Update_and_Send_Fn();

			break;

		case Setting:
							Whileloop_Setting_Fn();

			break;

		case Setting_Send_Data:
							Whileloop_Setting_Send_Data_Fn();

			break;

		case Setting_Data_Rq:
							Whileloop_Setting_Data_Rq_EEPROM_Fn();

			break;

		case Save_Setting_in_EEPROM:
							Whileloop_Save_Setting_in_EEPROM_Fn();

			break;

		case User_Reset:
							Whileloop_User_Reset_Fn();

			break;

		case Daily_Reset:
							Whileloop_Daily_Reset_Fn();

			break;

		case Send_Reset_Rq:
							Whileloop_Send_Reset_Rq_Fn();

			break;

		case Ext_RTC_Set_Time_Date:

							Whileloop_Ext_RTC_Set_Time_Date_Fn();
			break;

		case RTC_Disp_Time_Date:

							Whileloop_Disp_Time_Date_Fn();
			break;

		case Error:
							Whileloop_Error_Fn();
			break;

		default : State = Metering;
			break;
	}
}

void Whileloop_Metering_Fn()
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		Disp_Cntrl.Mtrng_Index = 1;
		LCD_Clear_Display();
		Disp_Cntrl.First_Time_State_Entry = 0;
	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		if(Switch_Detect_Incrmnt_Btn.Pressed == 1)
		{
			Disp_Cntrl.Mtrng_Index = Disp_Cntrl.Mtrng_Index + 1;
			if(Disp_Cntrl.Mtrng_Index > Disp_Cntrl.Mtrng_Max_Index)
			{
				State = RTC_Disp_Time_Date;
				Disp_Cntrl.First_Time_State_Entry = 1;
				//Disp_Cntrl.Mtrng_Index = 1;
			}
			Switch_Detect_Incrmnt_Btn.Pressed = 0;
		}

		else if(Switch_Detect_Decrmnt_Btn.Pressed == 1)
		{
			Disp_Cntrl.Mtrng_Index = Disp_Cntrl.Mtrng_Index - 1;
			if(Disp_Cntrl.Mtrng_Index <  1)
			{
				Disp_Cntrl.Mtrng_Index = Disp_Cntrl.Mtrng_Max_Index;
			}
			Switch_Detect_Decrmnt_Btn.Pressed = 0;
		}

		else if(Switch_Detect_Set_Enter_Btn.Pressed == 1)
		{
			State = Password;
			Disp_Cntrl.First_Time_State_Entry = 1;
			Switch_Detect_Set_Enter_Btn.Pressed = 0;
		}
		else
		{

		}

		Metering_State_Disp_Fn();
	}
}

void Whileloop_Option_Fn()
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		LCD_Clear_Display();
		Disp_Cntrl.Optn_Index = 0;
		Disp_Cntrl.First_Time_State_Entry = 0;
	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{

		if(Switch_Detect_Incrmnt_Btn.Pressed == 1)
		{
			Disp_Cntrl.Optn_Index = Disp_Cntrl.Optn_Index + 1;
			if(Disp_Cntrl.Optn_Index > Disp_Cntrl.Optn_Max_Index)
			{
				Disp_Cntrl.Optn_Index = 0;
			}
			Switch_Detect_Incrmnt_Btn.Pressed = 0;
		}

		else if(Switch_Detect_Decrmnt_Btn.Pressed == 1)
		{
			Disp_Cntrl.Optn_Index = Disp_Cntrl.Optn_Index - 1;
			if(Disp_Cntrl.Optn_Index <  0)
			{
				Disp_Cntrl.Optn_Index = Disp_Cntrl.Optn_Max_Index;
			}
			Switch_Detect_Decrmnt_Btn.Pressed = 0;
		}

		else if(Switch_Detect_Enter_Btn.Long_Press == 1)
		{
			if(Disp_Cntrl.Optn_Index == 0)
			{
				State = Calibration;
				Disp_Cntrl.First_Time_State_Entry = 1;
			}
			else if(Disp_Cntrl.Optn_Index == 1)
			{
				State = Setting;
				Disp_Cntrl.First_Time_State_Entry = 1;
			}
			else if(Disp_Cntrl.Optn_Index == 2)
			{
				State = User_Reset;
				Disp_Cntrl.First_Time_State_Entry = 1;
			}
			else if(Disp_Cntrl.Optn_Index == 3)
			{
				State = Ext_RTC_Set_Time_Date;
				Disp_Cntrl.First_Time_State_Entry = 1;
			}
			else
			{
				State = Mtrng_Energy_Disp_1Mnth;
				Disp_Cntrl.First_Time_State_Entry = 1;
			}
			Switch_Detect_Enter_Btn.Long_Press = 0;
		}

		else if(Switch_Detect_Set_Enter_Btn.Pressed == 1)
		{
			State = Metering;
			Disp_Cntrl.First_Time_State_Entry = 1;
			Switch_Detect_Set_Enter_Btn.Pressed = 0;
		}
		else
		{

		}
		Option_State_Disp_Fn();

	}
}

void Whileloop_Password_Fn()
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		LCD_Clear_Display();
		Disp_Cntrl.Pswrd_Index = 0;
		Disp_Cntrl.First_Time_State_Entry = 0;

	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		if(Switch_Detect_Set_Enter_Btn.Pressed == 1)
		{
			State = Option;
			Switch_Detect_Set_Enter_Btn.Pressed = 0;
			Disp_Cntrl.First_Time_State_Entry = 1;
		}
		Password_State_Disp_Fn();
	}
}

void Whileloop_Calibration_Fn()
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		LCD_Clear_Display();
		Disp_Cntrl.Calib_Index = 1;
		Disp_Cntrl.First_Time_State_Entry = 0;
	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		if(Switch_Detect_Incrmnt_Btn.Pressed == 1)
		{
			Disp_Desired_Metrng_Calib_Value[Disp_Cntrl.Calib_Index] =  Disp_Desired_Metrng_Calib_Value[Disp_Cntrl.Calib_Index] + 10;
			 Switch_Detect_Incrmnt_Btn.Pressed = 0 ;

		}

		else if(Switch_Detect_Decrmnt_Btn.Pressed == 1)
		{
			Disp_Desired_Metrng_Calib_Value[Disp_Cntrl.Calib_Index] =  Disp_Desired_Metrng_Calib_Value[Disp_Cntrl.Calib_Index] - 10;
			 Switch_Detect_Decrmnt_Btn.Pressed = 0;
		}

		else if(Switch_Detect_Set_Btn.Shrt_Press == 1)
		{
			//Disp_Calib_Set_Value[Disp_Cntrl.Calib_Index] = Disp_Calib_Value[Disp_Cntrl.Calib_Index];
			Switch_Detect_Set_Btn.Shrt_Press = 0 ;
		}

		else if(Switch_Detect_Enter_Btn.Shrt_Press == 1)
		{
			Disp_Cntrl.Calib_Index = Disp_Cntrl.Calib_Index + 1;
			if(Disp_Cntrl.Calib_Index > Disp_Cntrl.Calib_Max_Index)
			{
				Disp_Cntrl.Calib_Index = 1;
			}
			Switch_Detect_Enter_Btn.Shrt_Press = 0;
		}

		else if(Switch_Detect_Set_Enter_Btn.Pressed == 1)
		{
			State = Calib_Update_and_Send;
			Disp_Cntrl.First_Time_State_Entry = 1;
			Switch_Detect_Set_Enter_Btn.Pressed = 0;
		}
		else
		{

		}

		Calib_Value[Disp_Cntrl.Calib_Index] = Disp_Desired_Metrng_Calib_Value[Disp_Cntrl.Calib_Index];
//        Calib_Value_Updated[Disp_Cntrl.Calib_Index] = Disp_Desired_Metrng_Calib_Value[Disp_Cntrl.Calib_Index];
		Calibration_State_Disp_Fn();

	}
}

void Whileloop_Calib_Update_and_Send_Fn(void)
{
	if(Disp_Cntrl.First_Time_State_Entry)
	{
		LCD_Clear_Display();

		U1Mast_App_Populate_And_Send_Txdata_Array_With_Zeros_Calib();

			Disp_Cntrl.First_Time_State_Entry = 0;


	}
	if((Disp_Cntrl.First_Time_State_Entry == 0) && (U1Mast_App_Rec_Flags.Received_Message_c == 1))
	{
		Calibration_Update();
		U1Mast_App_Populate_And_Send_Txdata_Array_With_Msg_Calib();
		LCDWriteString("Calibrating...");
		if(U1Mast_App_Rec_Flags.Received_Message_c_again == 1)
		{
			State = Metering;
			U1Mast_App_Rec_Flags.Received_Message_c_again = 0;
			Disp_Cntrl.First_Time_State_Entry = 0;
		}
		else
		{
			State = Error;
			Disp_Cntrl.First_Time_State_Entry = 1;
			U1Mast_App_Send_Flags.Calib_Communication_eror = 1;
		}
	}
}

void Calibration_Update(void)
{


	for(int i = 1; i <11; i++)
	{
		if(Disp_Metrng_Calib_Value[i] > 0)
		{

			uint32_t temp;
			temp = (uint32_t)Calib_Value[i] * (uint32_t)Disp_Desired_Metrng_Calib_Value[i];
			temp = temp/Disp_Metrng_Calib_Value[i];
			Calib_Value[i] = (uint16_t)temp;



//			Calib_Value[i]  = Calib_Value[i] * ((float)Disp_Desired_Metrng_Calib_Value[i]/(float)Disp_Metrng_Calib_Value[i]);
		}
	}
}

void Whileloop_Setting_Fn()
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		LCD_Clear_Display();
		Disp_Cntrl.Settng_Index = 1;
		Disp_Cntrl.First_Time_State_Entry = 0;
	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		if(Switch_Detect_Incrmnt_Btn.Pressed == 1)
		{
			Disp_New_Setting_Value[Disp_Cntrl.Settng_Index] =  Disp_New_Setting_Value[Disp_Cntrl.Settng_Index] + 2;
			 Switch_Detect_Incrmnt_Btn.Pressed = 0 ;
		}

		else if(Switch_Detect_Decrmnt_Btn.Pressed == 1)
		{
			Disp_New_Setting_Value[Disp_Cntrl.Settng_Index] =  Disp_New_Setting_Value[Disp_Cntrl.Settng_Index] - 2;
			 Switch_Detect_Decrmnt_Btn.Pressed = 0;
		}

		else if(Switch_Detect_Enter_Btn.Shrt_Press == 1)
		{
			Disp_Cntrl.Settng_Index = Disp_Cntrl.Settng_Index + 1;
			if(Disp_Cntrl.Settng_Index > Disp_Cntrl.Settng_Max_Index)
			{
				Disp_Cntrl.Settng_Index = 1;
			}
			Switch_Detect_Enter_Btn.Shrt_Press = 0;

		}

		else if(Switch_Detect_Set_Enter_Btn.Pressed == 1)
		{
			State = Save_Setting_in_EEPROM;
			EEPROM_App_Flags.Write_Settings_Req = 1;
			Disp_Cntrl.First_Time_State_Entry = 1;
			Switch_Detect_Set_Enter_Btn.Pressed = 0;
		}
		else
		{

		}
		Disp_Setting_Write_Value[Disp_Cntrl.Settng_Index] =  Disp_New_Setting_Value[Disp_Cntrl.Settng_Index];


		Settings_State_Disp_Fn();

	}
}

void Whileloop_Setting_Data_Rq_EEPROM_Fn(void)
{
	if(Disp_Cntrl.First_Time_State_Entry ==1)
	{
		LCD_Clear_Display();
		Disp_Cntrl.First_Time_State_Entry = 0;
	}

	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		// Data retrieve from EEPROM fn has to be placed
		Settings_Data_Rq_EEPROM_Disp_Fn();
		EEPROM_App_Read_Settings();
		Delay(1000);

		if(EEPROM_App_Flags.Read_Error == 0)
		{
			Disp_Setting_Value[0] = (uint16_t)(EEPROM_Read_Array[0]);  // Index 0 is S

			__IO uint8_t j = 1;
			for(int i =1; i<78 ; i = i+2)
			{
				Disp_Setting_Value[j] = (uint16_t)(EEPROM_Read_Array[i])|((uint16_t)(EEPROM_Read_Array[i+1])<<8);
				j = j+1;
			}
			Disp_Setting_Value[40] = (uint16_t)(EEPROM_Read_Array[79]); // index 79 is CRC

			for(int i =0; i <41 ; i++)
			{
				Disp_New_Setting_Value[i] = Disp_Setting_Value[i];
			}

			State = Setting_Send_Data;
			Disp_Cntrl.First_Time_State_Entry = 1;
		}
		else if(EEPROM_App_Flags.Read_Error == 1)
		{
			State = Setting;
			Disp_Cntrl.First_Time_State_Entry = 1;
			LCD_Clear_Display();
		}
		else
		{

		}
	}
}

void Whileloop_Save_Setting_in_EEPROM_Fn()
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		LCD_Clear_Display();
		Disp_Cntrl.First_Time_State_Entry = 0;
	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{

		//Disp_Setting_Write_Value[40] =(uint16_t) U1Mast_Drv_crcFast(Disp_Setting_Write_Value,40);

		EEPROM_Write_Array[0] = 0xff & Disp_Setting_Write_Value[0];
		__IO uint8_t j = 1;
		for(int i=1; i<79;i = i+2)
		{
			EEPROM_Write_Array[i] = 0xff & Disp_Setting_Write_Value[j];
			EEPROM_Write_Array[i + 1] = (0xff & Disp_Setting_Write_Value[j])>>8;
			j = j + 1;
		}
		EEPROM_Write_Array[79] = (uint8_t) U1Mast_Drv_crcFast(EEPROM_Write_Array,79);

		EEPROM_App_Write_Settings();

		Save_Settings_in_EEPROM_Settings_State_Disp_Fn();

		if(1)
		{
			State = Setting_Data_Rq;
			EEPROM_App_Flags.Read_Settings_Req = 1;
			Disp_Cntrl.First_Time_State_Entry = 1;
		}
	}
}

void Whileloop_User_Reset_Fn()
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		LCD_Clear_Display();
		U1Mast_App_Populate_And_Send_Txdata_Array_With_Msg_RESET();
		Disp_Cntrl.First_Time_State_Entry = 0;
	}
	//Initially the data will be stored in EEPROM
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		if(U1Mast_App_Rec_Flags.Received_Message_r == 1)
		{
			Reset_Send_Rq_State_Disp_Fn();
			State = Metering;
			U1Mast_App_Rec_Flags.Received_Message_r = 0;
			Disp_Cntrl.First_Time_State_Entry = 1;
		}
	}
}

void Whileloop_Daily_Reset_Fn()
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		LCD_Clear_Display();
		EEPROM_App_Var.Mtrng_Energy_Cntr =  EEPROM_Drv_Read_Byte(EEPROM_App_Metering_Cntr_Start_Addr);
		if(EEPROM_App_Var.Mtrng_Energy_Cntr > 31)
		{
			EEPROM_App_Flags.Read_Metering_Req = 1;
			EEPROM_App_Read_Metering();
			EEPROM_App_Var.Mtrng_Energy_Cntr = 0;
			EEPROM_Drv_Write_Byte(EEPROM_App_Metering_Cntr_Start_Addr , EEPROM_App_Var.Mtrng_Energy_Cntr);
		}
		Disp_Cntrl.First_Time_State_Entry = 0;
		EEPROM_App_Flags.Write_Metering_Req = 1;
	}
	//Initially the data will be stored in EEPROM
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		EEPROM_Write_Array[0] = Disp_RTC_Value[3];
		EEPROM_Write_Array[1] = Disp_RTC_Value[4];
		EEPROM_Write_Array[2] = Disp_RTC_Value[5];
//		EEPROM_Write_Array[3] = 100;
//		EEPROM_Write_Array[4] = 10;
//		EEPROM_Write_Array[5] = 5;
//		EEPROM_Write_Array[6] = 20;
		EEPROM_Write_Array[7] = (uint8_t) U1Mast_Drv_crcFast(EEPROM_Write_Array,7);

		EEPROM_App_Write_Metering();
		if(EEPROM_App_Flags.Write_Metering_Req == 0)
		{
			EEPROM_App_Var.Mtrng_Energy_Cntr = EEPROM_App_Var.Mtrng_Energy_Cntr + 1;
			EEPROM_Drv_Write_Byte(EEPROM_App_Metering_Cntr_Start_Addr , EEPROM_App_Var.Mtrng_Energy_Cntr);
			Reset_State_Disp_Fn();
			State = Send_Reset_Rq;
			Disp_Cntrl.First_Time_State_Entry = 1;
		}
	}
}

void Whileloop_Send_Reset_Rq_Fn()
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		LCD_Clear_Display();
		Disp_Cntrl.First_Time_State_Entry = 0;
		U1Mast_App_Populate_And_Send_Txdata_Array_With_Msg_RESET();
	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		// later the reset is sent to the MCU and after recieving the r it will again go to metering
		if(U1Mast_App_Rec_Flags.Received_Message_r == 1)
		{
			Reset_Send_Rq_State_Disp_Fn();
			State = Metering;
			U1Mast_App_Rec_Flags.Received_Message_r = 0;
			Disp_Cntrl.First_Time_State_Entry = 1;
		}

	}
}

void Whileloop_Ext_RTC_Set_Time_Date_Fn(void)
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		LCD_Clear_Display();

		RTC_Drv_Get_Ext_Date_Time();
		Disp_RTC_Value[0] = RTC_Drv_Ext_Time.Seconds;
		Disp_RTC_Value[1] = RTC_Drv_Ext_Time.Minutes;
		Disp_RTC_Value[2] = RTC_Drv_Ext_Time.Hours;
		Disp_RTC_Value[3] = RTC_Drv_Ext_Time.Day;
		Disp_RTC_Value[4] = RTC_Drv_Ext_Time.Month;
		Disp_RTC_Value[5] = RTC_Drv_Ext_Time.Year;

		Disp_Cntrl.RTC_Index = 1;
		Disp_Cntrl.First_Time_State_Entry =0;
	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		if(Switch_Detect_Incrmnt_Btn.Pressed == 1)
		{
			Disp_RTC_Value[Disp_Cntrl.RTC_Index] = Disp_RTC_Value[Disp_Cntrl.RTC_Index] + 1;

			if(Disp_RTC_Value[1] > 59) // Limiting the minutes
			{
				Disp_RTC_Value[1] = 0;
			}
			else if (Disp_RTC_Value[2] > 23) //Limiting the hours
			{
				Disp_RTC_Value[2] = 0;
			}
			else if (Disp_RTC_Value[3] > 31) // Limiting the date
			{
				Disp_RTC_Value[3] = 1;
			}
			else if (Disp_RTC_Value[4] > 12) // Limiting the month
			{
				Disp_RTC_Value[4] = 1;
			}
			else if (Disp_RTC_Value[5] > 99) // Limiting the year
			{
				Disp_RTC_Value[5] = 0;
			}
			else
			{

			}
			Switch_Detect_Incrmnt_Btn.Pressed = 0;
		}

		else if(Switch_Detect_Decrmnt_Btn.Pressed == 1)
		{
			Disp_RTC_Value[Disp_Cntrl.RTC_Index] = Disp_RTC_Value[Disp_Cntrl.RTC_Index] - 1;

			if(Disp_RTC_Value[1] < 0) // Limiting the minutes
			{
				Disp_RTC_Value[1] = 59;
			}
			else if (Disp_RTC_Value[2] < 0) //Limiting the hours
			{
				Disp_RTC_Value[2] = 23;
			}
			else if (Disp_RTC_Value[3] < 1) // Limiting the date
			{
				Disp_RTC_Value[3] = 31;
			}
			else if (Disp_RTC_Value[4] < 1) // Limiting the month
			{
				Disp_RTC_Value[4] = 12;
			}
			else if (Disp_RTC_Value[5] < 0) // Limiting the year
			{
				Disp_RTC_Value[5] = 99;
			}
			else
			{

			}
			Switch_Detect_Decrmnt_Btn.Pressed = 0;
		}

		else if(Switch_Detect_Enter_Btn.Shrt_Press == 1)
		{
			Disp_Cntrl.RTC_Index = Disp_Cntrl.RTC_Index + 1;
			if(Disp_Cntrl.RTC_Index > Disp_Cntrl.RTC_Max_Index)
			{
				Disp_Cntrl.RTC_Index = 1;
			}
			Switch_Detect_Enter_Btn.Shrt_Press = 0;
		}

		else if(Switch_Detect_Set_Enter_Btn.Pressed == 1)
		{
			RTC_Drv_Ext_Time.Minutes = Disp_RTC_Value[1] ;
			RTC_Drv_Ext_Time.Hours = Disp_RTC_Value[2];
			RTC_Drv_Ext_Time.Day = Disp_RTC_Value[3];
			RTC_Drv_Ext_Time.Month = Disp_RTC_Value[4];
			RTC_Drv_Ext_Time.Year = Disp_RTC_Value[5];
			RTC_Drv_Set_Ext_Date_Time();
			State = RTC_Disp_Time_Date;
			Disp_Cntrl.First_Time_State_Entry = 1;
			Switch_Detect_Set_Enter_Btn.Pressed = 0;
		}
		else
		{

		}

		External_Set_Time_Date_Disp_Fn();
	}

}

void Whileloop_Disp_Time_Date_Fn(void)
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		LCD_Clear_Display();
		RTC_Drv_Get_Ext_Date_Time();
		Disp_RTC_Value[0] = RTC_Drv_Ext_Time.Seconds;
		Disp_RTC_Value[1] = RTC_Drv_Ext_Time.Minutes;
		Disp_RTC_Value[2] = RTC_Drv_Ext_Time.Hours;
		Disp_RTC_Value[3] = RTC_Drv_Ext_Time.Day;
		Disp_RTC_Value[4] = RTC_Drv_Ext_Time.Month;
		Disp_RTC_Value[5] = RTC_Drv_Ext_Time.Year;

		Disp_Cntrl.RTC_Index = 0;
		Disp_Cntrl.First_Time_State_Entry =0;
	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		Time_Date_Disp_Fn();
		Delay(2000);
		Disp_Cntrl.Mtrng_Index = 1;
		State = Metering;
		Disp_Cntrl.First_Time_State_Entry = 1;

	}
}

void Whileloop_Energy_Mtrng_Disp_1Mnth(void)
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		Disp_Cntrl.First_Time_State_Entry = 0;
	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		EEPROM_App_Var.Mtrng_Energy_Cntr =  EEPROM_Drv_Read_Byte(EEPROM_App_Metering_Cntr_Start_Addr);
		EEPROM_App_Flags.Read_Metering_Req = 1;
		EEPROM_App_Read_Metering();
		State = Metering;
		Disp_Cntrl.First_Time_State_Entry = 1;
	}

}

void Whileloop_Error_Fn(void)
{
	if(Disp_Cntrl.First_Time_State_Entry == 1)
	{
		LCD_Clear_Display();
		Disp_Cntrl.First_Time_State_Entry = 0;
		////////////////////////////////////////////////////
//		U1Mast_App_Send_Flags.Setting_Communication_eror =0;
	}
	if(Disp_Cntrl.First_Time_State_Entry == 0)
	{
		Error_State_Disp_Fn();
		if(U1Mast_App_Send_Flags.Meterng_Communication_eror == 1)
		{
			State = Metering_Data_Rq;
			U1Mast_App_Send_Flags.Meterng_Communication_eror = 0;
			Disp_Cntrl.First_Time_State_Entry =1;
		}
		else if(U1Mast_App_Send_Flags.Setting_Communication_eror == 1)
		{
			State = Setting_Send_Data;
			U1Mast_App_Send_Flags.Setting_Communication_eror = 0;
			Disp_Cntrl.First_Time_State_Entry = 1;
		}
		else if(U1Mast_App_Send_Flags.Calib_Communication_eror == 1)
		{
			State = Calib_Update_and_Send;
			U1Mast_App_Send_Flags.Calib_Communication_eror = 0;
			Disp_Cntrl.First_Time_State_Entry = 1;

		}

	}

}

void Main_Variables_Init(void)
{
	Disp_Cntrl.First_Time_State_Entry = 1;

	Disp_Cntrl.Calib_Max_Index = 9;
	Disp_Cntrl.Mtrng_Max_Index = 11;
	Disp_Cntrl.Settng_Max_Index = 37;
	//Disp_Cntrl.Reset_Max_Index = 4;
	Disp_Cntrl.Optn_Max_Index = 4;
	Disp_Cntrl.RTC_Max_Index = 5;

}
