/*
 * software_timer.h
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#ifndef SOFTWARE_TIMER_SOFTWARE_TIMER_H_
#define SOFTWARE_TIMER_SOFTWARE_TIMER_H_

#include "stdint.h"
#include "software_timer_cfg.h"



typedef uint32_t (*get_timer_tick_ms_func_t)(void);

typedef uint8_t software_timer_id_t;

typedef void (*timer_timeout_cb_func_t)(software_timer_id_t sw_timer_id);

typedef enum{

	TIMER_STATE_STOP_e,
	TIMER_STATE_RUNNING_e,
	TIMER_STATE_TIMEOUT_e,
	TIMER_STATE_ERROR_e,

}timer_state_e;

typedef enum{

	TIMER_RELOAD_MANUEL_e,	// it waits to be started by a user.
	TIMER_RELOAD_AUTO_e,     // reload this value to start_tick : current tick
	TIMER_RELOAD_PERIODIC_e, // reload this value to start_tick : start_tick + timeout_value

}timer_reload_option_e;

typedef struct{

	timer_reload_option_e reload_option;
	timer_timeout_cb_func_t timeout_callback_func;

}software_timer_cfg_t;

typedef struct{

	const software_timer_cfg_t *software_timer_cfg_ptr;
	get_timer_tick_ms_func_t get_timer_tick_ms_func;

}software_timer_general_cfg_t;

void init_software_timer_module(const software_timer_general_cfg_t *timer_general_cfg_ptr);

void start_software_timer(software_timer_id_t sw_timer_id,uint32_t timeout_value);

void stop_software_timer(software_timer_id_t sw_timer_id);

void run_all_software_timers(void);

timer_state_e check_status_of_software_timer(software_timer_id_t sw_timer_id);

#endif /* SOFTWARE_TIMER_SOFTWARE_TIMER_H_ */
