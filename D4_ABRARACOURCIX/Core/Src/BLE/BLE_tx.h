/*
 * BLE_tx.h
 *
 *  Created on: Dec 3, 2025
 *      Author: rempl
 */

#ifndef SRC_BLE_BLE_TX_H_
#define SRC_BLE_BLE_TX_H_

void send_uint32_t_package(char header, uint32_t value);
void send_float_package(char header, float value);

#endif /* SRC_BLE_BLE_TX_H_ */
