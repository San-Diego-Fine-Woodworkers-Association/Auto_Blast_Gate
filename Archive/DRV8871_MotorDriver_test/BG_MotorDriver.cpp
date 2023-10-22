/*
  Name:    BG_MotorDriver.cpp
  Created: 12/23/2021 10:32:45 PM
  Author:  Lem Davis
*/

#include <Arduino.h>
#include "BG_VariableTypes.h"
#include "BG_MotorDriver.h"
#include "DebugPrint.h"
#include <Adafruit_MotorShield.h>

BG_MotorDriver::BG_MotorDriver()
{}

BG_MotorDriver_Adafruit_Shield::BG_MotorDriver_Adafruit_Shield() : BG_MotorDriver()
{
  _motorCount = 4;
  // Motor driver (H-bridge)
  _AFMS = Adafruit_MotorShield();
}

bool BG_MotorDriver_Adafruit_Shield::setup(int motorNum, int ignore, int ignore2, int ignore3)
{
  _actuatorMotor = _AFMS.getMotor(motorNum);
  if (_AFMS.begin())   // create with the default frequency 1.6KHz
    return true;
  return false;
}

void BG_MotorDriver_Adafruit_Shield::forward(int speed)
{
  _actuatorMotor->setSpeed(speed);
  _actuatorMotor->run(FORWARD);

}

void BG_MotorDriver_Adafruit_Shield::backward(int speed)
{
  _actuatorMotor->setSpeed(speed);
  _actuatorMotor->run(BACKWARD);
}

void BG_MotorDriver_Adafruit_Shield::brake()
{
  _actuatorMotor->run(RELEASE);
}

void BG_MotorDriver_Adafruit_Shield::release()
{
  _actuatorMotor->run(RELEASE);
}

BG_MotorDriver_6612::BG_MotorDriver_6612() : BG_MotorDriver()
{
  _motorCount = 2;
}

bool BG_MotorDriver_6612::setup(int in1, int in2, int pwm, int stbyPin)
{
  _in1 = in1;
  _in2 = in2;
  _pwm = pwm;
  _stbyPin = stbyPin;
  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
  pinMode(_pwm, OUTPUT);
  pinMode(_stbyPin, OUTPUT);
  return true;
}

void BG_MotorDriver_6612::forward(int speed)
{
  digitalWrite(_stbyPin, HIGH);   // Enable (turn off standby)
  digitalWrite(_in1, HIGH);
  digitalWrite(_in2, LOW);
  analogWrite(_pwm, speed);
}

void BG_MotorDriver_6612::backward(int speed)
{
  digitalWrite(_stbyPin, HIGH);   // Enable (turn off standby)
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, HIGH);
  analogWrite(_pwm, speed);
}

void BG_MotorDriver_6612::brake()
{
  digitalWrite(_stbyPin, HIGH);   // Enable (turn off standby)
  digitalWrite(_in1, HIGH);
  digitalWrite(_in2, HIGH);
  analogWrite(_pwm, 0);
}

void BG_MotorDriver_6612::release()
{
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, LOW);
  analogWrite(_pwm, 0);
  digitalWrite(_stbyPin, LOW);   // Standby(?)
}

BG_MotorDriver_8871::BG_MotorDriver_8871()
{
  _motorCount = 2;
}

bool BG_MotorDriver_8871::setup(int pwm1, int pwm2, int ignore, int ignore2)
{
  _pwm1 = pwm1;
  _pwm2 = pwm2;
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  DebugPrint bgDebug;
  bgDebug.println("BG_MotorDriver_8871::setup");
  return true;
}

void BG_MotorDriver_8871::forward(int speed)
{
  digitalWrite(_pwm1, LOW);
  analogWrite(_pwm2, speed);
}

void BG_MotorDriver_8871::backward(int speed)
{
  digitalWrite(_pwm2, LOW);
  analogWrite(_pwm1, speed);
}

void BG_MotorDriver_8871::brake()
{
  digitalWrite(_pwm1, HIGH);
  digitalWrite(_pwm2, HIGH);
}

void BG_MotorDriver_8871::release()
{
  digitalWrite(_pwm1, LOW);
  digitalWrite(_pwm2, LOW);
  DebugPrint bgDebug;
  bgDebug.println("BG_MotorDriver_8871::release");
}

#ifdef SERIAL_CONTROLLED_DRIVER
#include #include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
BG_MotorDriver::BG_MotorDriver()
{
  motorCount = 1;
}

bool BG_MotorDriver::setup(int motorNum)
{
  _actuatorMotor.settings.commInterface = I2C_MODE;
  //  set address if I2C configuration selected with the config jumpers
  _actuatorMotor.settings.I2CAddress = 0x5A; //config pattern "0101" on board for address 0x5A
  //*****initialize the driver get wait for idle*****//

  bool motorInit = false;
  // Try up to 4 times for the motor to begin
  for (int i = 0; i < 4; i++) {
    if (_actuatorMotor.begin() == 0xA9 ) {   //Wait until a valid ID word is returned
      motorInit = true;
      break;
    }
    delay(500);
  }
  // Try up to 4 times for the driver to be ready
  for (int i = 0; i < 4; i++) {
    if (_actuatorMotor.ready()) {   //Wait until the driver is done looking for slaves before beginning
      motorInit = true;
      break;
    }
    delay(500);
  }
  return motorInit;
}

void BG_MotorDriver::forward(int speed)
{
  _actuatorMotor.setDrive( 0, 1, 255); //Drive motor forward at speed
}

void BG_MotorDriver::backward(int speed)
{
  _actuatorMotor.setDrive( 0, 0, 255); //Drive motor backward at speed
}

void BG_MotorDriver::brake()
{
  _actuatorMotor.setDrive( 0, 1, 0); //Set speed to zero
}

void BG_MotorDriver::release()
{
  _actuatorMotor.setDrive( 0, 1, 0); //Set speed to zero
}
#endif
