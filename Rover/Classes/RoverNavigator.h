#ifndef RoverNavigator_h
#define RoverNavigator_h

#include "LMotorController.h"
#include "Arduino.h"
#include "PID_v1.h"

class RoverNavigator {
private:
    LMotorController *_motorController;
    
    double _kp, _prevKp, _ki, _prevKi, _kd, _prevKd;
    double _pidInput, _pidOutput, _pidSetpoint;
    PID *_pid;

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
