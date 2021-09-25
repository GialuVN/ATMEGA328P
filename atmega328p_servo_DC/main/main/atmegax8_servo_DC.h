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


typedef struct SERVO_DC
{
	unsigned int servo_force;
	unsigned char servo_dir;
}SERVO_DC;



typedef struct SERVO_PID_POSITION
{
	unsigned int	servo_kp;
	unsigned int	servo_ki;
	unsigned int	servo_kd;
	unsigned long	servo_position;
	double	servo_integral;
	unsigned char dir;
}SERVO_PID_POSITION;


typedef struct SERVO_PID_SPEED
{
	unsigned int	servo_kp;
	unsigned int	servo_ki;
	unsigned int	servo_kd;
	unsigned int	servo_speed;
	 unsigned int	servo_integral;
	unsigned char dir;
}SERVO_PID_SPEED;


typedef struct SERVO_CTR
{
	unsigned char servo_range_check;
	
	unsigned char servo_sample_counter;
	unsigned char servo_sample_rate;	//2ms*(servo_sample_rate+1)
	
	unsigned char servo_pre_dir;
	unsigned char servo_dir;
	
	unsigned int servo_speed_sample;
	unsigned  int servo_pre_speed;
	unsigned  int servo_speed;
	
	 int servo_accelerator;
	 
	unsigned long servo_pre_position;
	unsigned long servo_position;
	
	unsigned int servo_force;
	
}SERVO_CTR;


void SERVO_DC_initial();
void SERVO_CTR_initial();
void SERVO_DC_dir(unsigned char _dir);
void SERVO_DC_force(unsigned int _val);
void SERVO_DC_DRIVER(SERVO_DC _val);
SERVO_DC SERVO_DC_PID_SPEED(unsigned int KP,unsigned int KI,unsigned int KD,unsigned int SPEED,unsigned char DIR);
void SERVO_DC_PID_SPEED_UPDATA(unsigned int KP,unsigned int KI,unsigned int KD,unsigned int SPEED,unsigned char DIR);
//void SERVO_DC_PID_POSITION_UPDATA(unsigned int KP,unsigned int KI,unsigned int KD,unsigned long POSITION);
//SERVO_DC SERVO_DC_PID_POSITION(unsigned int KP,unsigned int KI,unsigned int KD,unsigned long POSITION);
#endif /* ATMEGAX8_SERVO_DC_H_ */