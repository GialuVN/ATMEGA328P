//**************************************************************
// ****** FUNCTIONS FOR SPI COMMUNICATION *******
//**************************************************************
//Controller: ATmega328 (Clock: 16 Mhz-internal)
//Compiler	: AVR-GCC (winAVR with AVRStudio)
//Project V.: Version - 2.4.1
//Author	: CC Dharmani, Chennai (India)
//			  www.dharmanitech.com
//Date		: 24 Apr 2011
//**************************************************************

#include <avr/io.h>
#include "SPI_routines.h"

//SPI initialize for SD card
//clock rate: 125Khz
void spi_init(void)
{
	DDRB |=(1<<PINB5)|(1<<PINB2)|(1<<PINB3);
	DDRB &=~(1<<PINB4);
	SPCR |=(1<<MSTR)|(1<<SPE)|(1<<SPR1)|(1<<SPR0);//125khz
}

unsigned char SPI_transmit(unsigned char data)
{
// Start transmission
SPDR = data;
// Wait for transmission complete
while(!(SPSR & (1<<SPIF)));
data = SPDR;

return(data);
}

unsigned char SPI_receive(void)
{
unsigned char data;
// Wait for reception complete

SPDR = 0xff;
while(!(SPSR & (1<<SPIF)));
data = SPDR;

// Return data register
return data;
}

//******** END ****** www.dharmanitech.com *****
