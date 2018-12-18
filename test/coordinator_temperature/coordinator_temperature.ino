#include <Ethernet.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <XBee.h>

#define mqtt_server "192.168.137.157"
#define mqtt_port 1883
#define wifi_ssid "SuriLaptop"
#define wifi_pass "TutteCapre00"

//XBee object with callbacks
XBeeWithCallbacks xbee;

//Ethernet mac address
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x28, 0x8F};

WiFiClient wifiCoordinatorClient;
PubSubClient coordinator(wifiCoordinatorClient);


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void receive(ZBRxResponse& rx, uintptr_t) 
{
  int temperature = extractTemperature(rx);
  coordinator.publish("temperature", temperature);
}

int extractTemperature(ZBRxResponse& rx)
{
  int temperature = concatenate(rx.getData(0)-48, rx.getData(1)-48);
  Serial.print(temperature);
  Serial.println("");
  return temperature;
}

unsigned concatenate(unsigned x, unsigned y) 
{
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

void connect_to_ethernet()
{
  Ethernet.begin(mac);
  delay(1000);
   
  if (Ethernet.linkStatus() == LinkOFF) 
  {
      Serial.println("Ethernet cable is not connected.");
  }
}

void connect_to_WiFi()
{
  WiFi.begin(wifi_ssid, wifi_pass);
  delay(500);
  Serial.print("Connecting to WiFi...");
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("WiFi connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void connect_to_broker()
{
  coordinator.setServer(mqtt_server, mqtt_port);
 
  while (!coordinator.connected()) 
  {
    Serial.println("Connecting to MQTT...");
 
    if (coordinator.connect("ESP8266Client")) 
    {
      Serial.println("Connected to broker!");  
    } 
    else 
    {
      Serial.print("failed with state ");
      Serial.print(coordinator.state());
      delay(2000);
    }
  }
}

void setup()  
{
  Serial.begin(9600);
  xbee.setSerial(Serial);
  xbee.onZBRxResponse(receive);
  //connect_to_ethernet();
  connect_to_WiFi();
  connect_to_broker();
}
 
void loop()  
{
  xbee.loop();
  coordinator.loop();
}
