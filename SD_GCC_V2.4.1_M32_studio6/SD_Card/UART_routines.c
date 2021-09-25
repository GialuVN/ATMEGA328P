//**************************************************************
//******** FUNCTIONS FOR SERIAL COMMUNICATION USING UART *******
//**************************************************************
//Controller: ATmega328 (Clock: 16 Mhz-internal)
//Compiler	: AVR-GCC (winAVR with AVRStudio)
//Project V.: Version - 2.4.1
//Author	: CC Dharmani, Chennai (India)
//			  www.dharmanitech.com
//Date		: 24 Apr 2011
//**************************************************************


#define F_CPU 16000000UL// Clock Speed
#define BAUD 250000
#define MYUBRR F_CPU/16/BAUD-1

#include "UART_routines.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>


volatile unsigned char _holding;

//**************************************************
//UART0 initialize
//baud rate: 19200  (for controller clock = 8MHz)
//char size: 8 bit
//parity: Disabled
//**************************************************
void uart0_init(void)
{
	RS_DDR |=(1<<TXD_PIN)|(1<<TXEN_PIN);
	RS_DDR &=~(1<<RXD_PIN);
	RS_PORT |= 1<<RXD_PIN;
	UCSR0B = 0x00; //disable while setting baud rate
	UCSR0A = 0x00;
	/* Enable transmitter */
	/* Set frame format: 8data, 1stop bit */
	UCSR0C =(1<<UCSZ00)|(1<<UCSZ01);
	UBRR0H =(unsigned char)((MYUBRR)>>8);
	UBRR0L = (unsigned char) (MYUBRR);
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	_holding = 0;
}


void RS485_TXEN(unsigned char _val)// _ENABLE || _DISABLE
{
	if (_val)
	{
		 RS_PORT |= 1<<TXEN_PIN;
		 UCSR0B &= ~(1<<RXEN0);
		 USART_Flush();
		 _delay_ms(1);
		
	}
	
	else
	{
		while ( !(UCSR0A & (1<<TXC0)));
		 RS_PORT &=~(1<<TXEN_PIN);
		 UCSR0B |= (1<<RXEN0);
		   _delay_ms(10);
			USART_Flush();
		
		 
		 
	}
}

void USART_Flush( void )
{
	unsigned char  dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}

//**************************************************
//Function to receive a single byte
//*************************************************
unsigned char receiveByte( void )
{
	unsigned char data, status;
	
	if (_holding==0) RS485_TXEN(_DISABLE);
	_holding =1;
	while(!(UCSR0A & (1<<RXC0))); 	// Wait for incomming data
	status = UCSR0A;
	data = UDR0;
	return(data);
}
//***************************************************
//Function to transmit a single byte
//***************************************************
void transmitByte( unsigned char data )
{
	if (_holding==1) RS485_TXEN(_ENABLE);
	_holding =0;
	while ( !(UCSR0A & (1<<UDRE0)) )
		; 			                /* Wait for empty transmit buffer */
	UDR0 = data; 			        /* Start transmition */
	
}


//***************************************************
//Function to transmit hex format data
//first argument indicates type: CHAR, INT or LONG
//Second argument is the data to be displayed
//***************************************************
void transmitHex( unsigned char dataType, unsigned long data )
{
unsigned char count, i, temp;
unsigned char dataString[] = "0x        ";

if (dataType == CHAR) count = 2;
if (dataType == INT) count = 4;
if (dataType == LONG) count = 8;

for(i=count; i>0; i--)
{
  temp = data % 16;
  if((temp>=0) && (temp<10)) dataString [i+1] = temp + 0x30;
  else dataString [i+1] = (temp - 10) + 0x41;

  data = data/16;
}

transmitString (dataString);
}

//***************************************************
//Function to transmit a string in Flash
//***************************************************
void transmitString_F( const char* string)
{
  while (pgm_read_byte(&(*string)))
   transmitByte(pgm_read_byte(&(*string++)));
}

//***************************************************
//Function to transmit a string in RAM
//***************************************************
void transmitString(unsigned char* string)
{
  while (*string)
   transmitByte(*string++);
}

//************ END ***** www.dharmanitech.com *******
