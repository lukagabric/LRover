#ifndef RoverMain_h
#define RoverMain_h

#include "LMotorController.h"
#include "Arduino.h"
#include "PID_v1.h"

class RoverMain {
private:
    LMotorController *_motorController;
    
    double _pidInput, _pidOutput, _pidSetpoint;
    PID *_pid;

    unsigned long _time1Hz, _time5Hz, _time10Hz, _time100Hz;
    void loopAt1Hz();
    void loopAt5Hz();
    void loopAt10Hz();
    void loopAt100Hz();
    
    void updatePID();
    void updateMovement();
public:
    void setup();
    void loop();
};

#endif
