/*
 * Periph_Timer.h
 *
 *  Created on: Sep 25, 2025
 *      Author: felix
 */

#ifndef SRC_PERIPH_APP_TIMERS_H_
#define SRC_PERIPH_APP_TIMERS_H_

#include <stdint.h>
#include "main.h"

#define CLK_TIMER_4			(72000000) //72MHz

typedef enum{
	TIMER1 = 0,
	TIMER2 ,
	TIMER3 ,
	TIMER4 ,
	TIMER5 ,
	TIMER6 ,
	TIMER7 ,
	TIMER8 ,


}eTimersID;



void Timers_SetFrequency(uint32_t uFrequency, TIM_TypeDef* tim_PWM);
bool Timers_SetDutyCycle(float uDC, TIM_TypeDef* tim_PWM, volatile uint32_t* uChannel);
uint32_t Timers_GetDutyCycle(TIM_TypeDef* tim_PWM, volatile uint32_t* uChannel);
uint32_t Timers_GetFrequency(TIM_TypeDef* tim_PWM);

#endif /* SRC_PERIPH_APP_TIMERS_H_ */

