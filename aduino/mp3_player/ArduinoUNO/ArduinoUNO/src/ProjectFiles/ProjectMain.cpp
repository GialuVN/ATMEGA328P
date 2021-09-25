
/*************************************************** 
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout 
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
// include SPI, MP3 and SD libraries
#include "ProjectMain.h"
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// define the pins used
#define CLK 13       // SPI Clock, shared with SD card
#define MISO 12      // Input data, from VS1053/SD card
#define MOSI 11      // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins. 
// See http://arduino.cc/en/Reference/SPI "Connections"

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  8      // VS1053 reset pin (unused!)
#define SHIELD_CS     6      // VS1053 chip select pin (output)
#define SHIELD_DCS    7      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 9     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 2       // VS1053 Data request, ideally an Interrupt pin

#define sensor1	A0
#define sensor2 A1


boolean PlayNext(void);

 File temp;
 long _position;
int _sensor_val;

Adafruit_VS1053_FilePlayer musicPlayer = 
  // create breakout-example object!
 // Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);
  // create shield-example object!
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
  
  
  
void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit VS1053 music player");

  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
 
  Serial.println(F("VS1053 ready!"));
  
  delay(100); 
  if (!SD.begin(CARDCS)) {
	  Serial.println(F("SD failed, or not present"));
	  while (1);  // don't do anything more
  }
  Serial.println("SD OK!");
  
  
  delay(1000);
 // TAO DANH SACH BAI HAT
   temp = SD.open("/");
   	if (SD.exists(((char*)"LIST.LMT")))
   	{
		Serial.print("XOA FILE LIST.LMT");
   		SD.remove((char*)"LIST.LMT");
   	}
	musicPlayer.acc_reset(100);
	musicPlayer.music_path(temp);
	musicPlayer.acc_close();
    Serial.println("done!");
	_position = 0;

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
  // Play another file in the background, REQUIRES interrupts!
//  musicPlayer.startPlayingFile(musicPlayer.PlayNext().name());
 PlayNext();
}
void loop() {
	
  // File is playing in the background
  if (musicPlayer.stopped()) {
	  PlayNext();
   // musicPlayer.startPlayingFile(musicPlayer.PlayNext().name());
  }
  
  if (Serial.available()) {
    char c = Serial.read();
    
    // if we get an 's' on the serial console, stop!
    if (c == 's') {
      musicPlayer.stopPlaying();
    }
	 if (c == 'n') {
		
			musicPlayer.stopPlaying();
			if (PlayNext()==false)
			{
				Serial.print("\n\r");
				Serial.print("HET NHAC ROI!");
				Serial.print("\n\r");
			}
		//	PlayNext();
		//	 musicPlayer.startPlayingFile(musicPlayer.PlayNext().name());
	 }
    // if we get an 'p' on the serial console, pause/unpause!
    if (c == 'p') {
      if (! musicPlayer.paused()) {
        Serial.println("Paused");
        musicPlayer.pausePlaying(true);
      } else { 
        Serial.println("Resumed");
        musicPlayer.pausePlaying(false);
      }
    }
  }
  
  delay(100);
}








boolean PlayNext(void)
{
	File _temp_file;
	char _path[100];
	boolean _stage=false;
	char _c=0;
	for (uint8_t i = 0; i < sizeof(_path); i++) _path[i]=0;
	_temp_file = SD.open("LIST.LMT",FILE_READ);
	if (_temp_file)
	{
		Serial.print("\n\r");
		Serial.print("LOADING...");
		Serial.print("\n\r");
	} 
	else
	{
			Serial.print("\n\r");
			Serial.print("list.lmt not found!");
			Serial.print("\n\r");
			delay(1000);
			return false;
	}
	
	_temp_file.seek(_position);
	
	while(_temp_file.available())
	{
		_c= _temp_file.read();
		if (_c=='|')
		{	
			_stage = true;
			continue;
		}
		else if ((_c!='|')&& (_stage==true) )
		{
			while (_temp_file.available())
			{
				for (uint8_t i = 0; i < sizeof(_path); i++)
				{
					_path[i]=_c;
					
					_c= _temp_file.read();
					if (_c=='|')
					{
						_position=_temp_file.position();
						_temp_file.close();
						Serial.print("\n\r");
						Serial.print(_path);
						musicPlayer.startPlayingFile(_path);
						return true;
					}
				}
			}
		}
		else _stage = false;
	}
	_temp_file.close();
	_position = 0;
	return	false;
}

