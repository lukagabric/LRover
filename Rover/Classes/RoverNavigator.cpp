#include "RoverNavigator.h"
#include "Arduino.h"
#include "PID_v1.h"
#include "LUltrasonic.h"
#include <Wire.h>

#define LOG_PID_CONSTANTS 1
#define LOG_PID_OUTPUT 0
#define LOG_WHEEL_SPEED 0
#define LOG_DIRECTION 1
#define MANUAL_TUNING 1
#define USE_DISTANCE_LOW_PASS_FILTER 0
#define DRIVE 0

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

//Low-Pass Filter
#define LPF_RC 0.005
#define LPF_DT 1/20.0

//Compass
#define Addr 0x1E

#pragma mark - Setup

void RoverNavigator::setup() {
#if LOG_PID_CONSTANTS || LOG_PID_OUTPUT || LOG_WHEEL_SPEED || LOG_DIRECTION
    Serial.begin(9600);
#endif

    delay(100);
    
    // initialize device
    Serial.println("Initializing I2C devices...");
    _compass = new HMC5883L();
    _compass->initialize();
    
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(_compass->testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");

    delay(2000);
    
    _motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
    
    _lowPassFilter = new LLowPassFilter(LPF_RC, LPF_DT);
    
    _pidSetpoint = 0;
    _pid = new PID(&_pidInput, &_pidOutput, &_pidSetpoint, Kp, Ki, Kd, DIRECT);
#if MANUAL_TUNING
    _pid->SetTunings(_kp, _ki, _kd);
#endif
    _pid->SetMode(AUTOMATIC);
    _pid->SetSampleTime(50);
    _pid->SetOutputLimits(-255, 255);
}

#pragma mark - Loop

void RoverNavigator::loop() {
    _compass->getHeading(&_mx, &_my, &_mz);
    
    // display tab-separated gyro x/y/z values
    Serial.print("Compass:\t");
    Serial.print(_mx); Serial.print("\t");
    Serial.print(_my); Serial.print("\t");
    Serial.print(_mz); Serial.print("\t");

    // To calculate heading in degrees. 0 degree indicates North
    float heading = atan2(_my, _mx);
    if (heading < 0) {
        heading += 2 * M_PI;
    }
    Serial.print("heading:\t");
    Serial.println(heading * 180/M_PI);
    
    
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

void RoverNavigator::loopAt1Hz() {
#if MANUAL_TUNING
    updatePIDConstants();
#endif
}

void RoverNavigator::loopAt20Hz() {
    updatePID();
    updateMovement();
}

#pragma mark - Operations

void RoverNavigator::updatePIDConstants() {
    int potKp = analogRead(A0);
    int potKi = analogRead(A1);
    int potKd = analogRead(A2);
    
    _kp = map(potKp, 0, 1023, 0, 25000) / 100.0; //0 - 250
    _ki = map(potKi, 0, 1023, 0, 100000) / 100.0; //0 - 1000
    _kd = map(potKd, 0, 1023, 0, 500) / 100.0; //0 - 5
    
    if (_kp == _prevKp && _ki == _prevKi && _kd == _prevKd) return;
    
#if LOG_PID_CONSTANTS
    Serial.print(_kp);Serial.print(", ");Serial.print(_ki);Serial.print(", ");Serial.println(_kd);
#endif
    
    _pid->SetTunings(_kp, _ki, _kd);
    _prevKp = _kp; _prevKi = _ki; _prevKd = _kd;
}

void RoverNavigator::updatePID() {
    double rawDirection;
#if USE_DISTANCE_LOW_PASS_FILTER
    _pidInput = _lowPassFilter->filteredValue(rawDirection);
#else
    _pidInput = rawDirection;
#endif
    
    _pid->Compute();
    
#if LOG_PID_OUTPUT
    if (_pidOutput != _prevPidOutput) {
        Serial.print("PID OUTPUT: ");Serial.println(_pidOutput);
        _prevPidOutput = _pidOutput;
    }
#endif
}

void RoverNavigator::updateMovement() {
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
