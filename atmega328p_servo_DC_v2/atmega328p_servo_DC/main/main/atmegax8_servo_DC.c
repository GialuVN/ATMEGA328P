/*
 * atmegax8_servo_DC.c
 *
 * Created: 6/16/2015 9:33:12 AM
 *  Author: admin
 */ 


#include "atmegax8_servo_DC.h"
#include "disp/xiudun2008V.h"
#include "pwm/pwm6ch.h"
#include "remote/pt2260_dec.h"
volatile SERVO_INPUT servo_input;
volatile SERVO_CTR servo_ctr;
volatile SERVO_PID servo_pid;





void SERVO_SPEED_PID(int kp,int ki,int kd)
{
	
	unsigned int _e;
	unsigned int kp_part;
	unsigned int kd_part;
	double ki_part;
	unsigned int pid;
	ki_part = 0;
	kd_part = 0;
	_e = abs(servo_input.servo_input_speed-servo_ctr.servo_speed);
	
	if ((kp*_e)>SERVO_MAX_FORCE) kp_part=SERVO_MAX_FORCE;
	else kp_part=kp*_e;
	
	
	
	if (servo_input.servo_input_speed>servo_ctr.servo_speed)
	{
		
		
		
	}
	
	
	else if (servo_input.servo_input_speed<servo_ctr.servo_speed)
	{
		
		
		
	}
	
	else
	{
		
	}
	
	
	if ((kp*_e/10)>SERVO_MAX_FORCE) kp_part = SERVO_MAX_FORCE;
	else kp_part =(unsigned int)(kp*_e/10);
	
	if ((kd*servo_ctr.servo_speed)>SERVO_MAX_FORCE) kd_part = SERVO_MAX_FORCE;
	else kd_part =kd*servo_ctr.servo_speed;
	
	
	if (_e>SERVO_MAX_FORCE) servo_pid.servo_pos_i= KI_POS_MIN;
	else
	{
		if ((((double)ki*_e/100)+servo_pid.servo_pos_i)>SERVO_MAX_FORCE) servo_pid.servo_pos_i=SERVO_MAX_FORCE;
		else servo_pid.servo_pos_i+=(double)ki*_e/100;
		ki_part= servo_pid.servo_pos_i;
	}
	
	if ((kp_part+ki_part+kd_part)>SERVO_MAX_FORCE) pid=SERVO_MAX_FORCE;
	else pid =kp_part+ki_part+kd_part;
	
	if (servo_ctr.servo_position>servo_input.servo_input_pos)
	{
		SERVO_FORCE(pid);
		SERVO_DIR(TURN_LEFT);
	}
	
	else if (servo_ctr.servo_position<servo_input.servo_input_pos)
	{
		SERVO_FORCE(pid);
		SERVO_DIR(TURN_RIGHT);
	}
	
	else
	{
		servo_pid.servo_pos_i=KI_POS_MIN;
		SERVO_FORCE(0);
	}
	
	
	
	
	
	
}





void SERVO_POS_PID(int kp,int ki,int kd)
{
	unsigned long _e;
	unsigned int kp_part;
	unsigned int kd_part;
	double ki_part;
	unsigned int pid;
	ki_part = 0;
	kd_part = 0;
	 _e = labs(servo_input.servo_input_pos-servo_ctr.servo_position);
	 
	if ((kp*_e)>SERVO_MAX_FORCE) kp_part = SERVO_MAX_FORCE;
	else kp_part =(unsigned int)(kp*_e);
	
	if ((kd*servo_ctr.servo_speed)>SERVO_MAX_FORCE) kd_part = SERVO_MAX_FORCE;
	else kd_part =kd*servo_ctr.servo_speed;
	
	if (_e>SERVO_MAX_FORCE) servo_pid.servo_pos_i= 0;
	else
	{
		if ((((double)ki*_e/250)+servo_pid.servo_pos_i)>SERVO_MAX_FORCE) servo_pid.servo_pos_i=KI_POS_MIN;
		else servo_pid.servo_pos_i+=(double)ki*_e/250;
		ki_part= servo_pid.servo_pos_i;
	}
	
	if ((kp_part+ki_part+kd_part)>SERVO_MAX_FORCE) pid=SERVO_MAX_FORCE;
	else pid =kp_part+ki_part+kd_part;
	
	if (servo_ctr.servo_position>servo_input.servo_input_pos)
	{
		SERVO_FORCE(pid);
		SERVO_DIR(TURN_LEFT);
	}
	
	else if (servo_ctr.servo_position<servo_input.servo_input_pos)
	{
		SERVO_FORCE(pid);
		SERVO_DIR(TURN_RIGHT);
	}
	
	else 
	{
		servo_pid.servo_pos_i=KI_POS_MIN;
		SERVO_FORCE(0);
	}
	
}

































void SERVO_DC_initial()
{
	// encoder input config
	PH1_DDR &= ~(1<<PH1_PIN);
	PH2_DDR &= ~(1<<PH2_PIN);
	PH1_POR |= (1<<PH1_PIN);
	PH2_POR |= (1<<PH2_PIN);
	PCICR |= 1<<PCIE1;	// PCINT1 select
	PCMSK1 |= (1<<PCINT13)|(1<<PCINT12);
	
	//dir control ouput config
	DIR_DDR |= 1<<DIR_PIN;
	DIR_POR|=1<<DIR_PIN;
	//pwm control ouput config
	pwm_phasecorrect_timer1_option_initial(clk_timer1_div8,pwm_10bits);
	//Sampling PID
		TCCR2A = (1 << WGM21);                      // Set the Timer Mode to CTC
		OCR2A = 249;                                 // Set 249 as value to count to //f=250 c=4ms
		TIMSK2 |= (1 << OCIE0A);                     //Set the ISR COMPA vector
		TCCR2B |= (1 << CS20) | (1 << CS22) ;        // set pre-scaler to 128 and start the timer
		
		//display initial
		SEG7_initial();
		SEG7_disp_uint(0,0);
		//servo default
		SERVO_default();
		SERVO_DIR(TURN_RIGHT);
		SERVO_FORCE(500);
}

void SERVO_default(void)
{
	servo_input.servo_force = 500;
	servo_input.servo_input_dir=LEFT;
	servo_input.servo_input_pos=10000;
	servo_input.servo_input_speed=0;
	
	servo_ctr.servo_sample_rate = 1; //4ms
	servo_ctr.servo_position = 50000;
}


void SERVO_DIR(DIR _dir)
{
	if (_dir==TURN_LEFT) DIR_POR|=1<<DIR_PIN;
	else DIR_POR &=~(1<<DIR_PIN);
}


void SERVO_FORCE(int _val)
{
	if(_val>SERVO_MAX_FORCE) return;
	 pwm_servo_timer1_OCR1B_updata(1023-_val);
}


ISR(TIMER2_COMPA_vect)
{
		if (servo_ctr.servo_sample_counter==0)
		{
			servo_ctr.servo_sample_counter=servo_ctr.servo_sample_rate;
			
			servo_ctr.servo_speed =servo_ctr.servo_speed_sample;
			servo_ctr.servo_speed_sample=0;
			servo_ctr.servo_accelerator = servo_ctr.servo_speed -servo_ctr.servo_pre_speed;
			servo_ctr.servo_pre_speed = servo_ctr.servo_speed;
			////////////////////////////////PID CODE HERE//////////////////////////////
			
			 SERVO_POS_PID(7,3,20);
			
			//////////////////////////////////////////////////////////////////////////
			
		}
	else servo_ctr.servo_sample_counter--;
}


ISR(PCINT1_vect)
{
	unsigned char pre_dir_temp = 0;
	if (PH1_IN&(1<<PH1_PIN)) pre_dir_temp =1;
	if (PH2_IN&(1<<PH2_PIN)) pre_dir_temp|=1<<1;
	switch (pre_dir_temp)
	{
		case 0:
		if (servo_ctr.servo_pre_dir==1) servo_ctr.servo_dir = LEFT;
		else if (servo_ctr.servo_pre_dir==2) servo_ctr.servo_dir = RIGHT;
		else return;
		break;
		case 1:
		if (servo_ctr.servo_pre_dir==3) servo_ctr.servo_dir = LEFT;
		else if (servo_ctr.servo_pre_dir==0) servo_ctr.servo_dir = RIGHT;
		else return;
		break;
		case 2:
		if (servo_ctr.servo_pre_dir==0) servo_ctr.servo_dir = LEFT;
		else if (servo_ctr.servo_pre_dir==3) servo_ctr.servo_dir = RIGHT;
		else return;
		break;
		case 3:
		if (servo_ctr.servo_pre_dir==2) servo_ctr.servo_dir = LEFT;
		else if (servo_ctr.servo_pre_dir==1) servo_ctr.servo_dir = RIGHT;
		else return;
		break;
		default:
		break;
		//return;
	}
	servo_ctr.servo_pre_dir = pre_dir_temp;
	servo_ctr.servo_speed_sample++;
	if (servo_ctr.servo_dir)
	{
		if (servo_ctr.servo_position>=SERVO_MAX_POSITION)
		{
			servo_ctr.servo_range_check = SERVO_MAX_RANGE;
			 return;
		}
		else 
		{
			servo_ctr.servo_range_check = SERVO_IN_RANGE;
			servo_ctr.servo_position++;
		}
	}
	else
	{
		if (servo_ctr.servo_position<=0) 
		{
			servo_ctr.servo_range_check = SERVO_MIN_RANGE;
			return;
		}
		else 
		{
			servo_ctr.servo_range_check = SERVO_IN_RANGE;
			servo_ctr.servo_position--;
		}
	}
	
}