/*
 * main.c
 *
 * Created: 6/15/2015 1:16:25 PM
 *  Author: admin
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "hc595.h"
#include "xiudun2008V.h"
int main(void)
{
	hc595_set_spi();
	SEG7_initial();
	sei();
	
	SEG7_disp_uint(84,79);
	
	//SEG7_updata(s11,0b11111110);
	//SEG7_updata(s12,0b11111100);
	//SEG7_updata(s13,0b11111000);
	//SEG7_updata(s14,0b11110000);
	
	//SEG7_updata(s21,0b11111110);
	//SEG7_updata(s22,0b11111100);
	//SEG7_updata(s23,0b11111000);
	//SEG7_updata(s24,0b11110000);
	//
	SEG7_updata(l61,0b00000000);
	SEG7_updata(l62,0b00000000);
	
    while(1)
    {
	
	
	
    }
}