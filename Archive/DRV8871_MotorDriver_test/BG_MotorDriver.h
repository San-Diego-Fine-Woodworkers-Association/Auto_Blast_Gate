/*
  Name:    BG_MotorDriver.h
  Created: 12/23/2021 10:32:45 PM
  Author:  Lem Davis
*/
#ifndef _Motor_Driver_h
#define _Motor_Driver_h
#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#ifdef SERIAL_CONTROLLED_DRIVER
#include <SCMD.h>
#include <SCMD_config.h> //Contains #defines for common SCMD register names and values
#endif

//**********************************************************
class BG_MotorDriver
{
  public:
    BG_MotorDriver();
    virtual bool setup(int, int = 3, int pwmPin = 5, int stbyPin = 9) {return true;}
    virtual void forward(int speed) {}
    virtual void backward(int speed) {}
    virtual void brake() {}
    virtual void release() {}
};

//**********************************************************
class BG_MotorDriver_Adafruit_Shield : public BG_MotorDriver
{
  private:
    int _motorCount;
    Adafruit_MotorShield _AFMS;
    // Select which 'port' M1, M2, M3 or M4.
    Adafruit_DCMotor* _actuatorMotor;

  public:
    BG_MotorDriver_Adafruit_Shield();
    bool setup(int, int in2 = 3, int pwmPin = 5, int stbyPin = 9);
    void forward(int speed);
    void backward(int speed);
    void brake();
    void release();
};

//**********************************************************
class BG_MotorDriver_6612 : public BG_MotorDriver
{
  private:
    int _motorCount;
    int _in1, _in2, _pwm, _stbyPin;

  public:
    BG_MotorDriver_6612();
    bool setup(int, int in2 = 3, int pwmPin = 5, int stbyPin = 9);
    void forward(int speed);
    void backward(int speed);
    void brake();
    void release();
};

//**********************************************************
class BG_MotorDriver_8871 : public BG_MotorDriver
{
  private:
    int _motorCount;
    int _pwm1, _pwm2;

  public:
    BG_MotorDriver_8871();
    bool setup(int, int, int ignore = 5, int ignore2 = 9);
    void forward(int speed);
    void backward(int speed);
    void brake();
    void release();
};


#endif
