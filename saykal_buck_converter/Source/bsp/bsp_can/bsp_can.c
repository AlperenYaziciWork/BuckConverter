/*
 * bsp_can.c
 *
 *  Created on: May 19, 2025
 *      Author: alperenyazici
 */


#include "bsp_can.h"
#include "bsp_gpio.h"
#include "stdbool.h"

#ifndef BSP_CAN_TX_MESSAGE
#define BSP_CAN_TX_MESSAGE 0U
#endif

static CAN_HandleTypeDef m_can_driver;

static bsp_can_cfg_t *m_bsp_can_config_ptr = NULL;

static CAN_TxHeaderTypeDef m_bsp_can_tx_header;

static uint32_t m_mailbox = 0U;

static bool find_message_id_from_config(uint16_t message_id,
										const can_tx_message_cfg_t *tx_message_cfg_ptr);

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




