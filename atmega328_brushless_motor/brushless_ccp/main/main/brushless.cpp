/*
 * brushless.cpp
 *
 * Created: 10/3/2015 2:42:01 PM
 *  Author: RnD
 */ 

#include "brushless.h"
Brushless motor;



void burshless_init()
{
	TIMSK2 |= (1 << OCIE0A);					 // set output compare interrupt enable
	TCCR2A |= (1 << WGM21);						// set CTC mode
	TCCR2B |= TIMER2_PRESCALER;					//CLK/32
	OCR2A   = TIMER2_COMPARE_VALUE;				// set compare value for interrupt
	//interrupt initial
	DDR_S &= ~(1<<PINx_S);
	PORT_S |=1<<PINx_S;
	PCICR = 1<<PCIE1;	// PCINT10 select
	PCMSK1 = 1<<PCINT10;
	//motor initial
	DDR_M |= 1<<PINx_M;
	PORT_M &=~(1<<PINx_M);
	sei();
}

void speed_update(int speed)
{
	
	motor.input_speed = speed;
	
}


ISR(PCINT1_vect)
{
	if (motor.signal_en==true)
	{
		if (!(PIN_S&(1<<PINx_S)))
		{
			motor.counter_en = false;
			motor.curent_speed = motor.counter;
			motor.counter = 0;
			motor.stage = 0;
		}
	}
	
}
ISR(TIMER2_COMPA_vect)
{
	if (motor.counter_en == true) if (motor.counter<=65000) motor.counter++;
	
	if (motor.curent_speed>motor.input_speed)
	{
		switch (motor.stage)
		{
			case 0:
				motor.signal_en = false;
				motor.counter_en = true;
				motor.counter_delay = motor.curent_speed/4;
				motor.counter_power = motor.curent_speed/8;
				motor.stage = 1;
			break;
			case 1:
			if (motor.counter_delay!=0) motor.counter_delay--;
			else
			{
				PORT_M |=(1<<PINx_M);	//motor on
				 motor.stage = 2;
			}
			break;
			
			case 2:
			if (motor.counter_power!=0) motor.counter_power--;
			else
			{
				PORT_M &=~(1<<PINx_M);	//motor off
				motor.signal_en = true;
				motor.stage = 3;
			}
			
			break;
			default:
			break;
		}
	}
	else
	{
		switch (motor.stage)
		{
			case 0:
			motor.signal_en = false;
			motor.counter_en = true;
			motor.counter_delay = motor.curent_speed/2;
			motor.stage = 1;
			break;
			case 1:
			if (motor.counter_delay!=0) motor.counter_delay--;
			else
			{
				motor.signal_en = true;
				 motor.stage = 3;
			}
			break;
			default:
			break;
		}
		
	}
	
}
