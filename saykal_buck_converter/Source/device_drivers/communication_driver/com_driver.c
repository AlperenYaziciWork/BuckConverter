/**
 * @file com_driver.c
 * @brief Communication Driver Source File
 * @details
 * This file implements a communication driver that handles signal packing into PDUs (Protocol Data Units)
 * and transmits them over various communication buses such as CAN, SPI, or UART.
 * 
 * Features:
 * - Signal-to-message mapping
 * - Bit-level manipulation for little-endian and big-endian signals
 * - Periodic message transmission via software timers
 * 
 * Author: Alperen Yazıcı
 * Created on: May 19, 2025
 */


#include "com_driver.h"
#include "stddef.h"

/**
 * @def COM_MESSAGE_DATA_LEN_MAX
 * @brief Maximum length (in bytes) of any message buffer.
 */
#ifndef COM_MESSAGE_DATA_LEN_MAX
#define COM_MESSAGE_DATA_LEN_MAX 0
#endif

/**
 * @def COM_MESSAGE_CNT
 * @brief Total number of communication messages defined in the system.
 */
#ifndef COM_MESSAGE_CNT
#define COM_MESSAGE_CNT 0
#endif

/**
 * @def COM_SIGNAL_CNT
 * @brief Total number of communication signals defined in the system.
 */
#ifndef COM_SIGNAL_CNT
#define COM_SIGNAL_CNT 0
#endif

/**
 * @var m_com_message_buffer
 * @brief 2D buffer holding raw PDU data for each message.
 * Indexed by message ID, sized according to maximum data length.
 */
static uint8_t m_com_message_buffer[COM_MESSAGE_CNT][COM_MESSAGE_DATA_LEN_MAX];

/**
 * @var m_com_configs_ptr
 * @brief Pointer to the active communication configuration structure.
 */
static com_configs_t *m_com_configs_ptr = NULL;

/**
 * @brief Starts software timers for periodic transmission of messages.
 */
static void start_periodic_tx_messages_timers(void);

/**
 * @brief Sends the message buffer over the selected communication bus.
 *
 * @param[in] message_bus Communication bus type (CAN, SPI, UART).
 * @param[in] message_id ID of the message to be sent.
 * @param[in] message_data_ptr Pointer to message data.
 * @param[in] message_length Length of the message data.
 */
static void send_message_over_related_bus(com_message_bus_e message_bus,
                                         com_message_id_t message_id,
                                         uint8_t *message_data_ptr,
                                         uint16_t message_length);

                                         /**
 * @brief Maps a signal bit stream into its corresponding PDU buffer.
 *
 * Handles both little endian and big endian placement.
 *
 * @param[in] signal_info Signal bit position, size and endianness.
 * @param[in] p_signal_buff Pointer to signal value buffer.
 * @param[out] p_pdu_memory Pointer to the message buffer (PDU) to be filled.
 * @return true if success, false if endianness unsupported.
 */
static inline bool signal_to_message_locate(signal_base_info_t signal_info,
                                        const uint8_t* p_signal_buff,
                                        uint8_t* p_pdu_memory);

                                        /**
 * @brief Searches for the message containing the given signal ID.
 *
 * @param[in] signal_id Signal ID to find.
 * @param[out] message_id_ptr Pointer to store found message ID.
 * @param[out] signal_index_in_message_ptr Index of the signal in the message.
 * @return true if found, false otherwise.
 */
static bool find_message_with_signal_id(com_signal_id_t signal_id,
										com_message_id_t *message_id_ptr,
										uint8_t *signal_index_in_message_ptr);

/**
 * @brief bit set function into uint8_t type array
 *
 * @param[out] p_dest destination array start address
 * @param[in] bit     will be set bit destination.
 */
static inline void bit_set(uint8_t* p_dest, uint32_t bit);

/**
 * @brief bit clear function into uint8_t type array
 *
 * @param[out] p_dest destination array start address
 * @param[in] bit     will be cleared bit destination.
 */
static inline void bit_clear(uint8_t *p_dest, uint32_t bit);

/**
 * @brief bit get function from uint8_t type array
 *
 * @param[in] p_source  source array start address
 * @param[in] bit       will be getten bit destination
 * @return uint8_t      read bit's value
 */
static inline uint8_t bit_get(const uint8_t *p_source, uint32_t bit);

/**
 * @brief Initializes the communication driver.
 *
 * Sets up internal pointers and starts software timers for periodic message transmission.
 *
 * @param[in] com_configs_ptr Pointer to communication configuration.
 */
void init_com_driver(const com_configs_t *com_configs_ptr)
{
	if(NULL != com_configs_ptr)
	{
		m_com_configs_ptr = (com_configs_t *)com_configs_ptr;

        start_periodic_tx_messages_timers();
	}
	else
	{
		report_development_error();
	}
}

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
void trigger_send_of_message(com_message_id_t message_id)
{
	send_message_over_related_bus(
	                m_com_configs_ptr->messages_ptr[message_id].transmission_bus_of_message,
					message_id,
	                &m_com_message_buffer[message_id][0],
	                m_com_configs_ptr->messages_ptr[message_id].message_data_length);
}
/**
 * @brief Sends a signal by mapping it into its message buffer.
 *
 * Finds the message that includes the given signal and inserts the signal value into the corresponding buffer.
 *
 * @param[in] signal_id ID of the signal to be sent.
 * @param[in] signal_value_ptr Pointer to the value of the signal to be sent.
 * @return true if successful, false otherwise.
 */
bool send_signal_over_com(com_signal_id_t signal_id , void *signal_value_ptr)
{
	if(signal_id >= COM_SIGNAL_CNT)
	{
		report_development_error();
		return false;
	}

	com_message_id_t message_id = 0U;
	uint8_t signal_index_in_message = 0U;
	bool is_message_found = find_message_with_signal_id(signal_id,&message_id,&signal_index_in_message);

	if(false == is_message_found)
	{
		report_development_error();
		return false;
	}

	const signal_base_info_t *signal_base_info_ptr =
		&m_com_configs_ptr->messages_ptr[message_id].signals_ptr[signal_index_in_message].signal_base_info;

	signal_to_message_locate((*signal_base_info_ptr),
						 signal_value_ptr,
						 &m_com_message_buffer[message_id][0]);

	return true;
}

/**
 * @brief Callback function for periodic message transmission.
 *
 * Called by the software timer and checks which message should be sent.
 *
 * @param[in] sw_timer_id ID of the triggered software timer.
 */
void send_periodic_message_timeout_cb(software_timer_id_t sw_timer_id)
{
    for (uint8_t msg_idx = 0U; msg_idx < COM_MESSAGE_CNT; msg_idx++)
    {
        if(NULL == m_com_configs_ptr->messages_ptr[msg_idx].periodic_send_info)
        {
            continue;
        }

        software_timer_id_t message_sw_timer_id = 
            m_com_configs_ptr->messages_ptr[msg_idx].periodic_send_info->sw_timer_id;
        
        if(message_sw_timer_id == sw_timer_id)
        {
            send_message_over_related_bus(
                m_com_configs_ptr->messages_ptr[msg_idx].transmission_bus_of_message,
                msg_idx,
                &m_com_message_buffer[msg_idx][0],
                m_com_configs_ptr->messages_ptr[msg_idx].message_data_length);
        }
    }
    
}

/**
 * @brief Sends the message buffer over the selected communication bus.
 *
 * @param[in] message_bus Communication bus type (CAN, SPI, UART).
 * @param[in] message_id ID of the message to be sent.
 * @param[in] message_data_ptr Pointer to message data.
 * @param[in] message_length Length of the message data.
 */
static void send_message_over_related_bus(com_message_bus_e message_bus,
                                         com_message_id_t message_id,
                                         uint8_t *message_data_ptr,
                                         uint16_t message_length)
{
    switch (message_bus)
    {
        case MESSAGE_BUS_CANBUS:
        {
            send_message_over_canbus(message_id,message_data_ptr,message_length);
            break;
        }
        case MESSAGE_BUS_SPI:
        {
            // message transmission bus easly change in configuration.
            break;
        }
        case MESSAGE_BUS_UART:
        {
            // message transmission bus easly change in configuration.
            break;
        }
    default:
        break;
    }
}

/**
 * @brief Searches for the message containing the given signal ID.
 *
 * @param[in] signal_id Signal ID to find.
 * @param[out] message_id_ptr Pointer to store found message ID.
 * @param[out] signal_index_in_message_ptr Index of the signal in the message.
 * @return true if found, false otherwise.
 */
static bool find_message_with_signal_id(com_signal_id_t signal_id,
										com_message_id_t *message_id_ptr,
										uint8_t *signal_index_in_message_ptr)
{
	bool is_message_found = false;
	for(com_message_id_t msg_idx = 0U; msg_idx < COM_MESSAGE_CNT;msg_idx++)
	{
		uint8_t signal_cnt_in_message =
				m_com_configs_ptr->messages_ptr[msg_idx].total_signal_cnt_in_message;

		for(com_message_id_t signal_idx = 0U; signal_idx < signal_cnt_in_message;signal_idx++)
		{
			if(signal_id ==
			   m_com_configs_ptr->messages_ptr[msg_idx].signals_ptr[signal_idx].signal_id)
			{
				is_message_found = true;
				*message_id_ptr = msg_idx;
				*signal_index_in_message_ptr =signal_idx;
			}
		}
	}

	return is_message_found;
}

/**
 * @brief Maps a signal bit stream into its corresponding PDU buffer.
 *
 * Handles both little endian and big endian placement.
 *
 * @param[in] signal_info Signal bit position, size and endianness.
 * @param[in] p_signal_buff Pointer to signal value buffer.
 * @param[out] p_pdu_memory Pointer to the message buffer (PDU) to be filled.
 * @return true if success, false if endianness unsupported.
 */
static inline bool signal_to_message_locate(signal_base_info_t signal_info,
                                        	const uint8_t* p_signal_buff,
											uint8_t* p_pdu_memory)
{
    uint32_t start_bit = signal_info.com_bit_position;
    uint8_t length = signal_info.com_bit_size;
    com_signal_endianness_e endian = signal_info.com_signal_endianness;
    uint32_t pdu_bit_index = start_bit;

    if (COM_SIGNAL_ENDIANNESS_LITTLE_ENDIAN == endian)
    {
        for (uint8_t signal_bit_idx = 0;
             signal_bit_idx < length;
             signal_bit_idx++)
        {
            uint8_t bit_val = bit_get(p_signal_buff , (uint32_t)signal_bit_idx);

            if(1u == bit_val)
            {
                bit_set(p_pdu_memory , (uint32_t)pdu_bit_index);
            }
            else
            {
                bit_clear(p_pdu_memory ,(uint32_t)pdu_bit_index);
            }
            pdu_bit_index++;
        }

    }
    else if(COM_SIGNAL_ENDIANNESS_BIG_ENDIAN == endian)
    {
        uint8_t signal_bit_idx = length;

        do
        {
            signal_bit_idx--;

            uint8_t bit_val = bit_get(p_signal_buff , (uint32_t)signal_bit_idx);

            if(1u == bit_val)
            {
                bit_set(p_pdu_memory , pdu_bit_index);
            }
            else
            {
                bit_clear(p_pdu_memory , pdu_bit_index);
            }

            if((pdu_bit_index%8u) == 0u)
            {
                pdu_bit_index +=16u;
            }

            pdu_bit_index--;

        }while (signal_bit_idx > 0u);
    }
    else
    {
        return false;
    }

    return true;
}

/**
 * @brief bit set function into uint8_t type array
 *
 * @param[out] p_dest destination array start address
 * @param[in] bit     will be set bit destination.
 */
static inline void bit_set(uint8_t* p_dest, uint32_t bit)
{
    p_dest[bit / 8U] |= (uint8_t)(1u << (bit % 8U));
}

/**
 * @brief bit clear function into uint8_t type array
 *
 * @param[out] p_dest destination array start address
 * @param[in] bit     will be cleared bit destination.
 */
static inline void bit_clear(uint8_t *p_dest, uint32_t bit)
{
    p_dest[bit / 8U] &= (uint8_t)~(1u << (bit % 8U));
}

/**
 * @brief bit get function from uint8_t type array
 *
 * @param[in] p_source  source array start address
 * @param[in] bit       will be getten bit destination
 * @return uint8_t      read bit's value
 */
static inline uint8_t bit_get(const uint8_t *p_source, uint32_t bit)
{
    return (uint8_t)((p_source[bit / 8U] & (1u << (bit % 8U)))>>(bit%8u));
}

/**
 * @brief Starts software timers for periodic transmission of messages.
 */
static void start_periodic_tx_messages_timers()
{
    for (uint8_t msg_idx = 0; msg_idx < COM_MESSAGE_CNT; msg_idx++)
    {
        if(NULL != m_com_configs_ptr->messages_ptr[msg_idx].periodic_send_info)
        {
            software_timer_id_t sw_timer_id = 
                m_com_configs_ptr->messages_ptr[msg_idx].periodic_send_info->sw_timer_id;

            uint16_t tx_period_ms = 
                m_com_configs_ptr->messages_ptr[msg_idx].periodic_send_info->send_period_ms;

            start_software_timer(sw_timer_id , tx_period_ms);
        }
    }
}

