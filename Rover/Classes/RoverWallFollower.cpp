#include "RoverWallFollower.h"
#include "Arduino.h"
#include "PID_v1.h"
#include "LUltrasonic.h"

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
#if DEBUG_LOG
    Serial.begin(9600);
#endif
    _sonic = new LUltrasonic(SONIC_ECHO_PIN, SONIC_TRIG_PIN);
    _sonicLPF = new LLowPassFilter(LPF_RC, LPF_DT);

    _motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
    
    _goalDistance = TARGET_WALL_DISTANCE;
    _pid = new PID(&_currentDistance, &_pidOutput, &_goalDistance, Kp, Ki, Kd, DIRECT);
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
    configurePIDConstants();
#endif
#if DEBUG_LOG
    debugLog();
#endif
}

void RoverWallFollower::loopAt20Hz() {
    configurePIDOutput();
    configureMovement();
}

#pragma mark - Operations

#if MANUAL_PID_TUNING
void RoverWallFollower::configurePIDConstants() {
    int potKp = analogRead(A0);
    int potKi = analogRead(A1);
    int potKd = analogRead(A2);
    
    _kp = map(potKp, 0, 1023, 0, 25000) / 100.0; //0 - 250
    _ki = map(potKi, 0, 1023, 0, 100000) / 100.0; //0 - 1000
    _kd = map(potKd, 0, 1023, 0, 500) / 100.0; //0 - 5
    
    _pid->SetTunings(_kp, _ki, _kd);
}
#endif

void RoverWallFollower::configurePIDOutput() {
    double rawDistance = _sonic->measureDistance();

#if USE_DISTANCE_LOW_PASS_FILTER
    _currentDistance = _lowPassFilter->filteredValue(rawDistance);
#else
    _currentDistance = rawDistance;
#endif

    _pid->Compute();
}

void RoverWallFollower::configureMovement() {
    _rightWheelSpeed = 255;
    _leftWheelSpeed = 255;
    
    if (_pidOutput < 0) {
        //too far, turn right
        _rightWheelSpeed += _pidOutput;
        _rightWheelSpeed = max(MINIMUM_WHEEL_SPEED, _rightWheelSpeed);
    }
    else {
        //too close, turn left
        _leftWheelSpeed -= _pidOutput;
        _leftWheelSpeed = max(MINIMUM_WHEEL_SPEED, _leftWheelSpeed);
    }
    
#if DRIVE
    _motorController->move(_leftWheelSpeed, _rightWheelSpeed);
#endif
}

#if DEBUG_LOG
void RoverWallFollower::debugLog() {
    Serial.print("\nDISTANCE: ");Serial.println(_currentDistance);
    Serial.print("\nKp: ");Serial.print(_kp);Serial.print("    Ki:");Serial.print(_ki);Serial.print("    Kd:");Serial.println(_kd);
    Serial.print("\nPID OUTPUT: ");Serial.println(_pidOutput);
    Serial.print("\nRW: ");Serial.print(_rightWheelSpeed);Serial.print("    LW: ");Serial.println(_leftWheelSpeed);
}
#endif

#pragma mark -
