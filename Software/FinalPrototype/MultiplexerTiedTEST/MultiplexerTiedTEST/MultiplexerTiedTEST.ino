int hallSensorValues[] = {0,0};
int LEDValues[] = {1,0};

//Mux control pins
int s[] = {8,9,10,11};

//Mux in "SIG" pin
#define SIG_pin A0
#define LEDTrigger_pin 7
#define EnableLED 4
#define EnableHALL 3

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
  pinMode(LEDTrigger_pin, OUTPUT);
  pinMode(EnableLED, OUTPUT);
  digitalWrite(EnableLED, LOW);
  pinMode(EnableHALL, OUTPUT);
  digitalWrite(EnableHALL, LOW);
  digitalWrite(LEDTrigger_pin, LOW);
  
  Serial.begin(9600);
}

void loop() 
{
  for(int i = 0; i < 16; i++)
  {
    digitalWrite(LEDTrigger_pin, LOW);
    //Select
    select(i);
    //Hall
    hallSensorValues[i%2] = analogRead(SIG_pin);
    Serial.print(hallSensorValues[i%2]);
    Serial.print(",");

    if(LEDValues[i%2])
    {
      digitalWrite(LEDTrigger_pin, HIGH);
    }

    delay(1);
  }
  Serial.println();
}
