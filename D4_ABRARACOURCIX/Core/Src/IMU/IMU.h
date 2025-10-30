/*
 * IMU.h
 *
 *  Created on: Oct 30, 2025
 *      Author: felix
 */

#ifndef SRC_IMU_IMU_H_
#define SRC_IMU_IMU_H_

void IMU_Init(void);
void IMU_Task(void);
void IMU_GetGyro(float *x, float *y, float *z);

#endif /* SRC_IMU_IMU_H_ */
