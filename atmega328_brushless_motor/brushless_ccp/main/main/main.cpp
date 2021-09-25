/*
 * main.cpp
 *
 * Created: 10/3/2015 2:41:19 PM
 * Author : RnD
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "brushless.h"
#include "adc_megax8.h"
int main(void)
{
	burshless_init();
	ADC_initial(0b00000010,ADC_div128,ADC_REF_VCC);
	ADC_start();
	
	while(1)
	{
		speed_update(ADC_read(1)*5);
		_delay_ms(1000);
	}
}