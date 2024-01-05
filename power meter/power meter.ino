#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);
Adafruit_INA219 ina219;

unsigned long previousMillis = 0;
unsigned long interval = 100;
float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float energy = 0;


void setup() {
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  ina219.begin();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    ina219values();

    displaydata();
  }
}

void displaydata() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(loadvoltage);
  display.setCursor(35, 0);
  display.println("V");
  display.setCursor(50, 0);
  display.println(current_mA);
  display.setCursor(95, 0);
  display.println("mA");
  display.setCursor(0, 10);
  display.println(loadvoltage * current_mA);
  display.setCursor(65, 10);
  display.println("mW");
  display.setTextSize(2);
  display.setCursor(0, 30);
  display.println(energy);
  display.setTextSize(1);
  display.setCursor(108, 35);
  display.println("mWh");
  // display.setCursor(0, 30);
  // display.println(previousMillis/1000);
  display.setCursor(0, 50);
  display.println(previousMillis/1000);
  display.setCursor(50, 50);
  display.println("Sec");
  // display.setCursor(0, 50);
  // display.println((previousMillis/1000)/360);
  display.display();
}

void ina219values() {
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  energy = energy + loadvoltage * current_mA / 3600;
}




