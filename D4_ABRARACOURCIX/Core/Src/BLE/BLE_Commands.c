/*
 * BLE_Commands.c
 *
 *  Created on: Oct 13, 2025
 *      Author: Etienne
 */

#include "BLE_Commands.h"
#include "../Motor/motor.h"
#include <stdlib.h>
#include <string.h>

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
            char number_string[4];
            memcpy(number_string, &cmd[1], 3);
            number_string[3] = '\0';

            uint8_t value = (uint8_t)atoi(number_string);
            if (value > 100) value = 100;

            Motor_SetSpeed(value);
            break;
        }

        default:
            break;
    }
}



