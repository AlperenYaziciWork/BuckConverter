#include "bsp_gpio.h"

#define ERROR_STATE_ABNORMAL_RETUN_VALUE 0xFFU

/**
 * @brief Pointer to the last used GPIO pin configuration table.
 *
 * This global variable holds the address of the GPIO configuration table passed to 
 * init_bsp_gpio(). It is used by other GPIO-related functions to access configuration data.
 */
static const gpio_pin_cfg_t *m_last_gpio_pin_config_ptr = NULL;


/**
 * @brief Enables the clock for the specified GPIO port.
 *
 * This function activates the peripheral clock for the GPIO port used in pin initialization.
 * If the provided port is not supported, a development error is reported.
 *
 * @param[in] gpio_port Pointer to the GPIO port (e.g., GPIOA, GPIOB, etc.).
 */
static void enable_used_gpio_pin_clock(GPIO_TypeDef* gpio_port);

/**
 * @brief Initializes the GPIO configuration table.
 *
 * Stores the pointer to the array of GPIO pin configurations to be used in further operations.
 *
 * @param[in] gpio_pin_configs_ptr Pointer to the array of GPIO pin configurations.
 */
void init_bsp_gpio(const gpio_pin_cfg_t *gpio_pin_configs_ptr)
{
    if(NULL != gpio_pin_configs_ptr)
    {
        m_last_gpio_pin_config_ptr = gpio_pin_configs_ptr;
    }
}

/**
 * @brief Initializes a specific GPIO pin based on its configuration.
 *
 * Configures the selected GPIO pin using the settings stored in the configuration table.
 *
 * @param[in] pin_no Index and unique identifier of the GPIO pin in the configuration table.
 */
void init_gpio_pin(uint8_t pin_no)
{
  if(NULL == m_last_gpio_pin_config_ptr)
  {
	  report_development_error();
	  return;
  }

  enable_used_gpio_pin_clock(m_last_gpio_pin_config_ptr[pin_no].Port);

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = m_last_gpio_pin_config_ptr[pin_no].Pin;
  GPIO_InitStruct.Mode = m_last_gpio_pin_config_ptr[pin_no].Mode; 
  GPIO_InitStruct.Pull = m_last_gpio_pin_config_ptr[pin_no].Pull;  
  HAL_GPIO_Init(m_last_gpio_pin_config_ptr[pin_no].Port, &GPIO_InitStruct);
}

/**
 * @brief Writes a value to a specific GPIO pin.
 *
 * Sets the output state of the specified GPIO pin, unless it is configured as alternate function (AF).
 *
 * @param[in] pin_no Index and unique identifier of the GPIO pin in the configuration table.
 * @param[in] pin_status Desired output state of the pin (e.g., GPIO_PIN_SET or GPIO_PIN_RESET).
 */
void write_gpio_pin(uint8_t pin_no , uint8_t pin_status)
{
	if(NULL == m_last_gpio_pin_config_ptr)
	{
	  report_development_error();
	  return ERROR_STATE_ABNORMAL_RETUN_VALUE;
	}

	if(GPIO_MODE_AF_PP != m_last_gpio_pin_config_ptr[pin_no].Mode)
	{
		HAL_GPIO_WritePin(m_last_gpio_pin_config_ptr[pin_no].Port,
						  m_last_gpio_pin_config_ptr[pin_no].Pin,
						  pin_status);
	}
	else
	{
		report_development_error();
	}

}

/**
 * @brief Reads the current state of a specific GPIO pin.
 *
 * Returns the logical state (set or reset) of the selected GPIO pin.
 *
 * @param[in] pin_no Index and unique identifier of the GPIO pin in the configuration table.
 * @retval uint8_t The current state of the GPIO pin (GPIO_PIN_SET or GPIO_PIN_RESET).
 */
uint8_t read_gpio_pin(uint8_t pin_no)
{
	if(NULL == m_last_gpio_pin_config_ptr)
	{
	  report_development_error();
	  return 0xFF; // return abnormal value
	}

    return HAL_GPIO_ReadPin(m_last_gpio_pin_config_ptr[pin_no].Port,m_last_gpio_pin_config_ptr[pin_no].Pin);
}

/**
 * @brief Enables the clock for the specified GPIO port.
 *
 * This function activates the peripheral clock for the GPIO port used in pin initialization.
 * If the provided port is not supported, a development error is reported.
 *
 * @param[in] gpio_port Pointer to the GPIO port (e.g., GPIOA, GPIOB, etc.).
 */
static void enable_used_gpio_pin_clock(GPIO_TypeDef* gpio_port)
{
	if(GPIOA == gpio_port)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}
	else if(GPIOB == gpio_port)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
	}
	else if(GPIOC == gpio_port)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
	}
	else if(GPIOH == gpio_port)
	{
		__HAL_RCC_GPIOH_CLK_ENABLE();
	}
	else
	{
		report_development_error();
	}

}
