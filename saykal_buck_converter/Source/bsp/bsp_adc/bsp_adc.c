
#include "bsp_adc.h"

#define RAW_TO_VOLTAGE_FACTOR	3.3f/4095

/** @brief Rank definitions for ADC channels. */
#define ADC_CHANNEL_FIRST_RANK 1U
#define ADC_CHANNEL_SECOND_RANK 2U
#define ADC_CHANNEL_THIRD_RANK 3U

/** 
 * @brief ADC handle for ADC1. 
 */
static ADC_HandleTypeDef m_hadc1;

/**
 * @brief Configures the ADC channel used for current sensing.
 * @note  This function is used internally before reading current sensing value.
 */
static void configure_current_sense_adc_channel();

/**
 * @brief Configures the ADC channel used for voltage sensing.
 * @note  This function is used internally before reading voltage sensing value.
 */
static void configure_voltage_sense_adc_channel();

/**
 * @brief Configures the ADC channel used for temperature sensing.
 * @note  This function is used internally before reading temperature sensing value.
 */
static void configure_temperature_sense_adc_channel();

/**
 * @brief Initializes the ADC peripheral with predefined settings.
 *
 * This function configures ADC1 for multi-channel operation with 12-bit resolution
 * and sets various parameters such as scan mode, trigger source, and number of conversions.
 * 
 * @retval None
 */
void init_bsp_adc()
{
    /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
     */
    m_hadc1.Instance = ADC1;
    m_hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    m_hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    m_hadc1.Init.ScanConvMode = ENABLE;
    m_hadc1.Init.ContinuousConvMode = DISABLE;
    m_hadc1.Init.DiscontinuousConvMode = DISABLE;
    m_hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    m_hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    m_hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    m_hadc1.Init.NbrOfConversion = 3U;
    m_hadc1.Init.DMAContinuousRequests = DISABLE;
    m_hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init(&m_hadc1) != HAL_OK)
    {
    Error_Handler();
    }

}

/**
 * @brief Reads the ADC value from the current sense channel.
 *
 * @param[out] raw_value Pointer to store the ADC voltage value.
 * @retval BSP_ADC_STATE_OK if the conversion is successful.
 * @retval BSP_ADC_STATE_ERROR if the conversion fails.
 */
bsp_adc_status_e read_current_sense_adc_value(float *voltage_value_ptr)
{
    bsp_adc_status_e read_status = BSP_ADC_STATE_ERROR;
    configure_current_sense_adc_channel();
    HAL_ADC_Start(&m_hadc1);
    HAL_StatusTypeDef poll_state =
        HAL_ADC_PollForConversion(&m_hadc1,5U);

    if(HAL_OK == poll_state)
    {
    	*voltage_value_ptr = RAW_TO_VOLTAGE_FACTOR * HAL_ADC_GetValue(&m_hadc1);
        read_status = BSP_ADC_STATE_OK;
    }

    HAL_ADC_Stop(&m_hadc1);

    return read_status;
}

/**
 * @brief Reads the ADC value from the voltage sense channel.
 *
 * @param[out] voltage_value_ptr Pointer to store the ADC voltage value.
 * @retval BSP_ADC_STATE_OK if the conversion is successful.
 * @retval BSP_ADC_STATE_ERROR if the conversion fails.
 */
bsp_adc_status_e read_voltage_sense_adc_value(float *voltage_value_ptr)
{
    bsp_adc_status_e read_status = BSP_ADC_STATE_ERROR;
    configure_voltage_sense_adc_channel();
    HAL_ADC_Start(&m_hadc1);
    HAL_StatusTypeDef poll_state =
        HAL_ADC_PollForConversion(&m_hadc1,5U);

    if(HAL_OK == poll_state)
    {
    	*voltage_value_ptr = RAW_TO_VOLTAGE_FACTOR * HAL_ADC_GetValue(&m_hadc1);
        read_status = BSP_ADC_STATE_OK;
    }

    HAL_ADC_Stop(&m_hadc1);

    return read_status;
}

/**
 * @brief Reads the ADC value from the temperature sense channel.
 *
 * @param[out] voltage_value_ptr Pointer to store the ADC voltage value.
 * @retval BSP_ADC_STATE_OK if the conversion is successful.
 * @retval BSP_ADC_STATE_ERROR if the conversion fails.
 */
bsp_adc_status_e read_temperature_sense_adc_value(float *voltage_value_ptr)
{
    bsp_adc_status_e read_status = BSP_ADC_STATE_ERROR;
    configure_temperature_sense_adc_channel();
    HAL_ADC_Start(&m_hadc1);
    HAL_StatusTypeDef poll_state =
        HAL_ADC_PollForConversion(&m_hadc1,5U);

    if(HAL_OK == poll_state)
    {
    	*voltage_value_ptr = RAW_TO_VOLTAGE_FACTOR * HAL_ADC_GetValue(&m_hadc1);
        read_status = BSP_ADC_STATE_OK;
    }

    HAL_ADC_Stop(&m_hadc1);

    return read_status;
}

/**
 * @brief Configures the ADC channel and sampling time for current sensing.
 * @note  Sets the rank and channel to ADC_CHANNEL_1 with a short sampling time.
 */
static void configure_current_sense_adc_channel()
{
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
     */
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = ADC_CHANNEL_FIRST_RANK;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&m_hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Configures the ADC channel and sampling time for voltage sensing.
 * @note  Sets the rank and channel to ADC_CHANNEL_2 with medium sampling time.
 */
static void configure_voltage_sense_adc_channel()
{
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
     */
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_2;
    sConfig.Rank = ADC_CHANNEL_SECOND_RANK;
    sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
    if (HAL_ADC_ConfigChannel(&m_hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Configures the ADC channel and sampling time for temperature sensing.
 * @note  Sets the rank and channel to ADC_CHANNEL_3 with a long sampling time.
 */
static void configure_temperature_sense_adc_channel()
{
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
     */
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_3;
    sConfig.Rank = ADC_CHANNEL_THIRD_RANK;
    sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
    if (HAL_ADC_ConfigChannel(&m_hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

