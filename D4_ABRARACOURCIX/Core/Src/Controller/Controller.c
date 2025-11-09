#include "../IMU/IMU.h"
#include "../Servo/Servo.h"
#include "Controller.h"


const float MAX_INTEG_ERROR = 0;
const float MAX_ANGLE = 0.098;
const float MIN_ANGLE = 0.078;
const float dt = 25;


float kp = 0.005;
float ki = 0.02;
float integralError = 0;

float angSpeedX = 0;
float angSpeedY = 0;
float angSpeedZ = 0;

float commandServo = 0;


void regulate(float setPointAngSpeed){

	IMU_GetGyro(&angSpeedX, &angSpeedY, &angSpeedZ);

	commandServo = PICompute(kp, ki, angSpeedZ, setPointAngSpeed, &integralError);
	setAllServos(commandServo);

}


float PICompute(float kp, float ki, float angSpeed, float setPointAngSpeed, float * integralError)
{
    float speedError = (setPointAngSpeed - angSpeed);
    *integralError += speedError * dt;

    // Clamp integrator
    if(*integralError >  MAX_INTEG_ERROR) *integralError =  MAX_INTEG_ERROR;
    if(*integralError < -MAX_INTEG_ERROR) *integralError = -MAX_INTEG_ERROR;

    float output = kp * speedError + ki * (*integralError);

    output = fmaxf(output, MIN_ANGLE);
    output = fminf(output, MAX_ANGLE);

    //float command  = fminf(kp * speedError + ki * (*integralError),65535);

    return output;

}




