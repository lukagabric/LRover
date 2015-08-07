#include "LMotorController.h"
#include "Arduino.h"

LMotorController::LMotorController(int ena, int in1, int in2, int enb, int in3, int in4, double motorAConst, double motorBConst) {
    _motorAConst = motorAConst;
    _motorBConst = motorBConst;
    
	_ena = ena;
	_in1 = in1;
	_in2 = in2;
	_enb = enb;
	_in3 = in3;
	_in4 = in4;
	
	pinMode(_ena, OUTPUT);
	pinMode(_in1, OUTPUT);
	pinMode(_in2, OUTPUT);
    
	pinMode(_enb, OUTPUT);
	pinMode(_in3, OUTPUT);
	pinMode(_in4, OUTPUT);
}

void LMotorController::move(int leftSpeed, int rightSpeed) {
    leftWheelSpeed = max(leftSpeed, -255);
    leftWheelSpeed = min(leftSpeed, 255);
    
    rightWheelSpeed = max(rightSpeed, -255);
    rightWheelSpeed = min(rightSpeed, 255);
    
    digitalWrite(_in3, rightWheelSpeed > 0 ? HIGH : LOW);
    digitalWrite(_in4, rightWheelSpeed > 0 ? LOW : HIGH);
    digitalWrite(_in1, leftWheelSpeed > 0 ? HIGH : LOW);
    digitalWrite(_in2, leftWheelSpeed > 0 ? LOW : HIGH);
    analogWrite(_ena, leftWheelSpeed * _motorAConst);
    analogWrite(_enb, rightWheelSpeed * _motorBConst);
}

void LMotorController::move(int speed) {
    move(speed, speed);
}

void LMotorController::turnRight(int speed, bool kick) {
    speed = max(speed, 0);
    
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, HIGH);
    
    if (kick) {
        analogWrite(_ena, 255);
        analogWrite(_enb, 255);
        
        delay(100);
    }
    
    analogWrite(_ena, speed * _motorAConst);
    analogWrite(_enb, speed * _motorBConst);
    
    leftWheelSpeed = speed;
    rightWheelSpeed = -1 * speed;
}

void LMotorController::turnLeft(int speed, bool kick) {
    speed = max(speed, 0);

    digitalWrite(_in1, LOW);
    digitalWrite(_in2, HIGH);
    digitalWrite(_in3, HIGH);
    digitalWrite(_in4, LOW);
    
    if (kick) {
        analogWrite(_ena, 255);
        analogWrite(_enb, 255);
        
        delay(100);
    }
    
    analogWrite(_ena, speed * _motorAConst);
    analogWrite(_enb, speed * _motorBConst);
    
    leftWheelSpeed = -1 * speed;
    rightWheelSpeed = speed;
}

void LMotorController::stopMoving() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, LOW);
    digitalWrite(_ena, HIGH);
    digitalWrite(_enb, HIGH);
    
    leftWheelSpeed = 0;
    rightWheelSpeed = 0;
}
