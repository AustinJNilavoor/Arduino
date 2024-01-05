//#include <AJSP.hpp>

//#include <Arduino_JSON.h>


#include <HttpClient.h>

                                               //Include the required libraries#include <WiFi.h>
#include <Wire.h>
#include <NTPClient.h> 
#include <WiFiUdp.h>
#include <ArduinoJson.h>

const char* ssid = "Network Name";                                            //Set your WiFi network name and password
const char* password = "Password";

const int httpsPort = 443;                                                          //Bitcoin price API powered by CoinDesk - https://www.coindesk.com/price/bitcoin
const String url = "http://api.coindesk.com/v1/bpi/currentprice/BTC.json";
const String cryptoCode = "BTC";

WiFiClient client;                                                            //Create a new WiFi client
HTTPClient http;

void setup() 
{
  Serial.begin(115200);                                                       //Start the serial monitor

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)                                        //Connect to the WiFi network
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();


void loop() 
{
  Serial.print("Connecting to ");                                                       //Display url on Serial monitor for debugging
  Serial.println(url);

  http.begin(url);
  int httpCode = http.GET();                                                            //Get crypto price from API
  StaticJsonDocument<2000> doc;
  DeserializationError error = deserializeJson(doc, http.getString());

  if (error)                                                                            //Display error message if unsuccessful
  {
    Serial.print(F("deserializeJson Failed"));
    Serial.println(error.f_str());
    delay(2500);
    return;
  }

  Serial.print("HTTP Status Code: ");
  Serial.println(httpCode);

  String BTCUSDPrice = doc["bpi"]["USD"]["rate_float"].as<String>();                    //Store crypto price and update date in local variables
  String lastUpdated = doc["time"]["updated"].as<String>();
  http.end();

  Serial.print("Getting history...");
  StaticJsonDocument<2000> historyDoc;
  http.begin(historyURL);                                                               //Get historical crypto price from API
  int historyHttpCode = http.GET();
  DeserializationError historyError = deserializeJson(historyDoc, http.getString());

  if (historyError) {                                                                   //Display error message if unsuccessful
    Serial.print(F("deserializeJson(History) failed"));
    Serial.println(historyError.f_str());
    delay(2500);
    return;
  }

  Serial.print("History HTTP Status Code: ");
  Serial.println(historyHttpCode);
  JsonObject bpi = historyDoc["bpi"].as<JsonObject>();
  double yesterdayPrice;
  for (JsonPair kv : bpi) {
    yesterdayPrice = kv.value().as<double>();                                           //Store yesterday's crypto price
  }

  Serial.print("BTCUSD Price: ");                                                       //Display current price on serial monitor
  Serial.println(BTCUSDPrice.toDouble());

  Serial.print("Yesterday's Price: ");                                                  //Display yesterday's price on serial monitor
  Serial.println(yesterdayPrice);
  
  bool isUp = BTCUSDPrice.toDouble() > yesterdayPrice;                                  //Check whether price has increased or decreased
  double percentChange;
  String dayChangeString = "24hr. Change: "; 
 

  Serial.print("Percent Change: ");                                                     //Display the percentage change on the serial monitor
  Serial.println(percentChange);
                                      
  http.end();
  delay(1000);//Sleep for 15 minutes
}
