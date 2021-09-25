/*
 * main.cpp
 *
 * Created: 10/9/2015 3:21:00 PM
 * Author : RnD
 */ 


#include <avr/io.h>
#include "effect_RGB.h"
#include "PWM_3.h"
#include <avr/eeprom.h>
unsigned char mode EEMEM = 0xAA; 
unsigned char gray EEMEM = 1;
unsigned char speed EEMEM = 1;

bool check = false;
unsigned char _how = 0;
unsigned char _inc = 0;
unsigned char temp1 = 0;  
unsigned char _mode = 0;
unsigned char _gray = 0;
unsigned char _speed = 0;
unsigned char _value[] ={1,5,25,50,125,150,200,255};
	void delayms(unsigned int val);
int main(void)
{
	timer1SetPrescaler(TIMER_CLK_DIV64);
	timer1PWMInit();
	timer1PWMInitICR(255);
	timer1PWMBOn();
	timer1PWMAOn();
	timer2SetPrescaler(TIMER_CLK_DIV64);
	timer2PWMInit();
	timer2PWMInitICR();
	timer2PWMOn();
	timer1PWMASet(0);
	timer1PWMBSet(0);
	timer2PWMSet(0);
    /* Replace with your application code */
	
	
	DDRC &=~(1<<PORTC5);
	eeprom_busy_wait();
	temp1 = eeprom_read_byte(&mode); // read 
	_mode = temp1;
	if (temp1 ==0xAA)
	{
		eeprom_busy_wait();
		eeprom_update_byte(&mode,0xCC);
	}
	else
	{
		eeprom_busy_wait();
		eeprom_update_byte(&mode,0xAA);
	}
	
	eeprom_busy_wait();
	_gray = eeprom_read_byte(&gray); // read 
	eeprom_busy_wait();
	_speed = eeprom_read_byte(&speed); // read 
	
    while (1) 
    {
		if (_mode==0xAA)
		{
			out_color(color_convert(_gray,_gray,_gray));
			
			if (!(PINC&(1<<PINC5)))
			{
				for (unsigned char i = 0;i<200;i++)
				{
					if (PINC&(1<<PINC5)) break;
					if ((!(PINC&(1<<PINC5)))&& (i>=20))
					{
						out_color(color_convert(255,255,255));
						_delay_ms(500);
						out_color(color_convert(0,0,0));
						_delay_ms(500);
						out_color(color_convert(255,255,255));
						_delay_ms(500);
						out_color(color_convert(0,0,0));
						_delay_ms(500);
						while (!(PINC&(1<<PINC5))){_delay_ms(250);};
							
						_how = 0;
						_inc = 0;
						out_color(color_convert(_inc,_inc,_inc));
						while (1)
						{
						_delay_ms(250);
						if (!(PINC&(1<<PINC5)))
						{
						_gray = _value[_inc];
						out_color(color_convert(_gray,_gray,_gray));
						_inc++;
						if (_inc>=8) _inc=0;
							for (unsigned char j = 0;j<200;j++)
							{
								if (PINC&(1<<PINC5)) break;
								if ((!(PINC&(1<<PINC5)))&& (j>=20))
								{
									
									out_color(color_convert(255,255,255));
									_delay_ms(200);
									out_color(color_convert(0,0,0));
									_delay_ms(200);
									out_color(color_convert(255,255,255));
									_delay_ms(200);
									out_color(color_convert(0,0,0));
									_delay_ms(200);
									eeprom_busy_wait();
									eeprom_update_byte(&gray,_gray);
									while (!(PINC&(1<<PINC5))){_delay_ms(250);};
									_how = 2;
									break;
								}
								_delay_ms(250);
							}
						}
						
							if (_how ==2) break;
							
						}
						
						break;
					}
					
					_delay_ms(250);
				}
				
				
			}
			
		}
		else
		{
			
			for (unsigned int i = 0;i<256;i++)
			{
					out_color(color_convert(i,i,i));
					delayms(_speed);
					if (!(PINC&(1<<PINC5)))
					{
						if (_speed>=20) _speed = 1;
						else _speed++;
						i = 0;
							for (unsigned char j = 0;j<200;j++)
							{
								if (PINC&(1<<PINC5)) break;
								if ((!(PINC&(1<<PINC5)))&& (j>=20))
								{
									_speed--;
									
									out_color(color_convert(255,255,255));
									_delay_ms(200);
									out_color(color_convert(0,0,0));
									_delay_ms(200);
									out_color(color_convert(255,255,255));
									_delay_ms(200);
									out_color(color_convert(0,0,0));
									_delay_ms(200);
									eeprom_busy_wait();
									eeprom_update_byte(&speed,_speed);
									while (!(PINC&(1<<PINC5))){_delay_ms(250);};
								}
								_delay_ms(250);
							}
					}
				
			}
			
			delayms(500+_speed*10);
			
			for (unsigned int i = 0;i<256;i++)
			{
				out_color(color_convert(255-i,255-i,255-i));
				delayms(_speed);
				if (!(PINC&(1<<PINC5)))
				{
					if (_speed>=20) _speed = 1;
					else _speed++;
					i = 0;
					for (unsigned char j = 0;j<200;j++)
					{
						if (PINC&(1<<PINC5)) break;
						if ((!(PINC&(1<<PINC5)))&& (j>=20))
						{
							_speed--;
							out_color(color_convert(255,255,255));
							_delay_ms(200);
							out_color(color_convert(0,0,0));
							_delay_ms(200);
							out_color(color_convert(255,255,255));
							_delay_ms(200);
							out_color(color_convert(0,0,0));
							_delay_ms(200);
							eeprom_busy_wait();
							eeprom_update_byte(&speed,_speed);
							while (!(PINC&(1<<PINC5))){_delay_ms(250);};
						}
						_delay_ms(250);
					}
				}
				
			}
			
			delayms(500+_speed*10);
		
		}
    }
}


void delayms(unsigned int val)
{
	for (unsigned int i = 0; i < val; i++)
	{
		_delay_ms(1);
	}
	
}
