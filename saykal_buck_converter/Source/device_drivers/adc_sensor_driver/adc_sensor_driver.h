/*
 * adc_sensor_driver.h
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#ifndef ADC_SENSOR_DRIVER_CS_H_
#define ADC_SENSOR_DRIVER_CS_H_

#include "bsp_adc.h"

typedef bsp_adc_status_e (*read_sensor_adc_raw_value_function_t)(float *raw_value_ptr);

typedef struct{
	read_sensor_adc_raw_value_function_t read_adc_sensor_raw_voltage_func;
	float sensitivity_volt_per_output_unit;
	float raw_voltage_factor;
	float reference_voltage_for_zero_output;

}adc_sensor_driver_config_t;

void read_adc_sensor_value(uint8_t sensor_id , float *sensor_value_ptr);

void init_adc_sensor_driver(const adc_sensor_driver_config_t *adc_sensors_config);

#endif /* ADC_SENSOR_DRIVER_CS_H_ */
