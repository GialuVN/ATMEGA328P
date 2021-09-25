/*
 * brushless.h
 *
 * Created: 10/2/2015 9:01:59 AM
 *  Author: RnD
 */ 


#ifndef BRUSHLESS_H_
#define BRUSHLESS_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/wdt.h>

#include <stdio.h>
#include <stdlib.h>


#define DDR_S	DDRC
#define PORT_S PORTC
#define PINx_S	PINC2
#define PIN_S	PINC

#define DDR_M	DDRC
#define PORT_M PORTC
#define PINx_M PINC3

#define TIMER2_COMPARE_VALUE  24  //(24+1)*2 = 50us
#define TIMER2_PRESCALER      (0 << CS22) | (1 << CS21) | (1 << CS20)

typedef struct 
{
	unsigned int counter;
	
	unsigned int low_time;
	unsigned int high_time;
	unsigned int last_low_time;
	unsigned int last_high_time;
	
	
	
	
}Brushless;


void burshless_init();

#endif /* BRUSHLESS_H_ */