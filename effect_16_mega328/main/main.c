/*
 * main.c
 *
 * Created: 8/22/2013 6:24:51 PM
 *  Author: HI
 */ 


#include "PWM.h"
#include "pwm_general.h"
#include "RGB_control.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <ctype.h>
#include <inttypes.h>
#include <math.h>
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
	
const uint8_t border_51[] PROGMEM = {1,5,15,25,50};	
const uint8_t border_52[] PROGMEM = {50,25,15,5,1};	
	
uint8_t vien[4];	
 uint8_t gray_scale[DATA_LEN];
int main(void)
{
	
	wdt_reset();
	wdt_enable(WDTO_250MS);
	output_init();
	timer2_CTC_init();
	
	DDRD &=~(1<<PIND2);
	PORTD|=1<<PIND2;
	DDRD |=(1<<PIND1);
	
	
	sei();
	_delay_ms(100);
	light_appear(0,15, gray_scale,10,2,0);
	light_appear(0,15, gray_scale,10,2,1);
	light_appear(0,15, gray_scale,10,2,2);
	light_appear(0,15, gray_scale,10,2,3);
    while(1)
    {
		
		
// anh quang

//TAT CA
soft_flash(0,7,5,2,0,resolution);
sleep(100,gray_scale);
//TIEM VANG
pendul(0,2,gray_scale,20,3,5,resolution,0);
sleep(100,gray_scale);
pendul(3,7,gray_scale,20,3,5,resolution,0);
sleep(100,gray_scale);
//DIA CHI
soft_flash(0,2,4,2,0,resolution);
sleep(50,gray_scale);
soft_flash(3,7,4,2,0,resolution);
sleep(50,gray_scale);
//TA CA SANG LEN
light_appear(0,7, gray_scale,10,2,0);
sleep(100,gray_scale);
light_appear(0,7, gray_scale,10,2,1);
sleep(300,gray_scale);
//TAT CA
sleep(200,gray_scale);
light_appear(0,7, gray_scale,10,2,2);
sleep(100,gray_scale);
light_appear(0,7, gray_scale,10,2,3);
sleep(300,gray_scale);
soft_flash(0,2,4,2,0,resolution);
sleep(50,gray_scale);
soft_flash(3,7,4,2,0,resolution);
sleep(50,gray_scale);
sleep(300,gray_scale);
////////////////////////////////////////////////////////

		//
	////	light_appear(0,15, gray_scale,10,2,2);
	////	light_appear(0,15, gray_scale,10,2,3);
		//
//
	////TAT CA
	//soft_flash(1,15,5,2,0,resolution);
	//sleep(100,gray_scale);
	//soft_flash(0,0,5,2,0,resolution);
	//sleep(100,gray_scale);
	////HOA VAN DAU CUOI
	//soft_flash(0,0,4,2,0,resolution);
	//sleep(50,gray_scale);
	////TIEM VANG
	//pendul(1,2,gray_scale,35,3,5,resolution,0);
	//sleep(50,gray_scale);
	////KIM HOANG 
	//pendul(3,5,gray_scale,30,3,5,resolution,0);
	//sleep(50,gray_scale);
	//pendul(6,10,gray_scale,25,3,5,resolution,0);
	//sleep(50,gray_scale);
	////HOANG YEN
	//pendul(11,12,gray_scale,35,3,5,resolution,0);
	//sleep(50,gray_scale);
	////LOGO HY
	//soft_flash(13,13,4,2,0,resolution);
	//sleep(50,gray_scale);
	////CHUYEN...
	//soft_flash(14,14,4,2,0,resolution);
	//sleep(50,gray_scale);
	////DIA CHI
	//soft_flash(15,15,4,2,0,resolution);
	//sleep(200,gray_scale);
	////TA CA SANG LEN
	//light_appear(0,15, gray_scale,10,2,0);
	//sleep(100,gray_scale);
	//light_appear(0,15, gray_scale,10,2,1);
	//sleep(300,gray_scale);
	////TAT CA
	//soft_flash(1,15,5,2,0,resolution);
	//sleep(100,gray_scale);
	//soft_flash(0,0,5,2,0,resolution);
	//sleep(100,gray_scale);
	////HOA VAN DAU CUOI
	//soft_flash(0,0,4,2,0,resolution);
	//sleep(50,gray_scale);
	////TIEM VANG
	//soft_flash(1,2,4,2,0,resolution);
	//sleep(50,gray_scale);
	////KIM HOANG 
	//soft_flash(3,10,4,2,0,resolution);
	//sleep(50,gray_scale);
	////HOANG YEN
	//soft_flash(11,12,4,2,0,resolution);
	//sleep(50,gray_scale);
	////LOGO HY
	//soft_flash(13,13,4,2,0,resolution);
	//sleep(50,gray_scale);
	////CHUYEN...
	//soft_flash(14,14,4,2,0,resolution);
	//sleep(50,gray_scale);
	////DIA CHI
	//soft_flash(15,15,4,2,0,resolution);
	//sleep(200,gray_scale);
	//light_appear(0,15, gray_scale,10,2,2);
	//sleep(100,gray_scale);
	//light_appear(0,15, gray_scale,10,2,3);
	//sleep(300,gray_scale);

	
	//////////////////////////dai - ichi life///////////////////////////////////
	//
		//dai-ichi life
		//if(PIND&(1<<PIND2)) light_appear(0,12, gray_scale,10,3,1);
		//else light_appear(0,12, gray_scale,10,10,1);
		
	//	hard_flash(13,15,gray_scale,100,3,1);
		
	//	sleep(200,gray_scale);
		
/////////////////////////////gage////////////////////////////////
		////vien5
		//border(0,4,gray_scale,12,15,border_51,1);
		//border(0,4,gray_scale,12,15,border_52,0);
		//
		//hard_flash(5,6,gray_scale,50,3,1);
		//hard_flash(7,8,gray_scale,50,3,1);
		//hard_flash(9,10,gray_scale,50,3,1);
		
//////////////////////////////////////////////////////////////////////////
		
		
		//fill_drop(0,15,gray_scale,5,8,0);
		//fill_drop(0,15,gray_scale,5,8,1);
		
		//random_light_st1(0,15,gray_scale,2,10000,100);
	//	random_light_st2(0,15,gray_scale,1,10000);


		//// nha khoa ha thanh//
		////vien chay jot nuoc
		//pgm_read_block(vien,border4_1,4);
		//border(0,3,gray_scale,10,40,vien,1);
		////nha khoa vua chay vua chop
		//running_flash(4,12,gray_scale,5,2,16,1);
		//running_flash(4,12,gray_scale,5,2,resolution,0);
		////tat ca nhap nhay 3 lan
		//soft_flash(0,12,4,3,0,resolution);
		////vien chay jot nuoc
		//pgm_read_block(vien,border4_2,4);
		//border(0,3,gray_scale,10,20,vien,0);
		////nha khoa hieu ung combine
		//fill_combine(4,12,gray_scale,10,10,1);
		//fill_combine(4,12,gray_scale,10,10,0);
		////vien chay jot nuoc
		//pgm_read_block(vien,border4_3,4);
		//border(0,3,gray_scale,10,20,vien,0);
		//pgm_read_block(vien,border4_3,4);
		//border(0,3,gray_scale,10,20,vien,1);
		////vien nhay 3 lan
		//soft_flash(0,3,4,3,0,resolution);
		////nha khoa nhay 3 lan
		//soft_flash(4,12,4,3,0,resolution);
		//
		////vien chay jot nuoc
		//pgm_read_block(vien,border4_4,4);
		//border(0,3,gray_scale,10,20,vien,0);
		//pgm_read_block(vien,border4_4,4);
		//border(0,3,gray_scale,10,20,vien,1);
		//
		//// nha khoa sao bang
		//shooting_star(4,12,gray_scale,5,16,1);
		//shooting_star(4,12,gray_scale,5,16,0);
		//
		//////vien chay jot nuoc
		//pgm_read_block(vien,border4_3,4);
		//border(0,3,gray_scale,10,40,vien,1);
		//////nha khoa hieu ung combine
		//combine(4,12,gray_scale,5,5,16,0);
		//fill_pendul(4,12,gray_scale,5,16,1);
		//sleep(100,gray_scale);
		
		//shooting_star(0,31,gray_scale,3,16,1);
		//shooting_star(0,31,gray_scale,3,16,0);
		//shooting_star(0,31,gray_scale,3,16,1);
		//shooting_star(0,31,gray_scale,3,16,0);
		//
		

	//	soft_flash(0,15,10,2,0,resolution);

//
//
		//
		//
///************************************************************************/
///*			SUA CHUA
			//IPHONE
//
                                                                  //*/
///************************************************************************/	
////
		////VIEN
			//soft_flash(13,15,4,2,0,resolution);
		////SUA CHUA
			//soft_flash(0,6,4,2,0,resolution);
		////PHU KIEN
			//soft_flash(7,7,4,2,0,resolution);	
		////IPHONE+ SASUNG+NOKIA	
			//running_flash(8,10,gray_scale,7,2,16,1);
		////DÁN MÁY T?I NH?C
			//running_flash(11,12,gray_scale,7,2,16,1);
		////TAT CA NHAP NHAY
			//soft_flash(0,15,4,2,0,resolution);
			////dung lai 1s
			//sleep(100,gray_scale);
		//// VIEN CHAY SANG TRAI
			//border(13,15,gray_scale,20,15,border3_1,1);
		//// VIEN CHAY SANG PHAI
			//border(13,15,gray_scale,20,15,border3_2,0);
		////dung lai 1s
			//sleep(100,gray_scale);
		////SUA CHUA
			//combine(0,6,gray_scale,12,5,16,0);
			//fill_combine(0,6,gray_scale,12,16,0);
			////dung lai 1s
			//sleep(100,gray_scale);
			////PHU KIEN
			//soft_flash(7,7,4,2,0,resolution);	
			////IPHONE+ SASUNG+NOKIA	
			//soft_flash(8,10,4,2,0,resolution);
			////DÁN MÁY T?I NH?C
			//soft_flash(11,12,4,2,0,resolution);
		////dung lai 1s
			//sleep(100,gray_scale);
		//// VIEN CHAY SANG TRAI
			//border(13,15,gray_scale,20,15,border3_3,1);
		//// VIEN CHAY SANG PHAI
			//border(13,15,gray_scale,20,15,border3_3,0);
		////QUANG NUI	
			//shooting_star(0,6,gray_scale,10,4,1);
			//shooting_star(0,6,gray_scale,10,4,0);
			//shooting_star(0,6,gray_scale,10,4,1);
			//shooting_star(0,6,gray_scale,10,4,0);
		////dung lai 1s
		//sleep(100,gray_scale);
		////QUANG NUI
		
		
/************************************************************************/
/*			TIEM VANG 
			QUANG NUI
                                                                     */
/************************************************************************/	
////
		////TIEM VANG NHAP NHAY
			//soft_flash(0,1,4,2,0,resolution);
		////QUANG NUI
			//soft_flash(2,9,4,2,0,resolution);
		////MUA BAN
			//soft_flash(10,10,4,2,0,resolution);
		////DICH VU
			//soft_flash(11,11,4,2,0,resolution);
		////VIEN
			//soft_flash(12,15,4,2,0,resolution);
		////dung lai 1s
			//sleep(100,gray_scale);
		//// VIEN CHAY SANG TRAI
			//border(12,15,gray_scale,20,15,border4_1,1);
		//// VIEN CHAY SANG PHAI
			//border(12,15,gray_scale,20,15,border4_2,0);
		////dung lai 1s
			//sleep(100,gray_scale);
		////QUANG NUI
			//combine(2,9,gray_scale,12,5,16,0);
			//fill_combine(2,9,gray_scale,12,16,0);
		//
		////TIEM VANG NHAP NHAY
			//soft_flash(0,1,4,2,0,resolution);
		////MUA BAN
			//soft_flash(10,10,4,2,0,resolution);
		////DICH VU
			//soft_flash(11,11,4,2,0,resolution);
		////VIEN
			//soft_flash(12,15,4,2,0,resolution);
		////dung lai 1s
			//sleep(100,gray_scale);
		//// VIEN CHAY SANG TRAI
			//border(12,15,gray_scale,20,15,border4_3,1);
		//// VIEN CHAY SANG PHAI
			//border(12,15,gray_scale,20,15,border4_3,0);
		////QUANG NUI	
		//shooting_star(2,9,gray_scale,10,4,1);
		//shooting_star(2,9,gray_scale,10,4,0);
		//shooting_star(2,9,gray_scale,10,4,1);
		//shooting_star(2,9,gray_scale,10,4,0);
		////dung lai 1s
		//sleep(100,gray_scale);
		////QUANG NUI
		//running_flash(2,9,gray_scale,7,2,16,1);
			////dung lai 1s
		//sleep(100,gray_scale);
		////TIEM VANG NHAP NHAY
		//soft_flash(0,15,4,2,0,resolution);
		//// VIEN CHAY SANG TRAI
		//border(12,15,gray_scale,20,1,border4_3,1);
		//// VIEN CHAY SANG PHAI
		//border(12,15,gray_scale,20,1,border4_3,0);
		//// VIEN CHAY SANG TRAI
		//border(12,15,gray_scale,20,1,border4_3,1);
		//// VIEN CHAY SANG PHAI
		//border(12,15,gray_scale,20,1,border4_3,0);
			////dung lai 1s
		//sleep(100,gray_scale);
/************************************************************************/
/* GAO THANH TUNG
                                                                 */
/************************************************************************/	
			//
			//soft_flash(0,11,4,2,0,resolution);
			////dung lai 1s
			//sleep(100,gray_scale);
			////gao
			//soft_flash(0,2,4,2,0,resolution);
			////dung lai 1s
			//sleep(100,gray_scale);
			////thanh tung
			//soft_flash(3,11,4,2,0,resolution);
			////dung lai 1s
			//sleep(100,gray_scale);
			////thanh tung chay qua lai
			//pendul(3,11,gray_scale,10,3,16,resolution,0);
			////dung lai 1s
			//sleep(100,gray_scale);
			////gao nhap nhay
			//soft_flash(0,2,4,2,0,resolution);
			////dung lai 1s
			//sleep(100,gray_scale);
			//shooting_star(3,11,gray_scale,10,16,1);
			//shooting_star(3,11,gray_scale,10,16,0);
			////dung lai 1s
			//sleep(100,gray_scale);
			////vua chay vua nhap nhay
			//running_flash(0,2,gray_scale,7,2,16,1);
			//running_flash(0,2,gray_scale,7,2,resolution,0);
			////tat ca nhap nhay
			//soft_flash(0,2,4,2,0,resolution);
				////dung lai 1s
			//sleep(100,gray_scale);
			//combine(3,11,gray_scale,15,5,16,0);
				////dung lai 1s
			//sleep(100,gray_scale);
			//light_appear(3,11, gray_scale,10,10,2);
			//light_appear(3,11, gray_scale,10,10,3);
			////tat ca nhap nhay 2 lan
			////tat ca nhap nhay
			//soft_flash(0,2,4,2,0,resolution);
				////dung lai 5s
			//sleep(500,gray_scale);
		
	 //random_light_st1(0,15,gray_scale,2,40000,180);
	
		
		//
		////tat ca nhap nhay 2 lan
		//soft_flash(0,13,4,2,0,resolution);
		////dung lai 1s
		//sleep(100,gray_scale);
		////chay vien
		//border(0,3,gray_scale,15,20,border4_1,1);
		////am thuc
		//soft_flash(11,12,4,2,0,resolution);
		////dong que
		//soft_flash(4,10,4,2,0,resolution);
		//
		//
		//
		////400m
		//soft_flash(13,13,6,3,0,resolution);
		////chay vien
		//border(0,3,gray_scale,15,20,border4_3,1);
		////dong que chay qua lai
		//pendul(4,10,gray_scale,15,3,16,resolution,0);
//
		////chay vien
		//border(0,3,gray_scale,15,20,border4_4,1);
		//// am thuc nhap nhay
		//soft_flash(11,11,3,3,0,resolution);
		//soft_flash(12,12,3,3,0,resolution);
//
		////vua chay vua nhap nhay
		//running_flash(4,10,gray_scale,7,2,16,1);
		//running_flash(4,10,gray_scale,7,2,resolution,0);
		//
		////tat ca nhap nhay
		//soft_flash(0,13,4,2,0,resolution);
		//
	/////////////bac lieu cong chao kieu2////////////
	
	
	
		//bytwo(0,15,gray_scale,35,20,0,0,2);
		//bytwo(0,15,gray_scale,35,20,0,0,1);
		//
		//
		//
		//radian_gen(0,7,gray_scale,resolution,0,0,0);
		//radian_gen(8,15,gray_scale,resolution,1,0,0);
		//
		//n_rota(0,15,gray_scale,1,35,150);
		//n_rota(0,15,gray_scale,0,35,150);
		//
		//bytwo(0,15,gray_scale,35,20,0,0,0);
		//bytwo(0,15,gray_scale,35,20,0,0,3);



	/////////////bac lieu cong chao kieu1/////////

		//
		//odd_even(0,15,gray_scale,4,10,1);
		//
		//sleep(100,gray_scale);
		//
		//radian_gen(0,7,gray_scale,resolution,0,0,0);
		//radian_gen(8,15,gray_scale,resolution,1,0,0);
		//
		//n_rota(0,15,gray_scale,1,30,150);
		//n_rota(0,15,gray_scale,0,30,150);
		//
		//sleep(100,gray_scale);
		//shooting_star(0,15,gray_scale,20,16,1);
		//shooting_star(0,15,gray_scale,20,16,0);
		//shooting_star(0,15,gray_scale,20,16,1);
		//shooting_star(0,15,gray_scale,20,16,0);
		//shooting_star(0,15,gray_scale,20,16,1);
		//shooting_star(0,15,gray_scale,20,16,0);
		//
		//sleep(100,gray_scale);
		//growing(0,15,gray_scale,25,5,6,2);
		//downing(0,15,gray_scale,25,5,6,2);
		//growing(0,15,gray_scale,25,5,6,2);
		//downing(0,15,gray_scale,25,5,6,2);
		//growing(0,15,gray_scale,25,5,6,2);
		//downing(0,15,gray_scale,25,5,6,2);
		//
		//sleep(100,gray_scale);
		//
		//combine(0,15,gray_scale,20,5,16,0);
		//combine(0,15,gray_scale,20,5,64,1);
		//
		//sleep(100,gray_scale);
		//
		//pendul(0,15,gray_scale,20,3,16,64,2);
		//sleep(100,gray_scale);
		
/////////////////////////////////////////////////////		
		//anh duc
		
		////tat ca nhap nhay 2 lan
	//	soft_flash(0,7,6,2,0,resolution);
		////dung lai 1s
		//sleep(50,gray_scale);
		//
		////chay vien
		//border(0,3,gray_scale,20,20,border4_1,1);
		//border(0,3,gray_scale,20,20,border4_2,0);
		//
		////goi dau massa nhap nhay
		//soft_flash(4,5,6,2,0,resolution);
		////goi dau massa nhap nhay
		//soft_flash(6,7,6,2,0,resolution);
		//
		////chay vien
		//border(0,3,gray_scale,20,20,border4_4,1);
		//border(0,3,gray_scale,20,20,border4_4,0);
		//
		//
		//
		//running_flash(4,7,gray_scale,15,3,resolution,1);
		//running_flash(4,7,gray_scale,15,3,resolution,0);
///////////////////////////////////////////////////////		
		
		
		
		//for (uint8_t i = 0;i<50;i++)
		//{
			//
			//if ((i%4)==0) load_value(8,11,gray_scale,border4_1);
			//if ((i%3)==0) load_value(12,14,gray_scale,border3_1);
			//
			//pwm_gen(10,resolution,gray_scale,port);
			//rotatal(8,11,gray_scale,1,1);
			//
			//rotatal(12,14,gray_scale,1,1);
//
		//}
		
		
		////ta ca sang
		//set_value(0,7,resolution,gray_scale);
		////dung lai 2s
		//sleep(20,gray_scale);
	//
		//// chay qua lai
		//pendul(0,7,gray_scale,6,3,8,resolution,0);
		////chay vao ra
		//combine(0,7,gray_scale,6,3,16,0);
		//
		////dung lai 2s
		//sleep(100,gray_scale);
		//
			//
		////cafe nhap nhay 2 lan
		//soft_flash(15,15,4,2,0,resolution);
		////dung lai 1s
		//sleep(50,gray_scale);
		//
		//
		//// vien + li cafe
		//for (uint8_t i = 0;i<100;i++)
		//{
			//
			//if ((i%4)==0) load_value(8,11,gray_scale,border4_2);
			//if ((i%3)==0) load_value(12,14,gray_scale,border3_2);
			//
			//pwm_gen(10,resolution,gray_scale,port);
			//rotatal(8,11,gray_scale,1,0);
			//rotatal(12,14,gray_scale,1,1);
		//}
		//
		//fill_pendul(0,7,gray_scale,5,10,1);
		////dung lai 2s
		//sleep(100,gray_scale);
		//fill_drop(0,7,gray_scale,5,8,0);
		//
			////dung lai 2s
		//sleep(100,gray_scale);
	//
		//for (uint8_t i = 0;i<100;i++)
		//{
			//
			//if ((i%4)==0) load_value(8,11,gray_scale,border4_2);
			//if ((i%3)==0) load_value(12,14,gray_scale,border3_1);
			//
			//pwm_gen(10,resolution,gray_scale,port);
			//rotatal(8,11,gray_scale,1,0);
			//
			//rotatal(12,14,gray_scale,1,1);
//
		//}
		//
		//
		//set_value(0,14,resolution,gray_scale);
			////dung lai 1s
		//sleep(100,gray_scale);
				//
		////cafe nhap nhay 2 lan
		//soft_flash(15,15,4,2,0,resolution);
				//
		////tat ca nhap nhay 2 lan
		//soft_flash(0,7,4,2,0,resolution);
		
		//
		//
		//
		//
		//
		//for (uint8_t i = 0;i<100;i++)
		//{
			//
			//if ((i%4)==0) load_value(8,11,gray_scale,border4_2);
			//if ((i%3)==0) load_value(12,14,gray_scale,border3_1);
			//
			//pwm_gen(10,resolution,gray_scale,port);
			//rotatal(8,11,gray_scale,1,0);
			//
			//rotatal(12,14,gray_scale,1,1);
//
		//}
		//
		//set_value(0,14,resolution,gray_scale);
//
//


		
		////vien chay jot nuoc
		//pgm_read_block(vien,border4_1,4);
		//border(16,19,gray_scale,10,40,vien,1);
		
		
		
//
			////t?t c? nh?p nháy
		//
			////tat ca nhap nhay 2 lan
			//soft_flash(0,7,4,3,0,resolution);
			////dung lai 1s
			//sleep(10,gray_scale);
			//// 2 diem nhap nhay xen ke
			//twopoint(6,7,gray_scale,5,4,1);
			////d?ng l?i 3s
			//sleep(300,gray_scale);
			//pendul(0,4,gray_scale,10,3,8,resolution,0);
			//combine(0,4,gray_scale,10,5,16,0);
			////d?ng l?i 3s
			//sleep(300,gray_scale);
			////tat ca nhap nhay 2 lan
			//soft_flash(0,4,4,3,0,resolution);
			////tat ca nhap nhay 2 lan
			//soft_flash(5,5,4,3,0,resolution);
			////tat ca nhap nhay 2 lan
			//soft_flash(6,6,4,3,0,resolution);
			////tat ca nhap nhay 2 lan
			//soft_flash(7,7,4,3,0,resolution);
			////d?ng l?i 3s
			//sleep(300,gray_scale);
			//running_flash(0,4,gray_scale,5,6,10,0);
			//running_flash(0,4,gray_scale,5,6,resolution,1);
			////d?ng l?i 3s
			//sleep(300,gray_scale);
		//
		
/////////////////hieu ung led RGB/////////////////////////////////
		//set_value(0,23,0,gray_scale);
		//set_value(0,random()%24,resolution,gray_scale);
		//out_color(24,25,26,gray_scale,set_color(random()%7));
		//sleep(10,gray_scale);
		
		//set_value(0,23,0,gray_scale);
		//set_value(8,15,resolution,gray_scale);
		//out_color(24,25,26,gray_scale,set_color(green));
		//sleep(1,gray_scale);
		//
		//set_value(0,23,0,gray_scale);
		//set_value(16,23,resolution,gray_scale);
		//out_color(24,25,26,gray_scale,set_color(blue));
		//sleep(1,gray_scale);
		
		//
		//fill_combine(0,16,gray_scale,5,10,0);
				////dung lai 15s
	//	sleep(1500,gray_scale);
		//
		//set_value_slowly(0,23,resolution,gray_scale,5,0);
		
		
		//shooting_star(0,23,gray_scale,3,16,1);
		
		//auto_change_together(24,25,26,set_color(random()%7),1,2);
		////auto_change_together(24,25,26,set_RGB(resolution,0,0),1,2);
//
		//shooting_star(0,23,gray_scale,3,16,0);
		//shooting_star(0,23,gray_scale,3,16,1);
		//shooting_star(0,23,gray_scale,3,16,0);
		//shooting_star(0,23,gray_scale,3,16,1);
		//shooting_star(0,23,gray_scale,3,16,0);
		
				////dung lai 15s
		//sleep(1500,gray_scale);
		//growing(0,16,gray_scale,5,8,6,2);
		//soft_flash(0,16,4,2,0,resolution);
				////dung lai 15s
		//sleep(1500,gray_scale);
		//fill_pendul(0,16,gray_scale,5,15,1);
		////dung lai 15s
		//sleep(1500,gray_scale);
		
		
		
		
		////tat ca nhap nhay 2 lan
		//soft_flash(0,4,4,2,0,resolution);
		////dung lai 15s
		//sleep(1500,gray_scale);
		//// trung tam nhap nhay 2 lan
		//soft_flash(4,4,4,2,0,resolution);
		////dang ngoc nhap nhay 2 lan
		//soft_flash(2,3,4,2,0,resolution);
		////dung lai 15s
		//sleep(1500,gray_scale);
		//// trai phai nhap nhay 2 lan
		//soft_flash(0,1,4,2,0,resolution);
		////dung lai 15s
		//sleep(3000,gray_scale);
		//
		
///////////////////////////////////////////////////////////		


////////////////////////anh dao hotel/////////////////////////		
		////anh ?ào nh?p nháy 3 l?n
		//soft_flash(0,5,4,3,0,resolution);
		//// mekong nh?p nháy 3 l?n
		//soft_flash(6,11,4,3,0,resolution);
		//// hotel nh?p nháy 3 l?n
		//soft_flash(12,12,4,3,0,resolution);
		////d?ng l?i 3s
		//sleep(300,gray_scale);
		//running_flash(0,12,gray_scale,5,6,10,0);
		//running_flash(0,12,gray_scale,5,6,resolution,1);
		////d?ng l?i 3s
		//sleep(300,gray_scale);
		//fill_pendul(0,11,gray_scale,10,10,1);
		//soft_flash(12,12,4,3,0,resolution);
		////d?ng l?i 3s
		//sleep(300,gray_scale);
		//fill_drop(0,11,gray_scale,5,8,1);
		////d?ng l?i 3s
		//sleep(300,gray_scale);
		//pendul(0,11,gray_scale,10,3,8,resolution,0);
		//combine(0,11,gray_scale,10,5,16,0);
		//// hotel nh?p nháy 3 l?n
		//soft_flash(12,12,4,3,0,resolution);
		////d?ng l?i 3s
		//sleep(300,gray_scale);
	
		
////////////////////// anh ?ào 2///////////////////////////////
		////anh ?ào nh?p nháy 3 l?n
		//soft_flash(0,5,4,3,0,resolution);
		//// mekong nh?p nháy 2 l?n
		//soft_flash(6,11,4,3,0,resolution);
		//// hotel nh?p nháy 3 l?n
		//soft_flash(12,12,4,3,0,resolution);
		////d?ng l?i 3s
		//sleep(600,gray_scale);
		////running_flash(0,12,gray_scale,5,6,10,0);
		////running_flash(0,12,gray_scale,5,6,resolution,1);
		//////d?ng l?i 3s
		//soft_flash(0,12,4,3,0,resolution);
		////sleep(600,gray_scale);
		////light_appear(0,12, gray_scale,8,2,0);
		////
		////light_appear(0,12, gray_scale,8,2,1);
		////d?ng l?i 3s
		//sleep(1000,gray_scale);
		//
	
/////////////////////////////////////////////////////////	
	
	
		
	//	bytwo(0,11,gray_scale,5,5,10,1,1);
		
	//	bytwo(0,11,gray_scale,5,5,10,1,2);
		
	
			//fill_drop(0,11,gray_scale,5,8,0);
		//shooting_star(0,11,gray_scale,5,16,0);
		
		//pendul(0,11,gray_scale,10,3,8,resolution,0);
		//combine(0,11,gray_scale,10,5,16,0);
		//fill_combine(0,11,gray_scale,10,10,0);
		//fill_pendul(0,11,gray_scale,5,10,1);
		
		
		
		//set_value(2,2,0,gray_scale);
		//for (uint8_t i = 0;i<5;i++)
		//{
			//twopoint(0,1,gray_scale,2,10,0);
			//twopoint(0,1,gray_scale,2,10,1);
		//}
		//hard_flash(0,0,gray_scale,6,10,1);
		//hard_flash(1,1,gray_scale,6,10,1);
		//
		//soft_flash(2,2,4,3,0,resolution);
		//hard_flash(2,2,gray_scale,6,10,1);
		//sleep(500,gray_scale);
		//
		//running_flash(3,7,gray_scale,5,6,10,1);
		//running_flash(3,7,gray_scale,5,6,10,0);
		//
		//sleep(300,gray_scale);
		//pendul(3,7,gray_scale,10,3,8,resolution,0);
		//sleep(100,gray_scale);
		//
		//hard_flash(3,7,gray_scale,9,10,1);
		//sleep(100,gray_scale);
		//
		//shooting_star(3,7,gray_scale,10,16,1);
		//shooting_star(3,7,gray_scale,10,16,0);
		//sleep(100,gray_scale);
		//
		//hard_flash(0,7,gray_scale,9,10,1);
		//sleep(500,gray_scale);
		//
		
		
		
		
		
		
		
		
		
		
		
		
		//
		//
	//pendul(0,16,gray_scale,4,3,220,10,0);
	//pendul(0,16,gray_scale,4,3,220,10,1);
	//pendul(0,16,gray_scale,4,3,220,10,2);
	//pendul(0,16,gray_scale,4,3,220,10,3);
	//
	//pendul(0,16,gray_scale,4,3,22,100,0);
	//pendul(0,16,gray_scale,4,3,22,100,1);
	//pendul(0,16,gray_scale,4,3,22,100,2);
	//pendul(0,16,gray_scale,4,3,22,100,3);	
	//
	
	//
	//
//// nha khoa ha thanh//
	//
	////vien chay jot nuoc
	//pgm_read_block(vien,border4_1,4);
	//border(16,19,gray_scale,10,40,vien,1);
	////nha khoa vua chay vua chop
	//running_flash(0,6,gray_scale,5,2,16,1);
	//running_flash(0,6,gray_scale,5,2,resolution,0);
	////ha thanh vua chay vua chop
	//running_flash(7,13,gray_scale,5,2,16,1);
	//running_flash(7,13,gray_scale,5,2,resolution,0);
	////tat ca nhap nhay 3 lan
	//soft_flash(0,19,4,3,0,resolution);
	////vien chay jot nuoc
	//pgm_read_block(vien,border4_2,4);
	//border(16,19,gray_scale,10,20,vien,0);
	////nha khoa hieu ung combine
	//fill_combine(0,6,gray_scale,10,10,1);
	//fill_combine(0,6,gray_scale,10,10,0);
	////ha thanh hieu ung combine
	//fill_combine(7,13,gray_scale,10,10,1);
	//fill_combine(7,13,gray_scale,10,10,0);
	//
	////vien chay jot nuoc
	//pgm_read_block(vien,border4_3,4);
	//border(16,19,gray_scale,10,20,vien,0);
	//pgm_read_block(vien,border4_3,4);
	//border(16,19,gray_scale,10,20,vien,1);
	////vien nhay 3 lan
	//soft_flash(16,19,4,3,0,resolution);
	////nha khoa nhay 3 lan
	//soft_flash(0,6,4,3,0,resolution);
	////nha khoa nhay 3 lan
	//soft_flash(7,13,4,3,0,resolution);
	////vien chay jot nuoc
	//pgm_read_block(vien,border4_4,4);
	//border(16,19,gray_scale,10,20,vien,0);
	//pgm_read_block(vien,border4_4,4);
	//border(16,19,gray_scale,10,20,vien,1);
	//
//
		//// nha khoa sao bang
		//shooting_star(0,6,gray_scale,5,16,1);
		//shooting_star(0,6,gray_scale,5,16,0);
		//set_value(0,13,resolution,gray_scale);
		//// ha thanh sao bang
		//shooting_star(7,13,gray_scale,5,16,1);
		//shooting_star(7,13,gray_scale,5,16,0);
		//set_value(0,13,resolution,gray_scale);
		//// nha khoa ha thanh sao bang
		//shooting_star(0,13,gray_scale,5,16,1);
		//shooting_star(0,13,gray_scale,5,16,0);
		//set_value(0,13,resolution,gray_scale);
		//////vien chay jot nuoc
		//pgm_read_block(vien,border4_3,4);
		//border(16,19,gray_scale,10,40,vien,1);
		//////nha khoa hieu ung combine
		//combine(0,6,gray_scale,5,5,16,0);
		//fill_pendul(0,6,gray_scale,5,16,1);
		//////ha thanh hieu ung combine
		//combine(7,13,gray_scale,5,5,16,0);
		//fill_pendul(7,13,gray_scale,4,16,1);
		//set_value(0,13,resolution,gray_scale);
				
////////////////////////////////////////////////////////////////////		
		//hao hoa hotel
		
		////soft_flash(0,5,4,3,0,resolution);
		////soft_flash(6,10,4,3,0,resolution);
		////sleep(500,gray_scale);
		////running_flash(0,5,gray_scale,5,2,16,1);
		////running_flash(0,5,gray_scale,5,2,resolution,0);
		////sleep(300,gray_scale);
		////pendul(0,5,gray_scale,10,3,16,1);
		////
		////sleep(300,gray_scale);
		////shooting_star(6,10,gray_scale,10,16,1);
		////shooting_star(6,10,gray_scale,10,16,0);
		////
		////sleep(300,gray_scale);
		////fill_drop(0,5,gray_scale,8,6,1);
		////sleep(300,gray_scale);
	//////////////////////////////////////////////////////////////
		
		
		
		
		
		
		
		
		
		
		
		
		
	
	//
	//pgm_read_block(vien,border4_2,4);	
	//border(7,10,gray_scale,20,10,vien,0);	
	//
	//pgm_read_block(vien,border4_3,4);
	//border(7,10,gray_scale,20,10,vien,0);	
	//
	//pgm_read_block(vien,border4_4,4);
	//border(7,10,gray_scale,20,10,vien,0);	
	//
////running_flash(0,31,gray_scale,5,2,10,0);
////running_flash(0,31,gray_scale,5,2,10,1);
////running_flash(0,31,gray_scale,5,3,10,1);		
		////hard_flash(0,31,gray_scale,3,3,1);
		////sleep(10,gray_scale);
		////
		////
////combine(0,30,gray_scale,5,50,0);
////fill_pendul(2,29,gray_scale,2,40,1);
//fill_combine(0,31,gray_scale,2,10,1);
//fill_combine(0,31,gray_scale,2,10,0);	
		////set_value_slowly(0,31,128,gray_scale,5,1);
		////set_value_slowly(0,31,50,gray_scale,5,0);
		////
//
//
	//fill_seed(0,31,gray_scale,1,20,0);
	//fill_seed(0,31,gray_scale,1,20,1);
	//fill_seed(0,31,gray_scale,1,20,2);
	//fill_seed(0,31,gray_scale,1,20,3);
	//
	////seed(0,14,gray_scale,1,3,3);
	//
	////seed(0,14,gray_scale,1,3,0);
	////seed(0,14,gray_scale,1,3,1);	
		////
	//growing(0,31,gray_scale,5,10,10,3);
	//downing(0,31,gray_scale,5,10,10,3);
	//growing(0,31,gray_scale,5,10,10,2);
	//downing(0,31,gray_scale,5,10,10,2);
	////
	////growing(0,31,gray_scale,10,10,5,0);
	////downing(0,31,gray_scale,10,10,5,0);
	////growing(0,31,gray_scale,10,10,5,1);
	////downing(0,31,gray_scale,10,10,5,1);
	////
	////
////growing(0,31,gray_scale,5,15,7,2);	
////downing(0,31,gray_scale,5,15,7,2);
		////
		//////
////bytwo(0,31,gray_scale,5,5,0,2,1);
////a--;
		////if (a==0) a=50;
		//////
		//////
		////////rotatal(0,15,gray_scale,1,0);
		////////rotatal(16,31,gray_scale,1,1);
		////////
		////////pwm_gen(2,resolution,gray_scale,port);
		//////
	//fill_drop(0,31,gray_scale,4,16,1);
	//fill_drop(0,31,gray_scale,4,16,0);
		////////
	////////	random_light(0,31,gray_scale);
	//////
	////////brighness_down(0,31,gray_scale,2,1,100);	
	////////brighness_up(0,31,gray_scale,2,1,100);		
		////////
	////////auto_change(0,31,gray_scale,1,2,(uint8_t)random()/2);
	////////radian_gen(0,31,gray_scale,20,0,1,1);	
	////soft_flash(0,31,4,3,128,0);
	////////
	//light_appear(0,31, gray_scale,5,1,0);
	//light_appear(0,31, gray_scale,5,1,1);
	//light_appear(0,31, gray_scale,5,1,2);
	//light_appear(0,31, gray_scale,5,1,3);
	////////
	////////set_value(0,gray_scale);
	//fill_pendul(0,31,gray_scale,5,4,3);
	//pendul(0,31,gray_scale,5,3,10,1);
	//pendul(0,31,gray_scale,5,3,20,2);
	//pendul(0,31,gray_scale,5,3,30,3);
	//pendul(0,31,gray_scale,5,3,40,7);
	////////
	//pendul_inv(0,31,gray_scale,3,3,10,2);
	//pendul_inv(0,31,gray_scale,3,3,20,4);
	//pendul_inv(0,31,gray_scale,3,3,30,2);
	//pendul_inv(0,31,gray_scale,3,3,40,3);
	//////
	//shooting_star(0,31,gray_scale,3,16,1);
	//shooting_star(0,31,gray_scale,3,16,0);
////  shooting_star(0,31,gray_scale,1,4,0,0);
	
	
    }
}

void pgm_read_block(uint8_t *ram,const uint8_t *pgm,uint8_t size)
{
	for (uint8_t  i= 0; i <size; i++)
	ram[i]=pgm_read_byte(&pgm[i]);
}
