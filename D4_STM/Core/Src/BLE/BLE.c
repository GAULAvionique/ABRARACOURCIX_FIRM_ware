/*
 * BLE.c
 *
 *  Created on: Oct 9, 2025
 *      Author: Etienne
 */

#include "BLE.h"
#include <string.h>
#include "usart.h"
#include "stm32f4xx_it.h"
#include "cmsis_os.h"
#include "Motor/motor.h"

extern UART_HandleTypeDef huart2;


void BLE_SendString(const char *str) {
    HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

void BLE_SendData(uint8_t *data, uint16_t size) {
    HAL_UART_Transmit(&huart2, data, size, HAL_MAX_DELAY);
}

uint8_t BLE_ReceiveByte(uint8_t *byte) {
    if (HAL_UART_Receive(&huart2, byte, 1, 0) == HAL_OK) {
        if(byte[0]=='A'){
        	Motor_Init();
        } else if(byte[0]=='B'){
        	Motor_Stop();
        }
    }
    return 0;  // No data
}
