/*
 * led.c
 *
 *  Created on: Feb 1, 2025
 *      Author: felix
 */
#include "main.h"
#include "led.h"

//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

//LED PG13 et PG14


void LED_GreenSetState(eLedState eState)
{
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, eState);
}

void LED_RedSetState(eLedState eState)
{
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, eState);
}
