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

void init_buck_converter(const buck_converter_cfg_t *buck_converter_cfg_ptr);

void control_out_voltage_with_current_limit(void);

#endif /* APP_BUCK_CONVERTER_H_ */
