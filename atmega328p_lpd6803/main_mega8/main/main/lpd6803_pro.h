/*
 * lpd6803_pro.h
 *
 * Created: 24/09/2013 10:40:17 AM
 *  Author: THIET KE 3
 */ 


#ifndef LPD6803_PRO_H_
#define LPD6803_PRO_H_
#include <stdlib.h>
#include <stdio.h>
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

typedef struct cl
{
	uint8_t Red:5;
	uint8_t Green:5;
	uint8_t Blue:5;
	
} Cl;

typedef union {
	Cl Color;
	uint16_t Pack;
}Color_pack;


#define max_led	 300
#define _TOP	(max_led-1)
#define _BOT	0
void out_to_lpd(Color_pack *rgb, uint16_t nled);
void set_base_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,uint8_t R,uint8_t G,uint8_t B);
Color_pack pack_convert(uint8_t R,uint8_t G,uint8_t B);
Color_pack base_convert(Mycolors _color);
void rotatal(Color_pack *rgb,uint16_t first_point,uint16_t last_point,uint8_t direct);

uint8_t color_change(Color_pack *color1,Color_pack *color2,uint8_t ratio);
void color_change_sys(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack to_color,uint8_t speed,uint8_t ratio,uint16_t wait);
void color_to_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack color1,Color_pack color2,uint8_t style);
void soft_paint(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack color1,Color_pack color2);
void paint_touch(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack _color,uint8_t style);


void gen_color_linear(Color_pack *rgb,uint16_t first_point,uint16_t last_point,uint8_t speed, uint8_t div,uint16_t loop,uint8_t style);
void gen_two_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack cl1,Color_pack cl2,uint8_t speed, uint8_t len,uint16_t loop,uint8_t style);
void gen_soft_two_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack cl1,Color_pack cl2,uint8_t speed, uint8_t div,uint16_t loop,uint8_t style);

#endif /* LPD6803_PRO_H_ */