#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#include <ESP8266WiFi.h>

#define WIFI_SSID "WIFIC933D2"
#define WIFI_PASS "DKASY2E12ZECTXX5"

#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "Mikester0822"
#define MQTT_PASS "fa6ec8e440f240c48db095f0e3ed403b"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

Adafruit_MQTT_Subscribe onoff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/onoff");

void setup()
{
  Serial.begin(9600);

  //Connect to WiFi
  Serial.print("\n\nConnecting Wifi... ");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.println("OK!");

  //Subscribe to the onoff topic
  mqtt.subscribe(&onoff);

  pinMode(LED_BUILTIN, OUTPUT);
}

/***************************************************
Adafruit MQTT Library ESP8266 Example
Must use ESP8266 Arduino from:  https://github.com/esp8266/Arduino
Works great with Adafruit's Huzzah ESP board & Feather
 ---->   https://github.com/esp8266/Arduino
 ---->   https://github.com/esp8266/Arduino
Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!
Written by Tony DiCola for Adafruit Industries.
MIT license, all text above must be included in any redistribution
****************************************************/
void MQTT_connect() 
{
  int8_t ret;
  // Stop if already connected
  if (mqtt.connected())
  {
    return;
  }

  //Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  { 
    //Serial.println(mqtt.connectErrorString(ret));
    //Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(100);  // wait 5 seconds
    retries--;
    if (retries == 0) 
    {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  //Serial.println("MQTT Connected!");
}

void loop()
{
  //Connect/Reconnect to MQTT
  MQTT_connect();

  //Read from our subscription queue until we run out, or
  //wait up to 5 seconds for subscription to update
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    //If we're in here, a subscription updated...
    if (subscription == &onoff)
    {
      //Print the new value to the serial monitor
      Serial.print("onoff: ");
      Serial.println((char*) onoff.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) onoff.lastread, "ON"))
      {
        //active low logic
        digitalWrite(LED_BUILTIN, LOW);
      }
      else
      {
        digitalWrite(LED_BUILTIN, HIGH);
      }
    }
  }
}
