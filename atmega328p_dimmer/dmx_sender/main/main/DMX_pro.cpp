/*
 * DMX_pro.cpp
 *
 * Created: 10/8/2015 1:07:22 PM
 *  Author: RnD
 */  
#include "DMX_pro.h"
volatile uint8_t rota_buff[MAX_ROTA_CHANNEL];
 extern volatile uint8_t channel_buff[MAX_DMX_CHANNEL];
dmx_control dmxcontrol[MAX_AUTO_CHANNEL];
volatile rotatal_ctr rota_ctr[MAX_ROTA_GROUP];
volatile uint8_t counter;
volatile bool flag;
volatile bool en;
volatile uint8_t rota_en;
volatile uint16_t bot_channel;
volatile uint16_t top_channel;
volatile uint32_t ms_counter;
volatile uint16_t _temp_bot;
volatile uint16_t _temp_top;

volatile uint16_t _temp_rota_bot;
volatile uint16_t _temp_rota_top;
volatile uint8_t _temp_rota_slot;

void dmxcontrol_default(void)
{
	dmx_control temp;
	temp.bot_gray = 0;
	temp.top_gray = RESOLUS;
	temp.count_repeat = 0;
	temp.counter = 0;
	temp.fade_in = 10;
	temp.fade_out = 10;
	temp.hold =100;
	temp.on_delay = 100;
	temp.mode = 0;
	temp.repeat = 0;
	temp.stage = 255;
	for (uint8_t i = 0; i < MAX_AUTO_CHANNEL; i++) dmxcontrol[i]= temp;
	dmxctr_close();
}

void dmxctr_random_vector(uint8_t bot,uint8_t top,SELECT selection,uint16_t from_val,uint16_t to_val)
{
	if (from_val>to_val)
	{
		switch (selection)
		{
			case ondelay:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[i+bot].on_delay=Random_range(from_val,to_val);
			break;
			case fadein:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[i+bot].fade_in=Random_range(from_val,to_val);
			break;
			case hold:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[i+bot].hold=Random_range(from_val,to_val);
			break;
			case fadeout:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[i+bot].fade_out=Random_range(from_val,to_val);
			break;
			case repeat:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[i+bot].repeat=Random_range(from_val,to_val);
			break;
			case gray:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[i+bot].gray=Random_range(from_val,to_val);
			break;
			
			default:
			break;
		}
	}

	else if (from_val<to_val)
	{
		switch (selection)
		{
			case ondelay:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].on_delay=Random_range(from_val,to_val);
			break;
			case fadein:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].fade_in=Random_range(from_val,to_val);
			break;
			case hold:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].hold=Random_range(from_val,to_val);
			break;
			case fadeout:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].fade_out=Random_range(from_val,to_val);
			break;
			case repeat:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].repeat=Random_range(from_val,to_val);
			break;
			case gray:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].gray=Random_range(from_val,to_val);
			break;
			default:
			break;
			
		}
	}
	else
	{
		switch (selection)
		{
			case ondelay:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].on_delay=from_val;
			break;
			case fadein:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].fade_in=from_val;
			break;
			case hold:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].hold=from_val;
			break;
			case fadeout:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].fade_out=from_val;
			break;
			case repeat:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].repeat=from_val;
			break;
			case gray:
			for (uint8_t i = 0; i <(top-bot+1); i++) dmxcontrol[top-i].gray=from_val;
			break;
			default:
			break;
		}
	}
	
}



void dmxctr_config_vector(uint8_t bot,uint8_t top,SELECT selection,uint16_t from_val,uint16_t to_val)
{
	uint8_t n_point = top-bot+1;
	uint16_t n_val = abs(from_val-to_val);
	float ratio =(float)n_val/(n_point-1);
	if (from_val>to_val)
	{
		switch (selection)
		{
			case ondelay:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].on_delay=ratio*i+to_val;
			break;
			case fadein:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].fade_in=ratio*i+to_val;
			break;
			case hold:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].hold=ratio*i+to_val;
			break;
			case fadeout:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].fade_out=ratio*i+to_val;
			break;
			case repeat:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].repeat=ratio*i+to_val;
			break;
			case gray:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].gray=ratio*i+to_val;
			break;
			
			default:
			break;
		}
	}

	else if (from_val<to_val)
	{
		switch (selection)
		{
			case ondelay:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].on_delay=ratio*i+from_val;
			break;
			case fadein:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].fade_in=ratio*i+from_val;
			break;
			case hold:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].hold=ratio*i+from_val;
			break;
			case fadeout:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].fade_out=ratio*i+from_val;
			break;
			case repeat:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].repeat=ratio*i+from_val;
			break;
			case gray:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].gray=ratio*i+from_val;
			break;
			default:
			break;
			
		}
	}
	else
	{
		switch (selection)
		{
			case ondelay:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].on_delay=from_val;
			break;
			case fadein:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].fade_in=from_val;
			break;
			case hold:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].hold=from_val;
			break;
			case fadeout:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].fade_out=from_val;
			break;
			case repeat:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].repeat=from_val;
			break;
			case gray:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[top-i].gray=from_val;
			break;
			default:
			break;
		}
	}
	
}


void dmxctr_config_ref(uint8_t bot,uint8_t top,uint8_t max_gray,uint8_t min_gray)
{
	uint8_t n_point = top-bot+1;
	for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].top_gray=max_gray;
	for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].bot_gray=min_gray;
}


//update : 18/1/2015
void dmxctr_config_value(uint8_t bot,uint8_t top,SELECT selection,uint16_t val)
{
	uint8_t n_point = top-bot+1;
		switch (selection)
		{
			case ondelay:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].on_delay=val;
			break;
			case fadein:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].fade_in=val;
			break;
			case hold:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].hold=val;
			break;
			case fadeout:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].fade_out=val;
			break;
			case repeat:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].repeat=val;
			break;
			case gray:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].gray=val;
			break;
			case mode:
			for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].mode =(dmxcontrol[i+bot].mode &0xf0)|((uint8_t)val & 0x0f);
			break;
			case output:
			switch (val)
			{
				case output_normal:
				for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].mode =(dmxcontrol[i+bot].mode &0x0f)|output_normal<<4;
				break;
				
				case output_reverse:
				for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].mode =(dmxcontrol[i+bot].mode &0x0f)|output_reverse<<4;
				break;
				case output_logic:
				for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].mode =(dmxcontrol[i+bot].mode &0x0f)|output_logic<<4;
				break;
				case output_haft:
				for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].mode =(dmxcontrol[i+bot].mode &0x0f)|output_haft<<4;
				break;
				case output_haft_reverse:
				for (uint8_t i = 0; i <n_point; i++) dmxcontrol[i+bot].mode =(dmxcontrol[i+bot].mode &0x0f)|output_haft_reverse<<4;
				break;
				default:
				break;
			}
			break;
			case enable:
			if (val!=0) val = 0;
			else val = 255;
			
			for (uint8_t i = 0; i <n_point; i++)
			{
				dmxcontrol[i+bot].count_repeat = 0;
				 dmxcontrol[i+bot].stage=val;
			}
			break;
			default:
			break;
		}
}


void dmxctr_open(void) {en = true;}
void dmxctr_close(void) {en = false;}


void waitting_complete_n(uint8_t bot,uint8_t top)
{
	while(check_equal(bot,top,255)==0){};
}

void waitting_return_n(uint8_t bot,uint8_t top)
{
	while(check_equal(bot,top,0)==0){};
}

void waitting_complete(void)
{
	while(check_equal(bot_channel,top_channel,255)==0){};
}

void waitting_return(void)
{
	while(check_equal(bot_channel,top_channel,0)==0){};
}

uint8_t check_equal(uint8_t bot,uint8_t top,uint8_t val)
{
	for (uint8_t i = 0; i < (top-bot+1); i++)
	{
	 if (dmxcontrol[i+bot].stage != val) return 0;
	 else continue;
	}
	return 1;
}

void dmxctr_using(uint16_t bot,uint16_t top)
{
	bot_channel = bot;
	top_channel = top;
}

void dmxctr_block_Enable(uint16_t bot,uint16_t top)
{
	uint8_t _max = 0;
	uint8_t _min = RESOLUS;
		for (uint16_t i = 0;i<(top-bot+1);i++)
		{
			if (dmxcontrol[i+bot].gray<_min) _min=dmxcontrol[i+bot].gray;
			if (dmxcontrol[i+bot].gray>_max) _max = dmxcontrol[i+bot].gray;
		}
		if (_min!=_max) dmxctr_config_ref(bot,top,_max,_min);
	dmxctr_config_value(bot,top,enable,1);
}

void dmxctr_block_Disable(uint16_t bot,uint16_t top)
{
	dmxctr_config_value(bot,top,enable,0);
}

void dmxctr_soft_change(uint16_t bot,uint16_t top,uint8_t speed)
{
	uint16_t _counting;
	if (top>=MAX_AUTO_CHANNEL) return;
	while(1)
	{
		_counting = top-bot+1;
		for (uint16_t i = 0 ;i<(top-bot+1);i++)
		{
			if (channel_buff[i+bot]< (uint8_t)(dmxcontrol[i+bot].gray)) channel_buff[i+bot]++;
			else if (channel_buff[i+bot]>(uint8_t)(dmxcontrol[i+bot].gray)) channel_buff[i+bot]--;
			else 
			{
				_counting--;
				if (_counting==0) return;
				
			}
			delay_ms(speed);
		}
	}
}

/************************************************************************/
/*                          
							SIMPLY STRUCTION                             */
/************************************************************************/

void Block_Set(uint16_t bot,uint16_t top)
{
	if ((bot>top) || (top>=MAX_DMX_CHANNEL))
	{
		_temp_bot = 0;
		_temp_top = 0;
	}
	else
	{
		_temp_bot = bot;
		_temp_top = top;
	}
	dmxctr_block_Disable(_temp_bot,_temp_top);
	
}
void Block_Diasble(void) {dmxctr_block_Disable(_temp_bot,_temp_top);}
void Block_gray_range(uint8_t _min,uint8_t _max){dmxctr_config_ref(_temp_bot,_temp_top,_max,_min);}
void Block_gray(uint16_t value_1,uint16_t value_2){dmxctr_config_vector(_temp_bot,_temp_top,gray,value_1,value_2);}



void Block_gray_haft(uint8_t l1,uint8_t l2,uint8_t r1,uint8_t r2)
{
	dmxctr_config_vector(_temp_bot,_temp_bot+(_temp_top-_temp_bot)/2,gray,l1,l2);
	dmxctr_config_vector(_temp_bot+((_temp_top-_temp_bot)/2)+1,_temp_top,gray,r1,r2);
}

void Block_ondelay(uint16_t value_1,uint16_t value_2){dmxctr_config_vector(_temp_bot,_temp_top,ondelay,value_1,value_2);}
	
void Block_ondelay_haft(uint16_t l1,uint16_t l2,uint16_t r1,uint16_t r2)
{
	dmxctr_config_vector(_temp_bot,_temp_bot+(_temp_top-_temp_bot)/2,ondelay,l1,l2);
	dmxctr_config_vector(_temp_bot+((_temp_top-_temp_bot)/2)+1,_temp_top,ondelay,r1,r2);
}
void Block_hold(uint16_t value_1,uint16_t value_2){dmxctr_config_vector(_temp_bot,_temp_top,hold,value_1,value_2);}
	
	void Block_hold_haft(uint16_t l1,uint16_t l2,uint16_t r1,uint16_t r2)
	{
		dmxctr_config_vector(_temp_bot,_temp_bot+(_temp_top-_temp_bot)/2,hold,l1,l2);
		dmxctr_config_vector(_temp_bot+((_temp_top-_temp_bot)/2)+1,_temp_top,hold,r1,r2);
	}
void Block_fadein(uint16_t value_1,uint16_t value_2){dmxctr_config_vector(_temp_bot,_temp_top,fadein,value_1,value_2);}
	
	void Block_fadein_haft(uint16_t l1,uint16_t l2,uint16_t r1,uint16_t r2)
	{
		dmxctr_config_vector(_temp_bot,_temp_bot+(_temp_top-_temp_bot)/2,fadein,l1,l2);
		dmxctr_config_vector(_temp_bot+((_temp_top-_temp_bot)/2)+1,_temp_top,fadein,r1,r2);
	}
	
void Block_fadeout(uint16_t value_1,uint16_t value_2){dmxctr_config_vector(_temp_bot,_temp_top,fadeout,value_1,value_2);}
	
	void Block_fadeout_haft(uint16_t l1,uint16_t l2,uint16_t r1,uint16_t r2)
	{
		dmxctr_config_vector(_temp_bot,_temp_bot+(_temp_top-_temp_bot)/2,fadeout,l1,l2);
		dmxctr_config_vector(_temp_bot+((_temp_top-_temp_bot)/2)+1,_temp_top,fadeout,r1,r2);
	}
	
void Block_repeat(uint16_t value_1,uint16_t value_2){dmxctr_config_vector(_temp_bot,_temp_top,repeat,value_1,value_2);}

void Block_repeat_haft(uint16_t l1,uint16_t l2,uint16_t r1,uint16_t r2)
{
	dmxctr_config_vector(_temp_bot,_temp_bot+(_temp_top-_temp_bot)/2,repeat,l1,l2);
	dmxctr_config_vector(_temp_bot+((_temp_top-_temp_bot)/2)+1,_temp_top,repeat,r1,r2);
}

void Block_repeat_mode(MODE _mode){dmxctr_config_value(_temp_bot,_temp_top,mode,_mode);}
void Block_output(OUTPUT _output){dmxctr_config_value(_temp_bot,_temp_top,output,_output);}
void Block_Run(void){dmxctr_block_Enable(_temp_bot,_temp_top);}
void Block_Run_f(uint16_t bot,uint16_t top)
{
	dmxctr_block_Enable(bot,top);	
}

void Block_wait(void){waitting_complete_n(_temp_bot,_temp_top);}
	
void Block_soft_fade(uint8_t _speed){dmxctr_soft_change(_temp_bot,_temp_top,_speed);}

void Block_init(uint16_t bot,uint16_t top,uint8_t _min_gray,uint8_t _max_gray)
{
	Block_Set(bot,top);
	Block_gray_range(_min_gray,_max_gray);
}

void Block_delay(uint16_t ondelay1,uint16_t ondelay2,uint16_t hold1,uint16_t hold2)
{
	Block_ondelay(ondelay1,ondelay2);
	Block_hold(hold1,hold2);
}


void Block_fade(uint8_t fadein1,uint8_t fadein2,uint8_t fadeout1,uint8_t fadeout2)
{
	Block_fadein(fadein1,fadein2);
	Block_fadeout(fadeout1,fadeout2);
}

void Block_loop(uint16_t value_1,uint16_t value_2,MODE _mode)
{
	Block_repeat( value_1,value_2);
	Block_repeat_mode(_mode);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//update : 18/1/2015

 void gray_adj(uint8_t bot,uint8_t top)
{
	uint8_t _temp;
	if (top>=MAX_AUTO_CHANNEL) return;
	
	for (uint8_t i = 0; i <(top-bot)+1; i++)
	{
		switch (dmxcontrol[i].mode>>4)
		{
			case output_normal:
			channel_buff[bot+i]=dmxcontrol[i].gray;
			break;
			case output_reverse:
			channel_buff[bot+i]=RESOLUS-dmxcontrol[i].gray;
			break;
			case output_logic:
			if (dmxcontrol[i].gray>=(RESOLUS/2)) channel_buff[bot+i]=dmxcontrol[i].top_gray;
			else channel_buff[bot+i]=dmxcontrol[i].bot_gray;
			break;
			case output_haft:
			_temp = dmxcontrol[i].gray;
			if (_temp<=(RESOLUS/2)-1)channel_buff[bot+i]=(((RESOLUS/2)-1)-_temp)*2+1;
			else channel_buff[bot+i]=(_temp-(RESOLUS/2))*2+1;
			break;
			case output_haft_reverse:
			_temp =dmxcontrol[i].gray;
			if (_temp<=(RESOLUS/2)-1)channel_buff[bot+i]=RESOLUS-(((RESOLUS/2)-1-_temp)*2+1);
			else channel_buff[bot+i]=RESOLUS-((_temp-(RESOLUS/2))*2+1);
			break;
			default:
			break;
		}
	}
	if (DMX_Is_Ready()) DMX_start_transmit(0);
}

void delay_ms(uint32_t val)
{
	
	ms_counter = val;
	while(ms_counter!=0){};
}

void set_ms_counter(uint32_t val)
{
	ms_counter = val;
}

uint8_t check_ms_counter(void)
{
	if (ms_counter!=0) return 0;
	return 1;
}

void timer0_init(void)
{
	TCCR0B |= (5 << CS00);
	TIMSK0 |= (1 << TOIE0);
	TIFR0 &=~(1<<TOV0);
	TCNT0  = 0;
}



ISR(TIMER0_OVF_vect)
{
	wdt_reset();
	TCNT0 = 240;
	if(ms_counter!=0) ms_counter--;
	if (en)
	{
		for (uint8_t i =0;i<top_channel-bot_channel+1;i++)
		{
			switch(dmxcontrol[i].stage)
			{
				case 0:
				dmxcontrol[i].counter = dmxcontrol[i].on_delay;
				dmxcontrol[i].stage = 1;
				break;
				case 1:
				if (dmxcontrol[i].counter==0)
				{
					dmxcontrol[i].counter = dmxcontrol[i].fade_in;
					dmxcontrol[i].stage = 2;
				}
				else dmxcontrol[i].counter--;
				break;
				case 2:
				
				if (dmxcontrol[i].counter==0)
				{
					if (dmxcontrol[i].gray >=dmxcontrol[i].top_gray)
					{
						dmxcontrol[i].counter = dmxcontrol[i].hold;
						dmxcontrol[i].stage = 3;
						break;
					}
					else dmxcontrol[i].gray++;
					dmxcontrol[i].counter = dmxcontrol[i].fade_in;
				}
				
				else dmxcontrol[i].counter--;
				break;
				case 3:
				if (dmxcontrol[i].counter==0)
				{
					dmxcontrol[i].counter = dmxcontrol[i].fade_out;
					dmxcontrol[i].stage = 4;
				}
				else dmxcontrol[i].counter--;
				break;
				case 4:
				if (dmxcontrol[i].counter==0)
				{
					if (dmxcontrol[i].gray <=dmxcontrol[i].bot_gray) dmxcontrol[i].stage = 5;
					else dmxcontrol[i].gray--;
					dmxcontrol[i].counter = dmxcontrol[i].fade_out;
				}
				else dmxcontrol[i].counter--;
				break;
				case 5:
				switch (dmxcontrol[i].mode&0x0f)
				{
					case 0: //repeat to minus
					dmxcontrol[i].stage = 0;
					break;
					
					case 1: //repeat n time and off
					
					if (dmxcontrol[i].count_repeat>=dmxcontrol[i].repeat)
					{
						if (dmxcontrol[i].counter==0)
						{
							dmxcontrol[i].stage = 5;
							if (dmxcontrol[i].gray>dmxcontrol[i].bot_gray) dmxcontrol[i].gray--;
							else
							{
								dmxcontrol[i].stage = 255;
								dmxcontrol[i].count_repeat = 0;
							}
							dmxcontrol[i].counter = dmxcontrol[i].fade_out;
						}
						else dmxcontrol[i].counter--;
					}
					else
					{
						dmxcontrol[i].stage =0;
						dmxcontrol[i].count_repeat++;
					}
					
					break;
					case 2://repeat n time and on
					if (dmxcontrol[i].count_repeat>=dmxcontrol[i].repeat)
					{
						dmxcontrol[i].stage = 5;
						
						if (dmxcontrol[i].counter==0)
						{
							if (dmxcontrol[i].gray<dmxcontrol[i].top_gray) dmxcontrol[i].gray++;
							else
							{
								dmxcontrol[i].stage = 255;
								dmxcontrol[i].count_repeat = 0;
							}
							dmxcontrol[i].counter = dmxcontrol[i].fade_out;
						}
						else dmxcontrol[i].counter--;
					}
					else
					{
						dmxcontrol[i].stage = 0;
						dmxcontrol[i].count_repeat++;
					}
					break;
					default:// one circle
					dmxcontrol[i].stage = 255;
					dmxcontrol[i].count_repeat = 0;
					break;
				}
				break;
				default:
				break;
			}
		}
		 gray_adj(bot_channel,top_channel);
	}
	 if (rota_en) rota_manager();
}

void rota_init(uint8_t _rota_slot,uint16_t bot,uint16_t top)
{
	if (_rota_slot>=MAX_ROTA_GROUP) return;
	if ((bot>top) || (top>=MAX_DMX_CHANNEL))
	{
		_temp_rota_bot = 0;
		_temp_rota_top = 0;
	}
	else
	{
		_temp_rota_bot = bot;
		_temp_rota_top = top;
	}
	
	_temp_rota_slot = _rota_slot;
	
	rota_group_set(_temp_rota_slot,_temp_rota_bot,_temp_rota_top,1,0,_DISABLE);
}

void rota_pattern_fill(uint8_t _n,NAVI _dir,uint8_t p0,uint8_t p1,uint8_t p2,uint8_t p3,uint8_t p4,uint8_t p5,uint8_t p6)
{
	uint8_t _temp_buff[7];
	_temp_buff[0] = p0;
	_temp_buff[1] = p1;
	_temp_buff[2] = p2;
	_temp_buff[3] = p3;
	_temp_buff[4] = p4;
	_temp_buff[5] = p5;
	_temp_buff[6] = p6;
	pattern_fill(_temp_rota_bot,_temp_rota_top,_temp_buff,_n,_dir);
}


void rota_soft_fill_all(uint8_t val_begin,uint8_t val_finish)
{
	fill_soft(_temp_rota_bot,_temp_rota_top,val_begin,val_finish);
}



void rota_run(uint8_t _speed,NAVI _dir)
{
	rota_group_set(_temp_rota_slot,_temp_rota_bot,_temp_rota_top,_speed,_dir,_ENABLE);
}

void rota_this_stop(void)
{
	rota_group_set(_temp_rota_slot,_temp_rota_bot,_temp_rota_top,1,left,_DISABLE);
	
}



void rota_stop(uint8_t _slot)
{
	rota_group_set(_slot,rota_ctr[_slot].G_bot,rota_ctr[_slot].G_top,1,left,_DISABLE);
}

void rota_manager(void)
{
	for (uint8_t i = 0; i < MAX_ROTA_GROUP; i++)
	{
			if (rota_ctr[i].G_enable)
			{
				if (rota_ctr[i].G_counter!=0) rota_ctr[i].G_counter--;
				else
				{
					rota(rota_ctr[i].G_bot,rota_ctr[i].G_top,rota_ctr[i].G_dir);
					rota_ctr[i].G_counter= rota_ctr[i].G_speed;
				}
			for (uint8_t j = 0;j<rota_ctr[i].G_top-rota_ctr[i].G_bot+1;j++) channel_buff[rota_ctr[i].G_bot+j]=rota_buff[rota_ctr[i].G_bot+j];
			}
	}
}

void rota_enable(void){rota_en = true;}
void rota_disable(void){rota_en = false;}

void rota_group_default(void)
{
	rota_disable();
	for (uint8_t i = 0; i < MAX_ROTA_GROUP; i++) rota_group_set(i,0,0,0,0,0);	
}

void rota_group_set(uint8_t group_number,uint8_t g_bot,uint8_t g_top,uint8_t speed,uint8_t dir,uint8_t _enable)
{
	if(g_top>=MAX_ROTA_CHANNEL) return;
	rota_ctr[group_number].G_bot = g_bot;
	rota_ctr[group_number].G_top = g_top;
	rota_ctr[group_number].G_dir = dir;
	rota_ctr[group_number].G_enable = _enable;
	rota_ctr[group_number].G_speed = speed;
}

void pattern_fill(uint8_t bot,uint8_t top,uint8_t *_pattern,uint8_t _pattern_size,uint8_t direct)
{
	uint16_t _pointer = 0;
	if(top>=MAX_ROTA_CHANNEL) return;
	while (1)
	{
		for (uint16_t i = 0;i<_pattern_size;i++)
		{
			if (_pointer>=(uint16_t)(top-bot+1)) return;
			if (direct) rota_buff[bot+_pointer] =_pattern[i];
			else rota_buff[bot+_pointer] =_pattern[(_pattern_size-1)-i];
			_pointer++;
		}
	}
}

void fill_soft(uint16_t bot,uint16_t top,uint8_t val_begin,uint8_t val_finish)
{
	uint16_t chanal_range = top-bot;
	uint8_t gray_range = abs(val_finish-val_begin);
	double ratio = gray_range/chanal_range;
	if (val_finish>=val_begin)
	{
		 for(uint16_t i = 0;i<top-bot+1;i++)
		 {
			 if ((i*ratio+val_begin)>255) rota_buff[bot+i] = 255;
			 else rota_buff[bot+i] = i*ratio+val_begin;
		 }
	}
	else
	{
		 for(uint16_t i = 0;i<top-bot+1;i++)
		 {
			if ((i*ratio+val_finish)>255) rota_buff[top-i] = 255;
			 else rota_buff[top-i] = i*ratio+val_finish;
		 }
	}
	
}


void rota(uint16_t bot,uint16_t top,uint8_t dir)
{
	uint8_t _buff;
	
	if (dir)
	{
		_buff=rota_buff[bot];
		for (uint16_t i = 0;i<(top-bot);i++)
		{
			rota_buff[i+bot]=rota_buff[bot+i+1];
		}
		
		rota_buff[top] = _buff;
	}
	
	else
	{
		_buff=rota_buff[top];
		for (uint16_t i = 0;i<(top-bot);i++)
		{
			rota_buff[top-i]=rota_buff[top-1-i];
		}
		rota_buff[bot] = _buff;
	}
}

void soft_change(uint16_t bot,uint16_t top,uint8_t speed,uint8_t from_val,uint8_t to_val)
{
	if (from_val==to_val) return;
	if (from_val>to_val)
	{
		while (from_val>to_val)
		{
			
			set_val(bot,top,from_val);
			sleep(speed);
			from_val--;
		}
		
	}
	
	else
	{
		while (from_val<to_val)
		{
			set_val(bot,top,from_val);
			sleep(speed);
			from_val++;
		}
	}
}


void sleep(uint16_t val)
{
	while (val--)
	{
		wdt_reset();
		_delay_ms(1);
	}
}


void set_val(uint16_t bot,uint16_t top,uint8_t val)
{
	for (uint16_t i = 0; i <(top-bot+1); i++) rota_buff[bot+i] = val;
}



uint16_t Random_range(uint16_t _from,uint16_t _to)
{
	if (_from>_to) return ((rand()%(_from-_to+1))+_to);
	return ((rand()%(_to-_from+1))+_from);
}