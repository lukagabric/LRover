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
    
    _gps = new LGPS();
    _gps->_goalLat = GOAL_LAT;
    _gps->_goalLon = GOAL_LON;
    
#if DRIVE
    _motorController = new LMotorController(ENA, IN1, IN2, ENB, IN3, IN4, 1, 1);
#endif 
    
    _cruisePID = new LPID(Kp, Ki, Kd, DIRECT);
    _cruisePID->SetMode(AUTOMATIC);
    _cruisePID->SetOutputLimits(-255, 255);
    _cruisePID->SetSampleTime(50);
    
#if MANUAL_PID_TUNING
    _cruisePIDTuner = new LPIDTuner(_cruisePID, POT_Kp, POT_Ki, POT_Kd);
#endif
    
#if LCD_DEBUG_LOG
    _lcd = new LLCD();
#endif

#if DEBUG_LOG || LCD_DEBUG_LOG
    std::vector<LDebugLog*> logItems;
    
    if (_sonics) logItems.push_back(_sonics);
    
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
    readLocation();
    
    //path planning
    if (_locationChanged && isCurrentEqualToGoalLocation()) {
        arrivedAtGoal();
        return;
    }

    bool followWall = _sonics->isObstacleTooClose();
    int leftWheelSpeed, rightWheelSpeed;

    if (followWall) {
        configureWallFollowOutput(&leftWheelSpeed, &rightWheelSpeed);
    }
    else {
        configureCruiseOutput(&leftWheelSpeed, &rightWheelSpeed);
    }
    
    //path execution
    move(leftWheelSpeed, rightWheelSpeed);
}

#pragma mark - Perception

void LRoverNavigator::updateSensorReadings() {
    _sonics->performNextMeasurement();
    _compass->updateHeading();
}

#pragma mark - Localization

void LRoverNavigator::readLocation() {
    if (_gps->isLocationValid() && (_lat != _gps->latitude() || _lon != _gps->longitude())) {
        _lat = _gps->latitude();
        _lon = _gps->longitude();
        
        _locationChanged = true;
    }
    else {
        _locationChanged = false;
    }
}

#pragma mark - Path Planning

bool LRoverNavigator::isCurrentEqualToGoalLocation() {
    float distanceToLocation = _gps->distanceTo(GOAL_LAT, GOAL_LON);
    return distanceToLocation < GOAL_RADIUS_METERS;
}

void LRoverNavigator::arrivedAtGoal() {
    _atGoal = true;
    
    _motorController->turnLeft(255, false);
    delay(4000);
    _motorController->stopMoving();
}

#pragma mark - Cruise

void LRoverNavigator::configureCruiseOutput(int *leftWheelSpeed, int *rightWheelSpeed) {
    if (!_gps->isLocationValid()) return;
    
    if (_locationChanged) {
        configureCruiseGoalHeading();
    }
    
    updateCruisePID();
    configureCruiseWheelSpeeds(leftWheelSpeed, rightWheelSpeed);
}

void LRoverNavigator::configureCruiseGoalHeading() {
    double goalHeadingDeg = _gps->bearingDegTo(GOAL_LAT, GOAL_LON);
    _compass->setGoalHeadingDeg(goalHeadingDeg);
}

void LRoverNavigator::updateCruisePID() {
    _cruisePID->setInput(_compass->offsetFromGoalHeadingDeg());
    _cruisePID->Compute();
}

void LRoverNavigator::configureCruiseWheelSpeeds(int *leftSpeed, int *rightSpeed) {
    int leftWheelSpeed = 255;
    int rightWheelSpeed = 255;
    
    double pidOutput = _cruisePID->output();
    
    if (pidOutput > 0) {
        //turn left
        leftWheelSpeed -= pidOutput;
        leftWheelSpeed = std::max(MINIMUM_FORWARD_WHEEL_SPEED, leftWheelSpeed);
    }
    else {
        //turn right
        rightWheelSpeed += pidOutput;
        rightWheelSpeed = std::max(MINIMUM_FORWARD_WHEEL_SPEED, rightWheelSpeed);
    }
    
    *leftSpeed = leftWheelSpeed;
    *rightSpeed = rightWheelSpeed;
}

#pragma mark - Wall Follow

void LRoverNavigator::configureWallFollowOutput(int *leftWheelSpeed, int *rightWheelSpeed) {
    *leftWheelSpeed = 0;
    *rightWheelSpeed = 0;
}

#pragma mark - Path Execution

void LRoverNavigator::move(int leftWheelSpeed, int rightWheelSpeed) {
#if DRIVE
    _motorController->move(leftWheelSpeed, rightWheelSpeed);
#endif
}

#pragma mark -
