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
    leftSpeed = max(leftSpeed, -255);
    leftSpeed = min(leftSpeed, 255);
    
    rightSpeed = max(rightSpeed, -255);
    rightSpeed = min(rightSpeed, 255);
    
    digitalWrite(_in3, rightSpeed > 0 ? HIGH : LOW);
    digitalWrite(_in4, rightSpeed > 0 ? LOW : HIGH);
    digitalWrite(_in1, leftSpeed > 0 ? HIGH : LOW);
    digitalWrite(_in2, leftSpeed > 0 ? LOW : HIGH);
    analogWrite(_ena, leftSpeed * _motorAConst);
    analogWrite(_enb, rightSpeed * _motorBConst);
}

void LMotorController::move(int speed) {
    speed = max(speed, -255);
    speed = min(speed, 255);
    
    digitalWrite(_in1, speed > 0 ? HIGH : LOW);
    digitalWrite(_in2, speed > 0 ? LOW : HIGH);
    digitalWrite(_in3, speed > 0 ? HIGH : LOW);
    digitalWrite(_in4, speed > 0 ? LOW : HIGH);
    analogWrite(_ena, speed * _motorAConst);
    analogWrite(_enb, speed * _motorBConst);
}

void LMotorController::turnRight(int speed, bool kick) {
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
}

void LMotorController::turnLeft(int speed, bool kick) {
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
}

void LMotorController::stopMoving() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, LOW);
    digitalWrite(_ena, HIGH);
    digitalWrite(_enb, HIGH);
}
