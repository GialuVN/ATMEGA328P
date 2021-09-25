/*
 * main.cpp
 *
 * Created: 11/16/2015 9:13:06 AM
 * Author : RnD
 */ 

#include <avr/io.h>
#include "DMX_effect.h"
#include "DMX_standard.h"
Color_pack RGB[max_led];
int main(void)
{
	DMX_Init(MYUBRR);
    /* Replace with your application code */
	set_base_color(RGB,_BOT,_TOP,255,255,255);
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

    while (1) 
    {
		
		gen_color_linear(RGB,_BOT,_TOP,30,15,30,1);
		gen_color_linear(RGB,_BOT,_TOP,30,10,30,2);
		gen_color_linear(RGB,_BOT,_TOP,30,10,30,0);
		gen_color_linear(RGB,_BOT,_TOP,30,10,30,3);
		
	
	gen_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),80,1,100,0);
	gen_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),80,1,100,1);
	//
	//gen_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),200,2,50,3);
	//gen_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),200,2,50,2);
	
	gen_soft_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%6+1)),20,15,10,0);
	gen_soft_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),20,15,10,3);
	gen_soft_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),20,15,10,1);
	gen_soft_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),20,15,10,2);
	
	for (uint8_t i = 0; i < 7; i++)
	{
		color_change_sys(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),3,1,2000);
	}
	
	//
	//gen_color_linear()
	//gen_color_linear(RGB,_BOT,_TOP,10,1,30,0);
	//gen_color_linear(RGB,_BOT,_TOP,10,1,30,2);
	//gen_color_linear(RGB,_BOT,_TOP,10,1,30,1);
	//gen_color_linear(RGB,_BOT,_TOP,10,1,100,3);
	//
	//
	//gen_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),25,5,120,0);
	//gen_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),25,5,60,3);
	//gen_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),25,5,60,2);
	//gen_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),25,5,120,1);
	//
	//gen_soft_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),20,2,50,0);
	//gen_soft_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),20,2,25,3);
	//gen_soft_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),20,2,50,1);
	//gen_soft_two_color(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),base_convert((Mycolors)(rand()%7+1)),20,2,25,2);
	//
	//for (uint8_t i = 0; i < 7; i++)
	//{
		//color_change_sys(RGB,_BOT,_TOP,base_convert((Mycolors)(rand()%7+1)),100,1,2000);
	//}
	//
//

		
    }
}

