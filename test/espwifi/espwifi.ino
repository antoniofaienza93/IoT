#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

SoftwareSerial ESPserial(D7, D6); // RX | TX

#define mqtt_server "90.147.188.131"
//#define mqtt_server "192.168.43.68"
#define mqtt_port 1883
#define wifi_ssid "SuriLaptop"
#define wifi_pass "TutteCapre00"

WiFiClient espClient;
PubSubClient client(espClient);

void setup() 
{
  Serial.begin(9600);
  connect_to_WiFi();
  connect_to_broker();
  ESPserial.begin(115200); 
}

void loop() 
{
  client.loop();
  if (ESPserial.available()>0)
  {
    int val = ESPserial.read();
    char str[2];
    sprintf(str, "%d", val);
    client.publish("temperature", str);
  }
  delay(3000);
}

void connect_to_WiFi()
{
  WiFi.begin(wifi_ssid, wifi_pass);
  delay(500);
  Serial.print("Connecting to WiFi");
 
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
  client.setServer(mqtt_server, mqtt_port);
 
  while (!client.connected()) 
  {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client"))
    {
      Serial.println("Connected to broker!");  
    } 
    else 
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
