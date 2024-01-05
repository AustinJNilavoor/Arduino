int red = 2;       // LOW = on, HIGH = off
int green = 10;    // LOW = on, HIGH = off
int blue = 11;     // LOW = on, HIGH = off

char cmd[100];
int cmdIndex;


void exeCmd() {
  
  if( (cmd[0]=='r' || cmd[0]=='g' || cmd[0]=='b') && cmd[1]==' ' ) { 
    // "r", "g", "b" are the ids for red, green and blue    
       int val = 0;
       for(int i=2; cmd[i]!=0; i++) {
         val = val*10 + (cmd[i]-'0');
       }
       // if cmd is "r 100", val will be 100        
       if(cmd[0]=='r') analogWrite(red, 255-val);
  } 

  
}



void setup() {
  
  delay(500); // wait for bluetooth module to start

  bluetooth.begin(115200); // Bluetooth default baud is 115200
  
  pinMode(red, OUTPUT);
  
  digitalWrite(red, HIGH);  // off
  
  cmdIndex = 0;
}


void loop() {
  
  if(bluetooth.available()) {
    
    char c = (char)bluetooth.read();
    
    if(c=='\n') {
      cmd[cmdIndex] = 0;
      exeCmd();  // execute the command
      cmdIndex = 0; // reset the cmdIndex
    } else {      
      cmd[cmdIndex] = c;
      if(cmdIndex<99) cmdIndex++;
    }
   
    
  }
  
}
