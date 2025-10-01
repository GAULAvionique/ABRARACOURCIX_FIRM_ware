/*
 * motor.c
 *
 *  Created on: Sep 24, 2025
 *      Author: Etienne
 */
#include <stdint.h>
#include "stm32f4xx.h"
#include "tim.h"
#include "motor.h"

#define MINIMUM_THROTLE_PULSE 1000 //us
#define MAXIMUM_THROTLE_PULSE 1400 //us

// Function to initialize PWM and start motor control
void Motor_Init(void) {
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, MINIMUM_THROTLE_PULSE);
	HAL_Delay(2000); // wait ~2s for arming
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, MAXIMUM_THROTLE_PULSE);
	HAL_Delay(4000); // wait ~2s for arming
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1600);
}

// Function to set motor speed (pulse width in microseconds)
void Motor_SetSpeed(uint16_t pulse_width_us) {
    if (pulse_width_us < 1000) pulse_width_us = 1000;
    if (pulse_width_us > 2000) pulse_width_us = 2000;

    // Set initial pulse width (1 ms = 1000 ticks)
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, pulse_width_us);
}

