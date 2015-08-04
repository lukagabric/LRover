#ifndef RoverNavigator_h
#define RoverNavigator_h

#include "LMotorController.h"
#include "Arduino.h"
#include "PID_v1.h"
#include "LUltrasonic.h"
#include "LLowPassFilter.h"
#include "LCompass.h"

#define DEBUG_LOG 0
#define MANUAL_PID_TUNING 1
#define USE_COMPASS_LOW_PASS_FILTER 1
#define DRIVE 1

class RoverNavigator {
private:
    int state;
    
    LMotorController *_motorController;
    int _leftWheelSpeed, _rightWheelSpeed;
    
    PID *_pid;
    double _kp, _ki, _kd;
    double _headdingOffset, _pidOutput, _pidSetpoint, _currentHeading, _goalHeading;
    
    LCompass *_compass;
    LLowPassFilter *_compassLPF;    
    
    unsigned long _time1Hz, _time20Hz, _time15s;
    void loop15s();
    void loopAt1Hz();
    void loopAt20Hz();
    
#if MANUAL_PID_TUNING
    void configurePIDConstants();
#endif
    void configurePIDOutput();
    void configureMovement();
#if DEBUG_LOG
    void debugLog();
#endif
public:
    void setup();
    void loop();
};

#endif
