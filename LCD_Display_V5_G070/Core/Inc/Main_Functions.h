/*
 * User_Defined_Functions.h
 *
 *  Created on: 15-May-2020
 *      Author: pc
 */

#ifndef USER_DEFINED_FUNCTIONS_H_
#define USER_DEFINED_FUNCTIONS_H_



void WhileLoop_Display_Menu_Fns(uint8_t Id);

void Whileloop_State_Fn(void);

void Whileloop_Metering_Fn(void);

void Whileloop_Metering_Rq_Data_Fn(void);

void Whileloop_Option_Fn(void);

void Whileloop_Password_Fn(void);

void Whileloop_Calibration_Fn(void);

void Whileloop_Calib_Update_and_Send_Fn(void);

void Calibration_Update(void);

void Whileloop_Setting_Fn(void);

void Whileloop_Setting_Data_Rq_EEPROM_Fn(void);

void Whileloop_Save_Setting_in_EEPROM_Fn(void);

void Whileloop_User_Reset_Fn(void);

void Whileloop_Daily_Reset_Fn(void);

void Whileloop_Send_Reset_Rq_Fn(void);

void Whileloop_Ext_RTC_Set_Time_Date_Fn(void);

void Whileloop_Disp_Time_Date_Fn (void);

void Whileloop_Energy_Mtrng_Disp_1Mnth(void);

void Whileloop_Error_Fn(void);

void Main_Variables_Init(void);


#endif /* USER_DEFINED_FUNCTIONS_H_ */
