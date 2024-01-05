
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
}

void loop() {
  // set the cursor to (0,0):
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("Austin");
  // set the cursor to (16,1):
  lcd.setCursor(10, 16);
  // Print a message to the LCD.
  lcd.print("Austin");
    // Turn off the display:
  lcd.noDisplay();
  delay(750);
  // Turn on the display:
  lcd.display();
  delay(750);
  lcd.clear();
  
   // set the cursor to (0,0):
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("   J");
  // set the cursor to (16,1):
  lcd.setCursor(10, 16);
  // Print a message to the LCD.
  lcd.print("  J");
    // Turn off the display:
  lcd.noDisplay();
  delay(750);
  // Turn on the display:
  lcd.display();
  delay(750);
  lcd.clear();
  
   // set the cursor to (0,0):
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("Nilavoor");
  // set the cursor to (16,1):
  lcd.setCursor(8, 16);
  // Print a message to the LCD.
  lcd.print("Nilavoor");
    // Turn off the display:
  lcd.noDisplay();
  delay(750);
  // Turn on the display:
  lcd.display();
  delay(750);
  lcd.clear();
}
