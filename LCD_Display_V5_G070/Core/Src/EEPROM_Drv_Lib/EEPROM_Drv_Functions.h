

void EEPROM_Drv_Init(I2C_TypeDef* I2Cx, uint8_t Device_Address);

uint8_t EEPROM_Drv_Read_Byte(volatile uint16_t Memory_Addr);

void EEPROM_Drv_Write_Byte(volatile uint16_t Memory_Addr, volatile uint8_t Data);


void EEPROM_Drv_Read_Array();

void EEPROM_Drv_Write_Array();

