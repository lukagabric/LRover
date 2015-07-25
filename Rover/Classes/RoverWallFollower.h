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
    double _pidInput, _pidOutput, _pidSetpoint;
    PID *_pid;
    
    LUltrasonic *_sonic;
    
    LLowPassFilter *_lowPassFilter;
    
    unsigned long _time1Hz, _time5Hz, _time10Hz, _time100Hz;
    void loopAt1Hz();
    void loopAt5Hz();
    void loopAt10Hz();
    void loopAt100Hz();
    
    void updatePID();
    void updatePIDConstants();
    void updateMovement();
public:
    void setup();
    void loop();
};

#endif
