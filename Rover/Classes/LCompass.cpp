//
//  LCompass.cpp
//  Rover
//
//  Created by Luka Gabric on 04/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LCompass.h"

LCompass::LCompass() {
    _compass = new HMC5883L();
    _compass->initialize();
    _compass->setSampleAveraging(5);
}

double LCompass::headingDeg() {
    _compass->getHeading(&_mx, &_my, &_mz);
    
    float heading = atan2(_my, _mx);
    if (heading < 0) {
        heading += 2 * M_PI;
    }
    return heading * 180/M_PI;
}

double LCompass::headingOffset(double goalHeading, double currentHeading) {
    double headingOffset = goalHeading - currentHeading;
    
    if (headingOffset < -180) {
        headingOffset += 360;
    }
    else if (headingOffset > 180) {
        headingOffset -= 360;
    }

    return headingOffset;
}
