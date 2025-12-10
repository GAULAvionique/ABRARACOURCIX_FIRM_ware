/*
 * Servo.h
 *
 *  Created on: Oct 10, 2025
 *      Author: rempl
 */

#ifndef SRC_SERVO_SERVO_H_
#define SRC_SERVO_SERVO_H_

#include "main.h"

void setServoDuty(int servoID, float dutyCycle);
void setAllServos(float dutyCycle);
void setServosSep(float dutyCycle1, float dutyCycle2, float dutyCycle3, float dutyCycle4);

void set_min_range(float p_min_range);
void set_max_range(float p_max_range);

void update_range(float p_range);

void set_offset(uint8_t servo_id, float offset);

float compute_corrected_duty(uint8_t servo_id, float duty);

void update_mid_point();
void init_offset();
float get_duty_cycle();

void set_motor_intensity(float intensity);

#endif /* SRC_SERVO_SERVO_H_ */
