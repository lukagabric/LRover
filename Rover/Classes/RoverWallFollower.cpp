#include "RoverWallFollower.h"
#include "Arduino.h"
#include "PID_v1.h"
#include "LUltrasonic.h"

#define LOG_PID_CONSTANTS 1
#define LOG_PID_OUTPUT 0
#define LOG_WHEEL_SPEED 0
#define LOG_DISTANCE 1
#define MANUAL_TUNING 1
#define USE_DISTANCE_LOW_PASS_FILTER 0
#define DRIVE 1

//Motor Controller
#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 7
#define ENB 6

#define MINIMUM_WHEEL_SPEED 10

//PID Constants
#define Kp 5
#define Ki 0.01
#define Kd 0.25

//Ultrasonic
#define SONIC_ECHO_PIN 9
#define SONIC_TRIG_PIN 8

//Low-Pass Filter
#define LPF_RC 0.005
#define LPF_DT 1/20.0

//Target Wall Distance
#define TARGET_WALL_DISTANCE 30

#pragma mark - Setup

void RoverWallFollower::setup() {
#if LOG_PID_CONSTANTS || LOG_PID_OUTPUT || LOG_WHEEL_SPEED || LOG_DISTANCE
    Serial.begin(9600);
#endif
    _sonic = new LUltrasonic(SONIC_ECHO_PIN, SONIC_TRIG_PIN);

    _motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
    
    _lowPassFilter = new LLowPassFilter(LPF_RC, LPF_DT);
    
    _pidSetpoint = TARGET_WALL_DISTANCE;
    _pid = new PID(&_pidInput, &_pidOutput, &_pidSetpoint, Kp, Ki, Kd, DIRECT);
#if MANUAL_TUNING
    _pid->SetTunings(_kp, _ki, _kd);
#endif
    _pid->SetMode(AUTOMATIC);
    _pid->SetSampleTime(50);
    _pid->SetOutputLimits(-255, 255);
}

#pragma mark - Loop

void RoverWallFollower::loop() {
    unsigned long currentTime = millis();
    
    if (currentTime - _time1Hz >= 1000) {
        _time1Hz = currentTime;
        loopAt1Hz();
    }
    if (currentTime - _time20Hz >= 50) {
        _time20Hz = currentTime;
        loopAt20Hz();
    }
}

void RoverWallFollower::loopAt1Hz() {
#if MANUAL_TUNING
    updatePIDConstants();
#endif
}

void RoverWallFollower::loopAt20Hz() {
    updatePID();
    updateMovement();
}

#pragma mark - Operations

void RoverWallFollower::updatePIDConstants() {
    int potKp = analogRead(A0);
    int potKi = analogRead(A1);
    int potKd = analogRead(A2);
    
    _kp = map(potKp, 0, 1023, 0, 1000) / 100.0;
    _ki = map(potKi, 0, 1023, 0, 1000) / 100.0;
    _kd = map(potKd, 0, 1023, 0, 100) / 100.0;
    
    if (_kp == _prevKp && _ki == _prevKi && _kd == _prevKd) return;

#if LOG_PID_CONSTANTS
        Serial.print(_kp);Serial.print(", ");Serial.print(_ki);Serial.print(", ");Serial.println(_kd);
#endif

    _pid->SetTunings(_kp, _ki, _kd);
    _prevKp = _kp; _prevKi = _ki; _prevKd = _kd;
}

void RoverWallFollower::updatePID() {
    double rawDistance = _sonic->measureDistance();

#if USE_DISTANCE_LOW_PASS_FILTER
    _pidInput = _lowPassFilter->filteredValue(rawDistance);
#else
    _pidInput = rawDistance;
#endif

    _pid->Compute();

#if LOG_PID_OUTPUT
    if (_pidOutput != _prevPidOutput) {
        Serial.print("PID OUTPUT: ");Serial.println(_pidOutput);
        _prevPidOutput = _pidOutput;
    }
#endif
}

void RoverWallFollower::updateMovement() {
    int rightWheelSpeed = 255;
    int leftWheelSpeed = 255;
    
    int output = _pidOutput;
    
    if (_pidOutput < 0) {
        //too far, turn right
        rightWheelSpeed += _pidOutput;
        rightWheelSpeed = max(MINIMUM_WHEEL_SPEED, rightWheelSpeed);
    }
    else {
        //too close, turn left
        leftWheelSpeed -= _pidOutput;
        leftWheelSpeed = max(MINIMUM_WHEEL_SPEED, leftWheelSpeed);
    }
    
#if LOG_WHEEL_SPEED
    Serial.print("\tRW=");Serial.print(rightWheelSpeed);Serial.print("\tLW");Serial.println(leftWheelSpeed);
#endif
    
#if LOG_DISTANCE
    if (_pidInput != _prevDistance) {
        Serial.print("\tDST=");Serial.println(_pidInput);
        _prevDistance = _pidInput;
    }
#endif

#if DRIVE
    _motorController->move(leftWheelSpeed, rightWheelSpeed);
#endif
}

#pragma mark -
