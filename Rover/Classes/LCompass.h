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

class LCompass {
private:
    HMC5883L *_compass;
    int16_t _mx, _my, _mz;
public:
    LCompass();
    void updateHeading();
    double headingDeg;
    double headingOffset(double goalHeading, double currentHeading); //Direction: CCW
};

#endif /* defined(__Rover__LCompass__) */
