/*
 * DMX_pro.h
 *
 * Created: 10/8/2015 1:07:43 PM
 *  Author: RnD
 */ 


#ifndef DMX_PRO_H_
#define DMX_PRO_H_
#include "DMX_standard.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <inttypes.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

typedef enum colors		//base color
{
	black,
	red,
	green,
	blue,
	yellow,
	cyan,
	purple,
	white,
	
}Mycolors;

typedef struct
{
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
	
} Color_pack;


#define _ENABLE	1
#define _DISABLE 0

//update : 18/1/2015
typedef enum OUTPUT	//MODE
{
	output_normal,
	output_reverse,
	output_haft,
	output_haft_reverse,
	output_logic,
}OUTPUT;



typedef enum MODE	//MODE
{
	mode_minus,
	mode_repoff,
	mode_repon,
	mode_one,
}MODE;


typedef enum NAVI	//NAVIGATIVE
{
	left,
	right,
}NAVI;



//update : 18/1/2015
typedef enum select	//CONTROL
{
	ondelay,
	gray,
	fadein ,
	hold,
	fadeout,
	repeat,
	mode,
	output,
	enable,
}SELECT;


typedef struct rotatal_ctr
{
	bool G_enable;
	uint8_t G_dir;
	uint8_t G_speed;
	uint8_t G_counter;
	uint8_t G_bot;
	uint8_t G_top;

}rotatal_ctr;

typedef struct DMX_control
{
	uint8_t gray;
	uint8_t top_gray;
	uint8_t bot_gray;
	uint16_t counter;
	uint16_t on_delay;
	uint8_t fade_in;
	uint16_t hold;
	uint8_t fade_out;
	uint8_t stage;
	uint8_t repeat;
	uint8_t count_repeat;
	uint8_t mode;
}dmx_control;


void timer0_init(void);
void dmxcontrol_default(void);
void dmxctr_using(uint16_t bot,uint16_t top);
void gray_adj(uint8_t bot,uint8_t top);

void dmxctr_config_ref(uint8_t bot,uint8_t top,uint8_t max_gray,uint8_t min_gray);
void dmxctr_config_vector(uint8_t bot,uint8_t top,SELECT selection,uint16_t from_val,uint16_t to_val);
void dmxctr_random_vector(uint8_t bot,uint8_t top,SELECT selection,uint16_t from_val,uint16_t to_val);
void dmxctr_config_value(uint8_t bot,uint8_t top,SELECT selection,uint16_t val);
void dmxctr_open(void);
void dmxctr_close(void);

void dmxctr_block_Enable(uint16_t bot,uint16_t top);
void dmxctr_block_Disable(uint16_t bot,uint16_t top);
void dmxctr_soft_change(uint16_t bot,uint16_t top,uint8_t speed);

void waitting_complete(void);
void waitting_return(void);
uint8_t check_equal(uint8_t bot,uint8_t top,uint8_t val);

void waitting_complete_n(uint8_t bot,uint8_t top);
void waitting_return_n(uint8_t bot,uint8_t top);

void delay_ms(uint32_t val);
void set_ms_counter(uint32_t val);
uint8_t check_ms_counter(void);

/////////////////////SIMPLY STRUCT////////////////////////////////////
void Block_Set(uint16_t bot,uint16_t top);
void Block_Diasble(void);
void Block_gray_range(uint8_t _min,uint8_t _max);

void Block_gray(uint16_t value_1,uint16_t value_2);
void Block_gray_haft(uint8_t l1,uint8_t l2,uint8_t r1,uint8_t r2);
void Block_ondelay(uint16_t value_1,uint16_t value_2);
void Block_ondelay_haft(uint16_t l1,uint16_t l2,uint16_t r1,uint16_t r2);
void Block_hold(uint16_t value_1,uint16_t value_2);
void Block_hold_haft(uint16_t l1,uint16_t l2,uint16_t r1,uint16_t r2);
void Block_fadein(uint16_t value_1,uint16_t value_2);
void Block_fadein_haft(uint16_t l1,uint16_t l2,uint16_t r1,uint16_t r2);
void Block_fadeout(uint16_t value_1,uint16_t value_2);
void Block_fadeout_haft(uint16_t l1,uint16_t l2,uint16_t r1,uint16_t r2);
void Block_repeat(uint16_t value_1,uint16_t value_2);
void Block_repeat_haft(uint16_t l1,uint16_t l2,uint16_t r1,uint16_t r2);

void Block_repeat_mode(MODE _mode);
void Block_output(OUTPUT _output);
void Block_soft_fade(uint8_t _speed);
void Block_Run(void);
void Block_Run_f(uint16_t bot,uint16_t top);
void Block_wait(void);


void Block_init(uint16_t bot,uint16_t top,uint8_t _min_gray,uint8_t _max_gray);
void Block_delay(uint16_t ondelay1,uint16_t ondelay2,uint16_t hold1,uint16_t hold2);
void Block_fade(uint8_t fadein1,uint8_t fadein2,uint8_t fadeout1,uint8_t fadeout2);
void Block_loop(uint16_t value_1,uint16_t value_2,MODE _mode);

/////////////////////////////////////////////////////////////////////////


///////////////////////////ROTA SIMPLY STRUCT/////////////////////////////////
void rota_init(uint8_t _rota_slot,uint16_t bot,uint16_t top);
void rota_pattern_fill(uint8_t _n,NAVI _dir,uint8_t p0,uint8_t p1,uint8_t p2,uint8_t p3,uint8_t p4,uint8_t p5,uint8_t p6);
void rota_soft_fill_all(uint8_t val_begin,uint8_t val_finish);
void rota_run(uint8_t _speed,NAVI _dir);
void rota_this_stop(void);
void rota_stop(uint8_t _slot);
//////////////////////////////////////////////////////////////////////////

void rota_manager(void);
void rota_enable(void);
void rota_disable(void);
void rota_group_set(uint8_t group_number,uint8_t g_bot,uint8_t g_top,uint8_t speed,uint8_t dir,uint8_t _enable);
void rota_group_default(void);
void fill_soft(uint16_t bot,uint16_t top,uint8_t val_begin,uint8_t val_finish);
void pattern_fill(uint8_t bot,uint8_t top,uint8_t *_pattern,uint8_t _pattern_size,uint8_t direct);
void rota(uint16_t bot,uint16_t top,uint8_t dir);
void sleep(uint16_t val);
void set_val(uint16_t bot,uint16_t top,uint8_t val);
void soft_change(uint16_t bot,uint16_t top,uint8_t speed,uint8_t from_val,uint8_t to_val);
uint16_t Random_range(uint16_t _from,uint16_t _to);

#endif /* DMX_PRO_H_ */