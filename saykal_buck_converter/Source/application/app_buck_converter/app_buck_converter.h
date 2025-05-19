/*
 * app_buck_converter.h
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#ifndef APP_BUCK_CONVERTER_H_
#define APP_BUCK_CONVERTER_H_

#include "stdint.h"
#include "pid_controller.h"

/**
 * @brief Configuration structure for the buck converter control system.
 *
 * This structure holds all the parameters and references required to
 * initialize and operate a buck converter using cascaded PID control.
 */
typedef struct
{
    /**
     * @brief Pointer to the PID controller for output voltage regulation.
     *
     * This controller calculates the desired output current reference based
     * on the error between measured and target output voltage.
     */
    pid_controller_t *pid_out_voltage_cotroller_ptr;

    /**
     * @brief Pointer to the PID controller for output current control.
     *
     * This controller generates the PWM duty cycle based on the error between
     * measured and target output current (which is derived from the outer voltage loop).
     */
    pid_controller_t *pid_out_current_cotroller_ptr;

    /**
     * @brief Period (in milliseconds) to execute the control process.
     *
     * Determines how frequently the control loop should run. It is typically
     * used by a software timer.
     */
    uint8_t period_time_process_of_controller_ms;

    /**
     * @brief Reference voltage value (in volts) to be maintained at the converter output.
     *
     * This is the target voltage used by the outer PID voltage controller.
     */
    float v_out_ref;

    /**
     * @brief Maximum allowable output current (in amperes).
     *
     * If the measured output current exceeds this value consistently for a certain
     * duration, it is treated as an overcurrent fault.
     */
    float i_out_max;

    /**
     * @brief Minimum duration (in control loop cycles) over which overcurrent must persist to be considered a fault.
     *
     * Helps prevent false positives due to short spikes or noise. If overcurrent is
     * detected for at least this number of consecutive cycles, a critical fault is reported.
     */
    uint16_t over_current_occurence_time_min;

} buck_converter_cfg_t;


/**
 * @brief Initializes the buck converter application with the given configuration.
 *
 * This function sets the buck converter configuration, starts the corresponding PWM channel for the MOSFET,
 * and starts a software timer to periodically execute the control loop.
 *
 * @param[in] buck_converter_cfg_ptr Pointer to the configuration structure of the buck converter.
 *                                   Must not be NULL.
 *
 * @retval None
 */
void init_buck_converter(const buck_converter_cfg_t *buck_converter_cfg_ptr);

/**
 * @brief Performs cascaded PID control for output voltage with current limiting.
 *
 * This function implements a cascaded control loop where the output voltage is regulated
 * using an outer PID loop that generates a current reference. This reference is then used
 * by an inner PID loop to control the output current. The result is translated into a PWM duty cycle
 * to drive the buck converter MOSFET.
 *
 * It reads both output voltage and output current via the ADC sensor driver.
 *
 * It is called by software timer (BUCK_CONVERTER_PID_SOFTWARE_TIMER_ID) periodically.
 *
 * @retval None
 */
void control_out_voltage_with_current_limit(void);

#endif /* APP_BUCK_CONVERTER_H_ */
