/*
 * pt2260_dec.c
 *
 * Created: 6/10/2015 2:19:27 PM
 *  Author: admin
 */ 

#include "pwm6ch.h"
#include "pt2260_dec.h"

volatile RF_DECODE rf_decode;

void RF_decode_initial(unsigned char id)
{
	DDR_RF &= ~(1<<IN_RF);
	POR_RF |=1<<IN_RF;
	PCICR = 1<<PCIE0;	// PCINT0 select
	PCMSK0 = 1<<PCINT0;
	PCMSK1 =0;
	PCMSK2 =0;
	rf_decode.rf_id = id;	
}

void RF_decode_stop()
{
	PCICR &=~(1<<PCIE0);	// PCINT0 disable	
}

void RF_decode_start()
{
	PCICR |=(1<<PCIE0);		// PCINT0 enable
}



unsigned char RF_decode_read() //rf_key read back
{
	return rf_decode.rf_data;
}

static unsigned char RF_decode(void)
{
	unsigned int _data = 0;
	unsigned char _counter = 0;
	
	
	while(1)
	{
		while (!(PIN_RF&(1<<IN_RF))) {}; // waitting 1
			_delay_us(2*rf_1a);
			
			if (PIN_RF&(1<<IN_RF))
			{
				while (PIN_RF&(1<<IN_RF)) {}; //waitting 0
				while (!(PIN_RF&(1<<IN_RF))) {}; // waitting 1
				_delay_us(2*rf_1a);
				if (PIN_RF&(1<<IN_RF))
				{
					//bit 1 detected
					_data <<=1;
					_data|=1;
					while (PIN_RF&(1<<IN_RF)) {}; //waitting 0
				}
				else return 0;
			}
			else
			{
				while (!(PIN_RF&(1<<IN_RF))) {}; // waitting 1
				_delay_us(2*rf_1a);
				if (!(PIN_RF&(1<<IN_RF)))
				{
					//bit 0 detected
					_data <<=1;
				}
				else 
				{
					//floating detected  = 1
					_data <<=1;
					_data|=1;
					while (PIN_RF&(1<<IN_RF)) {}; //waitting 0
				}
			}
				_counter++;
				if (_counter>=rf_data_len)
				{
					if ((_data>>4)==(unsigned int)rf_decode.rf_id) return _data &=0x000f;
					else return 0;
				}
		}
		return 0;
}

ISR(PCINT0_vect)
{
	unsigned char _temp_data;
	// start condition detector
	if (!(PIN_RF&(1<<IN_RF)))
	{
		_delay_ms(12);
		if (!(PIN_RF&(1<<IN_RF))) 
		{
			_temp_data = RF_decode();
			if (_temp_data!=0)
			{
				 rf_decode.rf_data = _temp_data;
				 RF_decode_stop();// removeable
			}
			
		}
	}
}
