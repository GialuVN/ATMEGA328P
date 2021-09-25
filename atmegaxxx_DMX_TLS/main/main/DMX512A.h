/*
 * DMX512A.h
 *
 * Created: 11/3/2015 2:08:15 PM
 *  Author: RnD
 */ 


#ifndef DMX512A_H_
#define DMX512A_H_


#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define nop() asm volatile ("nop")

#define DDR_OUT DDRD
#define POR_OUT PORTD
#define PIN_OUT PORTD1

#define PIN_MASK_POS (1<<PIN_OUT)
#define PIN_MASK_NEG (~PIN_MASK_POS)

#define DMX_CH	100

void DMX512A_init(void);
void DMX512A_send_break_mab(void);
void DMX512A_send_byte(uint8_t val);
void DMX512A_send(uint8_t *data,uint16_t len);


void rota(uint8_t bot,uint8_t top,volatile uint8_t *data,uint8_t dir);
void soft_change(uint8_t bot,uint8_t top,uint8_t *data,uint8_t speed,uint8_t from_val,uint8_t to_val);
void sleep(uint16_t val);
void set_val(uint8_t bot,uint8_t top,volatile uint8_t *data,uint8_t val);



#endif /* DMX512A_H_ */