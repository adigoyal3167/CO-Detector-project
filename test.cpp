#include <iostream>
#include <RF24/RF24.h>
//#include "/home/pi/lcd/lcd_driver.h"
//#include "nRF24L01.h"
//#include <Sync.h>
//#include <SPI.h>
//extern "C"{
//void lcd_init(void);
//void ClrLcd(void);
//void lcdLoc(int line);
//void typeln(const char *s);
//}

using namespace std;

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
	setup();
	//lcd_init();
cout<<"here\n";
	while(true)
	{

		if(radio.available())
		{
			int ps = radio.getDynamicPayloadSize();
			if(ps > 0)
			{
				char* p = new char[ps+1];
				radio.read(p,ps);
				p[ps] = '\0';
				cout<<"msg : "<<p<<endl;
              			
			  //     	ClrLcd();
			    //line_lcd(LINE1,p);
		//		lcdLoc(0x80);
				//typeln("                ");
			//	lcdLoc(0x80);
			//	typeln(p);	
				sscanf(p,"%d:%d",&val,&lim);
				if(val > 100)
					printf("Hi I am 100 now..\n");
			
			}
		}
	}
}
