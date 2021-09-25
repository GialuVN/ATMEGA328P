/*
 * main.c
 *
 * Created: 6/16/2015 9:32:34 AM
 *  Author: admin
 */ 

#include "remote/pt2260_dec.h"
#include "atmegax8_servo_DC.h"
#include "disp/xiudun2008V.h"
#include <avr/io.h>

float a;
double b;
int c;
unsigned char d;
unsigned int e;
unsigned int f;



int main(void)
{
	SERVO_DC_initial();
	SERVO_CTR_initial();
//	RF_decode_initial(0xDA);
	sei();
	//SERVO_DC_PID_SPEED_UPDATA(30,20,55,10,RIGHT);
	
	e = 100;
	e-=1000;
	
    while(1)
    {
		_delay_ms(100);
		SEG7_disp_uint(abs(e),50);
		
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

