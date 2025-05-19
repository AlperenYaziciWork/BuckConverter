################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Source/libraries/pid_controller/subdir.mk
-include Source/device_drivers/software_timer/subdir.mk
-include Source/device_drivers/communication_driver/subdir.mk
-include Source/device_drivers/adc_sensor_driver/subdir.mk
-include Source/bsp/bsp_pwm/subdir.mk
-include Source/bsp/bsp_gpio/subdir.mk
-include Source/bsp/bsp_adc/subdir.mk
-include Source/application/app_buck_converter/subdir.mk
-include Project_Configs/software_timer_cfg/subdir.mk
-include Project_Configs/com_driver_cfg/subdir.mk
-include Project_Configs/bsp_pwm_config/subdir.mk
-include Project_Configs/bsp_gpio_cfg/subdir.mk
-include Project_Configs/app_buck_converter_cfg/subdir.mk
-include Project_Configs/adc_sensor_driver_cfg/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
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


BUILD_ARTIFACT_NAME := saykal_buck_converter
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
saykal_buck_converter.elf \

MAP_FILES += \
saykal_buck_converter.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
saykal_buck_converter.list \


# All Target
all: main-build

# Main-build Target
main-build: saykal_buck_converter.elf secondary-outputs

# Tool invocations
saykal_buck_converter.elf saykal_buck_converter.map: $(OBJS) $(USER_OBJS) /Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/STM32F407IGHX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "saykal_buck_converter.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/STM32F407IGHX_FLASH.ld" --specs=nosys.specs -Wl,-Map="saykal_buck_converter.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

saykal_buck_converter.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "saykal_buck_converter.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout saykal_buck_converter.elf saykal_buck_converter.list saykal_buck_converter.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
