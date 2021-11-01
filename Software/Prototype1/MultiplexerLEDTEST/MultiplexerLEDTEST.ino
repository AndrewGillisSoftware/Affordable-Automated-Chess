
#define LED_COUNT 8
bool LEDStatus[LED_COUNT] = {true,false,true,false,true,false,true,false};

int pinINH = 7;
int pinCOM_IN = 6;

int pinA = 8;
int pinB = 9;
int pinC = 10;

int waitLED = 1;

void select(int LED_ID)
{
  switch(LED_ID)
  {
    case 0:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      break;
    case 1:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      break;
    case 2:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, LOW);
      break;
    case 3:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, LOW);
      break;
    case 4:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      break;
    case 5:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      break;
    case 6:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      break;
    case 7:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      break;
    default:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      break;
  }
}

void setup() 
{
   Serial.begin(9600);
   pinMode(pinINH, OUTPUT);
   pinMode(pinCOM_IN, OUTPUT);
   pinMode(pinA, OUTPUT);
   pinMode(pinB, OUTPUT);
   pinMode(pinC, OUTPUT);

   digitalWrite(pinINH, LOW);
   digitalWrite(pinCOM_IN, HIGH);
}

void loop() 
{
  for(int i = 0; i < LED_COUNT; i++)
  {
    if(LEDStatus[i])
    {
      digitalWrite(pinCOM_IN, HIGH);
      select(i);
    }
    delay(waitLED);
    digitalWrite(pinCOM_IN, LOW);
  }
}
