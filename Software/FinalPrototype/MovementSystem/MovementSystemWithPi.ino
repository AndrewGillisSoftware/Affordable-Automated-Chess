#include <Stepper.h>
#include <Servo.h>
#include <Wire.h>

#define LONG 0
#define SHORT 1
#define BLACK 0
#define WHITE 1
#define UNKNOWN_POS -1

const int stepsPerRevolution = 2048;
// Wiring:
// Pin 10 to IN1, Pin 11 to IN2, Pin 12 to IN3, Pin 13 to IN4
int StepperPins[2][4] = {{6, 7, 8, 9}, {10, 11, 12 , 13}};

const int endEffectPin = 3;

const int limitSwitchPins[] = {5, 22};

const long int axisRangeMaxSteps[] = {18000, 11700};

const int axisNormal[] = {1,-1};

//For Start of Non Grave Yard Square Bottom Left
const int squareStartBound[] = {2800,0};
const int squareEndBound[] = {14500,11700};
const int squareSeperation = 1462;
const int speedAxis = 12;

Servo myservo; 

int GLOBAL_POS[] = {UNKNOWN_POS, UNKNOWN_POS};

Stepper steppers [] = {Stepper(stepsPerRevolution, StepperPins[LONG][0], StepperPins[LONG][2], StepperPins[LONG][1], StepperPins[LONG][3]),
                       Stepper(stepsPerRevolution, StepperPins[SHORT][0], StepperPins[SHORT][2], StepperPins[SHORT][1], StepperPins[SHORT][3])};

volatile boolean receiveFlag = false;
int temp[4];

int color = WHITE;
int turns = 0;

int readCounter = 0;
int readArray[4];

void setup() {
  Serial.begin(9600);
  myservo.attach(endEffectPin);
  pinMode(limitSwitchPins[LONG], INPUT); 
  pinMode(limitSwitchPins[SHORT], INPUT); 
  steppers[SHORT].setSpeed(speedAxis);
  steppers[LONG].setSpeed(speedAxis);

  calibrate();

  //Join I2C Bus
  Wire.begin(0x8);

  Wire.onReceive(receiveEvent);
}

void receiveEvent(int numBytes){
  //spits out first byte (command byte)
  Wire.read();
  
  //reads in 4 move bytes as integers (might need to change casting)
  for(int i=0; i<4; i++){
    temp[i] = Wire.read();
  }

  for(int i=0; i<4; i++){
    Serial.println(temp[i]);
  }
  //Start board movement
  receiveFlag = true;
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

void calibrate()
{
  dropPiece(WHITE);
  homeAxis(LONG);
  homeAxis(SHORT);
}

void goToXY(int longAxisPos, int shortAxisPos)
{
  steppers[LONG].step((longAxisPos - GLOBAL_POS[LONG])*(axisNormal[LONG]*-1));
  steppers[SHORT].step((shortAxisPos - GLOBAL_POS[SHORT])*(axisNormal[SHORT]*-1));
  
  GLOBAL_POS[LONG] = longAxisPos;
  GLOBAL_POS[SHORT] = shortAxisPos;
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

void dropPiece(int color)
{
  if(color == WHITE)
  {
    goToXY(GLOBAL_POS[LONG],GLOBAL_POS[SHORT] + (squareSeperation / 2));
  }
  else
  {
    goToXY(GLOBAL_POS[LONG],GLOBAL_POS[SHORT] - (squareSeperation / 2));
  }
  myservo.write(90);
}

void goToSquare(int pX, int pY)
{
  int x = squareStartBound[LONG] + (squareSeperation / 2) + (squareSeperation * pX);
  int y = squareStartBound[SHORT] + (squareSeperation / 2) + (squareSeperation * pY);
  goToXY(x,y);
}

void loop() {
  //On Receive Move From PI, Move to that location on board
  if(receiveFlag == true){
    if(temp[0] == 14){
      color = BLACK;
    }
    else if(temp[0] == 13){
      color = WHITE;
    }
    else{
      goToSquare(temp[0], temp[1]);
      grabPiece(WHITE);
      goToSquare(temp[2], temp[3]);
      dropPiece(WHITE);
      turns += 1;
      receiveFlag = false;
    }
  }
  if((color == WHITE && turns%2 == 0) || (color == BLACK && turns%2 == 1)){
    if(Serial.available() > 0){
      int incomingByte = Serial.read();
      readArray[readCounter] = incomingByte;
      readCounter++;
      if(readCounter > 3){
        readCounter = 0;
        Wire.write(readArray,4)
      }
    }
  }
}
