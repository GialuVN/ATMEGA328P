/*
 * main.c
 *
 * Created: 8/5/2015 9:06:33 AM
 *  Author: admin
 */ 

#include "PWM.h"
#include <avr/io.h>
unsigned char tem[DATA_LEN];
int main(void)
{
	tem[0] = 10;
	tem[1] = 50;
	tem[2] = 100;
	tem[3] = 254;
	tem[4] = 200;
	tem[5] = 255;
	PWM_initial();
	PWM_updata(tem);
    while(1)
    {
		
        //TODO:: Please write your application code 
    }

}

