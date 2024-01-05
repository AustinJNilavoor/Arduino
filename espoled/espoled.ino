#include "SH1106.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>
SH1106 display(0x3c, SDA, SCL);

//const char *ssid = "Austin J";
//const char *password = "987664321";
const char *ssid = "NILAVOOR";
const char *password = "N1lav00r213";

void setup() 
{
  Serial.begin(115200);
  display.init(); // Initialising the UI will init the display too.
  display.flipScreenVertically();
  display.clear();
  display.drawString(0, 10, "Connecting ..");
  display.display();
  WiFi.begin(ssid, password);
  delay(5000);
while ( WiFi.status() != WL_CONNECTED )
{
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  display.clear();
  display.drawString(0, 10, "Connected to");
  display.drawString(0, 20, ssid);
  display.drawString(0, 30, WiFi.localIP().toString());
  display.display();
  delay(1000);
  }
void loop() 
{
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
    http.begin("api.wazirx.com/api/v2/trades?market=shibinr");
    delay(3000);
    int httpCode = http.GET();                                        //Make the request
    //delay(3000);
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        //delay(3000);
        Serial.println(httpCode);
        Serial.println(payload);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
  else {
  Serial.println("Error request");
 }
  delay(10000);
}
