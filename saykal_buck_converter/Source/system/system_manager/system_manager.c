/*
 * system_manager.c
 *
 *  Created on: May 19, 2025
 *      Author: alperenyazici
 */


#include "system_manager.h"
#include "error_manager.h"
#include "bsp_adc.h"
#include "bsp_gpio.h"
#include "bsp_pwm.h"
#include "bsp_can.h"
#include "software_timer.h"
#include "adc_sensor_driver.h"
#include "com_driver.h"
#include "app_buck_converter.h"

/**
 * @brief Defines the operating states of the system.
 */
typedef enum{
	SYSTEM_STATE_INIT,           /**< System initialization phase */
	SYSTEM_STATE_RUNNING,        /**< Normal operation phase */
	SYSTEM_STATE_ERROR,          /**< Critical error occurred */
	SYSTEM_STATE_SAFE_RUNNING,   /**< Safe mode, only communication is active */
	SYSTEM_STATE_IDLE,           /**< Idle state, power-saving or inactive */
} system_state_e;

/**
 * @brief Current state of the system.
 */
static system_state_e m_system_state = SYSTEM_STATE_INIT;

/**
 * @brief External GPIO pin configuration table.
 *
 * @details Contains the configuration data for all GPIO pins used in the system.
 * Initialized in the board support package (BSP) layer.
 */
extern const gpio_pin_cfg_t g_pin_cfg_container[];

/**
 * @brief PWM timer configuration table.
 *
 * @details Holds configuration parameters for all PWM timers used in the application,
 * including frequency, duty, and pin mapping.
 */
extern const bsp_pwm_config_t g_bsp_pwm_timer_configs[];

/**
 * @brief CAN peripheral configuration.
 *
 * @details Defines the hardware parameters and transmit message structure for
 * the CAN interface (instance, timing, messages).
 */
extern const bsp_can_cfg_t g_bsp_can_configurations;

/**
 * @brief Software timer module general configuration.
 *
 * @details Contains the base configuration for initializing and running all
 * software timers in the system.
 */
extern const software_timer_general_cfg_t g_software_timer_general_config;

/**
 * @brief ADC sensor configuration table.
 *
 * @details Lists all sensors connected to ADC channels along with their
 * scaling, offsets, and logical IDs.
 */
extern const adc_sensor_driver_config_t g_adc_sensors_configuration[];

/**
 * @brief Communication module configuration structure.
 *
 * @details Holds signal IDs, message IDs, transmission method in the communication driver.
 */
extern const com_configs_t g_com_message_configs;

/**
 * @brief Buck converter configuration.
 *
 * @details Provides PID parameters, PWM settings, feedback sources, and
 * operating limits for the buck converter control loop.
 */
extern const buck_converter_cfg_t g_buck_converter_config;


/**
 * @brief Configures the system clocks using external HSE.
 *
 * @details Called during initialization to set up the RCC clock tree.
 */
static void SystemClock_Config(void);

/**
 * @brief Scales a float temperature value to a 16-bit unsigned integer for communication.
 *
 * @param[in] temperature    The raw temperature value (in °C).
 * @param[in] scale_min      Minimum temperature value in scaling range.
 * @param[in] scale_max      Maximum temperature value in scaling range.
 * @param[in] zero_offset    Offset added to the temperature before scaling.
 *
 * @return uint16_t          Scaled temperature as a 16-bit unsigned integer.
 */
static uint16_t scale_temperature_for_send_over_com(float temperature,
													float scale_min,
													float scale_max,
													float zero_offset);

/**
 * @brief Executes the system's main state machine.
 *
 * @details This function controls the main operating flow of the system, transitioning
 * between initialization, running, error, safe-running, and idle states. It is intended
 * to be called periodically in the main application loop.
 */
void run_state_machine_of_system_manager(void)
{
	switch(m_system_state)
	{
		case SYSTEM_STATE_IDLE:
		{
			// it may be necessary for power management
			break;
		}
		case SYSTEM_STATE_INIT:
		{
			HAL_Init();
			SystemClock_Config();
			init_bsp_gpio(g_pin_cfg_container);
			init_bsp_adc();
			init_bsp_pwm(g_bsp_pwm_timer_configs);
			init_bsp_can(&g_bsp_can_configurations);
			init_software_timer_module(&g_software_timer_general_config);
			init_adc_sensor_driver(g_adc_sensors_configuration);
			init_com_driver(&g_com_message_configs);
			init_buck_converter(&g_buck_converter_config);

			send_signal_over_com(COM_SYSTEM_STATE_SIGNAL_ID,(uint8_t*)&m_system_state);
			trigger_send_of_message(COM_SYSTEM_INFO_MESSAGE_ID);

			start_software_timer(SYSTEM_TEMPERATURE_PROCESS_TIMER_ID,
								 SYSTEM_TEMPERATURE_SENSE_PERIOD_MS);

			m_system_state = SYSTEM_STATE_RUNNING;

			break;
		}
		case SYSTEM_STATE_RUNNING:
		{
			send_signal_over_com(COM_SYSTEM_STATE_SIGNAL_ID,(uint8_t*)&m_system_state);
			// all application process connected a software timer callback so it is enough
			//to call run_all_software_timers
			run_all_software_timers();

			bool over_current_error_flag =
					get_system_overcurrent_error_status();

			if(true == over_current_error_flag)
			{
				m_system_state = SYSTEM_STATE_ERROR;
			}
			break;
		}
		case SYSTEM_STATE_ERROR:
		{
			send_signal_over_com(COM_SYSTEM_STATE_SIGNAL_ID,(uint8_t*)&m_system_state);
			trigger_send_of_message(COM_SYSTEM_INFO_MESSAGE_ID);
			// Stop buck converter controller task
			stop_software_timer(BUCK_CONVERTER_PID_SOFTWARE_TIMER_ID);
			// Reset pwm duty of buck converter mosfet
			set_pwm_duty(PWM_TIMER_ID_FOR_BUCK_MOSFET,0.0f);
			// stop buck converter mosfet PWM
			stop_pwm_channel(PWM_TIMER_ID_FOR_BUCK_MOSFET);

			m_system_state = SYSTEM_STATE_SAFE_RUNNING;
			break;
		}

		case SYSTEM_STATE_SAFE_RUNNING:
		{
			send_signal_over_com(COM_SYSTEM_STATE_SIGNAL_ID,(uint8_t*)&m_system_state);

			run_all_software_timers(); // only commmunication tasks are running.
		}

		default:
		{

			break;
		}
	}
}

/**
 * @brief Reads and sends system temperature over communication interface.
 *
 * @param[in] sw_timer_id ID of the software timer triggering the temperature reading.
 *
 * @details Temperature is read from an ADC-based sensor, scaled to a communication format,
 * and sent via CAN or another protocol defined in the communication layer.
 */
void calculate_system_temperature(software_timer_id_t sw_timer_id )
{
	float system_temperature = 0.0f;
	read_adc_sensor_value(TEMPERATURE_LM35_SENSOR_ID,&system_temperature);
	uint16_t raw_com_value =
			scale_temperature_for_send_over_com(system_temperature,
												SYSTEM_TEMPERATURE_SCALE_MIN,
												SYSTEM_TEMPERATURE_SCALE_MAX,
												SYSTEM_TEMPERATURE_SCALE_ZERO_OFFSET);

	send_signal_over_com(COM_SYSTEM_TEMPERATURE_SIGNAL_ID,&raw_com_value);
}

/**
 * @brief Scales a float temperature value to a 16-bit unsigned integer for communication.
 *
 * @param[in] temperature    The raw temperature value (in °C).
 * @param[in] scale_min      Minimum temperature value in scaling range.
 * @param[in] scale_max      Maximum temperature value in scaling range.
 * @param[in] zero_offset    Offset added to the temperature before scaling.
 *
 * @return uint16_t          Scaled temperature as a 16-bit unsigned integer.
 */
static uint16_t scale_temperature_for_send_over_com(float temperature,
													float scale_min,
													float scale_max,
													float zero_offset)
{
    // Offset uygulandıktan sonra yeni sıcaklık
    float adjusted_temp = temperature + zero_offset;

    // Aralık kontrolü
    if (adjusted_temp < scale_min) adjusted_temp = scale_min;
    if (adjusted_temp > scale_max) adjusted_temp = scale_max;

    // Ölçekleme işlemi
    float normalized = (adjusted_temp - scale_min) / (scale_max - scale_min);
    uint16_t result = (uint16_t)(normalized * 65535.0f); // uint16_t max: 65535

    return result;
}

/**
 * @brief Configures the system clock using HSE oscillator.
 *
 * @details Initializes RCC oscillator settings and sets HSE as the system clock source.
 */
static void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    report_init_error();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    report_init_error();
  }
}
