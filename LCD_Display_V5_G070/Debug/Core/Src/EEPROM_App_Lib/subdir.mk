################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/EEPROM_App_Lib/EEPROM_App_Functions.c \
../Core/Src/EEPROM_App_Lib/EEPROM_App_Variables.c 

OBJS += \
./Core/Src/EEPROM_App_Lib/EEPROM_App_Functions.o \
./Core/Src/EEPROM_App_Lib/EEPROM_App_Variables.o 

C_DEPS += \
./Core/Src/EEPROM_App_Lib/EEPROM_App_Functions.d \
./Core/Src/EEPROM_App_Lib/EEPROM_App_Variables.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/EEPROM_App_Lib/%.o Core/Src/EEPROM_App_Lib/%.su Core/Src/EEPROM_App_Lib/%.cyclo: ../Core/Src/EEPROM_App_Lib/%.c Core/Src/EEPROM_App_Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32G070xx -DUSE_FULL_LL_DRIVER -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=48000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -DHSE_VALUE=25000000 -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../Core/Src/Display_Application_Lib -I../Core/Src/EEPROM_App_Lib -I../Core/Src/EEPROM_Drv_Lib -I../Core/Src/LCD16X2_Driver_Lib -I../Core/Src/RTC_Drv_Lib -I../Core/Src/Switch_Application_Lib -I../Core/Src/UART1_Mast_App_Lib -I../Core/Src/UART1_Mast_Drv_Lib -I../Core/Src/UART1_Master_Drv_Lib -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-EEPROM_App_Lib

clean-Core-2f-Src-2f-EEPROM_App_Lib:
	-$(RM) ./Core/Src/EEPROM_App_Lib/EEPROM_App_Functions.cyclo ./Core/Src/EEPROM_App_Lib/EEPROM_App_Functions.d ./Core/Src/EEPROM_App_Lib/EEPROM_App_Functions.o ./Core/Src/EEPROM_App_Lib/EEPROM_App_Functions.su ./Core/Src/EEPROM_App_Lib/EEPROM_App_Variables.cyclo ./Core/Src/EEPROM_App_Lib/EEPROM_App_Variables.d ./Core/Src/EEPROM_App_Lib/EEPROM_App_Variables.o ./Core/Src/EEPROM_App_Lib/EEPROM_App_Variables.su

.PHONY: clean-Core-2f-Src-2f-EEPROM_App_Lib

