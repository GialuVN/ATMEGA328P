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
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
} Cl;

typedef union {
	Cl Color;
	uint8_t Pack[3];
}Color_pack;

#define max_gray 50
#define max_led	 5
#define _TOP	(max_led-1)
#define _BOT	0
void RGB_out_to_lpd(Color_pack *rgb, uint16_t nled);
void RGB_set_base_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,uint8_t R,uint8_t G,uint8_t B);
Color_pack RGB_pack_convert(uint8_t R,uint8_t G,uint8_t B);
Color_pack RGB_base_convert(Mycolors _color);
void RGB_rotatal(Color_pack *rgb,uint16_t first_point,uint16_t last_point,uint8_t direct);

uint8_t RGB_color_change(Color_pack *color1,Color_pack *color2,uint8_t ratio);
void RGB_color_change_sys(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack to_color,uint8_t speed,uint8_t ratio,uint16_t wait);
void RGB_color_to_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack color1,Color_pack color2,uint8_t style);
void RGB_soft_paint(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack color1,Color_pack color2);
void RGB_paint_touch(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack _color,uint8_t style);


void RGB_gen_color_linear(Color_pack *rgb,uint16_t first_point,uint16_t last_point,uint8_t speed, uint8_t div,uint16_t loop,uint8_t style);
void RGB_gen_two_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack cl1,Color_pack cl2,uint8_t speed, uint8_t len,uint16_t loop,uint8_t style);
void RGB_gen_soft_two_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack cl1,Color_pack cl2,uint8_t speed, uint8_t div,uint16_t loop,uint8_t style);

#endif /* LPD6803_PRO_H_ */