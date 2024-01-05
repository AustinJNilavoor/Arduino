int pot1 = A0;
int pot2 = A1;
int pot3 = A2;
int Buzzer = 2;
int potV1 = 0;
int potV2 = 0;
int potV3 = 0;
int tol = 30;

int v1 = 600;
int v2 = 285;
int v3 = 130;



void setup() {
  Serial.begin(9600);
  Serial.println("Serial Working");
  pinMode(pot1, INPUT);
  pinMode(pot2, INPUT);
  pinMode(pot3, INPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(Buzzer, LOW);
  // put your setup code here, to run once:
}

void loop() {
  potV1 = analogRead(pot1);
  potV2 = analogRead(pot2);
  potV3 = analogRead(pot3);
  Serial.println("pot1");
  Serial.println(potV1);
  Serial.println("pot2");
  Serial.println(potV2);


  Serial.println("pot3");
  Serial.println(potV3);

  if (v1 < potV1 + tol and v1 > potV1 - tol and v2 < potV2 + tol and v2 > potV2 - tol and v3 < potV3 + tol and v3 > potV3 - tol) {
    if (digitalRead(Buzzer) == LOW) {
      digitalWrite(Buzzer, HIGH);
    } 
  }
  else {
      digitalWrite(Buzzer, LOW);
    }
  delay(1000);
}
