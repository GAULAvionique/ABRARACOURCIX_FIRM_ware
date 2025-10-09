/*
 * BLE.h
 *
 *  Created on: Oct 9, 2025
 *      Author: Etienne
 */

#ifndef SRC_BLE_BLE_H_
#define SRC_BLE_BLE_H_

#include "stm32f4xx.h"

#include "stm32f4xx_hal.h"

#define BLE_RX_BUFFER_SIZE 64

void BLE_SendString(const char *str);

void BLE_SendData(uint8_t *data, uint16_t size);

uint8_t BLE_ReceiveByte(uint8_t *byte);

#endif /* SRC_BLE_BLE_H_ */
