#include "Arduino.h"
#include "LRoverNavigator.h"
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
    
    _sonics = new LRoverSonics();
    
    _goalLocation = LGeoLocation(GOAL_LAT, GOAL_LON);
    
    _gps = new LGPS();
    _gps->setGoalLocation(_goalLocation);
    
#if DRIVE
    _motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
#endif 
    
    _cruisePID = new LPID(Kp, Ki, Kd, DIRECT);
    _cruisePID->SetMode(AUTOMATIC);
    _cruisePID->SetOutputLimits(-255, 255);
    _cruisePID->SetSampleTime(50);
    
    _cruiseController = new LCruiseController(_cruisePID);
    _cruiseController->minimumForwardWheelSpeed = MINIMUM_FORWARD_WHEEL_SPEED;
    
    _wallFollowPID = new LPID(Kp, Ki, Kd, DIRECT);
    _wallFollowPID->SetMode(AUTOMATIC);
    _wallFollowPID->SetOutputLimits(-255, 255);
    _wallFollowPID->SetSampleTime(50);
    _wallFollowPID->setSetpoint(WALL_FOLLOW_DISTANCE_SETPOINT);
    
    _wallFollowController = new LWallFollowController(_wallFollowPID);
    
#if MANUAL_PID_TUNING
//    _cruisePIDTuner = new LPIDTuner(_cruisePID, POT_Kp, POT_Ki, POT_Kd);
    _wallFollowPIDTuner = new LPIDTuner(_wallFollowPID, POT_Kp, POT_Ki, POT_Kd);
#endif
    
#if LCD_DEBUG_LOG
    _lcd = new LLCD();
#endif

#if DEBUG_LOG || LCD_DEBUG_LOG
    std::vector<LDebugLog*> logItems;
    
    if (_sonics) {
        _sonicsLogger = new LRoverSonicsLogger(_sonics);
        logItems.push_back(_sonicsLogger);
    }
    if (_gps) {
        _gpsLogger = new LGPSLogger(_gps);
        logItems.push_back(_gpsLogger);
    }
    if (_compass) {
        _compassLogger = new LCompassLogger(_compass);
        logItems.push_back(_compassLogger);
    }
    if (_cruisePID) {
        _cruisePIDLogger = new LPIDLogger(_cruisePID);
        logItems.push_back(_cruisePIDLogger);
    }
    if (_wallFollowPID) {
        _wallFollowPIDLogger = new LPIDLogger(_wallFollowPID);
        logItems.push_back(_wallFollowPIDLogger);
    }
    if (_motorController) {
        _motorControllerLogger = new LMotorControllerLogger(_motorController);
        logItems.push_back(_motorControllerLogger);
    }
    
    _logger = new LLogger(_lcd, logItems);
#endif
}

#pragma mark - Loop

void LRoverNavigator::loop() {
    if (_atGoal) return;
    
    unsigned long currentTime = millis();
    
    if (currentTime - _time20Hz >= 50) {
        _time20Hz = currentTime;
        loopAt20Hz();
    }
    
    currentTime = millis();
    if (currentTime - _time20Hz > 20) return;
    
    _gps->readGPSData();
    if (currentTime - _time1Hz >= 1000) {
        _time1Hz = currentTime;
        loopAt1Hz();
    }
    if (currentTime - _time5s >= 5000) {
        _time5s = currentTime;
        loopAt5s();
    }
}

void LRoverNavigator::loopAt5s() {
#if LCD_DEBUG_LOG
    _logger->skipNextDebugLogToLCD();
#endif    
}

void LRoverNavigator::loopAt1Hz() {
#if MANUAL_PID_TUNING
    _cruisePIDTuner->configurePIDConstants();
#endif
#if DEBUG_LOG
    _logger->debugLogToSerial();
#endif
#if LCD_DEBUG_LOG
    _logger->debugLogToLCD();
#endif
}

void LRoverNavigator::loopAt20Hz() {
    //perception
    updateSensorReadings();

    //localization
    LGeoLocation currentLocation = _gps->location();
    
    //path planning
    if (currentLocation.isValid() && isCurrentEqualToGoalLocation()) {
        arrivedAtGoal();
        return;
    }

    bool followWall = _sonics->isObstacleTooClose();
    
    LWheelSpeeds wheelSpeeds;
    if (followWall) {
        wheelSpeeds = wallFollowOutput();
    }
    else {
        wheelSpeeds = _cruiseController->cruiseOutput(currentLocation, _goalLocation, _compass->headingDeg());
    }
    
    //path execution
#if DRIVE
    _motorController->move(wheelSpeeds.leftWheelSpeed, wheelSpeeds.rightWheelSpeed);
#endif
}

#pragma mark - Perception

void LRoverNavigator::updateSensorReadings() {
    _sonics->performNextMeasurement();
    _compass->updateHeading();
}

#pragma mark - Path Planning

bool LRoverNavigator::isCurrentEqualToGoalLocation() {
    float distanceToLocation = _gps->distanceToGoalLocation();
    return distanceToLocation < GOAL_RADIUS_METERS;
}

void LRoverNavigator::arrivedAtGoal() {
    _atGoal = true;
    
    _motorController->turnLeft(255, false);
    delay(4000);
    _motorController->stopMoving();
}

#pragma mark - Wall Follow

LWheelSpeeds LRoverNavigator::wallFollowOutput() {
    return {0, 0};
}

#pragma mark -
