	#include <stdio.h>
	#include <wiringPi.h> 



	int valve_off_function(void)

	{ 
	printf ("Raspberry pi - gertboard blink\n");

        
	wiringPiSetup ();
	pinMode (0, OUTPUT);
	pinMode (1, INPUT);
       digitalWrite(0, LOW);
      
	 for (;;)
 	 { 
	if(digitalRead(1) == LOW)
	{			
       	if(digitalRead(0) == HIGH)
           digitalWrite (0, LOW);
       	else if(digitalRead (0) ==LOW)
	       	digitalWrite (0, HIGH);
	}
  
  	}
	//return 0;
	}

