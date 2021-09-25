/*
 * DMX_standard.cpp
 *
 * Created: 10/13/2015 2:25:57 PM
 *  Author: RnD
 */ 

#include "DMX_standard.h"
extern volatile uint8_t channel_buff[16][8];
volatile uint16_t _pointer;
volatile bool _complete;
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

void DMX_transmit(void)
{
	UCSR0B &=~(1<<UDRIE0);
	DMX_BREAK_MAB_Transmit();
	UDR0 =0;
	
	for (unsigned char i = 0; i <4; i++)
	{
		for (unsigned char j= 0;j<8;j++)
		{
				UDR0 = channel_buff[7-j][i*2];
				while ( !( UCSR0A & (1<<UDRE0)) );//* Wait for empty transmit buffer */
		
		}
	for (unsigned char j= 0;j<8;j++)
		{
				UDR0 = channel_buff[j][i*2+1];
				while ( !( UCSR0A & (1<<UDRE0)) );//* Wait for empty transmit buffer */
		
		}
	}
	for (unsigned char i = 0; i <4; i++)
	{
		
		
	for (unsigned char j= 0;j<8;j++)
		{
				UDR0 = channel_buff[8+j][(3-i)*2+1];
				while ( !( UCSR0A & (1<<UDRE0)) );//* Wait for empty transmit buffer */
		}
		
		for (unsigned char j= 0;j<8;j++)
		{
				UDR0 = channel_buff[8+7-j][(3-i)*2];
				while ( !( UCSR0A & (1<<UDRE0)) );//* Wait for empty transmit buffer */
		
		}
		
	}
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
}


