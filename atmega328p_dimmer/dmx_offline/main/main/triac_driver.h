/*
 * triac_driver.h
 *
 * Created: 7/23/2014 8:53:22 AM
 *  Author: GIA
 */ 


#ifndef TRIAC_DRIVER_H_
#define TRIAC_DRIVER_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/wdt.h>

//SET BIT MASK
#define S_MASK_0		0B00000001
#define S_MASK_1		0B00000010
#define S_MASK_2		0B00000100
#define S_MASK_3		0B00001000
#define S_MASK_4		0B00010000
#define S_MASK_5		0B00100000
#define S_MASK_6		0B01000000
#define S_MASK_7		0B10000000

//CLEAR BIT MASK
#define C_MASK_0		0B11111110
#define C_MASK_1		0B11111101
#define C_MASK_2		0B11111011
#define C_MASK_3		0B11110111
#define C_MASK_4		0B11101111
#define C_MASK_5		0B11011111
#define C_MASK_6		0B10111111
#define C_MASK_7		0B01111111

//SET PORT MASK
#define S_MASK_PB		0b00111111
#define S_MASK_PC		0b00111111
#define S_MASK_PD		0b11110000

//CLEAR PORT MASK
#define C_MASK_PB		0b11000000
#define C_MASK_PC		0b11000000
#define C_MASK_PD		0b00001111

#define S_PD2			S_MASK_2
#define C_PD2			C_MASK_2

#define TIMER2_PRESCALER      (0 << CS22) | (1 << CS21) | (1 << CS20)
#define TIMER2_COMPARE_VALUE  99  //(99+1)*2 = 200us

#define RESOLUTION 50
#define DATA_LEN 16

#define debo	5
#define trimming 2

void dimmer_init(void);
void output_off_all();
void pin_table(uint8_t pins);
void dimmer_updata(const uint8_t *data);
#endif /* TRIAC_DRIVER_H_ */


