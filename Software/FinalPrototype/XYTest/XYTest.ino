#include <Stepper.h>
#include <Servo.h>

#define LONG 0
#define SHORT 1
#define UNKNOWN_POS -1

const int stepsPerRevolution = 2048;
// Wiring:
// Pin 10 to IN1, Pin 11 to IN2, Pin 12 to IN3, Pin 13 to IN4
int StepperPins[2][4] = {{10,11,12,13}, {5,6,7,8}};

const int endEffectPin = 9;

const int limitSwitchPins[] = {3, 2};

const int axisRangeMaxSteps[] = {15000, 117000};

int GLOBAL_POS[] = {UNKNOWN_POS, UNKNOWN_POS};

Stepper steppers [] = {Stepper(stepsPerRevolution, StepperPins[LONG][0], StepperPins[LONG][2], StepperPins[LONG][1], StepperPins[LONG][3]),
                       Stepper(stepsPerRevolution, StepperPins[SHORT][0], StepperPins[SHORT][2], StepperPins[SHORT][1], StepperPins[SHORT][3])};

void setup() {
  steppers[SHORT].setSpeed(10);
  steppers[LONG].setSpeed(10);
  // put your setup code here, to run once:
  homeAxis(LONG);
  homeAxis(SHORT);
  steppers[].step(axisRangeMaxSteps[SHORT]*-1);
  steppers[LONG].step(axisRangeMaxSteps[LONG]*-1);
}

void homeAxis(int axis)
{
  //While Limit Switch is open
  while(digitalRead(limitSwitchPins[axis]) == HIGH)
  {
    steppers[axis].step(1);
    delay(1); 
  }

  GLOBAL_POS[axis] = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

}
