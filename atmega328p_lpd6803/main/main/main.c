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
		
		switch (random()%13)
		{
		case 0:
		gen_color_linear(RGB,_BOT,_TOP,10,1,30,0);
		break;
		case 1:
		gen_color_linear(RGB,_BOT,_TOP,10,1,30,2);
		break;
		case 2:
		gen_color_linear(RGB,_BOT,_TOP,10,1,30,1);
		break;
		case 3:
		gen_color_linear(RGB,_BOT,_TOP,10,1,100,3);
		break;
		case 4:
		gen_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),25,5,120,0);
		break;
		case 5:
		gen_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),25,5,60,3);
		break;
		case 6:
		gen_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),25,5,60,2);
		break;
		case 7:
		gen_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),25,5,120,1);
		break;
		case 8:
		gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),20,2,50,0);
		break;
		case 9:
		gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),20,2,25,3);
		break;
		case 10:
		gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),20,2,50,1);
		break;
		
		
		case 11:
		gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),20,2,25,2);
		break;
		case 12:
		for (uint8_t i = 0; i < 7; i++) color_change_sys(RGB,_BOT,_TOP,base_convert(random()%7+1),30,1,2000);
		break;
		default:
		break;
		}
		
	
		//gen_color_linear(RGB,_BOT,_TOP,10,1,30,0);
		//gen_color_linear(RGB,_BOT,_TOP,10,1,30,2);
		//gen_color_linear(RGB,_BOT,_TOP,10,1,30,1);
		//gen_color_linear(RGB,_BOT,_TOP,10,1,100,3);
		//
		//
		//gen_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),25,5,120,0);
		//gen_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),25,5,60,3);
	//	gen_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),25,5,60,2);
		//gen_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),25,5,120,1);
		//
		
		
		// gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),20,2,50,0);
		 //gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),20,2,25,3);
		//gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),20,2,50,1);
		//gen_soft_two_color(RGB,_BOT,_TOP,base_convert(random()%7+1),base_convert(random()%7+1),20,2,25,2);
		//
	//	for (uint8_t i = 0; i < 7; i++) color_change_sys(RGB,_BOT,_TOP,base_convert(random()%7+1),30,1,2000);
		
		
		
    }
}

