/*
 * triac_driver.c
 *
 * Created: 7/23/2014 8:53:12 AM
 *  Author: GIA
 */ 


#include "triac_driver.h"

volatile uint8_t data_driver[TRIAC_DATA_LEN];
volatile uint8_t data_buff[TRIAC_DATA_LEN];
volatile uint16_t _counter_syn;
volatile uint8_t _counter;
volatile bool enable;
volatile bool data_enable;

void output_off_all()
{
	
	PORTB &= C_MASK_PB; //pinB 0,1,2,3,4,5
	PORTC &= C_MASK_PC; //pinC 0,1,2,3,4,5
	PORTD &= C_MASK_PD;//pinD 4,5,6,7
}

void dimmer_init(void)
{
	
	TIMSK |= (1 << OCIE2);                    // set output compare interrupt enable
	TCCR2 |= (1 << WGM21) | TIMER2_PRESCALER; // set CTC mode
	OCR2   = TIMER2_COMPARE_VALUE;            // set compare value for interrupt
	
	DDRD &= ~(1<<PIND2);	//int0
	PORTD |= (1<<PIND2);	
	
	MCUCR |= 1<<ISC01;		// fall edge
	GICR |= 1<<INT0;
	
	DDRD |= 1<<PIND1;		//led 
	
	DDRB |= S_MASK_PB;//pinB 0,1,2,3,4,5
	DDRC |= S_MASK_PC;//pinC 0,1,2,3,4,5
	DDRD |= S_MASK_PD;//pinD 4,5,6,7
	sei();
}

void dimmer_updata(volatile const uint8_t *data)
{
	unsigned char _i;
	for (uint8_t i = 0;i<TRIAC_DATA_LEN;i++)
	{
		_i=data[i]/5;
		if (_i>RESOLUTION) data_buff[i]=RESOLUTION;
		else data_buff[i]=_i;
	}
	data_enable = true;
}

void dimmer_updata_direct(volatile const uint8_t *data)
{
	for (uint8_t i = 0;i<TRIAC_DATA_LEN;i++) data_buff[i]=data[i];
	data_enable = true;
}

ISR(TIMER2_COMP_vect)
{
	uint8_t _pointer = 0;
	if (_counter_syn>=2000) PORTD &=~(1<<PIND1);
	else _counter_syn++;
	
	if (enable)
	{
		while (_pointer<TRIAC_DATA_LEN)
		{
			if ( _counter<data_driver[_pointer]) pin_table(_pointer);
			_pointer++;
		}
		if (_counter<=trimming)
		{
			 output_off_all();
			 enable = false;
		}
		_counter--;
	}
}

ISR(INT0_vect)
{
	wdt_reset();
	uint8_t debounce = debo;
	if (PIND &(S_PD2)) return;
	if (!(PIND &(S_PD2)))
	{
		while (debounce!=0)
		{
			if (PIND &(S_PD2)) return;
			_delay_us(1);
			debounce--;
		}
	}
	output_off_all();
	if (data_enable==true)
	{
		for (uint8_t i = 0;i<TRIAC_DATA_LEN;i++) data_driver[i]=data_buff[i];
		data_enable = false;
	}
	_counter = RESOLUTION;
	PORTD ^=1<<PIND1;
	_counter_syn = 0;
	enable = true;
}

void pin_table(uint8_t pins)
{
	switch (pins)
	{
		case 0:
			PORTC |=S_MASK_5;
		return;
		case 1:
			PORTC |=S_MASK_4;
		return;
		case 2:
			PORTC |=S_MASK_3;
		return;
		case 3:
			PORTC |=S_MASK_2;
		return;
		case 4:
			PORTC |=S_MASK_1;
		return;
		case 5:
			PORTC |=S_MASK_0;
		return;
		case 6:
			PORTB |=S_MASK_5;
		return;
		case 7:
			PORTB |=S_MASK_4;
		return;
		case 8:
			PORTB |=S_MASK_3;
		return;
		case 9:
			PORTB |=S_MASK_2;
		return;
		case 10:
			PORTB |=S_MASK_1;
		return;
		case 11:
			PORTB |=S_MASK_0;
		return;
		case 12:
			PORTD |=S_MASK_7;
		return;
		case 13:
			PORTD |= S_MASK_6;
		return;
		case 14:
			PORTD |=S_MASK_5;
		return;
		default:
			PORTD |=S_MASK_4;
		return;
	}
}

