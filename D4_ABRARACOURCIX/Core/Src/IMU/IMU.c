





#include "IMU.h"
#include <stdint.h>
#include "stm32f4xx.h"
#include <stdlib.h>
#include "tim.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"
#include "i2c.h"

#define FILTER_MOVING_AVG 	(1)
#define FILTER_IIR_LOWPASS 	(2)
#define SIZE_WINDOW 	(10)

float alpha = 0.25;
float filter_length = 20;
uint32_t filter_id = FILTER_MOVING_AVG;

float moving_avg_data[SIZE_WINDOW] = {0.0f};

float moving_avg_sum = 0.0f;
uint8_t moving_avg_index = 0;

static char CLI_BUFF[100] = {0};

static float gyro_x = 0.0f;
static float gyro_y = 0.0f;
static float gyro_z = 0.0f;

uint8_t i2c_done = 0;



static void IMU_Filter(float x, float y, float z);

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
	//HAL_Delay(10);

	HAL_I2C_Master_Receive_DMA(&hi2c1 , 0x28 << 1, (uint8_t *)RX_Buffer, 8);

	while(!i2c_done);
	i2c_done = 0;
    int16_t x = (int16_t)((RX_Buffer[1] << 8) | RX_Buffer[0]);
    int16_t y = (int16_t)((RX_Buffer[3] << 8) | RX_Buffer[2]);
    int16_t z = (int16_t)((RX_Buffer[5] << 8) | RX_Buffer[4]);
    float gyro_x_new = (float)x / 16.0f;
    float gyro_y_new = (float)y / 16.0f;
    float gyro_z_new = (float)z / 16.0f;

	IMU_Filter(gyro_x_new,gyro_y_new ,gyro_z_new);


	  /* USER CODE END 2 */
}

static void IMU_Filter(float x, float y, float z)
{
	if (filter_id == FILTER_IIR_LOWPASS)
	{
	
		gyro_z = alpha * z + (1-alpha) * gyro_z;
	}
	else if (filter_id == FILTER_MOVING_AVG)
	{
		moving_avg_sum += z;
		moving_avg_sum -= moving_avg_data[moving_avg_index];
		moving_avg_data[moving_avg_index++] = z;

		moving_avg_index = (moving_avg_index == (SIZE_WINDOW))?(0):(moving_avg_index);
		gyro_z = moving_avg_sum/SIZE_WINDOW;
	}
	else
	{
		gyro_z = z;
	}

	gyro_x = x;
	gyro_y = y;
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

void IMU_SetAlpha(float p_alpha)
{
	alpha = p_alpha;
}

void IMU_SetIIR_Length(uint32_t p_length)
{
	filter_length = p_length;
}

void IMU_SetFilter(uint32_t filt_id)
{
	filter_id = filt_id;
}

uint32_t get_filter_type(){
	return filter_id;
}
