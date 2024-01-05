  //Room temp monitor
  //austin j nilavoor
  
  // include the library code:
#include <LiquidCrystal.h>

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};
  // Define the A0 pin as “sensor”
#define tempSensor 0
  // Variable to read the value from the Arduino’s pin A0
  int Vin;
  // Variable that receives the converted voltage value to ºCtemperature
  float TC;
  
  // initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  lcd.createChar(1, smiley);
  lcd.begin(16, 2);
  lcd.print(" ");
  lcd.write(byte( 1));
  lcd.print(" Christo J ");
  lcd.write(byte(1));
  lcd.setCursor(0, 1);
  lcd.print("temp = ");
}

void loop() {
  /* Tells the Arduino to read A0 and stores the value in “Vin” */
  Vin = analogRead (tempSensor);
  /* Converts the voltage value into temperature and stores it into the “TC” variable (in ºC)*/
  TC=(500.0*Vin)/1023.0;
  // Moves the cursor of the display to the next line
  lcd.setCursor(8, 1);
  // Exhibits the value of the temperature on the display
  lcd.print(TC);
   //degree symbol
  lcd.print((char)223);
  // Writes “C” to indicate that it is in Fahrenheit scale
  lcd.print("C ");
  // Waits for one second to read the sensor pin again
  delay(1000);
  
 }
