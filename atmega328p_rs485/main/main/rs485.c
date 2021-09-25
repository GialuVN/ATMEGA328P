/*
 * rs485.c
 *
 * Created: 6/24/2015 8:56:54 AM
 *  Author: admin
 */ 
#include "rs485.h"

volatile RS485_PACK  rs_pack;
volatile RS485_CTR	 rs_ctr;
volatile RS485_flag  rs_flag;
#include "disp/xiudun2008V.h"
void RS485_initial(unsigned int ubrr,unsigned char _myaddr)// MYUBRR
{
	RS_DDR |=(1<<TXD_PIN)|(1<<TXEN_PIN);
	RS_DDR &=~(1<<RXD_PIN);
	RS_PORT |= 1<<RXD_PIN;
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable transmitter */
	UCSR0B = (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C =(1<<USBS0)|(3<<UCSZ00);
	rs_pack.my_ddr = _myaddr;
	rs_flag.all = 0;
	rs_ctr.stage = 0;
}

void RS485_TXEN(unsigned char _val)// _ENABLE || _DISABLE
{
	if (_val) RS_PORT |= 1<<TXEN_PIN;
	else RS_PORT &=~(1<<TXEN_PIN);
}

unsigned char RS485_frame_build(unsigned char *_data_in,unsigned char _data_len)// return _ERR _data_len>250
{
	if (_data_len>250) return _ERR;
	while (rs_flag.mode==_SEND){};
	rs_pack.data[0] = 0xAA;
	rs_pack.data[1] = rs_pack.my_ddr;
	rs_pack.data[2] = _data_len;
	for (unsigned int i = 0;i<_data_len;i++) rs_pack.data[3+i]=_data_in[i];
	rs_pack.data[_data_len+3] = CheckSum(rs_pack.data,_data_len+3);
	rs_pack.data[_data_len+4] = 0x55;
	rs_pack.len = _data_len+5;
	return _OK;
}


void RS485_frame_respond(unsigned char _cmd,unsigned char _val)
{
	while (rs_flag.mode==_SEND){};
	rs_pack.data[0] = 0xCC;
	rs_pack.data[1] = _cmd;
	rs_pack.data[2] = _val;
	rs_pack.data[3] = CheckSum(rs_pack.data,3);
	rs_pack.data[4] = 0x55;
	rs_pack.len = 5;
}
	void USART_Flush( void )
	{
		unsigned char dummy;
		while ( UCSR0A&(1<<RXC0) )
		{
			dummy = UDR0;
		}
	}
	
	
	void BREAK_MAB_Transmit(void)
	{
		UCSR0B &=~(1<<TXEN0);	// TXEN disable
		RS_DDR |=1<<TXD_PIN; // TXD config output port
		RS_PORT &=~(1<<TXD_PIN);	// TXD pin pull low
		_delay_us(80);				//170us
		RS_PORT |=(1<<TXD_PIN);	//TXD pin pull high
		_delay_us(8);				// 8us
		UCSR0B |=(1<<TXEN0);			//TXEN enable
	}
	
	
void RS485_sending(void)
{
	RS485_TXEN(_ENABLE);
	while( !( UCSR0A & (1<<UDRE0)));
	rs_flag.all = 0;
	rs_flag.mode = _SEND;
	rs_ctr.counter = 0;
	UDR0 = 0;
}

void RS485_reciving(void)
{
	RS485_TXEN(_DISABLE);
	rs_flag.all = 0;
	rs_ctr.stage = 0;
}

unsigned char RS485_reading(unsigned char *_data)// [len][d0][d1][d2][d3]...
{
	if ((rs_ctr.stage==255) && (rs_flag.complete==1))
	{
		if (rs_flag.error==_ERR) return 0;
		else
		{
			if (rs_flag.mode==_REC_DATA)
			{
				for (unsigned int i = 0; i <(rs_pack.data[2]+1); i++) _data[i]=rs_pack.data[i+2];
				return _REC_DATA;
			}
			if (rs_flag.mode==_REC_RESPOND)
			{
				_data[0] = 2;
				_data[1] = rs_pack.data[1];
				_data[2] = rs_pack.data[2];
				return _REC_RESPOND;
			}
		}
	}
	return 0;
}

unsigned char CheckSum(volatile unsigned char *_data_in,unsigned int _data_len)	// CRC CHECK , 255 if error
{
	unsigned char crc;
	crc = 0;
	for (unsigned int i = 0;i<_data_len;i++)
	crc = _crc_ibutton_update(crc,_data_in[i]);
	return crc;
}

ISR(USART_TX_vect)
{
	
		if (rs_flag.mode!=_SEND)  return;
	
			if (rs_ctr.counter<rs_pack.len)
			{
				while( !( UCSR0A & (1<<UDRE0)));
				UDR0 =rs_pack.data[rs_ctr.counter];
				rs_ctr.counter++;
			}
			else
			{
				
				RS485_TXEN(_DISABLE);
				 USART_Flush();
				rs_flag.complete = 1;
				rs_flag.mode=_WAIT;
			}
}




ISR(USART_RX_vect)
{
	unsigned char _temp;
	_temp = UDR0;
	if (rs_flag.mode ==_SEND) return;
	switch (rs_ctr.stage)
	{
		case 0:
		if (_temp==0xAA) rs_ctr.stage = 1;
		else if (_temp==0xCC) rs_ctr.stage = 4;
		else rs_ctr.stage = 0;
		break;
		case 1:
		
		if (_temp==rs_pack.my_ddr) rs_ctr.stage = 2;
		else rs_ctr.stage = 0;
		break;
		case 2:
		if (_temp!=0) 
		{
			rs_pack.data[0]=0xAA;
			rs_pack.data[1]=rs_pack.my_ddr;
			rs_pack.data[2]=_temp;
			rs_ctr.counter = 0;
			rs_ctr.stage = 3;
		}
		else rs_ctr.stage = 0;
		break;
		case 3:
		rs_pack.data[rs_ctr.counter+3]=_temp;
		 rs_ctr.counter++;
		if (rs_ctr.counter>=(rs_pack.data[2]+2))
		{
			rs_flag.complete = 1;
			if	(rs_pack.data[rs_pack.data[2]+3]!=CheckSum(rs_pack.data,rs_pack.data[2]+3)) rs_flag.error  = _ERR;
			rs_flag.mode = _REC_DATA;
			rs_ctr.stage = 255;
		}
		break;
		case 4:
		rs_pack.data[0]=0xCC;
		rs_pack.data[1] = _temp;
		rs_ctr.counter = 0;
		rs_ctr.stage = 5;
		break;
		case 5:
		rs_pack.data[rs_ctr.counter+2]=_temp;
		rs_ctr.counter++;
		if (rs_ctr.counter>=2)
		{
			rs_flag.complete = 1;
			if	(rs_pack.data[3]!=CheckSum(rs_pack.data,3)) rs_flag.error  = _ERR;
			rs_flag.mode = _REC_RESPOND;
			rs_ctr.stage = 255;
		}
		break;
		default:
		break;
	}
}
