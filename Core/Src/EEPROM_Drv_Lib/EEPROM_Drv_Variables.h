
//#define EEPROM_Device_Addr 0b1010000<<1

#include "i2c.h"

#define EEPROM_Drv_Device_Addr ((uint8_t)0b1010000<<1)

#define EEPROM_Drv_PAGE_SIZE 128


struct EEPROM_Drv_Variables{

	volatile uint8_t Device_Addr;
	volatile uint8_t Memory_Upper_Addr; //Memory_Addr_Upper_Byte    no need to init
	volatile uint8_t Memory_Lower_Addr; //Memory_Addr_Lower_Byte    no need to init
	volatile uint16_t Meomry_Start_Addr_16bit;  //WRITING : addr must be in multiples of PAGE_SIZE //READING: any random addr is valied
	volatile uint16_t Length_to_Read_or_Write; // WRITING : any length is valied // READING : 0-255
	volatile uint16_t Delay;
	volatile uint16_t Delay_MAX;
	volatile uint8_t Cntr;
	volatile uint8_t Cntr_Limit;
	volatile uint8_t Cntr_Req;
	I2C_TypeDef* I2Cx;
	volatile uint8_t Write_Flag;
	volatile uint8_t Read_Flag;

};
extern volatile struct EEPROM_Drv_Variables EEPROM_Drv_Var; //EEPROM_I2C_Var;


extern volatile uint8_t EEPROM_Write_Array[300];
//extern volatile uint8_t EEPROM_I2C_Recv_Array[300];

//extern volatile uint8_t EEPROM_Write_Array[255];
extern volatile uint8_t EEPROM_Read_Array[255];



//struct EEPROM_API_Variables{
//
//	volatile uint8_t Day_to_Write;
//	volatile uint8_t Month_to_Write;
//	volatile uint16_t Year_to_Write;
//	volatile uint16_t KWH_to_Write;
//};


struct Disp_EEPROM_Cntrl_Flags{

	__IO unsigned Calib_Store_Rq:1;
	__IO unsigned Calib_Retrieve_Rq:1;
	__IO unsigned Energy_Store_Rq:1;
	__IO unsigned Energy_Retrieve_Rq:1;
	__IO unsigned Settngs_Store_Rq:1;
	__IO unsigned Settngs_Retrieve_Rq:1;
	__IO unsigned Error:1;

};
extern struct Disp_EEPROM_Cntrl_Flags Disp_EEPROM_Flag;

struct Disp_EEPROM_Cntrl_Variables{

	__IO uint16_t Device_Address_7bit;
	__IO uint16_t Calib_Store_Start_Address;
	__IO uint16_t Calib_Store_len;  //if u have 40 values, give 40 as len including crc (not 39)
	__IO uint16_t Energy_Store_Start_Address;
	__IO uint16_t Energy_Store_len;  //if u have 40 values, give 40 as len including crc (not 39)
	__IO uint16_t Energy_Store_Last_Write_Index;
	__IO uint16_t Settings_Store_Start_Address;
	__IO uint16_t Settings_Store_len;
	__IO uint16_t Max_Energy_Storage_Days;

};
extern struct Disp_EEPROM_Cntrl_Variables Disp_EEPROM;
