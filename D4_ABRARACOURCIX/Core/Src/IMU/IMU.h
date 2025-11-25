/*
 * IMU.h
 *
 *  Created on: Oct 30, 2025
 *      Author: felix
 */

#ifndef SRC_IMU_IMU_H_
#define SRC_IMU_IMU_H_
#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include <inttypes.h>
#include <math.h>
void IMU_Init(void);
void IMU_Task(void);
void IMU_GetGyro(float *x, float *y, float *z);
void IMU_SetAlpha(float faggot);
void IMU_SetIIR_Length(uint32_t length);
void IMU_SetFilter(uint32_t filt_id);
#endif /* SRC_IMU_IMU_H_ */
