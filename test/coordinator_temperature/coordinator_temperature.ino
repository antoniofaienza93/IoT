#include <XBee.h>

XBeeWithCallbacks xbee;

//Coordinator address
XBeeAddress64 coordinator_address = XBeeAddress64(0x0, 0x0);

void receive(ZBRxResponse& rx, uintptr_t) 
{
  printPayload(rx);
  
  Serial.println("");
}

void printPayload(ZBRxResponse& rx)
{
  for (int i = 0; i < rx.getDataLength(); i++) 
  {
    Serial.print("Payload: ");
    //Minus 48 because it's an ASCII value
    Serial.print(rx.getData(i)-48, DEC);
  }
  Serial.println("");
}
void setup()  
{
  Serial.begin(9600);
  xbee.setSerial(Serial);
  xbee.onZBRxResponse(receive);
  delay(100);
}
 
void loop()  
{
  xbee.loop();
}
