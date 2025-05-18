################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Configs/bsp_pwm_config/bsp_pwm_cfg.c 

OBJS += \
./Project_Configs/bsp_pwm_config/bsp_pwm_cfg.o 

C_DEPS += \
./Project_Configs/bsp_pwm_config/bsp_pwm_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Configs/bsp_pwm_config/%.o Project_Configs/bsp_pwm_config/%.su Project_Configs/bsp_pwm_config/%.cyclo: ../Project_Configs/bsp_pwm_config/%.c Project_Configs/bsp_pwm_config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_pwm_config" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_gpio_cfg" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_gpio" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_adc" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp/bsp_pwm" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/device_drivers/ACS724_current_sensor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Project_Configs-2f-bsp_pwm_config

clean-Project_Configs-2f-bsp_pwm_config:
	-$(RM) ./Project_Configs/bsp_pwm_config/bsp_pwm_cfg.cyclo ./Project_Configs/bsp_pwm_config/bsp_pwm_cfg.d ./Project_Configs/bsp_pwm_config/bsp_pwm_cfg.o ./Project_Configs/bsp_pwm_config/bsp_pwm_cfg.su

.PHONY: clean-Project_Configs-2f-bsp_pwm_config

