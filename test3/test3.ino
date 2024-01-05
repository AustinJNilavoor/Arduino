#include <SoftwareSerial.h>

SoftwareSerial Serial1(2, 3);
#define DEBUG true
int pin=1;
 
void setup()
{
  Serial.begin(115200);    ///////For Serial monitor 
  Serial1.begin(115200); ///////ESP Baud rate
  pinMode(13,OUTPUT);    /////used if connecting a LED to pin 11
  digitalWrite(13,LOW);
 
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}


int connectionId;
void loop(){
  if(Serial1.available())
  {
    /////////////////////Recieving from web browser to toggle led
    if(Serial1.find("+IPD,"))
     { 
     String request = Serial1.readStringUntil('\r');
     Serial.println(request);
     if (request.indexOf("/LEDON?") != -1)
     digitalWrite(13, HIGH);
     if (request.indexOf("/LEDOFF?") != -1){
     digitalWrite(13, LOW);
    }
   
    /////////////////////Sending data to browser
    else
    {
      String webpage = "<!DOCTYPE html><html><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><head><title>LED Control</title></head><body><div id='main'><h2>LED Control</h2>";
      espsend(webpage);
      String add1="<form id='F1' action='LEDON'><input class='button' type='submit' value='LED ON' ></form><br>";
      espsend(add1);
      String add2="<form id='F2' action='LEDOFF'><input class='button' type='submit' value='LED OFF' ></form><br>";
      espsend(add2);
      String add3="</div></body></html>";
      espsend(add3);
     }
     
     String closeCommand = "AT+CIPCLOSE=";  ////////////////close the socket connection////esp command 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     sendData(closeCommand,3000,DEBUG);
    }
  }
}
 
  //////////////////////////////sends data from ESP to webpage///////////////////////////
 
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
