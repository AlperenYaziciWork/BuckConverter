/*
 * bsp_gpio.h
 *
 *  Created on: May 17, 2025
 *      Author: alperenyazici
 */

#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef enum
{
	PIN_0 = 0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_COUNT,
}gpio_pin_id_e;

typedef struct
{
	uint32_t 		Pin;
	GPIO_TypeDef* Port;
	uint32_t 	Mode;
	uint32_t 	Pull;
	uint32_t 	Speed;
}gpio_pin_cfg_t;

#define USED_GPIO_PIN_CLOCKS_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE();  __HAL_RCC_GPIOA_CLK_ENABLE(); // __HAL_RCC_GPIOB_CLK_ENABLE();

void init_gpio_pin(uint8_t bsp_gpio_pin_index);

#endif /* BSP_GPIO_H_ */
