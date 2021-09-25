/*
 * lpd6803_pro.c
 *
 * Created: 24/09/2013 8:39:58 AM
 *  Author: THIET KE 3
 */ 



#define F_CPU 16000000ul
#include <util/delay.h>
#include <avr/io.h>
#include "lpd6803.h"
#include "lpd6803_pro.h"
#include <math.h>

extern Color_pack RGB[max_led];

void out_to_lpd(Color_pack *rgb, uint16_t nled)
{
	lpd6803_start_farme();
	for (uint16_t i= 0; i < nled; i++)
	lpd6803_rgb(rgb[i].Color.Red,rgb[i].Color.Green,rgb[i].Color.Blue);
	lpd_6803_npulse(nled);
}


void set_base_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,uint8_t R,uint8_t G,uint8_t B)
{
	
		Color_pack tem_color;
		tem_color.Color.Red = R;
		tem_color.Color.Green = G;
		tem_color.Color.Blue = B;
		while (first_point<=last_point)
		{
			rgb[first_point] = tem_color;
			first_point++;
		}
}

Color_pack base_convert(Mycolors _color)
{
	Color_pack _temp;
	switch (_color)
	{
	case black:
	_temp.Color.Red = 0;
	_temp.Color.Green =0;
	_temp.Color.Blue = 0;
	break;
	case red:
	_temp.Color.Red = max_gray;
	_temp.Color.Green = 0;
	_temp.Color.Blue = 0;
	break;
	case green:
	_temp.Color.Red = 0;
	_temp.Color.Green = max_gray;
	_temp.Color.Blue = 0;
	break;
	case blue:
	_temp.Color.Red = 0;
	_temp.Color.Green = 0;
	_temp.Color.Blue = max_gray;
	break;
	case yellow:
	_temp.Color.Red = max_gray;
	_temp.Color.Green =max_gray;
	_temp.Color.Blue = 0;
	break;
	case purple:
	_temp.Color.Red = max_gray;
	_temp.Color.Green =0;
	_temp.Color.Blue = max_gray;
	break;
	case cyan:
	break;
	_temp.Color.Red = 0;
	_temp.Color.Green =max_gray;
	_temp.Color.Blue = max_gray;
	break;
	
	case white:
	_temp.Color.Red = max_gray;
	_temp.Color.Green =max_gray;
	_temp.Color.Blue = max_gray;
	break;
	}
	return _temp;
}





Color_pack pack_convert(uint8_t R,uint8_t G,uint8_t B)
{
	Color_pack tem_color;
	tem_color.Color.Red = R;
	tem_color.Color.Green = G;
	tem_color.Color.Blue = B;
	return tem_color;
}

void rotatal(Color_pack *rgb,uint16_t first_point,uint16_t last_point,uint8_t direct)
{
	Color_pack _buff;
	uint16_t _num = last_point - first_point;
	
	if (direct==0)
	{
		
		_buff=rgb[first_point];
		for (uint16_t i = 0;i<_num;i++)
			{
				rgb[first_point]= rgb[first_point+1];
				first_point++;
			}
				rgb[last_point] = _buff;
	}
	
	else
	{
		_buff=rgb[last_point];
		
		for (uint16_t i = 0;i<_num;i++)
			{
				rgb[last_point]= rgb[last_point-1];
				last_point--;
			}
				rgb[first_point] = _buff;
	}
}



void gen_soft_two_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack cl1,Color_pack cl2,uint8_t speed, uint8_t div,uint16_t loop,uint8_t style)
{
	uint16_t _num = last_point - first_point;
	
	if ((cl1.Color.Blue==cl2.Color.Blue)&&(cl1.Color.Red==cl2.Color.Red)&&(cl1.Color.Green==cl2.Color.Green)) return;
	
	Color_pack cur_color =cl1;
	Color_pack to_color = cl2;
	switch (style)
	{
		case 0:
		for (uint16_t j = 0; j <loop; j++)
		{
			do
			{
				rgb[first_point] = cur_color;
				rotatal(rgb,first_point,last_point,1);
				out_to_lpd(rgb,_num+1);
				for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
			}
			while (color_change(&cur_color,&to_color,div)==0);
			cur_color = cl2;
			to_color =  cl1;
			
			do
			{
				rgb[first_point] = cur_color;
				rotatal(rgb,first_point,last_point,1);
				out_to_lpd(rgb,_num+1);
				for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
			}
			while (color_change(&cur_color,&to_color,div)==0);
			cur_color = cl1;
			to_color =  cl2;
			
			
		}
		break;
		case 1:
		for (uint16_t j = 0; j <loop; j++)
		{
			do
			{
				rgb[last_point] = cur_color;
				rotatal(rgb,first_point,last_point,0);
				out_to_lpd(rgb,_num+1);
				for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
			}
			while (color_change(&cur_color,&to_color,div)==0);
			cur_color = cl2;
			to_color =  cl1;
			
			do
			{
				rgb[last_point] = cur_color;
				rotatal(rgb,first_point,last_point,0);
				out_to_lpd(rgb,_num+1);
				for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
			}
			while (color_change(&cur_color,&to_color,div)==0);
			cur_color = cl1;
			to_color =  cl2;
			
			
		}
		break;
		case 2:
		
		for (uint16_t j = 0; j <loop; j++)
		{
			do
			{
				
				rgb[last_point] = cur_color;
				rgb[first_point] = cur_color;
				rotatal(rgb,first_point,((last_point-first_point)/2)+first_point,0);
				rotatal(rgb,((last_point-first_point)/2)+first_point+1,last_point,1);
				out_to_lpd(rgb,_num+1);
				for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
			}
			while (color_change(&cur_color,&to_color,div)==0);
			cur_color = cl2;
			to_color =  cl1;
			
			do
			{
				rgb[last_point] = cur_color;
				rgb[first_point] = cur_color;
				rotatal(rgb,first_point,((last_point-first_point)/2)+first_point,0);
				rotatal(rgb,((last_point-first_point)/2)+first_point+1,last_point,1);
				out_to_lpd(rgb,_num+1);
				for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
			}
			while (color_change(&cur_color,&to_color,div)==0);
			
			cur_color = cl1;
			to_color =  cl2;
			
		}
		
		break;
		
		default:
		for (uint16_t j = 0; j <loop; j++)
		{
			do
			{
				rgb[((last_point-first_point)/2)+first_point] = cur_color;
				rgb[((last_point-first_point)/2)+first_point+1] = cur_color;
				rotatal(rgb,first_point,((last_point-first_point)/2)+first_point,1);
				rotatal(rgb,((last_point-first_point)/2)+first_point+1,last_point,0);
				out_to_lpd(rgb,_num+1);
				for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
			}
			while (color_change(&cur_color,&to_color,div)==0);
			
			cur_color = cl2;
			to_color =  cl1;
			
			do
			{
				rgb[((last_point-first_point)/2)+first_point] = cur_color;
				rgb[((last_point-first_point)/2)+first_point+1] = cur_color;
				rotatal(rgb,first_point,((last_point-first_point)/2)+first_point,1);
				rotatal(rgb,((last_point-first_point)/2)+first_point+1,last_point,0);
				out_to_lpd(rgb,_num+1);
				for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
			}
			while (color_change(&cur_color,&to_color,div)==0);
			cur_color = cl1;
			to_color =  cl2;
			
		}
		break;
	}
}



void gen_two_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack cl1,Color_pack cl2,uint8_t speed, uint8_t len,uint16_t loop,uint8_t style)
{
		uint16_t _num = last_point - first_point;
		
		if ((cl1.Color.Blue==cl2.Color.Blue)&&(cl1.Color.Red==cl2.Color.Red)&&(cl1.Color.Green==cl2.Color.Green)) return;
		
		switch (style)
		{
			case 0:
			for (uint16_t j = 0; j <loop; j++)
			{
				for (uint8_t k = 0; k < len; k++)
				{
					rgb[first_point] = cl1;
					rotatal(rgb,first_point,last_point,1);
					out_to_lpd(rgb,_num+1);
					for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
				}
				for (uint8_t k = 0; k < len; k++)
				{
					rgb[first_point] = cl2;
					rotatal(rgb,first_point,last_point,1);
					out_to_lpd(rgb,_num+1);
					for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
				}
			}
			break;
			
			case 1:
				for (uint16_t j = 0; j <loop; j++)
				{
					for (uint8_t k = 0; k < len; k++)
					{
						rgb[last_point] = cl1;
						rotatal(rgb,first_point,last_point,0);
						out_to_lpd(rgb,_num+1);
						for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
					}
					for (uint8_t k = 0; k < len; k++)
					{
						rgb[last_point] = cl2;
						rotatal(rgb,first_point,last_point,0);
						out_to_lpd(rgb,_num+1);
						for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
					}
				}
			break;
			case 2:
			
				for (uint16_t j = 0; j <loop; j++)
				{
					for (uint8_t k = 0; k < len; k++)
					{
						rgb[last_point] = cl1;
						rgb[first_point] = cl1;
						rotatal(rgb,first_point,((last_point-first_point)/2)+first_point,0);
						rotatal(rgb,((last_point-first_point)/2)+first_point+1,last_point,1);
						out_to_lpd(rgb,_num+1);
						for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
					}
					for (uint8_t k = 0; k < len; k++)
					{
						rgb[last_point] =cl2;
						rgb[first_point] = cl2;
						rotatal(rgb,first_point,((last_point-first_point)/2)+first_point,0);
						rotatal(rgb,((last_point-first_point)/2)+first_point+1,last_point,1);
						out_to_lpd(rgb,_num+1);
						for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
					}
				}
			
			break;
			
			default:
			for (uint16_t j = 0; j <loop; j++)
			{
				for (uint8_t k = 0; k < len; k++)
				{
					rgb[((last_point-first_point)/2)+first_point] = cl1;
					rgb[((last_point-first_point)/2)+first_point+1] = cl1;
					rotatal(rgb,first_point,((last_point-first_point)/2)+first_point,1);
					rotatal(rgb,((last_point-first_point)/2)+first_point+1,last_point,0);
					out_to_lpd(rgb,_num+1);
					for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
				}
				for (uint8_t k = 0; k < len; k++)
				{
					rgb[((last_point-first_point)/2)+first_point] = cl2;
					rgb[((last_point-first_point)/2)+first_point+1] = cl2;
					rotatal(rgb,first_point,((last_point-first_point)/2)+first_point,1);
					rotatal(rgb,((last_point-first_point)/2)+first_point+1,last_point,0);
					out_to_lpd(rgb,_num+1);
					for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
				}
			}
		
			break;
		}
}



void gen_color_linear(Color_pack *rgb,uint16_t first_point,uint16_t last_point,uint8_t speed, uint8_t div,uint16_t loop,uint8_t style)
{
		uint16_t _num = last_point - first_point;
		Color_pack cur_color =base_convert((random()%7));
		Color_pack to_color = base_convert((random()%7));
		switch (style)
		{
			case 0:
			for (uint16_t j = 0; j <loop; j++)
			{
				do
				{
					rgb[first_point] = cur_color;
					rotatal(rgb,first_point,last_point,1);
					out_to_lpd(rgb,_num+1);
					for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
				}
				while (color_change(&cur_color,&to_color,div)==0);
				cur_color = to_color;
				to_color = base_convert((random()%7));
			}
			break;
			
			case 1:
			for (uint16_t j = 0; j <loop; j++)
			{
				do
				{
					rgb[last_point] = cur_color;
					rotatal(rgb,first_point,last_point,0);
					out_to_lpd(rgb,_num+1);
					for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
				}
				while (color_change(&cur_color,&to_color,div)==0);
				cur_color = to_color;
				to_color = base_convert((random()%7));
			}
			break;
			case 2:
			
			for (uint16_t j = 0; j <loop; j++)
			{
				do
				{
					
					rgb[last_point] = cur_color;
					rgb[first_point] = cur_color;
					rotatal(rgb,first_point,((last_point-first_point)/2)+first_point,0);
					rotatal(rgb,((last_point-first_point)/2)+first_point+1,last_point,1);
					out_to_lpd(rgb,_num+1);
					for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
				}
				while (color_change(&cur_color,&to_color,div)==0);
				cur_color = to_color;
				to_color = base_convert((random()%7));
			}
			
			break;
			
			default:
			for (uint16_t j = 0; j <loop; j++)
			{
				do
				{
					rgb[((last_point-first_point)/2)+first_point] = cur_color;
					rgb[((last_point-first_point)/2)+first_point+1] = cur_color;
					rotatal(rgb,first_point,((last_point-first_point)/2)+first_point,1);
					rotatal(rgb,((last_point-first_point)/2)+first_point+1,last_point,0);
					out_to_lpd(rgb,_num+1);
					for (uint8_t i = 0; i<speed;i++) _delay_ms(1);
				}
				while (color_change(&cur_color,&to_color,div)==0);
				cur_color = to_color;
				to_color = base_convert((random()%7));
			}
			break;
		}
}



uint8_t color_change(Color_pack *color1,Color_pack *color2,uint8_t ratio)
{
	
	if ((color1->Color.Blue==color2->Color.Blue) &&(color1->Color.Green==color2->Color.Green) &&(color1->Color.Red ==color2->Color.Red)) return 1;
	for (uint8_t i =0;i<ratio;i++)
	{
		
		if (color1->Color.Red>color2->Color.Red)  color1->Color.Red-=1;
		else if (color1->Color.Red<color2->Color.Red)  color1->Color.Red+= 1;
		
		if (color1->Color.Green>color2->Color.Green) color1->Color.Green -=1;
		else if (color1->Color.Green<color2->Color.Green) color1->Color.Green  += 1;
		
		if (color1->Color.Blue>color2->Color.Blue) color1->Color.Blue -=1;
		else if (color1->Color.Blue<color2->Color.Blue) color1->Color.Blue  += 1;
		
	}
	return 0;
}



void color_change_sys(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack to_color,uint8_t speed,uint8_t ratio,uint16_t wait)
{
	Color_pack _cur_color=rgb[first_point];
	
	if ((_cur_color.Color.Blue==to_color.Color.Blue)&&(_cur_color.Color.Red==to_color.Color.Red)&&(_cur_color.Color.Green==to_color.Color.Green)) return;
	do 
	{
		for (uint16_t i=0;i<(last_point-first_point)+1;i++) rgb[first_point+i]=_cur_color;
		out_to_lpd(rgb,(last_point-first_point)+1);
		for (uint16_t i = 0;i<speed;i++) _delay_ms(1);
	} while (color_change(&_cur_color,&to_color,ratio)==0);
	for (uint16_t i = 0;i<wait;i++)
	_delay_ms(1);
}

void paint_touch(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack _color,uint8_t style)
{
	uint16_t _num = last_point - first_point;
	Color_pack cur_color;
	Color_pack to_color;
	uint8_t _temp;
	double k;
	if (_color.Color.Red>=_color.Color.Green)
	{
		if (_color.Color.Red>=_color.Color.Blue) _temp = _color.Color.Red;
		else _temp = _color.Color.Blue;
	}
	else
	{
		if (_color.Color.Green>=_color.Color.Blue) _temp = _color.Color.Green;
		else _temp = _color.Color.Blue;
	}
	k = (double)_temp/_num;
	switch (style)
	{
		case 0:
		to_color = pack_convert(0,0,0);
		for (uint16_t i = 0; i <(_num+1); i++)
		{
			cur_color = _color;
			color_change(&cur_color,&to_color,round(k*i));
			rgb[first_point+i].Color.Red |= cur_color.Color.Red;
			rgb[first_point+i].Color.Green |= cur_color.Color.Green;
			rgb[first_point+i].Color.Blue |= cur_color.Color.Blue;
		}
		break;
		case 1:
		to_color = _color ;
		for (uint16_t i = 0; i <(_num+1); i++)
		{
			cur_color =pack_convert(0,0,0);
			color_change(&cur_color,&to_color,round(k*i));
			rgb[first_point+i].Color.Red |= cur_color.Color.Red;
			rgb[first_point+i].Color.Green |= cur_color.Color.Green;
			rgb[first_point+i].Color.Blue |= cur_color.Color.Blue;
		}
		break;
		default:
		break;
	}
}

void color_to_color(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack color1,Color_pack color2,uint8_t style)
{
	Color_pack max_resolut[max_gray+1];
	Color_pack _buff = color1;
	uint16_t _num = (last_point - first_point)+1 ;
	uint16_t _count=0;
	uint16_t _temp;
	double k;
	
	while (1)
	{
		max_resolut[_count]=_buff;
		_count++;
		if (color1.Color.Red>color2.Color.Red) _buff.Color.Red -=1;
		else if (color1.Color.Red<color2.Color.Red) _buff.Color.Red  += 1;
		
		if (color1.Color.Green>color2.Color.Green) _buff.Color.Green -=1;
		else if (color1.Color.Green<color2.Color.Green) _buff.Color.Green  += 1;
		
		if (color1.Color.Blue>color2.Color.Blue) _buff.Color.Blue -=1;
		else if (color1.Color.Blue<color2.Color.Blue) _buff.Color.Blue  += 1;
		if(_buff.Color.Red==color2.Color.Red && _buff.Color.Green==color2.Color.Green &&  _buff.Color.Blue ==color2.Color.Blue) break;
	}
	k=(double)_count/_num;
	for (uint16_t i = 0; i <_num; i++)
	{
		switch (style)
		{
			case 0:
				_temp = round(k*i);
				rgb[first_point]=max_resolut[_temp];
				first_point++;
			break;
			default:
			_temp =round(k*i);
			rgb[first_point].Color.Red= rgb[first_point].Color.Red | max_resolut[_temp].Color.Red;
			rgb[first_point].Color.Green= rgb[first_point].Color.Green | max_resolut[_temp].Color.Green;
			rgb[first_point].Color.Blue= rgb[first_point].Color.Blue | max_resolut[_temp].Color.Blue;
			first_point++;
			break;
		}
	}
}

void soft_paint(Color_pack *rgb,uint16_t first_point,uint16_t last_point,Color_pack color1,Color_pack color2)
{
	color_to_color(rgb,first_point,(last_point-first_point)/2+first_point,color1,color2,0);
	color_to_color(rgb,(last_point-first_point)/2+1+first_point,last_point,color2,color1,0);	
}