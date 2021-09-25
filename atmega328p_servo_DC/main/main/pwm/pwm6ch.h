/*
 * pwm6ch.h
 *
 * Created: 6/4/2015 8:29:08 AM
 *  Author: admin
 */ 


#ifndef PWM6CH_H_
#define PWM6CH_H_

//pwm PHASE CORRECT timer 0
//OC0B -- PD5
//OC0A -- PD6
#define clk_timer0_stop			0
#define clk_timer0_div1			1
#define clk_timer0_div8			2
#define clk_timer0_div64		3
#define clk_timer0_div256		4
#define clk_timer0_div1024		5
#define clk_timer0_divt0_fall	6
#define clk_timer0_divt0_rise	7


void pwm_phasecorrect_timer0_initial(unsigned char clk);
void pwm_phasecorrect_timer0_OCR0A_updata(unsigned char	val);
void pwm_phasecorrect_timer0_OCR0B_updata(unsigned char val);


//pwm PHASE CORRECT timer 1 (8bit)
//OC1B -- PB2
//OC1A -- PB1
#define clk_timer1_stop			0
#define clk_timer1_div1			1
#define clk_timer1_div8			2
#define clk_timer1_div64		3
#define clk_timer1_div256		4
#define clk_timer1_div1024		5
#define clk_timer1_divt1_fall	6
#define clk_timer1_divt1_rise	7

//option
#define pwm_8bits	(0<<WGM11)|(1<<WGM10)		
#define pwm_9bits	(1<<WGM11)|(0<<WGM10)		
#define pwm_10bits	(1<<WGM11)|(1<<WGM10)		
//api
void pwm_phasecorrect_timer1_initial(unsigned char clk);//8bits default
void pwm_phasecorrect_timer1_option_initial(unsigned char clk,unsigned char nbits);//8bit,9bit,10bit
void pwm_phasecorrect_timer1_OCR1A_updata(unsigned int	val);
void pwm_phasecorrect_timer1_OCR1B_updata(unsigned int val);


//pwm_servo control two channel at PB2, PB1
void pwm_servo_timer1_initial(void);
void pwm_servo_timer1_OCR1A_updata(unsigned int val);
void pwm_servo_timer1_OCR1B_updata(unsigned int val);



void pwm_phasecorrect_4ch_updata(unsigned char ch1,unsigned char ch2,unsigned char ch3,unsigned char ch4);
void pwm_servo_2ch_updata(unsigned int ch1,unsigned int ch2);

//pwm PHASE CORRECT timer 2 (8bit)
//OC2B -- PD3
//OC2A -- PB3
#define clk_timer2_stop			0
#define clk_timer2_div1			1
#define clk_timer2_div8			2
#define clk_timer2_div32		3
#define clk_timer2_div64		4
#define clk_timer2_div128		5
#define clk_timer2_div256		6
#define clk_timer2_div1024 		7

void pwm_phasecorrect_timer2_initial(unsigned char clk);
void pwm_phasecorrect_timer2_OCR2A_updata(unsigned char	val);
void pwm_phasecorrect_timer2_OCR2B_updata(unsigned char val);
void pwm_phasecorrect_6ch_updata(unsigned char ch1,unsigned char ch2,unsigned char ch3,unsigned char ch4,unsigned char ch5,unsigned char ch6);


#endif /* PWM6CH_H_ */