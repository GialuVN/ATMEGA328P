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
volatile SERVO_DC servo_dc;
volatile SERVO_CTR servo_ctr;
volatile SERVO_PID_SPEED servo_pid_speed;
volatile SERVO_PID_POSITION servo_pid_position;
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
		
//		DDRC|=1<<PINC3;
		
	//initial control
	servo_ctr.servo_position =  0;
	servo_ctr.servo_force = 1000;
	SERVO_DC_force(servo_ctr.servo_force);
	servo_ctr.servo_dir=LEFT;
	SERVO_DC_dir(servo_ctr.servo_dir);
	
	servo_ctr.servo_sample_rate = 1;
 SERVO_DC_PID_SPEED_UPDATA(10,5,25,10,RIGHT);
 //SERVO_DC_PID_POSITION_UPDATA(1,0,0,9900);
}

void SERVO_DC_PID_SPEED_UPDATA(unsigned int KP,unsigned int KI,unsigned int KD,unsigned int SPEED,unsigned char DIR)
{
	servo_pid_speed.dir = DIR;
	servo_pid_speed.servo_kd = KD;
	servo_pid_speed.servo_ki = KI;
	servo_pid_speed.servo_kp = KP;
	servo_pid_speed.servo_speed = SPEED;
	servo_pid_speed.servo_integral = 0;
}
//
//void SERVO_DC_PID_POSITION_UPDATA(unsigned int KP,unsigned int KI,unsigned int KD,unsigned long POSITION)
//{
	//servo_pid_position.servo_kd = KD;
	//servo_pid_position.servo_ki = KI;
	//servo_pid_position.servo_kp = KP;
	//servo_pid_position.servo_position = POSITION;
	//servo_pid_position.servo_integral = 0;
//}
void SERVO_CTR_initial()
{
	SEG7_initial();
	SEG7_disp_uint(0,0);
	
}


void SERVO_DC_DRIVER(SERVO_DC _val)
{
	SERVO_DC_dir(_val.servo_dir);
	SERVO_DC_force(_val.servo_force);
}


void SERVO_DC_dir(unsigned char _dir)
{
	if (_dir) DIR_POR|=1<<DIR_PIN;
	else DIR_POR &=~(1<<DIR_PIN);
}

void SERVO_DC_force(unsigned int _val)
{
	pwm_servo_timer1_OCR1B_updata(_val);
}

//
//SERVO_DC SERVO_DC_PID(unsigned int KP,unsigned int KI,unsigned int KD)
//{
	//SERVO_DC _servo_temp;
	//
//
	//
	//servo_pid.servo_kp = KP*abs(servo_ctr.servo_position_in-servo_ctr.servo_position)/10;
	//servo_pid.servo_kd = KD*servo_ctr.servo_speed/10;
	//if (servo_pid.servo_ki>SERVO_MAX_FORCE) servo_pid.servo_ki=0;
	//else servo_pid.servo_ki += KI*abs(servo_ctr.servo_position_in-servo_ctr.servo_position)/(float)100;
	//
	//servo_pid.servo_F = servo_pid.servo_kp - servo_pid.servo_kd + servo_pid.servo_ki;
	//
	//if(servo_pid.servo_F>SERVO_MAX_FORCE) 
	//{
		//servo_pid.servo_F = SERVO_MAX_FORCE;
		//servo_pid.servo_ki = 0;
	//}
	//
	//else if (servo_pid.servo_F<=0)  servo_pid.servo_F=0;
	//_servo_temp.servo_force =(unsigned int)servo_pid.servo_F;
	//
	//if (servo_ctr.servo_position_in>servo_ctr.servo_position) _servo_temp.servo_dir = LEFT;
	//else if (servo_ctr.servo_position_in<servo_ctr.servo_position) _servo_temp.servo_dir = RIGHT;
	//else _servo_temp.servo_force = 0;
	//
	//return _servo_temp;
//}




//
//SERVO_DC SERVO_DC_PID_POSITION(unsigned int KP,unsigned int KI,unsigned int KD,unsigned long POSITION)
//{
	//SERVO_DC _servo_temp;
	//unsigned long _temp = labs(POSITION-servo_ctr.servo_position);
	//unsigned int _kp_temp;
	//double _ki_temp; 
	//unsigned int _kd_temp; 
	//unsigned int _output_temp;
	////servo_pid_position.servo_integral +=(double)KI*_temp/((double)SERVO_MAX_FORCE+_temp);
	////_ki_temp=servo_pid_position.servo_integral;
	////unsigned int _kd_temp = KD*servo_ctr.servo_accelerator;
	////	unsigned int _ki_temp;
	//if (_temp<=SERVO_THRESHOLD)
		//{
			 //_kp_temp= KP*_temp;
			//if (_kp_temp>SERVO_MAX_FORCE)  _kp_temp = SERVO_MAX_FORCE;
			 //_output_temp= _kp_temp;
			 ////_kd_temp = KD*servo_ctr.servo_speed;
			 ////if (_kd_temp>SERVO_MAX_FORCE)  _kd_temp = SERVO_MAX_FORCE;
			 ////
			 ////_ki_temp = KI*(double)_temp/(SERVO_MAX_FORCE+_temp);
			 ////if (servo_pid_position.servo_integral>SERVO_MAX_FORCE)  servo_pid_position.servo_integral = 0;
			 ////servo_pid_position.servo_integral+=_ki_temp;
			 ////
			 ////if (_kd_temp>=(_kp_temp+ servo_pid_position.servo_integral)) _output_temp = 0;
			 ////else _output_temp=_kp_temp+ servo_pid_position.servo_integral+_kd_temp; 
			 ////
			 //
			 //SEG7_disp_uint(servo_ctr.servo_speed, _kp_temp);
			 //
		//}
		//else
		//{
			 //servo_pid_position.servo_integral=0;
			  //_output_temp=0;
		//}
	//
	//if (servo_ctr.servo_position>POSITION)
	//{
		//
		//if (_temp<=SERVO_THRESHOLD)
		//{
			//
			//if (_output_temp<=SERVO_MAX_FORCE) _servo_temp.servo_force = _output_temp;
			//else
			//{
				//_servo_temp.servo_force = SERVO_MAX_FORCE;
			//}
		//}
		//_servo_temp.servo_dir = RIGHT;
		//
	//}
	//
	//else if (servo_ctr.servo_position<POSITION)
	//{
		//
		//
		//if (_temp<=SERVO_THRESHOLD)
		//{
			//if (_output_temp<=SERVO_MAX_FORCE) _servo_temp.servo_force = _output_temp;
			//else
			//{
				//_servo_temp.servo_force = SERVO_MAX_FORCE;
			//}
		//}
		//
		//_servo_temp.servo_dir = LEFT;
	//}
	//else
	//{
		//servo_pid_position.servo_integral=0;
		//_servo_temp.servo_force =0;
	//}
	//
	//return _servo_temp;
	//
//}

SERVO_DC SERVO_DC_PID_SPEED(unsigned int KP,unsigned int KI,unsigned int KD,unsigned int SPEED,unsigned char DIR)
{
	SERVO_DC _servo_temp;
	unsigned int _temp = abs(servo_ctr.servo_speed-SPEED);
	unsigned int _kp_temp =(KP*_temp*(SERVO_MAX_SPEED/(float)SERVO_MAX_FORCE));
	unsigned int _kd_temp = KD*servo_ctr.servo_accelerator;
	unsigned int _ki_temp;
	servo_pid_speed.servo_integral += KI*_temp*(SERVO_MAX_SPEED/(float)SERVO_MAX_FORCE)/(float)10;
	_ki_temp =servo_pid_speed.servo_integral;
	_servo_temp.servo_dir=DIR;
	_servo_temp.servo_force = servo_ctr.servo_force;
	
	if (servo_ctr.servo_speed>SPEED)
	{
		if (_servo_temp.servo_force>=_kp_temp) _servo_temp.servo_force-=_kp_temp;
		if (_servo_temp.servo_force>=KI*_ki_temp) _servo_temp.servo_force-=KI*_ki_temp;
		else
		{
				if ( (_servo_temp.servo_force>0)) _servo_temp.servo_force-=1;
		}
		if (servo_ctr.servo_accelerator>0)
		{
				if (_servo_temp.servo_force>=_kd_temp) _servo_temp.servo_force-=_kd_temp;
		}
	}
	else if (servo_ctr.servo_speed<SPEED)
	{
		if ((_servo_temp.servo_force+_kp_temp)<=SERVO_MAX_FORCE) _servo_temp.servo_force+=_kp_temp;
		if (((_servo_temp.servo_force+_ki_temp)<=SERVO_MAX_FORCE)) _servo_temp.servo_force+=_ki_temp;
		else
		{
				if ( (_servo_temp.servo_force+1)<=SERVO_MAX_FORCE) _servo_temp.servo_force+=1;
		}
		
		if (servo_ctr.servo_accelerator<0)
		{
				if ((_servo_temp.servo_force+abs(_kd_temp))<=SERVO_MAX_FORCE) _servo_temp.servo_force+=abs(_kd_temp);
		}
	}
	else servo_pid_speed.servo_integral = 0;
	 servo_ctr.servo_force=_servo_temp.servo_force;
	return _servo_temp;
}


ISR(TIMER2_COMPA_vect)
{
		if (servo_ctr.servo_sample_counter==0)
		{
			servo_ctr.servo_sample_counter=servo_ctr.servo_sample_rate;
			servo_ctr.servo_speed =servo_ctr.servo_speed_sample;
			servo_ctr.servo_speed_sample=0;
			servo_ctr.servo_accelerator =(int)servo_ctr.servo_speed -(int)servo_ctr.servo_pre_speed;
			servo_ctr.servo_pre_speed = servo_ctr.servo_speed;
			
			//SEG7_disp_uint(servo_ctr.servo_position,servo_ctr.servo_speed);
			
			SERVO_DC_DRIVER(SERVO_DC_PID_SPEED(servo_pid_speed.servo_kp,servo_pid_speed.servo_ki,servo_pid_speed.servo_kd,servo_pid_speed.servo_speed,servo_pid_speed.dir));
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