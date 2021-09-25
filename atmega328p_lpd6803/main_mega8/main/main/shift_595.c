/*
 * shift_595.c
 *
 * Created: 31/08/2013 8:22:23 AM
 *  Author: THIET KE 3
 */ 


#include "shift_595.h"
#include <avr/io.h>
#include <inttypes.h>



void shift_config_pin()
{
	//ck,da,la ouput pin
	CK_DDR |=1<<CK_PIN;
	DT_DDR |=1<<DT_PIN;
	LA_DDR |=1<<LA_PIN;
	//da, out level 1
	DT_POR |=1<<DT_PIN;
	//la,ck out level 0
	CK_POR &=~(1<<CK_PIN);
	LA_POR &=~(1<<LA_PIN);
}

void shift_byte(uint8_t value)
{
	uint8_t i = 0;
	while(i<8)
	{
#ifdef MSB_FIRST		
		
		if (value & (1<<(7-i)))	DT_POR |=1<<DT_PIN;
		else DT_POR &=~(1<<DT_PIN);
#endif	

#ifdef LSB_FIRST
		if (value & (1<<i)) DT_POR |=1<<DT_PIN;
		else DT_POR &=~(1<<DT_PIN);
	
#endif		
		CK_POR |=1<<CK_PIN;
		CK_POR &=~(1<<CK_PIN);
		i++;
	}
}

void shift_latch()
{
	LA_POR |=1<<LA_PIN;
	LA_POR &=~(1<<LA_PIN);
}




