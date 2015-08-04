#ifndef RoverWallFollower_h
#define RoverWallFollower_h

#include "LMotorController.h"
#include "Arduino.h"
#include "PID_v1.h"
#include "LUltrasonic.h"
#include "LLowPassFilter.h"

#define DEBUG_LOG 1
#define MANUAL_PID_TUNING 1
#define USE_DISTANCE_LOW_PASS_FILTER 0
#define DRIVE 1

class RoverWallFollower {
private:
    LMotorController *_motorController;
    int _leftWheelSpeed, _rightWheelSpeed;
    
    PID *_pid;
    double _kp, _ki, _kd;
    double _currentDistance, _pidOutput, _goalDistance;
    
    LUltrasonic *_sonic;
    LLowPassFilter *_sonicLPF;
    
    unsigned long _time1Hz, _time20Hz;
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
