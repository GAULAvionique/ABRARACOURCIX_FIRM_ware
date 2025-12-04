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
#include "../Controller/Controller.h"

#define MINIMUM_THROTLE_PULSE 1000 //us
#define MAXIMUM_THROTLE_PULSE 2000 //us

// Function to initialize PWM and start motor control
void Motor_Init(void) {
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, MINIMUM_THROTLE_PULSE);
	//HAL_Delay(2000); // wait ~2s for arming
	//__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, MINIMUM_THROTLE_PULSE);
	//HAL_Delay(2000); // wait ~2s for arming
	//__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, MINIMUM_THROTLE_PULSE+50);
}

// Function to set motor speed (pulse width in microseconds)
void Motor_SetSpeed(uint8_t p_duty_cycle) {
    if (p_duty_cycle < 0) p_duty_cycle = 0;
    if (p_duty_cycle > 100) p_duty_cycle = 100;
    Set_motor_speed(p_duty_cycle);
    uint16_t pulse_width_us = MINIMUM_THROTLE_PULSE + ((uint32_t)p_duty_cycle * MINIMUM_THROTLE_PULSE) / 100;

    // Set initial pulse width (1 ms = 1000 ticks)
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse_width_us);
}

// Function to stop the motor
void Motor_Stop(void) {
    // Set PWM to minimum throttle
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

