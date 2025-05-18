/*
 * adc_sensor_driver.h
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#ifndef ADC_SENSOR_DRIVER_CS_H_
#define ADC_SENSOR_DRIVER_CS_H_

#include "bsp_adc.h"
#include "adc_sensor_driver_cfg.h"

typedef bsp_adc_status_e (*read_sensor_adc_raw_value_function_t)(float *raw_value_ptr);

typedef enum
{
	ADC_SENSOR_ERROR,
	ADC_SENSOR_OK

}adc_sensor_state_e;


typedef struct{
	read_sensor_adc_raw_value_function_t read_adc_sensor_raw_voltage_func;
	float sensitivity_volt_per_output_unit;
	float raw_voltage_factor;
	float reference_voltage_for_zero_output;

}adc_sensor_driver_config_t;


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
void init_adc_sensor_driver(const adc_sensor_driver_config_t *adc_sensors_config);

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
adc_sensor_state_e read_adc_sensor_value(uint8_t sensor_id , float *sensor_value_ptr);


#endif /* ADC_SENSOR_DRIVER_CS_H_ */
