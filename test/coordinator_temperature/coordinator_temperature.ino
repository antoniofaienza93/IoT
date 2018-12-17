#include <Ethernet.h>
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
  int temperature = concatenate(rx.getData(0)-48, rx.getData(1)-48);
  Serial.print(temperature);
  Serial.println("");
}

unsigned concatenate(unsigned x, unsigned y) 
{
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
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
