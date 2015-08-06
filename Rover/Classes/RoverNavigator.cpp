#include "RoverNavigator.h"
#include "Arduino.h"
#include "PID_v1.h"
#include "LUltrasonic.h"
#include <Wire.h>

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
#define LPF_RC 0.05
#define LPF_DT 1/20.0

#pragma mark - Setup

void RoverNavigator::setup() {
#if DEBUG_LOG
    Serial.begin(9600);
#endif
    
    delay(100);
    
#if ENABLE_LCD
    _lcd = new LLCD();
#endif

    _compass = new LCompass();
    _compassLPF = new LLowPassFilter(LPF_RC, LPF_DT);

    _gps = new LGPS();
    
    _motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
    
    _goalHeading = 262; //S
    _pidSetpoint = 0;
    _pid = new PID(&_headdingOffset, &_pidOutput, &_pidSetpoint, Kp, Ki, Kd, DIRECT);
#if MANUAL_PID_TUNING
    _pid->SetTunings(_kp, _ki, _kd);
#endif
    _pid->SetMode(AUTOMATIC);
    _pid->SetSampleTime(50);
    _pid->SetOutputLimits(-255, 255);
}

#pragma mark - Loop

void RoverNavigator::loop() {
    unsigned long currentTime = millis();
    
    if (currentTime - _time15s >= 15000) {
        _time15s = currentTime;
        loop15s();
    }
    if (currentTime - _time1Hz >= 1000) {
        _time1Hz = currentTime;
        loopAt1Hz();
    }
    if (currentTime - _time20Hz >= 50) {
        _time20Hz = currentTime;
        loopAt20Hz();
    }
}

void RoverNavigator::loop15s() {
    //E = 166; N = 28; W = 321; S = 262
    
    switch (state) {
        case 0:
            _goalHeading = 166; //E
            break;
        case 1:
            _goalHeading = 28; //N
            break;
        case 2:
            _goalHeading = 321; //W
            break;
        default:
            _goalHeading = 262; //S
            break;
    }
    
    state = ++state % 4;
}

void RoverNavigator::loopAt1Hz() {
    _gps->location(&_lat, &_lon, &_age);

#if ENABLE_LCD
    printToLCD();
#endif
    
#if MANUAL_PID_TUNING
    configurePIDConstants();
#endif
    
#if DEBUG_LOG
    debugLog();
#endif
}

void RoverNavigator::loopAt20Hz() {
    configurePIDOutput();
    configureMovement();
}

#pragma mark - Operations

#if MANUAL_PID_TUNING
void RoverNavigator::configurePIDConstants() {
    int potKp = analogRead(A0);
    int potKi = analogRead(A1);
    int potKd = analogRead(A2);
    
    _kp = map(potKp, 0, 1023, 0, 25000) / 100.0; //0 - 250
    _ki = map(potKi, 0, 1023, 0, 100000) / 100.0; //0 - 1000
    _kd = map(potKd, 0, 1023, 0, 500) / 100.0; //0 - 5
    
    _pid->SetTunings(_kp, _ki, _kd);
}
#endif

void RoverNavigator::configurePIDOutput() {
    double rawHeading = _compass->headingDeg();
    
#if USE_COMPASS_LOW_PASS_FILTER
    _currentHeading = _compassLPF->filteredValue(rawHeading);
#else
    _currentHeading = rawHeading;
#endif
    
    _headdingOffset = _compass->headingOffset(_goalHeading, _currentHeading);
    
    _pid->Compute();
}

void RoverNavigator::configureMovement() {
    _rightWheelSpeed = 255;
    _leftWheelSpeed = 255;
    
    if (_pidOutput < 0) {
        //turn right
        _rightWheelSpeed += _pidOutput;
        _rightWheelSpeed = max(MINIMUM_WHEEL_SPEED, _rightWheelSpeed);
    }
    else {
        //turn left
        _leftWheelSpeed -= _pidOutput;
        _leftWheelSpeed = max(MINIMUM_WHEEL_SPEED, _leftWheelSpeed);
    }
    
#if DRIVE
    _motorController->move(_leftWheelSpeed, _rightWheelSpeed);
#endif
}

#pragma mark - Debug

#if ENABLE_LCD
void RoverNavigator::printToLCD() {
    if (_gps->locationValid(_lat, _lon)) {
        _lcd->print(0, 0, "LAT=");
        _lcd->print(4, 0, _lat, 8);
        _lcd->print(0, 1, "LON=");
        _lcd->print(4, 1, _lon, 8);
    }
    else {
#if ENABLE_LCD
        _lcd->print(0, 0, "LOCATION");
        _lcd->print(0, 1, "UNAVAILABLE");
#endif
    }
}
#endif

#if DEBUG_LOG
void RoverNavigator::debugLog() {
    Serial.println("\n==================================================================================================");
    if (_gps->locationValid(_lat, _lon)) {
        Serial.print("\nLAT: ");Serial.print(_lat);Serial.print("    LON: ");Serial.print(_lon);Serial.print("    AGE: ");Serial.println(_age);
    }
    else {
        Serial.println("\nLOCATION UNAVAILABLE");
    }
    Serial.print("\nCURRENT HEADING: ");Serial.print(_currentHeading);Serial.print("    GOAL HEADING: ");Serial.print(_goalHeading);Serial.print("    HEADING OFFSET: ");Serial.println(_headdingOffset);
    Serial.print("\nKp: ");Serial.print(_kp);Serial.print("    Ki:");Serial.print(_ki);Serial.print("    Kd:");Serial.println(_kd);
    Serial.print("\nPID OUTPUT: ");Serial.println(_pidOutput);
    Serial.print("\nRW: ");Serial.print(_rightWheelSpeed);Serial.print("    LW: ");Serial.println(_leftWheelSpeed);
}
#endif

#pragma mark -
