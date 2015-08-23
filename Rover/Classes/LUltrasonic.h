#ifndef LUltrasonic_h
#define LUltrasonic_h

#include <Arduino.h>
#include "LLCD.h"
#include "LDebugLog.h"
#include "NewPing.h"

#define LULTRASONIC_INFINITE_DISTANCE 999999
#define MAX_MEASUREABLE_DISTANCE 60

class LUltrasonic : public LDebugLog {
private:
    unsigned long singleDistanceMeasurement();
    unsigned long _distance;
    NewPing *_sonic;
public:
    LUltrasonic(unsigned int echoPin, unsigned int triggerPin);
    
    void measureDistance();
    void measureDistance3();
    
    unsigned long distance();
    
    virtual void printToSerial();
    virtual void printToLCD(LLCD *lcd);
};

#endif
