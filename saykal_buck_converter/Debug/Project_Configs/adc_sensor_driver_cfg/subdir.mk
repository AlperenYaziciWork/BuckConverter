################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Configs/adc_sensor_driver_cfg/adc_sensor_driver_cfg.c 

OBJS += \
./Project_Configs/adc_sensor_driver_cfg/adc_sensor_driver_cfg.o 

C_DEPS += \
./Project_Configs/adc_sensor_driver_cfg/adc_sensor_driver_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Configs/adc_sensor_driver_cfg/%.o Project_Configs/adc_sensor_driver_cfg/%.su Project_Configs/adc_sensor_driver_cfg/%.cyclo: ../Project_Configs/adc_sensor_driver_cfg/%.c Project_Configs/adc_sensor_driver_cfg/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_pwm_config" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_gpio_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_gpio" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_adc" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_pwm" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/adc_sensor_driver_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/adc_sensor_driver" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/libraries/pid_controller" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/software_timer" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/software_timer_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/application/app_buck_converter" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/com_driver_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/communication_driver" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_can_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_can" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Project_Configs-2f-adc_sensor_driver_cfg

clean-Project_Configs-2f-adc_sensor_driver_cfg:
	-$(RM) ./Project_Configs/adc_sensor_driver_cfg/adc_sensor_driver_cfg.cyclo ./Project_Configs/adc_sensor_driver_cfg/adc_sensor_driver_cfg.d ./Project_Configs/adc_sensor_driver_cfg/adc_sensor_driver_cfg.o ./Project_Configs/adc_sensor_driver_cfg/adc_sensor_driver_cfg.su

.PHONY: clean-Project_Configs-2f-adc_sensor_driver_cfg

