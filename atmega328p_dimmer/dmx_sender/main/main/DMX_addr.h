/*
 * DMX_addr.h
 *
 * Created: 10/15/2015 2:06:03 PM
 *  Author: RnD
 */ 


#ifndef DMX_ADDR_H_
#define DMX_ADDR_H_
#include "DMX_sender_config.h"
#include "DMX_standard.h"
#include <util/crc16.h>

//define before progamming
#define VER		0x01
#define ID		1000
///////////////////////////


//fix define
#define DTA		0x00
#define CTR		0xAA


#define HEAD	0xCC
#define ADDR_default 1
#define SMILE	2015
#define SLEEP_EVENT	0XAAAA
#define FIRST_START 0xCCCC
/////////////////////////////


void DMX_set_addr(uint8_t ver,uint16_t id, uint16_t _addr);
void DMX_reset_device(uint8_t ver,uint16_t id);
void DMX_fixed_random(uint8_t ver,uint16_t id,uint8_t _speed,uint8_t _sleep,uint16_t _repeat,uint16_t _loop);
void DMX_fixed_shooting(uint8_t ver,uint16_t id,uint8_t _speed,uint8_t _size,uint16_t _style,uint16_t _loop);
void DMX_fixed_soft_flash(uint8_t ver,uint16_t id,uint8_t _speed,uint8_t _repeat,uint8_t _val1,uint8_t _val2,uint16_t _loop);
void DMX_fixed_filldrop(uint8_t ver,uint16_t id,uint8_t _speed,uint8_t _size,uint8_t _style,uint16_t _loop);
void DMX_fixed_close(uint8_t ver,uint16_t id);
void DMX_sleep_device(uint8_t ver,uint16_t id);
uint8_t crc_make(uint8_t *data,uint8_t len);


#endif /* DMX_ADDR_H_ */