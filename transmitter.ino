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
   delay(5000);
   Serial.print('s');
   delay(5000);
}
