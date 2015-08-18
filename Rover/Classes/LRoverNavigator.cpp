#include "LRoverNavigator.h"
#include "Arduino.h"
#include <Wire.h>
#include "LUltrasonic.h"
#include "LDebugLog.h"

#define goalLat 10
#define goalLon 10

#pragma mark - Setup

void LRoverNavigator::setup() {
#if DEBUG_LOG
    Serial.begin(9600);
    Serial.println("Starting...");
#endif

    delay(100);
    
    _compass = new LCompass(NULL);

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
    
#if LCD_DEBUG_LOG
    _lcd = new LLCD();
#endif

#if DEBUG_LOG || LCD_DEBUG_LOG
    std::vector<LDebugLog*> logItems;
    
    if (_gps) logItems.push_back(_gps);
    if (_compass) logItems.push_back(_compass);
    if (_pid) logItems.push_back(_pid);
    if (_motorController) logItems.push_back(_motorController);
    
    _logger = new LLogger(_lcd, logItems);
#endif
}

#pragma mark - Loop

void LRoverNavigator::loop() {
    _gps->readGPSData();
    
    unsigned long currentTime = millis();
    
    if (currentTime - _time5s >= 5000) {
        _time5s = currentTime;
        loop5s();
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

void LRoverNavigator::loop5s() {
#if LCD_DEBUG_LOG
    _logger->skipNextDebugLogToLCD();
#endif    
}

void LRoverNavigator::loopAt1Hz() {
#if MANUAL_PID_TUNING
    _pidTuner->configurePIDConstants();
#endif
#if DEBUG_LOG
    _logger->debugLogToSerial();
#endif
#if LCD_DEBUG_LOG
    _logger->debugLogToLCD();
#endif
    configureGoalHeading();
}

void LRoverNavigator::loopAt20Hz() {
    configureMovement();
}

#pragma mark - Operations

void LRoverNavigator::configureGoalHeading() {
    float goalHeadingDeg = _gps->bearingDegTo(goalLat, goalLon);
    if (goalHeadingDeg < 0) return;
    
    _compass->setGoalHeadingDeg(goalHeadingDeg);
}

void LRoverNavigator::configureMovement() {
    _compass->updateHeading();
    _pid->setInput(_compass->offsetFromGoalHeadingDeg());
    _pid->Compute();
    
#if DRIVE
    _motorController->move(_pid->output(), MINIMUM_WHEEL_SPEED);
#endif
}

#pragma mark -
