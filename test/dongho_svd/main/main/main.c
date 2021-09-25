/*
 * main.c
 *
 * Created: 6/10/2015 2:18:41 PM
 *  Author: admin
 */ 

#include <avr/io.h>
#include "pt2260_dec.h"

#define CKIN PORTC4
#define OUT1  PORTB2
#define OUT2  PORTB3

int main(void)
{
	wdt_reset();
	wdt_enable(WDTO_250MS);
	timer0_init();
	RF_decode_initial(0x00);
	RF_decode_setup(300,25);
	RF_decode_start();
	DDRD|=1<<PORTD4;
	DDRC &=~(1<<CKIN);
	PORTC|=1<<CKIN;
	DDRB |=(1<<OUT1)|(1<<OUT2);
	RF_clear_key();
    while(1)
    {
		
		if (!(PINC&(1<<CKIN)))
		{
				
					PORTD^=1<<PORTD4;
					PORTB |= 1<<OUT1;
					PORTB &=~(1<<OUT2);
					set_ms_counter(3200);
					while (!check_ms_counter()){};
					PORTB &=~(1<<OUT1);
					PORTB &=~(1<<OUT2);
					set_ms_counter(16000);
					while (!check_ms_counter()){};
					PORTB |= 1<<OUT2;
					PORTB &=~(1<<OUT1);
					set_ms_counter(3200);
					while (!check_ms_counter()){};
					PORTB &=~(1<<OUT1);
					PORTB &=~(1<<OUT2);
				
		}
		
		if (RF_get_key()==8)
		{
			PORTD|=1<<PORTD4;
			_delay_ms(300);
			RF_clear_key();
			
			while (1)
			{
				PORTB |= 1<<OUT1;
				PORTB &=~(1<<OUT2);
				set_ms_counter(1280);
				while (!check_ms_counter()){};
				PORTB &=~(1<<OUT1);
				PORTB &=~(1<<OUT2);
				set_ms_counter(1280);
				while (!check_ms_counter()){};
				PORTB |= 1<<OUT2;
				PORTB &=~(1<<OUT1);
				set_ms_counter(1280);
				while (!check_ms_counter()){};
				PORTB &=~(1<<OUT1);
				PORTB &=~(1<<OUT2);
				set_ms_counter(1280);
				while (!check_ms_counter()){};
				if (RF_get_key()==8)
				{
					_delay_ms(1000);
					RF_clear_key();
					break;
				}
			}
	
		}
	else if (RF_get_key()==4)
	{
		
		
		PORTD|=1<<PORTD4;
		_delay_ms(300);
		RF_clear_key();
		
		while (1)
		{
			PORTB |= 1<<OUT1;
			PORTB &=~(1<<OUT2);
			set_ms_counter(640);
			while (!check_ms_counter()){};
			PORTB &=~(1<<OUT1);
			PORTB &=~(1<<OUT2);
			set_ms_counter(640);
			while (!check_ms_counter()){};
			PORTB |= 1<<OUT2;
			PORTB &=~(1<<OUT1);
			set_ms_counter(640);
			while (!check_ms_counter()){};
			PORTB &=~(1<<OUT1);
			PORTB &=~(1<<OUT2);
			set_ms_counter(640);
			while (!check_ms_counter()){};
			if (RF_get_key()==4)
			{
				_delay_ms(1000);
				RF_clear_key();
				break;
			}
		}
	}
	else if(RF_get_key()==2)
	{
		PORTB &=~(1<<OUT1);
		PORTB &=~(1<<OUT2);
		PORTD|=1<<PORTD4;
		_delay_ms(300);
		RF_clear_key();
		while (1)
		{
			if (RF_get_key()==2)
			{
				_delay_ms(1000);
				RF_clear_key();
				break;
			}
			_delay_ms(1);
		}
	}
	_delay_ms(1);
        //TODO:: Please write your application code 
    }
}
