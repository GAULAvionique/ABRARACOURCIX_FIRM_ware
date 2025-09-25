/*
 * Ctrl_Servo.c
 *
 *  Created on: Sep 25, 2025
 *      Author: felix
 */


#include "Ctrl_Servo.h"
#include "tim.h"
#include "stm32f429xx.h"

extern sServoCtrl_t sServoCtrl[NUMBER_OF_SERVO];


void CtrlServo_Init(void)
{
	sServoCtrl[SERVO_1].sServoHW.tim_PWM = TIM4;
	sServoCtrl[SERVO_1].pfSetPosition = Servo_SetPosition;
	sServoCtrl[SERVO_1].pfGetPosition = Servo_GetPosition;

	//Servo 1

	sServoCtrl[SERVO_1].eServoID = SERVO_1;
	sServoCtrl[SERVO_1].sServoHW.uTimChan = &TIM4->CCR1;

	//Servo 2
	memcpy(&sServoCtrl[SERVO_2],&sServoCtrl[SERVO_1], sizeof(sServoCtrl[SERVO_1]));
	sServoCtrl[SERVO_2].eServoID = SERVO_2;
	sServoCtrl[SERVO_2].sServoHW.uTimChan = &TIM4->CCR2;


	//Servo 3
	memcpy(&sServoCtrl[SERVO_3],&sServoCtrl[SERVO_1], sizeof(sServoCtrl[SERVO_1]));
	sServoCtrl[SERVO_3].eServoID = SERVO_3;
	sServoCtrl[SERVO_3].sServoHW.uTimChan = &TIM4->CCR3;



	//Servo 4
	memcpy(&sServoCtrl[SERVO_4],&sServoCtrl[SERVO_1], sizeof(sServoCtrl[SERVO_1]));
	sServoCtrl[SERVO_4].eServoID = SERVO_4;
	sServoCtrl[SERVO_4].sServoHW.uTimChan = &TIM4->CCR4;



}
