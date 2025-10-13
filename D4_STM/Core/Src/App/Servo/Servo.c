/*
 * Servo.c
 *
 *  Created on: Oct 10, 2025
 *      Author: rempl
 */

#include "Servo.h"


void setServoDuty(int servoID, float dutyCycle){


	if(dutyCycle < 0.01 || dutyCycle>1.0){
		// Invalid duty cycle
		return;
	}

	int16_t ccr = (int16_t)(dutyCycle * TIM4->ARR);

	switch(servoID){
	case 1:
		TIM4->CCR1 = ccr;
		break;

	case 2:
		TIM4->CCR2 = ccr;
		break;

	case 3:
		TIM4->CCR3 = ccr;
		break;

	case 4:
		TIM4->CCR4 = ccr;
		break
		;
	default:

	}


	return;
}


void setAllServos(float dutyCycle){
	  setServoDuty(1, dutyCycle);
	  setServoDuty(2, dutyCycle);
	  setServoDuty(3, dutyCycle);
	  setServoDuty(4, dutyCycle);
}

