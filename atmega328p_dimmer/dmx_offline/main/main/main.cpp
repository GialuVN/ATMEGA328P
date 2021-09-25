/*
 * main.cpp
 *
 * Created: 10/8/2015 8:48:01 AM
 * Author : RnD
 */ 

#include <avr/io.h>
#include "triac_driver.h"
#include "effect_classic.h"
#include "DMX_pro.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>

const uint8_t border4_1[] PROGMEM = {8,32,64,128};
const uint8_t border4_2[] PROGMEM = {128,64,32,8};
const uint8_t border4_3[] PROGMEM = {128,16,16,16};
const uint8_t border4_4[] PROGMEM = {16,128,128,128};


const uint8_t border3_1[] PROGMEM = {8,64,128};
const uint8_t border3_2[] PROGMEM = {128,64,8};

const uint8_t border3_3[] PROGMEM = {128,32,32};
const uint8_t border3_4[] PROGMEM = {128,128,32};

uint8_t gray_scale[max_port];


uint8_t star_mode;
uint8_t wind_mode;

int main(void)
{
	
	wdt_enable(WDTO_250MS);
	timer0_init();
	dmxcontrol_default();
	rota_group_default();
	dmxctr_using(A1,A16);
	dmxctr_open();
	rota_disable();
	dimmer_init();
	dmxcontrol_default();
	rota_group_default();
	dmxctr_config_value(0,MAX_AUTO_CHANNEL-1,enable,1);
	star_mode = random()%4;
	wind_mode =  random()%4;

	//light_appear(0,15, gray_scale,2,10,0);
	//light_appear(0,15, gray_scale,2,10,1);
	
		
		while(1)
		{
			dmxctr_config_ref(0,MAX_AUTO_CHANNEL-1,RESOLUS,0);
			dmxctr_config_value(0,15,enable,1);
			dmxctr_using(0,15);
			
			dmxctr_close();
			
			switch (wind_mode)
			{
				case 0:
				//GIO THU VAO 2
				dmxctr_config_vector(A10,A15,gray,RESOLUS,0);
				dmxctr_config_vector(A10,A15,ondelay,300,300);
				dmxctr_config_vector(A10,A15,hold,50,50);
				dmxctr_config_vector(A10,A15,fadein,10,10);
				dmxctr_config_vector(A10,A15,fadeout,10,10);
				dmxctr_config_value(A10,A15,mode,mode_minus);
				dmxctr_config_value(A10,A15,output,output_reverse);
				wind_mode = 1;
				
				break;
				case 1:
				//GIO TOA RA 2
				dmxctr_config_vector(A10,A15,gray,0,RESOLUS);
				dmxctr_config_vector(A10,A15,ondelay,300,300);
				dmxctr_config_vector(A10,A15,hold,50,50);
				dmxctr_config_vector(A10,A15,fadein,10,10);
				dmxctr_config_vector(A10,A15,fadeout,10,10);
				dmxctr_config_value(A10,A15,mode,mode_minus);
				dmxctr_config_value(A10,A15,output,output_reverse);
				wind_mode =2;
				break;
				case 2:
				//GIO THU VAO 1
				
				dmxctr_config_vector(A10,A15,gray,0,RESOLUS);
				dmxctr_config_vector(A10,A15,ondelay,300,300);
				dmxctr_config_vector(A10,A15,hold,50,50);
				dmxctr_config_vector(A10,A15,fadein,10,10);
				dmxctr_config_vector(A10,A15,fadeout,10,10);
				dmxctr_config_value(A10,A15,mode,mode_minus);
				dmxctr_config_value(A10,A15,output,output_normal);
				
				wind_mode = 3;
				break;
				default:
				//GIO THU VAO 2
				dmxctr_config_vector(A10,A15,gray,RESOLUS,0);
				dmxctr_config_vector(A10,A15,ondelay,300,300);
				dmxctr_config_vector(A10,A15,hold,50,50);
				dmxctr_config_vector(A10,A15,fadein,10,10);
				dmxctr_config_vector(A10,A15,fadeout,10,10);
				dmxctr_config_value(A10,A15,mode,mode_minus);
				dmxctr_config_value(A10,A15,output,output_normal);
				wind_mode = 0;
				break;
			}
			
			switch(star_mode)
			{
				
				case 0:
				//NGOI SAO LAP LANH
				
				dmxctr_config_vector(A1,A9,gray,0,0);
				dmxctr_config_vector(A1,A9,ondelay,200,50);
				dmxctr_config_vector(A1,A9,hold,50,100);
				dmxctr_config_vector(A1,A9,fadein,10,10);
				dmxctr_config_vector(A1,A9,fadeout,10,10);
				dmxctr_config_value(A1,A9,mode,mode_minus);
				dmxctr_config_value(A1,A9,output,output_normal);
				
				star_mode = 1;
				break;
				case 1:
				//NGOI SAO CHAY LEN 1
				dmxctr_config_vector(A1,A9,gray,0,RESOLUS);
				dmxctr_config_vector(A1,A9,ondelay,50,50);
				dmxctr_config_vector(A1,A9,hold,500,500);
				dmxctr_config_vector(A1,A9,fadein,10,10);
				dmxctr_config_vector(A1,A9,fadeout,10,10);
				dmxctr_config_value(A1,A9,mode,mode_minus);
				dmxctr_config_value(A1,A9,output,output_normal);
				
				star_mode = 2;
				break;
				case 2:
				
				//NGOI SAO CHAY LEN 2
				
				dmxctr_config_vector(A1,A9,gray,0,RESOLUS);
				dmxctr_config_vector(A1,A9,ondelay,50,50);
				dmxctr_config_vector(A1,A9,hold,500,500);
				dmxctr_config_vector(A1,A9,fadein,10,10);
				dmxctr_config_vector(A1,A9,fadeout,10,10);
				dmxctr_config_value(A1,A9,mode,mode_minus);
				dmxctr_config_value(A1,A9,output,output_reverse);
				star_mode = 3;
				break;
				case 3:
				//NGOI SAO TOA RA
				dmxctr_config_vector(A1,A4,gray,RESOLUS,0);
				dmxctr_config_vector(A5,A9,gray,0,RESOLUS);
				dmxctr_config_vector(A1,A9,ondelay,50,50);
				dmxctr_config_vector(A1,A9,hold,500,500);
				dmxctr_config_vector(A1,A9,fadein,10,10);
				dmxctr_config_vector(A1,A9,fadeout,10,10);
				dmxctr_config_value(A1,A9,mode,mode_minus);
				dmxctr_config_value(A1,A9,output,output_reverse);
				star_mode = 4;
				break;
				
				default:
				dmxctr_config_vector(A1,A4,gray,0,RESOLUS);
				dmxctr_config_vector(A5,A9,gray,RESOLUS,0);
				dmxctr_config_vector(A1,A9,ondelay,50,50);
				dmxctr_config_vector(A1,A9,hold,500,500);
				dmxctr_config_vector(A1,A9,fadein,10,10);
				dmxctr_config_vector(A1,A9,fadeout,10,10);
				dmxctr_config_value(A1,A9,mode,mode_minus);
				dmxctr_config_value(A1,A9,output,output_reverse);
				star_mode = 0;
				break;
			}
			dmxctr_open();
			delay_ms(60000);
		}

		
		
		
		//HIEU UNG KHOI DONG
		//Block_init(A1,A6,RESOLUS/2,RESOLUS);
		//
		//Block_gray(0,0);
		//Block_delay(1,500,100,1);
		//Block_fade(10,10,30,30);
		//Block_loop(10,10,mode_minus);
		//Block_output(output_normal);
		//Block_Run();
		//Block_wait();
		//
		//
		////HIEU UNG KHOI DONG
		//Block_init(A1,A16,0,RESOLUS);
		//Block_gray(0,0);
		//Block_delay(100,1000,10,500);
		//Block_fade(20,20,20,20);
		//Block_loop(10,10,mode_minus);
		//Block_output(output_normal);
		//Block_Run();
		//Block_wait();
		
		//Block_init(A1,A16,0,RESOLUS);
		//Block_gray(0,0);
		//Block_delay(5000,1,1,1000);
		//Block_fade(10,10,10,10);
		//Block_loop(10,10,mode_one);
		//Block_output(output_normal);
		//Block_Run();
		//Block_wait();

		
		
		
	//fill_drop(0,15,gray_scale,5,16,0);
	//fill_drop(0,15,gray_scale,5,16,1);
	//random_light_st1(0,15,gray_scale,2,10000,100);
	//random_light_st2(0,15,gray_scale,10,1000);
	
    }





