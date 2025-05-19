################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/bsp/bsp_adc/bsp_adc.c 

OBJS += \
./Source/bsp/bsp_adc/bsp_adc.o 

C_DEPS += \
./Source/bsp/bsp_adc/bsp_adc.d 


# Each subdirectory must supply rules for building sources it contributes
Source/bsp/bsp_adc/%.o Source/bsp/bsp_adc/%.su Source/bsp/bsp_adc/%.cyclo: ../Source/bsp/bsp_adc/%.c Source/bsp/bsp_adc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_pwm_config" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_gpio_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_gpio" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_adc" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_pwm" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/adc_sensor_driver_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/adc_sensor_driver" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/libraries/pid_controller" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/software_timer" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/software_timer_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/application/app_buck_converter" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/com_driver_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/communication_driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-bsp-2f-bsp_adc

clean-Source-2f-bsp-2f-bsp_adc:
	-$(RM) ./Source/bsp/bsp_adc/bsp_adc.cyclo ./Source/bsp/bsp_adc/bsp_adc.d ./Source/bsp/bsp_adc/bsp_adc.o ./Source/bsp/bsp_adc/bsp_adc.su

.PHONY: clean-Source-2f-bsp-2f-bsp_adc

