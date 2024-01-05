#include <LiquidCrystal.h>
#include <dht11.h>
#define DHT11PIN 13
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

dht11 DHT11;

byte degree_symbol[8] = 
              {
                0b00111,
                0b00101,
                0b00111,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };

void setup() { 
  lcd.begin(16, 2);
  lcd.print("Temp = ");
  lcd.setCursor(0,1);
  lcd.print("Humidity = ");
  lcd.createChar(1, degree_symbol);
  lcd.setCursor(12,0);
  lcd.write(1);
  lcd.print("C");
  lcd.setCursor(13,1);
  lcd.print("%");
}

void loop() {
  delay(500);
  int chk = DHT11.read(DHT11PIN);
  lcd.setCursor(7, 0);
  lcd.print((float)DHT11.temperature, 2);
  lcd.setCursor(11, 1);
  lcd.print((float)DHT11.humidity, 2);
 }
