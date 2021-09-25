/*
 * main.c
 *
 * Created: 6/10/2015 2:18:41 PM
 *  Author: admin
 */ 

#include "pwm6ch.h"
#include <avr/io.h>
#include "pt2260_dec.h"
int main(void)
{
	pwm_phasecorrect_timer0_initial(clk_timer0_div64);
	pwm_phasecorrect_timer1_initial(clk_timer1_div64);
	pwm_phasecorrect_timer2_initial(clk_timer2_div64);
	

	RF_decode_initial(0xDA);
	sei();
    while(1)
    {
			switch (RF_decode_read())
			{
				case 1:
				pwm_phasecorrect_6ch_updata(255,0,0,0,0,0);
				break;
				case 2:
				pwm_phasecorrect_6ch_updata(0,255,0,0,0,0);
				break;
				case 4:
				pwm_phasecorrect_6ch_updata(0,0,255,0,0,0);
				break;
				case 8:
				pwm_phasecorrect_6ch_updata(0,0,0,255,0,0);
				break;
				default:
				break;
			}
			
			RF_decode_start();
		
		
		_delay_ms(100);
		
		
        //TODO:: Please write your application code 
    }
}