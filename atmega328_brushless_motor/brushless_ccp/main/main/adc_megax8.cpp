/*
 * adc_megax8.c
 *
 * Created: 6/8/2015 10:07:54 AM
 *  Author: admin
 */ 

#include "adc_megax8.h"
volatile ADC_DATA adc_data;
volatile ADC_CTR adc_ctr;

void ADC_initial(unsigned char mask,unsigned char div,unsigned char ref)
{
	if (mask==0) return;
		adc_ctr.adc_sequence = 0;
		adc_ctr.adc_ref = ref;
		adc_ctr.adc_mask = mask; //save mask
		DIDR0 = mask;			 //digital disable
		ADCSRA = div;			// division factor
}

void ADC_start(void)
{
	if (adc_ctr.adc_mask==0) return;
	while(adc_ctr.adc_sequence<8)
	{
		if (adc_ctr.adc_mask&(1<<adc_ctr.adc_sequence))
		{
			ADMUX =(adc_ctr.adc_ref<<REFS0)|(adc_ctr.adc_sequence);		//ref config and MUX sequence
			ADCSRA |= (1<<ADIE)|(1<<ADIF)|(1<<ADEN)|(1<<ADSC);	//adc interrupt enable and adc enable and start						
			adc_ctr.adc_sequence++;
			return;
		}
		adc_ctr.adc_sequence++;
	}
	adc_ctr.adc_sequence=0;
	ADC_start();
}


void ADC_stop(void)
{
	while(!(ADCSRA&(1<<ADIF))){};
	ADCSRA &= ~((1<<ADEN)|(1<<ADSC))|(1<<ADIE);//adc disable and stop and adc interrupt disable
}

unsigned int ADC_read(unsigned char mux)
{
	switch (mux)
	{
		case 0:
		return adc_data.adc0_val;
		case 1:
		return adc_data.adc1_val;
		case 2:
		return adc_data.adc2_val;
		case 3:
		return adc_data.adc3_val;
		case 4:
		return adc_data.adc4_val;
		case 5:
		return adc_data.adc5_val;
		case 6:
		return adc_data.adc6_val;
		case 7:
		return adc_data.adc7_val;
		default:
		return 0;
	}
	return 0;
}

ISR(ADC_vect)
{
	switch (adc_ctr.adc_sequence-1)
	{
		case 0:
		adc_data.adc0_val = ADCL;
		adc_data.adc0_val|=(unsigned int)(ADCH<<8);
		ADC_start();
		break;
		
		case 1:
		adc_data.adc1_val = ADCL;
		adc_data.adc1_val|=(unsigned int)(ADCH<<8);
		ADC_start();
		break;
		case 2:
		adc_data.adc2_val = ADCL;
		adc_data.adc2_val|=(unsigned int)(ADCH<<8);
		ADC_start();
		break;
		case 3:
		adc_data.adc3_val = ADCL;
		adc_data.adc3_val|=(unsigned int)(ADCH<<8);
		ADC_start();
		break;
		case 4:
		adc_data.adc4_val = ADCL;
		adc_data.adc4_val|=(unsigned int)(ADCH<<8);
		ADC_start();
		break;
		case 5:
		adc_data.adc5_val = ADCL;
		adc_data.adc5_val|=(unsigned int)(ADCH<<8);
		ADC_start();
		break;
		case 6:
		adc_data.adc6_val = ADCL;
		adc_data.adc6_val|=(unsigned int)(ADCH<<8);
		ADC_start();
		break;
		case 7:
		adc_data.adc7_val = ADCL;
		adc_data.adc7_val|=(unsigned int)(ADCH<<8);
		ADC_start();
		break;
		default:
		break;
	}
	
}
