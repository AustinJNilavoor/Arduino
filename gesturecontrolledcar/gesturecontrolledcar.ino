int xPin=A3; //X axis input
int yPin=A2; //Y axis input
int Q1=10,Q2=11,Q3=12,Q4=13; //Output pins to be connected to 10, 11, 12, 13 of Decoder IC
long x; //Variabe for storing X coordinates
long y; //Variabe for storing Y coordinates
void setup()
{
  Serial.begin(9600);
  pinMode(Q1,OUTPUT);
  pinMode(Q2,OUTPUT);
  pinMode(Q3,OUTPUT);
  pinMode(Q4,OUTPUT);
}
void loop()
{
  x = analogRead(xPin); //Reads X coordinates
  y = analogRead(yPin); //Reads Y coordinates
    if(x<330)      // Change the value for adjusting sensitivity  
      forward();
    else if(x>390) // Change the value for adjusting sensitivity
      backward();
    else if(y>390) // Change the value for adjusting sensitivity
      right();
    else if(y<330) // Change the value for adjusting sensitivity
      left();
    else
      stop_();
    delay(100);
}
void stop_()
{
  Serial.println("");
  Serial.println("STOP");
  digitalWrite(Q1,LOW);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,LOW);
  digitalWrite(Q4,LOW);
}
void forward()
{
  Serial.println("");
  Serial.println("Forward");
  digitalWrite(Q1,HIGH);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,HIGH);
  digitalWrite(Q4,LOW);
}
void backward()
{
  Serial.println("");
  Serial.println("Backward");
  digitalWrite(Q1,LOW);
  digitalWrite(Q2,HIGH);
  digitalWrite(Q3,LOW);
  digitalWrite(Q4,HIGH);
}
void left()
{
  Serial.println("");
  Serial.println("Left");
  digitalWrite(Q1,LOW);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,HIGH);
  digitalWrite(Q4,LOW);
}
void right()
{
  Serial.println("");
  Serial.println("Right");
  digitalWrite(Q1,HIGH);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,LOW);
  digitalWrite(Q4,LOW);
}
