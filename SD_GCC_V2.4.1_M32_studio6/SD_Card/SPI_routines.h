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

#ifndef _SPI_ROUTINES_H_
#define _SPI_ROUTINES_H_

#define SPI_SD             SPCR =(1<<MSTR)|(1<<SPE)|(1<<SPR1)|(1<<SPR0); //125kHZ
#define SPI_HIGH_SPEED     SPCR =(1<<MSTR)|(1<<SPE)|(1<<SPR1); SPSR |= (1<<SPI2X)	//4MhZ

void spi_init(void);
unsigned char SPI_transmit(unsigned char);
unsigned char SPI_receive(void);

#endif
