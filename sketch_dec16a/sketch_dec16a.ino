//Mux control pins
int s0 = 8;
int s1 = 9;
int s2 = 10;
int s3 = 11;

int sig = 12;

int speed = 1;

void setup(){
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  pinMode(sig, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);

  digitalWrite(sig, HIGH);

  Serial.begin(9600);
}

void loop(){
  //Loop through and read all 16 values
  for(int i = 0; i < 16; i ++){
    if (i % 2 == 0) {
      writeMux(i);
      delay(speed);
    }
  }
}


// Convert channel into binary and extract each binary digit 
// Write one binary digit per board pin 
void writeMux(int channel){
  digitalWrite(s0, channel & 0b0001);
  digitalWrite(s1, (channel & 0b0010) >> 1);
  digitalWrite(s2, (channel & 0b0100) >> 2); 
  digitalWrite(s3, (channel & 0b1000) >> 3);
  
  return;
}
