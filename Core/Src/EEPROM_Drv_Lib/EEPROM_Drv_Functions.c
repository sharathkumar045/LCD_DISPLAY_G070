/*
 * EEPROM_I2C_Functions.c
 *
 *  Created on: 30 Nov 2019
 *      Author: G SK Reddy
 */



#include "i2c.h"
#include "gpio.h"

#include "EEPROM_Drv_Functions.h"
#include "EEPROM_Drv_Variables.h"


void EEPROM_Drv_Init(I2C_TypeDef* I2CX, uint8_t Device_Address)
{
	EEPROM_Drv_Var.I2Cx=I2CX;
	EEPROM_Drv_Var.Device_Addr = Device_Address;
	EEPROM_Drv_Var.Delay_MAX = 12000;
	EEPROM_Drv_Var.Delay = EEPROM_Drv_Var.Delay_MAX;
	EEPROM_Drv_Var.Cntr = 0;
	EEPROM_Drv_Var.Cntr_Limit = 10;
	EEPROM_Drv_Var.Cntr_Req = 0;

	LL_I2C_DisableAutoEndMode(EEPROM_Drv_Var.I2Cx);

}

uint8_t EEPROM_Drv_Read_Byte(volatile uint16_t Memory_Addr)
{

	volatile uint8_t data=0;


	EEPROM_Drv_Var.Delay=EEPROM_Drv_Var.Delay_MAX;
	while(EEPROM_Drv_Var.Delay--)
	{}

	EEPROM_Drv_Var.Memory_Lower_Addr = (uint8_t)((0x00FF)&Memory_Addr);
	EEPROM_Drv_Var.Memory_Upper_Addr = (uint8_t)((0x00FF)&(Memory_Addr>>8));


	LL_I2C_SetSlaveAddr(EEPROM_Drv_Var.I2Cx,EEPROM_Drv_Var.Device_Addr);
	EEPROM_Drv_Var.I2Cx->CR2&=(~I2C_CR2_RD_WRN);
	LL_I2C_SetMasterAddressingMode(EEPROM_Drv_Var.I2Cx,LL_I2C_ADDRESSING_MODE_7BIT);
	LL_I2C_SetTransferSize(EEPROM_Drv_Var.I2Cx,2);

	EEPROM_Drv_Var.I2Cx->CR2|= I2C_CR2_START;


	EEPROM_Drv_Var.Cntr = 0;
	while(LL_I2C_IsActiveFlag_TXE(EEPROM_Drv_Var.I2Cx)!=1)
	{
		EEPROM_Drv_Var.Cntr_Req = 1;
		if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
			return -1;
	}
	EEPROM_Drv_Var.Cntr_Req = 0;
	EEPROM_Drv_Var.Cntr = 0;

	LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Drv_Var.Memory_Upper_Addr);

	EEPROM_Drv_Var.Cntr = 0;
	while(LL_I2C_IsActiveFlag_TXE(EEPROM_Drv_Var.I2Cx)!=1)
	{
		EEPROM_Drv_Var.Cntr_Req = 1;
		if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
			return -1;
	}
	EEPROM_Drv_Var.Cntr_Req = 0;
	EEPROM_Drv_Var.Cntr = 0;

	LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Drv_Var.Memory_Lower_Addr);

	EEPROM_Drv_Var.I2Cx->CR2|=I2C_CR2_RD_WRN;
	LL_I2C_SetTransferSize(EEPROM_Drv_Var.I2Cx,1);


	EEPROM_Drv_Var.I2Cx->CR2|= I2C_CR2_START;



	EEPROM_Drv_Var.Cntr = 0;
	while(!LL_I2C_IsActiveFlag_RXNE(EEPROM_Drv_Var.I2Cx))
	{
		EEPROM_Drv_Var.Cntr_Req = 1;
		if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
			return -1;
	}
	EEPROM_Drv_Var.Cntr_Req = 0;
	EEPROM_Drv_Var.Cntr = 0;

	data=LL_I2C_ReceiveData8(EEPROM_Drv_Var.I2Cx);


	LL_I2C_GenerateStopCondition(EEPROM_Drv_Var.I2Cx);

	return data;

}

void EEPROM_Drv_Write_Byte(volatile uint16_t Memory_Addr, volatile uint8_t Data)
{

	EEPROM_Drv_Var.Delay=EEPROM_Drv_Var.Delay_MAX;
	while(EEPROM_Drv_Var.Delay--)
	{}

	EEPROM_Drv_Var.Memory_Lower_Addr = (uint8_t)((0x00FF)&Memory_Addr);
	EEPROM_Drv_Var.Memory_Upper_Addr = (uint8_t)((0x00FF)&(Memory_Addr>>8));

	LL_I2C_SetSlaveAddr(EEPROM_Drv_Var.I2Cx,EEPROM_Drv_Var.Device_Addr);
	EEPROM_Drv_Var.I2Cx->CR2&=(~I2C_CR2_RD_WRN);	//Write direction
	LL_I2C_SetMasterAddressingMode(EEPROM_Drv_Var.I2Cx,LL_I2C_ADDRESSING_MODE_7BIT);
	LL_I2C_SetTransferSize(EEPROM_Drv_Var.I2Cx,3);

	EEPROM_Drv_Var.I2Cx->CR2|= I2C_CR2_START;

	EEPROM_Drv_Var.Cntr = 0;
	while(LL_I2C_IsActiveFlag_TXIS(EEPROM_Drv_Var.I2Cx)!=1)
	{
		EEPROM_Drv_Var.Cntr_Req = 1;
		if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
			break;
	}
	EEPROM_Drv_Var.Cntr_Req = 0;
	EEPROM_Drv_Var.Cntr = 0;

	LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Drv_Var.Memory_Upper_Addr);

	EEPROM_Drv_Var.Cntr = 0;
	while(LL_I2C_IsActiveFlag_TXIS(EEPROM_Drv_Var.I2Cx)!=1)
	{
		EEPROM_Drv_Var.Cntr_Req = 1;
		if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
			break;
	}
	EEPROM_Drv_Var.Cntr_Req = 0;
	EEPROM_Drv_Var.Cntr = 0;

	LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Drv_Var.Memory_Lower_Addr);


	EEPROM_Drv_Var.Cntr = 0;
	while(LL_I2C_IsActiveFlag_TXIS(EEPROM_Drv_Var.I2Cx)!=1)
	{
		EEPROM_Drv_Var.Cntr_Req = 1;
		if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
			break;
	}
	EEPROM_Drv_Var.Cntr_Req = 0;
	EEPROM_Drv_Var.Cntr = 0;

	LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, Data);

	EEPROM_Drv_Var.Cntr = 0;
	while(LL_I2C_IsActiveFlag_TXE(EEPROM_Drv_Var.I2Cx)!=1)
	{
		EEPROM_Drv_Var.Cntr_Req = 1;
		if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
			break;
	}
	EEPROM_Drv_Var.Cntr_Req = 0;
	EEPROM_Drv_Var.Cntr = 0;


	LL_I2C_GenerateStopCondition(EEPROM_Drv_Var.I2Cx);

//	if(Data==EEPROM_I2C_Read_Byte(Memory_Addr))
//		return 1;
//	else
//		return 0;


}

//void EEPROM_I2C_Write_Array(volatile uint8_t *Array, volatile uint16_t length_of_Array, volatile uint16_t Memory_Start_Addr)
//{
//	for (int i = 0; i <length_of_Array ; i++)
//	{
//		EEPROM_I2C_Write_Byte(Memory_Start_Addr+i, Array[i]);
//	}
//}

void EEPROM_Drv_Read_Array()
{
	EEPROM_Drv_Var.Delay=EEPROM_Drv_Var.Delay_MAX;
		while(EEPROM_Drv_Var.Delay--)
		{}

		EEPROM_Drv_Var.Memory_Lower_Addr = (uint8_t)((0x00FF)&EEPROM_Drv_Var.Meomry_Start_Addr_16bit);
		EEPROM_Drv_Var.Memory_Upper_Addr = (uint8_t)((0x00FF)&(EEPROM_Drv_Var.Meomry_Start_Addr_16bit>>8));

		LL_I2C_SetSlaveAddr(EEPROM_Drv_Var.I2Cx,EEPROM_Drv_Var.Device_Addr);
		EEPROM_Drv_Var.I2Cx->CR2&=(~I2C_CR2_RD_WRN);
		LL_I2C_SetMasterAddressingMode(EEPROM_Drv_Var.I2Cx,LL_I2C_ADDRESSING_MODE_7BIT);
		LL_I2C_SetTransferSize(EEPROM_Drv_Var.I2Cx,2);

		EEPROM_Drv_Var.I2Cx->CR2|= I2C_CR2_START;

		EEPROM_Drv_Var.Cntr = 0;
		while(LL_I2C_IsActiveFlag_TXE(EEPROM_Drv_Var.I2Cx)!=1)
		{
			EEPROM_Drv_Var.Cntr_Req = 1;
			if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
				break;
		}
		EEPROM_Drv_Var.Cntr_Req = 0;
		EEPROM_Drv_Var.Cntr = 0;

		LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Drv_Var.Memory_Upper_Addr);

		EEPROM_Drv_Var.Cntr = 0;
		while(LL_I2C_IsActiveFlag_TXE(EEPROM_Drv_Var.I2Cx)!=1)
		{
			EEPROM_Drv_Var.Cntr_Req = 1;
			if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
				break;
		}
		EEPROM_Drv_Var.Cntr_Req = 0;
		EEPROM_Drv_Var.Cntr = 0;

		LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Drv_Var.Memory_Lower_Addr);

		EEPROM_Drv_Var.I2Cx->CR2|=I2C_CR2_RD_WRN;
		LL_I2C_SetTransferSize(EEPROM_Drv_Var.I2Cx,EEPROM_Drv_Var.Length_to_Read_or_Write);


		EEPROM_Drv_Var.I2Cx->CR2|= I2C_CR2_START;


		for(uint16_t i=0;i<EEPROM_Drv_Var.Length_to_Read_or_Write;i++)
		{
			EEPROM_Drv_Var.Cntr = 0;
			while(!LL_I2C_IsActiveFlag_RXNE(EEPROM_Drv_Var.I2Cx))
			{
				EEPROM_Drv_Var.Cntr_Req = 1;
				if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
					break;
			}
			EEPROM_Drv_Var.Cntr_Req = 0;
			EEPROM_Drv_Var.Cntr = 0;

			EEPROM_Read_Array[i]=LL_I2C_ReceiveData8(EEPROM_Drv_Var.I2Cx);
		}

		LL_I2C_GenerateStopCondition(EEPROM_Drv_Var.I2Cx);

}


/*
void EEPROM_Drv_Write_Array()
{

	volatile uint16_t no_of_pages=EEPROM_Drv_Var.Length_to_Read_or_Write/EEPROM_Drv_PAGE_SIZE;    // 128
	volatile uint8_t remaining_bytes= EEPROM_Drv_Var.Length_to_Read_or_Write - (no_of_pages*EEPROM_Drv_PAGE_SIZE);
	volatile uint16_t Index=0, no_of_iterations=0;




	for(uint16_t i=0;i<=no_of_pages;i++)
	{

		if( (i<no_of_pages) && (no_of_pages!=0) )
		{
			LL_I2C_SetTransferSize(EEPROM_Drv_Var.I2Cx, 2 + EEPROM_Drv_PAGE_SIZE);
			no_of_iterations=EEPROM_Drv_PAGE_SIZE;
		}
		else
		{
			LL_I2C_SetTransferSize(EEPROM_Drv_Var.I2Cx, 2 + remaining_bytes);
			no_of_iterations=remaining_bytes;
		}


		EEPROM_Drv_Var.Delay=EEPROM_Drv_Var.Delay_MAX;
		while(EEPROM_Drv_Var.Delay--)
		{}

		volatile uint16_t Memory_Addr = EEPROM_Drv_Var.Meomry_Start_Addr_16bit + (i*EEPROM_Drv_PAGE_SIZE);

		EEPROM_Drv_Var.Memory_Lower_Addr = (uint8_t)((0x00FF)&Memory_Addr);
		EEPROM_Drv_Var.Memory_Upper_Addr = (uint8_t)((0x00FF)&(Memory_Addr>>8));

		LL_I2C_SetSlaveAddr(EEPROM_Drv_Var.I2Cx,EEPROM_Drv_Var.Device_Addr);
		EEPROM_Drv_Var.I2Cx->CR2&=(~I2C_CR2_RD_WRN);	//Write direction
		LL_I2C_SetMasterAddressingMode(EEPROM_Drv_Var.I2Cx,LL_I2C_ADDRESSING_MODE_7BIT);



		EEPROM_Drv_Var.I2Cx->CR2|= I2C_CR2_START;

		EEPROM_Drv_Var.Cntr = 0;
		while(LL_I2C_IsActiveFlag_TXE(EEPROM_Drv_Var.I2Cx)!=1)
		{
			EEPROM_Drv_Var.Cntr_Req = 1;
		}
		EEPROM_Drv_Var.Cntr_Req = 0;
		EEPROM_Drv_Var.Cntr = 0;

		LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Drv_Var.Memory_Upper_Addr);

		EEPROM_Drv_Var.Cntr = 0;
		while(LL_I2C_IsActiveFlag_TXE(EEPROM_Drv_Var.I2Cx)!=1)
		{
			EEPROM_Drv_Var.Cntr_Req = 1;
//			if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
//				return -1;
		}
		EEPROM_Drv_Var.Cntr_Req = 0;
		EEPROM_Drv_Var.Cntr = 0;

		LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Drv_Var.Memory_Lower_Addr);


		for(uint8_t j=0;j<no_of_iterations;j++)
		{
			EEPROM_Drv_Var.Cntr = 0;
			while(LL_I2C_IsActiveFlag_TXE(EEPROM_Drv_Var.I2Cx)!=1)
			{
				EEPROM_Drv_Var.Cntr_Req = 1;

			}
			EEPROM_Drv_Var.Cntr_Req = 0;
			EEPROM_Drv_Var.Cntr = 0;

			LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Write_Array[Index++]);
		}

		EEPROM_Drv_Var.Cntr = 0;
			while(LL_I2C_IsActiveFlag_TXE(EEPROM_Drv_Var.I2Cx)!=1)
			{
				EEPROM_Drv_Var.Cntr_Req = 1;

			}
			EEPROM_Drv_Var.Cntr_Req = 0;
			EEPROM_Drv_Var.Cntr = 0;


			LL_I2C_GenerateStopCondition(EEPROM_Drv_Var.I2Cx);

	}

}

*/

void EEPROM_Drv_Write_Array()
{
	volatile uint8_t  no_of_iterations=0;
	volatile uint16_t Mem_Start_Addr= EEPROM_Drv_Var.Meomry_Start_Addr_16bit, Write_Length=EEPROM_Drv_Var.Length_to_Read_or_Write, next_page_start=0, Index=0;

	while(Write_Length)
	{
		next_page_start=((Mem_Start_Addr/EEPROM_Drv_PAGE_SIZE)+1)*EEPROM_Drv_PAGE_SIZE;
		no_of_iterations=next_page_start-Mem_Start_Addr;
		if(Write_Length<no_of_iterations)
		{
			no_of_iterations=Write_Length;
		}
		Write_Length-=no_of_iterations;


			EEPROM_Drv_Var.Delay=EEPROM_Drv_Var.Delay_MAX;
			while(EEPROM_Drv_Var.Delay--)
			{}

			EEPROM_Drv_Var.Memory_Lower_Addr = (uint8_t)((0x00FF)&Mem_Start_Addr);
			EEPROM_Drv_Var.Memory_Upper_Addr = (uint8_t)((0x00FF)&(Mem_Start_Addr>>8));

			LL_I2C_SetSlaveAddr(EEPROM_Drv_Var.I2Cx,EEPROM_Drv_Var.Device_Addr);
			EEPROM_Drv_Var.I2Cx->CR2&=(~I2C_CR2_RD_WRN);	//Write direction
			LL_I2C_SetMasterAddressingMode(EEPROM_Drv_Var.I2Cx,LL_I2C_ADDRESSING_MODE_7BIT);
			LL_I2C_SetTransferSize(EEPROM_Drv_Var.I2Cx, 2+no_of_iterations);

			EEPROM_Drv_Var.I2Cx->CR2|= I2C_CR2_START;

			EEPROM_Drv_Var.Cntr = 0;
			while(LL_I2C_IsActiveFlag_TXIS(EEPROM_Drv_Var.I2Cx)!=1)
			{
				EEPROM_Drv_Var.Cntr_Req = 1;
				if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
					break;
			}
			EEPROM_Drv_Var.Cntr_Req = 0;
			EEPROM_Drv_Var.Cntr = 0;

			LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Drv_Var.Memory_Upper_Addr);

			EEPROM_Drv_Var.Cntr = 0;
			while(LL_I2C_IsActiveFlag_TXIS(EEPROM_Drv_Var.I2Cx)!=1)
			{
				EEPROM_Drv_Var.Cntr_Req = 1;
				if(EEPROM_Drv_Var.Cntr>=EEPROM_Drv_Var.Cntr_Limit)
					break;
			}
			EEPROM_Drv_Var.Cntr_Req = 0;
			EEPROM_Drv_Var.Cntr = 0;

			LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Drv_Var.Memory_Lower_Addr);


			for(uint8_t j=0;j<no_of_iterations;j++)
			{
				EEPROM_Drv_Var.Cntr = 0;
				while(LL_I2C_IsActiveFlag_TXE(EEPROM_Drv_Var.I2Cx)!=1)
				{
					EEPROM_Drv_Var.Cntr_Req = 1;

				}
				EEPROM_Drv_Var.Cntr_Req = 0;
				EEPROM_Drv_Var.Cntr = 0;

				LL_I2C_TransmitData8(EEPROM_Drv_Var.I2Cx, EEPROM_Write_Array[Index++]);
			}

			EEPROM_Drv_Var.Cntr = 0;
			while(LL_I2C_IsActiveFlag_TXE(EEPROM_Drv_Var.I2Cx)!=1)
			{
				EEPROM_Drv_Var.Cntr_Req = 1;

			}
			EEPROM_Drv_Var.Cntr_Req = 0;
			EEPROM_Drv_Var.Cntr = 0;


			LL_I2C_GenerateStopCondition(EEPROM_Drv_Var.I2Cx);


			Mem_Start_Addr=next_page_start;

	}

}




