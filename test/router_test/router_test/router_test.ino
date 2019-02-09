#include <XBee.h>

XBeeWithCallbacks xbee;
XBeeAddress64 coordinator_address = XBeeAddress64(0x0013a200, 0x4079a81f);

void receive(ZBRxResponse& rx, uintptr_t) 
{
  //Message packet
  ZBTxRequest message = ZBTxRequest(coordinator_address, rx.getFrameData(), rx.getDataLength());
  xbee.send(message);
}

void setup()  
{
  xbee.onZBRxResponse(receive);
  Serial.begin(9600);
  xbee.setSerial(Serial);
  delay(100);
}

void loop()  
{
  xbee.loop();
}
