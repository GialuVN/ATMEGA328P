/*
 * main.c
 *
 * Created: 6/8/2015 10:06:53 AM
 *  Author: admin
 */ 



#include "main.h"


 char buf[100];

int main(void)
{
	LED_DDR |= 1<<LED_PIN;
	RS485_initial(MYUBRR);
	ADC_initial(0x01,ADC_div128,ADC_REF_VCC);
	ADC_start();
	sei();
    while(1)
    {
			//USART_putc((const uint8_t*)"[\0");
			
			RS485_TXEN(_ENABLE);
			snprintf(buf, sizeof(buf), "%d", ADC_read(ADC0));
			RS485_putc((const unsigned char*)buf);
			TX_NEWLINE;
			_delay_ms(100);
			
			if (ADC_read(ADC0)<=500)
			{
				LED_PORT&=~(1<<LED_PIN);
			}
			else if(ADC_read(ADC0)>=540)
			{
				LED_PORT|=1<<LED_PIN;
			}
			else
			{
				LED_PORT ^=1<<LED_PIN;
			}
			//USART_putc((const uint8_t*)buf);
			//USART_putc((const uint8_t*)"]\0");
		//USART_putc((const uint8_t*)"\r\n\0");
		//USART_putc((const uint8_t*)"size of farme is: \0");

		
        //TODO:: Please write your application code 
    }
}
