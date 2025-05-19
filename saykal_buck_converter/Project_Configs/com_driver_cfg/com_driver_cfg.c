/*
 * com_driver_cfg.c
 *
 *  Created on: May 19, 2025
 *      Author: alperenyazici
 */


#include "com_driver.h"
#include "software_timer_cfg.h"

const com_periodic_send_info_t m_com_periodic_voltage_current_system_info_message =
{
	.send_period_ms = 100u,
	.sw_timer_id = COM_VOLTAGE_CURRENT_SYSTEM_INFO_MESSAGE_TIMER,
};

const com_signal_t m_com_signals_of_voltage_info_message[] =
{
	{
		.signal_id = COM_BUCK_OUTPUT_VOLTAGE_SIGNAL_ID,
		.signal_base_info =
		{
			.com_bit_position = 0,
			.com_bit_size = 32U,
			.com_signal_endianness = COM_SIGNAL_ENDIANNESS_LITTLE_ENDIAN,
			.com_signal_variable_type = COM_SIGNAL_VARIABLE_FLOAT32,
		},

	},
	{
		.signal_id = COM_BUCK_INPUT_VOLTAGE_SIGNAL_ID,
		.signal_base_info =
		{
			.com_bit_position = 32U,
			.com_bit_size = 32U,
			.com_signal_endianness = COM_SIGNAL_ENDIANNESS_LITTLE_ENDIAN,
			.com_signal_variable_type = COM_SIGNAL_VARIABLE_FLOAT32,
		},

	},
};

const com_signal_t m_com_signals_of_current_info_message[] =
{
	{
		.signal_id = COM_BUCK_OUTPUT_CURRENT_SIGNAL_ID,
		.signal_base_info =
		{
			.com_bit_position = 0,
			.com_bit_size = 32U,
			.com_signal_endianness = COM_SIGNAL_ENDIANNESS_LITTLE_ENDIAN,
			.com_signal_variable_type = COM_SIGNAL_VARIABLE_FLOAT32,
		},

	},
	{
		.signal_id = COM_BUCK_INPUT_CIURRENT_SIGNAL_ID,
		.signal_base_info =
		{
			.com_bit_position = 32U,
			.com_bit_size = 32U,
			.com_signal_endianness = COM_SIGNAL_ENDIANNESS_LITTLE_ENDIAN,
			.com_signal_variable_type = COM_SIGNAL_VARIABLE_FLOAT32,
		},

	},
};

const com_signal_t m_com_signals_of_system_info_message[] =
{
	{
		.signal_id = COM_SYSTEM_TEMPERATURE_SIGNAL_ID,
		.signal_base_info =
		{
			.com_bit_position = 0,
			.com_bit_size = 16U,
			.com_signal_endianness = COM_SIGNAL_ENDIANNESS_LITTLE_ENDIAN,
			.com_signal_variable_type = COM_SIGNAL_VARIABLE_UINT16,
		},

	},
	{
		.signal_id = COM_SYSTEM_STATE_SIGNAL_ID,
		.signal_base_info =
		{
			.com_bit_position = 16U,
			.com_bit_size = 2U,
			.com_signal_endianness = COM_SIGNAL_ENDIANNESS_LITTLE_ENDIAN,
			.com_signal_variable_type = COM_SIGNAL_VARIABLE_UINT8,
		},

	},
};

const com_message_t m_com_messages[] =
{
	{
		.message_id = COM_BUCK_VOLTAGE_INFO_MESSAGE_ID,
		.message_data_length = 8U,
		.total_signal_cnt_in_message = 2U,
		.transmission_bus_of_message = MESSAGE_BUS_CANBUS,
		.periodic_send_info = &m_com_periodic_voltage_current_system_info_message,//All messages connected the same time base
		.signals_ptr = m_com_signals_of_voltage_info_message,

	},
	{
		.message_id = COM_BUCK_CURRENT_INFO_MESSAGE_ID,
		.message_data_length = 8U,
		.total_signal_cnt_in_message = 2U,
		.transmission_bus_of_message = MESSAGE_BUS_CANBUS,
		.periodic_send_info = &m_com_periodic_voltage_current_system_info_message,//All messages connected the same time base
		.signals_ptr = m_com_signals_of_current_info_message,

	},
	{
		.message_id = COM_BUCK_SYSTEM_INFO_MESSAGE_ID,
		.message_data_length = 8U,
		.total_signal_cnt_in_message = 2U,
		.transmission_bus_of_message = MESSAGE_BUS_CANBUS,
		.periodic_send_info = &m_com_periodic_voltage_current_system_info_message,//All messages connected the same time base
		.signals_ptr = m_com_signals_of_system_info_message,

	},
};

const com_configs_t g_com_message_configs =
{
	.messages_ptr = m_com_messages,
};
