/*
 * effect_classic.cpp
 *
 * Created: 10/8/2015 10:48:23 AM
 *  Author: RnD
 */ 
/*
 * pwm.c
 *
 * Created: 23/02/2013 1:29:10 PM
 *  Author: THIET KE 3
 */ 

#include "effect_classic.h"
#include "DMX_sender_config.h"
#include "triac_driver.h"
#include "DMX_2015.h"

extern volatile uint8_t buffer[MAX_DMX_CHANNEL];
volatile bool _flag_effect;


void effect_enable(void) { _flag_effect = true;}

						
//exit command
/************************************************************************/
/* 
[0xCC][  CMD=254  ][1 bytes VER][ 2 bytes  ID ][10 bytes option][ 1 bytes CRC ]

 1byte    1byte		1bytes			2 bytes			10bytes			1bytes
                                                                     */
/************************************************************************/


/*
28/02/2013
pwm_gen(rate,resolut,*gray,num_port) [ham phat xung pwm xuat ra ic dem 74hc595]
rate(1-255): toc do dich chuyen cua "hinh anh"
resolut(1-255):do phan giai cua  "hinh anh"
*gray: mang chua du lieu do choi
num_port: so luong port su dung (1 port = 8 pin)
pwm_gen(1,resolut,gray,port);
*/

void pwm_gen(uint8_t rate,volatile uint8_t *gray)
{
	uint8_t _res;
	uint16_t _tem;
	 uint8_t _DMX_buff[DMX_LEN];
	 wdt_reset();
	if (_flag_effect)
	{
		_res = DMX_get_data(_DMX_buff,DMX_LEN);
		 if(_res==2)
		{
			_tem = 0;
			if (DMX_Frame_CheckSum(_DMX_buff,DMX_LEN)==true)
			{
				if ((_DMX_buff[0]==HEAD) && (_DMX_buff[2]==VER))
				{
						 _tem = (uint16_t)_DMX_buff[3]<<8;
						 _tem |= (uint16_t)_DMX_buff[4];
						if ( _tem==ID ||  _tem==ID_boardcast)
						{
							for (uint8_t  i=0;i<DMX_LEN;i++) buffer[i] = 0;
							dimmer_updata_direct(buffer);
							if (_DMX_buff[1]==254) _flag_effect=false;
						}
				}
			}
		}
	}
if (_flag_effect==false) return;
else
{
		dimmer_updata_direct(buffer);

		for (unsigned char i = 0; i < rate; i++)
		{
			wdt_reset();
			_delay_ms(5);
		}
}

}

/*
28/02/2013
rotatal(bot,top,*gray,step,direct)[xoay trai, phai khung du lieu do choi]
bot: vi tri bat dau xoay
top: vi tri cuoi
*gray: vi tri khung du lieu
step: so buoc moi lan xoay
direct: huong xoay (0:trai; 1: phai)
rotatal(0,15,gray,1,0);
rotatal(16,31,gray,1,1);
*/


void rotatal(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t step,uint8_t direct)

{
	volatile uint8_t *point1;
	volatile uint8_t *point2;
	uint8_t temp;
	uint8_t length;
	length = top - bot;
	
	while (step>0)
	{
	if (direct <=0)
	{
		point1 =bot+gray; 
		point2 = point1+1;
		temp = *point1;
		
		for (uint8_t i = 0;i<length;i++)
		{
			
			*point1=*point2;
			
			point1++;
			point2++;
		}
		
		*point1=temp;
	}
	else
	{
		point1 =top+gray;
		point2 = point1-1;
		temp = *point1;
		
		for (uint8_t i = 0;i<length;i++)
		{
			
			*point1=*point2;
			
			point1--;
			point2--;
		}
		
		*point1=temp;	
	}
	
	step--;
	}
}

/*
28/02/2013
set_value(uint8_t bot,uint8_t top,value,*gray) [dat tat ca du lieu bang 1 gia tri]
value: gia tri muon dat
*gray:du lieu
set_value(1,10,255,gray) 
*/
void set_value(uint8_t bot,uint8_t top,uint8_t value,volatile uint8_t *gray) 
{
	for (uint8_t i =bot;i<=top;i++) gray[i] = value;
}
/*
25/8/2013
void set_value_slowly(uint8_t bot,uint8_t top,uint8_t value,volatile uint8_t *gray,uint8_t speed,uint8_t direct) 
value: gia tri muon dat
*gray:du lieu
set_value_slowly(1,10,255,gray,5,1) 
*/
void set_value_slowly(uint8_t bot,uint8_t top,uint8_t value,volatile uint8_t *gray,uint8_t speed,uint8_t direct) 
{
	
	if (direct==0)
	{
		for (int i =bot;i<=top;i++)
		{
			gray[i] = value;
			pwm_gen(speed,gray);
		}
	}
	
	else
	{
		
		for (int i =top;i>=bot;i--)
		{
			gray[i] = value;
			pwm_gen(speed,gray);
		}
	}
	
}
/*
28/02/2013
radian_gen(bot,top,*gray,resolut,direct,adj,adj2) [ham phat du lieu tang/ giam dan]
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
resolut: do phan giai
direct: huong (0: sang trai, 1: sang phai)
adj: dieu chinh do muot
adj2:dieu chinh do sang
radian_gen(16,31,gray,255,1,0,0);
*/

void radian_gen(uint8_t bot,uint8_t top,volatile uint8_t *gray, uint8_t resolut,uint8_t direct, uint8_t adj,uint8_t adj2)
{
volatile uint8_t *point1;
	uint8_t lenght;
	uint8_t temp;
	lenght = top - bot;
	temp = resolut/lenght;
	uint16_t check;
	
	if(direct<=0)
	{
		point1 = gray+top;
		
		for (uint8_t i =0;i<=lenght;i++)
		{
			*point1 = i;
			*point1 = *point1*temp;
			point1--;
		}
	}
	else
	{
		
		point1 = gray+bot;
		for (uint8_t i =0;i<=lenght;i++)
		{
			*point1 = i;
			*point1 = *point1*temp;
			point1++;
		}
		
	}
	
	
	if (adj2>0)
	{
		
		point1 = gray+bot;
		for (uint8_t i =0;i<=lenght;i++)
		{
			*point1 =*point1/adj2;
			
			if(*point1>0)
			{
				*point1-=1;
			}
			
			point1++;
		}
		
	}
	
	if (adj>0)
	{
		check = 0;
		point1 = gray+bot;
		for (uint8_t i =0;i<=lenght;i++)
		{
			check = *point1;
			check+=adj;
			if(check<=resolut)
			{
				*point1 =*point1 + adj;
			}
			
			point1++;
		}
	}
}
/*
28/02/2013
void brighness_down(bot,top,*gray,speed,step,level)[giam do sang]
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
step: buoc nhay
speed: toc do
level: muc do giam
brighness_down(0,31,gray,2,1,100);	
*/
void brighness_down(uint8_t bot, uint8_t top, volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t level)
{
	volatile uint8_t *point;
	uint8_t lenght;
	lenght = top - bot;
	
	for(uint8_t k = 0;k<level;k++)
	{
	point = gray + bot;
	for (uint8_t i=0;i<=lenght;i++)
	{
		for(uint8_t j=0;j<step;j++)
		if (*point>0) *point = *point-1;
		point++;
	}
	pwm_gen(speed,gray);
	
	}

}
/*
28/02/2013
void brighness_up(bot,top,*gray,step,speed,level)[tang do sang]
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed: toc do
level: muc do tang
brighness_up(0,31,gray,2,1,100);		

*/
void brighness_up(uint8_t bot, uint8_t top, volatile uint8_t *gray,uint8_t step,uint8_t speed,uint8_t level)
{
volatile uint8_t *point;
	uint8_t lenght;
	lenght = top - bot;
	for(uint8_t k = 0;k<level;k++)
	{
		point = gray + bot;
		for (uint8_t i=0;i<=lenght;i++)
		{
			for(uint8_t j=0;j<step;j++)
			if (*point<RESOLUS) *point = *point+1;
			point++;
		}
		pwm_gen(speed,gray);
	}
}
/*
1/03/2013
void light_change(bot, top, *gray,step,style)[thay doi do sang]
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
step: buoc chuyen doi
style: kieu chuyen doi (0: tat dan, 1 sang dan)
	light_change(0,31,gray,1,1);

*/		
void light_change(uint8_t bot, uint8_t top, volatile uint8_t *gray,uint8_t step,uint8_t style)
{
	volatile uint8_t *point;
	uint8_t lenght;
	lenght = top - bot;
	point = gray + bot;
	if(style==0)
	{
		
	for (uint8_t i=0;i<=lenght;i++)
	{
		for (uint8_t j = 1; j<=step;j++)
		if (*point>0)	*point = *point-1;
		point++;
	}
	
	}
	else
	{
		for (uint8_t i=0;i<=lenght;i++)
		{
			
			for (uint8_t j = 1; j<=step;j++)
			if (*point<255) *point = *point+1;
			point++;
		}
		
	}
	
}	

/*
1/03/2013
uint8_t  check(bot,top,*gray,val)[kiem tra tat ca du lieu
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
val: gia tri kiem tra(neu = tra ve 1)
*/
uint8_t  check_equ(uint8_t bot,uint8_t top, volatile uint8_t *gray,uint8_t val)

{
	volatile uint8_t *point;
	uint8_t lenght;
	uint8_t signal;
	lenght = top - bot;
	point = gray + bot;
	for (uint8_t i = 0;i<=lenght;i++)
	{
		
		if (*point != val)
		{
			signal =0;
			break;
		}
		
		signal = 1;
		point++;
	}		
	return signal;
}
/*
1/03/2013
void random_light(bot,top,*gray)[phat du lieu ngau nhien tu 0 - 255]
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
*/

void random_light(uint8_t bot,uint8_t top,volatile uint8_t *gray)
{
	uint8_t lenght;
	lenght = top - bot;
	gray = gray + bot;
	for (uint8_t i = 0;i<=lenght;i++)
	gray[i] = random();
}
/*
2/03/2013
void light_appear(bot,top,*gray,speed,style)[4 kieu kieu xuat hien]
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
step: buoc chuyen
style: kieu xuat hien (0: p>t;1: t<p; 2: toa ra; 3: lan vo)
light_appear(0,31, gray,2,10,0);
light_appear(0,31, gray,2,10,1);
light_appear(0,31, gray,2,10,2);
light_appear(0,31, gray,2,10,3);
*/
void light_appear(uint8_t bot,uint8_t top, volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t style)
{
	volatile uint8_t *point;
	uint8_t lenght;
	uint8_t k;
	uint8_t mid;
	uint8_t top1;
	uint8_t	bot1;
	volatile uint8_t *point1;
	lenght = top - bot;
	mid = (lenght+1)/2;
	top1 = bot+mid;
	bot1 =top1+1;
	point1 = gray+bot1;
	set_value(bot,top,0,gray);	
	if (style==0)
	{
		k = 0;
		point = gray + bot;
		while(check_equ(bot,top,gray,RESOLUS)==0)
		{
			*point = k;
			rotatal(bot,top,gray,1,0);
			pwm_gen(speed,gray);
			for (uint8_t i = 0;i<step;i++)
			{
				if (k ==RESOLUS)	k-=1;
				k++;
			}
		}
	}
	else if (style==1)
	{
		
		point = gray+top;
		k = 0;
		while(check_equ(bot,top,gray,RESOLUS)==0)
		{
			*point = k;
			rotatal(bot,top,gray,1,1);
			pwm_gen(speed,gray);
			
				for (uint8_t i = 0;i<step;i++)
				{
					if (k ==RESOLUS)	k-=1;
					k++;
				}
		}
	}
	else if(style == 2)
	{
		point = gray+bot1;
		point1 = gray+top1;
		k = 0;
		while(check_equ(bot,top,gray,RESOLUS)==0)
		{
			*point = k;
			*point1 = k;
			rotatal(bot,top1,gray,1,1);
			rotatal(bot1,top,gray,1,0);
			pwm_gen(speed,gray);
			for (uint8_t i = 0;i<step;i++)
			{
				if (k ==RESOLUS)	k-=1;
				k++;
			}
		}
	}		
		
	else
	{
		point = gray+bot;
		point1 = gray+top;
		k = 0;
		while(check_equ(bot,top,gray,RESOLUS)==0)
		{
			*point = k;
			*point1 = k;
			rotatal(bot,top1,gray,1,0);
			rotatal(bot1,top,gray,1,1);
			pwm_gen(speed,gray);
			
			for (uint8_t i = 0;i<step;i++)
			{
				if (k ==RESOLUS)	k-=1;
				k++;
			}
		}			
		
	}
}

/*
2/03/2013
pendul(bot,top,*gray,speed,repeat,back_light,style)[hieu ung con lac]
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
repeat: so lan lap lai
back_light: do sang nen
style: kieu chay (0: bat dau tu bot;1:bat dau tu top; 2: bat dau tu bot ko lap lai; 3:bat dau tu top ko lap lai)
pendul(0,16,gray,4,3,220,100,0);
pendul(0,16,gray,4,3,220,100,1);
pendul(0,16,gray,4,3,220,100,2);
pendul(0,16,gray,4,3,220,100,3);
*/
void pendul(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t back_light,uint8_t front_light,uint8_t style)
{
	set_value(bot,top,back_light,gray);
	set_value(bot,style+bot,front_light,gray);
	while(repeat>0)
	{
		
			for (uint8_t i=0;i<(top-bot-style);i++)
			{
					pwm_gen(speed,gray);
					if (gray[top] ==0) break;
					rotatal(bot,top,gray,1,1);
			}
			
			for (uint8_t i=0;i<(top-bot-style);i++)
			{
				pwm_gen(speed,gray);
				if (gray[bot] ==0) break;
				rotatal(bot,top,gray,1,0);
			}
		repeat--;
	}
	
	set_value(bot,top,RESOLUS,gray);
}

/*
23/08/2013
void fill_pendul(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t back_light,uint8_t style)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
back_light: do sang nen
style: khoi luong con lac
fill_pendul(0,31,gray,1,40,1);
*/
void fill_pendul(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t back_light,uint8_t style)
{
	set_value(bot,top,back_light,gray);
	set_value(bot,style+bot-1,RESOLUS,gray);
	
	for (uint8_t k = 0;k<250;k++)
	{
		for (uint8_t i=0;i<250;i++)
		{
			pwm_gen(speed,gray);
			if (gray[top] ==RESOLUS) break;
			rotatal(bot,top,gray,1,1);
		}
			 set_value(top,top,RESOLUS,gray);
			 top--;
			 set_value(top-style,top-1,RESOLUS,gray);
			 
			if (bot==top) break;

		for (uint8_t i=0;i<250;i++)
		{
			pwm_gen(speed,gray);
			if (gray[bot] ==RESOLUS) break;
			rotatal(bot,top,gray,1,0);
		}
		
			set_value(bot,bot,RESOLUS,gray);
			bot++;
			set_value(bot,bot+style-1,RESOLUS,gray);
			if (bot==top) break;
	}
	
		set_value(bot,top,RESOLUS,gray);
}


/*
2/03/2013
auto_change(bot,top,*gray,speed,step,val)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
step: buoc tang giam
val: gia tri tang giam den
auto_change(0,31,gray,1,5,random());
*/
 void auto_change(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t val)
{
	volatile uint8_t *point;
	uint8_t lenght;
	lenght = top - bot;
	point = gray + bot;
	
	while(check_equ(bot,top,gray,val) == 0)
		{
		point = gray + bot;
		for (uint8_t i=0;i<=lenght;i++)
		{
			if (*point<val)
			{
				for (uint8_t j = 0;j<step;j++)
				{
				*point = *point+1;
				if (*point==val) break;
				}
			}			
			
			else if (*point>val)
			{
				for (uint8_t j = 0;j<step;j++)
				{
					
				*point = *point-1;
				if (*point==val) break;			
				}
			}
			
			point++;
		}
		pwm_gen(speed,gray);
		
	}	
}
/*
23/08/2013
shooting_star(bot,top,*gray,speed,size,postion,direct )[hieu ung sao bang]
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
size: chieu dai sao
postion: vi tri xuat hien
direct: chieu chuyen dong cua sao

shooting_star(0,31,gray,2,16,1);
shooting_star(0,31,gray,2,16,0);
*/

void shooting_star(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t size,uint8_t direct )
{
	
	uint8_t buf_gray[(top+size+1)-bot];
	uint8_t temp;
	temp = RESOLUS/size;
	set_value(0,sizeof(buf_gray)-1,0,buf_gray);
	if(direct==0)
	{
		for (uint8_t i =1;i<=size;i++)
			buf_gray[i-1] = temp*i;

	for (uint8_t k = 0;k<sizeof(buf_gray);k++)
	{
		for (uint8_t i = 0;i<((top+1)-bot);i++)
		gray[bot+i] = buf_gray[size+i];
		
		pwm_gen(speed,gray);	
		rotatal(0,sizeof(buf_gray)-1,buf_gray,1,1);
	}
	
	}
	else
	{
		for (uint8_t i =1;i<=size;i++)
		buf_gray[i-1] = temp*(size-(i-1));

		for (uint8_t k = 0;k<sizeof(buf_gray);k++)
		{
			for (uint8_t i = 0;i<((top+1)-bot);i++)
			gray[bot+i] = buf_gray[size+i];
			
			pwm_gen(speed,gray);
			rotatal(0,sizeof(buf_gray)-1,buf_gray,1,0);
		}
	}
	set_value(bot,top,RESOLUS,gray);
}


/*
fill_drop(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t size,uint8_t direct )
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
size: chieu dai sao
direct: chieu chuyen dong cua sao
fill_drop(0,11,gray,5,8,0);
*/
void fill_drop(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t size,uint8_t direct )
{
		set_value(bot,top,0,gray);
		
		if (direct==0)
		{
				for (int i = top;i>=bot;i--)
				{
					shooting_star(bot,i,gray,speed,size,0);
					auto_change(i,i,gray,2,RESOLUS/10,RESOLUS);
				}
		}
		else
		{
			
			for (int i = bot;i<=top;i++)
			{
				shooting_star(i,top,gray,speed,size,1);
				auto_change(i,i,gray,2,RESOLUS/10,RESOLUS);
			}
			
		}
	
		set_value(bot,top,RESOLUS,gray);
}

/*
void bytwo(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t brigness,uint8_t type_radian,uint8_t direct)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
repeat: so lan lap lai
brigness: do sang (=0 sang nhat)
type_radian: huong vetor
direct: chieu quay
bytwo(0,11,gray,5,5,10,1,1);
	

*/
void bytwo(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t brigness,uint8_t type_radian,uint8_t direct)
{
	uint8_t bot1 = bot;
	uint8_t top1 = bot+(top-bot)/2;
	uint8_t bot2 = bot+(top-bot)/2 +1;
	uint8_t top2 = top;
	uint8_t cicle = (top-bot +1)/2;
	switch (type_radian)
	{
		case 0:
		radian_gen(bot1,top1,gray,RESOLUS,0,1,brigness);
		radian_gen(bot2,top2,gray,RESOLUS,0,1,brigness);
		break;
		case 1:
		radian_gen(bot1,top1,gray,RESOLUS,1,1,brigness);
		radian_gen(bot2,top2,gray,RESOLUS,0,1,brigness);
		break;
		case 2:
		radian_gen(bot1,top1,gray,RESOLUS,0,1,brigness);
		radian_gen(bot2,top2,gray,RESOLUS,1,1,brigness);
		break;
		default:
		radian_gen(bot1,top1,gray,RESOLUS,1,1,brigness);
		radian_gen(bot2,top2,gray,RESOLUS,1,1,brigness);
		break;
	}
	
	while (repeat>0)
	{
		
	for (uint8_t i = 0;i<cicle;i++)
	{

	switch (direct)
	{
		case 0:
		rotatal(bot1,top1,gray,1,0);
		rotatal(bot2,top2,gray,1,0);
		break;
		case 1:
		rotatal(bot1,top1,gray,1,0);
		rotatal(bot2,top2,gray,1,1);
		break;
		case 2:
		rotatal(bot1,top1,gray,1,1);
		rotatal(bot2,top2,gray,1,0);
		break;
		default:
		rotatal(bot1,top1,gray,1,1);
		rotatal(bot2,top2,gray,1,1);
		break;
	}
		pwm_gen(speed,gray);
		
	}	
		
	repeat--;
	}
}

/*
void growing(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t size,uint8_t type)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
step: buoc sang
size: kich thuoc khoi
type: kieu 0 - 3
growing(0,31,gray,5,15,7,2);

*/
void growing(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t size,uint8_t type)
{
	uint8_t bot1 = bot;
	uint8_t top1 = bot+(top-bot)/2;
	uint8_t bot2 = bot+(top-bot)/2 +1;
	uint8_t top2 = top;
	uint8_t temp = RESOLUS/step;
	
	set_value(bot,top,0,gray);
	
	switch (type)
	{
		case 0:
		
		for (uint8_t i = 0;i<step;i++)
		{
			for (uint8_t k = 0;k<size;k++)
			{
				set_value(bot,bot,i*temp,gray);
				pwm_gen(speed,gray);
				rotatal(bot,top,gray,1,1);
			}
		}
		
		while (!check_equ(bot,top,gray,RESOLUS))
		{
			set_value(bot,bot,RESOLUS,gray);
			pwm_gen(speed,gray);
			rotatal(bot,top,gray,1,1);
		}

		break;
		
		case 1:
		
		for (uint8_t i = 0;i<step;i++)
		{
			for (uint8_t k = 0;k<size;k++)
			{
				set_value(top,top,i*temp,gray);
				pwm_gen(speed,gray);
				rotatal(bot,top,gray,1,0);
			}
		}

		while (!check_equ(bot,top,gray,RESOLUS))
		{
			set_value(top,top,RESOLUS,gray);
			pwm_gen(speed,gray);
			rotatal(bot,top,gray,1,0);
		}

		break;
		
		
		case 2:
		
		for (uint8_t i = 0;i<step;i++)
		{
			for (uint8_t k = 0;k<size;k++)
			{
				
				set_value(bot2,bot2,i*temp,gray);
				set_value(top1,top1,i*temp,gray);
				pwm_gen(speed,gray);
				rotatal(bot2,top2,gray,1,1);
				rotatal(bot1,top1,gray,1,0);
			}
		}
		
		while (!check_equ(bot,top,gray,RESOLUS))
		{
			set_value(bot2,bot2,RESOLUS,gray);
			set_value(top1,top1,RESOLUS,gray);
			pwm_gen(speed,gray);
			rotatal(bot2,top2,gray,1,1);
			rotatal(bot1,top1,gray,1,0);
		}

		break;
		
		default:
		for (uint8_t i = 0;i<step;i++)
		{
			for (uint8_t k = 0;k<size;k++)
			{
				
				set_value(top2,top2,i*temp,gray);
				set_value(bot1,bot1,i*temp,gray);
				pwm_gen(speed,gray);
				rotatal(bot2,top2,gray,1,0);
				rotatal(bot1,top1,gray,1,1);
			}
		}
		
		while (!check_equ(bot,top,gray,RESOLUS))
		{
			set_value(top2,top2,RESOLUS,gray);
			set_value(bot1,bot1,RESOLUS,gray);
			pwm_gen(speed,gray);
			rotatal(bot2,top2,gray,1,0);
			rotatal(bot1,top1,gray,1,1);
		}
		
		break;
		
	}
	
}

/*
void downing(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t size,uint8_t type)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
step: buoc sang
size: kich thuoc khoi
type: kieu 0 - 3
downing(0,31,gray,5,15,7,2);
*/
void downing(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t size,uint8_t type)
{
	uint8_t bot1 = bot;
	uint8_t top1 = bot+(top-bot)/2;
	uint8_t bot2 = bot+(top-bot)/2 +1;
	uint8_t top2 = top;
	uint8_t temp = RESOLUS/step;
	set_value(bot,top,RESOLUS,gray);
	
	switch (type)
	{
		case 0:
		
		for (uint8_t i = 0;i<step;i++)
		{
			for (uint8_t k = 0;k<size;k++)
			{
				set_value(bot,bot,(step-i)*temp,gray);
			pwm_gen(speed,gray);
				rotatal(bot,top,gray,1,1);
			}
		}
		
		while (!check_equ(bot,top,gray,0))
		{
			set_value(bot,bot,0,gray);
			pwm_gen(speed,gray);
			rotatal(bot,top,gray,1,1);
		}

		break;
		
		case 1:
		
		for (uint8_t i = 0;i<step;i++)
		{
			for (uint8_t k = 0;k<size;k++)
			{
				set_value(top,top,(step-i)*temp,gray);
				pwm_gen(speed,gray);
				rotatal(bot,top,gray,1,0);
			}
		}

		while (!check_equ(bot,top,gray,0))
		{
			set_value(top,top,0,gray);
			pwm_gen(speed,gray);
			rotatal(bot,top,gray,1,0);
		}

		break;
		
		
		case 2:
		
		for (uint8_t i = 0;i<step;i++)
		{
			for (uint8_t k = 0;k<size;k++)
			{
				
				set_value(bot2,bot2,(step-i)*temp,gray);
				set_value(top1,top1,(step-i)*temp,gray);
				pwm_gen(speed,gray);
				rotatal(bot2,top2,gray,1,1);
				rotatal(bot1,top1,gray,1,0);
			}
		}
		
		while (!check_equ(bot,top,gray,0))
		{
			set_value(bot2,bot2,0,gray);
			set_value(top1,top1,0,gray);
			pwm_gen(speed,gray);
			rotatal(bot2,top2,gray,1,1);
			rotatal(bot1,top1,gray,1,0);
		}

		break;
		
		default:
		for (uint8_t i = 0;i<step;i++)
		{
			for (uint8_t k = 0;k<size;k++)
			{
				
				set_value(top2,top2,(step-i)*temp,gray);
				set_value(bot1,bot1,(step-i)*temp,gray);
			pwm_gen(speed,gray);
				rotatal(bot2,top2,gray,1,0);
				rotatal(bot1,top1,gray,1,1);
			}
		}
		
		while (!check_equ(bot,top,gray,0))
		{
			set_value(top2,top2,0,gray);
			set_value(bot1,bot1,0,gray);
			pwm_gen(speed,gray);
			rotatal(bot2,top2,gray,1,0);
			rotatal(bot1,top1,gray,1,1);
		}
		
		break;
		
	}
	
}

/*
void fill_seed(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t type)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
step: buoc nhay
type: kieu 0 - 3
fill_seed(0,15,gray,1,3,2);
fill_seed(0,15,gray,1,20,3);
*/

void fill_seed(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t type)
{
	uint8_t t_bot = bot;
	uint8_t t_top = top;
		switch (type)
		{
			case 0:
			
			set_value(t_bot,t_top,0,gray);
			for (uint8_t i= 0;i<250;i++)
			{
				if (bot>=top) break;
				seed(bot,top,gray,speed,step,1);
				set_value(bot,bot,RESOLUS,gray);
				bot++;
			}
			set_value(t_bot,t_top,RESOLUS,gray);
			break;
			
			case 1:
			set_value(t_bot,t_top,0,gray);
			for (uint8_t i= 0;i<250;i++)
			{
				if (bot>=top) break;
				seed(bot,top,gray,speed,step,0);
				set_value(top,top,RESOLUS,gray);
				top--;
			}
			set_value(t_bot,t_top,RESOLUS,gray);
			break;
			
			case 2:
				set_value(t_bot,t_top,0,gray);
			for (uint8_t i= 0;i<250;i++)
			{
				if (bot>=top) break;
				seed(bot,top,gray,speed,step,0);
				set_value(top,top,RESOLUS,gray);
				top--;
				if (bot>=top) break;
				seed(bot,top,gray,speed,step,1);
				set_value(bot,bot,RESOLUS,gray);
				bot++;
	
			}
				set_value(t_bot,t_top,RESOLUS,gray);
			break;
			
			
				default:
				set_value(t_bot,t_top,RESOLUS,gray);
				for (uint8_t i= 0;i<250;i++)
				{
					if (bot>=top) break;
					seed(bot,top,gray,speed,step,2);
					set_value(top,top,0,gray);
					top--;
					if (bot>=top) break;
					seed(bot,top,gray,speed,step,3);
					set_value(bot,bot,0,gray);
					bot++;
					
				}
				set_value(t_bot,t_top,0,gray);
				break;
		}
}
/*
void seed(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t type)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
step: buoc nhay
type: kieu 0 - 3
seed(0,15,gray,1,3,2);
seed(0,15,gray,1,3,3);
*/
void seed(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t type)
{
	switch (type)
	{
	case 0:
	
	for (uint8_t i = 0;i<250;i++)
	{
		twopoint(bot,bot+1,gray,speed,step,1);
		bot++;
		if (bot==top) break;
		
	}
	break;
	case 1:
		for (uint8_t i = 0;i<250;i++)
		{
			twopoint(top-1,top,gray,speed,step,0);
			top--;
			if (bot==top) break;
			
		}
	
	break;
	
	case 2:
		for (uint8_t i = 0;i<250;i++)
		{
			twopoint(bot,bot+1,gray,speed,step,0);
			bot++;
			if (bot==top) break;
		}
	
	break;
	default:
		for (uint8_t i = 0;i<250;i++)
		{
			twopoint(top-1,top,gray,speed,step,1);
			top--;
			if (bot==top) break;
			
		}
	break;
	}
	
	set_value(bot,top,RESOLUS,gray);
}
/*
void twopoint(uint8_t point1,uint8_t point2,volatile uint8_t *gray,uint8_t speed,uint8_t step,uint8_t type)
point1:vi tri 1
point2:vi tri 2
*gray: vi tri chua du lieu
speed:toc do
step: buoc nhay
repeat:so lan lap lai
type: kieu 0 - 1
twopoint(0,1,gray,5,4,0);
*/

void twopoint(uint8_t point1,uint8_t point2,volatile uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t type)
{
	switch (type)
	{
		case 0:
			for (uint8_t i=0;i<=RESOLUS;i+=8)
			{
				gray[point1]=RESOLUS-i;
				pwm_gen(speed,gray);
			}

			for (uint8_t k = 0; k < repeat; k++)
			{
				
				for (uint8_t i=0;i<=RESOLUS;i+=8)
				{
					gray[point1]=i;
					gray[point2]=RESOLUS-i;

					pwm_gen(speed,gray);
				}
				
				for (uint8_t i=0;i<=RESOLUS;i+=8)
				{
					gray[point1]=RESOLUS-i;
					gray[point2]=i;

					pwm_gen(speed,gray);
				}
				
			}
			gray[point1]=RESOLUS;
			
		break;
		default:
					for (uint8_t i=0;i<=RESOLUS;i+=8)
					{
						gray[point2]=RESOLUS-i;
						pwm_gen(speed,gray);
					}

					for (uint8_t k = 0; k < repeat; k++)
					{
						
						for (uint8_t i=0;i<=RESOLUS;i+=8)
						{
							gray[point1]=RESOLUS-i;
							gray[point2]=i;

							pwm_gen(speed,gray);
						}
						
						for (uint8_t i=0;i<=RESOLUS;i+=8)
						{
							gray[point1]=i;
							gray[point2]=RESOLUS-i;

							pwm_gen(speed,gray);
						}
					}
					
					gray[point2]=RESOLUS;
		break;
	}
		
}

/*
void fill_combine(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t backgound,uint8_t type)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
backgound:nen
type: kieu 0 - 1
fill_combine(0,31,gray,2,10,1);
fill_combine(0,31,gray,2,10,0);
*/

void fill_combine(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t backgound,uint8_t type)
{
	switch (type)
	{
		case 0:
			
			for (uint8_t i= 0;i<250;i++)
			{
				if (bot>=top) break;
				combine(bot,top,gray,speed,1,backgound,0);
				set_value(bot,bot,RESOLUS,gray);
				set_value(top,top,RESOLUS,gray);
				top--;
				bot++;
			}
		break;
		default:
		for (uint8_t i= 0;i<250;i++)
		{
			if (bot>=top) break;
			combine(bot,top,gray,speed,1,RESOLUS,1);
			set_value(bot,bot,backgound,gray);
			set_value(top,top,backgound,gray);
			top--;
			bot++;
		
		}
		
		break;
	}
	
}

/*
void combine(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t backgound,uint8_t type)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
backgound:nen
type: kieu 0 - 1
combine(0,31,gray,5,5,50,0);
combine(0,31,gray,5,5,50,1);
*/
void combine(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t backgound,uint8_t type)
{
	uint8_t _buff1[top-bot+1];
	uint8_t _buff2[top-bot+1];
	
		set_value(0,sizeof(_buff1)-1,backgound,_buff1);
		set_value(0,sizeof(_buff2)-1,backgound,_buff2);
	switch (type)
	{
		case 0:
		
		while(repeat>0)
		{
			
			set_value(0,0,RESOLUS,_buff2);
			set_value(sizeof(_buff1)-1,sizeof(_buff1)-1,RESOLUS,_buff1);
			for (uint8_t k=0;k<(top-bot+1);k++)
			{
				for (uint8_t i=0;i<(top-bot+1);i++)
				gray[i+bot]=_buff1[i]|_buff2[i];
				pwm_gen(speed,gray);
				rotatal(0,sizeof(_buff1)-1,_buff1,1,1);
				rotatal(0,sizeof(_buff2)-1,_buff2,1,0);
			}
			repeat--;
		}
		
		break;
		default:
		while(repeat>0)
		{
		set_value(0,0,0,_buff1);
		set_value(sizeof(_buff2)-1,sizeof(_buff2)-1,0,_buff2);
		for (uint8_t k=0;k<(top-bot+1);k++)
		{
			for (uint8_t i=0;i<(top-bot+1);i++)
			gray[i+bot]=_buff1[i]&_buff2[i];
			pwm_gen(speed,gray);
			rotatal(0,sizeof(_buff1)-1,_buff1,1,1);
			rotatal(0,sizeof(_buff2)-1,_buff2,1,0);
		}
			repeat--;
		}
		break;
	}
	set_value(bot,top,RESOLUS,gray);
}

/*
void sleep(uint16_t interval,volatile uint8_t *gray)
interval:khoang thoi gian
*gray: vi tri chua du lieu
*/
void sleep(uint16_t interval,volatile uint8_t *gray)
{
	for (uint16_t i = 0;i<interval;i++)
	pwm_gen(1,gray);
}
/*
void hard_flash(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t type)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
repeat:so lan lap lai
type: kieu 0 - 1
hard_flash(0,31,gray,3,3,1);
*/

void hard_flash(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t type)
	{
		
		if (type==0)
		{
			for (uint8_t i=0;i<repeat;i++)
			{
				set_value(bot,top,RESOLUS,gray);
				sleep(speed,gray);
				set_value(bot,top,0,gray);
				sleep(speed,gray);
			}
			
			
		}
		else
		{
			for (uint8_t i=0;i<repeat;i++)
			{
				set_value(bot,top,0,gray);
				sleep(speed,gray);
				set_value(bot,top,RESOLUS,gray);
				sleep(speed,gray);
				
			}
			
		}
		
	}
	
/*
void running_flash(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t back_gound,uint8_t type)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
repeat:so lan lap lai
backgound: muc sang nen
type: kieu 0 - 1
running_flash(0,31,gray,5,3,10,0);
running_flash(0,31,gray,5,3,10,1);
*/
void running_flash(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t back_gound,uint8_t type)
{
	if (type==0)
		{
			uint8_t t_bot= bot;	
			for (uint8_t i=0;i<(top-bot+1);i++)
			{
				hard_flash(t_bot,t_bot,gray,speed,repeat,1);
				set_value(t_bot,t_bot,back_gound,gray);
				t_bot++;
			}
			
		}
		else
		{
			uint8_t t_top= top;
				for (uint8_t i=0;i<(top-bot+1);i++)
				{
					hard_flash(t_top,t_top,gray,speed,repeat,1);
					set_value(t_top,t_top,back_gound,gray);
					t_top--;
				}
		}
		set_value(bot,top,RESOLUS,gray);
		
}

/*
void running_flash(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t back_gound,uint8_t type)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
repeat:so lan lap lai
val1: do sang bat dau
val2:do sang ket thuc
flash(0,31,1,3,0,255);
*/
void soft_flash(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t val1,uint8_t val2)
{
	while(repeat>0)
	{
		auto_change(bot,top,gray,speed,RESOLUS/10,val1);
		auto_change(bot,top,gray,speed,RESOLUS/10,val2);
		repeat--;
	}
}


/*
void odd_even(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t step)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
repeat:so lan lap lai
step: buoc chuyen
odd_even(0,15,gray,2,10,1);
*/
void odd_even(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t step)
{
	uint8_t value = 0;
	uint8_t count = 0;
	
	for (uint16_t m = 0;m<repeat;m++)
	{
		value = 0;
		count = 0;
			for (uint16_t k = 0;k<=RESOLUS;k++)
			{
				count +=1;
				value = k;
				if (count == step)
				{
					for (uint16_t i =bot;i<=top;i+=2)
					{
						gray[i] = value;
						gray[i+1] =RESOLUS - value;
					}
					count = 0;
				}
				
				pwm_gen(speed,gray);
			}
			
			
			for (uint16_t k = 0;k<=RESOLUS;k++)
			{
				count +=1;
				value = k;
				if (count == step)
				{
					for (uint8_t i =bot;i<=top;i+=2)
					{
						
						gray[i] =RESOLUS - value;
						gray[i+1] = value;
					}
					count = 0;
				}
				
				pwm_gen(speed,gray);
			}
	}
		
	set_value(bot,top,RESOLUS,gray);
}

/*
void n_rota(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t direct,uint8_t speed,uint16_t repeat )
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
direct:huong quay
speed:toc do
repeat:so lan lap lai

*/

void n_rota(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t direct,uint8_t speed,uint16_t repeat )
{
	for (uint16_t i = 0;i<=repeat;i++)
	{
		rotatal(bot,top,gray,1,direct);
		pwm_gen(speed,gray);
	}
		
}

/*
void border(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,uint8_t *point,uint8_t type)
bot:vi tri bat dau phat
top:vi tri cuoi
*gray: vi tri chua du lieu
speed:toc do
repeat:so lan lap lai
point: trang thai
type: kieu chay 
border(7,10,gray,20,10,vien,1);
*/

void border(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint8_t repeat,const uint8_t *point,uint8_t type)
	{
			load_value(bot,top,gray,point);
			for (uint8_t j = 0;j<repeat;j++)
			{
				for (uint8_t i=0;i<(top-bot+1);i++)
				{
					pwm_gen(speed,gray);
					rotatal(bot,top,gray,1,type);
				}
			}
				set_value(bot,top,RESOLUS,gray);
	}
	
	

void load_value(uint8_t bot,uint8_t top,uint8_t *gray,const uint8_t *point)
{
		uint8_t k = 0;
		for (uint8_t i =bot;i<=top;i++)
		{
			gray[i]=pgm_read_byte(&point[k]);
			k++;
		}
}


void random_light_st1(uint8_t bot,uint8_t top,volatile uint8_t *gray,uint8_t speed,uint16_t repeat,uint8_t max_sleep)
{
	//uint8_t pharse[top-bot+1];
	uint8_t flag[top-bot+1];
	uint16_t time_sleep[top-bot+1];
//	uint8_t counter = 0;
	//for (uint8_t i = 0;i<=(top-bot+1);i++) pharse[i] = random()%(RESOLUS+1);
	for (uint8_t i = 0;i<=(top-bot+1);i++) flag[i] = rand()%2;
	for (uint8_t i = 0;i<=(top-bot+1);i++) time_sleep[i] =rand()%max_sleep;
	
	//while (1)
	//{
			//counter = 0;
		//for (uint8_t i = 0;i<(top-bot+1);i++)
		//{
			//
			//if (gray[i]>pharse[i]) gray[i]-=1;
			//else if (gray[i]<pharse[i]) gray[i]+=1;
			//else continue;
			//counter+=1;
			//
		//}
		//pwm_gen(speed,gray);
		//if (counter==0) break;
		//
	//}
	for (uint16_t k= 0;k<repeat;k++)
	{
			for (uint8_t i = 0;i<(top-bot+1);i++)
			{
				
				
				if (flag[i]>=1)
				{
					if (gray[i]<RESOLUS) gray[i]+=1;
					else
					{
						gray[i] = RESOLUS;
						if (time_sleep[i]<=0)
						{
							time_sleep[i]=rand()%max_sleep;
							 flag[i] = 0;
						}
						else 
						{
							time_sleep[i]-=1;
							continue;
						}
						
					}
				}
				else
				{
					if (gray[i]>0) gray[i]-=1;
					else
					{
						gray[i] = 0;
						if (time_sleep[i]<=0)
						{
							time_sleep[i]=rand()%max_sleep;
								flag[i] = 1;
						}
						else
						{
							time_sleep[i]-=1;
							continue;
						}
					
					}
				}
				
			}

		pwm_gen(speed,gray);
	}
}


void random_light_st2(uint8_t bot,uint8_t top,uint8_t *gray,uint8_t speed,uint16_t repeat)
{
	uint8_t pharse[top-bot+1];
	uint8_t flag[top-bot+1];
	for (uint8_t i = 0;i<=(top-bot+1);i++) pharse[i] =RESOLUS;
	for (uint8_t i = 0;i<=(top-bot+1);i++) flag[i] = rand()%2;
	for (uint16_t k= 0;k<repeat;k++)
	{
			for (uint8_t i = 0;i<(top-bot+1);i++)
			{
				if (flag[i]>=1)
				{
					if (gray[i]<pharse[i]) gray[i]+=1;	
					else 
						{
							gray[i]=rand()%(RESOLUS+1);
							flag[i] = 0;
						}
				}
				else
				{
					if (gray[i]>pharse[i]) gray[i]-=1;
					else
					{
						 gray[i]=0;
						 flag[i] = 1;
					}
				}
			}

		pwm_gen(speed,gray);
	}
}