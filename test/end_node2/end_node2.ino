#include <SoftwareSerial.h>
#include <XBee.h>
#include <dht11.h>

#define DHT_PIN 7

//Software serial
//SoftwareSerial swSerial(10, 11); // RX, TX

//XBee instance
XBee xbee = XBee();

//Temperature sensor instance
dht11 sensor;

//Router address
XBeeAddress64 router_address = XBeeAddress64(0x0013a200, 0x4079D623);

//Coordinator address
XBeeAddress64 coordinator_address = XBeeAddress64(0x0013a200, 0x4079a81f);

//Status response
ZBTxStatusResponse statusResponse = ZBTxStatusResponse();

void setup()  
{
   //Hardware serial initialization
   Serial.begin(9600);

   //Maps hardware serial with xbee serial
   xbee.setSerial(Serial);

   delay(100);
}
 
void loop()  
{
   uint8_t temperature = getTemperature();
   
   //Message packet
   ZBTxRequest message = ZBTxRequest(coordinator_address, temperature, sizeof(temperature));

   //Send message to router
   xbee.send(message);

  /*
   //Wait 5 seconds for a status response
   if (xbee.readPacket(5000)) 
   {             
      if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) 
      {
         xbee.getResponse().getZBTxStatusResponse(statusResponse);
         //If response
         if (statusResponse.getDeliveryStatus() == SUCCESS) 
         {
           Serial.println("Success");
         }
       }
   }
   //else
   //{
     //message = ZBTxRequest(coordinator_address, temperature, sizeof(temperature));
     //xbee.send(message);
   //}
   
   //Wait before sending another packet
   //delay(10000);
   */
   delay(3000);
}

int getTemperature()
{
  //Read temperature from sensor
   sensor.read(DHT_PIN);
   int temperature_number = sensor.temperature;
   return temperature_number;
}
