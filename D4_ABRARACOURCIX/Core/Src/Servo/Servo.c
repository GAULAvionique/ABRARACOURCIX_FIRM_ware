/*
 * Servo.c
 *
 *  Created on: Oct 10, 2025
 *      Author: rempl
 */

#include "Servo.h"


static float min_range = 0.071;
static float max_range = 0.105;
static float true_mid = 0.088;

static float all_offset[4] = {0.0};
static float epsilon[4] = {0.0};
static float epsilon_intensity[] = {0.0, 0.0, 0.0, 0.0};

static float current_duty_cycle = 0.0;

static float motor_intensity = 0.0;



void setServoDuty(int servoID, float dutyCycle){
	float corrected_duty_cycle = 0.0;
	float corrected_min = 0.0;
	float corrected_max = 0.0;


	if(dutyCycle<0.0){
		dutyCycle = 0.0;
	}
	else if(dutyCycle>100.0){
		dutyCycle = 100.0;
	}

	if (servoID < 1|| servoID > 4){
		//invalid id
		return;
	}
	// duty cycle entre 0 et 100
	corrected_min = min_range + epsilon[servoID - 1] + epsilon_intensity[servoID - 1];
	corrected_max = max_range + epsilon[servoID - 1] + epsilon_intensity[servoID - 1];

	corrected_duty_cycle = corrected_min + ((dutyCycle * (corrected_max - corrected_min)) / 100.0);


	int16_t ccr = (int16_t)(corrected_duty_cycle * TIM4->ARR);

	switch(servoID){
	case 1:
		TIM4->CCR1 = ccr;
		break;

	case 2:
		TIM4->CCR2 = ccr;
		break;

	case 3:
		TIM4->CCR3 = ccr;
		break;

	case 4:
		TIM4->CCR4 = ccr;
		break
		;
	default:
	}
	return;
}


void setAllServos(float dutyCycle){
	current_duty_cycle = dutyCycle;
	setServoDuty(1, dutyCycle);
	setServoDuty(2, dutyCycle);
	setServoDuty(3, dutyCycle);
	setServoDuty(4, dutyCycle);
}

void setServosSep(float dutyCycle1, float dutyCycle2, float dutyCycle3, float dutyCycle4){
	  setServoDuty(1, dutyCycle1);
	  setServoDuty(2, dutyCycle2);
	  setServoDuty(3, dutyCycle3);
	  setServoDuty(4, dutyCycle4);
}



void set_offset(uint8_t servo_id, float offset){

	switch(servo_id){
	case 1:
		all_offset[0] = offset;
		epsilon[0] = all_offset[0] - true_mid;
		break;

	case 2:
		all_offset[1] = offset;
		epsilon[1] = all_offset[1] - true_mid;
		break;

	case 3:
		all_offset[2] = offset;
		epsilon[2] = all_offset[2] - true_mid;
		break;

	case 4:
		all_offset[3] = offset;
		epsilon[3] = all_offset[3] - true_mid;
		break
		;
	default:

	}
	setAllServos(50.0);
}

void set_min_range(float p_min_range){
	min_range = p_min_range;
	update_mid_point();
}

void set_max_range(float p_max_range){
	max_range = p_max_range;
	update_mid_point();
}

// map intensité -> % range
// assume des coefficients PID fixes

//

void update_range(float p_range){
	p_range = p_range / 100.0;
	float half_range = p_range / 2.0;
	min_range = true_mid - half_range;
	max_range = true_mid + half_range;
	update_mid_point();

}

void update_mid_point(){
	true_mid = min_range + ((max_range - min_range) / 2.0);
	init_offset();
}


void init_offset(){
	set_offset(1, 0.091);
	set_offset(2, 0.085);
	set_offset(3, 0.085);
	set_offset(4, 0.086);
}

float get_duty_cycle(){
	return current_duty_cycle;
}


float compute_corrected_duty(uint8_t servo_id, float duty){
	// duty cycle entre 0 et 100
	float corrected_duty_cycle = 0.0;
	float corrected_min = 0.0;
	float corrected_max = 0.0;
	corrected_min = min_range + epsilon[servo_id - 1];
	corrected_max = max_range + epsilon[servo_id - 1];

	corrected_duty_cycle = corrected_min + ((duty * (corrected_max - corrected_min)) / 100.0);
	return corrected_duty_cycle;
}

float compute_intensity_to_duty(float intensity){
	float mapped_servo_command = 0.0;
	mapped_servo_command = (0.26429 * intensity) +39.04;
	// s'assure que la commande peut pas aller au delà de 50. (le drone accelererait)
	if (mapped_servo_command > 50.0){
		mapped_servo_command = 50.0;
	}
	return mapped_servo_command;
}



void set_motor_intensity(float intensity){
	float center_duty = 0.0;

	float null_speed_duty_cycle1 = 0.0;
	float null_speed_duty_cycle2 = 0.0;
	float null_speed_duty_cycle3 = 0.0;
	float null_speed_duty_cycle4 = 0.0;

	motor_intensity = intensity;

	// center duty serait la commande à envoyer pour stabiliser le drone
	center_duty = compute_intensity_to_duty(motor_intensity); // F0-100

	// La commande pour chaque servo pour le drone bouge pu.
	null_speed_duty_cycle1 = compute_corrected_duty(1, center_duty);
	null_speed_duty_cycle2 = compute_corrected_duty(2, center_duty);
	null_speed_duty_cycle3 = compute_corrected_duty(3, center_duty);
	null_speed_duty_cycle4 = compute_corrected_duty(4, center_duty);

	// l'Erreur entre mon centre plat et mon centre que drone bouge pu
	epsilon_intensity[0] = null_speed_duty_cycle1 - (true_mid + epsilon[0]);
	epsilon_intensity[1] = null_speed_duty_cycle2 - (true_mid + epsilon[1]);
	epsilon_intensity[2] = null_speed_duty_cycle3 - (true_mid + epsilon[2]);
	epsilon_intensity[3] = null_speed_duty_cycle4 - (true_mid + epsilon[3]);


	/*
	set_offset(1, compute_corrected_duty(1, center_duty));
	set_offset(2, compute_corrected_duty(2, center_duty));
	set_offset(3, compute_corrected_duty(3, center_duty));
	set_offset(4, compute_corrected_duty(4, center_duty));
	*/

}

