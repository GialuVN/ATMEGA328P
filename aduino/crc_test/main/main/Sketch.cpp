/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <util/crc16.h>

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
void setup();
void loop();
//End of Auto generated function prototypes by Atmel Studio
/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

// the setup function runs once when you press reset or power the board


uint8_t temp[16];
uint8_t _crc;

void setup() {
  // initialize digital pin 13 as an output.
  Serial.begin(9600);
  
 // pinMode(13, OUTPUT);
 
 for (uint8_t i = 0;i<15;i++) temp[i] = i+100;
 _crc = 0;
 
 for (uint8_t i = 0;i<15;i++) _crc = _crc_ibutton_update(_crc,temp[i]);
 
 temp[15] = _crc;
 
 Serial.print("CRC:  ");
 Serial.print(_crc);
 
 _crc = 0;
 for (uint8_t i = 0;i<16;i++) _crc = _crc_ibutton_update(_crc,temp[i]);
 
 Serial.print("rec CRC:  ");
 Serial.print(_crc);
 
}

// the loop function runs over and over again forever
void loop() {
	
	
//	Serial.print(10);
 // digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
 // digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
 // delay(1000);              // wait for a second
}
