#include <XBee.h>
#include <dht11.h>

#define DHT_PIN 7


//XBee instance
XBee xbee = XBee();

//Temperature sensor instance
dht11 sensor;

//Coordinator address
XBeeAddress64 coordinator_address = XBeeAddress64(0x0, 0x0);

//Router address
XBeeAddress64 router_address = XBeeAddress64(0x0013a200, 0x4079D623);

int packets = 0;
int num_packets[6] = {1, 5, 10, 20, 35, 50};
uint8_t text[2] = {'h','i'};
ZBTxRequest message = ZBTxRequest(router_address, text, sizeof(text));


void setup()  
{
   Serial.begin(9600);
   xbee.setSerial(Serial);
   Serial.print("End node on!");
   delay(25000);
}
 
void loop()  
{
  for(int i = 5; i < 6; i++)
  {
   packets = num_packets[i];
   Serial.println("");
   Serial.print("Sending ");
   Serial.print(packets);
   Serial.println(" packets in 1 second for 10 times...");
   for(int j = 0; j < 10; j++)
   {
    Serial.println(j);
    sendPackets(packets);
    Serial.println("");
    delay(5000);
   }
   Serial.println("Done!");
   delay(25000);
  }
  Serial.print("End transmission!");
  while(true);
}

void sendPackets(int numPackets)
{
  float d = 1000/numPackets;
  for(int i = 0; i < numPackets; i++)
  {
    xbee.send(message);
    delay(d);
  }
}
