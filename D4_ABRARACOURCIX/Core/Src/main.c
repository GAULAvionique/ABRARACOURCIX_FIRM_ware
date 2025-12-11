/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BLE/BLE.h"
#include "Servo/Servo.h"
#include "IMU/IMU.h"
#include "Controller/Controller.h"
#include "BLE/BLE_Commands.h"
#include "BLE/BLE_tx.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
float setpoint = 0;

// FONCTION APPELÉE À TOUS LES 25 MS.


// FONCTION POUR LIRE ADC
static uint32_t current = 0;
static uint32_t battery = 0;
uint32_t adcBuffer[2];
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if (hadc->Instance == ADC1) {
			current = adcBuffer[0];
			battery = adcBuffer[1];
	    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adcBuffer, 2);
	}
}
float get_bat_current()
{
	//        tension lue par ADC * ratio de résistances * ratio de l'ADC
float	current_conv = (float)current * 3.0 / 2.0 * 3.3 / 4096.0;
	return (current_conv - 2.5)*10.0;
}


float get_bat_voltage()
{
	//return 100.0 * (float)battery / 4096.0;

	//tension lue par l'ADC sur 4096 * ratio de l'ADC 12 bits
float	battery_conv = (float)battery * 3.3 / 4096.0;
// 3 = gain ampli diff - référence de tension / diviseur de tension
	return  ((battery_conv/3.0)+2.46)/0.2;
}

// FONCTION POUR METTRE À JOUR LE DISPLAY DATA

static int angular_speed = 0.0;
static float bat_current = 0.0;
static float current_set_point = 0.0;
static float bat_voltage = 0.0;
static float error = 0.0;
static float int_error = 0.0;
static float P = 0.0;
static float I = 0.0;
static float D = 0.0;
static int time_tick = 0;
static float m_duty_cycle = 0.0;


void update_disp_variables(){
	angular_speed = get_ang_speed();
	current_set_point = get_setpoint();
	error = get_error();
	int_error = get_int_error();
	P = get_P();
	I = get_I();
	D = get_D();
	time_tick = HAL_GetTick();
	bat_current = get_bat_current();
	bat_voltage = get_bat_voltage();
	m_duty_cycle = get_duty_cycle();
}

void disp_variables(){

	send_float_package('S', angular_speed);
	send_float_package('K', current_set_point);
	send_float_package('A', bat_current);
	send_uint32_t_package('T', time_tick);
	send_float_package('B', bat_voltage);
	send_float_package('E', error);
	send_float_package('N', int_error);
	send_float_package('P', P);
	send_float_package('I', I);
	send_float_package('D', D);
	send_float_package('L', m_duty_cycle);

}

static uint32_t counter = 0;
static int ready_to_send = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if(htim->Instance == TIM5)
    {
    	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_1);
    	regulate(setpoint);
    	if(counter == 10)
    	{
    		ready_to_send = 1;
    		counter = 0;
    	}
    	counter++;


    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM5_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
  HAL_TIM_Base_Start_IT(&htim5);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adcBuffer, 2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  IMU_Init();
  BLE_Init();
  init_offset();

  uint8_t uartData = 0;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(BLE_ReadData(&uartData)){
		  BLE_ParseCommand(&uartData);
	  }

	  IMU_Task();

	  //if(HAL_GetTick() - start_time >= delta_time){
	  if(ready_to_send){
		  update_disp_variables();
		  disp_variables();

		  ready_to_send = 0;

	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
