/*
 * DMX512A.cpp
 *
 * Created: 11/3/2015 2:08:35 PM
 *  Author: RnD
 */ 

#include "DMX512A.h"
void DMX512A_init(void);
void DMX512A_send_break_mab(void);
void DMX512A_send_byte(uint8_t val);

void DMX512A_init(void)
{
	DDR_OUT |= PIN_MASK_POS;
	POR_OUT |= PIN_MASK_POS;
}
void DMX512A_send_break_mab(void)
{
	 POR_OUT &=PIN_MASK_NEG;
	 _delay_us(176);
	POR_OUT |=PIN_MASK_POS;
	 _delay_us(12);
}
void DMX512A_send_byte(uint8_t val)
{
	 POR_OUT &=PIN_MASK_NEG;
		 _delay_us(3);
			 nop();
			 nop();
			 nop();
			 nop();
			 nop();
			 nop();
			 nop();
	for (uint8_t i = 0;i<8;i++)
	{
		if (val&0x01)
		{
			 POR_OUT |=PIN_MASK_POS;
			 nop();
			 nop();
			 nop();
			 nop();
			 nop();
		}
		else
		{
			 POR_OUT &=PIN_MASK_NEG;
			  nop();
			  nop();
			  nop();
			  nop();
			  nop();
			  nop();
			  nop();
		}
		_delay_us(3);
		val>>=1;
	}
	 POR_OUT |=PIN_MASK_POS;
		 _delay_us(7);
			 nop();
			 nop();
}

void DMX512A_send(uint8_t *data,uint16_t len)
{
	DMX512A_send_break_mab();
	DMX512A_send_byte(0);
	for (uint16_t i = 0;i<len;i++) DMX512A_send_byte(data[i]);
}



/************************************************************************/
/* EFFECTS                                                                     
*/
/************************************************************************/


void rota(uint8_t bot,uint8_t top,volatile uint8_t *data,uint8_t dir)
{
	uint8_t _buff;
	
	if (dir)
	{
		_buff=data[bot];
		for (uint8_t i = 0;i<(top-bot);i++)
		{
			data[i+bot]=data[bot+i+1];
		}
		
		data[top] = _buff;
	}
	
	else
	{
		_buff=data[top];
		for (uint8_t i = 0;i<(top-bot);i++)
		{
			data[top-i]=data[top-1-i];
		}
		data[bot] = _buff;
	}
}


void soft_change(uint8_t bot,uint8_t top,uint8_t *data,uint8_t speed,uint8_t from_val,uint8_t to_val)
{
	if (from_val==to_val) return;
	if (from_val>to_val)
	{
		while (from_val>to_val)
		{
			set_val(bot,top,data,from_val);
			DMX512A_send(data,DMX_CH);
			sleep(speed);
			from_val--;
		}
		
	}
	
	else
	{
		while (from_val<to_val)
		{
			set_val(bot,top,data,from_val);
			DMX512A_send(data,DMX_CH);
			sleep(speed);
			from_val++;
		}
	}
}



void sleep(uint16_t val)
{
	for (uint16_t i = 0;i<val;i++) _delay_ms(1);

}


void set_val(uint8_t bot,uint8_t top,volatile uint8_t *data,uint8_t val)
{
	for (uint8_t i = 0; i <(top-bot+1); i++) data[bot+i] = val;
}


/************************************************************************/
/* END EFFECTS
                                                                     */
/************************************************************************/