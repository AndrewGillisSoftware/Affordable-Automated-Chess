/* Example sketch to control a 28BYJ-48 stepper motor with ULN2003 driver board and Arduino UNO. More info: https://www.makerguides.com */
// Include the Arduino Stepper.h library:
#include <Stepper.h>
#include <Servo.h>
#include "Chess.c"
#include "PinsAndPosOffsets.c"

int GLOBAL_POS = UNKNOWN_POS;

//WIRING and OFFSETS!
const int stepsPerRevolution = 2048;
// Pin 8 to IN1, Pin 9 to IN2, Pin 10 to IN3, Pin 11 to IN4
const int stepPinOne = 8;
const int stepPinTwo = 10;
const int stepPinThree = 9;
const int stepPinFour = 11;

const int limitSwitchPin = 4;
const int closeHallSensorPin = 6;
const int farHallSensorPin = 7;

const int axisRangeMaxSteps = 11700;
const int stepsPerTile = 1450;
const int startSensorPos = 129;
const int startElectroMagPos = 650;

Stepper stepper = Stepper(stepsPerRevolution, stepPinOne, stepPinTwo, stepPinThree, stepPinFour);
Servo magnetServo;

String commandBuffer;

void setup() {
  magnetServo.attach(5);
  dropPiece();
  stepper.setSpeed(20);
  pinMode(closeHallSensorPin,INPUT);
  pinMode(farHallSensorPin,INPUT);
  
  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);

  struct Board board;

  initBoard(&board);

  scanBoard(&board);

  printBoard(&board);

  /*
  goToTile(0 , false);
  delay(500);
  goToTile(3 , false);
  delay(500);
  goToTile(4 , true);
  delay(500);
  goToTile(5 , true);
  */
  
}

void homeAxis()
{
  //While Limit Switch is open
  while(digitalRead(limitSwitchPin) == HIGH)
  {
    stepper.step(1);
    delay(1); 
  }

  GLOBAL_POS = 0;
}

void grabPiece()
{
  magnetServo.write(70);
}

void dropPiece()
{
  for(int i = 71; i <= 170; i++)
  {
    magnetServo.write(i);
    delay(100);
  }
}

void homeSuckTile()
{
  homeAxis();
  goToTile(0, false);
}

void homeScanTile()
{
  homeAxis();
}

//returns true if success. 
bool goToGlobalPos(int pos)
{
  if(pos < 0 || pos > axisRangeMaxSteps)
  {
    return false;
  }

  //Is Device NOT Homed?
  if(GLOBAL_POS == UNKNOWN_POS)
  {
    //Not Homed so Home
    homeAxis();
  }

  //Walk to Position
  if(GLOBAL_POS > pos)
  {
    stepper.step((-(GLOBAL_POS - pos))*-1);
  }
  else
  {
    stepper.step((pos - GLOBAL_POS)*-1);
  }

  //Set the New Position
  GLOBAL_POS = pos;
  return true;
}

//tile 0-7
int scanTile(int tile)
{
  //Move to Tile
  int tilePos = startSensorPos + (tile * stepsPerTile);
  
  goToGlobalPos(tilePos);

  //Scan
  return (digitalRead(closeHallSensorPin) + digitalRead(farHallSensorPin));
}

bool scanBoard(struct Board *board)
{
  if(board == NULL)
  {
    return false;
  }
  
  for(int i = 0; i < NUM_OF_SPACES; i++)
  {
    board->tiles[i] = scanTile(i);
    delay(100);
  }

  return true;
}

void printBoard(struct Board *board)
{
  Serial.print("|L|");
  for(int i = 0; i < NUM_OF_SPACES; i++)
  {
    if(board->tiles[i] == BLACK_PIECE)
    {
      Serial.print("B|");
    }
    else if(board->tiles[i] == WHITE_PIECE)
    {
      Serial.print("W|");
    }
    else
    {
      Serial.print(" |");
    }
  }
  Serial.println("");
}

bool goToTile(int tile, bool suck)
{
  //Bad Parameters
  if(tile < 0 || tile > NUM_OF_SPACES)
  {
    return false;
  }
  
  //Turn on Electromagnet
  if(suck)
  {
    grabPiece();
  }
  //Move to Tile
  int tilePos = startElectroMagPos + (tile * stepsPerTile);

  goToGlobalPos(tilePos);
 
  //Turn off Electromagnet
  dropPiece();

  //All Checks Passed
  return true;
}

void commandControl(String buffer)
{
   
}

void loop()
{
  Serial.println("Enter Command: ");
  while(Serial.available() == 0){}
  commandBuffer = Serial.readString();
  Serial.print(commandBuffer);
}
