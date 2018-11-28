#include <XBee.h>
#include <dht11.h>

#define DHT_PIN 7


//XBee instance
XBee xbee = XBee();

//Temperature sensor instance
dht11 sensor;

//Coordinator address
XBeeAddress64 coordinator_address = XBeeAddress64(0x0, 0x0);


uint8_t text[2] = {'h','i'};
ZBTxRequest message = ZBTxRequest(coordinator_address, text, sizeof(text));
int packets = 20;

void setup()  
{
   Serial.begin(9600);
   Serial.println("Sending packets...");
   xbee.setSerial(Serial);
   delay(5000);
}
 
void loop()  
{
   sendPackets(packets);
   Serial.println("");
   Serial.print("Packets in 1 second: ");
   Serial.println(packets);
   Serial.println("Wait 5 seconds...");
   Serial.println("");
   delay(5000);
}

void sendPackets(int numPackets)
{
  for(int i = 0; i < numPackets; i++)
  {
    xbee.send(message);
    delay(1000/numPackets);
  }
}
