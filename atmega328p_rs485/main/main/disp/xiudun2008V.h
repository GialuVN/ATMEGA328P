/*
 * xiudun2008V.h
 *
 * Created: 6/15/2015 1:17:57 PM
 *  Author: admin
 */ 


#ifndef XIUDUN2008V_H_
#define XIUDUN2008V_H_
#include "hc595.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#define s11 0
#define s12 1
#define s13 2
#define s14 3
#define s21 4
#define s22 5
#define s23 6
#define s24 7
#define l61 8
#define l62 9

typedef struct SEG7_DATA
{
	unsigned char seg11;
	unsigned char seg12;
	unsigned char seg13;
	unsigned char seg14;
	unsigned char seg21;
	unsigned char seg22;
	unsigned char seg23;
	unsigned char seg24;
	unsigned char leds_61;
	unsigned char leds_62;
}SEG7_DATA;


typedef struct SEG7_CTR
{
	unsigned char seg7_stage;
	unsigned char seg7_counter;
}SEG7_CTR;

void SEG7_initial(void);
void SEG7_scan(void);
void SEG7_send(unsigned char mux,unsigned val);
void SEG7_updata(unsigned char select,unsigned val);
void SEG7_disp_uint(unsigned int sg1,unsigned int sg2);
void HEX2BCD_uint(unsigned int val,unsigned char* bcd);
#endif /* XIUDUN2008V_H_ */