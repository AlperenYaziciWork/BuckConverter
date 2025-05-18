#include "bsp_pwm.h"
#include "bsp_gpio.h"
#include "stdbool.h"

/**
 * @def PWM_TIMER_TOTAL_CNT
 * @brief Total number of configured PWM timers.
 * 
 * If not defined elsewhere, defaults to 0.
 */
#ifndef PWM_TIMER_TOTAL_CNT
#define PWM_TIMER_TOTAL_CNT 0U
#endif

#define PWM_DUTY_MAX 1.0f /**< Maximum allowed PWM duty cycle */
#define PWM_DUTY_MIN 0.0f /**< Minimum allowed PWM duty cycle */


/**
 * @brief Timer instance for Hal_tim library input , it will be filled in 
 * the init_bsp_pwm function with predefined bsp_pwm configurations.
 */
static TIM_HandleTypeDef m_htim[PWM_TIMER_TOTAL_CNT]; 

/**
 * @brief Pointer to the most recently used BSP PWM configuration.
 */
static bsp_pwm_config_t *m_last_bsp_pwm_config_ptr = NULL;

/**
 * @brief Finds the timer and PWM config index of a given PWM channel.
 * 
 * @param[in]  bsp_pwm_channel PWM channel to search.
 * @param[out] timer_config_index_ptr Pointer to store timer index.
 * @param[out] pwm_config_index_ptr Pointer to store PWM config index.
 * 
 * @retval true  If channel is found.
 * @retval false If not found.
 */
static bool find_timer_config_index_of_pwm_channel(bsp_pwm_channel_idx_t bsp_pwm_channel,
												  uint8_t *timer_config_index_ptr,
												  uint8_t *pwm_config_index_ptr);

/**
 * @brief Sets the CCR (Compare Capture Register) value for a specific PWM channel.
 * 
 * @param[in] timer_config_idx Timer index.
 * @param[in] timer_pwm_channel PWM channel (TIM_CHANNEL_x).
 * @param[in] CCR_value Value to set in CCR register.
 */
static void set_capture_compare_register_of_pwm_channel(uint8_t timer_config_idx,
														uint32_t timer_pwm_channel,
														uint32_t CCR_value);

/**
 * @brief Initializes the PWM channels for a given timer.
 * 
 * @param[in] timer_idx_of_pwm_channels Index of the timer to initialize.
 */
static void init_timer_pwm_channels(uint8_t timer_idx_of_pwm_channels);

/**
 * @brief Initializes all configured PWM timers and GPIOs.
 * 
 * @param[in] bsp_pwm_configs_ptr Pointer to array of PWM configurations.
 */
void init_bsp_pwm(bsp_pwm_config_t *bsp_pwm_configs_ptr)
{
	if(NULL != bsp_pwm_configs_ptr)
	{
		m_last_bsp_pwm_config_ptr = bsp_pwm_configs_ptr;
	}

	for(uint8_t pwm_timer_idx = 0U; pwm_timer_idx < PWM_TIMER_TOTAL_CNT;pwm_timer_idx++)
	{
	  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	  TIM_MasterConfigTypeDef sMasterConfig = {0};
	  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

	  m_htim[pwm_timer_idx].Instance = bsp_pwm_configs_ptr[pwm_timer_idx].timer_instance_ptr;
	  m_htim[pwm_timer_idx].Init.Prescaler = bsp_pwm_configs_ptr[pwm_timer_idx].pwm_timer_prescalar;
	  m_htim[pwm_timer_idx].Init.CounterMode = TIM_COUNTERMODE_UP;
	  m_htim[pwm_timer_idx].Init.Period = bsp_pwm_configs_ptr[pwm_timer_idx].pwm_timer_period;
	  m_htim[pwm_timer_idx].Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  m_htim[pwm_timer_idx].Init.RepetitionCounter = 0;
	  m_htim[pwm_timer_idx].Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	  if (HAL_TIM_Base_Init(&m_htim[pwm_timer_idx]) != HAL_OK)
	  {
	    report_init_error(); // TODO: gerçek error handler ekle
	  }
	  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	  if (HAL_TIM_ConfigClockSource(&m_htim[pwm_timer_idx], &sClockSourceConfig) != HAL_OK)
	  {
	    report_init_error(); // TODO: gerçek error handler ekle
	  }
	  if (HAL_TIM_PWM_Init(&m_htim[pwm_timer_idx]) != HAL_OK)
	  {
	    report_init_error(); // TODO: gerçek error handler ekle
	  }
	  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	  if (HAL_TIMEx_MasterConfigSynchronization(&m_htim[pwm_timer_idx], &sMasterConfig) != HAL_OK)
	  {
	    report_init_error(); // TODO: gerçek error handler ekle
	  }

	  init_timer_pwm_channels(pwm_timer_idx);
	  
	  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	  sBreakDeadTimeConfig.DeadTime = 0;
	  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	  if (HAL_TIMEx_ConfigBreakDeadTime(&m_htim[pwm_timer_idx], &sBreakDeadTimeConfig) != HAL_OK)
	  {
	    report_init_error();
	  }

	  init_gpio_pin(bsp_pwm_configs_ptr[pwm_timer_idx].pwm_out_gpio_pin_id_in_bsp_gpio);
	}
}

/**
 * @brief Starts a specific PWM channel.
 * 
 * @param[in] bsp_pwm_channel PWM channel to start.
 */
void start_pwm_channel(bsp_pwm_channel_idx_t bsp_pwm_channel)
{
	if(NULL == m_last_bsp_pwm_config_ptr)
	{
		// bsp_pwm module has not initialized.
		report_development_error(); //TODO:
		return;
	}

	uint8_t timer_config_idx = 0;
	uint8_t pwm_config_idx = 0;
	bool is_pwm_found =
		find_timer_config_index_of_pwm_channel(bsp_pwm_channel,&timer_config_idx,&pwm_config_idx);

		
	if(is_pwm_found)
	{
		uint32_t timer_channel_idx = m_last_bsp_pwm_config_ptr[timer_config_idx].
			timer_channel_configs.pwm_channels_ptr[pwm_config_idx].timer_channel;

		HAL_TIM_PWM_Start(&m_htim[timer_config_idx],timer_channel_idx);
	}
	else
	{
		report_development_error();
	}
}

/**
 * @brief Stops a specific PWM channel.
 * 
 * @param[in] bsp_pwm_channel PWM channel to stop.
 */
void stop_pwm_channel(bsp_pwm_channel_idx_t bsp_pwm_channel)
{
	if(NULL == m_last_bsp_pwm_config_ptr)
	{
		// bsp_pwm module has not initialized.
		report_development_error(); //TODO:
		return;
	}

	uint8_t timer_config_idx = 0;
	uint8_t pwm_config_idx = 0;
	bool is_pwm_found =
		find_timer_config_index_of_pwm_channel(bsp_pwm_channel,&timer_config_idx,&pwm_config_idx);


	if(is_pwm_found)
	{
		uint32_t timer_channel_idx = m_last_bsp_pwm_config_ptr[timer_config_idx].
			timer_channel_configs.pwm_channels_ptr[pwm_config_idx].timer_channel;

		HAL_TIM_PWM_Stop(&m_htim[timer_config_idx],timer_channel_idx);
	}
	else
	{
		report_development_error();
	}
}

/**
 * @brief Sets the duty cycle of a specific PWM channel.
 * 
 * @param[in] bsp_pwm_channel PWM channel to set.
 * @param[in] duty_rate Duty cycle to set (range: 0.0 to 1.0).
 */
void set_pwm_duty(bsp_pwm_channel_idx_t bsp_pwm_channel, 
				  float duty_rate)
{

	/* Check limits of duty rate */
	if ((duty_rate < PWM_DUTY_MIN) || (duty_rate > PWM_DUTY_MAX))
	{
		report_development_error(); //TODO: 
		return;
	}

	if(NULL == m_last_bsp_pwm_config_ptr)
	{
		// bsp_pwm module has not initialized.
		report_development_error(); //TODO:
		return;
	}

	uint8_t timer_config_idx = 0;
	uint8_t pwm_config_idx = 0;
	bool is_pwm_found = 
		find_timer_config_index_of_pwm_channel(bsp_pwm_channel,&timer_config_idx,&pwm_config_idx);

	if(is_pwm_found)
	{
		uint32_t calculated_pwm_value = 
			m_last_bsp_pwm_config_ptr[timer_config_idx].pwm_timer_period * duty_rate;

		uint32_t timer_channel_id =
			m_last_bsp_pwm_config_ptr[timer_config_idx].timer_channel_configs.
			pwm_channels_ptr[pwm_config_idx].timer_channel;

		set_capture_compare_register_of_pwm_channel(timer_config_idx,
													timer_channel_id,
													calculated_pwm_value);
	}
	else
	{
		report_development_error();
	}
}

static void set_capture_compare_register_of_pwm_channel(uint8_t timer_config_idx,
														uint32_t timer_pwm_channel,
														uint32_t CCR_value)
{
	switch(timer_pwm_channel)
	{
		case TIM_CHANNEL_1:
		{
			m_htim[timer_config_idx].Instance->CCR1 = CCR_value;
			break;
		}
		case TIM_CHANNEL_2:
		{
			m_htim[timer_config_idx].Instance->CCR2 = CCR_value;
			break;
		}
		case TIM_CHANNEL_3:
		{
			m_htim[timer_config_idx].Instance->CCR3 = CCR_value;
			break;
		}
		case TIM_CHANNEL_4:
		{
			m_htim[timer_config_idx].Instance->CCR4 = CCR_value;
			break;
		}
	}
}

static bool find_timer_config_index_of_pwm_channel(bsp_pwm_channel_idx_t bsp_pwm_channel,
												uint8_t *timer_config_index_ptr,
												uint8_t *pwm_config_index_ptr)
{
	bool pwm_channel_found_state = false;

	if((NULL == m_last_bsp_pwm_config_ptr) || (NULL == timer_config_index_ptr))
	{
		return pwm_channel_found_state;
	}

	for (uint8_t config_idx = 0; config_idx < PWM_TIMER_TOTAL_CNT; config_idx++)
	{
		uint8_t total_pwm_of_timer = 
			m_last_bsp_pwm_config_ptr[config_idx].
			timer_channel_configs.total_timer_channel;
		
		for (size_t pwm_cfg_idx = 0; pwm_cfg_idx < total_pwm_of_timer; pwm_cfg_idx++)
		{
			bsp_pwm_channel_idx_t pwm_channel_id = m_last_bsp_pwm_config_ptr[config_idx].
			timer_channel_configs.pwm_channels_ptr[pwm_cfg_idx].pwm_channel_id;
			if(pwm_channel_id == bsp_pwm_channel)
			{
				// pwm channel is found !!
				*timer_config_index_ptr = config_idx;
				pwm_channel_found_state = true;
				break;
			}
		}
	}

	return pwm_channel_found_state;
}


static void init_timer_pwm_channels(uint8_t timer_idx_of_pwm_channels)
{
	uint8_t total_pwm_channel = m_last_bsp_pwm_config_ptr[timer_idx_of_pwm_channels].timer_channel_configs.total_timer_channel;
	for (uint8_t pwm_channel_cfg_idx = 0; pwm_channel_cfg_idx < total_pwm_channel; pwm_channel_cfg_idx++)
	{
		uint32_t pwm_channel_idx =
			m_last_bsp_pwm_config_ptr[timer_idx_of_pwm_channels].timer_channel_configs.
			pwm_channels_ptr[pwm_channel_cfg_idx].pwm_channel_id;
		TIM_OC_InitTypeDef sConfigOC = {0};
		sConfigOC.OCMode = TIM_OCMODE_PWM1;
		sConfigOC.Pulse = 0;
		sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
		sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
		sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
		if (HAL_TIM_PWM_ConfigChannel(&m_htim[timer_idx_of_pwm_channels], &sConfigOC, pwm_channel_idx) != HAL_OK)
		{
			report_init_error();
		}
	}
}
