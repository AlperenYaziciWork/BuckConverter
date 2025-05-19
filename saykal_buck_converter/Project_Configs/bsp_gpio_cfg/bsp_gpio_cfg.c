
#include "bsp_gpio.h"
#include "stm32f4xx_hal_gpio.h"

const uint32_t m_can_pins_alternate = GPIO_AF9_CAN1;

const gpio_pin_cfg_t PinCfgContainer[] = 
{
    {
		.Port = GPIOA ,
		.Pin = GPIO_PIN_8 ,
		.Mode = GPIO_MODE_AF_PP ,
		.Pull = GPIO_NOPULL,
		.Speed = GPIO_SPEED_FREQ_LOW
    }, // BUCK_PWM_OUT_PIN_ID
	{
			.Port = GPIOB ,
			.Pin = GPIO_PIN_8|GPIO_PIN_9 ,
			.Mode = GPIO_MODE_AF_PP ,
			.Pull = GPIO_NOPULL,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
			.Alternate_ptr = &m_can_pins_alternate
	}, // BUCK_PWM_OUT_PIN_ID

};
