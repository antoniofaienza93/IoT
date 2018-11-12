#include <XBee.h>

XBee xbee = XBee();

void setup()  
{
   Serial.begin(9600);
   xbee.setSerial(Serial);
}
 
void loop()  
{
   Serial.print('a');
   delay(100);
   Serial.print('s');
   delay(1000);
}
