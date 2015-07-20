#ifndef RoverMain_h
#define RoverMain_h

#include "LMotorController.h"
#include "Arduino.h"

class RoverMain {
private:
    LMotorController *motorController;
    void moveForward();
    void turnLeft();
    void turnRight();
public:
    void setup();
    void loop();
};

#endif
