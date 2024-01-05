int led1 = 9;
int led2 = 10;
int IRSensor[] = { 2, 3, 4, 5, 6, 7 };
int previousState[] = { 0, 0, 0, 0, 0, 0  };
int sensorStatus[] = { 0, 0, 0, 0, 0, 0 };
// int tonefreq[] = {261,293,329,369,392,440};
int tonefreq[] = { 523, 587, 659, 784, 880, 987 };
int entryList[] = { 0, 0, 0, 0, 0, 0, 0 };
int toneList[] = { 3, 3, 1, 1, 2, 2, 1 };
int count = 0;
int win = 0;
int wincount = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Working");
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, HIGH);
  for (int i = 0; i < 14; i++) {
    pinMode(IRSensor[i], INPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  for (int x = 0; x < 7; x++) {
    if (entryList[x] == toneList[x]) {
      win = 1;
      wincount++;
      delay(50);
    } else {
      win = 0;
    }
  }
  if (wincount < 7) {
    for (int i = 0; i < 6; i++) {
      sensorStatus[i] = digitalRead(IRSensor[i]);
      if (sensorStatus[i] != previousState[i]) {
        if (sensorStatus[i] == 1)  // Check if the pin high or not
        {

          noTone(8);  // LED LOW
          // Serial.println("Motion 1 Detected!");
        } else {
          tone(8, tonefreq[i]);
          Serial.println("Motion");
          entryList[count] = i;
          Serial.println("list data");
          Serial.println(entryList[count]);
          Serial.println(count);
          count++;
          if (count == 7) {
            count = 0;
           
          } 
        }
        previousState[i] = sensorStatus[i];
      }
    }
     int entryList[] = { 0, 0, 0, 0, 0, 0, 0 };
    wincount = 0;
  } else {
    Serial.println("Won");
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    noTone(8);
  }
}
