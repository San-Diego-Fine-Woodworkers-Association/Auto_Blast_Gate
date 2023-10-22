/*-------------------------------------------------------------------

    Stepper Control V3
    Dallas Keck
    ESP32 Based Controller
    Revised 10/07/23
    Version   S2.11

  2.11  Created a Keep WiFi Alive function.  It contuously monitors WiFi and reconnects when needed
  2.02  Simplified the configuation process.   Settings are assigned by boardID.
  2.01: (Includes the short lived 2.00 version)
        Added a tab "Settings" in simplify the configration process. 
        Removed the SPFF files and auto config function.   The configuration info is entered on the settings tab prior to loading the firmware.   OTA update   
          


  Changes with 1.50:  Status relay to toggle as soon as power is detected and go low as soon as power is off.
  Changes with 1.37:  Changes the status reed relay toogle to change once the tool is off rather than after the tool is off plus a delay.
  Changes with 1.352   Added quarter-step capability
  Changes with 1.351 Reduced the speed to increase torgue
  Changes with 1.35:  Created flag (combo) tgo identify early verion boards to automatically assign pins
  Changes with 1.32:
        Fixed bug with the link function: renamed triggerPin to linkPin
        Enable OTA updates
        Added HOST Name to WiFi

  Tasks to be completed:
        create timeout on Opening and closing in case of jammed gate
        capture data and upload to the cloud

  --------------------------------------------------------------------*/



#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "Settings.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>`
#include <WiFiManager.h> 


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    17 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
 #define WiFiTimeOutMS 10000

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//      Pin Assignements

#define ANALOG_PIN_IN             A0
const int limitSwitchPin  =       19;
const int reedRelayPin =          23;
const int greenLEDpin =           25;
const int redLEDpin =             26;
const int gateOn =                16;    // Controls H-Bridge
const int gateOff =               4;     // Controls H-Bridge
int linkPin =                     13;    // use pin 33 for ver 1-3   Use pin 13 for v4 plus
int stepPin =                     16;    // 16 for combo boards   04 for earlier versions
int dirPin =                      04;    // 04 for combo boards   02 for earlier versions
int enablePin  =                  17;    // 17 for combo boards  16 for early versions
const int speedPin =              18;   //  MS2 sets enables quarter stepping

//     Working Variables
int sensorIn =                    0;
int stepPosition =               103;
String trace =                  "test";
int countDown;

//     Paramenters
const int waitTime =           250;

const int backSteps =          50;    //steps required to open switch after homing
const int stepsPerRevolution = 200;
const int holdTime  =          500;   // time to stablize each cycle (microseconds)
const int displayTime =        000;
const int timeout =            120;

unsigned long closeDelayTime = 1000; // microseconds to be used for gate delay time
unsigned long currentTime;
unsigned long startTime;
unsigned long closeTime;
unsigned long x;

//Status Flags
volatile bool manualState =               false;
volatile bool limitSwitchState =          false;
volatile bool gateCloseState =            false;
volatile bool gateOpenState =             false;
bool shouldSaveConfig =                   false;
bool displayFlag =                        false;
int manualStatus = 0;
int flag = 0;


//Data
long toolRunTime = 0;
long toolTimer =   0;
int toolCycles =   0;
int loopCount = 0;


void closeGate();
void homePosition();
void openGate();
void checkSwitchState();
void printStat();
void displayStat();
