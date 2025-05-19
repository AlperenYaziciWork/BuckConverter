/*
 * com_driver.h
 *
 *  Created on: May 19, 2025
 *      Author: alperenyazici
 */

#ifndef COM_DRIVER_H_
#define COM_DRIVER_H_

#include "stdint.h"
#include "stdbool.h"
#include "software_timer.h"
#include "com_driver_cfg.h"

/**
 * @brief Type definition for message ID used in the communication module.
 */
typedef uint16_t com_message_id_t;

/**
 * @brief Type definition for signal ID used in the communication module.
 */
typedef uint16_t com_signal_id_t;

/**
 * @brief Defines the endianness of the signal's network representation.
 *
 */
typedef enum
{
    ///< Motorola byte order endianness
    COM_SIGNAL_ENDIANNESS_BIG_ENDIAN_e,
    ///< Intel byte order endianness
    COM_SIGNAL_ENDIANNESS_LITTLE_ENDIAN_e,

}com_signal_endianness_e;

/**
 * @brief The AUTOSAR type of the signal. Whether or not the signal is signed or
 * unsigned can be found by examining the value of this attribute.This type
 * could also be used to reserved appropriate storage in AUTOSAR COM.
 *
 */
typedef enum
{
    ///< boolen variable type
    COM_SIGNAL_VARIABLE_BOOLEAN_e,
    ///< float 32 bit variable type
    COM_SIGNAL_VARIABLE_FLOAT32_e,
    ///< float 64 bit variable type
    COM_SIGNAL_VARIABLE_FLOAT64_e,
    ///< signed int 16 bit data type
    COM_SIGNAL_VARIABLE_SINT16_e,
    ///< signed int 32 bit data type
    COM_SIGNAL_VARIABLE_SINT32_e,
    ///< signed int 64 bit data type
    COM_SIGNAL_VARIABLE_SINT64_e,
    ///< signed int 8 bit data type
    COM_SIGNAL_VARIABLE_SINT8_e,
    ///< unsigned int 16 bit data type
    COM_SIGNAL_VARIABLE_UINT16_e,
    ///< unsigned int 32 bit data type
    COM_SIGNAL_VARIABLE_UINT32_e,
    ///< unsigned int 64 bit data type
    COM_SIGNAL_VARIABLE_UINT64_e,
    ///< unsigned int 8 bit data type
    COM_SIGNAL_VARIABLE_UINT8_e,
    ///< unsigned int8 has dynamic len data type
    COM_SIGNAL_VARIABLE_UINT8_DYN_e,
    ///< unsigned int 8 bit array
    COM_SIGNAL_VARIABLE_UINT8_N_e,

}com_signal_variable_e;

typedef enum{
	MESSAGE_BUS_CANBUS_e,
	MESSAGE_BUS_UART_e, // It is defined to demonstration,
	MESSAGE_BUS_SPI_e, // It is defined to demonstration

}com_message_bus_e;

/**
 * @brief group signal or signal' base informations
 *
 */
typedef struct
{
    ///< signal start bit position
    uint32_t com_bit_position;
    ///< signal bit size
    uint8_t com_bit_size;
    ///< signal endiannes
    com_signal_endianness_e com_signal_endianness;
    ///< signal variable type
    com_signal_variable_e com_signal_variable_type;

}signal_base_info_t;

typedef struct
{
	///< Signal configuration metadata
	signal_base_info_t signal_base_info;
	///< Unique id of signal
	com_signal_id_t signal_id;
    // TODO : signal initial value may be added.

}com_signal_t;

/**
 * @brief Configuration for sending periodic messages.
 */
typedef struct
{
	///< Software timer ID used for periodic message transmission
    software_timer_id_t sw_timer_id;
    ///< Transmission period in milliseconds
    uint16_t send_period_ms;

}com_periodic_send_info_t;

/**
 * @brief Represents a communication message structure.
 */
typedef struct
{
    com_message_id_t message_id;                              ///< Unique identifier of the message
    const com_signal_t *signals_ptr;                          ///< Pointer to array of signals in the message
    uint16_t message_data_length;                             ///< Length of the message data in bytes
    com_message_bus_e transmission_bus_of_message;            ///< Bus over which the message will be sent
    com_signal_id_t total_signal_cnt_in_message;              ///< Number of signals within this message
    const com_periodic_send_info_t *periodic_send_info;       ///< Optional configuration for periodic transmission

} com_message_t;

/**
 * @brief Top-level configuration for the communication module.
 */
typedef struct
{
	///< Pointer to array of message configurations
	const com_message_t *messages_ptr;

}com_configs_t;

/**
 * @brief Initializes the communication driver.
 *
 * Sets up internal pointers and starts software timers for periodic message transmission.
 *
 * @param[in] com_configs_ptr Pointer to communication configuration.
 */
void init_com_driver(const com_configs_t *com_configs_ptr);

/**
 * @brief Triggers the transmission of a specific message immediately.
 *
 * @details
 * This function sends the specified message over the configured bus (e.g., CAN, SPI, UART)
 * using the message's current data stored in the internal buffer. It does not check for
 * periodicity or signal updates—only performs transmission with current data.
 *
 * @param[in] message_id The ID of the message to be transmitted.
 */
void trigger_send_of_message(com_message_id_t message_id);

/**
 * @brief Callback function for periodic message transmission.
 *
 * Called by the software timer and checks which message should be sent.
 *
 * @param[in] sw_timer_id ID of the triggered software timer.
 */
void send_periodic_message_timeout_cb(software_timer_id_t sw_timer_id);

/**
 * @brief Sends a signal by mapping it into its message buffer.
 *
 * Finds the message that includes the given signal and inserts the signal value into the corresponding buffer.
 *
 * @param[in] signal_id ID of the signal to be sent.
 * @param[in] signal_value_ptr Pointer to the value of the signal to be sent.
 * @return true if successful, false otherwise.
 */
bool send_signal_over_com(com_signal_id_t signal_id , void *signal_value_ptr);

//TODO: As there is no reception requirement , reception functionality has not been implemented.
//bool receive_signal(com_signal_id_t signal_id , void *signal_value_ptr);

#endif /* COM_DRIVER_H_ */
