/*
 * BLE.c
 *
 *  Created on: Oct 9, 2025
 *      Author: Etienne
 */

#include "BLE.h"
#include "BLE/BLE_Commands.h"

#include "usart.h"
#include "stm32f4xx_it.h"

#include <string.h>

#define BLE_CMD_LENGTH 6


uint8_t rxBuffer[BLE_CMD_LENGTH];  // buffer for a single command
uint8_t rxIndex = 0;               // current position in buffer

extern UART_HandleTypeDef huart2;

void BLE_Init(void)
{
    rxIndex = 0;
    HAL_UART_Receive_IT(&huart2, &rxBuffer[rxIndex], 1);
}

void BLE_SendString(const char *str) {
    HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

void BLE_SendData(uint8_t *data, uint16_t size) {
    HAL_UART_Transmit(&huart2, data, size, HAL_MAX_DELAY);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)  // check your UART
    {
        rxIndex++;

        // If buffer full or received newline, process command
        if (rxIndex >= 4)  // minimum command length (A/B/C + 3 digits)
        {
            BLE_ProcessCommand(rxBuffer);  // parse & execute
            rxIndex = 0;                    // reset for next command
        }

        // Receive next byte
        HAL_UART_Receive_IT(&huart2, &rxBuffer[rxIndex], 1);
    }
}

