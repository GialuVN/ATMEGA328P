/*
 * effect_RGB.cpp
 *
 * Created: 10/9/2015 3:21:55 PM
 *  Author: RnD
 */ 



#include <avr/io.h>
#include "PWM_3.h"
#include "effect_RGB.h"

Color rgb;


void out_color(Color _color)
{
	timer1PWMASet(_color.Red);
	timer1PWMBSet(_color.Green);
	timer2PWMSet(_color.Blue);
}



Color color_convert(uint8_t R,uint8_t G,uint8_t B)
{
	Color rgb;
	rgb.Red = R;
	rgb.Green = G;
	rgb.Blue=B;
	return rgb;
}

Color base_convert(Mycolors color_type)
{
	Color rgb;
	switch (color_type)
	{
		case black:
		rgb.Red = 0;
		rgb.Green = 0;
		rgb.Blue=0;
		break;
		case red:
		rgb.Red = resolution;
		rgb.Green = 0;
		rgb.Blue=0;
		break;
		case green:
		rgb.Red = 0;
		rgb.Green = resolution;
		rgb.Blue=0;
		break;
		case blue:
		rgb.Red = 0;
		rgb.Green = 0;
		rgb.Blue=resolution;
		break;
		case yellow:
		rgb.Red = resolution;
		rgb.Green = resolution;
		rgb.Blue=0;
		break;
		case purple:
		rgb.Red = resolution;
		rgb.Green = 0;
		rgb.Blue = resolution;
		break;
		case cyan:
		rgb.Red = 0;
		rgb.Green = resolution;
		rgb.Blue=resolution;
		break;
		case white:
		rgb.Red = resolution;
		rgb.Green = resolution;
		rgb.Blue=resolution;
		break;
		default:
		rgb.Red = 0;
		rgb.Green = 0;
		rgb.Blue=0;
		break;
	}
	return rgb;
}



uint8_t color_change(Color *color1,Color *color2,uint8_t ratio)
{

	if ((color1->Blue==color2->Blue) &&(color1->Green==color2->Green) &&(color1->Red ==color2->Red)) return 1;
	for (uint8_t i =0;i<ratio;i++)
	{
		
		if (color1->Red>color2->Red)  color1->Red-=1;
		else if (color1->Red<color2->Red) color1->Red+= 1;
		
		if (color1->Green>color2->Green) color1->Green -=1;
		else if (color1->Green<color2->Green) color1->Green  += 1;
		
		if (color1->Blue>color2->Blue) color1->Blue -=1;
		else if (color1->Blue<color2->Blue) color1->Blue  += 1;
		
	}
	return 0;
}


void color_change_sys(Color to_color,uint8_t speed,uint8_t ratio,uint16_t wait)
{
	
	if ((rgb.Blue==to_color.Blue)&&(rgb.Red==to_color.Red)&&(rgb.Green==to_color.Green)) return;
	do
	{
		out_color(rgb);
		for (uint16_t i = 0;i<speed;i++) _delay_ms(1);
	} while (color_change(&rgb,&to_color,ratio)==0);
	for (uint16_t i = 0;i<wait;i++)
	_delay_ms(1);
}

