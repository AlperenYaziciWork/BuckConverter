################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/bsp_pwm/bsp_pwm.c 

OBJS += \
./Source/bsp_pwm/bsp_pwm.o 

C_DEPS += \
./Source/bsp_pwm/bsp_pwm.d 


# Each subdirectory must supply rules for building sources it contributes
Source/bsp_pwm/%.o Source/bsp_pwm/%.su Source/bsp_pwm/%.cyclo: ../Source/bsp_pwm/%.c Source/bsp_pwm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp_gpio" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp_pwm" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_pwm_config" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs/bsp_gpio_cfg" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-bsp_pwm

clean-Source-2f-bsp_pwm:
	-$(RM) ./Source/bsp_pwm/bsp_pwm.cyclo ./Source/bsp_pwm/bsp_pwm.d ./Source/bsp_pwm/bsp_pwm.o ./Source/bsp_pwm/bsp_pwm.su

.PHONY: clean-Source-2f-bsp_pwm

