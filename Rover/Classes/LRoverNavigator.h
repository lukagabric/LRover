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

#define DEBUG_LOG 0
#define LCD_DEBUG_LOG 1
#define MANUAL_PID_TUNING 0
#define DRIVE 1

#define GOAL_LAT 45.550991058349609
#define GOAL_LON 18.692028045654296
#define GOAL_RADIUS_METERS 5

//Motor Controller
#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 5
#define IN4 7
#define ENB 6
#define MINIMUM_WHEEL_SPEED 10

//PID Constants
#define Kp 15
#define Ki 0.01
#define Kd 0.12

//Low-Pass Filter
//#define LPF_RC 0.05
//#define LPF_DT 1/20.0

class LRoverNavigator {
private:
    bool _atGoal;
    
    LLCD *_lcd;
    LGPS *_gps;
    LMotorController *_motorController;
    LPIDTuner *_pidTuner;
    LPID *_pid;
    LCompass *_compass;
    LLogger *_logger;
    
    float _lat, _lon;
        
    unsigned long _time1Hz, _time20Hz, _time5s;
    void loop5s();
    void loopAt1Hz();
    void loopAt20Hz();
    
    bool newGPSData();
    
    void configureHeading();
    void configureMovement();
    
    bool currentEqualsGoalLocation();
    void arrivedAtGoal();
    
    void debugLogToLCD();
    void debugLog();
public:
    void setup();
    void loop();
};

#endif
