/*
 * TLS3001.cpp
 *
 * Created: 10/30/2015 1:47:50 PM
 *  Author: RnD
 */ 


#include "TLS3001.h"
#include <avr/interrupt.h>

void TLS3001_Initial(void)
{
	DDRD |= 1<<PORTD7;
	PORTD |=(1<<PIND7);
		DDR |=1<<PIN;		
}

void TLS3001_Send_Bits(unsigned long _long,unsigned char _n)
{
	
	for (unsigned char i = 0; i < _n; i++)
	{
		if (_long&0x80000000)
		{
			 POR |=_HIG_;
			 for (uint8_t j = 0;j<12;j++) nop();
			 nop();
			 POR &=_LOW_;
			 for (uint8_t j = 0;j<8;j++) nop();
			 nop();
			 nop();
			 nop();
			 nop();
			 nop();
			 nop();
		}
		else
		{
			POR &=_LOW_;
			 for (uint8_t j = 0;j<12;j++) nop();
			 nop();
			POR |= _HIG_;
			 for (uint8_t j = 0;j<8;j++) nop();
			 nop();
			 nop();
			 nop();
			 nop();
			 nop();
			 nop();
		}
		_long <<=1;
	}
}
void TLS3001_Send_Sys(void)
{
	TLS3001_Send_Bits(0xFFFE2000,30);
	POR &=_LOW_;
}
void TLS3001_Send_Reset(void)
{
	TLS3001_Send_Bits(0xFFFE8000,19);
	POR &=_LOW_;
}
void TLS3001_Send_Head(void)
{
	TLS3001_Send_Bits(0xFFFE4000,19);
	POR &=_LOW_;
}

void TLS3001_Send_RGB(unsigned int _R, unsigned int _G,unsigned int _B)
{
	for (unsigned char i = 0; i < 13; i++)
	{
		if (_R&0x1000)
		{
			POR |=_HIG_;
			for (uint8_t j = 0;j<12;j++) nop();
			nop();
			
			POR &=_LOW_;
			for (uint8_t j = 0;j<8;j++) nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
		}
		else
		{
			POR &=_LOW_;
			for (uint8_t j = 0;j<12;j++) nop();
			nop();
			POR |= _HIG_;
			for (uint8_t j = 0;j<8;j++) nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
		}
		_R <<=1;
	}
	for (unsigned char i = 0; i < 13; i++)
	{
		if (_G&0x1000)
		{
			POR |=_HIG_;
			for (uint8_t j = 0;j<12;j++) nop();
			nop();
			
			POR &=_LOW_;
			for (uint8_t j = 0;j<8;j++) nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
		}
		else
		{
			POR &=_LOW_;
			for (uint8_t j = 0;j<12;j++) nop();
			nop();
			POR |= _HIG_;
			for (uint8_t j = 0;j<8;j++) nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
		}
		_G <<=1;
	}
	for (unsigned char i = 0; i < 13; i++)
	{
		if (_B&0x1000)
		{
			POR |=_HIG_;
			for (uint8_t j = 0;j<12;j++) nop();
			nop();
			
			POR &=_LOW_;
			for (uint8_t j = 0;j<8;j++) nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
		}
		else
		{
			POR &=_LOW_;
			for (uint8_t j = 0;j<12;j++) nop();
			nop();
			POR |= _HIG_;
			for (uint8_t j = 0;j<8;j++) nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
			nop();
		}
		_B <<=1;
	}
	
}