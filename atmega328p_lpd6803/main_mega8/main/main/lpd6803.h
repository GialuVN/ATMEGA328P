/*
 * lpd6803.h
 *
 * Created: 24/09/2013 7:23:59 AM
 *  Author: THIET KE 3
 */ 


#ifndef LPD6803_H_
#define LPD6803_H_

#define CK_PIN PC2		//CLOCK out
#define CK_POR PORTC
#define CK_DDR DDRC

#define DT_PIN PC3		//DATA out
#define DT_POR PORTC
#define DT_DDR DDRC

#define max_gray 31

void shift_config_pin();
void lpd6803_start_farme();
void lpd_6803_npulse(uint16_t npulse);
void lpd6803_config_pin();
void lpd6803_rgb(uint8_t red,uint8_t green,uint8_t blue);


#endif /* LPD6803_H_ */