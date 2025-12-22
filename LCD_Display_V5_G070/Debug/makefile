################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32G0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/UART1_Mast_Drv_Lib/subdir.mk
-include Core/Src/UART1_Mast_App_Lib/subdir.mk
-include Core/Src/Switch_Application_Lib/subdir.mk
-include Core/Src/RTC_Drv_Lib/subdir.mk
-include Core/Src/LCD16X2_Driver_Lib/subdir.mk
-include Core/Src/EEPROM_Drv_Lib/subdir.mk
-include Core/Src/EEPROM_App_Lib/subdir.mk
-include Core/Src/Display_Application_Lib/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := LCD_Display_V5_G070
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
LCD_Display_V5_G070.elf \

MAP_FILES += \
LCD_Display_V5_G070.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
LCD_Display_V5_G070.list \

OBJCOPY_HEX += \
LCD_Display_V5_G070.hex \

OBJCOPY_BIN += \
LCD_Display_V5_G070.bin \


# All Target
all: main-build

# Main-build Target
main-build: LCD_Display_V5_G070.elf secondary-outputs

# Tool invocations
LCD_Display_V5_G070.elf LCD_Display_V5_G070.map: $(OBJS) $(USER_OBJS) D:\Sharath\ kumar\cube_ide\LCD_Display_V5_G070\LCD_Display_V5_G070\STM32G070CBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "LCD_Display_V5_G070.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"D:\Sharath kumar\cube_ide\LCD_Display_V5_G070\LCD_Display_V5_G070\STM32G070CBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="LCD_Display_V5_G070.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

LCD_Display_V5_G070.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "LCD_Display_V5_G070.list"
	@echo 'Finished building: $@'
	@echo ' '

LCD_Display_V5_G070.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "LCD_Display_V5_G070.hex"
	@echo 'Finished building: $@'
	@echo ' '

LCD_Display_V5_G070.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "LCD_Display_V5_G070.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) LCD_Display_V5_G070.bin LCD_Display_V5_G070.elf LCD_Display_V5_G070.hex LCD_Display_V5_G070.list LCD_Display_V5_G070.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
