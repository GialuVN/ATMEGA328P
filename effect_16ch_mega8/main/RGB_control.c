/*
 * RGB_control.c
 *
 * Created: 24/12/2013 9:12:01 AM
 *  Author: THIET KE 3
 */ 

#include <avr/io.h>
#include "PWM.h"
#include "pwm_general.h"
#include "RGB_control.h"
 extern uint8_t gray_scale[DATA_LEN];
	
void out_color(uint8_t pr,uint8_t pg,uint8_t pb, uint8_t  *gray,Color rgb)
{
	gray[pr] = rgb.Red;
	gray[pg] = rgb.Green;
	gray[pb] = rgb.Blue;
}

Color set_RGB(uint8_t R,uint8_t G,uint8_t B)
{
	Color rgb;
	rgb.Red = R;
	rgb.Green = G;
	rgb.Blue=B;
	return rgb;
}

Color set_color(Mycolors color_type)
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

void  auto_change_together(uint8_t pr,uint8_t pg,uint8_t pb,Color color_to,uint8_t steps,uint8_t speed)
{
	while (1)
	{
		for (int i= 0;i<steps;i++)
		{
			if (gray_scale[pr]>color_to.Red) gray_scale[pr] -=1;
			else if (gray_scale[pr]<color_to.Red) gray_scale[pr] += 1;
			
			if (gray_scale[pg]>color_to.Green) gray_scale[pg] -=1;
			else if (gray_scale[pg]<color_to.Green) gray_scale[pg]+=1;
			
			if (gray_scale[pb]>color_to.Blue) gray_scale[pb]  -=1;
			else if (gray_scale[pb]<color_to.Blue) gray_scale[pb] +=1;
			
		}
		out_color(pr,pg,pb,gray_scale,set_RGB(gray_scale[pr],gray_scale[pg],gray_scale[pb]));
		pwm_gen(speed,gray_scale);
		
		if (gray_scale[pr]==color_to.Red && gray_scale[pg]==color_to.Green && gray_scale[pb]==color_to.Blue) break;
	}
}


