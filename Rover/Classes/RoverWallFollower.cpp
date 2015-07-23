#include "RoverWallFollower.h"
#include "Arduino.h"
#include "PID_v1.h"
#include "LUltrasonic.h"

#define ENABLE_LOGGING 0

//Motor Controller
#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 7
#define ENB 6

#define MIN_WHEEL_SPEED 100

//PID Constants
#define Kp 70
#define Ki 250
#define Kd 1.9

//Ultrasonic
#define SONIC_ECHO_PIN 9
#define SONIC_TRIG_PIN 8
#define SONIC_WALL_DISTANCE 50

#pragma mark - Setup

void RoverWallFollower::setup() {
    Serial.begin(9600);
    
    _motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
    
    _pidSetpoint = 30;
    _pid = new PID(&_pidInput, &_pidOutput, &_pidSetpoint, Kp, Ki, Kd, DIRECT);
    _pid->SetMode(AUTOMATIC);
    _pid->SetSampleTime(10);
    _pid->SetOutputLimits(-255, 255);
    
    _sonic = new LUltrasonic(SONIC_ECHO_PIN, SONIC_TRIG_PIN);
}

#pragma mark - Loop

void RoverWallFollower::loop() {
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

void RoverWallFollower::loopAt1Hz() {

}

void RoverWallFollower::loopAt5Hz() {

}

void RoverWallFollower::loopAt10Hz() {

}

void RoverWallFollower::loopAt100Hz() {
    updatePID();
    updateMovement();
}

#pragma mark - Operations

void RoverWallFollower::updatePID() {
    _pidInput = _sonic->measureDistance();
    _pid->Compute();
}

void RoverWallFollower::updateMovement() {
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
