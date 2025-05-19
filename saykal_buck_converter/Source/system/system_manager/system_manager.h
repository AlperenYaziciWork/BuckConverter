/*
 * system_manager.h
 *
 *  Created on: May 19, 2025
 *      Author: alperenyazici
 */

#ifndef SYSTEM_MANAGER_H_
#define SYSTEM_MANAGER_H_

#include "stdint.h"
#include "software_timer.h"

/**
 * @brief Period of system temperature sensing in milliseconds.
 *
 * @details This defines how frequently the system temperature is sampled and processed.
 */
#define SYSTEM_TEMPERATURE_SENSE_PERIOD_MS 		100

/**
 * @brief Minimum expected temperature value for scaling.
 *
 * @details Used in the linear scaling operation before sending the temperature over communication.
 */
#define SYSTEM_TEMPERATURE_SCALE_MIN	   		0.0f

/**
 * @brief Maximum expected temperature value for scaling.
 *
 * @details Used in the linear scaling operation before sending the temperature over communication.
 */
#define SYSTEM_TEMPERATURE_SCALE_MAX	   		70.0f

/**
 * @brief Offset to be added to the raw temperature value before scaling.
 *
 * @details Useful for calibration or zero-shifting temperature readings.
 */
#define SYSTEM_TEMPERATURE_SCALE_ZERO_OFFSET	0.0f

/**
 * @brief Factor to be multiplied to the raw temperature value before scaling.
 *
 */
#define SYSTEM_TEMPERATURE_SCALE_FACTOR			0.1f

/**
 * @brief Executes the system's main state machine.
 *
 * @details This function controls the main operating flow of the system, transitioning
 * between initialization, running, error, safe-running, and idle states. It is intended
 * to be called constantly in the main application loop.
 */
void run_state_machine_of_system_manager(void);

/**
 * @brief Reads and sends system temperature over communication interface.
 *
 * @param[in] sw_timer_id ID of the software timer triggering the temperature reading.
 *
 * @details Temperature is read from an ADC-based sensor, scaled to a communication format,
 * and sent via CAN or another protocol defined in the communication layer.
 */
void calculate_system_temperature(software_timer_id_t sw_timer_id);

#endif /* SYSTEM_MANAGER_H_ */
