/*
 * app_buck_converter_cfg.c
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */


#include "app_buck_converter.h"

static pid_controller_t m_pid_voltage_controller =
{
	.Kp = 3,
	.Ki = 0.02,
	.Kd = 0.1,
	.Kaw = 0.02,
	.TimeStep = 20,
	.controller_output_max = 9.98f, // voltage controller output uses as output current reference
	.controller_output_min = 0.0f, // voltage controller output uses as output current reference
};

static pid_controller_t m_pid_current_controller =
{
	.Kp = 3,
	.Ki = 0.02,
	.Kd = 0.1,
	.Kaw = 0.02,
	.TimeStep = 20,
	.controller_output_max = 0.95f, // current controller output uses as output duty
	.controller_output_min = 0.0f, // current controller output uses as output duty
};

const buck_converter_cfg_t g_buck_converter_config =
{
	.i_out_max = 9.98f,
	.v_out_ref = 24.0f,
	.period_time_process_of_controller_ms = 20,
	.pid_out_voltage_cotroller_ptr = &m_pid_voltage_controller,
	.pid_out_current_cotroller_ptr = &m_pid_current_controller,
};
