#ifndef RoverNavigator_h
#define RoverNavigator_h

#include "LMotorController.h"
#include "Arduino.h"
#include "LPID.h"
#include "LUltrasonic.h"
#include "LCompass.h"
#include "LLCD.h"
#include "LGPS.h"
#include "LPIDTuner.h"

class RoverNavigator {
private:
    LLCD *_lcd;
    LGPS *_gps;
    LMotorController *_motorController;
    LPIDTuner *_pidTuner;
    LPID *_pid;
    LCompass *_compass;
    
    unsigned long _time1Hz, _time20Hz, _time15s;
    void loop15s();
    void loopAt1Hz();
    void loopAt20Hz();
    
    void configureMovement();
    
    void debugLogToLCD();
    void debugLog();
public:
    void setup();
    void loop();
};

#endif
