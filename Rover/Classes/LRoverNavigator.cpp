#include "LRoverNavigator.h"
#include "Arduino.h"
#include <Wire.h>
#include "LUltrasonic.h"
#include "LDebugLog.h"

#pragma mark - Setup

void LRoverNavigator::setup() {
#if DEBUG_LOG
    Serial.begin(9600);
    Serial.println("Starting...");
#endif

    delay(100);
    
    _compass = new LCompass(NULL);
    _compass->setDeclinationDeg(4.183333);
    
    _gps = new LGPS();
    _gps->_goalLat = GOAL_LAT;
    _gps->_goalLon = GOAL_LON;
    
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
    if (_atGoal) return;
    
    _gps->readGPSData();
    
    unsigned long currentTime = millis();
    
    if (currentTime - _time20Hz >= 50) {
        _time20Hz = currentTime;
        loopAt20Hz();
    }
    if (currentTime - _time1Hz >= 1000) {
        _time1Hz = currentTime;
        loopAt1Hz();
    }
    if (currentTime - _time5s >= 5000) {
        _time5s = currentTime;
        loop5s();
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
}

void LRoverNavigator::loopAt20Hz() {
    if (!_gps->isLocationValid()) return;

    if (newGPSData()) {
        if (currentEqualsGoalLocation()) {
            arrivedAtGoal();
            return;
        }
        
        configureHeading();
    }
    
    configureMovement();
}

#pragma mark - Operations

bool LRoverNavigator::newGPSData() {
    if (_lat != _gps->latitude() || _lon != _gps->longitude()) {
        _lat = _gps->latitude();
        _lon = _gps->longitude();
        
        return true;
    }
    
    return false;
}

bool LRoverNavigator::currentEqualsGoalLocation() {
    float distanceToLocation = _gps->distanceTo(GOAL_LAT, GOAL_LON);
    return distanceToLocation < GOAL_RADIUS_METERS;
}

void LRoverNavigator::arrivedAtGoal() {
    _atGoal = true;
    
    _motorController->turnLeft(255, false);
    delay(4000);
    _motorController->stopMoving();
    delay(300);
    _motorController->turnRight(255, false);
    delay(4000);
    _motorController->stopMoving();
}


void LRoverNavigator::configureHeading() {
    double goalHeadingDeg = _gps->bearingDegTo(GOAL_LAT, GOAL_LON);
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
