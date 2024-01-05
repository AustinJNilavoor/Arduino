/*
 ESP8266 Web Server
 Made By Austin J Nilavoor

 connect ESP8266 to Arduino uno/Mega
 Tx - Pin 2
 Rx - Pin 3
 Vcc - 3.3v
 Gnd - Gnd
 CHPD - 3.3v
*/
#include <SoftwareSerial.h>

SoftwareSerial Serial1(2, 3); // This will make the Arduino pin 2 as the RX pin and Arduino pin 3 as the TX. Software UART
#define DEBUG true
 
void setup()
{
  Serial.begin(115200);    //Band Rate For Serial monitor 
  Serial1.begin(115200); //ESP8266 Baud rate
  pinMode(13,OUTPUT);    //Define Led Pin 13 As Output
  digitalWrite(13,LOW);  //Led Pin 13 Low
 
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // Configure ESP8266 As Access Point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // Get ip address Of ESP8266
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // Configure For Multiple Connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // Turn on Server on Port 80
}


int connectionId;
void loop(){
  if(Serial1.available())
  {
    //Recieving from web browser to toggle led
    if(Serial1.find("+IPD,"))
     { 
     String request = Serial1.readStringUntil('\r'); //String request 
     Serial.println(request); // Println request
     if (request.indexOf("/LEDON?") != -1){ // if /LEDON? is recived
     digitalWrite(13, HIGH);// LED ON
     }
     if (request.indexOf("/LEDOFF?") != -1){// if /LEDOFF? is recived
     digitalWrite(13, LOW);// LED OFF
    }
   
    /////////////////////Sending data to browser////////////////////
    else
    {
      String webpage = "<!DOCTYPE html><html><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><head><title>LED Control</title></head><body><div id='main'><h2>LED Control</h2>";
      espsend(webpage);
      String add1="<form id='F1' action='LEDON'><input class='button' type='submit' value='LED ON' ></form><br>";
      espsend(add1);
      String add2="<form id='F2' action='LEDOFF'><input class='button' type='submit' value='LED OFF' ></form><br>";
      espsend(add2);
      String add3="<h3>made by</h3><h2>Austin J Nilavoor</h2></div></body></html>";
      espsend(add3);
     }
     
     String closeCommand = "AT+CIPCLOSE=";  //Close the Socket Connection 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     sendData(closeCommand,3000,DEBUG);
    }
  }
}
 
  ////////////////////////sends data from ESP to webpage///////////////////////////
 
 void espsend(String d)
         {
             String cipSend = " AT+CIPSEND=";
             cipSend += connectionId; 
             cipSend += ",";
             cipSend +=d.length();
             cipSend +="\r\n";
             sendData(cipSend,1000,DEBUG);
             sendData(d,1000,DEBUG); 
         }

//////////////gets the data from esp and displays in serial monitor///////////////////////         
String sendData(String command, const int timeout, boolean debug)
            {
                String response = "";
                Serial1.print(command);
                long int time = millis();
                while( (time+timeout) > millis())
                {
                   while(Serial1.available())
                      {
                         char c = Serial1.read(); // read the next character.
                         response+=c;
                      }  
                }
                if(debug)
                     {
                     Serial.print(response); //displays the esp response messages in arduino Serial monitor
                     }
                return response;
            }
