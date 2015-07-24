#include "RoverNavigator.h"
#include "Arduino.h"
#include "PID_v1.h"

#define ENABLE_LOGGING 1
#define MANUAL_TUNING 1

//Motor Controller
#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 7
#define ENB 6

#define MIN_WHEEL_SPEED 30

//PID Constants
#define Kp 70
#define Ki 250
#define Kd 1.9

#pragma mark - Setup

void RoverNavigator::setup() {
#if ENABLE_LOGGING
    Serial.begin(9600);
#endif
    
    _motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);

    _pidSetpoint = 0;
    _pid = new PID(&_pidInput, &_pidOutput, &_pidSetpoint, 0, 0, 0, DIRECT);
#if MANUAL_TUNING
    _pid->SetTunings(_kp, _ki, _kd);
#endif
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
#if MANUAL_TUNING
    updatePIDConstants();
#endif
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

#if MANUAL_TUNING
void RoverNavigator::updatePIDConstants() {
    int potKp = analogRead(A0);
    int potKi = analogRead(A1);
    int potKd = analogRead(A2);
    
    _kp = map(potKp, 0, 1023, 0, 25000) / 100.0; //0 - 250
    _ki = map(potKi, 0, 1023, 0, 100000) / 100.0; //0 - 1000
    _kd = map(potKd, 0, 1023, 0, 500) / 100.0; //0 - 5
    
    if (_kp != _prevKp || _ki != _prevKi || _kd != _prevKd) {
#if ENABLE_LOGGING
        Serial.print(_kp);Serial.print(", ");Serial.print(_ki);Serial.print(", ");Serial.println(_kd);
#endif
        _pid->SetTunings(_kp, _ki, _kd);
        _prevKp = _kp; _prevKi = _ki; _prevKd = _kd;
    }
}
#endif

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
    int rightWheelSpeed = 255;
    int leftWheelSpeed = 255;
    
    if (_pidOutput < 0) {
        rightWheelSpeed += _pidOutput;
    }
    else {
        leftWheelSpeed -= _pidOutput;
    }
    
    rightWheelSpeed = max(MIN_WHEEL_SPEED, rightWheelSpeed);
    leftWheelSpeed = max(MIN_WHEEL_SPEED, leftWheelSpeed);
    
#if ENABLE_LOGGING
    Serial.print("\tDST=");
    Serial.print(_pidInput);
    Serial.print("\tRW=");
    Serial.print(rightWheelSpeed);
    Serial.print("\tLW");
    Serial.println(leftWheelSpeed);
#endif
    
    _motorController->move(leftWheelSpeed, rightWheelSpeed);
}

#pragma mark -
