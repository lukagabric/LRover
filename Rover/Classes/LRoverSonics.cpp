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

#pragma mark - LDebugLog

void LRoverSonics::printToSerial() {
    Serial.print("\nF: ");Serial.print(_frontSonic->distance());Serial.print("    L: ");Serial.print(_leftSonic->distance());Serial.print("    R: ");Serial.println(_rightSonic->distance());
}

void LRoverSonics::printToLCD(LLCD *lcd) {
    lcd->print(0, 0, "F=");
    lcd->print(2, 0, _frontSonic->distance(), 1);
    lcd->print(0, 1, "L=");
    lcd->print(2, 1, _leftSonic->distance(), 1);
    lcd->print(9, 1, "R=");
    lcd->print(11, 1, _rightSonic->distance(), 1);
}

#pragma mark -
