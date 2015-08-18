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
#include "LDebugLog.h"

class LCompass : public LDebugLog {
private:
    HMC5883L *_compass;
    LLowPassFilter *_filter;
    int16_t _mx, _my, _mz;
    double _headingDeg;
    double _goalHeadingDeg;
public:
    LCompass(LLowPassFilter *filter);
    
    void updateHeading();
    
    double headingDeg();
    
    void setGoalHeadingDeg(double goalHeadingDeg);
    double goalHeadingDeg();
    
    double offsetFromGoalHeadingDeg(); //Direction: CCW
    
    virtual void printToSerial();
    virtual void printToLCD(LLCD *lcd);
};

#endif /* defined(__Rover__LCompass__) */
