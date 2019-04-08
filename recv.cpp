	#include <iostream>
	// RF24.h is hadder file in RF24 library
	#include <RF24/RF24.h>   
	//NRF24L01 is a hadder file in RF24 library 
	#include "RF24/nRF24L01.h"
	#include <stdio.h>
#include<string.h>

	using namespace std;

	//calling external functions of valve(CO valve), uart(function) and LCD. 
	extern void valve_off_function();
//	extern void valve_on_function();
	extern void gsm_function();
	extern void lcd_init();
	extern void lcdLoc(int);
	extern void ClrLcd(void);
	extern void typeln(const char *);
        char device[15]="\0";
	//this is define the line and characters used in display (lcd).
	void line_lcd(char line,char *str)
	{
	lcdLoc(line);
	typeln("               ");
	lcdLoc(line);
	typeln(str);
	}

	// we define value and limit integers for Radio Frequecy module (transreciver) 
	int val,lim;

	/* RF24 GPIO information with speed setup of 8MHZ same as set in Arduino #1 and Arduino #2 */
	RF24 radio(RPI_V2_GPIO_P1_22,RPI_V2_GPIO_P1_24,BCM2835_SPI_SPEED_8MHZ);
	const uint8_t data_pipe[6] = "00001";

	// this is radio setup which is basically same as arduino
	void setup()
	{
	radio.begin();
	radio.setRetries(15,15);
	radio.setPALevel(RF24_PA_MAX);
	radio.openReadingPipe(1,data_pipe);
	radio.startListening();
	}	

	int main ()
	{

	char ard[8];
	char str[16];
	
      // digitalWrite(0, LOW);
	
	setup();
        lcd_init();	
	//printing message I am here to show that RF module is working and wait for 
	//getting response from other side (Arduino's NRF24L01)
	cout<<"i am here\n";
	while(true)
	{
	//if the statement is working then program will run if condition otherwise not.

	if(radio.available())
	{
	int ps = radio.getDynamicPayloadSize();
	if(ps > 0)
	{
	//cout<<"value of ps:"<<ps<<endl;
	char* p = new char[ps+1];
	radio.read(p,ps);
	p[ps] = '\0';
	cout<<"CO value : "<<p<<endl;
	sscanf(p,"%s = %d:%d",&ard,&val,&lim);
	sprintf(str,"co value:%d",val);
	line_lcd(0x80,ard);
	line_lcd(0xC0,str);
	
	//its printing arduino number, value and limit of CO gas on LCD
	printf("%s %d %d\n",ard,val,lim);

	//IF conditon apply in this program to set the co limit which we can change any time
	//in which we call GSM function which send message to user 
	//we print values on LCD 
	//we also call valve off function which turf off the valve to stop the gas from furnace. 
	if(val > 110)
	{ 
	strcpy(device,ard);
	gsm_function();
	printf ("  CO LEVEL is Dangerous now..\n");
	printf ("arduino num:%s\n",ard);
//	valve_off_function();
	}
          if(val > 180)
	{
//	gsm_function();
//	printf (" CO LEVEL is Dangerous now valve is shutt down..\n");
//	printf ("arduino num:%s\n",ard);	
	valve_off_function();	
	}
/*	if(val < 180)
	{
	valve_on_function();
	}
*/	}
	}
	}
	return 0;
	}


