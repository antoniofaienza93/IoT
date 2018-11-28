#include <XBee.h>

XBeeWithCallbacks xbee;

//Coordinator address
XBeeAddress64 coordinator_address = XBeeAddress64(0x0, 0x0);

void receive(ZBRxResponse& rx, uintptr_t) 
{
  printPayload(rx);
  Serial.println("Message delivered!");
  ZBTxRequest message = ZBTxRequest(coordinator_address, rx.getFrameData() + rx.getDataOffset(), rx.getDataLength());
  xbee.send(message);
}

void printPayload(ZBRxResponse& rx)
{
  for (int i = 0; i < rx.getDataLength(); i++) 
  {
    Serial.print("payload [");
    Serial.print(i, DEC);
    Serial.print("] is ");
    Serial.println(rx.getData()[i], DEC);
  }
}
void setup()  
{
  Serial.begin(9600);
  xbee.setSerial(Serial);
  xbee.onZBRxResponse(receive);
  Serial.println("Router on!");
  delay(100);
}
 
void loop()  
{
  xbee.loop();
}
