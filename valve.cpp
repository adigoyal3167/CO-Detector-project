	#include <stdio.h>
	#include <wiringPi.h> 



	int valve_off_function(void)
//	int main () 

	{ 
	printf ("Raspberry pi - gertboard blink\n");

        
	wiringPiSetup ();
	pinMode (0, OUTPUT);
	pinMode (25, INPUT);
        digitalWrite(0, LOW);
      
//       for (;;)
 
       { 
         //  printf("gpio 17 low value");
	       digitalWrite(0, HIGH);
	   //    delay(100);
          // printf("read value on gpio 5");
	
	for (;;)
	       if(digitalRead(25) == HIGH)
	       {
	       	       digitalWrite(0, LOW);
		       return 0;
	       }
	//	       delay(100);

//	{			
  //     	if(digitalRead(0) == HIGH)
//        printf("valve off");
//	     	digitalWrite(0, LOW);
	//	delay(100);
    //   
      
    //
    //   else if(digitalRead (0) ==LOW)
//	       	digitalWrite (0, HIGH);
//	}
  
  	}

//     close (main);
       return 0;
	}

