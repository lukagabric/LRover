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

void LMotorController::move(int leftSpeed, int rightSpeed, int minAbsSpeed) {
    if (rightSpeed < 0) {
        rightSpeed = min(rightSpeed, -1*minAbsSpeed);
        rightSpeed = max(rightSpeed, -255);
    }
    else if (rightSpeed > 0) {
        rightSpeed = max(rightSpeed, minAbsSpeed);
        rightSpeed = min(rightSpeed, 255);
    }
    
    int realRightSpeed = map(abs(rightSpeed), 0, 255, minAbsSpeed, 255);
    
    if (leftSpeed < 0) {
        leftSpeed = min(leftSpeed, -1*minAbsSpeed);
        leftSpeed = max(leftSpeed, -255);
    }
    else if (leftSpeed > 0) {
        leftSpeed = max(leftSpeed, minAbsSpeed);
        leftSpeed = min(leftSpeed, 255);
    }
    
    int realLeftSpeed = map(abs(leftSpeed), 0, 255, minAbsSpeed, 255);
    
    digitalWrite(_in3, rightSpeed > 0 ? HIGH : LOW);
    digitalWrite(_in4, rightSpeed > 0 ? LOW : HIGH);
    digitalWrite(_in1, leftSpeed > 0 ? HIGH : LOW);
    digitalWrite(_in2, leftSpeed > 0 ? LOW : HIGH);
    analogWrite(_ena, realRightSpeed * _motorAConst);
    analogWrite(_enb, realLeftSpeed * _motorBConst);
}

void LMotorController::move(int speed, int minAbsSpeed) {
    if (speed < 0) {
        speed = max(speed, -1*minAbsSpeed);
        speed = min(speed, -255);
    }
    else if (speed > 0) {
        speed = max(speed, minAbsSpeed);
        speed = min(speed, 255);
    }
    
    int realSpeed = map(abs(speed), 0, 255, minAbsSpeed, 255);
    
    digitalWrite(_in1, speed > 0 ? HIGH : LOW);
    digitalWrite(_in2, speed > 0 ? LOW : HIGH);
    digitalWrite(_in3, speed > 0 ? HIGH : LOW);
    digitalWrite(_in4, speed > 0 ? LOW : HIGH);
    analogWrite(_ena, realSpeed * _motorAConst);
    analogWrite(_enb, realSpeed * _motorBConst);
}

void LMotorController::move(int speed) {
    if (speed > 255) speed = 255;
    else if (speed < -255) speed = -255;
    
    int realSpeed = map(abs(speed), 0, 255, 70, 255);
    
    digitalWrite(_in1, speed > 0 ? HIGH : LOW);
    digitalWrite(_in2, speed > 0 ? LOW : HIGH);
    digitalWrite(_in3, speed > 0 ? HIGH : LOW);
    digitalWrite(_in4, speed > 0 ? LOW : HIGH);
    analogWrite(_ena, realSpeed);
    analogWrite(_enb, realSpeed);
}

void LMotorController::turnLeft(int speed, bool kick) {
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, HIGH);
    
    if (kick) {
        analogWrite(_ena, 255);
        analogWrite(_enb, 255);
        
        delay(100);
    }
    
    analogWrite(_ena, speed);
    analogWrite(_enb, speed);
}

void LMotorController::turnRight(int speed, bool kick) {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, HIGH);
    digitalWrite(_in3, HIGH);
    digitalWrite(_in4, LOW);
    
    if (kick) {
        analogWrite(_ena, 255);
        analogWrite(_enb, 255);
        
        delay(100);
    }
    
    analogWrite(_ena, speed);
    analogWrite(_enb, speed);
}

void LMotorController::stopMoving() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, LOW);
    digitalWrite(_ena, HIGH);
    digitalWrite(_enb, HIGH);
}
