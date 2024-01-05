  //Room temp monitor
  //austin j nilavoor
  
int buzzerPin = 3; //pin for the led
int inputPin = 2; //input pin for pir
int val = 0;

void setup(){
  pinMode(buzzerPin, OUTPUT);
  pinMode(inputPin, INPUT);
}
void loop(){
  val = digitalRead(inputPin);
  if (val == HIGH){
    digitalWrite(buzzerPin, HIGH);
  } else{
    digitalWrite(buzzerPin, LOW);
  }
}

