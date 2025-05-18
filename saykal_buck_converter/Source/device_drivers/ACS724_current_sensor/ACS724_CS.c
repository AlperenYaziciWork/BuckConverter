#include "ACS724_CS.h"

static const ACS724_config_t *m_ACS724_CS_last_configs_ptr = NULL;

void init_ACS724_CS(const ACS724_config_t *ACS724_CS_configs_ptr)
{
	if(NULL == ACS724_CS_configs_ptr)
	{
		report_development_error();
		return;
	}

	m_ACS724_CS_last_configs_ptr = ACS724_CS_configs_ptr;
}

void read_current_value(uint8_t sensor_id , float *current_value_ptr)
{
	float read_data_for_adc_raw_voltage = 0.0f;
	bsp_adc_status_e raw_voltage_read_state = m_ACS724_CS_last_configs_ptr[sensor_id].
	read_current_sensor_raw_value(&read_data_for_adc_raw_voltage);

	float raw_voltage_factor = m_ACS724_CS_last_configs_ptr[sensor_id].raw_voltage_factor;
	float voltage_ref = m_ACS724_CS_last_configs_ptr[sensor_id].reference_voltage_for_zero_current;
	float volt_per_ampere = m_ACS724_CS_last_configs_ptr[sensor_id].sensitivity_volt_per_ampere;

	if(BSP_ADC_STATE_OK == raw_voltage_read_state)
	{
		*current_value_ptr =
			((read_data_for_adc_raw_voltage*raw_voltage_factor) - voltage_ref) / volt_per_ampere;
	}
	else
	{
		// low level notified an error already. It is not necessary in here.
	}
}

