/*
 * uTime.h
 *
 *  Created on: Feb 1, 2025
 *      Author: felix
 */

#ifndef SRC_UTIL_UTIME_H_
#define SRC_UTIL_UTIME_H_
#include <stdint.h>
#include "main.h"

uint32_t AppTime_GetTimeMs(void);
void AppTime_TaskDelayMs(uint32_t uDelay);
float AppTime_GetTimeS(void);
float AppTime_GetTimeS_ISR(void);

#endif /* SRC_UTIL_UTIME_H_ */
