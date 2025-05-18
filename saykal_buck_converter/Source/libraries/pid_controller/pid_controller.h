/*
 * pid_controller.h
 *
 *  Created on: May 18, 2025
 *      Author: alperenyazici
 */

#ifndef PID_CONTROLLER_PID_CONTROLLER_H_
#define PID_CONTROLLER_PID_CONTROLLER_H_

typedef struct
{
    float Kp;              // Proportional gain constant
    float Ki;              // Integral gain constant
    float Kd;              // Derivative gain constant
    float Kaw;             // Anti-windup gain constant
    float TimeStep;               // Time step
    float controller_output_max;             // Max controller_output
    float controller_output_min;             // Min controller_output
    float integral;        // Integral term
    float error_previous;        // Previous error
    float command_sat_prev;// Previous saturated controller_output
    float command_prev;    // Previous controller_output

}pid_controller_t;


float PID_Step(pid_controller_t *pid_parameters_ptr, float sensed_value, float reference_point);

#endif /* PID_CONTROLLER_PID_CONTROLLER_H_ */
