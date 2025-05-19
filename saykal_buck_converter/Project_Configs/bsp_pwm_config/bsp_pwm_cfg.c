#include "bsp_pwm.h"
#include "stm32f4xx_hal_tim.h"
#include "bsp_gpio_cfg.h"

static const bsp_pwm_channel_t m_bsp_pwm_channel_info =
{
	.pwm_channel_id = PWM_TIMER_ID_FOR_BUCK_MOSFET, // it is used from UPPER LAYER to abstract all pwm hardware things.
	.timer_channel = TIM_CHANNEL_1
};

const bsp_pwm_config_t g_bsp_pwm_timer_configs[] =
{
	{
		.timer_instance_ptr = TIM1,
		.pwm_out_gpio_pin_id_in_bsp_gpio = BUCK_PWM_OUT_PIN_ID,
		.timer_channel_configs = {
			.total_timer_channel = 1U,
			.pwm_channels_ptr = &m_bsp_pwm_channel_info
		}
	}

};
