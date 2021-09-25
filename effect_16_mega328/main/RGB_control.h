/*
 * RGB_control.h
 *
 * Created: 24/12/2013 9:12:16 AM
 *  Author: THIET KE 3
 */ 


#ifndef RGB_CONTROL_H_
#define RGB_CONTROL_H_
#include <stdlib.h>
#include <stdio.h>

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

Color set_color(Mycolors color_type);
void out_color(uint8_t pr,uint8_t pg,uint8_t pb,uint8_t *gray,Color rgb);
Color set_RGB(uint8_t R,uint8_t G,uint8_t B);
void  auto_change_together(uint8_t pr,uint8_t pg,uint8_t pb,Color color_to,uint8_t steps,uint8_t speed);

#endif /* RGB_CONTROL_H_ */