
/*
 * UART_Communication_Functions.c
 *
 *  Created on: Apr 19, 2019
 *      Author: krishna
 */
#ifndef __UART1_Mast_Functions_H
#define __UART1_Mast_Functions_H

#ifdef __cplusplus
 extern "C" {
#endif




#include "usart.h"


void Whileloop_Metering_Data_Rq_Fn(void);

void U1Mast_App_Populate_And_Send_Txdata_Array_With_Message_Request_Metering(void);

void Whileloop_Setting_Send_Data_Fn(void);

void U1Mast_App_Populate_And_Send_Txdata_Array_With_Message_Settings(void);

void U1Mast_App_Store_Received_Data_In_Variables(void);

void U1Mast_App_Populate_And_Send_Txdata_Array_With_Zeros_Calib(void);

void U1Mast_App_Populate_And_Send_Txdata_Array_With_Msg_Calib(void);

void U1Mast_App_Populate_And_Send_Txdata_Array_With_Msg_RESET(void);

void U1Mast_App_Update_Variables_if_Mesage_is_m(void);

void U1Mast_App_Update_Variables_if_Mesage_is_S(void);

void U1Mast_App_Update_Variables_if_Mesage_is_c(void);

void U1Mast_App_Update_Variables_if_Mesage_is_r(void);

void U1Mast_App_Use_Received_Data_m(void);

void U1Mast_App_Use_Received_Data_c(void);

void UART1_Master_Variables_Init(void);
  
void Display_to_Inverter(void);

#ifdef __cplusplus
}
#endif
#endif //__UART1_Mast_Functions_H
