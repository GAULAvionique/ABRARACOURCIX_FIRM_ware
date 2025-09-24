/*
 * App_Time.c
 *
 *  Created on: Feb 1, 2025
 *      Author: felix
 */





#include "App/App_Time/App_Time.h"
#include "FreeRTOS.h"
#include "task.h"

static uint32_t AppTime_TickToMS(uint32_t uTick);
static uint32_t AppTime_MsToTick(uint32_t uTimeMS);



uint32_t AppTime_GetTimeMs(void)
{
	return AppTime_TickToMS((uint32_t)xTaskGetTickCount());

}


float AppTime_GetTimeS(void)
{
	return (float)(AppTime_TickToMS((uint32_t)xTaskGetTickCount()))/1000.0f;

}

float AppTime_GetTimeS_ISR(void)
{
	return (float)(AppTime_TickToMS((uint32_t)xTaskGetTickCountFromISR()))/1000.0f;

}


void AppTime_TaskDelayMs(uint32_t uDelay)
{
	vTaskDelay(AppTime_MsToTick(uDelay));
}










static uint32_t AppTime_TickToMS(uint32_t uTick)
{
	return uTick*portTICK_PERIOD_MS;
}

static uint32_t AppTime_MsToTick(uint32_t uTimeMS)
{
	return uTimeMS/portTICK_PERIOD_MS;
}
