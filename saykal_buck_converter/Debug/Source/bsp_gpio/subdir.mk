################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/bsp_gpio/bsp_gpio.c 

OBJS += \
./Source/bsp_gpio/bsp_gpio.o 

C_DEPS += \
./Source/bsp_gpio/bsp_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
Source/bsp_gpio/%.o Source/bsp_gpio/%.su Source/bsp_gpio/%.cyclo: ../Source/bsp_gpio/%.c Source/bsp_gpio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Project_Configs" -I"/Users/alperenyazici/Documents/GitHub/BuckConverter/saykal_buck_converter/Source/bsp_gpio" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-bsp_gpio

clean-Source-2f-bsp_gpio:
	-$(RM) ./Source/bsp_gpio/bsp_gpio.cyclo ./Source/bsp_gpio/bsp_gpio.d ./Source/bsp_gpio/bsp_gpio.o ./Source/bsp_gpio/bsp_gpio.su

.PHONY: clean-Source-2f-bsp_gpio

