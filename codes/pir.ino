int ledPin = 3; //pin for the led
int inputPin = 2; //input pin for pir
int val = 0;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
}
void loop(){
  val = digitalRead(inputPin);
  if (val == HIGH){
    digitalWrite(ledPin, HIGH);
  } else{
    digitalWrite(ledPin, LOW);
  }
}

