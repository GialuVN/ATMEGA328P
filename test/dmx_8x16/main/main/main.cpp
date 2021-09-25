/*
 * main.cpp
 *
 * Created: 11/12/2015 10:14:24 AM
 * Author : RnD
 */ 

#include <avr/io.h>
#include "DMX_standard.h"
#include "matrix16x8.h"

int main(void)
{
    /* Replace with your application code */
	
	DMX_Init(MYUBRR);
	
	mt_set_all(0);
	DMX_transmit();
	
    while (1) 
    {
		for (unsigned char i = 0;i<8;i++)
		{
			 mt_set_all(0);
			 DMX_transmit();
			 mt_draw_round(7, 3, i);
			 DMX_transmit();
			 _delay_ms(50);
			
		}
		for (unsigned char i = 0;i<8;i++)
		{
			 mt_set_all(0);
			 DMX_transmit();
			mt_draw_round(7, 3, 7-i);
			DMX_transmit();
			_delay_ms(50);
		}
		
		//for (unsigned char i = 0;i<16;i++)
		//{
			//
			//for (unsigned char j=0;j<8;j++)
			//{
				//mt_set_xy(i,j,i*j*2);
				//DMX_transmit();
				//_delay_ms(20);
			//}
		//}
		//
		//_delay_ms(1000);
		//mt_set_all(0);
		//DMX_transmit();
		//
		//for (unsigned char i = 0;i<8;i++)
		//{
			//
			//for (unsigned char j=0;j<16;j++)
			//{
				//mt_set_xy(j,i,i*j*2);
				//DMX_transmit();
				//_delay_ms(20);
			//}
		//}
		//
		//_delay_ms(1000);
		//mt_set_all(0);
		//DMX_transmit();
    //}
	}
}

