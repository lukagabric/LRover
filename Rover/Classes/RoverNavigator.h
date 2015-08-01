#ifndef RoverNavigator_h
#define RoverNavigator_h

#include "LMotorController.h"
#include "Arduino.h"
#include "PID_v1.h"
#include "LUltrasonic.h"
#include "LLowPassFilter.h"
#include "HMC5883L.h"

class RoverNavigator {
private:
    LMotorController *_motorController;
    
    HMC5883L *_compass;
    int16_t _mx, _my, _mz;
    
    double _kp, _prevKp, _ki, _prevKi, _kd, _prevKd;
    double _pidInput, _pidOutput, _prevPidOutput, _pidSetpoint;
    PID *_pid;
    
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
