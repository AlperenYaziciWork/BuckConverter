/*
 * software_timer_cfg.c
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#include "software_timer.h"
#include "stm32f4xx_hal.h"
#include "app_buck_converter.h"
#include "com_driver.h"

const software_timer_cfg_t software_timers_configs[] =
{
	{
		.reload_option = TIMER_RELOAD_PERIODIC,
		.timeout_callback_func = control_out_voltage_with_current_limit,
	},
	{
		.reload_option = TIMER_RELOAD_PERIODIC,
		.timeout_callback_func = send_periodic_message_timeout_cb,
	},
};

const software_timer_general_cfg_t g_software_timer_general_config =
{
	.get_timer_tick_ms_func = HAL_GetTick,
	.software_timer_cfg_ptr = software_timers_configs,
};
