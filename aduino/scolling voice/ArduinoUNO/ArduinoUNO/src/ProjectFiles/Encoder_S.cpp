/*
 * Encoder_S.cpp
 *
 * Created: 9/11/2015 1:13:53 PM
 *  Author: RnD
 */ 
#include <Encoder_S.h>
//#define show
#define ledPin 13

volatile int timer1_counter;
volatile Encoder encoder;

volatile boolean starting;

void Encoder_S_initial(uint16_t _hz)
{
	pinMode(sensor1,INPUT);
	pinMode(sensor2,INPUT);
	pinMode(led,OUTPUT);
	
	PCICR |= 1<<PCIE1;
	PCMSK1 |= 1<<PCINT8|1<<PCINT9;
	noInterrupts();           // disable all interrupts
	TCCR1A = 0;
	TCCR1B = 0;
	// Set timer1_counter to the correct value for our interrupt interval
	//timer1_counter = 64886;   // preload timer 65536-16MHz/256/100Hz
	//timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
	// preload timer 65536-16MHz/256/2Hz
	encoder.timer_counter =(uint16_t)(65536-(62500/_hz));
	TCNT1 = encoder.timer_counter;   // preload timer
	TCCR1B |= (1 << CS12);    // 256 prescaler
	TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
	interrupts();             // enable all interrupts
	encoder._frame_num = -1;
	encoder._last_frame = 1;
	starting = true;
	encoder.new_frame_event = true;
}
int8_t Encoder_S_get_num(void)
{
	encoder.new_frame_event = false;
	encoder._last_frame = encoder._frame_num;
	return encoder._frame_num;
}

boolean Encoder_S_get(void)
{
	return encoder.new_frame_event;
}

	ISR(TIMER1_OVF_vect)        // interrupt service routiness
	{
		TCNT1 = encoder.timer_counter;   // preload timer
		
		if (encoder.timming<50000) encoder.timming++;
		
		if (encoder._counter_enable==true)
		{
			//stopping detect
			if (encoder.counter>=250) 
			{
				encoder._counter_enable=false;		// turn off counter
				
				if (((encoder._counter_R>=2)&&(encoder._counter_R<=7))||(((encoder._counter_L>=2)&&(encoder._counter_L<=7))))
				{
						if ((encoder._dir==true)&&(encoder._last_dir==true)) // up
						{
							encoder._frame_num ++;
						}
						else if ((encoder._dir==false)&&(encoder._last_dir==false)) //down
						{
							encoder._frame_num--;
						}
						else if ((encoder._dir==false)&&(encoder._last_dir==true))  // paper 5 to go
						{
							encoder._frame_num=5;
						}
						else	//paper 2 to go
						{
							encoder._frame_num=2;
						}
				}
				else if (encoder._counter_R<2) encoder._frame_num = 6;
				else if (encoder._counter_L<2) encoder._frame_num = 1;
				
				else encoder._frame_num = -1;
				if((encoder._frame_num<1)||(encoder._frame_num>6)) encoder._frame_num = -1;
				if (starting==true)
				{
					if((encoder._frame_num==1)||(encoder._frame_num==6)) starting = false;
					else
					{
						encoder._frame_num = -1;
					}
				}
				encoder._counter_L = 0;					//  reset counter
				encoder._counter_R = 0;					//	reset counter
				if(encoder._last_frame!=encoder._frame_num) encoder.new_frame_event=true;  //  new frame event trigger
				encoder._last_dir = encoder._dir;		//saving  current dir
			}
			else  encoder.counter++;
		}
	//	digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
	}
	
	ISR(PCINT1_vect)
	{
		if (digitalRead(sensor1)==HIGH) encoder._sensor_1=true;
		else encoder._sensor_1 = false;
		if (digitalRead(sensor2)==HIGH) encoder._sensor_2=true;
		else encoder._sensor_2 = false;
			if ((encoder._sensor_1==true) && (encoder._sensor_2==true))
			{
				encoder._and_sensor = true;
			}
			else if ((encoder._sensor_1==false) && (encoder._sensor_2==true))
			{
				encoder._counter_enable=false;
				if ((encoder.counter>=25)&&(encoder.counter<150)&&(encoder._and_sensor==true))
				{
					encoder.speed = encoder.counter;
					 encoder._dir = true;
					 encoder._counter_L++;
					 encoder._counter_R = 0;
#ifdef show
Serial.print("LEFT\t");
Serial.print(encoder.speed);
Serial.print("\n\r");
#endif
				}
				encoder._and_sensor = false;
			}
			else if ((encoder._sensor_1==true) && (encoder._sensor_2==false))
			{
					encoder._counter_enable=false;
					if ((encoder.counter>=25)&&(encoder.counter<150)&&(encoder._and_sensor==true)) 
					{
						encoder.speed = encoder.counter;
						encoder._dir = false;
						 encoder._counter_R++;
						 encoder._counter_L = 0;
#ifdef show
Serial.print("RIGHT\t");
Serial.print(encoder.speed);
Serial.print("\n\r");
#endif
					}
					
					encoder._and_sensor = false;
			}
			else
			{
#ifdef show
Serial.print("KIEM TRA CAM BIEN AH175, LOI VI TRI HOAC DA TU VONG!");
#endif
			}
			
			encoder._counter_enable=true;
			encoder.counter =0;
	}
	