/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32g0xx_ll_i2c.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_rtc.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Grid_Export_LED_Pin LL_GPIO_PIN_13
#define Grid_Export_LED_GPIO_Port GPIOC
#define Buzzer_Pin LL_GPIO_PIN_4
#define Buzzer_GPIO_Port GPIOA
#define Ent_Key_Pin LL_GPIO_PIN_1
#define Ent_Key_GPIO_Port GPIOB
#define Dec_Key_Pin LL_GPIO_PIN_2
#define Dec_Key_GPIO_Port GPIOB
#define Inc_Key_Pin LL_GPIO_PIN_10
#define Inc_Key_GPIO_Port GPIOB
#define Set_Key_Pin LL_GPIO_PIN_11
#define Set_Key_GPIO_Port GPIOB
#define RS485_RE_DE_Pin LL_GPIO_PIN_12
#define RS485_RE_DE_GPIO_Port GPIOA
#define LED_Spare_Pin LL_GPIO_PIN_15
#define LED_Spare_GPIO_Port GPIOA
#define PV_Available_LED_Pin LL_GPIO_PIN_0
#define PV_Available_LED_GPIO_Port GPIOD
#define RS_Pin LL_GPIO_PIN_1
#define RS_GPIO_Port GPIOD
#define EN_Pin LL_GPIO_PIN_2
#define EN_GPIO_Port GPIOD
#define D4_Pin LL_GPIO_PIN_3
#define D4_GPIO_Port GPIOD
#define D5_Pin LL_GPIO_PIN_3
#define D5_GPIO_Port GPIOB
#define D6_Pin LL_GPIO_PIN_4
#define D6_GPIO_Port GPIOB
#define D7_Pin LL_GPIO_PIN_5
#define D7_GPIO_Port GPIOB
#define Fault_LED_Pin LL_GPIO_PIN_8
#define Fault_LED_GPIO_Port GPIOB
#define LCD_Backlight_Pin LL_GPIO_PIN_9
#define LCD_Backlight_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
