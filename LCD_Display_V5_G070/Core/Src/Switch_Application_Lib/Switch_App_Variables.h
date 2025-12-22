/*
 * Display_Variables.h
 *
 *  Created on: 17-May-2020
 *      Author: pc
 */
#include "stm32g0xx.h"

#ifndef SWITCH_APP_VARIABLES_H_
#define SWITCH_APP_VARIABLES_H_

#define Inc_Bttn_Pressed ((GPIOB->IDR)&GPIO_IDR_ID10)
#define Dec_Bttn_Pressed ((GPIOB->IDR)&GPIO_IDR_ID2)
#define Set_Bttn_Pressed ((GPIOB->IDR)&GPIO_IDR_ID11)
#define Enter_Bttn_Pressed ((GPIOB->IDR)&GPIO_IDR_ID1)
#define Set_and_Enter_Bttn_Pressed ((Set_Bttn_Pressed)&&(Enter_Bttn_Pressed))

extern __IO uint8_t ID;

struct Switch_Cntrl_Variables{

	__IO uint16_t Cntr ;
	__IO unsigned Pressed:1;
	__IO unsigned Long_Press:1;
	__IO unsigned Shrt_Press:1;

};
extern struct Switch_Cntrl_Variables Switch_Detect_Incrmnt_Btn;

extern struct Switch_Cntrl_Variables Switch_Detect_Decrmnt_Btn;

extern struct Switch_Cntrl_Variables Switch_Detect_Set_Btn;

extern struct Switch_Cntrl_Variables Switch_Detect_Enter_Btn;

extern struct Switch_Cntrl_Variables Switch_Detect_Set_Enter_Btn;


#endif /* DISPLAY_VARIABLES_H_ */
