/*
 * App_Servo.h
 *
 *  Created on: Sep 25, 2025
 *      Author: felix
 */

#ifndef SRC_APP_APP_SERVO_APP_SERVO_H_
#define SRC_APP_APP_SERVO_APP_SERVO_H_

#include "main.h"
#include "stm32f429xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define NUMBER_OF_SERVO		(4)


typedef enum {

  SERVO_1 = (0),
  SERVO_2,
  SERVO_3,
  SERVO_4,

} eServoID_t;

typedef struct {
  TIM_TypeDef *tim_PWM;
  volatile uint32_t *uTimChan;

} sServoHW_t;


typedef struct sServoCtrl_t{
	eServoID_t eServoID;
	sServoHW_t sServoHW;
	bool (*pfSetPosition)(struct sServoCtrl_t* sServoCtrl, float uPosition);
	uint32_t (*pfGetPosition)(struct sServoCtrl_t* sServoCtrl);
} sServoCtrl_t;


bool Servo_SetPosition(sServoCtrl_t* sServoCtrl, float uPosition);
uint32_t Servo_GetPosition(sServoCtrl_t* sServoCtrl);



#endif /* SRC_APP_APP_SERVO_APP_SERVO_H_ */
