/*
 * DMX_addr.cpp
 *
 * Created: 10/15/2015 2:05:50 PM
 *  Author: RnD
 */ 

#include "DMX_addr.h"


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



void DMX_set_addr(uint8_t ver,uint16_t id, uint16_t _addr)
{
	uint8_t _temp[16];
	cli();
	_temp[0] = HEAD;
	_temp[1] = 1;
	_temp[2] = ver;
	_temp[3] =(uint8_t)(id>>8);
	_temp[4] =(uint8_t)id;
	_temp[5] = (uint8_t)(_addr>>8);
	_temp[6] = (uint8_t)_addr;
	_temp[15] = crc_make(_temp,15);
	DMX_transmit_setting(CTR,_temp,16);
	_delay_ms(10);
	sei();
}


//reset devices
/************************************************************************/
/* 
[0xCC][  CMD=0  ][1 bytes VER][ 2 bytes  ID ][10 bytes option][ 1 bytes CRC ]

 1byte    1byte		1bytes			2 bytes			10 bytes    	 1bytes
                                                                     */
/************************************************************************/
void DMX_reset_device(uint8_t ver,uint16_t id)
{
	uint8_t _temp[16];
	cli();
	_temp[0] = HEAD;
	_temp[1] = 0;
	_temp[2] = ver;
	_temp[3] =(uint8_t)(id>>8);
	_temp[4] =(uint8_t)id;
	_temp[15] = crc_make(_temp,15);
	DMX_transmit_setting(CTR,_temp,16);
	_delay_ms(10);
	sei();
}

//SLEEP_EVEN_forever
/************************************************************************/
/* 
[0xCC][  CMD=255  ][1 bytes VER][ 2 bytes  ID ][0xABCD][10 bytes option][ 1 bytes CRC ]

 1byte    1byte		1bytes			2 bytes		2 bytes    8bytes      	 1bytes
                                                                     */
/************************************************************************/

void DMX_sleep_device(uint8_t ver,uint16_t id)
{
	
	uint8_t _temp[16];
	cli();
	_temp[0] = HEAD;
	_temp[1] = 255;
	_temp[2] = ver;
	_temp[3] =(uint8_t)(id>>8);
	_temp[4] =(uint8_t)id;
	_temp[5] = (uint8_t)(0xABCD>>8);
	_temp[6] = (uint8_t)0xABCD;
	_temp[15] = crc_make(_temp,15);
	DMX_transmit_setting(CTR,_temp,16);
	_delay_ms(10);
	sei();
}


//random_effect
/************************************************************************/
/* 
[0xCC][  CMD=10 ][1 bytes VER][ 2 bytes  ID ][1byte  speed][2 bytes repeat][1 byte sleep][2 byte _loop][4 bytes option][ 1 bytes CRC ]

 1byte    1byte		1bytes			2 bytes			1 bytes			2bytes      1bytes			 2bytes		4bytes			1bytes
                                                                     */
/************************************************************************/

void DMX_fixed_random(uint8_t ver,uint16_t id,uint8_t _speed,uint8_t _sleep,uint16_t _repeat,uint16_t _loop)
{
	uint8_t _temp[16];
	cli();
	_temp[0] = HEAD;
	_temp[1] = 10;//cmd
	_temp[2] = ver;
	_temp[3] =(uint8_t)(id>>8);
	_temp[4] =(uint8_t)id;
	
	_temp[5] =_speed;
	_temp[6] =(uint8_t)_repeat>>8;
	_temp[7] =(uint8_t)_repeat;
	_temp[8] = _sleep;
	_temp[9] = (uint8_t)_loop>>8;;
	_temp[10] = (uint8_t)_loop;
	
	_temp[15] = crc_make(_temp,15);
	DMX_transmit_setting(CTR,_temp,16);
	_delay_ms(10);
	sei();
}

							
//shootting_effect
/************************************************************************/
/* 
[0xCC][  CMD=11  ][1 bytes VER][ 2 bytes  ID ][1byte  speed][1 bytes size][1 byte style][2 byte loop][5 bytes option][ 1 bytes CRC ]

 1byte    1byte		1bytes			2 bytes			1 bytes			1bytes      1bytes			 2bytes		5bytes			1bytes
                                                                     */
/************************************************************************/


void DMX_fixed_shooting(uint8_t ver,uint16_t id,uint8_t _speed,uint8_t _size,uint16_t _style,uint16_t _loop)
{
	uint8_t _temp[16];
	cli();
	_temp[0] = HEAD;
	_temp[1] = 11;//cmd
	_temp[2] = ver;
	_temp[3] =(uint8_t)(id>>8);
	_temp[4] =(uint8_t)id;
	_temp[5] =_speed;
	_temp[6] =_size;
	_temp[7] =_style;
	_temp[8] = (uint8_t)_loop>>8;;
	_temp[9] = (uint8_t)_loop;
	_temp[15] = crc_make(_temp,15);
	DMX_transmit_setting(CTR,_temp,16);
	_delay_ms(10);
	sei();
}


			
//softflash_effect
/************************************************************************/
/* 
[0xCC][  CMD=12  ][1 bytes VER][ 2 bytes  ID ][1byte  speed][1bytes repeat][1 byte val1] [1 byte val2][2 byte loop][4 bytes option][ 1 bytes CRC ]

 1byte    1byte		1bytes			2 bytes			1 bytes			1bytes      1bytes			 1bytes		2bytes		4bytes			1bytes
                                                                     */
/************************************************************************/



void DMX_fixed_soft_flash(uint8_t ver,uint16_t id,uint8_t _speed,uint8_t _repeat,uint8_t _val1,uint8_t _val2,uint16_t _loop)
{
	uint8_t _temp[16];
	cli();
	_temp[0] = HEAD;
	_temp[1] = 12;//cmd
	_temp[2] = ver;
	_temp[3] =(uint8_t)(id>>8);
	_temp[4] =(uint8_t)id;
	_temp[5] =_speed;
	_temp[6] =_repeat;
	_temp[7] =_val1;
	_temp[8] = _val2;
	_temp[9] = (uint8_t)(_loop>>8);
	_temp[10] = (uint8_t)_loop;
	_temp[15] = crc_make(_temp,15);
	DMX_transmit_setting(CTR,_temp,16);
	_delay_ms(10);
	sei();
}

//filldrop_effect
/************************************************************************/
/* 
[0xCC][  CMD=13  ][1 bytes VER][ 2 bytes  ID ][1byte  speed][1 bytes size][1 byte style][2 byte loop][5 bytes option][ 1 bytes CRC ]

1byte    1byte		1bytes			2 bytes			1 bytes			1bytes      1bytes			 2bytes		5bytes			1bytes
                                                                     */
/************************************************************************/		

void DMX_fixed_filldrop(uint8_t ver,uint16_t id,uint8_t _speed,uint8_t _size,uint8_t _style,uint16_t _loop)
{
	uint8_t _temp[16];
	cli();
	_temp[0] = HEAD;
	_temp[1] = 13;//cmd
	_temp[2] = ver;
	_temp[3] =(uint8_t)(id>>8);
	_temp[4] =(uint8_t)id;
	_temp[5] =_speed;
	_temp[6] =_size;
	_temp[7] =_style;
	_temp[8] = (uint8_t)(_loop>>8);
	_temp[9] = (uint8_t)_loop;
	_temp[15] = crc_make(_temp,15);
	DMX_transmit_setting(CTR,_temp,16);
	_delay_ms(10);
	sei();
}


//close_effect
/************************************************************************/
/* 
[0xCC][  CMD=254  ][1 bytes VER][ 2 bytes  ID ][10 bytes option][ 1 bytes CRC ]

1byte    1byte		1bytes			2 bytes		10bytes			1bytes
                                                                     */
/************************************************************************/		

void DMX_fixed_close(uint8_t ver,uint16_t id)
{
	uint8_t _temp[16];
	cli();
	_temp[0] = HEAD;
	_temp[1] = 254;//cmd
	_temp[2] = ver;
	_temp[3] =(uint8_t)(id>>8);
	_temp[4] =(uint8_t)id;
	_temp[15] = crc_make(_temp,15);
	DMX_transmit_setting(CTR,_temp,16);
	_delay_ms(10);
	sei();
}

uint8_t crc_make(uint8_t *data,uint8_t len)
{
	uint8_t _crc=0;
	for (uint8_t i = 0;i<len;i++) _crc = _crc_ibutton_update(_crc,data[i]);
	return _crc;
}