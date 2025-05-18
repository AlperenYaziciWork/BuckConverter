#include "bsp_gpio.h"

static const gpio_pin_cfg_t *m_last_gpio_pin_config_ptr = NULL;

void init_bsp_gpio(const gpio_pin_cfg_t *gpio_pin_configs_ptr)
{
    if(NULL != gpio_pin_configs_ptr)
    {
        m_last_gpio_pin_config_ptr = gpio_pin_configs_ptr;
    }
}

/**
  * @brief  Girilen pin numarasina ait gpio pinini m_last_gpio_pin_config_ptr 'ındaki konfiglere göre init eder.
  * @param  pin_no , parametresi m_last_gpio_pin_config_ptr'in indexi ve unique id'sidir.
  * @retval None
  */
void init_gpio_pin(uint8_t pin_no)
{
  if(NULL == m_last_gpio_pin_config_ptr)
  {
	  report_development_error();
	  return;
  }

  USED_GPIO_PIN_CLOCKS_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = m_last_gpio_pin_config_ptr[pin_no].Pin;
  GPIO_InitStruct.Mode = m_last_gpio_pin_config_ptr[pin_no].Mode; 
  GPIO_InitStruct.Pull = m_last_gpio_pin_config_ptr[pin_no].Pull;  
  HAL_GPIO_Init(m_last_gpio_pin_config_ptr[pin_no].Port, &GPIO_InitStruct);
}
/**
  * @brief  Girilen pin numarasina ait gpio pin durumuna, pin_status değerini yazar .
  * @param  pin_no , parametresi m_last_gpio_pin_config_ptr'in indexi ve unique id'sidir.
  * @param  pin_status , pin_no numaralı gpio pininin çıkışına atanmak istenen değerdir. 
  * @retval None
  */
void write_gpio_pin(uint8_t pin_no , uint8_t pin_status)
{
	if(NULL == m_last_gpio_pin_config_ptr)
	{
	  report_development_error();
	  return;
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
  * @brief  Girilen pin numarasina ait gpio pin durumunu geri döndürür.
  * @param  pin_no , parametresi m_last_gpio_pin_config_ptr'in indexi ve unique id'sidir.
  * @retval m_last_gpio_pin_config_ptr 'da tanimli olan pin_no ' lu ledin gpio pin durumunu geri döndürür. 
  */
uint8_t read_gpio_pin(uint8_t pin_no)
{
	if(NULL == m_last_gpio_pin_config_ptr)
	{
	  report_development_error();
	  return;
	}

    return HAL_GPIO_ReadPin(m_last_gpio_pin_config_ptr[pin_no].Port,m_last_gpio_pin_config_ptr[pin_no].Pin);
}
