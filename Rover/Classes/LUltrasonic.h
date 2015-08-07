#ifndef LUltrasonic_h
#define LUltrasonic_h

#include <Arduino.h>
#include "LLCD.h"

#define LULTRASONIC_INFINITE_DISTANCE 999999

class LUltrasonic {
private:
    unsigned int _echoPin, _triggerPin;
    unsigned long singleDistanceMeasurement();
    unsigned long _distance;
public:
    LUltrasonic(unsigned int echoPin, unsigned int triggerPin);
    
    void measureDistance();
    void measureDistance3();
    
    unsigned long distance();
    
    void printDistanceToLCD(LLCD *lcd);
    void printDistanceToSerial();
};

#endif
