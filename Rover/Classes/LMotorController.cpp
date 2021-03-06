#include "LMotorController.h"
#include "Arduino.h"

#pragma mark - Constructor

LMotorController::LMotorController(int ena, int in1, int in2, int enb, int in3, int in4, double motorAConst, double motorBConst) {
    _leftWheelSpeed = 0;
    _rightWheelSpeed = 0;
    
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

#pragma mark - Operations

void LMotorController::move(int leftSpeed, int rightSpeed) {
    _leftWheelSpeed = max(leftSpeed, -255);
    _leftWheelSpeed = min(leftSpeed, 255);
    
    _rightWheelSpeed = max(rightSpeed, -255);
    _rightWheelSpeed = min(rightSpeed, 255);
    
    digitalWrite(_in3, _rightWheelSpeed > 0 ? HIGH : LOW);
    digitalWrite(_in4, _rightWheelSpeed > 0 ? LOW : HIGH);
    digitalWrite(_in1, _leftWheelSpeed > 0 ? HIGH : LOW);
    digitalWrite(_in2, _leftWheelSpeed > 0 ? LOW : HIGH);
    analogWrite(_ena, abs(_leftWheelSpeed) * _motorAConst);
    analogWrite(_enb, abs(_rightWheelSpeed) * _motorBConst);
}

void LMotorController::move(int speed) {
    move(speed, speed);
}

void LMotorController::move(LWheelSpeeds wheelSpeeds) {
    move(wheelSpeeds.leftWheelSpeed, wheelSpeeds.rightWheelSpeed);
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
    
    _leftWheelSpeed = speed;
    _rightWheelSpeed = -1 * speed;
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
    
    _leftWheelSpeed = -1 * speed;
    _rightWheelSpeed = speed;
}

void LMotorController::stopMoving() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, LOW);
    digitalWrite(_ena, HIGH);
    digitalWrite(_enb, HIGH);
    
    _leftWheelSpeed = 0;
    _rightWheelSpeed = 0;
}

#pragma mark - Getters

int LMotorController::leftWheelSpeed() {
    return _leftWheelSpeed;
}

int LMotorController::rightWheelSpeed() {
    return _rightWheelSpeed;
}

#pragma mark -
