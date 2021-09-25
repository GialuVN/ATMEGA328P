/*
 * hc595.h
 *
 * Created: 23/05/2013 3:54:11 PM
 *  Author: THIET KE 3
 */ 


#ifndef HC595_H_
#define HC595_H_
#include <inttypes.h>
#define SPI_FUNC 0
#define MSB_FIRST

#if (SPI_FUNC==0)

#define CK_PIN PINC1		//CLOCK out
#define CK_POR PORTC
#define CK_DDR DDRC

#define DT_PIN PINC0		//DATA out
#define DT_POR PORTC
#define DT_DDR DDRC

#define LA_PIN PINC2		//LATCH
#define LA_POR PORTC
#define LA_DDR DDRC

#endif

void hc595_set_spi();
void hc595_byte_transmit(uint8_t x);
void hc595_latch();

#endif /* HC595_H_ */