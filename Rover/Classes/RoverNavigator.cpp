#include "RoverNavigator.h"
#include "Arduino.h"
#include "LUltrasonic.h"
#include <Wire.h>
#include "LLowPassFilter.h"

#define DEBUG_LOG 1
#define LCD_DEBUG_LOG 1
#define MANUAL_PID_TUNING 1
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

//Low-Pass Filter
#define LPF_RC 0.05
#define LPF_DT 1/20.0

#pragma mark - Setup

void RoverNavigator::setup() {
#if DEBUG_LOG
    Serial.begin(9600);
#endif
    
    delay(100);
    
#if LCD_DEBUG_LOG
    _lcd = new LLCD();
#endif

    LLowPassFilter *compassLPF = new LLowPassFilter(LPF_RC, LPF_DT);
    _compass = new LCompass(compassLPF);

    _gps = new LGPS();
    
#if DRIVE
    _motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
#endif
    
    _pid = new LPID(Kp, Ki, Kd, DIRECT);
    _pid->SetMode(AUTOMATIC);
    _pid->SetOutputLimits(-255, 255);
    _pid->SetSampleTime(50);
    
#if MANUAL_PID_TUNING
    _pidTuner = new LPIDTuner(_pid);
#endif
}

#pragma mark - Loop

void RoverNavigator::loop() {
    _gps->readGPSData();
    
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
    
}

void RoverNavigator::loopAt1Hz() {
#if LCD_DEBUG_LOG
    debugLogToLCD();
#endif
    
#if MANUAL_PID_TUNING
    _pidTuner->configurePIDConstants();
#endif
    
#if DEBUG_LOG
    debugLog();
#endif
}

void RoverNavigator::loopAt20Hz() {
    configureMovement();
}

#pragma mark - Operations

void RoverNavigator::configureMovement() {
    _compass->updateHeading();
    _pid->setInput(_compass->offsetFromGoalHeading());
    _pid->Compute();
    
#if DRIVE
    _motorController->move(_pid->output(), MINIMUM_WHEEL_SPEED);
#endif
}

#pragma mark - Debug

void RoverNavigator::debugLogToLCD() {
//    switch (state) {
//        case 0:
//            _goalHeading = 166; //E
//            break;
//        case 1:
//            _goalHeading = 28; //N
//            break;
//        case 2:
//            _goalHeading = 321; //W
//            break;
//        default:
//            _goalHeading = 262; //S
//            break;
//    }
//    
//    state = ++state % 4;
}

void RoverNavigator::debugLog() {
    Serial.println("\n==================================================================================================");
    _gps->printLocationToSerial();
    _compass->printHeadingToSerial();
    _pid->printPIDToSerial();
    _motorController->printSpeedToSerial();
}

#pragma mark -
