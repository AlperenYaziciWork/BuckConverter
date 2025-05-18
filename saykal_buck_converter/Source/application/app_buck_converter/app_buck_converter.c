/*
 * app_buck_converter.c
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#include "app_buck_converter.h"
#include "software_timer.h"
#include "adc_sensor_driver.h"
#include "bsp_pwm.h"

static buck_converter_cfg_t *m_buck_converter_cfg = NULL;

void init_buck_converter(const buck_converter_cfg_t *buck_converter_cfg_ptr)
{
	if(NULL != buck_converter_cfg_ptr)
	{
		m_buck_converter_cfg = buck_converter_cfg_ptr;
		start_pwm_channel(PWM_TIMER_ID_FOR_BUCK_MOSFET);
		start_software_timer(BUCK_CONVERTER_PID_SOFTWARE_TIMER_ID ,
							 m_buck_converter_cfg->period_time_process_of_controller_ms);
	}
	else
	{
		report_development_error();
	}
}

void control_out_voltage_with_current_limit(void)
{
	float sensed_output_voltage = 0.0f;

	read_adc_sensor_value(BUCK_CONVERTOR_OUT_VOLTAGE_RESISTOR_SENSOR_ID , &sensed_output_voltage);

	float i_out_reference = PID_Step(m_buck_converter_cfg->pid_out_voltage_cotroller_ptr,
									 sensed_output_voltage,
									 m_buck_converter_cfg->v_out_ref);

	float sensed_output_current = 0.0f;

	read_adc_sensor_value(BUCK_CONVERTOR_OUT_CURRENT_ACS724_SENSOR_ID , &sensed_output_current);

	float duty_reference = PID_Step(m_buck_converter_cfg->pid_out_current_cotroller_ptr,
									sensed_output_current,
									i_out_reference);

	set_pwm_duty(PWM_TIMER_ID_FOR_BUCK_MOSFET , duty_reference);
}
