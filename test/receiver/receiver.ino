#include <XBee.h>

int led = 13;
XBee xbee = XBee();

void setup()  
{
   Serial.begin(9600);
   xbee.setSerial(Serial);
   pinMode( led, OUTPUT );
   digitalWrite( led,LOW );
}
 
void loop()  
{
  if (Serial.available()) 
  {
    byte rcvd = Serial.read();
 
    if (rcvd == 'a') digitalWrite(led,HIGH); 
    if (rcvd == 's') digitalWrite(led,LOW);
  } 
  delay(300);
}
