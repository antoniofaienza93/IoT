#include <XBee.h>
#include <dht11.h>

#define DHT_PIN 7


//XBee instance
XBee xbee = XBee();

//Temperature sensor instance
dht11 sensor;

//Router address
XBeeAddress64 router_address = XBeeAddress64(0x0013a200, 0x4079D623);

//Coordinator address
XBeeAddress64 coordinator_address = XBeeAddress64(0x0, 0x0);


//Request objects
ZBTxRequest message;

uint8_t temperature[2];

void setup()  
{
   Serial.begin(9600);
   Serial.println("End_node on!");
   xbee.setSerial(Serial);
   delay(100);
}
 
void loop()  
{
   getTemperature();
   Serial.print("Measured temperature: ");
   Serial.println((char*)temperature);
   message = ZBTxRequest(router_address, temperature, sizeof(temperature));
   Serial.println("Sending temperature...");
   xbee.send(message);
   
   delay(3000);
}

void getTemperature()
{
  //Read temperature from sensor
   sensor.read(DHT_PIN);
   int temperature_number = sensor.temperature;
   sprintf(temperature, "%d", temperature_number);
}
