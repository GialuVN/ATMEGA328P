//*******************************************************
//   ***  I2C_ROUTINES HEADER FILE ******** 		
//*******************************************************
//Controller: ATmega32 (Clock: 8 Mhz-internal)
//Compiler	: AVR-GCC (winAVR with AVRStudio)
//Project V.: Version - 2.4.1
//Author	: CC Dharmani, Chennai (India)
//			  www.dharmanitech.com
//Date		: 24 Apr 2011
//*******************************************************

#ifndef _I2C_ROUTINES_H_
#define _I2C_ROUTINES_H_


#define	 START				0x08
#define  REPEAT_START		0x10
#define  MT_SLA_ACK			0x18
#define  MT_SLA_NACK		0x20
#define  MT_DATA_ACK		0x28
#define  MT_DATA_NACK		0x30
#define  MR_SLA_ACK			0x40
#define  MR_SLA_NACK		0x48
#define  MR_DATA_ACK		0x50
#define  MR_DATA_NACK		0x58
#define  ARB_LOST			0x38

#define  ERROR_CODE			0x7e
	
#define  DS1307_W			0xd0
#define  DS1307_R			0xd1
#define  EEPROM_W			0xa0
#define  EEPROM_R			0xa1

void twi_init(void);
unsigned char i2c_start(void);
unsigned char i2c_repeatStart(void);
unsigned char i2c_sendAddress(unsigned char);
unsigned char i2c_sendData(unsigned char);
unsigned char i2c_receiveData_ACK(void);
unsigned char i2c_receiveData_NACK(void);
void i2c_stop(void);


#endif
	
