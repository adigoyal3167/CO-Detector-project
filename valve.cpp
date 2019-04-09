	#include <stdio.h>
	// header file of wiringPi is included to operate GPIO Pins
	#include <wiringPi.h> 

	// valve_on_off function make to call this program from main program
	int valve_on_off_function(void)
	
	//int main is main program to run this program it self
	//int main() 
	{ 
	printf ("Raspberry pi - gertboard blink\n");
	wiringPiSetup ();

	//pinmode 0 is a GPIO 17 number pin for gas valve
	pinMode (0, OUTPUT);
	//pinmode 25 is a GPIO 26 number pin for switch 
	pinMode (25, INPUT);
	//digital write 0 is make the output pin low at first
        digitalWrite(0, LOW);
	{ 
	
	//digital write 0 is make 0 number pin high
	digitalWrite(0, HIGH);

	//for loop is used to loop this function until we press switch to make it reset.
	for (;;)
	//if condition is applied on switch pin 25(GPIO 26)
	if(digitalRead(25) == HIGH)
	{   
	printf("led off");
	// as upper if conditon is applid if switch is pressed than valve would be reset or low
	digitalWrite(0, LOW);
	return 0;
	}
	}
	}

