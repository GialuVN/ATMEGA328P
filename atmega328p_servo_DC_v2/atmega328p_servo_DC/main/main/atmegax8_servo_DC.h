/*
 * atmegax8_servo_DC.h
 *
 * Created: 6/16/2015 9:33:21 AM
 *  Author: admin
 */ 


#ifndef ATMEGAX8_SERVO_DC_H_
#define ATMEGAX8_SERVO_DC_H_
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <math.h>
#include "pwm/pwm6ch.h"


#define PH1_PIN PINC4		//PHASE 1
#define PH1_POR PORTC
#define PH1_DDR DDRC
#define PH1_IN PINC

#define PH2_PIN PINC5		//PHASE 2
#define PH2_POR PORTC
#define PH2_DDR DDRC
#define PH2_IN PINC

#define DIR_PIN PINB4		//DIR
#define DIR_POR PORTB
#define DIR_DDR DDRB

#define PWM_PIN PINB2		//PWM
#define PWM_POR PORTB	
#define PWM_DDR DDRB


#define LEFT	0
#define RIGHT	1

#define SERVO_MAX_RANGE	2
#define SERVO_IN_RANGE	1
#define SERVO_MIN_RANGE	0
#define SERVO_MAX_POSITION (unsigned long)4000000000
#define SERVO_THRESHOLD 1000
#define SERVO_MAX_FORCE	1023
#define SERVO_MAX_SPEED	150
//#define SERVO_KP_RANGE	1000

//PID define


typedef enum DIR
{
	TURN_LEFT,
	TURN_RIGHT
}DIR;


#define KI_POS_MIN 50

typedef struct SERVO_PID
{
	
	double servo_pos_i;
	unsigned int servo_speed_i;
	
	
}SERVO_PID;


typedef struct SERVO_INPUT
{
	unsigned char servo_input_dir;//input
	unsigned int servo_input_speed; //input
	unsigned long servo_input_pos;  //input
	unsigned int servo_force;//input
}SERVO_INPUT;


typedef struct SERVO_CTR
{
	unsigned char servo_range_check;
	unsigned char servo_sample_counter;
	unsigned char servo_sample_rate;	//2ms*(servo_sample_rate+1)
	
	unsigned char servo_pre_dir;
	unsigned char servo_dir;		//return
	
	int servo_accelerator;			//return
	
	unsigned int servo_speed_sample;
	unsigned int servo_pre_speed;
	unsigned int servo_speed;		//return
	
	unsigned long servo_pre_position;
	unsigned long servo_position;   //return
	
}SERVO_CTR;



void SERVO_DC_initial();
void SERVO_FORCE(int _val);
void SERVO_DIR(DIR _dir);
void SERVO_default(void);
void SERVO_POS_PID(int kp,int ki,int kd);
#endif /* ATMEGAX8_SERVO_DC_H_ */