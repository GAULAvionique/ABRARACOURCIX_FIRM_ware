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

#endif /* SRC_SERVO_SERVO_H_ */
