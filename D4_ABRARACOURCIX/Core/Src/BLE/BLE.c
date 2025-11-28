/*
 * BLE.c
 *
 *  Created on: Oct 9, 2025
 *      Author: Etienne
 */

#include "BLE.h"
#include "BLE_Commands.h"

#include "usart.h"
#include "stm32f4xx_it.h"

#include <string.h>


static CircularFIFO fifo = {.head_read = 0, .head_write = 0};
static char receivedChar;

extern UART_HandleTypeDef huart2;

void BLE_Init(void)
{
    HAL_UART_Receive_IT(&huart2, (uint8_t*)&fifo.buffer[fifo.head_write], 1);
}

void BLE_SendString(const char *str) {
    HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

void BLE_SendData(uint8_t *data, uint16_t size) {
    HAL_UART_Transmit(&huart2, data, size, HAL_MAX_DELAY);
}

uint8_t BLE_ReadData(uint8_t *uartData){

    if(fifo.head_read == fifo.head_write){
        return 0;
    }

    *uartData = fifo.buffer[fifo.head_read];
    fifo.head_read = (fifo.head_read + 1) % BUFFER_SIZE;
    return 1;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2) {

		__disable_irq();  // disable all interrupts

		if(fifo.head_write + 1 == fifo.head_read){
			fifo.head_read++;
		}
		fifo.buffer[fifo.head_write] = receivedChar;
		fifo.head_write += 1;

		if(fifo.head_write >= BUFFER_SIZE){
			fifo.head_write = 0;
		}
		HAL_UART_Receive_IT(huart, (uint8_t*)&receivedChar, 1);  // Restart reception
		__enable_irq();   // enable all interrupts
	}
}


