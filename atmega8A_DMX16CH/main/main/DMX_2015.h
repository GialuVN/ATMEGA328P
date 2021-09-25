/*
 * DMX_2015.h
 *
 * Created: 10/9/2015 8:54:49 AM
 *  Author: RnD
 */ 


#ifndef DMX_2015_H_
#define DMX_2015_H_

#define F_CPU 16000000UL// Clock Speed
#define BAUD 250000
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/wdt.h>
#include <util/crc16.h>
#define FE_MASK		(1<<FE)
#define RXC_MASK    (1<<RXC)
#define DMX_LEN 16

//#define MY_DMX_ADDR  1

//define before progamming
#define VER		0x01
#define ID		208
#define ADDR_default 1
#define ID_boardcast 0x0000


///////////////////////////


//fix define
#define DTA		0x00
#define CTR		0xAA
#define HEAD	0xCC

#define SMILE	2015
#define SLEEP_EVENT	0XAAAA
#define FIRST_START 0xCCCC	
/////////////////////////////

typedef struct DMX_DATA	//DMX_package control
{
	uint16_t counter;
	volatile uint16_t address;
	uint16_t address_buffer;
	uint8_t data_count;
	uint8_t stage;
	bool check_complete;
	bool enable;
	uint8_t command;
}DMX_DATA;


void DMX_USART_Init( unsigned int ubrr);
uint16_t DMX_get_address(void);
void DMX_data_reset(uint16_t dmx_adress);
uint8_t DMX_get_data(volatile uint8_t *data,uint8_t len);

bool DMX_Frame_CheckSum(uint8_t *_data,uint8_t len);
#endif /* DMX_2015_H_ */