/*
 * BLE_Commands.c
 *
 *  Created on: Oct 13, 2025
 *      Author: Etienne
 */

#include "BLE_Commands.h"
#include "../Motor/motor.h"
#include "../Controller/Controller.h"
#include "../IMU/IMU.h"
#include <stdlib.h>
#include <string.h>

float ki = 0;
float kp = 0;
float kd = 0;

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
            char number_string[4];
            memcpy(number_string, &cmd[1], 3);
            number_string[3] = '\0';

            uint8_t value = (uint8_t)atoi(number_string);
            if (value > 100) value = 100;

            Motor_SetSpeed(value);
            break;
        
        
        case 'P':
            memcpy(&kp, &cmd[1], 4);
            Set_PID(kp, ki, kd);
            break;

        case 'I':
            memcpy(&ki, &cmd[1], 4);
            Set_PID(kp, ki, kd);
            break;


        case 'D':
            memcpy(&kd, &cmd[1], 4);
            Set_PID(kp, ki, kd);
            break;

        case 'E' : //alpha
            float alpha = 0.0f; 
            memcpy(&alpha, &cmd[1], 4);

            IMU_SetAlpha(alpha);

            break;

        case 'Z':

            uint32_t filter_id = 0.0f; 
            memcpy(&filter_id, &cmd[1], 4);

            IMU_SetFilter(filter_id);
            break;

        case 'S':
            
            uint32_t length = 0; 
            memcpy(&length, &cmd[1], 4);

            IMU_SetIIR_Length(length);
            break;

        default:
            break;
    }
}



