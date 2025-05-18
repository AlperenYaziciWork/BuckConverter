

#include "adc_sensor_driver.h"

static const adc_sensor_driver_config_t *m_adc_sensor_driver_configs_ptr = NULL;

void init_adc_sensor_driver(const adc_sensor_driver_config_t *adc_sensors_config)
{
	if(NULL == adc_sensors_config)
	{
		report_development_error();
		return;
	}

	m_adc_sensor_driver_configs_ptr = adc_sensors_config;
}

void read_adc_sensor_value(uint8_t sensor_id , float *sensor_value_ptr)
{
	float read_data_for_adc_raw_voltage = 0.0f;
	bsp_adc_status_e raw_voltage_read_state = m_adc_sensor_driver_configs_ptr[sensor_id].
	read_adc_sensor_raw_voltage_func(&read_data_for_adc_raw_voltage);

	float raw_voltage_factor = m_adc_sensor_driver_configs_ptr[sensor_id].raw_voltage_factor;
	float voltage_ref = m_adc_sensor_driver_configs_ptr[sensor_id].reference_voltage_for_zero_output;
	float volt_per_output_unit = m_adc_sensor_driver_configs_ptr[sensor_id].sensitivity_volt_per_output_unit;

	if(BSP_ADC_STATE_OK == raw_voltage_read_state)
	{
		*sensor_value_ptr =
			((read_data_for_adc_raw_voltage*raw_voltage_factor) - voltage_ref) / volt_per_output_unit;
	}
	else
	{
		// low level notified an error already. It is not necessary in here.
	}
}


