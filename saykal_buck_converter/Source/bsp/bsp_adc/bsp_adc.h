/*
 * bsp_adc.h
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#ifndef BSP_ADC_H_
#define BSP_ADC_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"


typedef enum{
    BSP_ADC_STATE_OK_e,
    BSP_ADC_STATE_ERROR_e,

}bsp_adc_status_e;


/**
 * @brief Initializes the ADC peripheral with predefined settings.
 *
 * This function configures ADC1 for multi-channel operation with 12-bit resolution
 * and sets various parameters such as scan mode, trigger source, and number of conversions.
 * 
 * @retval None
 */
void init_bsp_adc();

/**
 * @brief Reads the ADC value from the current sense channel.
 *
 * @param[out] voltage_value_ptr Pointer to store the ADC voltage value.
 * @retval BSP_ADC_STATE_OK_e if the conversion is successful.
 * @retval BSP_ADC_STATE_ERROR_e if the conversion fails.
 */
bsp_adc_status_e read_current_sense_adc_value(float *voltage_value_ptr);

/**
 * @brief Reads the ADC value from the voltage sense channel.
 *
 * @param[out] voltage_value_ptr Pointer to store the ADC voltage value.
 * @retval BSP_ADC_STATE_OK_e if the conversion is successful.
 * @retval BSP_ADC_STATE_ERROR_e if the conversion fails.
 */
bsp_adc_status_e read_voltage_sense_adc_value(float *voltage_value_ptr);

/**
 * @brief Reads the ADC value from the temperature sense channel.
 *
 * @param[out] voltage_value_ptr Pointer to store the ADC voltage value.
 * @retval BSP_ADC_STATE_OK_e if the conversion is successful.
 * @retval BSP_ADC_STATE_ERROR_e if the conversion fails.
 */
bsp_adc_status_e read_temperature_sense_adc_value(float *voltage_value_ptr);

#endif /* BSP_ADC_H_ */
