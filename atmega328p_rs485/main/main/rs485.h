/*
 * rs485.h
 *
 * Created: 6/24/2015 8:57:16 AM
 *  Author: admin
 */ 


#ifndef RS485_H_
#define RS485_H_

#define F_CPU 16000000// Clock Speed
#define BAUD 250000
#define MYUBRR F_CPU/16/BAUD-1
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include <math.h>
#include <util/crc16.h>


#define TXEN_PIN	PORTD7
#define RXD_PIN		PORTD0
#define TXD_PIN		PORTD1
#define RS_DDR		DDRD
#define	RS_PORT		PORTD

#define _ENABLE 1
#define _DISABLE 0

#define _ERR	1
#define _OK		0

typedef enum MODE
{
	_WAIT,	
	_SEND,
	_REC_DATA,
	_REC_RESPOND,
	
}MODE;


typedef struct RS485_PACK
{
	unsigned char data[256];
	unsigned int len;
	unsigned char my_ddr;	
	
}RS485_PACK;

typedef struct RS485_CTR
{
	unsigned int counter;
	unsigned char stage;
}RS485_CTR;


typedef union RS485_flag                    
{
	unsigned char all;
	struct
	{
		unsigned char complete:1;
		unsigned char mode:2;
		unsigned char error:1;
		unsigned char unusebits:4;
	};

}RS485_flag;


void RS485_initial(unsigned int ubrr,unsigned char _myaddr);// MYUBRR
void RS485_TXEN(unsigned char _val);// _ENABLE || _DISABLE
unsigned char RS485_frame_build(unsigned char *_data_in,unsigned char _data_len);// return _ERR _data_len>250
void RS485_frame_respond(unsigned char _cmd,unsigned char _val);
unsigned char CheckSum(volatile unsigned char *_data_in,unsigned int _data_len);
void RS485_sending(void);
unsigned char RS485_reading(unsigned char *_data);// [len+1] ==AA--> data|[len+1] ==CC--> respond
void RS485_reciving(void);
void USART_Flush( void );
void BREAK_MAB_Transmit(void);
#endif /* RS485_H_ */