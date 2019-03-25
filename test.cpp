#include <iostream>
#include "../RF24/RF24.h"
#include "../RF24/nRF24L01.h"
//#include "../RF24/Sync.h"
#include <SPI.h>
using namespace std;

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
			
			}
		}
	}

}
