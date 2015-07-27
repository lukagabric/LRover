#ifndef RoverWallFollower_h
#define RoverWallFollower_h

#include "LMotorController.h"
#include "Arduino.h"
#include "PID_v1.h"
#include "LUltrasonic.h"
#include "LLowPassFilter.h"

class RoverWallFollower {
private:
    LMotorController *_motorController;
    
    double _kp, _prevKp, _ki, _prevKi, _kd, _prevKd;
    double _pidInput, _pidOutput, _prevPidOutput, _pidSetpoint;
    PID *_pid;
    
    LUltrasonic *_sonic;
    double _prevDistance;
    
    LLowPassFilter *_lowPassFilter;
    
    unsigned long _time1Hz, _time20Hz;
    void loopAt1Hz();
    void loopAt20Hz();
    
    void updatePID();
    void updatePIDConstants();
    void updateMovement();
public:
    void setup();
    void loop();
};

#endif
