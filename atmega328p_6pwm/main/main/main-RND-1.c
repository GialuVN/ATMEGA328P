/*
 * main.c
 *
 * Created: 6/4/2015 8:28:04 AM
 *  Author: admin
 */ 


#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "pwm6ch.h"
int main(void)
{
	
	pwm_phasecorrect_timer0_initial(clk_timer0_div64);
//	pwm_phasecorrect_timer1_initial(clk_timer1_div64);
	pwm_phasecorrect_timer2_initial(clk_timer2_div64);
	
	pwm_servo_timer1_initial();
	pwm_servo_timer1_OCR1A_updata(1000);
	//pwm_servo_timer1_OCR1B_updata(1000);
	pwm_phasecorrect_4ch_updata(100,200,50,10);
	
    while(1)
    {
		
		_delay_ms(2000);
		pwm_servo_timer1_OCR1B_updata(700);
		_delay_ms(2000);
		pwm_servo_timer1_OCR1B_updata(2400);
		
        //TODO:: Please write your application code 
    }
}

