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
#include "../Servo/Servo.h"
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 16

typedef enum {
  Init = 0,
  WaitInt = 1,
  WaitFloat = 2,
  WaitEOL = 3,
} States;

static float ki = 0;
static float kp = 0;
static float kd = 0;

static States state = Init;

static uint8_t dataIndex = 0;
static uint8_t dataBuffer[BUFFER_SIZE];

static uint32_t dataInt = 0;
static float dataFloat = 0;


void BLE_ParseCommand(uint8_t *cmd) {
	dataIndex = (dataIndex + 1) % BUFFER_SIZE;
	dataBuffer[dataIndex-1] = *cmd;

	switch (state) {
		case Init:
			switch(dataBuffer[0]) {
				case 'A':
				case 'B':
					state = WaitEOL;
					break;
				case 'C':
				case 'S':
				case 'Z':
				case 'G':
					state = WaitInt;
					break;
				case 'P':
				case 'I':
				case 'D':
				case 'E':
				case 'V':
				case 'F':
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
					state = WaitFloat;
					break;
				default:
					state = Init;
					dataIndex = 0;
					break;
			}
			break;

		case WaitEOL:
			if(dataBuffer[dataIndex-1] == '\n') {
				BLE_ProcessCommand(dataBuffer[0]);
			}
			state = Init;
			dataIndex = 0;
			break;

		case WaitInt:
			if(dataIndex == 5) {
				memcpy(&dataInt, &dataBuffer[1], 4);
				state = WaitEOL;
			}
			break;

		case WaitFloat:
			if(dataIndex == 5) {
				memcpy(&dataFloat, &dataBuffer[1], 4);
				state = WaitEOL;
			}
			break;
		default:
			break;
	}
}

void BLE_ProcessCommand(char commandType) {
	switch (commandType)
	{
		case 'A':
			Motor_Init();
			break;

		case 'B':
			Motor_Stop();
			break;

		case 'C':
			uint8_t motor_speed = dataInt;
			if (motor_speed > 100) {
				motor_speed = 100;
			}

			Motor_RampSpeed(motor_speed);
			break;


		case 'P':
			kp = dataFloat;
			Set_PID(kp, ki, kd);
			break;

		case 'I':
			ki = dataFloat;
			Set_PID(kp, ki, kd);
			break;


		case 'D':
			kd = dataFloat;
			Set_PID(kp, ki, kd);
			break;

		case 'E' :
			float alpha = dataFloat;
			IMU_SetAlpha(alpha);
			break;

		case 'Z':

			uint32_t filter_id = dataInt;
			IMU_SetFilter(filter_id);
			break;

		case 'S':

			uint32_t length = dataInt;
			IMU_SetIIR_Length(length);
			break;

		case 'V':

			setpoint = dataFloat;

			break;

		case 'F':
			float servoCommand = dataFloat;
			setAllServos(servoCommand);
			break;

		case 'G':
			uint32_t is_regulate = dataInt;
			set_Regulate(is_regulate);
			break;

		case 'a':
			float servo_offset1 = dataFloat;
			set_offset(1, servo_offset1);
			break;

		case 'b':
			float servo_offset2 = dataFloat;
			set_offset(2, servo_offset2);
			break;

		case 'c':
			float servo_offset3 = dataFloat;
			set_offset(3, servo_offset3);

			break;

		case 'd':
			float servo_offset4 = dataFloat;
			set_offset(4, servo_offset4);
			break;
		case 'e':
			float range = dataFloat;
			update_range(range);
			break;

		default:
			break;
	}
}




