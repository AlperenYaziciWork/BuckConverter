
#include "pid_controller.h"

float PID_Step(pid_controller_t *pid_parameters_ptr, float sensed_value, float reference_point)
{

    float calculated_error;
    float command;
    float command_sat;
    float derivation_measure;

    /* Error calculation */
    calculated_error = reference_point - sensed_value;

    /* Integral term calculation - including anti-windup */
    pid_parameters_ptr->integral += 
        pid_parameters_ptr->Ki*calculated_error*pid_parameters_ptr->TimeStep + 
        pid_parameters_ptr->Kaw*
        (pid_parameters_ptr->command_sat_prev - pid_parameters_ptr->command_prev)*
        pid_parameters_ptr->TimeStep;
    
    /* Derivative term calculation using filtered derivative method */
    derivation_measure = (calculated_error - pid_parameters_ptr->error_previous )/(pid_parameters_ptr->TimeStep);
    pid_parameters_ptr->error_previous = calculated_error;

    /* Summing the 3 terms */
    command = pid_parameters_ptr->Kp*calculated_error + pid_parameters_ptr->integral + pid_parameters_ptr->Kd*derivation_measure;

    /* Remember command at previous step */
    pid_parameters_ptr->command_prev = command;

    /* Saturate command */
    if (command > pid_parameters_ptr->controller_output_max)
    {
        command_sat = pid_parameters_ptr->controller_output_max;
    }
    else if (command < pid_parameters_ptr->controller_output_min)
    {
        command_sat = pid_parameters_ptr->controller_output_min;
    }
    else
    {
        command_sat = command;
    }

    /* Remember saturated command at previous step */
    pid_parameters_ptr->command_sat_prev = command_sat;

    return command_sat;
}

