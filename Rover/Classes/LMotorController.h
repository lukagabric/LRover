#ifndef LMotorController_h
#define LMotorController_h

#include "Arduino.h"

class LMotorController {
protected:
    unsigned int _ena, _in1, _in2, _enb, _in3, _in4;
    double _motorAConst, _motorBConst;
public:
    LMotorController(int ena, int in1, int in2, int enb, int in3, int in4, double motorAConst, double motorBConst);
    int leftWheelSpeed, rightWheelSpeed;
    void move(int leftSpeed, int rightSpeed);
    void move(int speed);
    void turnLeft(int speed, bool kick);
    void turnRight(int speed, bool kick);
    void stopMoving();
};

#endif
