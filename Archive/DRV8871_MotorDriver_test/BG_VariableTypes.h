/*
 Name:    VariableTypes.h
 Created: 12/12/2021 10:32:45 PM
 Author:  Lem Davis
*/

#ifndef _VariableTypes_h
#define _VariableTypes_h
#include <Arduino.h>

typedef enum _blastgate_state {
  BG_Open,
  BG_Closed,
  BG_OpenRamping,
  BG_CloseRamping,
  BG_MovingToOpen,
  BG_MovingToClosed,
  BG_State_Unknown,
  BG_Error_Opening,
  BG_Error_Closing
} BlastGateState;

typedef struct _BlastGateData {
  // Blast gate state
  BlastGateState gateState;

  // Keep track of the current drawn by the actuator, updated in gate open/close task
  float maxActuatorCurrentmA;  // During a gate transition
  float actuatorCurrentmA;
  float actuatorCurrentLimitmA;  // Shut down gate if the current limit is exceeded

  // The following values may need to be adjusted and are stored in non-volatile memory
  int countThreshhold;
  int onCurrentThreshhold;
  int offCurrentThreshhold;

  int transitionTimeLimitMs; //Milliseconds
  float transitionTimeSec;  // Seconds

  int accelerationSteps; //1 to 255
} BlastGateData;

typedef enum _controller_status {
  BG_OK,
  BG_Warning,
  BG_Error
} BlastGateControllerStatus;


#endif
