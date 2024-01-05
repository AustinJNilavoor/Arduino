#include <IRremote.h>
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define Fan 3
int i=0,j=0,k=0,n=0;
void setup()
{
  Serial.begin(9600);
  pinMode(Fan, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}
void loop() 
{
  if (irrecv.decode(&results)) 
   {
     Serial.println(results.value, HEX);
     if(results.value==0xC0000C)
     {
        i++;
        int x=i%2;
        digitalWrite(Fan, x);
     }
     irrecv.resume(); // Receive the next value 
     delay(1000);
   }
}
