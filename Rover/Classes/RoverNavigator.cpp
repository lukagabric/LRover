#include "RoverNavigator.h"
#include "Arduino.h"
#include "PID_v1.h"

//Motor Controller
#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 7
#define ENB 6

//PID Constants
#define Kp 70
#define Ki 250
#define Kd 1.9

#pragma mark - Setup

void RoverNavigator::setup() {
    Serial.begin(9600);
    
    _motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);

    _pidSetpoint = 0;
    _pid = new PID(&_pidInput, &_pidOutput, &_pidSetpoint, Kp, Ki, Kd, DIRECT);
    _pid->SetMode(AUTOMATIC);
    _pid->SetSampleTime(10);
    _pid->SetOutputLimits(-255, 255);
}

#pragma mark - Loop

void RoverNavigator::loop() {
    unsigned long currentTime = millis();
    
    if (currentTime - _time1Hz >= 1000) {
        _time1Hz = currentTime;
        loopAt1Hz();
    }
    if (currentTime - _time5Hz >= 200) {
        _time5Hz = currentTime;
        loopAt5Hz();
    }
    if (currentTime - _time10Hz >= 100) {
        _time10Hz = currentTime;
        loopAt10Hz();
    }
    if (currentTime - _time100Hz >= 10) {
        _time100Hz = currentTime;
        loopAt100Hz();
    }
}

void RoverNavigator::loopAt1Hz() {
    
}

void RoverNavigator::loopAt5Hz() {
    
}

void RoverNavigator::loopAt10Hz() {
    
}

void RoverNavigator::loopAt100Hz() {
    updatePID();
    updateMovement();
}

#pragma mark - Operations

void RoverNavigator::updatePID() {
    double compass = 20;
    double bearing = 350;
    
    double diffAngle = bearing - compass;
    if (diffAngle > 180) {
        diffAngle -= 360;
    }
    else if (diffAngle < -180) {
        diffAngle += 360;
    }
    
    _pidInput = diffAngle;
    _pid->Compute();
}

void RoverNavigator::updateMovement() {
    double rightWheelSpeed = 255;
    double leftWheelSpeed = 255;
    
    if (_pidOutput < 0) {
        rightWheelSpeed -= abs(_pidOutput);
    }
    else {
        leftWheelSpeed -= _pidOutput;
    }
    
    _motorController->move(leftWheelSpeed, rightWheelSpeed);
}

#pragma mark -
