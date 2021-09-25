/*
 * main.c
 *
 * Created: 8/20/2015 3:02:12 PM
 *  Author: admin
 */ 

#include "pwm6ch.h"
#include "RS485_debug.h"
#include "adc_megax8.h"
#include <avr/io.h>

char buf[100];
//unsigned char _pwm;

int main(void)
{
	LED_CONFIG;
	RS485_initial(MYUBRR);
	ADC_initial(0x01,ADC_div8,ADC_REF_VCC);
	pwm_phasecorrect_timer2_initial(clk_timer2_div8);
	pwm_phasecorrect_timer2_OCR2B_updata(0);
	ADC_start();
	sei();
    while(1)
    {
		//RS485_TXEN(_ENABLE);
		//snprintf(buf, sizeof(buf), "%d", ADC_read(ADC0));
		//RS485_putc((const unsigned char*)buf);
		//TX_NEWLINE;
		//_delay_ms(100);
		//
		//
		
			if (ADC_read(ADC0)>=555)
			{
				LED_ON;
				pwm_phasecorrect_timer2_OCR2B_updata(20);
			}
			else if ((ADC_read(ADC0)>=510) && (ADC_read(ADC0)<=540))
			{
				LED_OFF;
				pwm_phasecorrect_timer2_OCR2B_updata(100);
			}
			else if ((ADC_read(ADC0)<510))
			{
				LED_OFF;
				pwm_phasecorrect_timer2_OCR2B_updata(20);
				
			}
			else
			{
				
				LED_REV;
				pwm_phasecorrect_timer2_OCR2B_updata(255);
			}
		
        //TODO:: Please write your application code 
    }
}




	
