/*
 * pt2260.h
 *
 * Created: 11/5/2015 8:05:51 AM
 *  Author: RnD
 */ 



#ifndef PT2260_DEC_H_
#define PT2260_DEC_H_



#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
//port define
#define DDR_RF DDRB
#define POR_RF PORTB
#define PIN_RF PINB
#define IN_RF  PINB0
//remote_config
#define rf_data_len 12	//bits
#define rf_max_range 350
#define rf_min_range 80
//api

typedef struct RF_DECODE	// rf_decode
{
	unsigned char  rf_key;
	unsigned int  rf_data;
	unsigned char  rf_id;
	unsigned char  rf_stage;
	unsigned int   rf_timer;
	unsigned char rf_count_bit;
	unsigned int	rf_max_start;
	unsigned int	rf_min_start;
	unsigned char	rf_max_narow;
	unsigned char	rf_min_narow;
	unsigned char   rf_max_wide;
	unsigned char	rf_min_wide;
	unsigned char rf_check;
	
	
}RF_DECODE;

void timer0_init(void);
void delay_50us(unsigned int val);
void set_ms_counter(unsigned int val);
unsigned char check_ms_counter(void);
void RF_decode_setup(uint16_t start_frame_time ,uint8_t percent);
void RF_decode_initial(unsigned char id);
void RF_decode_stop();
void RF_decode_start();
unsigned char RF_get_key(void);
void RF_clear_key(void);




#endif /* PT2260_H_ */