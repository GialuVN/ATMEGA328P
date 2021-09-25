/*
 * matrix16x8.cpp
 *
 * Created: 11/13/2015 1:40:47 PM
 *  Author: RnD
 */ 
#include "matrix16x8.h"

volatile uint8_t channel_buff[16][8];


void mt_set_all(unsigned char val)
{
	for (unsigned char i = 0; i < 16; i++)
	{
		for (unsigned char j = 0;j<8;j++)
		{
			channel_buff[i][j] = val;
		}
	}
}

void mt_set_xy(unsigned char x, unsigned char y,unsigned char val){channel_buff[x][y] = val;}
unsigned char mt_get_xy(unsigned char x, unsigned char y){return channel_buff[x][y];}
	
void mt_draw_round(unsigned char a, unsigned char b, unsigned char r)
{
	int c;
	int res;
	c= a*a + b*b - r*r;
	for (unsigned char i = 0;i<8;i++)
	{
		for (unsigned char j=0;j<16;j++)
		{
			res = (i*i+j*j-(2*a*j)-(2*b*i)+c);
			if (res==0||res==1||res==-1)
			{
				mt_set_xy(j,i,255);
				
			}
		}
	}
}