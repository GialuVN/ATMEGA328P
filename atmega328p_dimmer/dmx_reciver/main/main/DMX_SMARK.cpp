/*
 * DMX_SMARK.cpp
 *
 * Created: 10/9/2015 2:45:45 PM
 *  Author: RnD
 */ 

#include "DMX_SMARK.h"


uint16_t _flag EEMEM = 0;
uint16_t _addr EEMEM = ADDR_default;
uint16_t _addr_bak EEMEM = ADDR_default;
uint16_t _addr_bak_2 EEMEM = ADDR_default;
uint16_t _id  EEMEM = ID;
uint16_t _smile   EEMEM = SMILE;

volatile uint16_t _MY_ADDR;
volatile uint8_t _DMX_frame[DMX_LEN];


bool DMX_Frame_CheckSum(void)
{
	uint8_t _crc =0;
	for (uint8_t i = 0;i<DMX_LEN;i++) _crc = _crc_ibutton_update(_crc,_DMX_frame[i]);
	if (_crc==0) return true;
	return false;
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
	uint16_t _tem2;
	cli();
	wdt_reset();
	wdt_enable(WDTO_2S);
	_delay_ms(250);
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
		_tem2 = eeprom_read_word(&_addr);
		eeprom_busy_wait();
		if (_tem2==eeprom_read_word(&_addr_bak))
		{
			_MY_ADDR = _tem2;
		}
		
		else
		{
			eeprom_busy_wait();
			_MY_ADDR = eeprom_read_word(&_addr_bak_2);
			eeprom_busy_wait();
			eeprom_write_word(&_addr,_MY_ADDR);
			eeprom_busy_wait();
			eeprom_write_word(&_addr_bak,_MY_ADDR);
			
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
		_MY_ADDR = ADDR_default;
	}
	DMX_USART_Init(MYUBRR);
	DMX_data_reset(_MY_ADDR);
	dimmer_init();
	sei();
}

void DMX_smart_running(void)
{
	uint8_t _result;
	uint16_t _tem;
	
	while(1)
	{
		wdt_reset();
		sei();
		_result = DMX_get_data(_DMX_frame,DMX_LEN);
		if (_result==1)
		{
			 dimmer_updata(_DMX_frame);
		}
		else if(_result==2)
		{
			_tem = 0;
			cli();
			if (DMX_Frame_CheckSum()==true)
			{
				if ((_DMX_frame[0]==HEAD) && (_DMX_frame[2]==VER))
				{
					switch (_DMX_frame[1])
					{
						case 0:
						_tem = (uint16_t)_DMX_frame[3]<<8;
						_tem |= (uint16_t)_DMX_frame[4];
						if (_tem==ID) while(1){};
						break;
						
						case 1:
						_tem = (uint16_t)_DMX_frame[3]<<8;
						_tem |= (uint16_t)_DMX_frame[4];
						
						if (_tem==ID)
						{
							_tem = (uint16_t)_DMX_frame[5]<<8;
							_tem |= (uint16_t)_DMX_frame[6];
							
							if (_tem != _MY_ADDR)
							{
								eeprom_busy_wait();
								eeprom_write_word(&_addr,_tem);
								eeprom_busy_wait();
								eeprom_write_word(&_addr_bak,_tem);
								eeprom_busy_wait();
								eeprom_write_word(&_addr_bak_2,_tem);
							//	while(1){};
								
								_MY_ADDR = _tem;
							}
						}
						DMX_data_reset(_MY_ADDR);
						break;
						case 255:
							_tem = (uint16_t)_DMX_frame[3]<<8;
							_tem |= (uint16_t)_DMX_frame[4];
							if (_tem==ID)
							 {
								_tem = (uint16_t)_DMX_frame[5]<<8;
								_tem |= (uint16_t)_DMX_frame[6];
								if (_tem==0xABCD)
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


