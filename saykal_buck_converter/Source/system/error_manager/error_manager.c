/**
 * @file error_manager.c
 * @brief Implements error reporting and error status management for the system.
 * 
 * This module is responsible for tracking system errors and reporting them
 * through the communication layer.
 * 
 * @date May 19, 2025
 * @author alperenyazici
 */


#include "error_manager.h"
#include "com_driver.h"

///< Stores the system error flags as a bitfield.
uint8_t m_system_errors = 0U;

/**
 * @brief Reports a sensor-related error.
 *
 * Sets the corresponding bit in the error status variable and transmits it
 * over the communication layer.
 */
void report_sensor_error(void)
{
	m_system_errors |= (1U << ERROR_TYPE_SENSOR);

	send_signal_over_com(COM_SYSTEM_ERROR_STATE_SIGNAL_ID,&m_system_errors);
}

/**
 * @brief Reports a development-time error.
 *
 * Typically used for assertion failures or invalid configuration. Sets the
 * appropriate error bit and notifies via communication.
 */
void report_development_error(void)
{
	m_system_errors |= (1U << ERROR_TYPE_DEVELOPMENT);

	send_signal_over_com(COM_SYSTEM_ERROR_STATE_SIGNAL_ID,&m_system_errors);
}

/**
 * @brief Reports an overcurrent condition.
 *
 * Marks the overcurrent bit in the system error status and sends the update.
 */
void report_over_current(void)
{
	m_system_errors |= (1U << ERROR_TYPE_OVERCURRENT);

	send_signal_over_com(COM_SYSTEM_ERROR_STATE_SIGNAL_ID,&m_system_errors);
}

/**
 * @brief Reports an initialization error.
 *
 * Used to indicate failure during hardware or module initialization. Sets
 * the init error bit and updates the communication layer.
 */
void report_init_error(void)
{
	m_system_errors |= (1U << ERROR_TYPE_INITIALIZE);

	send_signal_over_com(COM_SYSTEM_ERROR_STATE_SIGNAL_ID,&m_system_errors);
}

/**
 * @brief Returns whether an overcurrent system error is currently active.
 * 
 * @return uint8_t 1 if the overcurrent error bit is set, 0 otherwise.
 */
bool get_system_overcurrent_error_status(void)
{
	bool is_overcurrent_exist = false;
	if(1U == ((m_system_errors >> ERROR_TYPE_OVERCURRENT) & 0x01U))
	{
		is_overcurrent_exist = true;
	}
    return is_overcurrent_exist;
}

/**
 * @brief Returns the current system error status.
 *
 * @return uint8_t A bitfield representing all system errors currently flagged.
 */
uint8_t get_system_error_status(void)
{
	return m_system_errors;
}
