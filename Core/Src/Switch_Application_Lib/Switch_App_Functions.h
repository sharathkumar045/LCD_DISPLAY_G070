/*
 * User_Defined_Functions.h
 *
 *  Created on: 15-May-2020
 *      Author: pc
 */
#include "stm32g0xx.h"
#ifndef SWITCH_APP_FUNCTIONS_H_
#define SWITCH_APP_FUNCTIONS_H_

void Switch_1ms_Interrupt_Fn(void);

void Switch_Incrmnt_Detect(void);

void Switch_Decrmnt_Detect(void);

void Switch_Set_Detect(void);

void Switch_Enter_Detect(void);

void Switch_Set_and_Enter_Detect(void);

#endif /* USER_DEFINED_FUNCTIONS_H_ */
