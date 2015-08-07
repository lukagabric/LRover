#ifndef LMotorController_h
#define LMotorController_h

#include "Arduino.h"
#include "LLCD.h"

class LMotorController {
private:
    unsigned int _ena, _in1, _in2, _enb, _in3, _in4;
    double _motorAConst, _motorBConst;
    int _leftWheelSpeed, _rightWheelSpeed;
public:
    LMotorController(int ena, int in1, int in2, int enb, int in3, int in4, double motorAConst, double motorBConst);
    
    int leftWheelSpeed();
    int rightWheelSpeed();
    
    void move(int leftSpeed, int rightSpeed);
    void move(int speed);
    void move(double pidOutput, int minWheelSpeed);
    void turnLeft(int speed, bool kick);
    void turnRight(int speed, bool kick);
    void stopMoving();
    
    void printSpeedToLCD(LLCD *lcd);
    void printSpeedToSerial();
};

#endif
