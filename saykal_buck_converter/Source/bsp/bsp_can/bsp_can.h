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

/**
 * @brief Defines the type of CAN Identifier format.
 */
typedef enum
{
    /// Standard 11-bit CAN Identifier
    CANID_STANDARD,

    /// Extended 29-bit CAN Identifier
    CANID_EXTENDED,

} canid_e;

/**
 * @brief Configuration structure for a single CAN transmit message.
 */
typedef struct
{
    /// Logical message ID used by the application to refer to this message
    uint16_t message_id;

    /// Actual CAN identifier (11-bit or 29-bit depending on id_type)
    uint32_t can_id;

    /// Type of CAN identifier (standard or extended)
    canid_e id_type;

} can_tx_message_cfg_t;

/**
 * @brief Configuration structure for CAN peripheral and message mappings.
 */
typedef struct
{
    /// Pointer to CAN peripheral base (e.g., CAN1, CAN2)
    CAN_TypeDef *can_instance_ptr;

    /// Clock prescaler for CAN bit timing
    uint32_t clock_prescaler;

    /// Synchronization jump width setting for CAN bit timing
    uint32_t sync_jump_bit;

    /// Time segment 1 value for CAN bit timing
    uint32_t time_segment_1;

    /// Time segment 2 value for CAN bit timing
    uint32_t time_segment_2;

    /// GPIO pin configuration ID used for CAN TX/RX lines
    uint8_t can_gpio_pins_id;

    /// Pointer to the array of transmit message configurations
    const can_tx_message_cfg_t *tx_messages_ptr;

} bsp_can_cfg_t;


/**
 * @brief Initializes the CAN hardware with given configuration.
 *
 * This function sets up the GPIO pins, CAN peripheral settings (timing, modes)
 * and starts the CAN module.
 *
 * @param[in] bsp_can_configs_ptr Pointer to the CAN configuration structure.
 */
void init_bsp_can(const bsp_can_cfg_t *bsp_can_configs_ptr);

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
							  uint16_t data_len);

#endif /* BSP_CAN_H_ */
