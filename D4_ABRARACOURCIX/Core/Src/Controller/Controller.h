/*
 * Controller.h
 *
 *  Created on: Oct 30, 2025
 *      Author: rempl
 */

#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

void regulate(float setPointAngSpeed);
float PICompute(float kp, float ki, float angSpeed, float setPointAngSpeed, float * integralError);
void Set_PID(float _kp, float _ki, float _kd);




#endif /* SRC_CONTROLLER_CONTROLLER_H_ */
