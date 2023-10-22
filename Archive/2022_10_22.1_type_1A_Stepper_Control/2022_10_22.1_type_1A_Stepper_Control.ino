/*-------------------------------------------------------------------

   // 5 inch Stepper Motor Control
   //  Dallas Keck
   //  For use with type 1A Stepper control box
   //  ESP32 Based Controller

  --------------------------------------------------------------------*/

//PINS
//#define ANALOG_PIN_IN             A0  // Pin 2    Input from the current sensor
//
//const int limitSwitchPin  =       13;  // Pin 13  Limit Switch Pin
//const int manualSwitchStatePin =  12;  // Pin 12  Manual Override switch status
//const int stepPin =               14;  // Pin 11
//const int dirPin =                27;  // Pin 10
//const int reedRelayPin =          26;  // Pin 9
//const int greenLEDpin =           25;  // Pin 8  Green LED when gate open
//const int redLEDpin =             33;  // Pin 7  Red LED when gate is closed and there is power
//const int enablePin  =            32;  // Pin 6  Enable the A4988 driver

#define ANALOG_PIN_IN             36  // Pin 2    Input from the current sensor
const int limitSwitchPin  =       13;  // Pin 13  Limit Switch Pin
const int manualSwitchStatePin =  12;  // Pin 12  Manual Override switch status
const int stepPin =               33;  // Pin 11
const int dirPin =                32;  // Pin 10
//const int reedRelayPin =          26;  // Pin 9
const int greenLEDpin =           27;  // Pin 8  Green LED when gate open
const int redLEDpin =             26;  // Pin 7  Red LED when gate is closed and there is power
const int enablePin  =            25;  // Pin 6  Enable the A4988 driver

// Working Variables
int sensorIn =                    0;
int stepPosition =               99;

//Paramenters
const int waitTime =           250;
const int trigger =            150;   //A/D threshold from current sensor pin to determine tool-on condition
const int fullRunSteps =       2670;  //steps required between open and closed points
const int backSteps =          50;    //steps required to open switch after homing
const int stepsPerRevolution = 200;
const int delayTime =          750;   // hold time between steps lower=faster higher=slower
const int holdTime  =          1000;   // time to stablize each cycle (milliseconds)

//Status Flags
volatile bool manualState =               false;
volatile bool limitSwitchState =          false;
volatile bool gateCloseState =            false;
volatile bool gateOpenState =             false;

//Data
long toolRunTime = 0;
long toolTimer =   0;
int toolCycles =   0;

//------------------------------------------------------------------------------
void setup() {
  pinMode(ANALOG_PIN_IN, INPUT);
//  pinMode(reedRelayPin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);
  pinMode(redLEDpin, OUTPUT);
//  pinMode(reedRelayPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(limitSwitchPin, INPUT_PULLUP);
  pinMode(manualSwitchStatePin, INPUT_PULLUP);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  digitalWrite(greenLEDpin, HIGH);
  digitalWrite(redLEDpin, HIGH);
//  digitalWrite(reedRelayPin, LOW);
  digitalWrite(enablePin, HIGH);

  attachInterrupt ( digitalPinToInterrupt(limitSwitchPin), checkSwitchState, CHANGE);
  Serial.begin(115200);
}

//------------------------------------------------------------------------------
void checkSwitchState() {
  if (digitalRead(limitSwitchPin) == HIGH) {
    limitSwitchState = false;
    //gateCloseState = false;
     
  }

  else {
    limitSwitchState = true;
    gateOpenState = false;
    gateCloseState = true;
    digitalWrite(greenLEDpin, LOW);
    digitalWrite(redLEDpin, HIGH);
  }
}

//------------------------------------------------------------------------------
void homePosition() {

  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, HIGH);         //turn clockwise
  while (limitSwitchState == false) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayTime);
  }

  stepPosition = 0;
  gateCloseState = true;
  gateOpenState = false;
  digitalWrite(enablePin, HIGH);
  //delay(holdTime);
}

//------------------------------------------------------------------------------
void closeGate() {
  homePosition();
//  digitalWrite(reedRelayPin, LOW);
  digitalWrite(greenLEDpin, LOW);
  digitalWrite(redLEDpin, HIGH);
}

//------------------------------------------------------------------------------
void openGate() {

  digitalWrite(enablePin, LOW);

  if (digitalRead(limitSwitchPin) == HIGH) {
    homePosition();
  }
  digitalWrite(enablePin, LOW);
  //digitalWrite(reedRelayPin, LOW);

  digitalWrite(dirPin, LOW);       // turn counterClockwise
  for (stepPosition = 0; stepPosition < fullRunSteps; stepPosition++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayTime);
  }
  digitalWrite(enablePin, HIGH);
  gateOpenState = true;

//  digitalWrite(reedRelayPin, HIGH);
  digitalWrite(greenLEDpin, HIGH);
  digitalWrite(redLEDpin, LOW);
  digitalWrite(enablePin, HIGH);

}

//------------------------------------------------------------------------------
void printStat() {
  Serial.print(sensorIn);
  Serial.print("   ");
  Serial.print(stepPosition);
  Serial.print("   ");
  Serial.print(gateOpenState);
  Serial.print("   ");

  Serial.print(gateCloseState);
  Serial.print("   ");
  Serial.print(manualState);
  Serial.println("   ");


}

//------------------------------------------------------------------------------

void loop() {

  checkSwitchState();
  sensorIn = (analogRead(ANALOG_PIN_IN));

  printStat();


  //if ((sensorIn > trigger) || (manualState == true)) {
  if (sensorIn > trigger) {
    if (gateOpenState != true) {
      openGate();
     // stepPosition = 5555;
    }
  }


  //if (manualState == false) {
  if (sensorIn < trigger) {
    if (limitSwitchState != true) {
      closeGate();
      //stepPosition = 777;
      //  }
    }
  }

  printStat();
  delay(holdTime);
}
