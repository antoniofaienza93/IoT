#include <XBee.h>
#include <dht11.h>

#define DHT_PIN 7

XBee xbee = XBee();
dht11 sensor;

//Router
XBeeAddress64 address = XBeeAddress64(0x0013A200, 0x4079D623);
//Coordinator
//XBeeAddress64 address = XBeeAddress64(0x0013A200, 0x4079A81F);

void setup()  
{
   Serial.begin(9600);
   xbee.setSerial(Serial);
   delay(10);
}
 
void loop()  
{
   sensor.read(DHT_PIN);
   int temp = sensor.temperature;
   //uint8_t payload[] = {temp};
   uint8_t payload[] = { 'H', 'i' };
   
   ZBTxRequest message = ZBTxRequest(address, payload, sizeof(payload));
   xbee.send(message);
   delay(1000);
}
