/*
 * RS485_debug.h
 *
 * Created: 8/20/2015 3:21:46 PM
 *  Author: admin
 */ 


#ifndef RS485_DEBUG_H_
#define RS485_DEBUG_H_


#define F_CPU 16000000// Clock Speed
#define BAUD 250000
#define MYUBRR F_CPU/16/BAUD-1
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <math.h>

#define TXEN_PIN	PORTD7
#define RXD_PIN		PORTD0
#define TXD_PIN		PORTD1
#define RS_DDR		DDRD
#define	RS_PORT		PORTD

#define LED_DDR		DDRD
#define LED_PORT	PORTD
#define LED_PIN		PORTD4
#define _ENABLE 1
#define _DISABLE 0

void RS485_initial(unsigned int ubrr);// MYUBRR
void RS485_TXEN(unsigned char _val);// _ENABLE || _DISABLE
void USART_Flush( void );
void RS485_transmit(unsigned char _byte);
int RS485_recive(void);
void RS485_putc(const unsigned char *c);
void RS485_put(const unsigned char *data,unsigned int n);
#define TX_NEWLINE {RS485_transmit(0x0d); RS485_transmit(0x0a);}
	
#define LED_CONFIG {LED_DDR |= 1<<LED_PIN;}
#define LED_ON		{LED_PORT|=1<<LED_PIN;}
#define LED_OFF		{LED_PORT&=~(1<<LED_PIN);}
#define LED_REV		{LED_PORT ^=1<<LED_PIN;}

//////////////////////////////////////////////////////////////////////////
/************************************************************************/

//test
/* //USART_putc((const uint8_t*)"[\0");

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
}                                                                     */
/************************************************************************/

#endif /* RS485_DEBUG_H_ */