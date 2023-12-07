#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <time.h>

#define DHTPIN 16
#define DHTTYPE DHT11
#define MSG_BUFFER_SIZE (500)
char msg[MSG_BUFFER_SIZE];
int value = 0;

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
const char *SSID = "CLARO_2GCC5C89";
const char *PWD = "B7CC5C89";
const char *mqttServer = "192.168.0.9";
const int mqttPort = 1883;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void connectWifi();
void setupMQTT();
void reconnect();
void callback(char *topic, byte *payload, unsigned int length);

void setup()
{
  Serial.begin(9600);
  delay(5000);

  pinMode(2, OUTPUT);
  
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 100;

  connectWifi();
  setupMQTT();
}

void loop()
{
  if (!mqttClient.connected())
    reconnect();

  sensors_event_t event;
  dht.temperature().getEvent(&event);

  mqttClient.loop();

  ++value;
  snprintf(msg, MSG_BUFFER_SIZE, "%f", event.temperature);
  if(event.temperature > 40.0){
      digitalWrite(2, HIGH);
  }else{
      digitalWrite(2, LOW);
  }

  Serial.print("Publish message: ");
  Serial.println(msg);
  mqttClient.publish("/sensores/temperatura", msg);digitalWrite(2, LOW);
}

void connectWifi()
{
  Serial.print("Connecting to ");

  WiFi.begin(SSID, PWD);
  Serial.println(SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected.");
  Serial.print("Your IP = ");
  
  if(WiFi.enableIpV6())
    Serial.println(WiFi.localIPv6());
  else
    Serial.println(WiFi.localIP());
}

void setupMQTT()
{
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);
}

void reconnect()
{
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected())
  {
    Serial.println("Reconnecting to MQTT Broker..");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str()))
    {
      Serial.println("Connected.");
      mqttClient.subscribe("/sensores/teste");
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Callback - ");
  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
}