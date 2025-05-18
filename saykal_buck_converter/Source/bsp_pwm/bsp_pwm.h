/*
 * bsp_pwm.h
 *
 *  Created on: May 17, 2025
 *      Author: alperenyazici
 */

#ifndef BSP_PWM_BSP_PWM_H_
#define BSP_PWM_BSP_PWM_H_


#include "bsp_pwm_cfg.h"


#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef uint8_t bsp_pwm_channel_idx_t;

typedef struct 
{
	uint32_t timer_channel;
	bsp_pwm_channel_idx_t pwm_channel_id;// Must be unique for every pwm channel

}bsp_pwm_channel_t;


typedef struct
{
	const bsp_pwm_channel_t *pwm_channels_ptr;
	uint8_t total_timer_channel;

}bsp_pwm_timer_channel_config_t;


typedef struct
{
	TIM_TypeDef *timer_instance_ptr;
	uint8_t pwm_out_gpio_pin_id_in_bsp_gpio;
	bsp_pwm_timer_channel_config_t timer_channel_configs;
	uint32_t pwm_timer_prescalar;
	uint32_t pwm_timer_period;
	uint32_t pwm_timer_counter_direction_mode;

}bsp_pwm_config_t;


/**
 * @brief Initializes all configured PWM timers and GPIOs.
 *
 * @param[in] bsp_pwm_configs_ptr Pointer to array of PWM configurations.
 */
void init_bsp_pwm(bsp_pwm_config_t *bsp_pwm_configs_ptr);

/**
 * @brief Starts a specific PWM channel.
 *
 * @param[in] bsp_pwm_channel PWM channel to start.
 */
void start_pwm_channel(bsp_pwm_channel_idx_t bsp_pwm_channel);

/**
 * @brief Stops a specific PWM channel.
 *
 * @param[in] bsp_pwm_channel PWM channel to stop.
 */
void stop_pwm_channel(bsp_pwm_channel_idx_t bsp_pwm_channel);

/**
 * @brief Sets the duty cycle of a specific PWM channel.
 *
 * @param[in] bsp_pwm_channel PWM channel to set.
 * @param[in] duty_rate Duty cycle to set (range: 0.0 to 1.0).
 */
void set_pwm_duty(bsp_pwm_channel_idx_t bsp_pwm_channel,
				  float duty_rate);

#endif /* BSP_PWM_BSP_PWM_H_ */
