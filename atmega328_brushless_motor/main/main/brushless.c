/*
 * brushless.c
 *
 * Created: 10/2/2015 9:02:09 AM
 *  Author: RnD
 */ 

#include "brushless.h"
void burshless_init()
{
	TIMSK2 |= (1 << OCIE0A);					 // set output compare interrupt enable
	TCCR2A |= (1 << WGM21);						// set CTC mode
	TCCR2B |= TIMER2_PRESCALER;					//CLK/32
	OCR2A   = TIMER2_COMPARE_VALUE;				// set compare value for interrupt
	//interrupt initial
	DDR_S &= ~(1<<PINx_S);
	PORT_S |=1<<PINx_S;
	PCICR = 1<<PCIE1;	// PCINT10 select
	PCMSK1 = 1<<PCINT10;
	//motor initial
	DDR_M |= 1<<PINx_M;
	PORT_M |= 1<<PINx_M;
	sei();
}


ISR(PCINT1_vect)
{
	//
	//if (PIN_S&(1<<PINx_S))
	//{
		//PORT_M |= 1<<PINx_M;
	//}
	//else
	//{
		//PORT_M &=~( 1<<PINx_M);
	//}
	//
	

}



ISR(TIMER2_COMPA_vect)
{
	
	PORT_M ^=1<<PINx_M;
	
}
