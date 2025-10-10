/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tim.h"
#include "stm32f4xx_hal_i2c.h"
#include "i2c.h"
#include "CLI.h"
#include <stdio.h>
#include <string.h>
#include "App/App_Time/App_Time.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t i2c_done = 0;
uint32_t uTime1 = 0;
uint32_t delta = 0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 2400 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for xCLI */
osThreadId_t xCLIHandle;
const osThreadAttr_t xCLI_attributes = {
  .name = "xCLI",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void CLI(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of xCLI */
  xCLIHandle = osThreadNew(CLI, NULL, &xCLI_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	static char CLI_BUFF[100] = {0};
	CtrlServo_Init();
	uint8_t RX_Buffer[100] = {};
	uint8_t reg_config[] = {0x3D, 0x00} ;
	HAL_I2C_Master_Transmit_DMA(&hi2c1 , 0x28 << 1, reg_config, 2);
	HAL_Delay(1000);
	uint8_t reg_config_fu[] = {0x3D, 0x0C} ;
	HAL_I2C_Master_Transmit_DMA(&hi2c1 , 0x28 << 1, reg_config_fu, 2);
	HAL_Delay(1000);
	//ID
	uint8_t reg_D = 0x00;
	HAL_I2C_Master_Transmit_DMA(&hi2c1 , 0x28 << 1, &reg_D, 1);

    HAL_I2C_Master_Receive_DMA(&hi2c1 , 0x28 << 1, (uint8_t *)RX_Buffer, 1); //Receiving in DMA mode
    HAL_Delay(1000);
	uint8_t reg_gyro = 0x20;
	HAL_I2C_Master_Transmit_DMA(&hi2c1 , 0x28 << 1, &reg_gyro, 1);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);


  /* Infinite loop */
  for(;;)
  {
	  /* USER CODE BEGIN 2 */
	HAL_Delay(8);


	uTime1 = AppTime_GetTimeMs();
	HAL_I2C_Master_Receive_DMA(&hi2c1 , 0x28 << 1, (uint8_t *)RX_Buffer, 20);
	//Receiving in DMA mode
	while(!i2c_done);
	i2c_done = 0;
	int16_t w = (int16_t)((RX_Buffer[1] << 8) | RX_Buffer[0]);
    int16_t x = (int16_t)((RX_Buffer[3] << 8) | RX_Buffer[2]);
    int16_t y = (int16_t)((RX_Buffer[5] << 8) | RX_Buffer[4]);
    int16_t z = (int16_t)((RX_Buffer[7] << 8) | RX_Buffer[6]);
    float gyro_w_dps = (float)w / 16384.0;  // °/s
    float gyro_x_dps = (float)x / 16384.0;  // °/s
    float gyro_y_dps = (float)y / 16384.0;
    float gyro_z_dps = (float)z / 16384.0;

    uint16_t uSize = snprintf(CLI_BUFF,sizeof(CLI_BUFF), "%.2f; %.2f; %.2f; %.2f;\r\n", gyro_w_dps, gyro_x_dps, gyro_y_dps, gyro_z_dps);
    CLI_Send((uint8_t*)CLI_BUFF, uSize);
	  /* USER CODE END 2 */

  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_CLI */
/**
* @brief Function implementing the xCLI thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CLI */
void CLI(void *argument)
{
  /* USER CODE BEGIN CLI */
  /* Infinite loop */
	CLI_Init();
	CLICmd_RegisterCMD();

	vCLI_Task();
  /* USER CODE END CLI */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        i2c_done = 1; // RX finished
        delta = AppTime_GetTimeMs();
        delta = delta - uTime1;
    }}
/* USER CODE END Application */

