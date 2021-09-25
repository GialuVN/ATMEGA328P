/*
 * main.cpp
 *
 * Created: 10/30/2015 1:42:54 PM
 * Author : RnD
 */ 

#include <avr/io.h>
#include "TLS3001.h"


int main(void)
{
	TLS3001_Initial();
    while (1) 
    {
		TLS3001_Send_Sys();
		_delay_ms(200);
		TLS3001_Send_Head();
		TLS3001_Send_RGB(4095,0,0);
		TLS3001_Send_RGB(4095,0,0);
		TLS3001_Send_Reset();
		_delay_ms(1);
		TLS3001_Send_Sys();
		_delay_ms(200);
		TLS3001_Send_Head();
		TLS3001_Send_RGB(0,4095,0);
		TLS3001_Send_RGB(0,4095,0);
		TLS3001_Send_Reset();
		_delay_ms(1);
		TLS3001_Send_Sys();
		_delay_ms(200);
		TLS3001_Send_Head();
		TLS3001_Send_RGB(0,0,4095);
		TLS3001_Send_RGB(0,0,4095);
		TLS3001_Send_Reset();
		_delay_ms(1);
    }
}

