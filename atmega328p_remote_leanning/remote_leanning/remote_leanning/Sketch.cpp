/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <EEPROM.h>
/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
void setup();
void loop();
//End of Auto generated function prototypes by Atmel Studio
/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

typedef struct DATA_INFO
{
	unsigned int	_break;
	unsigned int	_wide_p;
	unsigned int	_narow_p;
	bool			_status;
	
	unsigned char	_data[16];
	unsigned int	_count_bits;
}DATA_INFO;


DATA_INFO temp_x;
DATA_INFO temp_s;
DATA_INFO get_data(DATA_INFO info);


DATA_INFO detector(int repeat);
unsigned int max_is(unsigned int *data,unsigned int len);
unsigned int min_is(unsigned int *data,unsigned int len);
// digital pin 2 has a pushbutton attached to it. Give it a name:
int rf = 2;
int button  = 12;
int led = 13;
bool status = true;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(rf, INPUT);
  pinMode(button,INPUT);
  digitalWrite(button,HIGH);
  
  pinMode(led,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
 
 
 
 
 
 //
 //if (temp_x._status==true)
 //{
	//temp_x = get_data(temp_x); 
//
	//for (unsigned int i = 0; i < ((temp_x._count_bits/8)+1); i++)
	//{
		//Serial.println(temp_x._data[i]);
	//}
	//Serial.println("//");
	//Serial.println(temp_x._break);
	//Serial.println(temp_x._wide_p);
	//Serial.println(temp_x._narow_p);
	//Serial.println("//");
 //}
 //
 
 
 temp_x =temp_s;
 temp_x = get_data(temp_x);
 
 if (temp_x._count_bits == temp_s._count_bits)
 {
	 for (unsigned char i = 0; i < 16; i++)
	 {
		 if (temp_s._data[i]!=temp_x._data[i]) break;
		 
		 else
		 {
			 if (i==15)
			 {
				 
				  if (status)
				  {
					  digitalWrite(led,HIGH);
					  status = false;
				  }
				  else
				  {
					  digitalWrite(led,LOW);
					  status = true;
					 
				  }
				  delay(300);
			 }
		 }
	 }
 }
 
 
 if (!digitalRead(button))
 {
	 if (status)
	 {
		 digitalWrite(led,HIGH);
		 status = false;
	 }
	 else
	 {
		 digitalWrite(led,LOW);
		 status = true;
	 }
	 
	 for (unsigned int	 i = 0;i<1000;i++)
	 {
		 delay(10);
		 if (i>=300)
		 {
			 for (unsigned char j=0;j<5;j++)
			 {
				  delay(200);
				  digitalWrite(led,LOW);
				  delay(200);
				  digitalWrite(led,HIGH);
			 }
			temp_x =  detector(1000);
			
			if (temp_x._status)
			{
				temp_s = get_data(temp_x);
				
				for (unsigned char j=0;j<5;j++)
				{
					delay(100);
					digitalWrite(led,LOW);
					delay(100);
					digitalWrite(led,HIGH);
				}
			}
			
			while (!digitalRead(button)) {};
		 }
		 if (digitalRead(button)) break;
	 }
 }
 delay(1);
}






DATA_INFO get_data(DATA_INFO info)
{
	unsigned int _data[128];
	unsigned int	_temp1;
	unsigned int _temp2;
	unsigned int	_break;
	unsigned int _count;
	if (info._status)
	{
	for (unsigned int i = 0;i<16;i++) info._data[i]=0;
	info._count_bits = 0;
	_break = info._break/2;
	while (1)
	{
		while (digitalRead(rf)){};
		_temp1 = 0;
		while(1)
			{
				_temp1++;
				_delay_us(10);
				if (digitalRead(rf)) break;
				if (_temp1>=_break)
					{
						while (!digitalRead(rf)){};
						for (unsigned int i = 0; i < 128; i+=2)
						{
								for (unsigned int s = 0;s<10000;s++)
								{
									_delay_us(10);
									if (!digitalRead(rf))
									{
										_data[i]=s;
										 break;
									}
								}
								if (_data[i]>=_break) return info;
								
								for (unsigned int s = 0;s<10000;s++)
								{
									_delay_us(10);
									if (digitalRead(rf))
									{
										_data[i+1]=s;
										break;
									}
								}
								if (_data[i+1]>=_break)
								{
									_count = i;
								break;
								}
							}
								if ((_count>10) && (_count<128))
								{
									info._count_bits = _count;
									_temp1 = 0;
									_temp2 = 0;
									while (1)
									{
										
										for (unsigned char k= 0;k<8;k++)
										{
											if ((_data[_temp2]/info._narow_p)<2) info._data[_temp1] &=~(1<<k);
											else info._data[_temp1] |=1<<k;
											if (_temp2 >=_count) return info;
											_temp2++;
										}
										_temp1++;
									}
								}
								else return info;			
				}
			
			}
		
		}
	}
	return info;
}


DATA_INFO detector(int repeat)
{
		DATA_INFO data_info;
		unsigned int	 _break;
		unsigned int	 _narow_p;
		unsigned int	_wide_p;
		unsigned int	temp[16];
		unsigned int	_count1;
		unsigned int	_count2;
		data_info._break = 0;
		data_info._narow_p = 0;
		data_info._status = false;
		data_info._wide_p = 0;
		while (repeat)
		{
		for (unsigned char i = 0;i<16;i++) temp[i] = 0;
		while (digitalRead(rf)){};
		while (!digitalRead(rf)){};
		for (unsigned char i = 0;i<10;i+=2)
		{
				for (unsigned int s = 0;s<10000;s++)
				{
					_delay_us(10);
					if (!digitalRead(rf))
					{
						temp[i]=s;
						break;
					}
				}
				
				for (unsigned int s = 0;s<10000;s++)
				{
					_delay_us(10);
					if (digitalRead(rf))
					{
						temp[i+1]=s;
						break;
					}
				}
		}
		_narow_p = min_is(temp,10);
		 _wide_p = max_is(temp,10);
		_count1 = 0;
		_count2 = 0;
		for (unsigned char i = 0;i<10;i++)
		{
			if ((temp[i]/_narow_p)==1)
			{
				_count1++;
				_count2++;
			}
			else
			{
				if (_count2>=3) break;
				_count2=0;
			}
		}
		if ((_count2<3)&&(_count1==5))
		{
			_count1 = 0;
			_count2 = 0;
			for (unsigned char i = 0;i<10;i++)
			{
				if ((_wide_p/temp[i])==1)
				{
					_count1++;
					_count2++;
				}
				else
				{
					if (_count2>=3) break;
					_count2=0;
				}
			}
			
			if ((_count2<3)&&(_count1==5))
			{
				data_info._break = _wide_p*10;
				data_info._narow_p = _narow_p;
				data_info._wide_p = _wide_p;
				data_info._status = true;
				return data_info;
			}
			
		}
		repeat--;
	}
		
	return data_info;
}

unsigned int max_is(unsigned int *data,unsigned int len)
{
	int k=data[0];
	for (int i = 1;i<len;i++)
	{
		if (data[i]>k) k=data[i];
	}
	return k;
}

unsigned int min_is(unsigned int *data,unsigned int len)
{
	int k=data[0];
	for (int i = 1;i<len;i++)
	{
		if (data[i]<k) k=data[i];
	}
	return k;
}