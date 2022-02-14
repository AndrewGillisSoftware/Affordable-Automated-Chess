int hallSensorValues[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//Mux control pins
int s[] = {11,10,9,8};

//Mux in "SIG" pin
#define SIG_pin A0

void select(int ID)
{
  int selector = 1;

  for(int i = 0; i < 4; i++)
  {
    if(selector & ID)
    {
      digitalWrite(s[i], HIGH);
    }
    else
    {
      digitalWrite(s[i], LOW);
    }
    selector *= 2;
  }
}

void setup(){
  pinMode(s[0], OUTPUT); 
  pinMode(s[1], OUTPUT); 
  pinMode(s[2], OUTPUT); 
  pinMode(s[3], OUTPUT); 

  select(0);

  pinMode(SIG_pin, INPUT); // analog
  
  Serial.begin(9600);
}

void loop() 
{
  for(int i = 0; i < 16; i++)
  {
    select(i);
    delay(100);
    hallSensorValues[i] = analogRead(SIG_pin);
    Serial.print(hallSensorValues[i]);
    Serial.print(",");
  }
  Serial.println();
  delay(1000);
}
