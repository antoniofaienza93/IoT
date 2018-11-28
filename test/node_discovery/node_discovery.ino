#include <XBee.h>
#include <dht11.h>

#define DHT_PIN 7

int timeout = 3000;

//XBee instance
XBeeWithCallbacks xbee;

ZBTxRequest message;
ZBRxResponse response;


void setup()  
{
   Serial.begin(9600);
   Serial.println("End_node on!");
   xbee.setSerial(Serial);

   delay(100);
}
 
void loop()  
{
  int nodeCount = 0;

  uint8_t nd[] = {'N', 'D'}
  message = ZBTxRequest(broadcast_address, nd, sizeof(nd));
  Serial.print("Sending discovery messages...");
  xbee.send(request);
  Serial.println("");
  
  while(xbee.readPacket(timeout)) 
  {
    // should be receiving AT command responses
    if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) 
    {
      xbee.getResponse().getAtCommandResponse(response);
      if (response.isOk()) 
      {
        nodeCount++;
      }
    }
  }

  Serial.print("Results: ");
  Serial.print(nodeCount, DEC);
  Serial.println(" node(s) responded.");
  Serial.println("");
}
