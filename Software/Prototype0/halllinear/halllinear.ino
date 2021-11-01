const int pinHall = A0; 

void setup() {
  pinMode(pinHall, INPUT);
  Serial.begin(9600);
} 
void loop() {
  //we measure 10 times adn make the mean
  long measure = 0;
  for(int i = 0; i < 10; i++){
      int value = 
      measure += analogRead(pinHall);
  }
  measure /= 10;  
  //voltage in mV
  float outputV = measure * 5000.0 / 1023;
//  Serial.print("Output Voltaje = ");
//  Serial.print(outputV);
 // Serial.print(" mV   \n");

  /*
  if(outputV > 2600)
  {
    if(outputV > 3400)
    {
      Serial.print("Black\n");
    }
    else
    {
      Serial.print("White\n");
    }
  }
  else
  {
    Serial.print("Empty\n");
  }
  */

  if(2400 < outputV && outputV < 2600)
  {
    Serial.print("Empty\n");
  }
  else
  {
    if(2600 <= outputV)
    {
      Serial.print("Black\n");
    }
    else
    {
      Serial.print("White\n");
    }
  }
  
  delay(100);
}
