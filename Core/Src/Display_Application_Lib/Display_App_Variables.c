/*
 * Variables.c
 *
 *  Created on: 15-May-2020
 *      Author: pc
 */

#include "stm32g0xx.h"
#include "Display_App_Variables.h"


  const char Disp_Metering_Name[22][10] = {"M","DC_Link   ","V_PV    ","I_PV    ","PV_KW  ","PV_KWH  ","V_Mains ","I_Inv   ",
		  	  	  	  	  	  	  	  	  "I_Mains ","F_Grid  ","Grid_KVA","Grid_KWH"," "," "," "," "," ","CRC"}; //25

  __IO float Disp_Metering_Value_Scaler[22] = {};

  __IO uint16_t Disp_Metering_Value[22] = {};

  const char Disp_Option_Name[5][20] = {"Calib","Setting","Reset","Time_Date","30_Days_Energy_Disp"};

  const char Disp_Password_Name[10] = {"Password"};
  __IO float Disp_Password_Value = 0;


  const char Disp_Metrng_Calib_Name[12][10] = {"C","V_Inv   ","V_Bat   ","I_Inv   ","I_Bat   ","V_PV    ","I_PV    ","V_Mains ","I_Mains_CT","I_Inv_CT"," ","CRC"};
  __IO uint16_t Disp_Metrng_Calib_Value[12] = {'C',2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,'C'};

  const char Disp_Desired_Metrng_Calib_Name[12][15] = {"C","Cal_V_Inv","Cal_V_Bat","Cal_I_Inv","Cal_I_Bat","Cal_V_PV","Cal_I_PV","Cal_V_Mains","C_I_Mains_CT ","C_I_Inv_CT "," ","CRC"};
  __IO uint16_t Disp_Desired_Metrng_Calib_Value[12] = {'C',2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,'C'};

  const char Disp_Calib_Name[12][10] = {"C","V_Inv","V_Bat","I_Inv","V_PV","I_PV","V_Mains"," "," "," ","CRC"};
  __IO uint16_t Calib_Value[12] = {'C',2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,'C'};
  __IO uint16_t Calib_Value_Updated[12] = {'C',2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,'C'};

//  __IO char Disp_New_Calib_Name[5][15] = {"NewBattVol","NewBattAmp","NewGridVol","NewGridAmp","NewPVVol"};
//  __IO uint16_t Disp_New_Calib_Value[5] = {2000,1500,3000,1000,2500};

  const char Disp_Setting_Name[41][20] = {"S","V_Inv_Ref","V_Inv_UL","V_Inv_LL","PV_Chg_V_Bat_Ref","V_Bat_H_Cutoff",
		  	  	  	  	  	  	  	  	  "V_Bat_H_Cutin","V_Bat_L_Cutin","V_Bat_L_Cutoff","I_Bat_Chg_UL","I_Inv_Full_Load",
										  "I_Inv_110_Load","I_Inv_125_Load","I_Inv_150_Load","I_Grid_Exp_Limit","I_Grid_Imp_Limit",
										  "PV_H_Cutoff","PV_H_Cutin","PV_L_Cutin","PV_L_Cutoff","I_PV_UL","V_Mains_H_Cutoff",
										  "V_Mains_H_Cutin","V_Mains_L_Cutin","V_Mains_L_Cutoff","V_Bat_Boost_Ref","V_Bat_Equlz_Ref",
										  "Bat_Equlztn_Rq","PV_Power_Limit","Mode","Grid_Conct_BV","Grid_Chg_Strt_BV",
										  "Grid_Chg_Stop_BV","Grid_Dis_BV","Grid_Dis._I_Bat","I_Chrg","Grid_Boost_Ref","Grid_Float_Ref","CRC"}; // 73

  __IO uint16_t Disp_Setting_Value[41] = {'S',1831,2165,1337,2765,3519,3368,2162,2011,2458,1639,1803,2049,2459,
		  	  	  	  	  	  	  	  	  1950,1950,2527,2359,505,421,1622,2633,2535,1755,1560,2900,2500,0,2000,
										  1,2500,2450,2500,2500,200,100,2500,2500,0,0,'C'};
  __IO uint16_t Disp_New_Setting_Value[41] = {'S',1831,2165,1337,2765,3519,3368,2162,2011,2458,1639,1803,2049,2459,
  	  	  	  	  	  	  	  	  	  	  	  1950,1950,2527,2359,505,421,1622,2633,2535,1755,1560,2900,2500,0,2000,
											  1,2500,2450,2500,2500,200,100,2500,2500,0,0,'C'};


  __IO uint16_t Disp_Calib_Set_Value[12] = {0};
  __IO uint16_t Disp_Setting_Write_Value[41] = {0};

//  const float Disp_Calib_Value_Scaler[12] = {0,0.25,0.2,0.25,0.35,0.25,0.2,0.15,0.2,0.3,0.2,0};
  const float Disp_Calib_Value_Scaler[12] = {0,0.25,0.2,0.023,0.35,0.18228,0.023,0.119,0,0.3,0.2,0};
  const float Disp_Setting_Value_Scaler[41] = {0,0.2,0.15,0.2,0.3,0.2,0.2,0.15,0.2,0.3,0.2,0.2,0.15,0.2,0.3,0.2,0.2,0.15,0.2,0.3,0.2,
		  	  	  	  	  	  	  	  	  	  	0.2,0.15,0.2,0.3,0.2,0.2,0.15,0.2,0.3,0.2,0.2,0.15,0.2,0.3,0.2,0.2,0.15,0.2,0.3,0};


  const char Disp_RTC_Name[6][10] = {"Seconds","Minutes","Hours","Day","Month","Year"};
  __IO int8_t Disp_RTC_Value[6] = {0,0,0,0,0,0};
