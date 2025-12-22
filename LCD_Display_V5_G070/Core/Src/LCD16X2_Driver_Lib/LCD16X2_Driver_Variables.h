/*
 * Display_Variables.h
 *
 *  Created on: 17-May-2020
 *      Author: pc
 */
#include"stm32g0xx.h"
#include <stdint.h>

#ifndef LCD16X2_DRIVER_VARIABLES_H_
#define LCD16X2_DRIVER_VARIABLES_H_


extern __IO uint32_t TimingDelay;

#define SET_E() (LL_GPIO_SetOutputPin(LCD_E_GPIO,LCD_E_PIN))
#define SET_RS() (LL_GPIO_SetOutputPin(LCD_RS_GPIO,LCD_RS_PIN))
#define SET_RW() (LL_GPIO_SetOutputPin(LCD_RW_GPIO,LCD_RW_PIN))

#define CLEAR_E() (LL_GPIO_ResetOutputPin(LCD_E_GPIO,LCD_E_PIN))
#define CLEAR_RS() (LL_GPIO_ResetOutputPin(LCD_RS_GPIO,LCD_RS_PIN))
#define CLEAR_RW() (LL_GPIO_ResetOutputPin(LCD_RW_GPIO,LCD_RW_PIN))



/*_________________________________________________________________________________________*/

/************************************************
	LCD CONNECTIONS
*************************************************/

#define LCD_DATA4_GPIO	GPIOD //data port
#define LCD_DATA4_Pin 	LL_GPIO_PIN_3//data port starts at PB12

#define LCD_DATA5_GPIO	GPIOB //data port
#define LCD_DATA5_Pin 	LL_GPIO_PIN_3//data port starts at PB12

#define LCD_DATA6_GPIO	GPIOB //data port
#define LCD_DATA6_Pin 	LL_GPIO_PIN_4//data port starts at PB12

#define LCD_DATA7_GPIO	GPIOB //data port
#define LCD_DATA7_Pin 	LL_GPIO_PIN_5//data port starts at PB12

#define LCD_E_GPIO 	GPIOD 	//Enable pin
#define LCD_E_PIN		LL_GPIO_PIN_2	//Enable is connected to PB2

#define LCD_RS_GPIO	GPIOD
#define LCD_RS_PIN 	LL_GPIO_PIN_1	//RS is connected to PB10

#define LCD_RW_GPIO	GPIOF
#define LCD_RW_PIN 	LL_GPIO_PIN_0 //RW is connected to PB11

#define LCD_Back_Light_GPIO	GPIOB //data port
#define LCD_Back_Light_Pin 	LL_GPIO_PIN_9//data port starts at PB12

#define LCD_TYPE_162					//LCD type is 16x2 can be 16x4 or 20x4 too


//************************************************

#define CURSOR_BLINK 0x01
#define CURSOR_ULINE 0x02
#define CURSOR_NONE  0x00

#define HD44780_CMD_SET_CG_RAM_ADD 0x40




#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

/***************************************************
	M A C R O S
***************************************************/
#define LCDClear() LCDCmd(0b00000001)
#define LCDHome() LCDCmd(0b00000010)

#define LCDWriteStringXY(x,y,msg) {\
 LCDGotoXY(x,y);\
 LCDWriteString(msg);\
}

#define LCDWriteIntXY(x,y,val,fl) {\
 LCDGotoXY(x,y);\
 LCDWriteInt(val,fl);\
}

/***************************************************/


extern unsigned char __cgram[64];

#ifdef LCD_TYPE_162
	#define LCD_TYPE_204
#endif

#ifdef LCD_TYPE_202
	#define LCD_TYPE_204
#endif

#endif /* DISPLAY_VARIABLES_H_ */
