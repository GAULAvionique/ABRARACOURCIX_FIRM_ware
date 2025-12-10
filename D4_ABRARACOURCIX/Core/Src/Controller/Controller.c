#include "../IMU/IMU.h"
#include "../Servo/Servo.h"
#include "Controller.h"
#include "../BLE/BLE.h"
#include <string.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include <inttypes.h>
#include <math.h>

#define PROGRAMMED_GAINS_LEN 4

const float MAX_INTEG_ERROR = 40.0;
const float MIN_INTEG_ERROR = -40.0;
const float MAX_ANGLE = 100.0;
const float MIN_ANGLE = 0.0;
const float dt = 0.1;

static uint32_t is_regulating = 1;

static float speedError;
static float d_input;
static float output;
static float int_err;

static int use_updated_pid = 0;
static uint8_t motor_speed = 0.0;
static float programmed_gains_P[PROGRAMMED_GAINS_LEN] = {0.0, 0.1, 0.3, 0.4};

static float kp = 0.0003;
static float kd = 0.0000;
static float ki = 0.0001;

float integralError = 0.0;

float angSpeedX = 0.0;
float angSpeedY = 0.0;
float angSpeedZ = 0.0;

static float commandServo = 0.0;
static float last_input = 0.0f;

static float cur_set_point = 0.0;

static float scaling_factor = 1.0;

void regulate(float setPointAngSpeed){

	cur_set_point = setPointAngSpeed;

	IMU_GetGyro(&angSpeedX, &angSpeedY, &angSpeedZ);
	if(is_regulating){

		commandServo = PICompute(kp, ki, angSpeedZ, setPointAngSpeed, &integralError);
		setAllServos(commandServo);

	}

}

void Set_PID(float _kp, float _ki, float _kd)
{
    kp = _kp;
    ki = _ki;
    kd = _kd;
    use_updated_pid = 0;
}

void Set_motor_speed(uint8_t new_motor_speed){
	motor_speed = new_motor_speed;
	// SI on a pas envoyé de nouveau param, utilisé par defaut programmé
	if(!use_updated_pid){
		//programmed_gains();
	}
}

void programmed_gains(){
	int programmed_index = 0;

	if(motor_speed >= 0 && motor_speed < 15){
		programmed_index = 0;
	}
	else if(motor_speed >= 15 && motor_speed < 30){
		programmed_index = 1;
	}
	else if(motor_speed >= 30 && motor_speed < 40){
		programmed_index = 2;
	}
	else if(motor_speed >= 40 && motor_speed < 50){
		programmed_index = 3;
	}

	kp = programmed_gains_P[programmed_index];
	return;
}

void set_Regulate(uint32_t set_regulate){
	is_regulating = set_regulate;
}

void set_scaling_factor(float p_scaling_factor){
	scaling_factor = p_scaling_factor;
}

float PICompute(float kp, float ki, float angSpeed, float setPointAngSpeed, float * integralError)
{


    speedError = (setPointAngSpeed - angSpeed);
    *integralError += speedError * dt;

    // Clamp integrator
    if(*integralError >  MAX_INTEG_ERROR) *integralError =  MAX_INTEG_ERROR;
    if(*integralError < MIN_INTEG_ERROR) *integralError = MIN_INTEG_ERROR;

    d_input = (angSpeed - last_input);

    output = kp * speedError + ki * (*integralError) - kd*d_input;


    int_err = *integralError;

    output = fmaxf(output, MIN_ANGLE);
    output = fminf(output, MAX_ANGLE);

    last_input = angSpeed;

    return output * scaling_factor;
}



float get_ang_speed(){
	return angSpeedZ;
}

float get_cmd_servo(){
	return output;
}

float get_error(){
	return speedError;
}

float get_int_error(){
	return int_err;
}

float get_P(){
	return kp;
}

float get_I(){
	return ki;
}

float get_D(){
	return kd;
}

float get_setpoint(){
	return cur_set_point;
}



