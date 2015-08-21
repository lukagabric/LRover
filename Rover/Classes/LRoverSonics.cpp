//
//  LRoverSonics.cpp
//  Rover
//
//  Created by Luka Gabric on 21/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LRoverSonics.h"
#include "LRoverNavigator.h"

LRoverSonics::LRoverSonics() {
    _frontSonic = new LUltrasonic(SONIC_FRONT_ECHO, SONIC_FRONT_TRIG);
    _rightSonic = new LUltrasonic(SONIC_RIGHT_ECHO, SONIC_RIGHT_TRIG);
    _leftSonic = new LUltrasonic(SONIC_LEFT_ECHO, SONIC_LEFT_TRIG);
    
    _sonics.push_back(_frontSonic);
    _sonics.push_back(_rightSonic);
    _sonics.push_back(_leftSonic);
    
    _measureState = 0;
}

void LRoverSonics::performNextMeasurement() {
    LUltrasonic *sonic = _sonics.at(_measureState);
    sonic->measureDistance();

    _measureState = ++_measureState % _sonics.size();
}

unsigned long LRoverSonics::frontDistance() {
    return _frontSonic->distance();
}

unsigned long LRoverSonics::rightDistance() {
    return _rightSonic->distance();
}

unsigned long LRoverSonics::leftDistance() {
    return _leftSonic->distance();
}
