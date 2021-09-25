/*
 * pwm6ch.c
 *
 * Created: 6/4/2015 8:28:50 AM
 *  Author: admin
 */ 


#include "pwm6ch.h"
#include <avr/io.h>

//timer 0 pwm_phasecorect

void pwm_phasecorrect_timer0_initial(unsigned char clk)
{
	DDRD |=(1<<PORTD5)|(1<<PORTD6); // OC0A,OC0B IS OUTPUT
	TCCR0A = (0<<COM0A0)| (1<<COM0A1)| (0<<COM0B0)| (1<<COM0B1)| (1<<WGM00);
	TCCR0B = (0<<WGM02)|(clk<<CS00);
	TCNT0 = 0;
	OCR0A = 0;
	OCR0B = 0;
}



void pwm_phasecorrect_timer0_OCR0A_updata(unsigned char	val)
{
	OCR0A = val;	
}

void pwm_phasecorrect_timer0_OCR0B_updata(unsigned char val)
{
	
	OCR0B =val;
}


//timer 1 pwm_phasecorect
void pwm_phasecorrect_timer1_initial(unsigned char clk)
{
	DDRB |=(1<<PORTB2)|(1<<PORTB1); // OC1A,OC1B IS OUTPUT
	TCCR1A = (0<<COM1A0)| (1<<COM1A1)| (0<<COM1B0)| (1<<COM1B1)| (1<<WGM10);
	TCCR1B =(clk<<CS00);
	TCNT1 = 0;
	OCR1A = 0;
	OCR1B = 0;
}


void pwm_phasecorrect_timer1_OCR1A_updata(unsigned char	val)
{
	OCR1A = val;	
}

void pwm_phasecorrect_timer1_OCR1B_updata(unsigned char val)
{
	
	OCR1B =val;
}




//timer 2 pwm_phasecorect
void pwm_phasecorrect_timer2_initial(unsigned char clk)
{
	 // OC2A,OC2B IS OUTPUT
	DDRB |=(1<<PORTB3);
	DDRD |=(1<<PORTD3);
	
	TCCR2A = (0<<COM2A0)| (1<<COM2A1)| (0<<COM2B0)| (1<<COM2B1)| (1<<WGM20);
	TCCR2B =(clk<<CS00);
	TCNT2 = 0;
	OCR2A = 0;
	OCR2B = 0;
}

void pwm_phasecorrect_timer2_OCR2A_updata(unsigned char	val)
{
	OCR2A = val;	
}

void pwm_phasecorrect_timer2_OCR2B_updata(unsigned char val)
{
	OCR2B =val;
}



void pwm_phasecorrect_6ch_updata(unsigned char ch1,unsigned char ch2,unsigned char ch3,unsigned char ch4,unsigned char ch5,unsigned char ch6)
{
	
		pwm_phasecorrect_timer2_OCR2A_updata(ch1);
		pwm_phasecorrect_timer1_OCR1B_updata(ch2);
		pwm_phasecorrect_timer1_OCR1A_updata(ch3);
		pwm_phasecorrect_timer0_OCR0A_updata(ch4);
		pwm_phasecorrect_timer0_OCR0B_updata(ch5);
		pwm_phasecorrect_timer2_OCR2B_updata(ch6);
}

