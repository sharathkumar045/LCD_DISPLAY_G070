/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32g0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Main_Variables.h"
#include "Main_Functions.h"

#include "LCD16X2_Driver_Functions.h"
#include "Switch_App_Functions.h"

#include "UART1_Mast_App_Functions.h"
#include "UART1_Mast_App_Variables.h"

#include "UART1_Mast_Drv_Functions.h"
#include "UART1_Mast_Drv_Variables.h"

#include "RTC_Drv_Functions.h"
#include "RTC_Drv_Variables.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 break, update, trigger and commutation interrupts.
  */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 0 */
	TimingDelay_Decrement();

	Switch_1ms_Interrupt_Fn();

	Disp_Cntrl.Timer_Count = Disp_Cntrl.Timer_Count + 1;
	if((Disp_Cntrl.Timer_Count > Three_Sec)&&(State == Metering))
	{
		Disp_Cntrl.Mtrng_Index = Disp_Cntrl.Mtrng_Index + 1;
		Disp_Cntrl.Timer_Count = 0;
		if(Disp_Cntrl.Mtrng_Index > Disp_Cntrl.Mtrng_Max_Index)
		{
			State = RTC_Disp_Time_Date;
			Disp_Cntrl.First_Time_State_Entry = 1;
			//Disp_Cntrl.Mtrng_Index = 1;
		}
	}

	if(RTC_Alarm_Flag)
	{
		RTC_Drv_Set_Intrnl_From_Ext();
		State = Daily_Reset;
		Disp_Cntrl.First_Time_State_Entry = 1;
		RTC_Alarm_Clr_Flag;
	}

	if(State == Metering)
	{
		Disp_Cntrl.Metering_Rqst_Count = Disp_Cntrl.Metering_Rqst_Count + 1;
		if(Disp_Cntrl.Metering_Rqst_Count >= Ten_Sec)
		{
			Disp_Cntrl.Metering_Rqst_Count = 0;
			U1Mast_App_Populate_And_Send_Txdata_Array_With_Message_Request_Metering();
		}
	}


//	Disp_Cntrl.Reset_Time_Count = Disp_Cntrl.Reset_Time_Count + 1;
//	if((Disp_Cntrl.Reset_Time_Count > Ten_Sec)&&(State == Metering))
//	{
//		Disp_Cntrl.Reset_Time_Count = 0;
//		State = Daily_Reset;
//		Disp_Cntrl.First_Time_State_Entry = 1;
//
//	}
//	U1Mast_Drv_Send_Function_Inside_Timer_Interrupt();
	U1Mast_Drv_Send_Function_Inside_Timer_Interrupt();


	U1Mast_App_Send_Var.Ack_Wait_Time_cntr = U1Mast_App_Send_Var.Ack_Wait_Time_cntr -1;
	if(U1Mast_App_Send_Var.Ack_Wait_Time_cntr <= 0)
	{
		U1Mast_App_Send_Var.Ack_Wait_Time_cntr = 0;
	}
  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 0 */
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 1 */
	TIM1->SR &= ~(TIM_SR_UIF);
  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	U1Mast_Drv_Receive_ISR_Program();
  /* USER CODE END USART1_IRQn 0 */
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles USART3 and USART4 interrupts.
  */
void USART3_4_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_4_IRQn 0 */

  /* USER CODE END USART3_4_IRQn 0 */
  /* USER CODE BEGIN USART3_4_IRQn 1 */

  /* USER CODE END USART3_4_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
