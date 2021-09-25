/*
 * PWM.c
 *
 * Created: 1/7/2015 10:42:04 AM
 *  Author: GIA
 */ 

#include "PWM.h"
volatile uint8_t channel_buff[DATA_LEN];
volatile uint8_t _counter;
volatile uint8_t _pointer;
volatile uint8_t _mapB;
volatile uint8_t _mapD;


void PWM_updata(unsigned char *_data)
{
	_mapB=0;
	_mapD=0;
	for (unsigned char i= 0;i<DATA_LEN;i++)
	{
		 channel_buff[i]= _data[i];
		 if (channel_buff[i]==RESOLUTION) map_maker(i);
	}
}


void PWM_initial(void)
{
	for(unsigned char i=0;i<DATA_LEN;i++) channel_buff[i] =0;
	output_init();
	output_off_all();
	timer2_CTC_init();
}



void output_init()
{
	DDRB |= S_MASK_PB;//pinB 1,2,3
	DDRD |= S_MASK_PD;//pinD 3,5,6
}

void output_off_all()
{
	PORTB &= C_MASK_PB|_mapB;//pinB 1,2,3
	PORTD &= C_MASK_PD|_mapD;//pinD 3,5,6
}

void timer2_CTC_init()
{
	TIMSK2 |= (1 << OCIE0A);					 // set output compare interrupt enable
	TCCR2A |= (1 << WGM21);						// set CTC mode
	TCCR2B |= TIMER2_PRESCALER;					//CLK/32
	OCR2A   = TIMER2_COMPARE_VALUE;				// set compare value for interrupt
	sei();
}

ISR(TIMER2_COMPA_vect)
{
	 _pointer = 0;
	 if (_counter==0)
	 {
		 output_off_all();
		 _counter = RESOLUTION;
	 }
	 while (_pointer<DATA_LEN)
	 {
		 if ( channel_buff[_pointer]>=_counter) pin_table(_pointer);
		 _pointer++;
	 }
	 _counter--;
}

void pin_table(uint8_t pins)
{
	switch (pins)
	{
		case 0:
		PORTB |=S_MASK_1;
		return;
		case 1:
		PORTB |=S_MASK_2;
		return;
		case 2:
		PORTB |=S_MASK_3;
		return;
		case 3:
		PORTD |=S_MASK_3;
		return;
		case 4:
		PORTD |=S_MASK_5;
		return;
		default:
		PORTD |=S_MASK_6;
		return;
	}
}


void map_maker(unsigned _mux)
{
	switch (_mux)
	{
		case 0:
		_mapB |=S_MASK_1;
		return;
		case 1:
		_mapB |=S_MASK_2;
		return;
		case 2:
		_mapB |=S_MASK_3;
		return;
		case 3:
		_mapD |=S_MASK_3;
		return;
		case 4:
		_mapD |=S_MASK_5;
		return;
		default:
		_mapD |=S_MASK_6;
		return;
	}

}
