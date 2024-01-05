#include <Wire.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);

void timerInterrupt();

const float Low_BAT_level = 2.80;
const int BAT_Pin = A1;
const byte Switch_Pin = 3;
const byte Trimpot_Pin = 2;
unsigned long Capacity;
float Capacity_f;
float Vcc = 5.00;
float BAT_Voltage = 0;
float sample = 0;
byte Hour = 0, Minute = 0, Second = 0;
bool initial = true, Done = false;


void setup() {
  pinMode(Switch_Pin, INPUT);
  pinMode(Trimpot_Pin, OUTPUT);
  digitalWrite(Trimpot_Pin, LOW);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(16, 20);
  display.print("Li-ion battery");
  display.setCursor(12, 40);
  display.print("Capacity Tester");
  display.display();
  delay(2000);
}

void loop() {
  if (initial) {
    BAT_Voltage = analogRead(BAT_Pin) * Vcc / 1024.0;
    display.clearDisplay();
    display.setCursor(16, 10);
    display.print("Battery Voltage");
    display.setCursor(12, 30);
    display.print(BAT_Voltage);
    display.print("V");
    display.setCursor(16, 50);
    display.print("Press Start!!");
    display.display();
  }

  if (digitalRead(Switch_Pin) == LOW) {
    digitalWrite(Trimpot_Pin, HIGH);
    timerInterrupt();
    initial = false;
  }
}

void timerInterrupt() {

  while (Done == false) {  //(Done == false)
    Second++;
    if (Second == 60) {
      Second = 0;
      Minute++;
    }
    if (Minute == 60) {
      Minute = 0;
      Hour++;
    }

    //************ Measuring Battery Voltage ***********

    for (int i = 0; i < 100; i++) {
      sample = sample + analogRead(BAT_Pin);  //read the Battery voltage
      delay(2);
    }
    sample = sample / 100;
    BAT_Voltage = sample * Vcc / 1024.0;
    //*********************************************

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(20, 5);
    // display.print(String(Hour) + ":" + String(Minute) + ":" + String(Second));
    display.print(Hour);
    display.print(":");
    display.print(Minute);
    display.print(":");
    display.print(Second);

    display.setTextSize(1);

    display.setCursor(2, 40);
    // display.print("Bat Volt:" + String(BAT_Voltage)+"V" );
    display.print("Bat Volt:");
    display.print(BAT_Voltage, 3);
    display.print("V");

    // When total seconds is greater than 32767 the statement below did not work until the byte values
    // Hour, Minute and Second were cast to an unsigned long. Apparently the compiler cast the byte
    // values to an "int" first which cannot represent 32768 correctly
    Capacity = ((unsigned long)Hour * 3600) + ((unsigned long)Minute * 60) + (unsigned long)Second;
    Capacity_f = ((float)Capacity * 1000) / 3600.0;

    display.setCursor(2, 55);
    // display.print("Capacity:" + String(Capacity) + "mAh");
    display.print("Capacity:");
    display.print(Capacity_f, 1);
    display.print("mAh");
    display.display();

    if (BAT_Voltage < Low_BAT_level) {  //BAT_Voltage < Low_BAT_level


      // When total seconds is greater than 32767 the statement below did not work until the byte values
      // Hour, Minute and Second were cast to an unsigned long. Apparently the compiler cast the byte
      // values to an "int" first which cannot represent 32768 correctly
      Capacity = ((unsigned long)Hour * 3600) + ((unsigned long)Minute * 60) + (unsigned long)Second;



      Capacity_f = ((float)Capacity * 1000) / 3600.0;



      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(2, 15);
      display.print("Capacity:");
      display.setCursor(2, 40);
      display.print(Capacity_f, 1);
      display.print("mAh");
      display.display();
      Done = true;
      digitalWrite(Trimpot_Pin, LOW);
    }
    delay(1000);
  }
}