/*
 * main.c
 *
 * Created: 6/24/2015 8:56:22 AM
 *  Author: admin
 */ 


#include <avr/io.h>
#include "rs485.h"
#include "disp/xiudun2008V.h"


unsigned char data[200];

int main(void)
{
	hc595_set_spi();
	SEG7_initial();
	RS485_initial(MYUBRR,100);
	
	sei();
	RS485_reciving();

	while (1)
	{
		
		if (RS485_reading(data)==_REC_DATA)
		{
			
			SEG7_disp_uint(data[0],data[1]);
			
			RS485_reciving();
		}
		
	}


    while(1)
    {
		
		for (unsigned char i = 0;i<200;i++)
		{
			data[0] = i;
			data[1] = i;
			SEG7_disp_uint(data[0],data[1]);
			RS485_frame_build(data,2);
			RS485_sending();
			_delay_ms(100);
		}
		
		//if (RS485_reading(data)!=0)
		//{
			//SEG7_disp_uint( data[1],data[2]);
			//RS485_reciving();
		//}
        //TODO:: Please write your application code 
    }
}