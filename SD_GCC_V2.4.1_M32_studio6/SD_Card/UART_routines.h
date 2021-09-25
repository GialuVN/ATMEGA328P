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

#ifndef _UART_ROUTINES_H_
#define _UART_ROUTINES_H_

#define CHAR 0
#define INT  1
#define LONG 2

#define _ENABLE 1
#define _DISABLE 0

#define TXEN_PIN	PORTD7
#define RXD_PIN		PORTD0
#define TXD_PIN		PORTD1
#define RS_DDR		DDRD
#define	RS_PORT		PORTD

#define TX_NEWLINE {transmitByte(0x0d); transmitByte(0x0a);}

void uart0_init(void);
void RS485_TXEN(unsigned char _val);
void USART_Flush( void );
unsigned char receiveByte(void);
void transmitByte(unsigned char);
void transmitString_F(const char*);
void transmitString(unsigned char*);
void transmitHex( unsigned char dataType, unsigned long data );


#endif
