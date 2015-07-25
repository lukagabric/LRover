#include "RoverWallFollower.h"
#include "Arduino.h"
#include "PID_v1.h"
#include "LUltrasonic.h"

#define LOG_PID_CONSTANTS 1
#define LOG_MOVEMENT 1
#define MANUAL_TUNING 1
#define DRIVE 0

//Motor Controller
#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 7
#define ENB 6

#define MIN_WHEEL_SPEED 30

//PID Constants
#define Kp 5
#define Ki 10
#define Kd 2

//Ultrasonic
#define SONIC_ECHO_PIN 9
#define SONIC_TRIG_PIN 8
#define SONIC_WALL_DISTANCE 50

#pragma mark - Setup

void RoverWallFollower::setup() {
#if LOG_PID_CONSTANTS || LOG_MOVEMENT
    Serial.begin(9600);
#endif
    _sonic = new LUltrasonic(SONIC_ECHO_PIN, SONIC_TRIG_PIN);

    _motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
    
    _pidSetpoint = 30;
    _pid = new PID(&_pidInput, &_pidOutput, &_pidSetpoint, Kp, Ki, Kd, DIRECT);
#if MANUAL_TUNING
    _pid->SetTunings(_kp, _ki, _kd);
#endif
    _pid->SetMode(AUTOMATIC);
    _pid->SetSampleTime(10);
    _pid->SetOutputLimits(-255, 255);
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
#if MANUAL_TUNING
    updatePIDConstants();
#endif
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

#if MANUAL_TUNING
void RoverWallFollower::updatePIDConstants() {
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
#endif

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

#if LOG_MOVEMENT
    Serial.print("\tDST=");Serial.print(_pidInput);Serial.print("\tRW=");Serial.print(rightWheelSpeed);Serial.print("\tLW");Serial.println(leftWheelSpeed);
#endif

#if DRIVE
    _motorController->move(leftWheelSpeed, rightWheelSpeed);
#endif
}

#pragma mark -
