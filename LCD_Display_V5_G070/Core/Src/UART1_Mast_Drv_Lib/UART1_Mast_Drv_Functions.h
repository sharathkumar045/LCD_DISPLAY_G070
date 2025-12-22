
/*
 * UART_Communication_Functions.c
 *
 *  Created on: Apr 19, 2019
 *      Author: krishna
 */
#ifndef __UART1_Mast_Drv_Functions_H
#define __UART1_Mast_Drv_Functions_H

#ifdef __cplusplus
 extern "C" {
#endif




#include "usart.h"


void UART1_Store_Received_Data_In_Variables(void);

unsigned char U1Mast_Drv_crcFast(unsigned char message[],unsigned int nbyte);


void U1Mast_Drv_Receive_ISR_Program(void);

void U1Mast_Drv_Send_Function_Inside_Timer_Interrupt(void); ///put this code in timer interrupt which is called every 200uS or so

void U1Mast_Drv_Variables_Init(void);
  


#ifdef __cplusplus
}
#endif
#endif //__UART1_Mast_Functions_H
