/*
 * DMX_standard.cpp
 *
 * Created: 10/13/2015 2:25:57 PM
 *  Author: RnD
 */ 

#include "DMX_standard.h"
void DMX_Init( unsigned int ubrr)
{
	DDRD |= 1<<PORTD7;
	PORTD |= 1<<PORTD7;
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable transmitter */
	UCSR0B = (1<<TXEN0);
	//UCSRA = (1<<U2X);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C =(1<<USBS0)|(3<<UCSZ00);
}

void DMX_transmit(unsigned char val)
{
		UDR0 =val;
		while ( !( UCSR0A & (1<<UDRE0)) );//* Wait for empty transmit buffer */
}
void DMX_BREAK_MAB_Transmit(void)
{
	//while ( !( UCSR0A & (1<<UDRE0)) );//* Wait for empty transmit buffer */
	UCSR0B &=~(1<<TXEN0);	// TXEN disable
	TXD_DDR |=1<<TXD_PIN; // TXD config output port
	TXD_PORT &=~(1<<TXD_PIN);	// TXD pin pull low
	_delay_us(120);				//170us
	TXD_PORT |=(1<<TXD_PIN);	//TXD pin pull high
	_delay_us(12);				// 8us
	UCSR0B |=(1<<TXEN0);	//TXEN enable
	UDR0 =0;
	while ( !( UCSR0A & (1<<UDRE0)) );//* Wait for empty transmit buffer */
}


