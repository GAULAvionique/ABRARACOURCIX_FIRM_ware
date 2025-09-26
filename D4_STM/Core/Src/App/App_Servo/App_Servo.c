/*
 * App_Servo.c
 *
 *  Created on: Sep 25, 2025
 *      Author: felix
*/




#include "CLI.h"
#include "freeRTOS.h"
#include "main.h"
#include "App_Servo.h"
#include "Periph_Timer.h"








sServoCtrl_t sServoCtrl[NUMBER_OF_SERVO];


bool Servo_SetPosition(sServoCtrl_t* sServoCtrl, float uPosition)
{
	return Timers_SetDutyCycle(uPosition, sServoCtrl->sServoHW.tim_PWM, sServoCtrl->sServoHW.uTimChan);
}

uint32_t Servo_GetPosition(sServoCtrl_t* sServoCtrl)
{
	return Timers_GetDutyCycle(sServoCtrl->sServoHW.tim_PWM, sServoCtrl->sServoHW.uTimChan);
}



void Servos_CLI_SetPositioAll(float fPos)
{
	for(uint8_t uIndex = 0; uIndex < NUMBER_OF_SERVO; uIndex++)
	{
		Servo_SetPosition(&sServoCtrl[uIndex], fPos);
	}
}
