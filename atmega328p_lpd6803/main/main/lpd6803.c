/*
 * lpd6803.c
 *
 * Created: 24/09/2013 7:23:33 AM
 *  Author: THIET KE 3
 */ 
#include <avr/io.h>
#include "lpd6803.h"



void lpd6803_config_pin()
{
	//ck,da,la ouput pin
	CK_DDR |=1<<CK_PIN;
	DT_DDR |=1<<DT_PIN;
	//da, out level 0
	DT_POR &=~(1<<DT_PIN);
	CK_POR  &=~(1<<CK_PIN);
}

void lpd6803_start_farme()
{
	CK_POR &=~(1<<CK_PIN);
	DT_POR &=~(1<<DT_PIN);
	
	for (uint8_t i=0;i<32;i++)
	{
		CK_POR |=1<<CK_PIN;
		CK_POR &=~(1<<CK_PIN);
	}
}

void lpd_6803_npulse(uint16_t npulse)
{
	CK_POR &=~(1<<CK_PIN);
	DT_POR &=~(1<<DT_PIN);
	for (uint16_t i=0;i<npulse;i++)
	{
		CK_POR |=1<<CK_PIN;
		CK_POR &=~(1<<CK_PIN);
	}
}


void lpd6803_rgb(uint8_t red,uint8_t green,uint8_t blue)
{
	uint8_t mask;
	//out 1 = start
	DT_POR |=1<<DT_PIN;
	CK_POR |=1<<CK_PIN;
	CK_POR &=~(1<<CK_PIN);
	mask = 0x10;
	for (uint8_t i = 0;i<5;i++)
	{
		if(mask &red) DT_POR |=1<<DT_PIN;
		else DT_POR &=~(1<<DT_PIN);
		CK_POR |=1<<CK_PIN;
		CK_POR &=~(1<<CK_PIN);
		mask>>=1; 
	}
	mask = 0x10;
	for (uint8_t i = 0;i<5;i++)
	{
		if(mask &green) DT_POR |=1<<DT_PIN;
		else DT_POR &=~(1<<DT_PIN);
		CK_POR |=1<<CK_PIN;
		CK_POR &=~(1<<CK_PIN);
		mask>>=1; 
	}
	mask = 0x10;
	for (uint8_t i = 0;i<5;i++)
	{
		if(mask &blue) DT_POR |=1<<DT_PIN;
		else DT_POR &=~(1<<DT_PIN);
		CK_POR |=1<<CK_PIN;
		CK_POR &=~(1<<CK_PIN);
		mask>>=1;
	}
}

