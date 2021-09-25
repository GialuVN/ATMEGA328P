/*
 * main.h
 *
 * Created: 10/16/2015 1:28:58 PM
 *  Author: RnD
 */ 


#ifndef MAIN_H_
#define MAIN_H_



#include "DMX_2015.h"
#include "triac_driver.h"
#include "effect_classic.h"
#include <util/crc16.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>


void DMX_smark_initial(void);
uint16_t concat_2bytes(uint8_t _MSB,uint8_t _LSB);

#endif /* MAIN_H_ */