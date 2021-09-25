/*
 * main.cpp
 *
 * Created: 11/3/2015 2:03:32 PM
 * Author : RnD
 */ 

#include "DMX512A.h"
#include "TLS3001.h"
#include "DMX_TLS.h"
#include "pt2260.h"
#include <avr/wdt.h>
extern _RGB _LED_DMX[Len];
extern _RGB _LED_TLS[Len];

 uint8_t _id_cl[max_range] EEMEM;
uint8_t _mode EEMEM;
uint8_t _count EEMEM;
uint8_t _default EEMEM;
 uint8_t _speed EEMEM;
 uint8_t _wait  EEMEM;

int main(void)
{
	
	wdt_reset();
	wdt_enable(WDTO_2S);
	delayms(100);
	wdt_reset();
	timer0_init();
	RF_decode_initial(0x00);
	RF_decode_setup(300,20);
	DMX_TLS_initial();
	RF_decode_start();
	DDRD|=1<<PORTD4;
	RF_clear_key();
	_delay_ms(1000);
	wdt_reset();
		if (RF_get_key()==1)
		{
			cli();
			eeprom_busy_wait();
			eeprom_write_byte(&_default,0x00);
		}
		wdt_reset();
	 DMX_TLS_set_color_all(base_convert(black),false);
	 DMX_TLS_set_color_all(base_convert(black),true);
	 cli();
	 DMX_TLS_Send_DMX();
	 DMX_TLS_Send_TLS();
	 delayms(1000);
	 eeprom_busy_wait();
	if (eeprom_read_byte(&_default)!=0xAA)
	{
		set_default(0,5,10);
		eeprom_busy_wait();
		eeprom_write_byte(&_default,0xAA);
		eeprom_busy_wait();
		eeprom_write_byte(&_wait,10);
		eeprom_busy_wait();
		eeprom_write_byte(&_speed,5);
		eeprom_busy_wait();
		eeprom_write_byte(&_mode,0);
	}
	else get_eeprom();
    while (1) 
    {
		if (get_mode()) custom_change();
		else color_change_sys_remote(base_convert((Mycolors)(rand()%7+1)));
    }
}

