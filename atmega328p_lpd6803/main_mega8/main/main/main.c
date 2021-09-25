/*
 * main.c
 *
 * Created: 24/09/2013 7:21:16 AM
 *  Author: THIET KE 3
 */ 
#define F_CPU 16000000ul
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include "lpd6803_pro.h"
#include "lpd6803.h"
Color_pack RGB[max_led];

int main(void)
{
	lpd6803_config_pin();
	set_base_color(RGB,_BOT,_TOP,0,0,0);
	//paint_touch(RGB,0,14,pack_convert(31,0,0),1);
	//paint_touch(RGB,15,30,pack_convert(31,0,0),1);
	//paint_touch(RGB,31,45,pack_convert(31,0,0),1);
	//paint_touch(RGB,46,60,pack_convert(31,0,0),1);
	
	//paint_touch(RGB,0,120,pack_convert(0,31,0),0);
	
	//paint_touch(RGB,0,100,pack_convert(0,0,0),0);
	//soft_paint(RGB,1,_TOP,pack_convert(31,0,0),pack_convert(0,31,0));
	
	//soft_paint(RGB,31,60,pack_convert(0,0,31),pack_convert(0,31,0));
	//soft_paint(RGB,61,90,pack_convert(0,31,0),pack_convert(0,0,31));
	//soft_paint(RGB,91,120,pack_convert(31,0,0),pack_convert(0,31,0));
	//	soft_paint(RGB,25,49,pack_convert(0,31,0),pack_convert(31,31,31));
	
    while(1)
    {
		
	
		gen_color_linear(RGB,_BOT,_TOP,15,5,200,0);
		gen_color_linear(RGB,_BOT,_TOP,15,5,200,2);
		gen_color_linear(RGB,_BOT,_TOP,15,5,200,1);
		gen_color_linear(RGB,_BOT,_TOP,15,5,200,3);
		
		gen_two_color(RGB,_BOT,_TOP,base_convert(random()%6+1),base_convert(random()%6+1),15,5,300,0);
		gen_two_color(RGB,_BOT,_TOP,base_convert(random()%6+1),base_convert(random()%6+1),15,5,300,3);
		gen_two_color(RGB,_BOT,_TOP,base_convert(random()%6+1),base_convert(random()%6+1),15,5,300,2);
		gen_two_color(RGB,_BOT,_TOP,base_convert(random()%6+1),base_convert(random()%6+1),15,5,300,1);
		
		gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%6+1),base_convert(random()%6+1),15,2,300,0);
		gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%6+1),base_convert(random()%6+1),15,2,300,3);
		gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%6+1),base_convert(random()%6+1),15,2,300,1);
		gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%6+1),base_convert(random()%6+1),15,2,300,2);
		
		for (uint8_t i = 0; i < 14; i++)
		{
			color_change_sys(RGB,_BOT,_TOP,base_convert(random()%6+1),50,1,2000);
		}
		
    }
}

