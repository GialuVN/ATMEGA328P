/*
 * main.c
 *
 * Created: 6/10/2015 10:52:56 AM
 *  Author: admin
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include "twi-master.h"
#include "pwm6ch.h"
#include <avr/io.h>

unsigned char temp[10];

int main(void)
{
	
	TWI_Master_Initialise();
	_delay_ms(100);
	temp[0] = 0x10;
	DS1307_write(7,temp,1);
	_delay_ms(100);
	temp[0] = 0x00;
	DS1307_write(0,temp,1);
	
	pwm_phasecorrect_timer0_initial(clk_timer0_div64);
	pwm_phasecorrect_timer1_initial(clk_timer1_div64);
	pwm_phasecorrect_timer2_initial(clk_timer2_div64);
	
    while(1)
    {
		
		if (DS1307_read(0,temp,1))
		{
			temp[0]=Bcd2dec(temp[0])*4.25f;
			pwm_phasecorrect_6ch_updata(temp[0],temp[0],temp[0],temp[0],temp[0],temp[0]);
		}
		_delay_ms(100);
		
        //TODO:: Please write your application code 
    }
}