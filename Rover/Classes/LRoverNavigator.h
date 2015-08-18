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

#define DEBUG_LOG 1
#define LCD_DEBUG_LOG 1
#define MANUAL_PID_TUNING 1
#define DRIVE 0

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

class LRoverNavigator {
private:
    LLCD *_lcd;
    LGPS *_gps;
    LMotorController *_motorController;
    LPIDTuner *_pidTuner;
    LPID *_pid;
    LCompass *_compass;
    LLogger *_logger;
        
    unsigned long _time1Hz, _time20Hz, _time5s;
    void loop5s();
    void loopAt1Hz();
    void loopAt20Hz();
    
    void configureMovement();
    
    void debugLogToLCD();
    void debugLog();
public:
    void setup();
    void loop();
};

#endif
