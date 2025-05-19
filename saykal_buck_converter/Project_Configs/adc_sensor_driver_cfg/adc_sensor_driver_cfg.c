/*
 * adc_sensor_driver_cfg.c
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */



#include <device_drivers/adc_sensor_driver/adc_sensor_driver.h>
#include "adc_sensor_driver_cfg.h"
#include "bsp_adc.h"

const adc_sensor_driver_config_t g_adc_sensors_configuration[] =
{
	[BUCK_CONVERTOR_OUT_CURRENT_ACS724_SENSOR_ID] = {
		.raw_voltage_factor = 2U, // opamp used input of adc 
		.read_adc_sensor_raw_voltage_func = read_current_sense_adc_value,
		.reference_voltage_for_zero_output = 2.5f, // reference voltage
		.sensitivity_volt_per_output_unit = 0.1f
	},
	[BUCK_CONVERTOR_OUT_VOLTAGE_RESISTOR_SENSOR_ID] = {
		.raw_voltage_factor = 1U,
		.read_adc_sensor_raw_voltage_func = read_voltage_sense_adc_value,
		.reference_voltage_for_zero_output = 0.0f,
		.sensitivity_volt_per_output_unit = (1.0f/14.54f) // Maximum 48V ölçebilecek şekilde dirençler ayarlandı.
	},
	[TEMPERATURE_LM35_SENSOR_ID] = {
		.raw_voltage_factor = 1U, // no voltage factor
		.read_adc_sensor_raw_voltage_func = read_temperature_sense_adc_value,
		.reference_voltage_for_zero_output = 0.0f, // 0V -> 0 degree
		.sensitivity_volt_per_output_unit = 0.01f // 10mV per degree
	}
};
