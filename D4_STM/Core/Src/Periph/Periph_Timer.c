/*
 * Periph_Timer.c
 *
 *  Created on: Sep 25, 2025
 *      Author: felix
 */


#include "Periph_Timer.h"

//static char bufferTX[150] = {0};

#include <math.h>

#include "stm32f429xx.h"

void Timers_SetFrequency(uint32_t uFrequency, TIM_TypeDef* tim_PWM)
{

	tim_PWM->ARR = (uint32_t)((ceil(CLK_TIMER_4 / (uFrequency * (tim_PWM->PSC + 1)))) - 1); //TODO Fix define

}
uint32_t Timers_GetDutyCycle(TIM_TypeDef* tim_PWM, volatile uint32_t* uChannel)
{
	return (uint32_t)(((float)(*uChannel)*100.0f)/((float)(tim_PWM->ARR)));
}


bool Timers_SetDutyCycle(float uDC, TIM_TypeDef* tim_PWM, volatile uint32_t* uChannel)
{

	if((0 > uDC) && (uDC > 1.0f)) return false;


		float uARR = (float)(tim_PWM->ARR);
		*uChannel = (uint32_t)(uARR*uDC);

	return true;

}

uint32_t Timers_GetFrequency(TIM_TypeDef* tim_PWM)
{
	return (uint32_t)(((float)CLK_TIMER_4)/((tim_PWM->ARR + 1)*(tim_PWM->PSC + 1)));
}


