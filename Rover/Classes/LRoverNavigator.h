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

#define DEBUG_LOG 1
#define LCD_DEBUG_LOG 1
#define MANUAL_PID_TUNING 1
#define DRIVE 1

//Centar terena Sloga, Ernestinovo: 45.452608, 18.662766

//Pet Centar
//#define GOAL_LAT 45.550991058349609
//#define GOAL_LON 18.692028045654296

//Dvorište, Ernestinovo
//#define GOAL_LAT 45.453231811523437
//#define GOAL_LON 18.661836624145507

//Prilaz kući, Ernestinovo
#define GOAL_LAT 45.452903747558593
#define GOAL_LON 18.662023544311523

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

class LRoverNavigator {
private:
    bool _atGoal;
    
    LLCD *_lcd;
    LGPSLogger *_gpsLogger;
    LGPS *_gps;
    LMotorController *_motorController;
    LMotorControllerLogger *_motorControllerLogger;
    LPIDTuner *_cruisePIDTuner;
    LPID *_cruisePID;
    LPIDLogger *_cruisePIDLogger;
    LCruiseController *_cruiseController;
    LCompass *_compass;
    LCompassLogger *_compassLogger;
    LRoverSonics *_sonics;
    LRoverSonicsLogger *_sonicsLogger;
    LLogger *_logger;
    
    LGeoLocation _goalLocation;
    
    unsigned long _time1Hz, _time20Hz, _time5s;
    void loopAt5s();
    void loopAt1Hz();
    void loopAt20Hz();
    
    void updateSensorReadings();

    void readLocation();
    
    bool isCurrentEqualToGoalLocation();
    void arrivedAtGoal();
        
    LWheelSpeeds wallFollowOutput();
    
    void move(int leftWheelSpeed, int rightWheelSpeed);
    
    void debugLogToLCD();
    void debugLog();
    
public:
    void setup();
    void loop();
};

#endif
