################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/bsp_pwm_1/bsp_pwm.c 

OBJS += \
./Source/bsp_pwm_1/bsp_pwm.o 

C_DEPS += \
./Source/bsp_pwm_1/bsp_pwm.d 


# Each subdirectory must supply rules for building sources it contributes
Source/bsp_pwm_1/%.o Source/bsp_pwm_1/%.su Source/bsp_pwm_1/%.cyclo: ../Source/bsp_pwm_1/%.c Source/bsp_pwm_1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/alperenyazici/Desktop/saykal_buck_converter/Source/bsp_pwm_1" -I"/Users/alperenyazici/Desktop/saykal_buck_converter/Project_Configs" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-bsp_pwm_1

clean-Source-2f-bsp_pwm_1:
	-$(RM) ./Source/bsp_pwm_1/bsp_pwm.cyclo ./Source/bsp_pwm_1/bsp_pwm.d ./Source/bsp_pwm_1/bsp_pwm.o ./Source/bsp_pwm_1/bsp_pwm.su

.PHONY: clean-Source-2f-bsp_pwm_1

