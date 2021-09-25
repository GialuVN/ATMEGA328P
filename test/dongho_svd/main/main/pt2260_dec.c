/*
 * pt2260_dec.c
 *
 * Created: 6/10/2015 2:19:27 PM
 *  Author: admin
 */ 

#include "pt2260_dec.h"

volatile RF_DECODE rf_decode;
volatile unsigned int x_counter; 

void RF_decode_initial(unsigned char id)
{
	DDR_RF &= ~(1<<IN_RF);
	POR_RF |=1<<IN_RF;
	PCICR |= 1<<PCIE0;	// PCINT0 select
	PCMSK0 |= 1<<PCINT0;
	rf_decode.rf_id = id;	
	rf_decode.rf_stage = 0;
	rf_decode.rf_timer = 0;
	rf_decode.rf_data = 0;
	rf_decode.rf_count_bit = 0;	
}

void RF_decode_setup(uint16_t start_frame_time ,uint8_t percent)
{
	rf_decode.rf_min_start = (start_frame_time*(100-percent))/100;
	rf_decode.rf_max_start = (start_frame_time*(100+percent))/100;
	rf_decode.rf_min_wide = rf_decode.rf_min_start/10;
	rf_decode.rf_max_wide = rf_decode.rf_max_start/10;
	rf_decode.rf_min_narow = rf_decode.rf_min_wide/3;
	rf_decode.rf_max_narow = rf_decode.rf_max_wide/3;
}

void RF_decode_stop()
{
	PCICR &=~(1<<PCIE0);	// PCINT0 disable	
}

void RF_decode_start()
{
	rf_decode.rf_stage = 0;
	PCICR |=(1<<PCIE0);		// PCINT0 enable
}

void delay_50us(unsigned int val)
{
	x_counter = val;
	while(x_counter!=0){};
}

void set_ms_counter(unsigned int val)
{
	cli();
	x_counter = val;
	sei();
}

unsigned char check_ms_counter(void)
{
	if (x_counter!=0) return 0;
	return 1;
}

void timer0_init(void)
{
	TIMSK0 |= (1 << OCIE0A);			// COMA     
	TCCR0A |= (1 << WGM01);				//CTC mode
	TCCR0B |= 1<<CS01;					//		clk/8	
	OCR0A   = 99;						 //		50us
	sei();
}
unsigned char RF_get_key(void)
{
	return rf_decode.rf_key;
}
void RF_clear_key(void)
{
	rf_decode.rf_key = 0;
}

ISR(TIMER0_COMPA_vect)
{
	//PORTD^=1<<PORTD4;
	wdt_reset();
	if(x_counter!=0) x_counter--;
	if(rf_decode.rf_timer<500) rf_decode.rf_timer++;
}

ISR(PCINT0_vect)
{
	switch (rf_decode.rf_stage)
	{
		case 0:
		if (!(PIN_RF&(1<<IN_RF)))
		{
			rf_decode.rf_count_bit=0;
			rf_decode.rf_data = 0;
			rf_decode.rf_stage=1;
			rf_decode.rf_timer=0;
		}
		break;
		case 1:
		if ((rf_decode.rf_timer>=rf_min_range) && (rf_decode.rf_timer<rf_max_range))
		{
			if (rf_decode.rf_check==0) RF_decode_setup(rf_decode.rf_timer,25);
			
			if ((rf_decode.rf_timer>=rf_decode.rf_min_start) && (rf_decode.rf_timer<rf_decode.rf_max_start))  //250x50= 12.5ms
			{
				 rf_decode.rf_stage = 2;  
				 rf_decode.rf_timer = 0;
			}
			else 
				{
					rf_decode.rf_stage =0;
					 rf_decode.rf_check = 0;
				 }
		}
		else rf_decode.rf_stage =0;
		break;
		case 2:
		if (!(PIN_RF&(1<<IN_RF)))
		{
			if ((rf_decode.rf_timer>=rf_decode.rf_min_narow) && (rf_decode.rf_timer<rf_decode.rf_max_narow)) rf_decode.rf_stage = 3;
			else if ((rf_decode.rf_timer>=rf_decode.rf_min_wide)&&(rf_decode.rf_timer<rf_decode.rf_max_wide)) rf_decode.rf_stage = 4;
			else rf_decode.rf_stage =0;
	
		}
		else rf_decode.rf_stage = 0;
		break;
		case 3:
			rf_decode.rf_stage = 5;
			rf_decode.rf_timer = 0;
		break;
		case 4:
			rf_decode.rf_stage = 6;
			rf_decode.rf_timer = 0;
		break;
		case 5:
		if (!(PIN_RF&(1<<IN_RF)))
		{
			if ((rf_decode.rf_timer>=rf_decode.rf_min_narow) && (rf_decode.rf_timer<rf_decode.rf_max_narow))
			{
				 rf_decode.rf_data <<= 1; //  bit 0
				 rf_decode.rf_stage = 7;
			}
			else if ((rf_decode.rf_timer>=rf_decode.rf_min_wide)&&(rf_decode.rf_timer<rf_decode.rf_max_wide))
			{
				 rf_decode.rf_data<<=1;//bit float = bit 0
				 rf_decode.rf_stage = 7;
			}
			else rf_decode.rf_stage =0;
			
				 
				
			
		}
		else rf_decode.rf_stage =0;
		break;
		case 6:
		if (!(PIN_RF&(1<<IN_RF)))
		{
			if ((rf_decode.rf_timer>=rf_decode.rf_min_wide)&&(rf_decode.rf_timer<rf_decode.rf_max_wide)) 
			{
				 rf_decode.rf_data <<= 1;
				 rf_decode.rf_data|=1;	//  bit 1
				 rf_decode.rf_stage = 7;
			}
			else rf_decode.rf_stage =0;
		}
		else rf_decode.rf_stage =0;
		break;
		case 7:
				rf_decode.rf_count_bit++;
				rf_decode.rf_stage = 2;  
				rf_decode.rf_timer = 0;
		break;
		default:
		
		
		break;
	}
	if (rf_decode.rf_count_bit>=rf_data_len) 
	{
		if ((rf_decode.rf_data>>4)==(unsigned int)rf_decode.rf_id) rf_decode.rf_key=rf_decode.rf_data & 0x000f;
		rf_decode.rf_count_bit=0;
		rf_decode.rf_stage =0;
		rf_decode.rf_check = 1;
	}
}
