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
    double _goalHeadingDeg;
    double _declinationDeg;
public:
    LCompass(LLowPassFilter *filter);
    ~LCompass();
    
    void updateHeading();
    
    double headingDeg();
    
    void setGoalHeadingDeg(double goalHeadingDeg);
    double goalHeadingDeg();
    
    void setDeclinationDeg(double declinationDeg);
    double declinationDeg();
    
    double offsetFromGoalHeadingDeg(); //-180 <= offset <= 180; offset < 0 => CCW; offset > 0 => CW
    
    double degToRad(double deg);
    double radToDeg(double rad);
};

#endif /* defined(__Rover__LCompass__) */
