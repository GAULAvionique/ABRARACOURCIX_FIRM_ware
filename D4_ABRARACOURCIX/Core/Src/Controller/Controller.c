#include "IMU/IMU.h"
#include "Servo/Servo.h"




const float MAX_INTEG_ERROR = 0;
const float MAX_ANGLE = 0.098;
const float MIN_ANGLE = 0.078;
const float dt = 100;

float integralError = 0;



float angSpeedX = 0;
float angSpeedY = 0;
float angSpeedZ = 0;


void regulate(float angSpeed){

	IMU_GetGyro(&angSpeedX, &angSpeedY, &angSpeedZ);



}


float PICompute(float kp, float ki, float angSpeed, float setPointAngSpeed, float * integralError)
{
    float speedError = (setPointAngSpeed - angSpeed);
    *integralError += speedError * dt;

    // Clamp integrator
    if(*integralError >  MAX_INTEG_ERROR) *integralError =  MAX_INTEG_ERROR;
    if(*integralError < -MAX_INTEG_ERROR) *integralError = -MAX_INTEG_ERROR;

    float cartTerm  = fminf(kp * speedError + ki * (*integralError),65535);

    return cartTerm;

}




