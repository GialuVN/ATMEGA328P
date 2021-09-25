/*
 * DMX_standard.cpp
 *
 * Created: 10/13/2015 2:25:57 PM
 *  Author: RnD
 */ 

#include "DMX_standard.h"
extern volatile uint8_t channel_buff[MAX_DMX_CHANNEL];
volatile uint16_t _pointer;
volatile bool _complete;

void DMX_Init( unsigned int ubrr)
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable transmitter */
	UCSR0B = (1<<TXEN0)|(1<<UDRIE0);
	//UCSRA = (1<<U2X);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C =(1<<USBS0)|(3<<UCSZ00);
	
}
void DMX_start_transmit(uint8_t _MODE)
{
	
	_complete = false;
	DMX_BREAK_MAB_Transmit();
	UCSR0B |=(1<<UDRIE0);
	_pointer=0;
	UDR0 = _MODE;
}



void DMX_transmit(uint8_t _MODE)
{
	UCSR0B &=~(1<<UDRIE0);
	DMX_BREAK_MAB_Transmit();
	UDR0 = _MODE;

	for (uint16_t i = 0; i < MAX_DMX_CHANNEL; i++)
	{
		UDR0 = channel_buff[i]*ZOOM_IN;
		while ( !( UCSR0A & (1<<UDRE0)) );//* Wait for empty transmit buffer */
	}
}

void DMX_transmit_setting(uint8_t _MODE,uint8_t *data,uint8_t len)
{
	UCSR0B &=~(1<<UDRIE0);
	DMX_BREAK_MAB_Transmit();
	UDR0 = _MODE;

	for (uint16_t i = 0; i < len; i++)
	{
		UDR0 = data[i];
		while ( !( UCSR0A & (1<<UDRE0)) );//* Wait for empty transmit buffer */
	}
}



bool DMX_Is_Ready(void){return _complete;}
	
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

ISR(USART_UDRE_vect)
{
	if (_pointer>=MAX_DMX_CHANNEL) _complete = true;
	else
	{
		UDR0 = channel_buff[_pointer]*ZOOM_IN;
		_pointer++;
		
	}
}



