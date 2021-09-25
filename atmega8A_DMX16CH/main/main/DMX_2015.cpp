/*
 * DMX_2015.cpp
 *
 * Created: 10/9/2015 8:54:36 AM
 *  Author: RnD
 */ 

#include "DMX_2015.h"

volatile uint8_t dmx_data_buff[DMX_LEN];
volatile DMX_DATA dmx_data;
volatile uint8_t _dmx_temp;
void DMX_USART_Init( unsigned int ubrr)
{
		DDRD &=~(1<<PIND0);
		PORTD |=(1<<PIND0);
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1<<RXEN)|(1<<RXCIE);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
	/* Enable recvice */
}

/************************************************************************/
/* in: 1 to 9999
                                                                     */
/************************************************************************/

uint16_t DMX_get_address(void)
{
	return dmx_data.address;
}

void DMX_data_reset(uint16_t dmx_adress)
{
	dmx_data.address = dmx_adress-1;
	dmx_data.counter = 0;
	dmx_data.data_count = 0;
	dmx_data.check_complete = false;
	dmx_data.check_complete = true;
	dmx_data.stage = 255;
}
/************************************************************************/
/* out:
	0: no new data
	1: new data display
	2: new data control
	3: too long data request
	                                                                     */
/************************************************************************/

uint8_t DMX_get_data(volatile uint8_t *data,uint8_t len)
{
	if (len>DMX_LEN) return 0;
	if (dmx_data.check_complete==true)
	{
		dmx_data.check_complete=false;
		if (dmx_data.command==DTA)
		{
			for (uint8_t i = 0;i<len;i++) data[i] = dmx_data_buff[i];
			dmx_data.enable = true;
			return 1;
		}
		else if (dmx_data.command==CTR)
		{
			for (uint8_t i = 0;i<len;i++) data[i] = dmx_data_buff[i];
			dmx_data.enable = true;
			return 2;
		}
	}
	dmx_data.enable = true;
	return 0;
	
}


ISR(USART_RXC_vect)
{
	if (dmx_data.enable==true)
	{

		if (UCSRA & FE_MASK)
		{
			dmx_data.counter = 0;
			dmx_data.data_count = 0;
			dmx_data.stage = 0;
		}
	
		_dmx_temp = UDR;
		switch (dmx_data.stage)
		{
			case 0:
			dmx_data.stage = 1;
			break;
			case 1:
			if ((_dmx_temp==DTA) || (_dmx_temp==CTR))
			{
				if (_dmx_temp==DTA) dmx_data.address_buffer = dmx_data.address;
				else dmx_data.address_buffer = 0;
				dmx_data.command =_dmx_temp;
				dmx_data.stage = 2;
			}
			else dmx_data.stage = 255;
			break;
			case 2:
			if (dmx_data.counter>=dmx_data.address_buffer)
			{
				dmx_data_buff[dmx_data.data_count] = _dmx_temp;
				dmx_data.data_count++;
				if (dmx_data.data_count>=DMX_LEN)
				{
					dmx_data.enable = false;
					dmx_data.check_complete = true;
					dmx_data.stage = 255;
				}
			}
			else dmx_data.counter++;
			break;
			default:
			break;
		}
	}
	else _dmx_temp = UDR;

}




bool DMX_Frame_CheckSum(uint8_t *_data,uint8_t len)
{
	uint8_t _crc =0;
	for (uint8_t i = 0;i<len;i++) _crc = _crc_ibutton_update(_crc,_data[i]);
	if (_crc==0) return true;
	return false;
}