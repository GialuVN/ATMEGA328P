/*
 * Encoder_S.h
 *
 * Created: 9/11/2015 1:13:43 PM
 *  Author: RnD
 */ 


#ifndef ENCODER_S_H_
#define ENCODER_S_H_

#include <Arduino.h>

#define sensor1	A0
#define sensor2 A1
#define led		13


typedef struct encoder
{
	uint16_t timer_counter;
	uint16_t counter;
	uint16_t timming;
	boolean _counter_enable;
	boolean _sensor_1;
	boolean _sensor_2;
	int8_t _frame_num;
	int8_t _last_frame;
	boolean new_frame_event;
	
	uint16_t speed;
	boolean _trigger;
	boolean _last_dir;
	boolean _dir;
	boolean _last_state;
	boolean _state;
	boolean _and_sensor;
	uint8_t _counter_L;
	uint8_t _counter_R;
}Encoder;



int8_t Encoder_S_get_num(void);
boolean Encoder_S_get(void);
void Encoder_S_initial(uint16_t _hz);

#endif /* ENCODER_S_H_ */