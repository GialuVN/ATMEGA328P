/*
 * hc595.h
 *
 * Created: 23/05/2013 3:54:11 PM
 *  Author: THIET KE 3
 */ 


#ifndef HC595_H_
#define HC595_H_


#define SPI_FUNC 1
#define LSB_FIRST

#if (SPI_FUNC==0)

#define CK_PIN PD1		//CLOCK out
#define CK_POR PORTD
#define CK_DDR DDRD

#define DT_PIN PD0		//DATA out
#define DT_POR PORTD
#define DT_DDR DDRD

#define LA_PIN PD2		//LATCH
#define LA_POR PORTD
#define LA_DDR DDRD

#endif

void hc595_set_spi();
void hc595_byte_transmit(uint8_t x);
void hc595_latch();

#endif /* HC595_H_ */