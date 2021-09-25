/*
 * xiudun2008V.c
 *
 * Created: 6/15/2015 1:17:47 PM
 *  Author: admin
 */ 
#include "xiudun2008V.h"
#include "hc595.h"
volatile SEG7_DATA seg7_data;
volatile SEG7_CTR seg7_ctr;
const uint8_t seg7_decode[] PROGMEM ={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xff,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xC2,0x89};
void SEG7_initial(void)
{
//	DDRC|=1<<PINC0;
	TCCR0A = (1 << WGM01);                      // Set the Timer Mode to CTC
	OCR0A = 249;                                 // Set 249 as value to count to 
	TIMSK0 |= (1 << OCIE0A);                     //Set the ISR COMPA vector
	TCCR0B |= (1 << CS00) | (1 << CS01) ;        // set pre-scaler to 64 and start the timer
	hc595_set_spi();
}

void SEG7_disp_uint(unsigned int sg1,unsigned int sg2)
{
	unsigned char _temp[4];
	if (sg1<=9999)
	{
		HEX2BCD_uint(sg1,_temp);
		seg7_data.seg11 = pgm_read_byte(&seg7_decode[_temp[0]]);
		seg7_data.seg12 = pgm_read_byte(&seg7_decode[_temp[1]]);
		seg7_data.seg13 = pgm_read_byte(&seg7_decode[_temp[2]]);
		seg7_data.seg14 = pgm_read_byte(&seg7_decode[_temp[3]]);
	}
	if (sg2<=9999)
	{
		
		HEX2BCD_uint(sg2,_temp);
		seg7_data.seg21 = pgm_read_byte(&seg7_decode[_temp[0]]);
		seg7_data.seg22 = pgm_read_byte(&seg7_decode[_temp[1]]);
		seg7_data.seg23 = pgm_read_byte(&seg7_decode[_temp[2]]);
		seg7_data.seg24 = pgm_read_byte(&seg7_decode[_temp[3]]);
	}
}


void HEX2BCD_uint(unsigned int val,unsigned char* bcd)
{
	if (val<=9999)
	{
		bcd[3]=val%10;
		bcd[2]= (val/10)%10;
		bcd[1]=(val/100)%10;
		bcd[0]=(val/1000)%10;
	}
	for (unsigned char i = 0;i<4;i++)
	{
		if(bcd[i]==0) bcd[i]=10;
		else return; 
	}
}

void SEG7_scan(void)
{
	switch(seg7_ctr.seg7_stage)
	{
		case 0:
		SEG7_send(0,seg7_data.seg12);
		seg7_ctr.seg7_stage =1;
		break;
		case 1:
		SEG7_send(1,seg7_data.seg13);
		seg7_ctr.seg7_stage =2;
		break;
		case 2:
		SEG7_send(2,seg7_data.seg14);
		seg7_ctr.seg7_stage =3;
		break;
		case 3:
		SEG7_send(3,seg7_data.seg22);
		seg7_ctr.seg7_stage =4;
		break;
		case 4:
		SEG7_send(4,seg7_data.seg23);
		seg7_ctr.seg7_stage =5;
		break;
		case 5:
		SEG7_send(5,seg7_data.seg24);
		seg7_ctr.seg7_stage =6;
		break;
		case 6:
		SEG7_send(6,seg7_data.seg11);
		seg7_ctr.seg7_stage =7;
		break;
		case 7:
		SEG7_send(7,seg7_data.seg21);
		seg7_ctr.seg7_stage =8;
		break;
		case 8:
		SEG7_send(8,seg7_data.leds_61);
		seg7_ctr.seg7_stage =9;
		break;
		case 9:
		SEG7_send(9,seg7_data.leds_62);
		seg7_ctr.seg7_stage =0;
		break;
		default:
		seg7_ctr.seg7_stage =0;
		break;
	}
}

 void SEG7_send(unsigned char mux,unsigned val)
{
	unsigned int _temp=0xffff;
	_temp &=~(1<<mux);
	hc595_byte_transmit(_temp>>8);
	hc595_byte_transmit(_temp);
	hc595_byte_transmit(val);
	hc595_latch();
}

void SEG7_updata(unsigned char select,unsigned val)
{
	switch (select)
	{
		case 0:
		seg7_data.seg11 = val;
		break;
		case 1:
		seg7_data.seg12 = val;
		break;
		case 2:
		seg7_data.seg13 = val;
		break;
		case 3:
		seg7_data.seg14 = val;
		break;
		case 4:
		seg7_data.seg21 = val;
		break;
		case 5:
		seg7_data.seg22 = val;
		break;
		case 6:
		seg7_data.seg23 = val;
		break;
		case 7:
		seg7_data.seg24 = val;
		break;
		case 8:
		seg7_data.leds_61 = val;
		break;
		case 9:
		seg7_data.leds_62 = val;
		break;
		default:
		break;
	}
}

ISR(TIMER0_COMPA_vect)
{
	SEG7_scan();
}