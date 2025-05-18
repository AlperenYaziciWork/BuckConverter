/*
 * ACS724_CS_cfg.c
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */



#include "ACS724_CS.h"
#include "bsp_adc.h"

const ACS724_config_t ACS724_CS_configurations[] =
{
	{
		.raw_voltage_factor = 2U,
		.read_current_sensor_raw_value = read_current_sense_adc_value,
		.reference_voltage_for_zero_current = 2.5f,
		.sensitivity_volt_per_ampere = 0.1f
	}
};
