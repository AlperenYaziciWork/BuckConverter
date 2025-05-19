/*
 * bsp_can.h
 *
 *  Created on: May 19, 2025
 *      Author: alperenyazici
 */

#ifndef BSP_CAN_H_
#define BSP_CAN_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"

typedef enum
{
	CANID_STANDARD,
	CANID_EXTENDED,

}canid_e;

typedef struct{

	uint16_t message_id;
	uint32_t can_id;
	canid_e id_type;

}can_tx_message_cfg_t;

typedef struct{

	CAN_TypeDef *can_instance_ptr;
	uint32_t clock_prescaler;
	uint32_t sync_jump_bit;
	uint32_t time_segment_1;
	uint32_t time_segment_2;
	uint8_t can_gpio_pins_id;
	const can_tx_message_cfg_t *tx_messages_ptr;

}bsp_can_cfg_t;

void init_bsp_can(const bsp_can_cfg_t *bsp_can_configs_ptr);

void send_message_over_canbus(uint16_t message_id,
							  uint8_t *message_data_ptr ,
							  uint16_t data_len);

#endif /* BSP_CAN_H_ */
