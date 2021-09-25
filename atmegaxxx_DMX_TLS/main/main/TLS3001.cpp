/*
 * TLS3001.cpp
 *
 * Created: 10/30/2015 1:47:50 PM
 *  Author: RnD
 */ 


#include "TLS3001.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

const uint16_t table[] PROGMEM ={
	0,
	16,
	32,
	48,
	64,
	80,
	96,
	112,
	128,
	145,
	161,
	177,
	193,
	209,
	225,
	241,
	257,
	273,
	289,
	305,
	321,
	337,
	353,
	369,
	385,
	401,
	418,
	434,
	450,
	466,
	482,
	498,
	514,
	530,
	546,
	562,
	578,
	594,
	610,
	626,
	642,
	658,
	674,
	691,
	707,
	723,
	739,
	755,
	771,
	787,
	803,
	819,
	835,
	851,
	867,
	883,
	899,
	915,
	931,
	947,
	964,
	980,
	996,
	1012,
	1028,
	1044,
	1060,
	1076,
	1092,
	1108,
	1124,
	1140,
	1156,
	1172,
	1188,
	1204,
	1220,
	1237,
	1253,
	1269,
	1285,
	1301,
	1317,
	1333,
	1349,
	1365,
	1381,
	1397,
	1413,
	1429,
	1445,
	1461,
	1477,
	1493,
	1510,
	1526,
	1542,
	1558,
	1574,
	1590,
	1606,
	1622,
	1638,
	1654,
	1670,
	1686,
	1702,
	1718,
	1734,
	1750,
	1766,
	1783,
	1799,
	1815,
	1831,
	1847,
	1863,
	1879,
	1895,
	1911,
	1927,
	1943,
	1959,
	1975,
	1991,
	2007,
	2023,
	2039,
	2056,
	2072,
	2088,
	2104,
	2120,
	2136,
	2152,
	2168,
	2184,
	2200,
	2216,
	2232,
	2248,
	2264,
	2280,
	2296,
	2312,
	2329,
	2345,
	2361,
	2377,
	2393,
	2409,
	2425,
	2441,
	2457,
	2473,
	2489,
	2505,
	2521,
	2537,
	2553,
	2569,
	2585,
	2602,
	2618,
	2634,
	2650,
	2666,
	2682,
	2698,
	2714,
	2730,
	2746,
	2762,
	2778,
	2794,
	2810,
	2826,
	2842,
	2858,
	2875,
	2891,
	2907,
	2923,
	2939,
	2955,
	2971,
	2987,
	3003,
	3019,
	3035,
	3051,
	3067,
	3083,
	3099,
	3115,
	3131,
	3148,
	3164,
	3180,
	3196,
	3212,
	3228,
	3244,
	3260,
	3276,
	3292,
	3308,
	3324,
	3340,
	3356,
	3372,
	3388,
	3404,
	3421,
	3437,
	3453,
	3469,
	3485,
	3501,
	3517,
	3533,
	3549,
	3565,
	3581,
	3597,
	3613,
	3629,
	3645,
	3661,
	3677,
	3694,
	3710,
	3726,
	3742,
	3758,
	3774,
	3790,
	3806,
	3822,
	3838,
	3854,
	3870,
	3886,
	3902,
	3918,
	3934,
	3950,
	3967,
	3983,
	3999,
	4015,
	4031,
	4047,
	4063,
	4079,
	4095
};

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

void TLS3001_pull(bool val)
{
	if(val) POR |=_HIG_;
	else POR &=_LOW_;
}



void TLS3001_Send_RGB_8(unsigned char _R, unsigned char _G,unsigned char _B)
{
	unsigned int t_R;
	unsigned int t_G;
	unsigned int t_B;
	t_R = pgm_read_word(&table[_R]);
	t_G = pgm_read_word(&table[_G]);
	t_B = pgm_read_word(&table[_B]);
	
	TLS3001_Send_RGB(t_R,t_G,t_B);
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

