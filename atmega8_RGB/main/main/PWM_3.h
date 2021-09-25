/*
 * PWM_3.h
 *
 * Created: 10/9/2015 3:21:35 PM
 *  Author: RnD
 */ 


#ifndef PWM_3_H_
#define PWM_3_H_

#include <stdint.h>
#include <avr/io.h>

#define TIMER_CLK_STOP			0x00	///< Timer Stopped
#define TIMER_CLK_DIV1			0x01	///< Timer clocked at F_CPU
#define TIMER_CLK_DIV8			0x02	///< Timer clocked at F_CPU/8
#define TIMER_CLK_DIV64			0x03	///< Timer clocked at F_CPU/64
#define TIMER_CLK_DIV256		0x04	///< Timer clocked at F_CPU/256
#define TIMER_CLK_DIV1024		0x05	///< Timer clocked at F_CPU/1024
#define TIMER_CLK_T_FALL		0x06	///< Timer clocked at T falling edge
#define TIMER_CLK_T_RISE		0x07	///< Timer clocked at T rising edge
#define TIMER_PRESCALE_MASK		0x07	///< Timer Prescaler Bit-Mask



void timer1SetPrescaler(uint8_t prescale);		///< set timer1 prescaler
void timer2SetPrescaler(uint8_t prescale);		///< set timer2 prescaler

void timer1PWMInit(void);
void timer1PWMInitICR(uint16_t topcount);
void timer1PWMOff(void);
void timer1PWMAOn(void);			///< Turn on timer1 Channel A (OC1A) PWM output.
void timer1PWMBOn(void);			///< Turn on timer1 Channel B (OC1B) PWM output.
void timer1PWMAOff(void);			///< turn off timer1 Channel A (OC1A) PWM output
void timer1PWMBOff(void);			///< turn off timer1 Channel B (OC1B) PWM output
void timer1PWMASet(uint16_t pwmDuty);	///< set duty of timer1 Channel A (OC1A) PWM output
void timer1PWMBSet(uint16_t pwmDuty);	///< set duty of timer1 Channel B (OC1B) PWM output


void timer2PWMInit();
void timer2PWMInitICR();
void timer2PWMSet(uint8_t pwmDuty);
void timer2PWMOff(void);
void timer2PWMOn(void);


/************************************************************************/
/*khoi tao PWM 3 channal
timer1SetPrescaler(TIMER_CLK_DIV8);
timer1PWMInit();
timer1PWMInitICR(255);
timer1PWMBOn();
timer1PWMAOn();
timer2SetPrescaler(TIMER_CLK_DIV8);
timer2PWMInit();
timer2PWMInitICR();
timer2PWMOn();
timer1PWMASet(0);
timer1PWMBSet(0);
timer2PWMSet(0);                                                                     */
/************************************************************************/

#endif /* PWM_3_H_ */