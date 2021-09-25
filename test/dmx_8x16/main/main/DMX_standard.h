/*
 * DMX_standard.h
 *
 * Created: 10/13/2015 2:26:18 PM
 *  Author: RnD
 */ 


#ifndef DMX_STANDARD_H_
#define DMX_STANDARD_H_
#define TXD_PIN	PD1
#define TXD_DDR	DDRD
#define TXD_PORT PORTD

#define F_CPU 16000000// Clock Speed
#define BAUD 250000
#define MYUBRR F_CPU/16/BAUD-1
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <math.h>
#include <avr/wdt.h>

void DMX_Init( unsigned int ubrr);
void DMX_transmit(void);
void DMX_BREAK_MAB_Transmit(void);


#endif /* DMX_STANDARD_H_ */