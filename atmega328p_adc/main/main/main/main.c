/*
 * main.c
 *
 * Created: 6/8/2015 10:06:53 AM
 *  Author: admin
 */ 


#define F_CPU 16000000UL
#include <util/delay.h>
#include "adc_megax8.h"
#include "pwm6ch.h"
#include <avr/io.h>

int main(void)
{
	
	pwm_phasecorrect_timer0_initial(clk_timer0_div64);
	pwm_phasecorrect_timer1_initial(clk_timer1_div64);
	pwm_phasecorrect_timer2_initial(clk_timer2_div64);
	
	
	
	ADC_initial(0x01,ADC_div128,ADC_REF_1V1);
	ADC_start();
	sei();
    while(1)
    {
		pwm_phasecorrect_6ch_updata(ADC_read(ADC0)/4,ADC_read(ADC1)/4,ADC_read(ADC2)/4,ADC_read(ADC3)/4,0,0);
		_delay_ms(10);
		
        //TODO:: Please write your application code 
    }
}