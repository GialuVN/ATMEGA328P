/*
 * PWM.h
 *
 * Created: 1/7/2015 10:42:13 AM
 *  Author: GIA
 */ 


#ifndef PWM_H_
#define PWM_H_

#define F_CPU 16000000UL// Clock Speed
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/wdt.h>

#define DATA_LEN 6
#define RESOLUTION 255
#define TIMER2_COMPARE_VALUE  10  //179hz

#define TIMER2_PRESCALER      (0 << CS22) | (1 << CS21) | (1 << CS20)
//SET BIT MASK
#define S_MASK_0		0B00000001
#define S_MASK_1		0B00000010
#define S_MASK_2		0B00000100
#define S_MASK_3		0B00001000
#define S_MASK_4		0B00010000
#define S_MASK_5		0B00100000
#define S_MASK_6		0B01000000
#define S_MASK_7		0B10000000

//SET PORT MASK
#define S_MASK_PB		0b00001110
#define S_MASK_PC		0b00000000
#define S_MASK_PD		0b01101000

//CLEAR BIT MASK
#define C_MASK_0		0b11111110
#define C_MASK_1		0b11111101
#define C_MASK_2		0b11111011
#define C_MASK_3		0b11110111
#define C_MASK_4		0b11101111
#define C_MASK_5		0b11011111
#define C_MASK_6		0b10111111
#define C_MASK_7		0b01111111

//CLEAR PORT MASK
#define C_MASK_PB		0b11110001
#define C_MASK_PC		0b11111111
#define C_MASK_PD		0b10010111

#define S_PD2			S_MASK_2
#define C_PD2			C_MASK_2

void PWM_initial(void);
void PWM_updata(unsigned char *_data);
void map_maker(unsigned _mux);
void output_init();
void output_off_all();
void pin_table(uint8_t pins);
void timer2_CTC_init();

#endif /* PWM_H_ */

