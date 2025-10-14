/*
 * BLE.h
 *
 *  Created on: Oct 9, 2025
 *      Author: Etienne
 */

#ifndef SRC_BLE_BLE_H_
#define SRC_BLE_BLE_H_

#include "stm32f4xx.h"

void BLE_Init(void);

void BLE_SendString(const char *str);

void BLE_SendData(uint8_t *data, uint16_t size);

uint8_t BLE_ReceiveByte(uint8_t *byte);

#endif /* SRC_BLE_BLE_H_ */
