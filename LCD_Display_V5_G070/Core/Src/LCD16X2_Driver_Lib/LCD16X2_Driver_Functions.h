/*
 * User_Defined_Functions.h
 *
 *  Created on: 15-May-2020
 *      Author: pc
 */

#ifndef LCD16X2_DRIVER_FUNCTIONS_H_
#define LCD16X2_DRIVER_FUNCTIONS_H_



/***************************************LCD related functions***********************************************/
void Delay(uint32_t nTime);

void TimingDelay_Decrement(void);

void LCD_Clear_Display(void);
void LCD_Locate(uint8_t row, uint8_t column);
void LCD_Disp_Off(void);
void LCD_Disp_On(void);

void Printfloat(float x,uint8_t Int_Digits, uint8_t Decimal_Digits);

/***************************************************
			F U N C T I O N S
****************************************************/

void DelayUS(uint32_t us);

void LCDByte(uint8_t,uint8_t);

void LCDBusyLoop(void);

void LCDInit(uint8_t style);

void LCDWriteString(const char *msg);

void LCDWriteInt(int val,int8_t field_length);

void LCDWrite_Unsigned_Int(int val,int8_t field_length);

void LCDGotoXY(uint8_t x,uint8_t y);

//Low level

void LCDGPIOInit(void);

void LCD_Scroll_Right(uint8_t ntimes);

void LCD_Scroll_Left(uint8_t ntimes);

void Nibble_Write(uint16_t LCD_Write_Data);
uint8_t Nibble_Read(void);
void Config_Data_Pins_As_Output(void);
void Config_Data_Pins_As_Input(void);




#endif /* USER_DEFINED_FUNCTIONS_H_ */
