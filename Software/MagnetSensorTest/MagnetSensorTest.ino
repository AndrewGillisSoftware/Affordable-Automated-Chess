int closeHallSensorPin = 6; // select the input pin
int farHallSensorPin = 7; // select the input pin
const int electroMagPin = 13;
int stateClose = 0;
int stateFar = 0;

void setup () {
Serial.begin (9600);
pinMode(closeHallSensorPin,INPUT);
pinMode(farHallSensorPin,INPUT);
 pinMode(electroMagPin,OUTPUT);
}

/*
void loop () {
stateClose = digitalRead(closeHallSensorPin);
stateFar = digitalRead(farHallSensorPin);
delay (100);
Serial.println (stateClose + stateFar, DEC);

}
*/
void loop()
{
   delay(1000);
   digitalWrite(electroMagPin, LOW);
   delay(1000);
   digitalWrite(electroMagPin, LOW);
}
