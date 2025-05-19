

#include "adc_sensor_driver.h"

#include "error_manager.h"


/**
 * @brief Pointer to the configuration array holding all ADC sensors parameters.
 */
static const adc_sensor_driver_config_t *m_adc_sensor_driver_configs_ptr = NULL;

/**
 * @brief Initializes the ADC sensor driver with the provided configuration.
 * 
 * This function stores the pointer to the array of ADC sensor configurations
 * that contain the necessary calibration and function references to read and convert
 * sensor values.
 * 
 * @param[in] adc_sensors_config Pointer to an array of ADC sensor driver configuration structures.
 *                               Must not be NULL.
 * 
 * @retval None
 */
void init_adc_sensor_driver(const adc_sensor_driver_config_t *adc_sensors_config)
{
	if(NULL == adc_sensors_config)
	{
		report_development_error();
		return;
	}

	m_adc_sensor_driver_configs_ptr = adc_sensors_config;
}

/**
 * @brief Reads and converts the ADC sensor value for a given sensor ID.
 * 
 * This function uses the function pointer defined in the configuration to obtain the raw voltage
 * value from the hardware ADC, then applies scaling and offset to convert it into a physical
 * sensor value (e.g., temperature, current, etc.).
 * 
 * The conversion is done using the following formula:
 * @code
 *     sensor_value = ((raw_voltage * raw_voltage_factor) - reference_voltage) / sensitivity
 * @endcode
 * 
 * @param[in]  sensor_id         Index of the sensor in the configuration array (used as a unique ID).
 * @param[out] sensor_value_ptr Pointer to a float variable where the calculated sensor value will be stored.
 *                               Must not be NULL.
 * 
 * @retval None
 */
adc_sensor_state_e read_adc_sensor_value(uint8_t sensor_id , float *sensor_value_ptr)
{
	float read_data_for_adc_raw_voltage = 0.0f;
	bsp_adc_status_e raw_voltage_read_state = m_adc_sensor_driver_configs_ptr[sensor_id].
	read_adc_sensor_raw_voltage_func(&read_data_for_adc_raw_voltage);

	float raw_voltage_factor = m_adc_sensor_driver_configs_ptr[sensor_id].raw_voltage_factor;
	float voltage_ref = m_adc_sensor_driver_configs_ptr[sensor_id].reference_voltage_for_zero_output;
	float volt_per_output_unit = m_adc_sensor_driver_configs_ptr[sensor_id].sensitivity_volt_per_output_unit;

	adc_sensor_state_e success_status = ADC_SENSOR_OK;

	if(BSP_ADC_STATE_OK == raw_voltage_read_state)
	{
		*sensor_value_ptr =
			((read_data_for_adc_raw_voltage*raw_voltage_factor) - voltage_ref) / volt_per_output_unit;

	}
	else
	{
		// low level notified an error already. It is not necessary in here.
		success_status = ADC_SENSOR_ERROR;
	}

	return success_status;
}


