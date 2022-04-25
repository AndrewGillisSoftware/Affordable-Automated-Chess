#include <Stepper.h>
#include <Servo.h>

#define LONG 0
#define SHORT 1
#define BLACK 1
#define WHITE 0
#define UNKNOWN_POS -1

const int stepsPerRevolution = 2048;
// Wiring:
// Pin 10 to IN1, Pin 11 to IN2, Pin 12 to IN3, Pin 13 to IN4
int StepperPins[2][4] = {{6, 7, 8, 9}, {10, 11, 12, 13}};

const int endEffectPin = 3;

const int limitSwitchPins[] = {5, 22};

const long int axisRangeMaxSteps[] = {18000, 11700};

const int axisNormal[] = {1,-1};

Servo myservo; 

int GLOBAL_POS[] = {UNKNOWN_POS, UNKNOWN_POS};

Stepper steppers [] = {Stepper(stepsPerRevolution, StepperPins[LONG][0], StepperPins[LONG][2], StepperPins[LONG][1], StepperPins[LONG][3]),
                       Stepper(stepsPerRevolution, StepperPins[SHORT][0], StepperPins[SHORT][2], StepperPins[SHORT][1], StepperPins[SHORT][3])};
void setup() {
  myservo.attach(endEffectPin);
  dropPiece();
  grabPiece(BLACK);
  pinMode(limitSwitchPins[LONG], INPUT); 
  pinMode(limitSwitchPins[SHORT], INPUT); 
  steppers[SHORT].setSpeed(10);
  steppers[LONG].setSpeed(10);
  // put your setup code here, to run once:
  homeAxis(LONG);
  homeAxis(SHORT);
  goToXY(18000,11700);
}

void homeAxis(int axis)
{
  //While Limit Switch is open
  while(digitalRead(limitSwitchPins[axis]) == HIGH)
  {
    steppers[axis].step(axisNormal[axis]);
    delay(1); 
  }

  GLOBAL_POS[axis] = 0;
}

void goToXY(int longAxisPos, int shortAxisPos)
{
  steppers[LONG].step(abs(GLOBAL_POS[LONG] - longAxisPos)*(axisNormal[LONG]*-1));
  steppers[SHORT].step(abs(GLOBAL_POS[SHORT] - shortAxisPos)*(axisNormal[SHORT]*-1));
}

void grabPiece(int color)
{
  if(color == WHITE)
  {
    myservo.write(0);
  }
  else
  {
    myservo.write(180); 
  }
}

void dropPiece()
{
  myservo.write(90);
}

void loop() {

}
