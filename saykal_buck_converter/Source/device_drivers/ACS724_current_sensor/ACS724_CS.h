/*
 * ACS724_CS.h
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#ifndef ACS724_CS_H_
#define ACS724_CS_H_

#include "bsp_adc.h"

typedef bsp_adc_status_e (*read_sensor_adc_raw_value_function_t)(float *raw_value_ptr);

typedef struct{
	read_sensor_adc_raw_value_function_t read_current_sensor_raw_value;
	float sensitivity_volt_per_ampere;
	float raw_voltage_factor;
	float reference_voltage_for_zero_current;

}ACS724_config_t;

void read_current_value(uint8_t sensor_id , float *current_value_ptr);

#endif /* ACS724_CS_H_ */
