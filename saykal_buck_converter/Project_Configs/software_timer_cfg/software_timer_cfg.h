/*
 * software_timer_cfg.h
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#ifndef SOFTWARE_TIMER_CFG_SOFTWARE_TIMER_CFG_H_
#define SOFTWARE_TIMER_CFG_SOFTWARE_TIMER_CFG_H_

#define BUCK_CONVERTER_PID_SOFTWARE_TIMER_ID 0U
#define COM_VOLTAGE_CURRENT_SYSTEM_INFO_MESSAGE_TIMER 1U // used 1 timer base for all defined messages 
                        //because it is better to send voltage and current information at the same time.
                        // but if it is needed to add any other timer for any com message, it is very easy to make it happen.

#define SOFTWARE_TIMER_CNT 2U

#endif /* SOFTWARE_TIMER_CFG_SOFTWARE_TIMER_CFG_H_ */
