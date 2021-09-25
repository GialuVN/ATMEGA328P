/*
 * triac_driver.c
 *
 * Created: 7/23/2014 8:53:12 AM
 *  Author: GIA
 */ 


#include "triac_driver.h"
/*
 * PWM.c
 *
 * Created: 1/7/2015 10:42:04 AM
 *  Author: GIA
 */ 
volatile uint8_t channel_buff[DATA_LEN];
volatile uint8_t _counter;
volatile uint8_t _pointer;

///updata 050815
volatile uint8_t _mapB;
volatile uint8_t _mapC;
volatile uint8_t _mapD;


void output_init()
{
	DDRB |= S_MASK_PB;//pinB 0,1,2,3,4,5
	DDRC |= S_MASK_PC;//pinC 0,1,2,3,4,5
	DDRD |= S_MASK_PD;//pinD 4,5,6,7
}

///updata 050815

void output_off_all()
{
	PORTB &= C_MASK_PB|_mapB; //pinB 0,1,2,3,4,5
	PORTC &= C_MASK_PC|_mapC; //pinC 0,1,2,3,4,5
	PORTD &= C_MASK_PD|_mapD;//pinD 4,5,6,7
}

void timer2_CTC_init()
{
	TIMSK2 |= (1 << OCIE0A);                    // set output compare interrupt enable
	TCCR2A |= (1 << WGM21);
	TCCR2B |= TIMER2_PRESCALER;				// set CTC mode
	OCR2A   = TIMER2_COMPARE_VALUE;            // set compare value for interrupt
	sei();
}


///updata 050815
void output_updata(unsigned char *_data)
{
	_mapB=0;
	_mapC=0;
	_mapD=0;
	for (unsigned char i= 0;i<DATA_LEN;i++)
	{
		channel_buff[i]= _data[i];
		if (channel_buff[i]>=MAX_COUNT) map_maker(i);
	}
}

ISR(TIMER2_COMPA_vect)
{
	 _pointer = 0;
	 if (_counter==0)
	 {
		 output_off_all();
		 _counter=MAX_COUNT;
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


///updata 050815
void map_maker(unsigned char _mux)
{
	switch (_mux)
	{
		case 0:
		_mapC |=S_MASK_5;
		return;
		case 1:
		_mapC |=S_MASK_4;
		return;
		case 2:
		_mapC |=S_MASK_3;
		return;
		case 3:
		_mapC |=S_MASK_2;
		return;
		case 4:
		_mapC |=S_MASK_1;
		return;
		case 5:
		_mapC |=S_MASK_0;
		return;
		case 6:
		_mapB |=S_MASK_5;
		return;
		case 7:
		_mapB |=S_MASK_4;
		return;
		case 8:
		_mapB |=S_MASK_3;
		return;
		case 9:
		_mapB |=S_MASK_2;
		return;
		case 10:
		_mapB |=S_MASK_1;
		return;
		case 11:
		_mapB |=S_MASK_0;
		return;
		case 12:
		_mapD |=S_MASK_7;
		return;
		case 13:
		_mapD |=S_MASK_6;
		return;
		case 14:
		_mapD |=S_MASK_5;
		return;
		default:
		_mapD |=S_MASK_4;
		return;
	}
}

