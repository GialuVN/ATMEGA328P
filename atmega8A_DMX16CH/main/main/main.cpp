/*
 * main.cpp
 *
 * Created: 10/9/2015 8:53:08 AM
 * Author : RnD
 */ 

#include "PWM_16CH.h"
#include "DMX_2015.h"
#include "main.h"
#include <avr/io.h>

#define LED PIND1

uint16_t _flag EEMEM = 0;
uint16_t _addr EEMEM = ADDR_default;
uint16_t _addr_bak EEMEM = ADDR_default;
uint16_t _addr_bak_2 EEMEM = ADDR_default;
uint16_t _id  EEMEM = ID;
uint16_t _smile   EEMEM = SMILE;

volatile uint8_t buffer[MAX_DMX_CHANNEL];
			 uint8_t _DMX_frame[DMX_LEN];
uint8_t _result;
uint16_t _temp;
uint16_t _loop;
uint8_t _style;
uint16_t _counting;
int main(void)
{
	
	
	DMX_smark_initial();
	output_init();
	timer2_CTC_init();
	DDRD |=1<<LED;
	
    while (1) 
    {
			wdt_reset();
			sei();
			if (_counting<20000) _counting++;
			else
			{
				PORTD &=~(1<<LED);
				_counting=0;
			}
			_result = DMX_get_data(_DMX_frame,DMX_LEN);
			if (_result==1)
			{
				PORTD |= 1<<LED;
				dimmer_updata(_DMX_frame);
			}
			else if(_result==2)
			{
				PORTD |= 1<<LED;
				_temp = 0;
				cli();
				if (DMX_Frame_CheckSum(_DMX_frame,DMX_LEN)==true)
				{
					if ((_DMX_frame[0]==HEAD) && (_DMX_frame[2]==VER))
					{
						switch (_DMX_frame[1])
						{
							case 0:
							_temp = (uint16_t)_DMX_frame[3]<<8;
							_temp |= (uint16_t)_DMX_frame[4];
							if (_temp==ID || _temp==ID_boardcast) while(1){};
							break;
							
							case 1:
							_temp = (uint16_t)_DMX_frame[3]<<8;
							_temp |= (uint16_t)_DMX_frame[4];
							if (_temp==ID || _temp==ID_boardcast)
							{
								_temp = (uint16_t)_DMX_frame[5]<<8;
								_temp |= (uint16_t)_DMX_frame[6];
								
								if (_temp != DMX_get_address())
								{
									eeprom_busy_wait();
									eeprom_write_word(&_addr,_temp);
									eeprom_busy_wait();
									eeprom_write_word(&_addr_bak,_temp);
									eeprom_busy_wait();
									eeprom_write_word(&_addr_bak_2,_temp);
									DMX_data_reset(_temp);
								}
							}
							
							break;			
//random_effect
/************************************************************************/
/* 
[0xCC][  CMD=10 ][1 bytes VER][ 2 bytes  ID ][1byte  speed][2 bytes repeat][1 byte sleep][2 byte loop][4 bytes option][ 1 bytes CRC ]

 1byte    1byte		1bytes			2 bytes			1 bytes			2bytes      1bytes			 2bytes		4bytes			1bytes
                                                                     */
/************************************************************************/
					
							case 10:
							sei();
								_temp = (uint16_t)_DMX_frame[3]<<8;
								_temp |= (uint16_t)_DMX_frame[4];
								if (_temp==ID || _temp==ID_boardcast)
								{
									_loop = (uint8_t)_DMX_frame[9]<<8;
									_loop |= (uint8_t)_DMX_frame[10];
									effect_enable();
									while (_loop!=0)
									{
									
										sei();
										random_light_st1(A1,A16,buffer,_DMX_frame[5],concat_2bytes(_DMX_frame[6],_DMX_frame[7]),_DMX_frame[8]);
									_loop--;
									}
									
									
								}
							break;
							
							
//shootting_effect
/************************************************************************/
/* 
[0xCC][  CMD=11  ][1 bytes VER][ 2 bytes  ID ][1byte  speed][1 bytes size][1 byte style][2 byte loop][5 bytes option][ 1 bytes CRC ]

 1byte    1byte		1bytes			2 bytes			1 bytes			1bytes      1bytes			 2bytes		5bytes			1bytes
                                                                     */
/************************************************************************/

							case 11:
							sei();
								_temp = (uint16_t)_DMX_frame[3]<<8;
								_temp |= (uint16_t)_DMX_frame[4];
								if (_temp==ID || _temp==ID_boardcast)
								{
									_style = _DMX_frame[7];
									_loop = (uint8_t)_DMX_frame[8]<<8;
									_loop |= (uint8_t)_DMX_frame[9];
									effect_enable();
									while(_loop!=0)
									{
										sei();
										switch (_style)
										{
											case 0:
											shooting_star(A1,A16,buffer,_DMX_frame[5],_DMX_frame[6],0);
											break;
											case 1:
											shooting_star(A1,A16,buffer,_DMX_frame[5],_DMX_frame[6],1);
											break;
											case 2:
											shooting_star(A1,A16,buffer,_DMX_frame[5],_DMX_frame[6],0);
											shooting_star(A1,A16,buffer,_DMX_frame[5],_DMX_frame[6],1);
											break;
										}
										_loop--;
										
									}
								}
							break;							
							
					
//softflash_effect
/************************************************************************/
/* 
[0xCC][  CMD=12  ][1 bytes VER][ 2 bytes  ID ][1byte  speed][1bytes repeat][1 byte val1] [1 byte val2][2 byte mode][4 bytes option][ 1 bytes CRC ]

 1byte    1byte		1bytes			2 bytes			1 bytes			1bytes      1bytes			 1bytes		2bytes		4bytes			1bytes
                                                                     */
/************************************************************************/

							case 12:
							sei();
								_temp = (uint16_t)_DMX_frame[3]<<8;
								_temp |= (uint16_t)_DMX_frame[4];
								if (_temp==ID || _temp==ID_boardcast)
								{
									_loop = (uint8_t)_DMX_frame[9]<<8;
									_loop |= (uint8_t)_DMX_frame[10];
									effect_enable();
									while(_loop!=0)
									{
										sei();
										soft_flash(A1,A16,buffer,_DMX_frame[5],_DMX_frame[6],_DMX_frame[7],_DMX_frame[8]);
										_loop--;
									}
								}
							break;			
//filldrop_effect
/************************************************************************/
/* 
[0xCC][  CMD=13  ][1 bytes VER][ 2 bytes  ID ][1byte  speed][1 bytes size][1 byte style][2 byte loop][5 bytes option][ 1 bytes CRC ]

1byte    1byte		1bytes			2 bytes			1 bytes			1bytes      1bytes			 2bytes		5bytes			1bytes
                                                                     */
/************************************************************************/						
								case 13:
								sei();
								_temp = (uint16_t)_DMX_frame[3]<<8;
								_temp |= (uint16_t)_DMX_frame[4];
								if (_temp==ID || _temp==ID_boardcast)
								{
									_style = _DMX_frame[7];
									_loop = (uint8_t)_DMX_frame[8]<<8;
									_loop |= (uint8_t)_DMX_frame[9];
									effect_enable();
									while(_loop!=0)
									{
										sei();
										switch (_style)
										{
											case 0:
											fill_drop(A1,A16,buffer,_DMX_frame[5],_DMX_frame[6],0);
											break;
											case 1:
											fill_drop(A1,A16,buffer,_DMX_frame[5],_DMX_frame[6],1);
											break;
											case 2:
											fill_drop(A1,A16,buffer,_DMX_frame[5],_DMX_frame[6],0);
											fill_drop(A1,A16,buffer,_DMX_frame[5],_DMX_frame[6],1);
											break;
										}
										_loop--;
									}
								}
								break;
													
							case 255:
							_temp = (uint16_t)_DMX_frame[3]<<8;
							_temp |= (uint16_t)_DMX_frame[4];
							if (_temp==ID || _temp==ID_boardcast)
							{
								_temp = (uint16_t)_DMX_frame[5]<<8;
								_temp |= (uint16_t)_DMX_frame[6];
								if (_temp == 0xABCD)
								{
									eeprom_busy_wait();
									eeprom_write_word(&_smile,SLEEP_EVENT);
									while(1){};
								}
							}
							break;
							
							default:
							
							break;
							
						}

					}

				}
			}

    }
}

//data frame
/************************************************************************/
/* 

[0xCC][  CMD  ][ 12bytes data ][ 1 bytes CRC ]

 1byte    1byte        13bytes      1bytes
 
                                                                     */
/************************************************************************/

//set addr frame
/************************************************************************/
/* 
[0xCC][  CMD=1  ][1 bytes VER][ 2 bytes  ID ][2 bytes addr][9 bytes option][ 1 bytes CRC ]

 1byte    1byte      1bytes		   2bytes		2bytes			8bytes			 1bytes
                                                                     */
/************************************************************************/

//reset devices
/************************************************************************/
/* 
[0xCC][  CMD=0  ][1 bytes VER][ 2 bytes  ID ][10 bytes option][ 1 bytes CRC ]

 1byte    1byte		1bytes			2 bytes			10 bytes    	 1bytes
                                                                     */
/************************************************************************/

//SLEEP_EVEN_forever
/************************************************************************/
/* 
[0xCC][  CMD=255  ][1 bytes VER][ 2 bytes  ID ][0xABCD][10 bytes option][ 1 bytes CRC ]

 1byte    1byte		1bytes			2 bytes		2 bytes    8bytes      	 1bytes
                                                                     */
/************************************************************************/

void DMX_smark_initial(void)
{
	uint16_t _tem;
	uint16_t _myaddr;
	cli();
	wdt_reset();
	wdt_enable(WDTO_2S);
	_delay_ms(1000);
	wdt_reset();
	eeprom_busy_wait();
	_tem= eeprom_read_word(&_smile);
	
//oh my golt 
	while (_tem==SLEEP_EVENT)
	{
		DMX_smark_initial();
	}
	eeprom_busy_wait();
	_tem= eeprom_read_word(&_flag);
	if (_tem==FIRST_START)
	{
		eeprom_busy_wait();
		_tem = eeprom_read_word(&_addr);
		eeprom_busy_wait();
		if (_tem==eeprom_read_word(&_addr_bak))
		{
			_myaddr = _tem;
		}
		
		else
		{
			eeprom_busy_wait();
			_myaddr = eeprom_read_word(&_addr_bak_2);
			eeprom_busy_wait();
			eeprom_write_word(&_addr,_myaddr);
			eeprom_busy_wait();
			eeprom_write_word(&_addr_bak,_myaddr);
			
		}
	}
	else 
	{
		eeprom_busy_wait();
		eeprom_write_word(&_addr,ADDR_default);
		eeprom_busy_wait();
		eeprom_write_word(&_addr_bak,ADDR_default);
		eeprom_busy_wait();
		eeprom_write_word(&_addr_bak_2,ADDR_default);
		eeprom_busy_wait();
		eeprom_write_word(&_id,ID);
		eeprom_busy_wait();
		eeprom_write_word(&_smile,SMILE);
		eeprom_busy_wait();
		eeprom_write_word(&_flag,FIRST_START);
		_myaddr = ADDR_default;
	}
	DMX_USART_Init(MYUBRR);
	DMX_data_reset(_myaddr);
	sei();
}



uint16_t concat_2bytes(uint8_t _MSB,uint8_t _LSB)
{
	uint16_t _tem;
	_tem = (uint16_t)_MSB<<8;
	_tem |=(uint16_t)_LSB;
	return _tem;
}