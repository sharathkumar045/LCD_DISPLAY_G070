/*
 * Variables.c
 *
 *  Created on: 15-May-2020
 *      Author: pc
 */


#include "stm32g0xx.h"
#include "main.h"
#include "Switch_App_Variables.h"

struct Switch_Cntrl_Variables Switch_Detect_Incrmnt_Btn = {0};

struct Switch_Cntrl_Variables Switch_Detect_Decrmnt_Btn = {0};

struct Switch_Cntrl_Variables Switch_Detect_Set_Btn = {0};

struct Switch_Cntrl_Variables Switch_Detect_Enter_Btn = {0};

struct Switch_Cntrl_Variables Switch_Detect_Set_Enter_Btn = {0};


__IO uint8_t ID = 1;
