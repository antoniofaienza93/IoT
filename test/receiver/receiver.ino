#include <XBee.h>

XBee xbee = XBee();
ZBRxResponse received_message = ZBRxResponse();
XBeeAddress64 address = XBeeAddress64(0x0013A200, 0x4079A81F);

void setup()  
{
   Serial.begin(9600);
   xbee.setSerial(Serial);
   delay(10);
}
 
void loop()  
{
  xbee.readPacket();

  if(xbee.getResponse().isAvailable())
  {
    xbee.getResponse().getZBRxResponse(received_message);
    ZBTxRequest message = ZBTxRequest(address, received_message.getFrameData(), received_message.getFrameDataLength());
    xbee.send(message);
  }
}
