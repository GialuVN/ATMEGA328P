//*************************************************************
//*** FUNCTIONS FOR EEPROM READ/WRITE ON I2C COMMUNICATION  ***
//*************************************************************
//Controller: ATmega32 (Clock: 8 Mhz-internal)
//Compiler	: AVR-GCC (winAVR with AVRStudio)
//Project V.: Version - 2.4.1
//Author	: CC Dharmani, Chennai (India)
//			  www.dharmanitech.com
//Date		: 24 Apr 2011
//********************************************************

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "rtc_routines.h"
#include "UART_routines.h"
#include "i2c_routines.h"

unsigned char time[10]; 		//xxam:xx:xx;
unsigned char date[12];		//xx/xx/xxxx;
unsigned char day;

//***************************************************************************
//Function to set initial address of the RTC for subsequent reading / writing
//***************************************************************************
unsigned char RTC_setStartAddress(void)
{
   unsigned char errorStatus;
   
   errorStatus = i2c_start();
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC start1 failed.."));
   	 i2c_stop();
	 return 1;
   } 
   
   errorStatus = i2c_sendAddress(DS1307_W);
   
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC sendAddress1 failed.."));
	 i2c_stop();
	 return 1;
   } 
   
   errorStatus = i2c_sendData(0x00);
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC write-2 failed.."));
	 i2c_stop();
	 return 1;
   } 

   i2c_stop();
   return 0;
}

//***********************************************************************
//Function to read RTC registers and store them in buffer rtc_register[]
//***********************************************************************    
unsigned char RTC_read(void)
{

  unsigned char errorStatus, i, data;
  
  errorStatus = i2c_start();
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC start1 failed.."));
   	 i2c_stop();
	 return 1;
   } 
   
   errorStatus = i2c_sendAddress(DS1307_W);
   
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC sendAddress1 failed.."));
	 i2c_stop();
	 return 1;
   } 
   
   errorStatus = i2c_sendData(0x00);
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC write-1 failed.."));
	 i2c_stop();
	 return 1;
   } 

    errorStatus = i2c_repeatStart();
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC repeat start failed.."));
   	 i2c_stop();
	 return 1;
   } 
   
    errorStatus = i2c_sendAddress(DS1307_R);
   
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC sendAddress2 failed.."));
	 i2c_stop();
	 return 1;
   } 
 
    for(i=0;i<7;i++)
   {
      if(i == 6)  	 //no Acknowledge after receiving the last byte
	   	  data = i2c_receiveData_NACK();
	  else
	  	  data = i2c_receiveData_ACK();
		  
   	  if(data == ERROR_CODE)
   	  {
       		//transmitString_F(PSTR("RTC receive failed.."));
			i2c_stop();
	   		return 1;
   	  }
	  
	  rtc_register[i] = data;
	}
	
	i2c_stop();
	return 0;
}	  

//******************************************************************
//Function to form time string for sending it to LCD & UART
//****************************************************************** 
unsigned char RTC_getTime(void)
{
   unsigned char error;
   error = RTC_read();
   if(error) return 1;

   RTC_read();
   time[8] = 0x00;	  //NIL
   time[7] = (SECONDS & 0x0f) | 0x30;		 //seconds(1's)
   time[6] = ((SECONDS & 0x70) >> 4) | 0x30; //seconds(10's)
   time[5] = ':';
   
   time[4] = (MINUTES & 0x0f) | 0x30;
   time[3] = ((MINUTES & 0x70) >> 4) | 0x30;
   time[2] = ':'; 
   
   time[1] = (HOURS & 0x0f) | 0x30;	
   time[0] = ((HOURS & 0x30) >> 4) | 0x30;

   return 0;
}

//******************************************************************
//Function to form date string for sending it to LCD & UART
//****************************************************************** 
unsigned char RTC_getDate(void)
{
  unsigned char error;
  error = RTC_read();
  if(error) return 1;

  date[11] = 0x00;
  date[10] = 0x00;
  date[9] = (YEAR & 0x0f) | 0x30;
  date[8] = ((YEAR & 0xf0) >> 4) | 0x30;
  date[7] = '0';
  date[6] = '2';
  date[5] = '/';
  date[4] = (MONTH & 0x0f) | 0x30;
  date[3] = ((MONTH & 0x10) >> 4) | 0x30;
  date[2] = '/';
  date[1] = (DATE & 0x0f) | 0x30;
  date[0] = ((DATE & 0x30) >> 4) | 0x30;
  return 0;
}  
  
//******************************************************************
//Function to display time on LCD and send it to PC (thru UART)
//****************************************************************** 
unsigned char RTC_displayTime(void)
{
  unsigned char error;
  error = RTC_getTime();
  if(error) return 1;
  
  TX_NEWLINE;
  transmitString_F(PSTR("Time:"));
  transmitString(time);

  return 0;
}

//******************************************************************
//Function to display date on LCD and send it to PC (UART)
//****************************************************************** 
unsigned char RTC_displayDate(void)
{
  unsigned char error;
  error = RTC_getDate();
  if(error) return 1;
  
  TX_NEWLINE;
  transmitString_F(PSTR("Date:")); 
  transmitString(date);  
  RTC_displayDay();  
  
  return 0; 
}

//******************************************************************
//Function to get the string for day 
//****************************************************************** 
void RTC_displayDay(void)
{
  transmitString_F(PSTR("    Day: "));
  
  switch(DAY)
  {
   case 0:transmitString_F(PSTR("Sunday"));
          break; 
   case 1:transmitString_F(PSTR("Monday"));
          break; 
   case 2:transmitString_F(PSTR("Tuesday"));
          break; 
   case 3:transmitString_F(PSTR("Wednesday"));
          break; 
   case 4:transmitString_F(PSTR("Thursday"));
          break; 		  
   case 5:transmitString_F(PSTR("Friday"));
          break; 		  
   case 6:transmitString_F(PSTR("Saturday"));
          break; 
   default:	transmitString_F(PSTR("Unknown"));  
  }
}	  		  
		  		     	  
//******************************************************************
//Function to update buffer rtc_register[] for next writing to RTC
//****************************************************************** 
void RTC_updateRegisters(void)
{
  SECONDS = ((time[6] & 0x07) << 4) | (time[7] & 0x0f);
  MINUTES = ((time[3] & 0x07) << 4) | (time[4] & 0x0f);
  HOURS = ((time[0] & 0x03) << 4) | (time[1] & 0x0f);  
  DAY = date[10];
  DATE = ((date[0] & 0x03) << 4) | (date[1] & 0x0f);
  MONTH = ((date[3] & 0x01) << 4) | (date[4] & 0x0f);
  YEAR = ((date[8] & 0x0f) << 4) | (date[9] & 0x0f);
}  


//******************************************************************
//Function to write new time in the RTC 
//******************************************************************   
unsigned char RTC_writeTime(void)
{
  unsigned char errorStatus, i;
  
   errorStatus = i2c_start();
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC start1 failed.."));
   	 i2c_stop();
	 return(1);
   } 
   
   errorStatus = i2c_sendAddress(DS1307_W);
   
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC sendAddress1 failed.."));
	 i2c_stop();
	 return(1);
   } 
   
   errorStatus = i2c_sendData(0x00);
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC write-1 failed.."));
	 i2c_stop();
	 return(1);
   } 

    for(i=0;i<3;i++)
    {
	  errorStatus = i2c_sendData(rtc_register[i]);  
   	  if(errorStatus == 1)
   	  {
       		//transmitString_F(PSTR("RTC write time failed.."));
			i2c_stop();
	   		return(1);
   	  }
    }
	
	i2c_stop();
	return(0);
}


//******************************************************************
//Function to write new date in the RTC
//******************************************************************   
unsigned char RTC_writeDate(void)
{
  unsigned char errorStatus, i;
  
   errorStatus = i2c_start();
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC start1 failed.."));
   	 i2c_stop();
	 return(1);
   } 
   
   errorStatus = i2c_sendAddress(DS1307_W);
   
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC sendAddress1 failed.."));
	 i2c_stop();
	 return(1);
   } 
   
   errorStatus = i2c_sendData(0x03);
   if(errorStatus == 1)
   {
     //transmitString_F(PSTR("RTC write-1 failed.."));
	 i2c_stop();
	 return(1);
   } 

    for(i=3;i<7;i++)
    {
	  errorStatus = i2c_sendData(rtc_register[i]);  
   	  if(errorStatus == 1)
   	  {
       		//transmitString_F(PSTR("RTC write date failed.."));
			i2c_stop();
	   		return(1);
   	  }
    }
	
	i2c_stop();
	return(0);
}
  
//******************************************************************
//Function to update RTC time by entering it at hyper terminal
//******************************************************************   
unsigned char RTC_updateTime(void)
{
  unsigned char data;
  TX_NEWLINE;
  transmitString_F(PSTR("Enter Time in 24h format(hh:mm:ss):")); 
  
    data = receiveByte(); 	   	  	  				//receive hours
	transmitByte(data);
	if(data < 0x30 || data > 0x32)
	   goto TIME_ERROR;
	   
	time[0]= data;
	 
	data = receiveByte();
	transmitByte(data);
	if(data < 0x30 || data > 0x39)
	   goto TIME_ERROR;
	 
	time[1]= data;
	
	transmitByte(':');
	
	if(((time[1] & 0x0f) + ((time[0] & 0x03)*10)) > 23)
	   goto TIME_ERROR;
	 
	 data = receiveByte();			   			  //receive minutes
	 transmitByte(data);
	if(data < 0x30 || data > 0x35)
	   goto TIME_ERROR;
	   
	time[3]= data; 
	
	data = receiveByte();
	transmitByte(data);
	if(data < 0x30 || data > 0x39)
	   goto TIME_ERROR;
	   
	time[4]= data; 
	
	transmitByte(':');
	
	 data = receiveByte();			   			  //receive seconds
	 transmitByte(data);
	if(data < 0x30 || data > 0x35)
	   goto TIME_ERROR;
	   
	time[6]= data; 
	
	data = receiveByte();
	transmitByte(data);
	if(data < 0x30 || data > 0x39)
	   goto TIME_ERROR;
	   
	time[7]= data; 
	
	 	  
  RTC_updateRegisters(); 
  data = RTC_writeTime();

  TX_NEWLINE;
  if(data == 0)
  {     
  	 transmitString_F(PSTR("Time Updated sucessfully!")); 
	 return 0;
  }	
  else 
  { 
     transmitString_F(PSTR("Time Update Failed.."));
	 return 1;
  }
TIME_ERROR:

  TX_NEWLINE;
  transmitString_F(PSTR("Invalid Entry..")); 
  return 1;
}  
  
  
//******************************************************************
//Function to update RTC date by entering it at hyper terminal
//******************************************************************   
unsigned char RTC_updateDate(void)
{
  unsigned char data;
  TX_NEWLINE;
  transmitString_F(PSTR("Enter Date (dd/mm/yy):")); 
  
    data = receiveByte(); 	   				  		//receive date
	transmitByte(data); 	   	  	  				
	if(data < 0x30 || data > 0x33)
	   goto DATE_ERROR;
	   
	date[0]= data;
	 
	data = receiveByte();
	transmitByte(data);
	if(data < 0x30 || data > 0x39)
	   goto DATE_ERROR;
	   
	date[1]= data;
	
	if(((date[1] & 0x0f) + ((date[0] & 0x03)*10)) > 31)
	   goto DATE_ERROR;
    transmitByte('/');
	
	date[2] = '/';
	   
	
	data = receiveByte();			   			  //receive month
	transmitByte(data);
	if(data < 0x30 || data > 0x31)
	  goto DATE_ERROR;
	  
	date[3]= data; 
	
	data = receiveByte();
	transmitByte(data);
	if(data < 0x30 || data > 0x39)
	  goto DATE_ERROR;
	  
	date[4] = data; 
	
	if(((date[4] & 0x0f) + ((date[3] & 0x03)*10)) > 12)
	   goto DATE_ERROR;
	transmitByte('/');
	   
	
	date[5] = '/';
	
	date[6] = '2'; 	   	   	  	  //year is 20xx
	date[7] = '0';
	
	data = receiveByte();			   			 
	transmitByte(data);
	if(data < 0x30 || data > 0x39)
	   goto DATE_ERROR;
	   
	date[8]= data; 
	
	data = receiveByte();
	transmitByte(data);
	if(data < 0x30 || data > 0x39)
	   goto DATE_ERROR;
	   
	date[9]= data; 
	
	TX_NEWLINE;
    transmitString_F(PSTR("Enter Day (Sunday:0, Monday:1...) (0-6):")); 
	
	data = receiveByte();				   //receive Day of the week
	transmitByte(data);
	if(data < 0x30 || data > 0x36)
	   goto DATE_ERROR;
	   
	date[10] = data & 0x0f;
		 	  
  RTC_updateRegisters(); 
  data = RTC_writeDate();

  TX_NEWLINE;
  if(data == 0)
  {
     
  	 transmitString_F(PSTR("Date Updated sucessfully!")); 
	 return 0;
  }	  
  else
  {
     transmitString_F(PSTR("Date Update Failed.."));
     return 1;
  }

  DATE_ERROR:

  TX_NEWLINE;
  transmitString_F(PSTR("Invalid Entry..")); 
  return 1;
}  



//******************************************************************
//Function to get RTC date & time in FAT32 format
//******************************************************************   
unsigned char getDateTime_FAT(void)
{
  
   unsigned char mth, dt, hr, min, sec, error; 
   unsigned int yr;

   error = RTC_read();
   if(error) return 1;

   yr = (YEAR & 0xf0) >> 4;
   yr = (yr * 10)+(YEAR & 0x0f);
   yr = yr+2000;
   yr = yr - 1980;

   dateFAT = yr;

   mth = (MONTH & 0xf0) >> 4;
   mth = (mth * 10)+(MONTH & 0x0f);

   dateFAT = (dateFAT << 4) | mth;

   dt = (DATE & 0xf0) >> 4;
   dt = (dt * 10)+(DATE & 0x0f);

   dateFAT = (dateFAT << 5) | dt;


   hr = (HOURS & 0xf0) >> 4;
   hr = (hr * 10)+(HOURS & 0x0f);

   timeFAT = hr;

   min = (MINUTES & 0xf0) >> 4;
   min = (min * 10)+(MINUTES & 0x0f);

   timeFAT = (timeFAT << 6) | min;

   sec = (SECONDS & 0xf0) >> 4;
   sec = (sec * 10)+(SECONDS & 0x0f);
   sec = sec / 2;    //FAT32 fromat accepts dates with 2sec resolution (e.g. value 5 => 10sec)

   timeFAT = (timeFAT << 5) | sec;

   
   return 0;
}
	  
 
 

 
