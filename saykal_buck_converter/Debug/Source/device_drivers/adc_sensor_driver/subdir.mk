################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/device_drivers/adc_sensor_driver/adc_sensor_driver.c 

OBJS += \
./Source/device_drivers/adc_sensor_driver/adc_sensor_driver.o 

C_DEPS += \
./Source/device_drivers/adc_sensor_driver/adc_sensor_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Source/device_drivers/adc_sensor_driver/%.o Source/device_drivers/adc_sensor_driver/%.su Source/device_drivers/adc_sensor_driver/%.cyclo: ../Source/device_drivers/adc_sensor_driver/%.c Source/device_drivers/adc_sensor_driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_pwm_config" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_gpio_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_gpio" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_adc" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_pwm" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/adc_sensor_driver_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/adc_sensor_driver" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/libraries/pid_controller" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/software_timer" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/software_timer_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/application/app_buck_converter" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/com_driver_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/communication_driver" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_can_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_can" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/system/error_manager" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/system/system_manager" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-device_drivers-2f-adc_sensor_driver

clean-Source-2f-device_drivers-2f-adc_sensor_driver:
	-$(RM) ./Source/device_drivers/adc_sensor_driver/adc_sensor_driver.cyclo ./Source/device_drivers/adc_sensor_driver/adc_sensor_driver.d ./Source/device_drivers/adc_sensor_driver/adc_sensor_driver.o ./Source/device_drivers/adc_sensor_driver/adc_sensor_driver.su

.PHONY: clean-Source-2f-device_drivers-2f-adc_sensor_driver

