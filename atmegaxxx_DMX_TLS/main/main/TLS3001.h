/*
 * TLS3001.h
 *
 * Created: 10/30/2015 1:48:05 PM
 *  Author: RnD
 */ 


#ifndef TLS3001_H_
#define TLS3001_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define nop() asm volatile ("nop")
#define  DDR	DDRD
#define  POR	PORTD
#define  PIN	PORTD1
#define _LOW_	~(1<<PIN)
#define _HIG_	(1<<PIN)

void TLS3001_Initial(void);
void TLS3001_Send_Sys(void);
void TLS3001_Send_Reset(void);
void TLS3001_Send_Head(void);
void TLS3001_Send_Bits(unsigned long _long,unsigned char _n);
void TLS3001_Send_RGB(unsigned int _R, unsigned int _G,unsigned int _B);
void TLS3001_Send_RGB_8(unsigned char _R, unsigned char _G,unsigned char _B);
void TLS3001_pull(bool val);



#endif /* TLS3001_H_ */