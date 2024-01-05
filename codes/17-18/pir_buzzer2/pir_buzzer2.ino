  //austin j nilavoor

int calibrationTime = 30;
int buzzerPin = 3; //output pin for buzzer
int inputPin = 2; //input pin for pir
int val = 0;

void setup(){
  pinMode(buzzerPin, OUTPUT);
  pinMode(inputPin, INPUT);
   //give the sensor some time to calibrate
    for(int i = 0; i < calibrationTime; i++){
      delay(1000);
      }
}
void loop(){
  val = digitalRead(inputPin);
  if (val == HIGH){
    digitalWrite(buzzerPin, HIGH);
  }
}

