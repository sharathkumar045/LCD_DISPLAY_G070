/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Main_Variables.h"
#include "Main_Functions.h"


#include "Display_App_Variables.h"
#include "Display_App_Functions.h"

#include "Switch_App_Variables.h"
#include "Switch_App_Functions.h"

#include "LCD16X2_Driver_Variables.h"
#include "LCD16X2_Driver_Functions.h"

#include "EEPROM_App_Functions.h"
#include "EEPROM_App_Variables.h"

#include "EEPROM_Drv_Functions.h"
#include "EEPROM_Drv_Variables.h"

#include "UART1_Mast_App_Functions.h"
#include "UART1_Mast_App_Variables.h"

#include "UART1_Mast_Drv_Functions.h"
#include "UART1_Mast_Drv_Variables.h"

#include "RTC_Drv_Functions.h"
#include "RTC_Drv_Variables.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, 3);

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART4_UART_Init();
  MX_TIM1_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */

  EEPROM_Drv_Init(I2C1,EEPROM_Drv_Device_Addr);
  RTC_Drv_Init(I2C1,RTC_Device_Addr);
  RTC_Drv_Intrnl_Alarm_Init();
  Main_Variables_Init();
  Display_Variables_Init();

  TIM1->DIER |= TIM_DIER_UIE;  //Update interrupt enable
  TIM1->CR1 |= TIM_CR1_CEN; // counter enable

  //GPIOB->BSRR |= LCD_Back_Light_Pin;

//  GPIOB->ODR &= ~LCD_Back_Light_Pin;
//  GPIOB->BSRR |= LCD_Back_Light_Pin;
//  LL_GPIO_SetOutputPin(LCD_Backlight_GPIO_Port,LCD_Back_Light_Pin);
//  LL_GPIO_SetOutputPin(Buzzer_GPIO_Port,Buzzer_Pin);



  LCDInit(CURSOR_ULINE);


  State=Metering_Data_Rq;
  EEPROM_App_Flags.Read_Settings_Req = 1;
  Disp_Cntrl.Settng_Index = 1;
  Disp_Cntrl.Calib_Index = 1;
  Disp_Cntrl.Mtrng_Index = 1;
//
//  RTC_Drv_Set_Intrnl_From_Ext();
//
//  EEPROM_App_Var.Mtrng_Energy_Cntr =  EEPROM_Drv_Read_Byte(EEPROM_App_Metering_Cntr_Start_Addr);
//
//  if(EEPROM_App_Var.Mtrng_Energy_Cntr > 31)
//  {
//	  EEPROM_App_Var.Mtrng_Energy_Cntr = 0;
//	  EEPROM_Drv_Write_Byte(EEPROM_App_Metering_Cntr_Start_Addr , EEPROM_App_Var.Mtrng_Energy_Cntr);
//  }

  UART1_Enable_Receive_Interrupt; //Enabling the receive interrupt
  UART1_Enable;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  LCD_Clear_Display();
  LCD_Disp_On();

  while (1)
  {
//	  WhileLoop_Display_Menu_Fns(ID);
	Whileloop_State_Fn();

	LCD_Disp_On();

	Delay(10);
//		LCD_Clear_Display();

	U1Mast_App_Store_Received_Data_In_Variables();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
  {
  }

  /* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* LSI configuration and activation */
  LL_RCC_LSI_Enable();
  while(LL_RCC_LSI_IsReady() != 1)
  {
  }

  LL_PWR_EnableBkUpAccess();
  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(64000000);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(64000000);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
