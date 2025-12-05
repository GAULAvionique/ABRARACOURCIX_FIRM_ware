/*
 * motor.h
 *
 *  Created on: Sep 24, 2025
 *      Author: Etienne
 */

#ifndef SRC_MOTOR_MOTOR_H_
#define SRC_MOTOR_MOTOR_H_

void Motor_Init(void);

void Motor_SetSpeed(uint8_t p_duty_cycle);

void Motor_RampSpeed(uint8_t p_duty_cycle);

void Motor_Stop(void);

#endif /* SRC_MOTOR_MOTOR_H_ */
