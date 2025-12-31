/*
 * General_Functions.c
 *
 *  Created on: 15-May-2020
 *      Author: pc
 */

#include "stm32g0xx.h"
#include "string.h"

#include "LCD16X2_Driver_Variables.h"
#include "LCD16X2_Driver_Functions.h"

#include "gpio.h"

/******************************************** LCD related functions ***************************************************/

void Delay(uint32_t nTime)
{
  /* Wait delay elapsed by interrupt update of timing delay variable*/
  TimingDelay = nTime;
  while (TimingDelay != 0);
}

/**
  ******************************************************************************
  * @brief Decrement initial value at each interrupt
  * @param[in]
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}


/**
  * @brief  Clear LCD module display
  * @param  None
  * @param  None
  * @retval None
  */

void LCD_Clear_Display(void)
{
  LCDCmd(0x01);
  Delay(2);
}

/**
  * @brief  Set Cursor to a specified location given by row and column information
  * @param  Row Number (1 to 2)
  * @param  Column Number (1 to 16) Assuming a 2 X 16 characters display
  * @retval None
  */
void LCD_Locate(uint8_t row, uint8_t column)
{
  column--;
  switch (row)
  {
    case 1:
      /* Set cursor to 1st row address and add index*/
      LCDCmd(column |= 0x80);
      break;
    case 2:
      /* Set cursor to 2nd row address and add index*/
      LCDCmd(column |= 0x40 | 0x80);
      break;
    default:
      break;
  }
}


void LCD_Disp_Off(void)
{
  LCDCmd(0x08);
  Delay(2);
}

void LCD_Disp_On(void)
{
  LCDCmd(0x0C);
  Delay(2);
}

void Printfloat(float x,uint8_t Int_Digits, uint8_t Decimal_Digits)
{
	int num;
	uint32_t Power =1;
	for(int i=0; i<Decimal_Digits; i++)
	{
		Power=Power*10;
	}
	if (x<0)
	{
		LCDData('-');
		x=x*-1;
	}
	else
	{
		LCDData(' ');
	}
	num = (int)(x);
	LCDWrite_Unsigned_Int(num, Int_Digits);
	LCDData('.');
	num=(int)((x-num)*(Power));
	LCDWrite_Unsigned_Int(num, Decimal_Digits);

}

void LCD_Scroll_Left(uint8_t ntimes){
	for(uint8_t i=0;i<=ntimes;i++){
		LCDCmd(0x18);
	}
}

void LCD_Scroll_Right(uint8_t ntimes){
	for(uint8_t i=0;i<=ntimes;i++){
		LCDCmd(0x1C);
	}
}



void DelayUS(uint32_t us)
{
	us=us*50;

	for(uint32_t i=0;i<us;i++)
	{
		__ASM("NOP");
	}
}

void LCDByte(uint8_t c,uint8_t isdata)
{
//Sends a byte to the LCD in 4bit mode
//cmd=0 for data
//cmd=1 for command


//NOTE: THIS FUNCTION RETURS ONLY WHEN LCD HAS PROCESSED THE COMMAND

uint16_t hn,ln;			//Nibbles
//uint16_t temp;

hn=c>>4;
ln=(c & 0x0F);

if(isdata==0)
	CLEAR_RS();
else
	SET_RS();

Delay(2);		//tAS


SET_E();


Nibble_Write(hn);

Delay(2);			//tEH

//Now data lines are stable pull E low for transmission

CLEAR_E();

Delay(2);

//Send the lower nibble
SET_E();

Nibble_Write(ln);

Delay(2);			//tEH

//SEND

CLEAR_E();

Delay(10);			//tEL

}

void LCDBusyLoop()
{
	Delay(100);
}

void LCDInit(uint8_t style)
{
	/*****************************************************************

	This function Initializes the lcd module
	must be called before calling lcd related functions

	Arguments:
	style = LS_BLINK,LS_ULINE(can be "OR"ed for combination)
	LS_BLINK : The cursor is blinking type
	LS_ULINE : Cursor is "underline" type else "block" type
        LS_NONE : No visible cursor

	*****************************************************************/

	//After power on Wait for LCD to Initialize
	Delay(30);


	//MX_GPIO_Init();

	//Set 4-bit mode
	SET_E();
	CLEAR_RS();

	LCDCmd(0x33);
	Delay(4);
	LCDCmd(0x32);
	Delay(4);

	LCDCmd(0x28);

	LCDCmd(0x0C);

	LCDCmd(0x06);

	Delay(200);

	LCD_Clear_Display();

  LCDCmd(HD44780_CMD_SET_CG_RAM_ADD);


	uint8_t __i;
	for(__i=0;__i<sizeof(__cgram);__i++)
		LCDData(__cgram[__i]);
}

void LCDWriteString(const char *msg)
{
	/*****************************************************************

	This function Writes a given string to lcd at the current cursor
	location.

	Arguments:
	msg: a null terminated C style string to print

	Their are 8 custom char in the LCD they can be defined using
	"LCD Custom Character Builder" PC Software.

	You can print custom character using the % symbol. For example
	to print custom char number 0 (which is a degree symbol), you
	need to write

	LCDWriteString("Temp is 30%0C");
                                  ^^
                                   |----> %0 will be replaced by
                                          custom char 0.

	So it will be printed like.

		Temp is 30�C

	In the same way you can insert any symbols numbered 0-7


	*****************************************************************/
 while(*msg!='\0')
 {
 	//Custom Char Support
	if(*msg=='%')
	{
		msg++;
		int8_t cc=*msg-'0';

		if(cc>=0 && cc<=7)
		{
			LCDData(cc);
		}
		else
		{
			LCDData('%');
			LCDData(*msg);
		}
	}
	else
	{
		LCDData(*msg);
	}
	msg++;
 }
}

void LCDWriteInt(int val,int8_t field_length)
{
	/***************************************************************
	This function writes a integer type value to LCD module

	Arguments:
	1)int val	: Value to print

	2)unsigned int field_length :total length of field in which the value is printed
	must be between 1-5 if it is -1 the field length is no of digits in the val

	****************************************************************/

	char str[5]={0,0,0,0,0};
	int i=4,j=0;

    //Handle negative integers
    if(val<0)
    {
        LCDData('-');   //Write Negative sign
        val=val*-1;     //convert to positive
    }
    else
    {
        LCDData(' ');
    }

    if(val==0 && field_length<1)
    {
        LCDData('0');
        return;
    }

	while(val)
	{
            str[i]=val%10;
            val=val/10;
            i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;


	for(i=j;i<5;i++)
	{
	LCDData(48+str[i]);
	}
}

void LCDWrite_Unsigned_Int(int val,int8_t field_length)
{
	/***************************************************************
		sameasabove function but it prints the value without sign
		hence no space is wasted for sign

		****************************************************************/

		char str[5]={0,0,0,0,0};
		int i=4,j=0;

	    //Handle negative integers
	    if(val<0)
	    {
	        //LCDData('-');   //Write Negative sign
	        val=val*-1;     //convert to positive
	    }
	    else
	    {
	        //LCDData(' ');
	    }

	    if(val==0 && field_length<1)
	    {
	        LCDData('0');
	        return;
	    }

		while(val)
		{
	            str[i]=val%10;
	            val=val/10;
	            i--;
		}
		if(field_length==-1)
			while(str[j]==0) j++;
		else
			j=5-field_length;


		for(i=j;i<5;i++)
		{
		LCDData(48+str[i]);
		}
}


/********************************************************************

Position the cursor to specific part of the screen

********************************************************************/
void LCDGotoXY(uint8_t x,uint8_t y)
{
 	if(x>=20) return;

	#ifdef LCD_TYPE_204

	switch(y)
	{
		case 0:
			break;
		case 1:
			x|=0x40;//0b01000000;
			break;
		case 2:
			x+=0x14;
			break;
		case 3:
			x+=0x54;
			break;
	}

	#endif

	#ifdef LCD_TYPE_164
	switch(y)
	{
		case 0:
			break;
		case 1:
			x|=0x40;//0b01000000;
			break;
		case 2:
			x+=0x10;
			break;
		case 3:
			x+=0x50;
			break;
	}

	#endif

	x|=0x80;//0b10000000;
  	LCDCmd(x);
}

void Nibble_Write(uint16_t LCD_Write_Data)
{

	if(LCD_Write_Data & 0x01)
	{
		LCD_DATA4_GPIO->ODR |= LCD_DATA4_Pin ;
	}
	else
	{
		LCD_DATA4_GPIO->ODR &= ~LCD_DATA4_Pin ;
	}

	if(LCD_Write_Data & 0x02)
	{
		LCD_DATA5_GPIO->ODR |= LCD_DATA5_Pin ;
	}
	else
	{
		LCD_DATA5_GPIO->ODR &= ~LCD_DATA5_Pin ;
	}

	if(LCD_Write_Data & 0x04)
	{
		LCD_DATA6_GPIO->ODR |= LCD_DATA6_Pin ;
	}
	else
	{
		LCD_DATA6_GPIO->ODR &= ~LCD_DATA6_Pin ;
	}

	if(LCD_Write_Data & 0x08)
	{
		LCD_DATA7_GPIO->ODR |= LCD_DATA7_Pin ;
	}
	else
	{
		LCD_DATA7_GPIO->ODR &= ~LCD_DATA7_Pin ;
	}
}

uint8_t Nibble_Read()
{
	uint8_t x = 0;
	x |= ((LCD_DATA4_GPIO->IDR & LCD_DATA4_Pin) >> 3);

	x |= ((LCD_DATA5_GPIO->IDR & LCD_DATA5_Pin)>>3)<<1 ; //The right shift is to bring it to zeroth bit and the to data position

	x |= ((LCD_DATA6_GPIO->IDR & LCD_DATA6_Pin)>>4)<<2 ;

	x |= ((LCD_DATA7_GPIO->IDR & LCD_DATA7_Pin)>>5)<<3 ;
	return x;

}





















