char           ver[10] =             "S2.11";



int            boardID=               22;
char*          MachineID=            "M17"; 
char*          gateName=             "22M17 8 inch Jointer";
int            gateDelaySeconds =     5;




const int      trigger =              400;   //A/D threshold from current sensor pin to determine tool-on condition
bool           rotation =             false;    // To accomodate some stepper motors that have non-standard pinout from motor.  Normal=false  Reverse=true
const char*    ssid=                  "SDFWAwifi";
const char*    password=              "dovetail";
bool           combo =                false;   //  set to false if this board V1 - V3  This reassigns pins to the old versions
int            delayTime =            9999;   // hold time between steps lower=faster higher=slower. 200-400 for 4988 drivers,  75-125 for TMC2209 drivers 
int            fullRunSteps =         1;  //steps required between open and closed points   4988 stepper 5" Full Step:2500, Quarter step =10000       TMC2209 Stepper 5" Gate = 21000



        
