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

#include "DMX_sender_config.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <math.h>
#include <avr/wdt.h>

void DMX_Init( unsigned int ubrr);
void DMX_start_transmit(uint8_t _MODE);
void DMX_transmit(uint8_t _MODE);
void DMX_transmit_setting(uint8_t _MODE,uint8_t *data,uint8_t len);
bool DMX_Is_Ready(void);
void DMX_BREAK_MAB_Transmit(void);


#endif /* DMX_STANDARD_H_ */