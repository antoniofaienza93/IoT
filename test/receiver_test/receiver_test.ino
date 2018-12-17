#include <XBee.h>

XBeeWithCallbacks xbee;
int receivedPackets = 0;

void receive(ZBRxResponse& rx, uintptr_t) 
{
  receivedPackets++;
  Serial.println(receivedPackets);
}

void setup()  
{
  Serial.begin(9600);
  xbee.setSerial(Serial);
  xbee.onZBRxResponse(receive);
  Serial.println("Receiving packets...");
}
 
void loop()  
{
  xbee.loop();
}
