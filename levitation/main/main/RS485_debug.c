/*
 * RS485_debug.c
 *
 * Created: 8/20/2015 3:21:35 PM
 *  Author: admin
 */ 

#include "RS485_debug.h"
void RS485_initial(unsigned int ubrr)// MYUBRR
{
	RS_DDR |=(1<<TXD_PIN)|(1<<TXEN_PIN);
	RS_DDR &=~(1<<RXD_PIN);
	RS_PORT |= 1<<RXD_PIN;
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable transmitter */
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C =(1<<USBS0)|(3<<UCSZ00);
	
}

void RS485_TXEN(unsigned char _val)// _ENABLE || _DISABLE
{
	if (_val) RS_PORT |= 1<<TXEN_PIN;
	else RS_PORT &=~(1<<TXEN_PIN);
}


void USART_Flush( void )
{
	unsigned char dummy;
	while ( UCSR0A&(1<<RXC0) )
	{
		dummy = UDR0;
	}
}

void RS485_transmit(unsigned char _byte)
{
	while( !( UCSR0A & (1<<UDRE0)));
	UDR0 =  _byte;
}


int RS485_recive(void)
{
	unsigned char _temp,_status;
	while ( UCSR0A&(1<<RXC0) ){};
	_status = UCSR0A;
	_temp = UDR0;
	if (_status & ((1<<FE0)|(1<<DOR0))) return -1;
	return (int)_temp;
}


void RS485_putc(const unsigned char *c)
{
	while(*c)
	{
		RS485_transmit(*c);
		c++;
	}
}

void RS485_put(const unsigned char *data,unsigned int n)
{
	for (unsigned int i = 0; i < n; i++) RS485_transmit(data[i]);
}
