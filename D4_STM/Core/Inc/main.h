/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BLE_System_Key_Pin GPIO_PIN_0
#define BLE_System_Key_GPIO_Port GPIOC
#define Debug_LED_Pin GPIO_PIN_1
#define Debug_LED_GPIO_Port GPIOC
#define IMU_Interrupt_Pin GPIO_PIN_0
#define IMU_Interrupt_GPIO_Port GPIOB
#define IMU_Reset_Pin GPIO_PIN_1
#define IMU_Reset_GPIO_Port GPIOB
#define Servo_1_Pin GPIO_PIN_12
#define Servo_1_GPIO_Port GPIOD
#define Servo_2_Pin GPIO_PIN_13
#define Servo_2_GPIO_Port GPIOD
#define Servo_3_Pin GPIO_PIN_14
#define Servo_3_GPIO_Port GPIOD
#define Servo_4_Pin GPIO_PIN_15
#define Servo_4_GPIO_Port GPIOD
#define Debug_UART_TX_Pin GPIO_PIN_9
#define Debug_UART_TX_GPIO_Port GPIOA
#define Debug_UART_RX_Pin GPIO_PIN_10
#define Debug_UART_RX_GPIO_Port GPIOA
#define BLE_UART_CTS_Pin GPIO_PIN_3
#define BLE_UART_CTS_GPIO_Port GPIOD
#define BLE_UART_RTS_Pin GPIO_PIN_4
#define BLE_UART_RTS_GPIO_Port GPIOD
#define BLE_UART_TX_Pin GPIO_PIN_5
#define BLE_UART_TX_GPIO_Port GPIOD
#define BLE_UART_RX_Pin GPIO_PIN_6
#define BLE_UART_RX_GPIO_Port GPIOD
#define Buzzer_Pin GPIO_PIN_4
#define Buzzer_GPIO_Port GPIOB
#define IMU_I2C_SCL_Pin GPIO_PIN_6
#define IMU_I2C_SCL_GPIO_Port GPIOB
#define IMU_I2C_SDA_Pin GPIO_PIN_7
#define IMU_I2C_SDA_GPIO_Port GPIOB
#define IMU_Bootloader_Select_Pin GPIO_PIN_8
#define IMU_Bootloader_Select_GPIO_Port GPIOB
#define IMU_I2C_Address_Select_Pin GPIO_PIN_9
#define IMU_I2C_Address_Select_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
