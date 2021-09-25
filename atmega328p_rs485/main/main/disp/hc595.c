/*
 * hc595.c
 *
 * Created: 23/02/2013 8:36:22 AM
 *  Author: THIET KE 3
 */ 

#include <avr/io.h>
#include "hc595.h"
//cai dat ISP che do 0 (che do ghi dich)

void hc595_set_spi()
{
#if (SPI_FUNC==1)
	
	DDRB |=(1<<PINB5)|(1<<PINB2)|(1<<PINB3);
	SPCR |=(1<<SPE)|(1<<MSTR)|(1<<DORD);
	SPSR |= 1<<SPI2X;
#else
//ck,da,la ouput pin
	CK_DDR |=1<<CK_PIN;
	DT_DDR |=1<<DT_PIN;
	LA_DDR |=1<<LA_PIN;
	//da, out level 1
	DT_POR |=1<<DT_PIN;
	//la,ck out level 0
	CK_POR &=~(1<<CK_PIN);
	LA_POR &=~(1<<LA_PIN);
#endif
}
//xuat 1 byte du lieu ra 595
void hc595_byte_transmit(uint8_t value)
{
	
#if (SPI_FUNC==1)	
		SPDR = value;
	while (!(SPSR & (1<<SPIF))){};
#else
		
	uint8_t i = 0;
	while(i<8)
	{
#ifdef MSB_FIRST
		
		if (value & (1<<(7-i)))	DT_POR |=1<<DT_PIN;
		else DT_POR &=~(1<<DT_PIN);
#endif

#ifdef LSB_FIRST
		if (value & (1<<i)) DT_POR |=1<<DT_PIN;
		else DT_POR &=~(1<<DT_PIN);
		
#endif
		CK_POR |=1<<CK_PIN;
		CK_POR &=~(1<<CK_PIN);
		i++;
	}

#endif	
}
		
		
//chot du lieu
void hc595_latch()
{
	
#if (SPI_FUNC==1)	
	PORTB |=1<<PINB2;
	PORTB &=~(1<<PINB2);
#else	
	
	LA_POR |=1<<LA_PIN;
	LA_POR &=~(1<<LA_PIN);
#endif
}


