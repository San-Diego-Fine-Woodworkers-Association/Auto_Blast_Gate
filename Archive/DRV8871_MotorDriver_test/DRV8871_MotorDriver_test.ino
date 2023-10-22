#include "BG_VariableTypes.h"
#include "BG_MotorDriver.h"
#include <Adafruit_INA219.h>

// Basic sketch for trying out the Adafruit DRV8871 using the MotorDriver class

#define MOTOR_IN1 14
#define MOTOR_IN2 16

BG_MotorDriver *actuatorMotor;

bool ina219Found = false;;
Adafruit_INA219 ina219;

// Keep track of the current drawn by the actuator, updated in gate open/close task
float maxActuatorCurrentmA = 0.0;  // During a gate transition
float actuatorCurrentmA;

// Set this to true to see debug messages
bool debugOn = true;

bool motorTest = true;

void setup() {
  Serial.begin(115200);

  actuatorMotor = new BG_MotorDriver_8871;

  delay(5000); //Allow time for Serial Monitor to open
  Serial.println("DRV8871 test\n");
  if (!actuatorMotor->setup(MOTOR_IN1, MOTOR_IN2)) {
    Serial.println("Motor drvr error");
    while (1) delay(10);
  }

  // Start the current sensor
  if (ina219.begin()) {
    ina219Found = true;
    ina219.setCalibration_16V_400mA();
  }
  else {
    Serial.println("INA219 not found");
    ina219Found = false;
  }
}

void loop() {
  if (motorTest) {
    for (int j = 0; j < 2; j++) {
      Serial.println("Forward");
      // ramp up forward
      for (int i = 0; i < 255; i++) {
        actuatorMotor->forward(i);
        if (ina219Found) {
          actuatorCurrentmA = ina219.getCurrent_mA();
          if (actuatorCurrentmA > maxActuatorCurrentmA)
            maxActuatorCurrentmA = actuatorCurrentmA;
        }
        delay(10);
      }
      if (ina219Found) {
        Serial.print("Forward max actuator current = ");
        Serial.println(maxActuatorCurrentmA);
      }
      delay(3350);

      Serial.println("Backward");
      // ramp up backward
      for (int i = 0; i < 255; i++) {
        actuatorMotor->backward(i);
        if (ina219Found) {
          actuatorCurrentmA = ina219.getCurrent_mA();
          if (actuatorCurrentmA > maxActuatorCurrentmA)
            maxActuatorCurrentmA = actuatorCurrentmA;
        }
        delay(10);
      }
      if (ina219Found) {
        Serial.print("Backward max actuator current = ");
        Serial.println(maxActuatorCurrentmA);
      }
      delay(3350);
    }
    motorTest = false;
    actuatorMotor->release();
    Serial.println("Done.");
  }
  delay(1000);
}
