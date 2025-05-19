/**
 * @file bsp_can.c
 * @brief CAN (Controller Area Network) hardware abstraction layer implementation.
 *
 * This module handles initialization and transmission of CAN messages using
 * STM32 HAL library. It is designed to interact with the hardware-specific CAN peripheral.
 *
 * @date May 19, 2025
 * @author alperenyazici
 */


#include "bsp_can.h"
#include "bsp_gpio.h"
#include "stdbool.h"
#include "error_manager.h"

#ifndef BSP_CAN_TX_MESSAGE
// Number of transmit CAN messages configured
#define BSP_CAN_TX_MESSAGE 0U
#endif

/// Internal CAN driver handle
static CAN_HandleTypeDef m_can_driver;

/// Pointer to CAN configuration
static bsp_can_cfg_t *m_bsp_can_config_ptr = NULL;

/// Transmit header structure used when sending CAN messages
static CAN_TxHeaderTypeDef m_bsp_can_tx_header;

/// Mailbox index for CAN message transmission
static uint32_t m_mailbox = 0U;

/**
 * @brief Searches for the given message ID in the CAN configuration table.
 *
 * @param[in]  message_id             Message identifier to search for.
 * @param[out] tx_message_cfg_ptr     Pointer to store found message configuration.
 * @return true if message is found, false otherwise.
 *
 * @note The current function does not return the pointer correctly
 * because `tx_message_cfg_ptr` is passed by value. Consider changing
 * to `can_tx_message_cfg_t **` for proper use.
 */
static bool find_message_id_from_config(uint16_t message_id,
										const can_tx_message_cfg_t *tx_message_cfg_ptr);

/**
 * @brief Initializes the CAN hardware with given configuration.
 *
 * This function sets up the GPIO pins, CAN peripheral settings (timing, modes)
 * and starts the CAN module.
 *
 * @param[in] bsp_can_configs_ptr Pointer to the CAN configuration structure.
 */
void init_bsp_can(const bsp_can_cfg_t *bsp_can_configs_ptr)
{
	if(NULL == bsp_can_configs_ptr)
	{
		report_development_error();
		return;
	}

	m_bsp_can_config_ptr = (bsp_can_cfg_t *)bsp_can_configs_ptr;

	init_gpio_pin(m_bsp_can_config_ptr->can_gpio_pins_id);

	m_can_driver.Instance = m_bsp_can_config_ptr->can_instance_ptr;
	m_can_driver.Init.Prescaler = m_bsp_can_config_ptr->clock_prescaler;
	m_can_driver.Init.Mode = CAN_MODE_NORMAL;
	m_can_driver.Init.SyncJumpWidth = m_bsp_can_config_ptr->sync_jump_bit;
	m_can_driver.Init.TimeSeg1 = m_bsp_can_config_ptr->time_segment_1;
	m_can_driver.Init.TimeSeg2 = m_bsp_can_config_ptr->time_segment_2;
	m_can_driver.Init.TimeTriggeredMode = DISABLE;
	m_can_driver.Init.AutoBusOff = DISABLE;
	m_can_driver.Init.AutoWakeUp = DISABLE;
	m_can_driver.Init.AutoRetransmission = DISABLE;
	m_can_driver.Init.ReceiveFifoLocked = DISABLE;
	m_can_driver.Init.TransmitFifoPriority = DISABLE;

	if (HAL_CAN_Init(&m_can_driver) != HAL_OK)
	{
		report_init_error();
	}

	if (HAL_CAN_Start(&m_can_driver) != HAL_OK)
	{
		report_init_error();
	}

}

/**
 * @brief Sends a CAN message using the specified message ID and data.
 *
 * This function searches for the message ID in the configuration, fills
 * the transmit header, and queues the message for transmission using HAL.
 *
 * @param[in] message_id       Identifier of the message to send.
 * @param[in] message_data_ptr Pointer to the data to send.
 * @param[in] data_len         Length of the data in bytes.
 */
void send_message_over_canbus(uint16_t message_id,
							  uint8_t *message_data_ptr ,
							  uint16_t data_len)
{
	can_tx_message_cfg_t *tx_message_cfg_ptr = NULL;

	bool is_msg_found = find_message_id_from_config(message_id,tx_message_cfg_ptr);

	if(false == is_msg_found)
	{
		report_development_error();
		return;
	}

	if(CANID_STANDARD == tx_message_cfg_ptr->id_type)
	{
		m_bsp_can_tx_header.IDE = CAN_ID_STD;
		m_bsp_can_tx_header.StdId = tx_message_cfg_ptr->can_id;
	}
	else if(CANID_EXTENDED == tx_message_cfg_ptr->id_type)
	{
		m_bsp_can_tx_header.IDE = CAN_ID_EXT;
		m_bsp_can_tx_header.ExtId = tx_message_cfg_ptr->can_id;
	}
	else
	{
		report_development_error();
		return;
	}

	m_bsp_can_tx_header.DLC = data_len;
	m_bsp_can_tx_header.RTR = CAN_RTR_DATA;

	HAL_CAN_AddTxMessage(&m_can_driver,
							 &m_bsp_can_tx_header,
							 message_data_ptr,
							 &m_mailbox);
}

/**
 * @brief Searches for the given message ID in the CAN configuration table.
 *
 * @param[in]  message_id             Message identifier to search for.
 * @param[out] tx_message_cfg_ptr     Pointer to store found message configuration.
 * @return true if message is found, false otherwise.
 *
 * @note The current function does not return the pointer correctly
 * because `tx_message_cfg_ptr` is passed by value. Consider changing
 * to `can_tx_message_cfg_t **` for proper use.
 */
static bool find_message_id_from_config(uint16_t message_id,
										const can_tx_message_cfg_t *tx_message_cfg_ptr)
{
	bool is_message_found = false;

	for(uint16_t tx_can_cfg_idx = 0;
		tx_can_cfg_idx < BSP_CAN_TX_MESSAGE;
		tx_can_cfg_idx++)
	{
		uint16_t tx_cfg_msg_id =
			m_bsp_can_config_ptr->tx_messages_ptr[tx_can_cfg_idx].message_id;

		if(tx_cfg_msg_id == message_id)
		{
			is_message_found = true;

			tx_message_cfg_ptr =
				&m_bsp_can_config_ptr->tx_messages_ptr[tx_can_cfg_idx];
		}
	}

	return is_message_found;
}




