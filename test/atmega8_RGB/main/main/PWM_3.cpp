/*
 * PWM_3.cpp
 *
 * Created: 10/9/2015 3:21:23 PM
 *  Author: RnD
 */ 
#include "PWM_3.h"

void timer1SetPrescaler(uint8_t prescale)
{
	// set prescaler on timer 1
	TCCR1B &=~TIMER_PRESCALE_MASK;
	TCCR1B |=prescale;
}

void timer2SetPrescaler(uint8_t prescale)
{
	// set prescaler on timer 2
	TCCR2 &=~TIMER_PRESCALE_MASK;
	TCCR2 |=prescale;
	
}

void timer2PWMInit()
{
	// configures timer1 for use with PWM output
	TCCR2|=1<<COM21;
	TCCR2 &=~(1<<COM20);
	OCR2 = 0;
}

void timer2PWMInitICR()

{
	// set PWM mode with ICR defalult = 0xff
	
	TCCR2|=1<<WGM20;
	TCCR2 &=~(1<<WGM21);
	OCR2 = 0;
}

void timer2PWMSet(uint8_t pwmDuty)
{
	OCR2 = pwmDuty;
}

void timer2PWMOff(void)
{
	// turn off channel A (OC2) PWM output
	// set OC2 (OutputCompare action) to none
	
	TCCR2 &=~(1<<COM21);
	TCCR2 &=~(1<<COM20);
}

void timer2PWMOn(void)
{
	// turn on channel C (OC2) PWM output
	// set OC2 as non-inverted PWM
	TCCR2 |=1<<COM21;
	TCCR2 &=~(1<<COM20);
	
	DDRB |=1<<PB3;
}

void timer1PWMInit(void)
{
	//// configures timer1 for use with PWM output
	
	TCCR1A |=1<<WGM11;
	TCCR1A &=~(1<<WGM10);
	
	OCR1AH = 0;
	OCR1AL = 0;
	OCR1AH = 0;
	OCR1AL = 0;
}

void timer1PWMInitICR(uint16_t topcount)
{
	// set PWM mode with ICR top-count
	TCCR1A |=1<<WGM10;
	TCCR1A &=~(1<<WGM11);
	TCCR1B &=~((1<<WGM12)|(1<<WGM13));
	ICR1 = topcount;
	// clear output compare value A
	OCR1A = 0;
	// clear output compare value B
	OCR1B = 0;
}

void timer1PWMOff(void)
{
	//// turn off timer1 PWM mode
	TCCR1A &=~((1<<WGM11)|(1<<WGM10));
	// set PWM1A/B (OutputCompare action) to none
	timer1PWMAOff();
	timer1PWMBOff();
}

void timer1PWMAOn(void)
{
	// turn on channel A (OC1A) PWM output
	// set OC1A as non-inverted PWM
	TCCR1A |= 1<<COM1A1;
	TCCR1A &=~(1<<COM1A0);
	DDRB |=1<<PB1;
}

void timer1PWMBOn(void)
{
	// turn on channel B (OC1B) PWM output
	// set OC1B as non-inverted PWM
	TCCR1A |= 1<<COM1B1;
	TCCR1A &=~(1<<COM1B0);
	DDRB |=1<<PB2;
}

void timer1PWMAOff(void)
{
	// turn off channel A (OC1A) PWM output
	// set OC1A (OutputCompare action) to none
	TCCR1A &=~(1<<COM1A1);
	TCCR1A &=~(1<<COM1A0);
}

void timer1PWMBOff(void)
{
	// turn off channel B (OC1B) PWM output
	// set OC1B (OutputCompare action) to none
	TCCR1A &=~(1<<COM1B1);
	TCCR1A &=~(1<<COM1B0);
	
}

void timer1PWMASet(uint16_t pwmDuty)
{
	OCR1A = pwmDuty;
}

void timer1PWMBSet(uint16_t pwmDuty)
{
	OCR1B = pwmDuty;
}
