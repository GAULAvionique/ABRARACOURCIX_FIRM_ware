/*
 * Controller.h
 *
 *  Created on: Oct 30, 2025
 *      Author: rempl
 */

#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

void regulate(float setPointAngSpeed);
float PICompute(float kp, float ki, float angSpeed, float setPointAngSpeed, float * integralError);
float ServoFilter(float PID_Output);
void Set_PID(float _kp, float _ki, float _kd);
void Set_Setpoint(float sp);
void Set_motor_speed(uint8_t new_motor_speed);
void programmed_gains();

void set_Regulate(uint32_t set_regulate);
void set_scaling_factor(float p_scaling_factor);

float get_ang_speed();
float get_cmd_servo();
float get_error();
float get_int_error();
float get_P();
float get_I();
float get_D();
float get_setpoint();
void setSetpoint(float p_setpoint);

extern float setpoint;

#endif /* SRC_CONTROLLER_CONTROLLER_H_ */
