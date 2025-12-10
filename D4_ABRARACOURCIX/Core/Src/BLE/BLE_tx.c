/*
 * BLE_tx.c
 *
 *  Created on: Dec 3, 2025
 *      Author: rempl
 */
#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include <inttypes.h>
#include <math.h>

#include "BLE.h"
#include "BLE_tx.h"

//static char buffer[50];
const uint16_t SIZE_OF_CHAR = 1;



void send_uint32_t_package(char header, uint32_t value){
	char buffer[100];

	uint16_t cxi = 0;
	buffer[0] = header;
	cxi = snprintf(buffer + SIZE_OF_CHAR, sizeof(buffer) - SIZE_OF_CHAR, "%"PRIu32";\n", value);
	BLE_SendData((uint8_t*)buffer, cxi+SIZE_OF_CHAR);
	return;

}


void send_float_package(char header, float value){
	char buffer[100] = {'0'};
	uint16_t cxf = 0;
	buffer[0] = header;

	cxf = snprintf(buffer + SIZE_OF_CHAR, sizeof(buffer) - SIZE_OF_CHAR, "%.3f;\n", value);

	BLE_SendData((uint8_t*)buffer, cxf+SIZE_OF_CHAR);
	return;
}
