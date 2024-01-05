#include <Wire.h> 
#include <Keypad.h>

#define Password_Length 5 

int signalPin = 12;

char Data[Password_Length]; 
char Master[Password_Length] = "789C"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 

void setup(){
  Serial.begin(9600);
  pinMode(signalPin, OUTPUT);
}

void loop(){
  Serial.println("Enter Password:");

  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey;  
    Serial.println(Data[data_count]); 
    data_count++; 
    }

  if(data_count == Password_Length-1){

    if(!strcmp(Data, Master)){
      Serial.println("Correct");
      digitalWrite(signalPin, HIGH); 
      delay(5000);
      digitalWrite(signalPin, LOW);
      
      }
    else{
      Serial.println("Incorrect");
      delay(1000);
      }
    
    clearData();  
  }
  delay(2000);
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}

