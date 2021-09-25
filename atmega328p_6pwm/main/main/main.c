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
void rotal(unsigned char _ch1,unsigned char _ch2,unsigned char _ch3,unsigned char _ch4,unsigned int _speed,unsigned int _loop,bool _dir);

unsigned char val[4];

int main(void)
{
	
	pwm_phasecorrect_timer0_initial(clk_timer0_div64);
	pwm_phasecorrect_timer1_initial(clk_timer1_div64);
	pwm_phasecorrect_timer2_initial(clk_timer2_div64);
	
	pwm_phasecorrect_6ch_updata(1,15,31,63,127,255);
	
	
	
    while(1)
    {
		rotal(5,50,100,255,10,100,0);
		rotal(255,100,50,5,10,100,1);
		//pwm_phasecorrect_6ch_updata(255,0,0,0,0,0);
		//_delay_ms(50);
		//pwm_phasecorrect_6ch_updata(127,255,0,0,0,0);
		//_delay_ms(50);
		//pwm_phasecorrect_6ch_updata(63,127,255,0,0,0);
		//_delay_ms(50);
		//pwm_phasecorrect_6ch_updata(31,63,127,255,0,0);
		//_delay_ms(50);
		//pwm_phasecorrect_6ch_updata(15,31,63,127,255,0);
		//_delay_ms(50);
		//pwm_phasecorrect_6ch_updata(1,15,31,63,127,255);
		//_delay_ms(50);
		//pwm_phasecorrect_6ch_updata(0,1,15,31,63,127);
		//_delay_ms(50);
		//pwm_phasecorrect_6ch_updata(0,0,1,15,31,63);
		//_delay_ms(50);
		//pwm_phasecorrect_6ch_updata(0,0,0,1,15,31);
		//_delay_ms(50);
		//pwm_phasecorrect_6ch_updata(0,0,0,0,1,15);
		//_delay_ms(50);
		//pwm_phasecorrect_6ch_updata(0,0,0,0,0,1);
		//_delay_ms(50);
		//pwm_phasecorrect_6ch_updata(0,0,0,0,0,0);
		//_delay_ms(50);
		
		
		
        //TODO:: Please write your application code 
    }
}


void rotal(unsigned char _ch1,unsigned char _ch2,unsigned char _ch3,unsigned char _ch4,unsigned int _speed,unsigned int _loop,bool _dir)
{
	unsigned char _val[4];
	unsigned char _temp;
	_val[0] = _ch1;
	_val[1] = _ch2;
	_val[2] = _ch3;
	_val[3] = _ch4;
	if (_dir)
	{
		for (unsigned int i = 0; i < _loop; i++)
		{
			_temp = _val[0];
			for (unsigned char j = 0; j < 3; j++) _val[j] = _val[j+1];
			_val[3] = _temp;
			for (unsigned int k = 0;k<_speed;k++) _delay_ms(1);
		}
		
	}
	else
	{
		for (unsigned int i = 0; i < _loop; i++)
		{
			_temp = _val[3];
			for (unsigned char j = 0; j < 3; j++) _val[3-j] = _val[3-j-1];
			_val[0] = _temp;
			for (unsigned int k = 0;k<_speed;k++) _delay_ms(1);
		}
	}
}