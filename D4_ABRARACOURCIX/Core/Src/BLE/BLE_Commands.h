/*
 * BLE_Commands.h
 *
 *  Created on: Oct 13, 2025
 *      Author: Etienne
 */

#ifndef SRC_BLE_BLE_COMMANDS_H_
#define SRC_BLE_BLE_COMMANDS_H_

#include "stm32f4xx.h"

void BLE_ParseCommand(uint8_t *cmd);
void BLE_ProcessCommand(char commandType);
#endif /* SRC_BLE_BLE_COMMANDS_H_ */
