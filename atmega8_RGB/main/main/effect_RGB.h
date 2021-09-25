/*
 * effect_RGB.h
 *
 * Created: 10/9/2015 3:22:12 PM
 *  Author: RnD
 */ 


#ifndef EFFECT_RGB_H_
#define EFFECT_RGB_H_

#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>


#define resolution 255


typedef struct color	//RGB block
{
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
}Color;
typedef enum colors		//base color
{
	black,
	blue,
	green,
	cyan,
	red,
	purple,
	yellow,
	white,
}Mycolors;


uint8_t color_change(Color *color1,Color *color2,uint8_t ratio);
void color_change_sys(Color to_color,uint8_t speed,uint8_t ratio,uint16_t wait);

void out_color(Color _color);
Color color_convert(uint8_t R,uint8_t G,uint8_t B);
Color base_convert(Mycolors color_type);
#endif /* EFFECT_RGB_H_ */