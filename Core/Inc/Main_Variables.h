/*
 * Display_Variables.h
 *
 *  Created on: 17-May-2020
 *      Author: pc
 */
#include"stm32g0xx.h"
#ifndef DISPLAY_VARIABLES_H_
#define DISPLAY_VARIABLES_H_

#define Two_Sec 2000
#define Three_Sec 3000
#define Five_Sec 5000
#define Ten_Sec 10000


enum State_Cntrl{
	Metering = 0,
	Metering_Data_Rq,
	Option,
	Password,
	Calibration,
	Calib_Update_and_Send,
	Setting,
	Setting_Data_Rq,
	Save_Setting_in_EEPROM,
	Setting_Send_Data,
	User_Reset,
	Daily_Reset,
	Send_Reset_Rq,
	Ext_RTC_Set_Time_Date,
	RTC_Disp_Time_Date,
	Mtrng_Energy_Disp_1Mnth,
	Error,
};
extern enum State_Cntrl State;

struct Display_Cntrl_Variables{


	__IO uint16_t Timer_Count;
	__IO uint16_t Reset_Time_Count;
	__IO unsigned First_Time_State_Entry:1;

	__IO int16_t Mtrng_Index;
	__IO int16_t Optn_Index;
	__IO int16_t Pswrd_Index;
	__IO int16_t Calib_Index;
	__IO int16_t Settng_Index;
	__IO int16_t Reset_Index;
	__IO int16_t RTC_Index;

	__IO uint16_t Mtrng_Max_Index;
	__IO uint16_t Optn_Max_Index;
	__IO uint16_t Pswrd_Max_Index;
	__IO uint16_t Calib_Max_Index;
	__IO uint16_t Settng_Max_Index;
	__IO uint16_t Reset_Max_Index;
	__IO uint16_t RTC_Max_Index;

	__IO uint16_t Rtrn_to_State;
	__IO uint16_t Prev_State;

	__IO uint16_t Metering_Rqst_Count;
};
extern struct Display_Cntrl_Variables Disp_Cntrl;

struct Debug_Variables{

	__IO uint16_t A;
	__IO uint16_t B;
	__IO uint16_t C;
	__IO uint16_t D;
	__IO uint16_t E;
	__IO uint16_t F;
	__IO uint16_t G;
	__IO uint16_t H;

};
extern struct Debug_Variables Debug;


//struct Scroll_Ctrl{
//	__IO uint8_t Inc_Btn_Cntr;
//	__IO uint8_t Dec_Btn_Cntr;
//	__IO uint8_t Id;
//};
//
//extern struct Scroll_Ctrl;
//struct Disp_EEPROM_Cntrl_Flags{
//
//	__IO unsigned Calib_Store_Rq:1;
//	__IO unsigned Calib_Retrieve_Rq:1;
//	__IO unsigned Energy_Store_Rq:1;
//	__IO unsigned Energy_Retrieve_Rq:1;
//	__IO unsigned Settngs_Store_Rq:1;
//	__IO unsigned Settngs_Retrieve_Rq:1;
//	__IO unsigned Error:1;
//
//};
//extern struct Disp_EEPROM_Cntrl_Flags Disp_EEPROM_Flag;
//
//struct Disp_EEPROM_Cntrl_Variables{
//
//	__IO uint16_t Device_Address_7bit;
//	__IO uint16_t Calib_Store_Start_Address;
//	__IO uint16_t Calib_Store_End_Address;
//	__IO uint16_t Energy_Store_Start_Address;
//	__IO uint16_t Energy_Store_End_Address;
//	__IO uint16_t Settngs_Store_Start_Address;
//	__IO uint16_t Settngs_Store_End_Address;
//
//};
//extern struct Disp_EEPROM_Cntrl_Variables Disp_EEPROM;
//
//struct Disp_RTC_Cntrl_Variables{
//
//	__IO uint16_t Time_to_be_Set_Secs;
//	__IO uint16_t Time_to_be_Set_Mins;
//	__IO uint16_t Time_to_be_Set_Hrs;
//	__IO uint16_t Date_to_be_Set_Day;
//	__IO uint16_t Date_to_be_Set_Mnth;
//	__IO uint16_t Date_to_be_Set_Year;
//
//	__IO unsigned Date_Set_Rq:1;
//	__IO unsigned Time_Set_Rq:1;
//
//	__IO uint16_t Time_Retrieved_Secs;
//	__IO uint16_t Time_Retrieved_Mins;
//	__IO uint16_t Time_Retrieved_Hrs;
//	__IO uint16_t Date_Retrieved_Day;
//	__IO uint16_t Date_Retrieved_Mnth;
//	__IO uint16_t Date_Retrieved_Year;
//
//	__IO unsigned Error:1;
//
//};
//extern struct Disp_RTC_Cntrl_Variables Disp_RTC_Cntrl;

#endif /* DISPLAY_VARIABLES_H_ */
