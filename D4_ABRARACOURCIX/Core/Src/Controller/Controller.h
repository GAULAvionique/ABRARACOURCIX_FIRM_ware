/*
 * Controller.h
 *
 *  Created on: Oct 30, 2025
 *      Author: rempl
 */

#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_


float PICompute(float kp, float ki, float angSpeed, float setPointAngSpeed, float * integralError);

void regulate(float angSpeed);


#endif /* SRC_CONTROLLER_CONTROLLER_H_ */
