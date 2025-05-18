/*
 * app_buck_converter.h
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#ifndef APP_BUCK_CONVERTER_H_
#define APP_BUCK_CONVERTER_H_

#include "stdint.h"
#include "pid_controller.h"

typedef struct
{
	pid_controller_t *pid_out_voltage_cotroller_ptr;
	pid_controller_t *pid_out_current_cotroller_ptr;
	uint8_t period_time_process_of_controller_ms;
	float v_out_ref;
	float i_out_max;

}buck_converter_cfg_t;

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
void init_buck_converter(const buck_converter_cfg_t *buck_converter_cfg_ptr);

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
void control_out_voltage_with_current_limit(void);

#endif /* APP_BUCK_CONVERTER_H_ */
