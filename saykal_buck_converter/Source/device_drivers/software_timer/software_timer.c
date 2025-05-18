/*
 * software_timer.c
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#include "software_timer.h"
#include "stddef.h"

typedef struct{

	uint32_t timeout_value;
	uint32_t start_tick;
	timer_state_e state;

}software_timer_t;

#ifndef SOFTWARE_TIMER_CNT
#define SOFTWARE_TIMER_CNT 0U
#endif

static software_timer_t m_software_timers[SOFTWARE_TIMER_CNT];

static software_timer_general_cfg_t *m_software_timer_general_config_ptr;

static void timer_timeout_process(software_timer_id_t sw_timer_id);

void init_software_timer_module(const software_timer_general_cfg_t *timer_general_cfg_ptr)
{
	if(NULL == timer_general_cfg_ptr)
	{
		report_development_error();
		return;
	}
	m_software_timer_general_config_ptr = (software_timer_general_cfg_t*)timer_general_cfg_ptr;
}

void start_software_timer(software_timer_id_t sw_timer_id,uint32_t timeout_value)
{
	m_software_timers[sw_timer_id].start_tick =
		m_software_timer_general_config_ptr->get_timer_tick_ms_func();

	m_software_timers[sw_timer_id].timeout_value = timeout_value;

	m_software_timers[sw_timer_id].state = TIMER_STATE_RUNNING;
}

void stop_software_timer(software_timer_id_t sw_timer_id)
{
	m_software_timers[sw_timer_id].state = TIMER_STATE_STOP;
}

void run_all_software_timers(void)
{
	for(uint8_t timer_idx = 0U; timer_idx < SOFTWARE_TIMER_CNT; timer_idx++)
	{
		if(TIMER_STATE_TIMEOUT == m_software_timers[timer_idx].state)
		{
			timer_timeout_process(timer_idx);
		}
	}
}

timer_state_e check_status_of_software_timer(software_timer_id_t sw_timer_id)
{
	return m_software_timers[sw_timer_id].state;
}

static void timer_timeout_process(software_timer_id_t sw_timer_id)
{
	timer_timeout_cb_func_t timer_callback_func =
			m_software_timer_general_config_ptr->parameters_ptr[sw_timer_id].
			timeout_callback_func;

	if(NULL != timer_callback_func)
	{
		timer_callback_func();
	}

	timer_reload_option_e timer_reload_option =
			m_software_timer_general_config_ptr->parameters_ptr[sw_timer_id].
			reload_option;

	if(TIMER_RELOAD_AUTO == timer_reload_option)
	{
		m_software_timers[sw_timer_id].start_tick =
				m_software_timer_general_config_ptr->get_timer_tick_ms_func();


		m_software_timers[sw_timer_id].state = TIMER_STATE_RUNNING;
	}
	else if(TIMER_RELOAD_PERIODIC == timer_reload_option)
	{
		m_software_timers[sw_timer_id].start_tick +=
			m_software_timers[sw_timer_id].timeout_value;


		m_software_timers[sw_timer_id].state = TIMER_STATE_RUNNING;
	}
	else
	{
		/* MISRA */
	}
}
