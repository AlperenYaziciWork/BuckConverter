################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f407ighx.s 

OBJS += \
./Core/Startup/startup_stm32f407ighx.o 

S_DEPS += \
./Core/Startup/startup_stm32f407ighx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_pwm_config" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_gpio_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_gpio" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_adc" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_pwm" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/adc_sensor_driver_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/adc_sensor_driver" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/libraries/pid_controller" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/software_timer" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/software_timer_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/application/app_buck_converter" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/com_driver_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/communication_driver" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_can_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_can" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/system/error_manager" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/system/system_manager" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f407ighx.d ./Core/Startup/startup_stm32f407ighx.o

.PHONY: clean-Core-2f-Startup

