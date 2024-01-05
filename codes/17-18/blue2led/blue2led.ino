/*
 created 13 July 2017
 by austin j nilavoor
 */
#define ledPin 2
#define led 4
int state = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}

void loop() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
 }

 if (state == '0') {
  digitalWrite(ledPin, LOW); // Turn LED OFF
  Serial.println("LED: ON"); // Send back, to the phone, the String "LED: ON"
  state = 0;
 }
  if (state == '1') {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED: OFF");
  state = 0;
 } 
  if (state == '2') {
  digitalWrite(led, LOW); // Turn LED OFF
  Serial.println("LED: ON"); // Send back, to the phone, the String "LED: ON"
  state = 0;
 }
  if (state == '3') {
  digitalWrite(led, HIGH);
  Serial.println("LED: OFF");
  state = 0;
 }
}

