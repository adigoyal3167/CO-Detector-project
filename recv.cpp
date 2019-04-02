#include <iostream>
#include <RF24/RF24.h>
#include "RF24/nRF24L01.h"
#include <stdio.h>
//#include<wiringPi.h>
//#include "GPIOClass.h"

using namespace std;

//extern int wiringPiSetup();
//extern int wiringPiSetupGpio();
//extern void pinMode(int pin,int mode);
//extern void digitalWrite(int pin,int value);

extern void function();
extern void lcd_init();
extern void lcdLoc(int);
extern void ClrLcd(void);
extern void typeln(const char *);

void line_lcd(char line,char *str)
{
	lcdLoc(line);
	typeln("               ");
	lcdLoc(line);
	typeln(str);
}

int val,lim;

RF24 radio(RPI_V2_GPIO_P1_22,RPI_V2_GPIO_P1_24,BCM2835_SPI_SPEED_8MHZ);
const uint8_t data_pipe[6] = "00001";

void setup()
{
	radio.begin();
	radio.setRetries(15,15);
	radio.setPALevel(RF24_PA_MAX);
	radio.openReadingPipe(1,data_pipe);
	radio.startListening();
}

int main()
{

	char ard[8];
	char str[16];
	setup();
//	wiringPiSetup();
//	wiringPiSetupGpio();
//	pinMode(26,OUTPUT);
//	digitalWrite(26,LOW);
lcd_init();	
cout<<"i am here\n";
	while(true)
	{
//		digitalWrite(26,LOW);

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
		//	strcpy(p,p+11);
			//	printf("%s\n",p);
			//	sscanf(p,"%d:%d",&val,&lim);
				printf("%s %d %d\n",ard,val,lim);
				if(val > 150)
				{ 

			//		digitalWrite(26,HIGH);
					function();
					printf("CO LEVEL > dangerous now..\n");
					printf("arduino num : %s\n",ard);
		//			delay(1000);
				}
			}
		}
	}
}

