/*
 * DMX_TLS.h
 *
 * Created: 11/3/2015 3:08:33 PM
 *  Author: RnD
 */ 


#ifndef DMX_TLS_H_
#define DMX_TLS_H_

#include "DMX512A.h"
#include "TLS3001.h"
#include <avr/eeprom.h>

#define max_range	30
#define Len 6
#define _TLS true
typedef struct _rgb
{
	unsigned char _R;
	unsigned char _G;
	unsigned char _B;
}_RGB;
typedef enum colors		//base color
{
	black=0,
	red,
	green,
	blue,
	yellow,
	cyan,
	purple,
	white,
}Mycolors;

typedef struct _data_cl
{
	uint8_t id_cl[max_range];
	uint8_t count_cl;
	uint8_t point_cl;
	uint8_t _mode_;
	uint8_t speed_cl;
	uint8_t wait_cl;
}_DATA_CL;



void DMX_TLS_initial(void);
void DMX_TLS_Send_DMX(void);
void DMX_TLS_Send_TLS(void);
void color_change_sys(_RGB to_color,uint8_t speed,uint8_t ratio,uint16_t wait);
bool color_change(_RGB *color1,_RGB *color2,uint8_t ratio);

void DMX_TLS_set_color_all(_RGB _color,bool _select);

_RGB color_convert(uint8_t R,uint8_t G,uint8_t B);
_RGB base_convert(Mycolors color_type);
void delayms(unsigned int val);


void setup_disp(_RGB _cl);
void Remote(unsigned char wait);

void set_default(uint8_t _mode,uint8_t _speed,uint8_t _wait);
void color_change_sys_remote(_RGB to_color);
bool get_mode(void);
void get_eeprom(void);
void custom_change(void);

#endif /* DMX_TLS_H_ */