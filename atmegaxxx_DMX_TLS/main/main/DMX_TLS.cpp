/*
 * DMX_TLS.cpp
 *
 * Created: 11/3/2015 3:08:15 PM
 *  Author: RnD
 */ 

#include "DMX_TLS.h"
#include "pt2260.h"
#include <avr/wdt.h>



extern  uint8_t _id_cl[max_range] EEMEM;
extern  uint8_t _mode EEMEM;
extern  uint8_t _count EEMEM;
extern  uint8_t _default EEMEM;
extern  uint8_t _speed EEMEM;
extern  uint8_t _wait  EEMEM;

_RGB _LED_DMX[Len];
_RGB _LED_TLS[Len];
_RGB _color_temp;
_DATA_CL _data;

void DMX_TLS_initial(void)
{
	DMX512A_init();
	TLS3001_Initial();
}

void DMX_TLS_Send_DMX(void)
{
	DMX512A_send_break_mab();
	DMX512A_send_byte(0);
	for (unsigned int i = 0; i < Len; i++)
	{
		DMX512A_send_byte(	_LED_DMX[i]._R);
		DMX512A_send_byte(	_LED_DMX[i]._G);
		DMX512A_send_byte(	_LED_DMX[i]._B);
	}
}

void DMX_TLS_Send_TLS(void)
{
	
#if _TLS
_delay_us(100);
TLS3001_pull(false);
_delay_us(100);
TLS3001_Send_Head();
for (unsigned int i = 0; i < Len; i++) TLS3001_Send_RGB_8(_LED_TLS[i]._R,_LED_TLS[i]._G,_LED_TLS[i]._B);
TLS3001_Send_Reset();
_delay_ms(1);
TLS3001_Send_Sys();
for (unsigned int i = 0; i < Len; i++)	_delay_us(1);
#endif
}

_RGB color_convert(uint8_t R,uint8_t G,uint8_t B)
{
	_RGB rgb;
	rgb._R = R;
	rgb._G = G;
	rgb._B = B;
	return rgb;
}

_RGB base_convert(Mycolors color_type)
{
	_RGB rgb;
	switch (color_type)
	{
		case black:
		rgb._R = 0;
		rgb._G = 0;
		rgb._B=0;
		break;
		case red:
		rgb._R = 255;
		rgb._G = 0;
		rgb._B=0;
		break;
		case green:
		rgb._R = 0;
		rgb._G = 255;
		rgb._B=0;
		break;
		case blue:
		rgb._R = 0;
		rgb._G = 0;
		rgb._B=255;
		break;
		case yellow:
		rgb._R = 255;
		rgb._G = 255;
		rgb._B=0;
		break;
		case purple:
		rgb._R = 255;
		rgb._G = 0;
		rgb._B = 255;
		break;
		case cyan:
		rgb._R = 0;
		rgb._G = 255;
		rgb._B=255;
		break;
		case white:
		rgb._R = 255;
		rgb._G = 255;
		rgb._B=255;
		break;
		default:
		rgb._R = 0;
		rgb._G = 0;
		rgb._B=0;
		break;
	}
	return rgb;
}


bool color_change(_RGB *color1,_RGB *color2,uint8_t ratio)
{

	if ((color1->_B==color2->_B) &&(color1->_G==color2->_G) &&(color1->_R ==color2->_R)) return true;
	for (uint8_t i =0;i<ratio;i++)
	{
		if (color1->_R>color2->_R)  color1->_R-=1;
		else if (color1->_R<color2->_R) color1->_R+= 1;
		
		if (color1->_G>color2->_G) color1->_G -=1;
		else if (color1->_G<color2->_G) color1->_G  += 1;
		
		if (color1->_B>color2->_B) color1->_B -=1;
		else if (color1->_B<color2->_B) color1->_B  += 1;
		wdt_reset();
	}
	return false;
}

void color_change_sys(_RGB to_color,uint8_t speed,uint8_t ratio,uint16_t wait)
{
	if ((_color_temp._B==to_color._B)&&(_color_temp._R==to_color._R)&&(_color_temp._G==to_color._G)) return;
	do
	{
		DMX_TLS_set_color_all(_color_temp,true);
		DMX_TLS_set_color_all(_color_temp,false);
		DMX_TLS_Send_DMX();
		delayms(speed);
		DMX_TLS_Send_TLS();	
	} while (color_change(&_color_temp,&to_color,ratio)==false);
		DMX_TLS_Send_TLS();	
		for (uint16_t i = 0;i<wait;i++) delayms(1);
}

void set_default(uint8_t _mode,uint8_t _speed,uint8_t _wait)
{
	_data.wait_cl = _wait;
	_data.speed_cl = _speed;
	_data._mode_ = _mode;
}

void color_change_sys_remote(_RGB to_color)
{
	if ((_color_temp._B==to_color._B)&&(_color_temp._R==to_color._R)&&(_color_temp._G==to_color._G)) return;
	do
	{
		if (_data.speed_cl<=0)
		{
			DMX_TLS_set_color_all(to_color,true);
			DMX_TLS_set_color_all(to_color,false);
		}
		else
		{
			DMX_TLS_set_color_all(_color_temp,true);
			DMX_TLS_set_color_all(_color_temp,false);
		}
		DMX_TLS_Send_DMX();
		
		if (_data.speed_cl>0)
		{
			delayms(_data.speed_cl);
		}
		DMX_TLS_Send_TLS();
	} while (color_change(&_color_temp,&to_color,1)==false);
	DMX_TLS_Send_TLS();
	Remote(_data.wait_cl);
}

void custom_change(void)
{
	unsigned char _point;
	if ((_data.count_cl==0) ||(_data.count_cl>max_range)) 
	{
		_data._mode_ = 0;
		return;
	}
	_point = 0;
	while (1)
	{
		color_change_sys_remote(base_convert((Mycolors)(_data.id_cl[_point])));
		_point++;
		if (_point>=_data.count_cl) _point =0;
		if (_data._mode_ == 0 ) break;
	}
}

bool get_mode(void)
{
	if (_data._mode_==0) return false;
	return true;
}


void get_eeprom(void)
{
	cli();
	eeprom_busy_wait();
	_data._mode_= eeprom_read_byte(&_mode);
	eeprom_busy_wait();
	_data.speed_cl = eeprom_read_byte(&_speed);
	eeprom_busy_wait();
	_data.wait_cl = eeprom_read_byte(&_wait);
	eeprom_busy_wait();
	_data.count_cl = eeprom_read_byte(&_count);
	eeprom_busy_wait();
	eeprom_read_block(&_data.id_cl,&_id_cl,max_range);
	delayms(100);
}
void Remote(unsigned char wait)
{
	PORTD|=1<<PORTD4;
	uint8_t _temp_mode = 0;
	bool _setup = false;
	signed char _loop =0;
	unsigned char _key;
	sei();
	RF_clear_key();
	while (wait)
	{
			delayms(100);
			if (RF_get_key()==1)
			{
				_setup = true;
				break;
				RF_clear_key();
			}
			wait--;
	}
	
	if (_setup)
	{
		setup_disp(base_convert(black));
		delayms(500);
		setup_disp(color_convert(255,0,0));
		_temp_mode = 1;
		delayms(1000);
		RF_clear_key();
		while (1)
		{
			_key = RF_get_key();
			
			if (_key ==1)
			{
				_temp_mode ++;
				switch (_temp_mode)
				{
					case 1:
					setup_disp(color_convert(255,0,0));
					break;
					case 2:
					setup_disp(color_convert(0,255,0));
					break;
					case 3:
					setup_disp(color_convert(0,0,255));
					break;
					case 4:
					setup_disp(color_convert(255,255,255));
					break;
					default:
					setup_disp(color_convert(0,0,0));
					_temp_mode = 0;
					break;
				}
				
			}
			else if (_key==2||_key==4||_key==8)
			{
				break;
				cli();
			}
			_key = 0;
			RF_clear_key();
			
			delayms(1000);
			if (_temp_mode ==0) 
			{
				cli();
				break;
			}
		}
	}
	else cli();
	
	switch (_temp_mode)
	{
		case 1:
				setup_disp(color_convert(_data.speed_cl,0,0));
				delayms(1000);
				RF_clear_key();
				while (1)
				{
					_key = RF_get_key();
					if (_key==8)
					{
						if (_data.speed_cl>0)
						{
							_data.speed_cl--;
							setup_disp(color_convert(_data.speed_cl,0,0));
						}
	
					}
					else if (_key==4)
					{
						if (_data.speed_cl<255)
						{
							_data.speed_cl++;
							setup_disp(color_convert(_data.speed_cl,0,0));
						}

					}
					else if (_key==1)
					{
						setup_disp(base_convert(black));
						cli();
						eeprom_busy_wait();
						eeprom_write_byte(&_speed,_data.speed_cl);
						delayms(500);
					
						break;
						
					}
						_key = 0;
						RF_clear_key();
					delayms(100);
					
				}
				break;
		case 2:
				if (_data.wait_cl>10)	_data.wait_cl/=3;
				setup_disp(color_convert(0,_data.wait_cl,0));
				delayms(1000);
				RF_clear_key();
				while (1)
				{
					_key = RF_get_key();
					
					if (_key==8)
					{
						if (_data.wait_cl>1)
						{
							_data.wait_cl--;
							setup_disp(color_convert(0,_data.wait_cl,0));
						}
					}
					else if (_key==4)
					{
						if (_data.wait_cl<255)
						{
							_data.wait_cl++;
							setup_disp(color_convert(0,_data.wait_cl,0));
						}
					}
					else if (_key==1)
					{
						if (_data.wait_cl>10)
						{
							if ((_data.wait_cl*3)<255) _data.wait_cl*=3;
							else _data.wait_cl = 255;
						}
						
						if (_data.wait_cl<=0) _data.wait_cl=1;
					
						setup_disp(base_convert(black));
						cli();
						eeprom_busy_wait();
						eeprom_write_byte(&_wait,_data.wait_cl);
						delayms(500);
						break;
					}
					_key = 0;
					RF_clear_key();
					delayms(100);
				}
				break;
				case 3:
						setup_disp(color_convert(0,0,0));
						delayms(1000);
						RF_clear_key();
						_data.count_cl = 0;
						_data.point_cl = 0;
						
						while (1)
						{
							_key = RF_get_key();
							
							if (_key==8)
							{
									_loop-=1;
								if (_loop<=-1) _loop =7;
							
									setup_disp(base_convert((Mycolors)_loop));
								
							}
							else if (_key==4)
							{
									_loop++;
									if (_loop>=8) _loop = 0;
									setup_disp(base_convert((Mycolors)_loop));
									
									
							}
							
							else if (_key==2)
							{
								if (_data.count_cl<max_range)
								{
									if (_loop==0)	setup_disp(base_convert(white));	
									else setup_disp(base_convert(black));
									cli();
									delayms(1000);
									setup_disp(base_convert((Mycolors)_loop));
									_data.id_cl[_data.count_cl]=_loop;
									_data.count_cl++;
								}
								
							}
							
							else if (_key==1)
							{
								setup_disp(base_convert(black));
								cli();
								wdt_reset();
								_data._mode_ = 1; //
								eeprom_busy_wait();
								eeprom_write_block(&_data.id_cl,&_id_cl,max_range);
								eeprom_busy_wait();
								eeprom_write_byte(&_mode,_data._mode_);
								eeprom_busy_wait();
								eeprom_write_byte(&_count,_data.count_cl);
								eeprom_busy_wait();
								eeprom_write_byte(&_speed,_data.speed_cl);
								eeprom_busy_wait();
								eeprom_write_byte(&_wait,_data.wait_cl);
								delayms(500);
								break;
							}
							_key = 0;
							RF_clear_key();
							delayms(1000);
						}
				break;
			case 4:
					if (_data._mode_==0) _data._mode_ = 1;
					else _data._mode_ = 0;
						setup_disp(base_convert(black));
						cli();
						eeprom_busy_wait();
						eeprom_write_byte(&_mode,_data._mode_);
						delayms(500);
			break;
			default:
			break;
	}

PORTD &=~(1<<PORTD4);
}

void setup_disp(_RGB _cl)
{
	cli();
	DMX_TLS_set_color_all(_cl,false);
	DMX_TLS_set_color_all(_cl,true);
	DMX_TLS_Send_DMX();
	delayms(5);
#if _TLS
DMX_TLS_Send_TLS();
delayms(5);
DMX_TLS_Send_DMX();
delayms(5);
DMX_TLS_Send_TLS();
#endif
	sei();
	
}


void delayms(unsigned int val)
{
	for (unsigned int i = 0; i < val; i++)
	{
		wdt_reset();
		_delay_ms(1);
	}
}

void DMX_TLS_set_color_all(_RGB _color,bool _select)
{
	if (_select) for (unsigned int i = 0; i < Len; i++) _LED_DMX[i] = _color;
	else for (unsigned int i = 0; i < Len; i++) _LED_TLS[i] = _color;
}