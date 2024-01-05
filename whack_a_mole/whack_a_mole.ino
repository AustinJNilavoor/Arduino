#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

long randNumber;
int step_counter = 0;
// int button_values[] = {1003,801,599,398,198};
int button_values[] = {913, 429, 267, 179, 110};
int button_values2[] = {913, 429, 267, 179, 110};
int btn_tol = 10;
int analogValue1 = 0;
int analogValue2 = 0;
int pin_p1 = A0;
int pin_p2 = A2;
int leds_cnt = 5;
int p1_leds[5] = {2,3,4,5,6};
int p2_leds[5] = {7,8,9,10,11};
int p1_score = 0;
int p2_score = 0;
int action_speed = 2000;
int action_speed_min = 250;

void setup()
{
  Serial.begin(9600); 

  randomSeed(analogRead(A3));
  
  pinMode(pin_p1, INPUT);
  pinMode(pin_p2, INPUT);

  for (int i = 0; leds_cnt > i; i++) {
    pinMode(p1_leds[i], OUTPUT);
  }
  for (int i = 0; leds_cnt > i; i++) {
    pinMode(p2_leds[i], OUTPUT);
  }  

  lcd.begin();
  lcd.clear();         
  lcd.backlight();
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Player1 : ");
  
  lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print("Player2 : ");

}

void loop()
{
  if(p1_score < 100 and p2_score < 100) {
    
    step_counter++;
    bool step_action = false;
    if (step_counter > action_speed) {
      step_counter = 0;
      step_action = true;  
      action_speed = action_speed - round(action_speed/50);
      if (action_speed < action_speed_min) {
        action_speed = action_speed_min;
      }
      Serial.println(action_speed);
    }
  
    if (step_action) {
      int pin_light = random(0,5);
      Serial.println(pin_light);
      digitalWrite(p1_leds[pin_light], HIGH);
      digitalWrite(p2_leds[pin_light], HIGH);
      
    }
  
    analogValue1 = analogRead(pin_p1);
    for (int i = 0; leds_cnt > i; i++) {
      if ( analogValue1 < button_values[i] + btn_tol and analogValue1 > button_values[i] - btn_tol ){
        if(digitalRead(p1_leds[i]) == HIGH){
          digitalWrite(p1_leds[i], LOW);
          p1_score++;
        }
      }
    }
  
    analogValue2 = analogRead(pin_p2);
    for (int i = 0; leds_cnt > i; i++) {
      if ( analogValue2 < button_values[i] + btn_tol and analogValue2 > button_values[i] - btn_tol ){
        if(digitalRead(p2_leds[i]) == HIGH){
          digitalWrite(p2_leds[i], LOW);
          p2_score++;
        }
      }
    }
  
    if ( step_counter % 100 == 0){
      Serial.println(p1_score);
      lcd.setCursor(11,0);   //Set cursor to character 2 on line 0
      lcd.print(p1_score);
  
      Serial.println(p2_score);
      lcd.setCursor(11,1);   //Set cursor to character 2 on line 0
  lcd.print(p2_score);
  
    }
  } else {
    if (p1_score > p2_score) {
      Serial.println("P1 win");
      lcd.clear();
      lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
      lcd.print("Player1 wins");
      delay(100000);
    } else {
      Serial.println("Player2_Win");
      lcd.clear();
      lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
      lcd.print("P2 wins");
      delay(100000);      
    }       
  }
}