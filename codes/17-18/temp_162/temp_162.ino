  //Room temp monitor
  //austin j nilavoor
  
  // include the library code:
#include <LiquidCrystal.h>
  // Define the A0 pin as “sensor”
#define tempSensor 0
  // Variable to read the value from the Arduino’s pin A0
  int Vin;
  // Variable that receives the converted voltage value to ºCtemperature
  float TC;
  // Variable to receive the converted value from ºC to ºF
  float TF;
  
  // initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("  temperature");
}

void loop() {
  /* Tells the Arduino to read A0 and stores the value in “Vin” */
  Vin = analogRead (tempSensor);
  /* Converts the voltage value into temperature and stores it into the “TC” variable (in ºC)*/
  TC=(500.0*Vin)/1023.0;
  // Moves the cursor of the display to the next line
  lcd.setCursor(0, 1);
  // Exhibits the value of the temperature on the display
  lcd.print(TC);
   //degree symbol
  lcd.print((char)223);
  // Writes “C” to indicate that it is in Fahrenheit scale
  lcd.print("C ");
  // Exhibits the value of the temperature on the display
  lcd.print(TF);
  //degree symbol
  lcd.print((char)223);
  // Writes “F” to indicate that it is in Fahrenheit scale
  lcd.print("F");
  // Waits for one second to read the sensor pin again
  delay(1000);
 }
