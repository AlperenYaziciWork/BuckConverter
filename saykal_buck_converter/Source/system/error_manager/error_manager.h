/*
 * error_manager.h
 *
 *  Created on: May 19, 2025
 *      Author: alperenyazici
 */

#ifndef ERROR_MANAGER_H_
#define ERROR_MANAGER_H_

#include "stdint.h"


/**
 * @def ERROR_TYPE_SENSOR
 * @brief Index for sensor-related error in the system error bitfield.
 */
#define	ERROR_TYPE_SENSOR 		0U

/**
 * @def ERROR_TYPE_DEVELOPMENT
 * @brief Index for development-time error in the system error bitfield.
 * 
 * Typically used for invalid parameters, configuration mismatches, or internal software issues.
 */
#define	ERROR_TYPE_DEVELOPMENT 	1U

/**
 * @def ERROR_TYPE_OVERCURRENT
 * @brief Index for overcurrent-related error in the system error bitfield.
 * 
 * Indicates excessive current detected in system hardware.
 */
#define	ERROR_TYPE_OVERCURRENT 	2U

/**
 * @def ERROR_TYPE_INITIALIZE
 * @brief Index for initialization error in the system error bitfield.
 * 
 * Set when a module or peripheral fails to initialize correctly.
 */
#define	ERROR_TYPE_INITIALIZE   3U



/**
 * @brief Reports a sensor-related error.
 *
 * Sets the corresponding bit in the error status variable and transmits it
 * over the communication layer.
 */
void report_sensor_error(void);

/**
 * @brief Reports a development-time error.
 *
 * Typically used for assertion failures or invalid configuration. Sets the
 * appropriate error bit and notifies via communication.
 */
void report_development_error(void);

/**
 * @brief Reports an overcurrent condition.
 *
 * Marks the overcurrent bit in the system error status and sends the update.
 */
void report_over_current(void);

/**
 * @brief Reports an initialization error.
 *
 * Used to indicate failure during hardware or module initialization. Sets
 * the init error bit and updates the communication layer.
 */
void report_init_error(void);

/**
 * @brief Returns the current system error status.
 * 
 * @return uint8_t A bitfield representing all system errors currently flagged.
 */
uint8_t get_system_error_status(void);

#endif /* ERROR_MANAGER_H_ */
