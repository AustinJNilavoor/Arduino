#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
//Servo servo6;
//Servo servo7;
//Servo servo8;
//Servo servo9;
char auth[] = "n_ka5jdOi70UcpmzUkOjSYkiIq8yusW9";
char ssid[] = "Allan";
char pass[] = "abcdefgh";

//char auth[] = "D9n_h9Tr3TLgkM7yYpA2eZS0Vg-bxc3x";
//char ssid[] = "NILAVOOR";
//char pass[] = "N1lav00r213";

void setup()
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  servo1.attach(16);
  servo2.attach(5);
  servo3.attach(4);
  servo4.attach(0);
  servo5.attach(2);
//  servo6.attach(14);
//  servo7.attach(15);
//  servo8.attach(13);
//  servo9.attach(12);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(1, OUTPUT);

  digitalWrite(14, LOW);
  digitalWrite(12, LOW);
  
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(3, LOW);
  digitalWrite(1, LOW);
  
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
//  servo5.write(0);
}

void motor1(int x1,int y1){
  if (x1 > 768 && y1 < 768 && y1 > 256){
    digitalWrite(14, HIGH);
    digitalWrite(12, LOW);
  }
  else if (x1 < 256 && y1 < 768 && y1 > 256){
    digitalWrite(14, LOW);
    digitalWrite(12, HIGH);
  }
  else if (y1 > 768 && x1 < 768 && x1 > 256){
    digitalWrite(14, HIGH);
    digitalWrite(12, LOW);
    servo4.write(25);
  }
  else if (y1 < 256 && x1 < 768 && x1 > 256){
    digitalWrite(14, HIGH);
    digitalWrite(12, LOW);
    servo4.write(155);
  }
  else {
    digitalWrite(14, LOW);
    digitalWrite(12, LOW);
  }
}

void motor2(int a){
  if (a > 150){
    digitalWrite(13, HIGH);
    digitalWrite(15, LOW);
  }
  else if (a < -150){
    digitalWrite(13, LOW);
    digitalWrite(15, HIGH);
  }
  else{
    digitalWrite(13, LOW);
    digitalWrite(15, LOW);
  }
  
}

void motor3(int b){
  if (b > 150){
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
  }
  else if (b < -150){
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
  }
  else{
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
  
}

void motor4(int c){
  if (c > 150){
    digitalWrite(3, HIGH);
    digitalWrite(1, LOW);
  }
  else if (c < -150){
    digitalWrite(3, LOW);
    digitalWrite(1, HIGH);
  }
  else{
    digitalWrite(3, LOW);
    digitalWrite(1, LOW);
  }
  
}


void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V1)
{
   servo1.write(param.asInt());
}
BLYNK_WRITE(V2)
{
   servo2.write(param.asInt());
}
BLYNK_WRITE(V3)
{
   servo3.write(param.asInt());
}
BLYNK_WRITE(V4)
{
  delay(1000);
  int x1 = param[0].asInt();
  int y1 = param[1].asInt();
//  servo4.write(param[1].asInt());
  motor1(x1,y1);
}
BLYNK_WRITE(V5)
{
  delay(1000);
  int a = param.asInt();
  motor2(a);
}

BLYNK_WRITE(V6)
{
  delay(1000);
  int b = param.asInt();
  motor3(b);
}
BLYNK_WRITE(V7)
{
  delay(1000);
  int c = param.asInt();
  motor4(c);
}
BLYNK_WRITE(V8)
{
   servo5.write(param.asInt());
}
