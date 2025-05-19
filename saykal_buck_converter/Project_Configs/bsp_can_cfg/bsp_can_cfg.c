/*
 * bsp_can_cfg.c
 *
 *  Created on: May 19, 2025
 *      Author: alperenyazici
 */

#include "bsp_can.h"
#include "bsp_gpio_cfg.h"
#include "com_driver_cfg.h"

const can_tx_message_cfg_t m_can_tx_messages_config[] =
{
		{
			.can_id = 0x123,
			.id_type = CANID_EXTENDED,
			.message_id = COM_BUCK_VOLTAGE_INFO_MESSAGE_ID,
		},
		{
			.can_id = 0x456,
			.id_type = CANID_EXTENDED,
			.message_id = COM_BUCK_CURRENT_INFO_MESSAGE_ID,
		},
		{
			.can_id = 0x789,
			.id_type = CANID_EXTENDED,
			.message_id = COM_BUCK_SYSTEM_INFO_MESSAGE_ID,
		},
};

const bsp_can_cfg_t g_bsp_can_configurations =
{
		.can_gpio_pins_id = BSP_CAN_PINS_ID,
		.can_instance_ptr = CAN1,
		.clock_prescaler = 1U,
		.sync_jump_bit = CAN_SJW_1TQ,
		.time_segment_1 = CAN_BS1_6TQ,
		.time_segment_2 = CAN_BS2_1TQ,
		.tx_messages_ptr = m_can_tx_messages_config,
};

