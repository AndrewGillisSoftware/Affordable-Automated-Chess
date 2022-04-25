#include <Stepper.h>
#include <Servo.h>

#define LONG 0
#define SHORT 1
#define BLACK 0
#define WHITE 1
#define UNKNOWN_POS -1

const int stepsPerRevolution = 2048;
// Wiring:
// Pin 10 to IN1, Pin 11 to IN2, Pin 12 to IN3, Pin 13 to IN4
int StepperPins[2][4] = {{6, 7, 8, 9}, {10, 11, 12, 13}};

//0 is Black, 1 is White, 2 is empty
int board[8][8] = {{0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {2,2,2,2,2,2,2,2},
                   {2,2,2,2,2,2,2,2},
                   {2,2,2,2,2,2,2,2},
                   {2,2,2,2,2,2,2,2},
                   {1,1,1,1,1,1,1,1},
                   {1,1,1,1,1,1,1,1}};

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
void setup() {
  myservo.attach(endEffectPin);
  pinMode(limitSwitchPins[LONG], INPUT); 
  pinMode(limitSwitchPins[SHORT], INPUT); 
  steppers[SHORT].setSpeed(speedAxis);
  steppers[LONG].setSpeed(speedAxis);

  int xM[] = {3,3,6,6,5,5,6,5,2,2,7,7,3,3,7,7};
  int yM[] = {1,3,6,4,1,3,7,5,1,2,6,5,0,1,7,5};
  playGame(xM,yM, 16);
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
  dropPiece();
  homeAxis(LONG);
  homeAxis(SHORT);
}

void goToXY(int longAxisPos, int shortAxisPos)
{
  steppers[SHORT].step(abs(GLOBAL_POS[SHORT] - shortAxisPos)*(axisNormal[SHORT]*-1));
  steppers[LONG].step(abs(GLOBAL_POS[LONG] - longAxisPos)*(axisNormal[LONG]*-1));
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

void dropPiece()
{
  goToXY(GLOBAL_POS[LONG],GLOBAL_POS[SHORT]+(squareSeperation / 2));
  myservo.write(90);
}

void goToSquare(int pX, int pY)
{
  int x = squareStartBound[LONG] + (squareSeperation / 2) + (squareSeperation * pX);
  int y = squareStartBound[SHORT] + (squareSeperation / 2) + (squareSeperation * pY);
  goToXY(x,y);
}

void playGame(int x[],int y[], int moves)
{
  calibrate();
  for(int i = 0; i < moves;)
  {
    int color = board[x[i]][y[i]];
    goToSquare(x[i],y[i]);
    grabPiece(color);
    goToSquare(x[i+1],y[i+1]);
    dropPiece();
    board[x[i]][y[i]] = 2;
    board[x[i+1]][y[i+1]] = color;
    i+=2;
  }
}


void loop() {

}
