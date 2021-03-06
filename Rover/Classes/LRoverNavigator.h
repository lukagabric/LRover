#ifndef LRoverNavigator_h
#define LRoverNavigator_h

#include "Arduino.h"
#include "LMotorController.h"
#include "LPID.h"
#include "LUltrasonic.h"
#include "LCompass.h"
#include "LLCD.h"
#include "LGPS.h"
#include "LPIDTuner.h"
#include "LLogger.h"
#include "vector"
#include "LRoverSonics.h"
#include "LGPSLogger.h"
#include "LPIDLogger.h"
#include "LCompassLogger.h"
#include "LMotorControllerLogger.h"
#include "LRoverSonicsLogger.h"
#include "LGeoLocation.h"
#include "LWheelSpeeds.h"
#include "LCruiseController.h"
#include "LWallFollowController.h"

#define DEBUG_LOG 1
#define LCD_DEBUG_LOG 1
#define MANUAL_PID_TUNING 0
#define DRIVE 1

#define GOAL_RADIUS_METERS 1

//Ultrasonic

#define SONIC_FRONT_ECHO 12
#define SONIC_FRONT_TRIG 12

#define SONIC_FRONT_RIGHT_ECHO A0
#define SONIC_FRONT_RIGHT_TRIG A0

#define SONIC_FRONT_LEFT_ECHO 13
#define SONIC_FRONT_LEFT_TRIG 13

#define SONIC_RIGHT_ECHO 8
#define SONIC_RIGHT_TRIG 8

#define SONIC_LEFT_ECHO 9
#define SONIC_LEFT_TRIG 9

#define FRONT_OBSTACLE_DISTANCE_THRESHOLD 35
#define SIDE_OBSTACLE_DISTANCE_THRESHOLD 30
#define OBSTACLE_CLEARED_DISTANCE_THRESHOLD 45

//Motor Controller
#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 7
#define ENB 6
#define MINIMUM_FORWARD_WHEEL_SPEED 10

//PID
#define Kp 15
#define Ki 0.01
#define Kd 0.12
#define POT_Kp A7
#define POT_Ki A6
#define POT_Kd A1

//Low-Pass Filter
//#define LPF_RC 0.05
//#define LPF_DT 1/20.0

enum LRoverState {LRoverStateInitialization = 0, LRoverStateCruise = 1, LRoverStateWallFollow = 2, LRoverStateGoalReached = 3};

class LRoverNavigator {
private:
    LRoverState _state;
    
    LGeoLocation _goalLocation;

    LLCD *_lcd;
    LGPSLogger *_gpsLogger;
    LGPS *_gps;
    LMotorController *_motorController;
    LMotorControllerLogger *_motorControllerLogger;
    LPID *_cruisePID;
    LPIDTuner *_cruisePIDTuner;
    LPIDLogger *_cruisePIDLogger;
    LCruiseController *_cruiseController;
    LCompass *_compass;
    LCompassLogger *_compassLogger;
    LRoverSonics *_sonics;
    LRoverSonicsLogger *_sonicsLogger;
    LWallFollowController *_wallFollowController;
    LPID *_wallFollowPID;
    LPIDTuner *_wallFollowPIDTuner;
    LPIDLogger *_wallFollowPIDLogger;
    LLogger *_logger;
    
    unsigned long _timeInit, _mainLoopTime20Hz, _loggingAndTuningTime1Hz, _loggingAndTuningTime5s;
    void initializationLoop();
    void mainLoopAt20Hz();
    void loggingAndTuningLoopAt5s();
    void loggingAndTuningLoopAt1Hz();
    
    void updateSensorReadings();

    void readLocation();
    
    bool isCurrentEqualToGoalLocation();
    void arrivedAtGoal();
        
    bool shouldForceCruiseAndIgnoreObstacle(LObstacleDistances obstacleDistances);

    void debugLogToLCD();
    void debugLog();
    
public:
    void setup();
    void loop();
};

#endif
