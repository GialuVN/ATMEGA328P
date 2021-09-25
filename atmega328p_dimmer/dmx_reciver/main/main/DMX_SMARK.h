/*
 * DMX_SMARK.h
 *
 * Created: 10/9/2015 2:46:03 PM
 *  Author: RnD
 */ 


#ifndef DMX_SMARK_H_
#define DMX_SMARK_H_

#include "DMX_2015.h"
#include "triac_driver.h"
#include <util/crc16.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>


bool DMX_Frame_CheckSum(void);
void DMX_smark_initial(void);
void DMX_smart_running(void);

#endif /* DMX_SMARK_H_ */