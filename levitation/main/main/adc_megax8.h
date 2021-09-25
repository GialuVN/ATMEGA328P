/*
 * adc_megax8.h
 *
 * Created: 6/8/2015 10:08:03 AM
 *  Author: admin
 */ 


#ifndef ADC_MEGAX8_H_
#define ADC_MEGAX8_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//adc REF selection

#define ADC_REF_AREF	0
#define ADC_REF_VCC		1
#define	ADC_REF_1V1		3

//adc MUX selcetion
#define ADC0		0
#define ADC1		1
#define ADC2		2
#define ADC3		3
#define ADC4		4
#define ADC5		5
#define ADC6		6
#define ADC7		7
#define ADC8		8//*
#define ADC_1v1		14
#define ADC_GND		15

//adc prescale selection
#define ADC_div2	0
#define ADC_div4	2
#define ADC_div8	3
#define ADC_div16	4
#define ADC_div32	5
#define ADC_div64	6
#define ADC_div128	7
//
////adc trigger source selection
//
//#define ADC_trigger_freerun		0
//#define ADC_trigger_analogcom   1
//#define ADC_trigger_exti0		2
//#define ADC_trigger_tccomA		3
//#define ADC_trigger_tcov0		4
//#define ADC_trigger_tccomB		5
//#define ADC_trigger_tcov1		6
//#define ADC_trigger_tccap		7


typedef struct ADC_DATA	// ADC RESULT
{
	unsigned int adc0_val;
	unsigned int adc1_val;
	unsigned int adc2_val;
	unsigned int adc3_val;
	unsigned int adc4_val;
	unsigned int adc5_val;
	unsigned int adc6_val;
	unsigned int adc7_val;
}ADC_DATA;


typedef struct ADC_CTR	// ADC CTR
{
	unsigned char adc_ref;
	unsigned char adc_stage;
	unsigned char adc_sequence;
	unsigned char adc_mask;
}ADC_CTR;

void ADC_initial(unsigned char mask,unsigned char div,unsigned char ref);
void ADC_start(void);
unsigned int ADC_read(unsigned char mux);
void ADC_stop(void);

#endif /* ADC_MEGAX8_H_ */