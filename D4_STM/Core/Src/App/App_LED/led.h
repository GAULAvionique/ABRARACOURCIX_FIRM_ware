/*
 * led.h
 *
 *  Created on: Feb 1, 2025
 *      Author: felix
 */

#ifndef SRC_LED_LED_H_
#define SRC_LED_LED_H_

typedef enum{

	OFF = 0,
	ON,
}eLedState;

void LED_GreenSetState(eLedState eState);
void LED_RedSetState(eLedState eState);

#endif /* SRC_LED_LED_H_ */
