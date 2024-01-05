  //austin j nilavoor
int multi = 3; //output pin for multi color led
int red = 4; //output pin for red
int green = 5; //output pin for green
int blue = 6; //output pin for blue
int white = 7; //output pin for white
int star = 8; //output pin for star

void setup(){
  pinMode(multi, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(white, OUTPUT);
  pinMode(star, OUTPUT);
  digitalWrite(star, HIGH);
}
void loop(){
  {
  digitalWrite(red, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(8000);                       // wait for a second
  digitalWrite(red, LOW);    // turn the LED off by making the voltage LOW
  delay(1);
  }
  {
  digitalWrite(green, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(8000);                       // wait for a second
  digitalWrite(green, LOW);    // turn the LED off by making the voltage LOW
  delay(1);
  }
  {
  digitalWrite(blue, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(8000);                       // wait for a second
  digitalWrite(blue, LOW);    // turn the LED off by making the voltage LOW
  delay(1);
  }
  {
  digitalWrite(white, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(8000);                       // wait for a second
  digitalWrite(white, LOW);    // turn the LED off by making the voltage LOW
  delay(1);
  }
  {
  digitalWrite(multi, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(8000);                       // wait for a second
  digitalWrite(multi, LOW);    // turn the LED off by making the voltage LOW
  delay(1);
  }
}
