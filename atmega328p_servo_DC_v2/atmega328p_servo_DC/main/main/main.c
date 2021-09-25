/*
 * main.c
 *
 * Created: 6/16/2015 9:32:34 AM
 *  Author: admin
 */ 
#include "atmegax8_servo_DC.h"
#include "disp/xiudun2008V.h"
#include <avr/io.h>

int main(void)
{
	SERVO_DC_initial();

	sei();
    while(1)
    {
		
		//
		//for (unsigned char i = 0;i<100;i++)
		//{
			//SERVO_DC_PID_SPEED_UPDATA(30,20,55,i,RIGHT);
			//_delay_ms(50);
		//}
		//
		//for (unsigned char i = 0;i<100;i++)
		//{
			//SERVO_DC_PID_SPEED_UPDATA(30,20,55,150-i,RIGHT);
			//_delay_ms(50);
		//}
		//
			//for (unsigned char i = 0;i<100;i++)
			//{
				//SERVO_DC_PID_SPEED_UPDATA(30,20,55,i,LEFT);
				//_delay_ms(50);
			//}
			//
			//for (unsigned char i = 0;i<100;i++)
			//{
				//SERVO_DC_PID_SPEED_UPDATA(30,20,55,150-i,LEFT);
				//_delay_ms(50);
			//}
        //TODO:: Please write your application code 
    }
}

