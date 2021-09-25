/*
 * GccApplication1.c
 *
 * Created: 7/26/2016 7:46:37 AM
 * Author : RnD
 */ 

#define F_CPU 1000000UL	
#include <util/delay.h>
#include <avr/io.h>
//relay
#define RL_DDR DDRB
#define RL_POT PORTB	
#define RL_PIN PINB3
//rf out
#define RF_DDR DDRD
#define RF_POT PORTD
#define RF_PIN PIND2
//switch in
#define IN_DDR DDRC
#define IN_PINP PINC
#define IN_PIN PINC3
#define IN_POT PORTC

bool _flip;
void start_frame(void);
void break_gen(void);
void byte_gen(unsigned char _byte);
int main(void)
{
	RF_DDR |= 1<<RF_PIN;
	RL_DDR |= 1<<RL_PIN;
	IN_DDR &=~(1<<IN_PIN);
	IN_POT |=1<<IN_PIN;
	RF_POT &=~(1<<RF_PIN);
	RL_POT &=~(1<<RL_PIN);
	_delay_ms(5000);
	for (unsigned int i = 0;i<200;i++)
	{
		if (IN_PINP&(1<<IN_PIN))
		{
			if (i>=100)
			{
				_flip = true;
				break;
			}
		}
		else break;
		_delay_ms(50);
	}
	
	for (unsigned int i = 0;i<200;i++)
	{
		if (!(IN_PINP&(1<<IN_PIN)))
		{
			if (i>=100)
			{
				_flip = false;
				break;
			}
		}
		else break;
		_delay_ms(50);
	}
    /* Replace with your application code */
    while (1) 
    {
		for (unsigned int i = 0;i<200;i++)
		{
			if (IN_PINP&(1<<IN_PIN))
			{
				if (i>=100)
				{
					if (_flip)
					{
						start_frame();
						for (unsigned char j = 0;j<100;j++)
						{
							break_gen();
							byte_gen(24);
							byte_gen(122);
							byte_gen(198);
						}
						_flip = false;
						break;
					}
					
				}
			}
			else break;
			_delay_ms(50);
		}
		
		for (unsigned int i = 0;i<200;i++)
		{
			if (!(IN_PINP&(1<<IN_PIN)))
			{
				if (i>=100)
				{
					if (!_flip)
					{
							start_frame();
							for (unsigned char j = 0;j<100;j++)
							{
								break_gen();
								byte_gen(198);
								byte_gen(24);
								byte_gen(122);
							}
						_flip = true;
						break;
					}
					
				}
			}
			else break;
			_delay_ms(50);
		}
		
    }
}



void start_frame(void)
{
	RF_POT |=(1<<RF_PIN);
	_delay_ms(14400);
}

void break_gen(void)
{
	RF_POT &=~(1<<RF_PIN);
	_delay_ms(14400);
	
}
void byte_gen(unsigned char _byte)
{
	for (char i=0;i<8;i++)
	{
		if (_byte&(1<<(7-i)))
		{
			RF_POT |=(1<<RF_PIN);
			_delay_us(1440);
			RF_POT &=~(1<<RF_PIN);
			_delay_us(480);
			
			
		}
		else
		{
			
			RF_POT |=(1<<RF_PIN);
			_delay_us(480);
			RF_POT &=~(1<<RF_PIN);
			_delay_us(1440);
			
		}
	}
}

