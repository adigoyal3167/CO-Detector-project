#include "MQ7.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


MQ7 mq7(A0,5.0);
const int AOUTpin=0;
const int DOUTpin=8;
const int ledpin=7;

RF24 radio(7,10);// CE, CSN
const byte address[6] = "00001";


int limit;
int value;

void setup()
{
   Serial.begin(9600);
    pinMode (DOUTpin, INPUT);
    pinMode (ledpin, OUTPUT);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
 char text[100];
 value= analogRead(AOUTpin);
 limit= digitalRead(DOUTpin);
 Serial.print(" CO value:");
 Serial.println(value);
 Serial.print("Limit:");
  Serial.print(limit);

  sprintf(text,"Arduino2 = %d:%d",value,limit);
  delay(100);
 /* 
Serial.print(" Allarm");
 {    if (limit ==HIGH)
     }
  else{
    Serial.print("OK");
  }*/
  //const char text[] = "Hello aditya & amardeep";
  radio.write(&text, sizeof(text));
  
  delay(3000);
}
