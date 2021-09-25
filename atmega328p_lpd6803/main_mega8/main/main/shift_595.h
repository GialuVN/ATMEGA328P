/*
 * shift_595.h
 *
 * Created: 31/08/2013 8:22:46 AM
 *  Author: THIET KE 3
 */ 


#ifndef SHIFT_595_H_
#define SHIFT_595_H_
#include <inttypes.h>

#define CK_PIN PD1		//CLOCK out
#define CK_POR PORTD
#define CK_DDR DDRD

#define DT_PIN PD0		//DATA out
#define DT_POR PORTD
#define DT_DDR DDRD

#define LA_PIN PD2		//LATCH
#define LA_POR PORTD
#define LA_DDR DDRD


void shift_config_pin();
void shift_byte(uint8_t value);
void shift_latch();

#endif /* SHIFT_595_H_ */

#ifndef LSB_FIRST
#define LSB_FIRST
#endif 