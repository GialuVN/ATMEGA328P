/*
 * matrix16x8.h
 *
 * Created: 11/13/2015 1:40:57 PM
 *  Author: RnD
 */ 


#ifndef MATRIX16X8_H_
#define MATRIX16X8_H_
#include "DMX_standard.h"



void mt_set_all(unsigned char val);
void mt_set_xy(unsigned char x, unsigned char y,unsigned char val);
unsigned char mt_get_xy(unsigned char x, unsigned char y);
void mt_draw_round(unsigned char a, unsigned char b, unsigned char r);
#endif /* MATRIX16X8_H_ */