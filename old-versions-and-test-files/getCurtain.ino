#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "ArduinoJson.h"
// WiFi Parameters
const char* ssid = "WIFIC933D2";
const char* password = "DKASY2E12ZECTXX5";
void setup() {
 Serial.begin(115200);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(1000);
   Serial.println("Connecting...");
 }
}
void loop() {
 // Check WiFi Status
 if (WiFi.status() == WL_CONNECTED) {
   HTTPClient http;  //Object of class HTTPClient
   http.begin("http://electropeak.com/api/ifttt/?apikey=1aa549ca5de0f1614fb0704ad40a167c");
   int httpCode = http.GET();
   //Check the returning code                                                                  
   if (httpCode > 0) {
     // Get the request response payload
     String payload = http.getString();
     // TODO: Parsing
     Serial.println(payload);
   }
   http.end();   //Close connection
 }
 // Delay
 delay(3000);
}
