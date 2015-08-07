#ifndef LUltrasonic_h
#define LUltrasonic_h

#include <Arduino.h>

#define LULTRASONIC_INFINITE_DISTANCE 999999

class LUltrasonic {
  protected:
    unsigned int _echoPin, _triggerPin;
    unsigned long measuredDistance();
  public:
    LUltrasonic(unsigned int echoPin, unsigned int triggerPin);
    
    void updateDistance();
    void updateDistance3();
    
    unsigned long distance;
};

#endif
