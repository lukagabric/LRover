#ifndef LUltrasonic_h
#define LUltrasonic_h

#include <Arduino.h>
#include "NewPing.h"

#define LULTRASONIC_INFINITE_DISTANCE 999999
#define MAX_MEASUREABLE_DISTANCE 60

class LUltrasonic {
private:
    NewPing *_sonic;
    unsigned long singleDistanceMeasurement();
    unsigned long _distance;
public:
    LUltrasonic(unsigned int echoPin, unsigned int triggerPin);
    ~LUltrasonic();
    
    void measureDistance();
    void measureDistance3();
    
    unsigned long distance();    
};

#endif
