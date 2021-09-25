/*
 * pt2260_dec.h
 *
 * Created: 6/10/2015 2:19:56 PM
 *  Author: admin
 */ 

#ifndef PT2260_DEC_H_
#define PT2260_DEC_H_



#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//port define
#define DDR_RF DDRB
#define POR_RF PORTB
#define PIN_RF PINB
#define IN_RF  PINB0

//timming
#define rf_30a 12600	//us
#define rf_1a	420		//us
#define rf_3a	1260	//us
#define rf_data_len 12	//bits
//api

typedef struct RF_DECODE	// rf_decode
{
	unsigned char  rf_data;
	unsigned char	rf_id;
}RF_DECODE;

void RF_decode_initial(unsigned char id);
void RF_decode_stop();
void RF_decode_start();
unsigned char  RF_decode_read();

#endif /* PT2260_DEC_H_ */