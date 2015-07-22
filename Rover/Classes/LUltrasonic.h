#ifndef LUltrasonic_h
#define LUltrasonic_h

#include <Arduino.h>

class LUltrasonic {
  protected:
    unsigned int _echoPin, _triggerPin;
  public:
    LUltrasonic(unsigned int echoPin, unsigned int triggerPin);
    unsigned long measureDistance();
    unsigned long measureDistance3();
};

#endif
