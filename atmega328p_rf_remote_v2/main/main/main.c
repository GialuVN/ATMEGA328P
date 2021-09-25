/*
 * main.c
 *
 * Created: 6/10/2015 2:18:41 PM
 *  Author: admin
 */ 

#include <avr/io.h>
int main(void)
{
	wdt_reset();
	wdt_enable(WDTO_250MS);
	timer0_init();
	DDRD|=1<<PORTD4;
    while(1)
    {
		
	if (RF_get_key()==8)
	{
		
		PORTD^=1<<PORTD4;
			_delay_ms(1000);
		RF_clear_key();
		
	
		
	}
	
        //TODO:: Please write your application code 
    
}
