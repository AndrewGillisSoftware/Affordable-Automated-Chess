#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

const int stepsPerRevolution = 2048;
// Wiring:
// Pin 8 to IN1, Pin 9 to IN2, Pin 10 to IN3, Pin 11 to IN4
const int stepPinOne = 8;
const int stepPinTwo = 10;
const int stepPinThree = 9;
const int stepPinFour = 11;

const int closeHallSensorPin = 2;
const int farHallSensorPin = 3;
const int limitSwitchPin = 4;

const int axisRangeMaxSteps = 11700;
const int stepsPerTile = 1450;
const int startSensorPos = 129;
const int startElectroMagPos = 650;

#endif
