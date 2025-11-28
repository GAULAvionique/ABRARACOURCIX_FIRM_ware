#include "../IMU/IMU.h"
#include "../Servo/Servo.h"
#include "Controller.h"
#include "../BLE/BLE.h"
#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include <inttypes.h>
#include <math.h>

const float MAX_INTEG_ERROR = 0.04;
const float MAX_ANGLE = 0.105;
const float MIN_ANGLE = 0.071;
const float dt = 0.025;


//float kp = 0.0003;
float kp = 0.0003;
float kd = 0.0003;
//float ki = 0.005;

//float ki = 0.0005;
//float ki = 0.00005;
float ki = 0.0001;
float integralError = 0;

float angSpeedX = 0;
float angSpeedY = 0;
float angSpeedZ = 0;

float commandServo = 0;
float last_input = 0.0f;

char string_fix[200] ={0};
uint8_t cx = 0;
uint32_t prev_tick = 0;
int32_t print_angspeed = 0;
void regulate(float setPointAngSpeed){

	IMU_GetGyro(&angSpeedX, &angSpeedY, &angSpeedZ);

	commandServo = PICompute(kp, ki, angSpeedZ, setPointAngSpeed, &integralError);
	setAllServos(commandServo);

}

void Set_PID(float _kp, float _ki, float _kd)
{
    kp = _kp;
    ki = _ki;
    kd = _kd;
}

float PICompute(float kp, float ki, float angSpeed, float setPointAngSpeed, float * integralError)
{
//	if (fabsf(angSpeed) < 5.0f) angSpeed = 0;
    float speedError = (setPointAngSpeed - angSpeed);
    *integralError += speedError * dt;




    // Clamp integrator
    if(*integralError >  MAX_INTEG_ERROR) *integralError =  MAX_INTEG_ERROR;
    if(*integralError < -MAX_INTEG_ERROR) *integralError = -MAX_INTEG_ERROR;

    float d_input = (angSpeed - last_input);

    //BLE_SendData((uint8_t*)string_fix, cx);

//  BLE_SendData((uint8_t*)string_fix, sizeof(string_fix));
    float output = kp * speedError + ki * (*integralError) - kd*d_input;

    output = 0.088 + output;
    float int_err = *integralError;
    output = fmaxf(output, MIN_ANGLE);
    output = fminf(output, MAX_ANGLE);

    uint32_t tick = HAL_GetTick();

    cx = snprintf(string_fix, sizeof(string_fix), "%f;%f;%f;%f;%f;%"PRIu32";\n\r",
    		angSpeed, setPointAngSpeed, speedError, int_err, output, tick);

    last_input = angSpeed;
    //float command  = fminf(kp * speedError + ki * (*integralError),65535);

    return output;

}




