/* Example sketch to control a 28BYJ-48 stepper motor with ULN2003 driver board and Arduino UNO. More info: https://www.makerguides.com */
// Include the Arduino Stepper.h library:
#include <Stepper.h>
const int stepsPerRevolution = 2048;
// Wiring:
// Pin 8 to IN1, Pin 9 to IN2, Pin 10 to IN3, Pin 11 to IN4
Stepper stepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
const int limitSwitchPin = 4;

const int axisRangeMaxSteps = 11700;
const int stepsPerTile = 1351;
const int startSensorPos = 0;
const int startElectroMagPos = 1190;

void setup() {
  stepper.setSpeed(10);
  pinMode(limitSwitchPin,INPUT);
  
  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);

  homeAxis();
  stepper.step(-axisRangeMaxSteps);
}

void homeAxis()
{
  //While Limit Switch is open
  while(digitalRead(limitSwitchPin) == HIGH)
  {
    stepper.step(1);
    delay(1); 
  }
}

//Returns 0 for Nothing. 1 for White. 2 for Black
//tile 0-7
int scanTile(int tile)
{
  
}


void loop()
{
  if(digitalRead(limitSwitchPin) == LOW) 
  {
    Serial.println("door is closed"); 
    delay(20); 
  }
  
   if(digitalRead(limitSwitchPin) == HIGH) 
   {
    Serial.println("door is opened"); 
    delay(20); 
  }
}
