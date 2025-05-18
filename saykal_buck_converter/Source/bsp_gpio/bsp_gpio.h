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


/**
 * @brief Initializes the GPIO configuration table.
 *
 * Stores the pointer to the array of GPIO pin configurations to be used in further operations.
 *
 * @param[in] gpio_pin_configs_ptr Pointer to the array of GPIO pin configurations.
 */
void init_bsp_gpio(const gpio_pin_cfg_t *gpio_pin_configs_ptr);

/**
 * @brief Initializes a specific GPIO pin based on its configuration.
 *
 * Configures the selected GPIO pin using the settings stored in the configuration table.
 *
 * @param[in] pin_no Index and unique identifier of the GPIO pin in the configuration table.
 */
void init_gpio_pin(uint8_t pin_no);

/**
 * @brief Writes a value to a specific GPIO pin.
 *
 * Sets the output state of the specified GPIO pin, unless it is configured as alternate function (AF).
 *
 * @param[in] pin_no Index and unique identifier of the GPIO pin in the configuration table.
 * @param[in] pin_status Desired output state of the pin (e.g., GPIO_PIN_SET or GPIO_PIN_RESET).
 */
void write_gpio_pin(uint8_t pin_no , uint8_t pin_status);

/**
 * @brief Reads the current state of a specific GPIO pin.
 *
 * Returns the logical state (set or reset) of the selected GPIO pin.
 *
 * @param[in] pin_no Index and unique identifier of the GPIO pin in the configuration table.
 * @retval uint8_t The current state of the GPIO pin (GPIO_PIN_SET or GPIO_PIN_RESET).
 */
uint8_t read_gpio_pin(uint8_t pin_no);

#endif /* BSP_GPIO_H_ */
