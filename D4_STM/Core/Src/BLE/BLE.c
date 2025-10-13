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
#include <stdlib.h>

#define BLE_CMD_LENGTH 6


uint8_t rxBuffer[BLE_CMD_LENGTH];  // buffer for a single command
uint8_t rxIndex = 0;               // current position in buffer

extern UART_HandleTypeDef huart2;

void BLE_Init(void)
{
    rxIndex = 0;
    HAL_UART_Receive_IT(&huart2, &rxBuffer[rxIndex], 1); // start receiving 1 byte
}

void BLE_SendString(const char *str) {
    HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

void BLE_SendData(uint8_t *data, uint16_t size) {
    HAL_UART_Transmit(&huart2, data, size, HAL_MAX_DELAY);
}


uint8_t BLE_ReceiveByte(uint8_t *byte) {
    // Expect exactly 4 bytes: command + 3 digits (e.g. "C075")
    if (HAL_UART_Receive(&huart2, byte, 4, HAL_MAX_DELAY) == HAL_OK)
    {
        switch (byte[0])
        {
            case 'A':
                Motor_Init();
                break;

            case 'B':
                Motor_Stop();
                break;

            case 'C':
            {
                // Copy next 3 bytes as an ASCII number string
                char number_string[4];
                memcpy(number_string, &byte[1], 3);
                number_string[3] = '\0';

                // Convert to integer
                uint8_t value = (uint8_t)atoi(number_string);
                if (value > 100)
                    value = 100;

                // Apply motor speed
                Motor_SetSpeed(value);
                break;
            }

            default:
                // Unknown command — ignore or handle error
                break;
        }
    }

    return 0;
}

void BLE_ProcessCommand(uint8_t *cmd) {
    switch (cmd[0])
    {
        case 'A':
            Motor_Init();
            break;

        case 'B':
            Motor_Stop();
            break;

        case 'C':
        {
            // Convert 3 digits after 'C' to uint8_t
            char number_string[4];
            memcpy(number_string, &cmd[1], 3);
            number_string[3] = '\0';

            uint8_t value = (uint8_t)atoi(number_string);
            if (value > 100) value = 100;

            Motor_SetSpeed(value);
            break;
        }

        default:
            // Unknown command
            break;
    }
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

