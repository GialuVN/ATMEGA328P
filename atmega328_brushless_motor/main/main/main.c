/*
 * main.c
 *
 * Created: 9/30/2015 2:32:07 PM
 *  Author: RnD
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "brushless.h"

int main(void)
{
	burshless_init();
	
    while(1)
    {
		
	}
}