/*
 * BLE.h
 *
 *  Created on: Oct 9, 2025
 *      Author: Etienne
 */

#ifndef SRC_BLE_BLE_H_
#define SRC_BLE_BLE_H_

#include "stm32f4xx.h"

#define BUFFER_SIZE 64


typedef struct{

    uint8_t buffer[BUFFER_SIZE];
    uint8_t head_read;
    uint8_t head_write;

} CircularFIFO;


void BLE_Init(void);

void BLE_SendString(const char *str);

void BLE_SendData(uint8_t *data, uint16_t size);

uint8_t BLE_ReadData(uint8_t *uartData);

#endif /* SRC_BLE_BLE_H_ */
