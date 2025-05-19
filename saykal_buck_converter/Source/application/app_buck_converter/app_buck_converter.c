/**
 * @file app_buck_converter.c
 * @brief Buck Converter Application Layer
 *
 * This module implements the application logic for controlling a buck converter
 * using a cascaded PID control approach with integrated overcurrent protection.
 *
 * The system reads output voltage and current via ADC sensors and applies:
 * - An outer PID controller to regulate the output voltage.
 * - An inner PID controller to limit output current based on the voltage controller’s output.
 *
 * The resulting control signal is used to set the PWM duty cycle for the buck converter's MOSFET.
 *
 * Key features:
 * - Cascaded voltage and current control loop
 * - Periodic control execution via software timer
 * - Overcurrent detection with configurable persistence threshold
 * - Robust error handling and protection against sensor or control failures
 *
 * @author Alperen Yazıcı
 * @date May 18, 2025
 */

#include "app_buck_converter.h"
#include "adc_sensor_driver.h"
#include "bsp_pwm.h"
#include "com_driver.h"
#include "stdbool.h"
/**
 * @brief Pointer to the active buck converter configuration.
 */
static buck_converter_cfg_t *m_buck_converter_cfg = NULL;

/**
 * @brief Indicates if a critical error (e.g., overcurrent) has been detected.
 *
 * If true, control loop will stop to protect the system.
 */
static bool is_cricial_error_detected = false;

/**
 * @brief Monitors output current and detects overcurrent condition.
 *
 * This is a basic counter-based filter that checks whether the sensed current exceeds
 * a defined overcurrent threshold continuously over a number of cycles.
 *
 * @param[in] sensed_output_current The measured output current value.
 * @param[in] over_current_value The threshold value for overcurrent detection.
 * @param[in] over_current_occurance_time_min Minimum number of consecutive detections to confirm overcurrent.
 *
 * @retval true  Overcurrent condition detected.
 * @retval false No overcurrent condition detected.
 */
static bool monitor_current_to_detect_over_current(float sensed_output_current ,
												   float over_current_value,
												   uint16_t over_current_occurance_time_min);
/**
 * @brief Initializes the buck converter application with the given configuration.
 *
 * This function sets the buck converter configuration, starts the corresponding PWM channel for the MOSFET,
 * and starts a software timer to periodically execute the control loop.
 *
 * @param[in] buck_converter_cfg_ptr Pointer to the configuration structure of the buck converter.
 *                                   Must not be NULL.
 *
 * @retval None
 */
void init_buck_converter(const buck_converter_cfg_t *buck_converter_cfg_ptr)
{
	if(NULL != buck_converter_cfg_ptr)
	{
		is_cricial_error_detected = false;
		m_buck_converter_cfg = (buck_converter_cfg_t*)buck_converter_cfg_ptr;
		start_pwm_channel(PWM_TIMER_ID_FOR_BUCK_MOSFET);
		start_software_timer(BUCK_CONVERTER_PID_SOFTWARE_TIMER_ID ,
							 m_buck_converter_cfg->period_time_process_of_controller_ms);
	}
	else
	{
		report_development_error();
	}
}

/**
 * @brief Performs cascaded PID control for output voltage with current limiting.
 *
 * This function implements a cascaded control loop where the output voltage is regulated
 * using an outer PID loop that generates a current reference. This reference is then used
 * by an inner PID loop to control the output current. The result is translated into a PWM duty cycle
 * to drive the buck converter MOSFET.
 *
 * It reads both output voltage and output current via the ADC sensor driver.
 *
 * It is called by software timer (BUCK_CONVERTER_PID_SOFTWARE_TIMER_ID) periodically.
 *
 * @retval None
 */
void control_out_voltage_with_current_limit(software_timer_id_t sw_timer_id)
{
	(void)sw_timer_id;

	if(true == is_cricial_error_detected)
	{
		return; // This is exist for double prevention,
		//because system will be in ERROR mode when critical error is detected
	}

	float sensed_output_voltage = 0.0f;

	adc_sensor_state_e adc_read_state =
		read_adc_sensor_value(BUCK_CONVERTOR_OUT_VOLTAGE_RESISTOR_SENSOR_ID , &sensed_output_voltage);

	if(ADC_SENSOR_ERROR == adc_read_state)
	{
		report_sensor_error();
		return;
	}

	send_signal_over_com(COM_BUCK_OUTPUT_VOLTAGE_SIGNAL_ID,sensed_output_voltage); 

	float i_out_reference = PID_Step(m_buck_converter_cfg->pid_out_voltage_cotroller_ptr,
									 sensed_output_voltage,
									 m_buck_converter_cfg->v_out_ref);

	float sensed_output_current = 0.0f;

	adc_read_state =
			read_adc_sensor_value(BUCK_CONVERTOR_OUT_CURRENT_ACS724_SENSOR_ID , &sensed_output_current);

	if(ADC_SENSOR_ERROR == adc_read_state)
	{
		report_sensor_error();
		return;
	}

	send_signal_over_com(COM_BUCK_OUTPUT_CURRENT_SIGNAL_ID,sensed_output_current);
	//TODO : current monitor to detect over current
	bool is_over_current =
		monitor_current_to_detect_over_current(sensed_output_current ,
											   m_buck_converter_cfg->i_out_max,
											   m_buck_converter_cfg->over_current_occurence_time_min);

	if(true == is_over_current)
	{
		set_pwm_duty(PWM_TIMER_ID_FOR_BUCK_MOSFET , 0.0f);
		stop_pwm_channel(PWM_TIMER_ID_FOR_BUCK_MOSFET);
		report_over_current();
		is_cricial_error_detected = true;
		return;
	}

	float duty_reference = PID_Step(m_buck_converter_cfg->pid_out_current_cotroller_ptr,
									sensed_output_current,
									i_out_reference);

	set_pwm_duty(PWM_TIMER_ID_FOR_BUCK_MOSFET , duty_reference);
}

static bool monitor_current_to_detect_over_current(float sensed_output_current ,
												   float over_current_value,
												   uint16_t over_current_occurance_time_min)
{
	bool is_over_current_detected = false;

	static uint16_t over_curent_detect_cnt = 0U;
	if(sensed_output_current > over_current_value)
	{
		over_curent_detect_cnt ++;
	}
	else
	{
		over_curent_detect_cnt = 0;
	}

	if(over_current_occurance_time_min <= over_curent_detect_cnt)
	{
		is_over_current_detected = true;
	}

	return is_over_current_detected;

}
