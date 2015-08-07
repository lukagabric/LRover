//
//  LCompass.h
//  Rover
//
//  Created by Luka Gabric on 04/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LCompass__
#define __Rover__LCompass__

#include <Arduino.h>
#include "HMC5883L.h"
#include "LLowPassFilter.h"
#include "LLCD.h"

class LCompass {
private:
    HMC5883L *_compass;
    LLowPassFilter *_filter;
    int16_t _mx, _my, _mz;
    double _headingDeg;
    double _goalHeading;
public:
    LCompass(LLowPassFilter *filter);
    
    void updateHeading();
    
    double headingDeg();
    
    void setGoalHeading(double goalHeading);
    double goalHeading();
    
    double offsetFromGoalHeading(); //Direction: CCW
    
    void printHeadingToLCD(LLCD *lcd);
    void printHeadingToSerial();
};

#endif /* defined(__Rover__LCompass__) */
