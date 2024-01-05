#include <SoftwareSerial.h>

SoftwareSerial Serial1(2, 3);
#define DEBUG true
int pin=1;
 
void setup()
{
  Serial.begin(9600);    ///////For Serial monitor 
  Serial1.begin(115200); ///////ESP Baud rate
  pinMode(13,OUTPUT);    /////used if connecting a LED to pin 11
  digitalWrite(13,LOW);
 
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}


int connectionId;
void loop()
{
  if(Serial1.available())
  {
    /////////////////////Recieving from web browser to toggle led
    if(Serial1.find("+IPD,"))
    {
     delay(300);
     connectionId = Serial1.read()-48;
     if(Serial1.find("pin="))
     { 
     Serial.println("recieving data from web browser");
     int pinNumber = (Serial1.read()-48)*10; 
     pinNumber += (Serial1.read()-48); 
     digitalWrite(pinNumber, !digitalRead(pinNumber));
     }
   
    /////////////////////Sending data to browser
    else
    {
      String webpage = "<html><head><tittle>Austin J Nilavoor</tittle></head><body><h1>Hello</h1><h2>World!</h2><button>LED1</button></body></html>";
      espsend(webpage);
      String add1="<h3>Austin J Nilavoor</h3>";
      espsend(add1);
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
