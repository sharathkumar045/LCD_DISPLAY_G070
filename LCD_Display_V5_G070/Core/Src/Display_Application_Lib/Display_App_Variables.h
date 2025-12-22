/*
 * Display_Variables.h
 *
 *  Created on: 17-May-2020
 *      Author: pc
 */
#include"stm32g0xx.h"
#ifndef DISPLAY_APP_VARIABLES_H_
#define DISPLAY_APP_VARIABLES_H_

extern const char Disp_Metering_Name[][10];
extern __IO uint16_t Disp_Metering_Value[];

extern const char Disp_Option_Name[][20];

extern const char Disp_Password_Name[];
extern __IO float Disp_Password_Value;

extern const char Disp_Metrng_Calib_Name[][10];
extern __IO uint16_t Disp_Metrng_Calib_Value[];

extern const char Disp_Desired_Metrng_Calib_Name[][15];
extern __IO uint16_t Disp_Desired_Metrng_Calib_Value[];

extern const char Disp_Calib_Name[][10];
extern __IO uint16_t Calib_Value[];

extern const char Disp_Setting_Name[][20];

extern __IO uint16_t Disp_Setting_Value[41];
extern __IO uint16_t Disp_New_Setting_Value[41];

extern __IO uint16_t Disp_Calib_Set_Value[];
extern __IO uint16_t Disp_Setting_Write_Value[41];

extern __IO float Disp_Metering_Value_Scaler[];
extern const float Disp_Calib_Value_Scaler[];
extern const float Disp_Setting_Value_Scaler[41];

extern const char Disp_RTC_Name[][10];
extern __IO int8_t Disp_RTC_Value[];







#endif /* DISPLAY_VARIABLES_H_ */
