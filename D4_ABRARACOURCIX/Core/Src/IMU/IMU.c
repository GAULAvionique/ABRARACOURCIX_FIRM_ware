





#include "IMU.h"
#include <stdint.h>
#include "stm32f4xx.h"
#include "tim.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "i2c.h"

static char CLI_BUFF[100] = {0};

static float gyro_x = 0.0f;
static float gyro_y = 0.0f;
static float gyro_z = 0.0f;

uint8_t i2c_done = 0;

void IMU_Init(void)
{

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

    HAL_I2C_Master_Receive_DMA(&hi2c1 , 0x28 << 1, (uint8_t *)RX_Buffer, 1);
    HAL_Delay(1000);
	uint8_t reg_gyro = 0x14;
	HAL_I2C_Master_Transmit_DMA(&hi2c1 , 0x28 << 1, &reg_gyro, 1);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
}

void IMU_Task(void)
{
	uint8_t RX_Buffer[100] = {};
	HAL_Delay(10);

	HAL_I2C_Master_Receive_DMA(&hi2c1 , 0x28 << 1, (uint8_t *)RX_Buffer, 8);

	while(!i2c_done);
	i2c_done = 0;
    int16_t x = (int16_t)((RX_Buffer[1] << 8) | RX_Buffer[0]);
    int16_t y = (int16_t)((RX_Buffer[3] << 8) | RX_Buffer[2]);
    int16_t z = (int16_t)((RX_Buffer[5] << 8) | RX_Buffer[4]);
    gyro_x = (float)x / 16.0f;
    gyro_y = (float)y / 16.0f;
    gyro_z = (float)z / 16.0f;

	  /* USER CODE END 2 */
}



void IMU_GetGyro(float *x, float *y, float *z)
{
	*x = gyro_x;
	*y = gyro_y;
	*z = gyro_z;
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1) {
        i2c_done = 1; // RX finished
    }
}
