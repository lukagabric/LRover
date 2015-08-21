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
    _frontRightSonic = new LUltrasonic(SONIC_RIGHT_ECHO, SONIC_RIGHT_TRIG);
    _frontLeftSonic = new LUltrasonic(SONIC_LEFT_ECHO, SONIC_LEFT_TRIG);
    
    _sonics.push_back(_frontSonic);
    _sonics.push_back(_frontRightSonic);
    _sonics.push_back(_frontLeftSonic);
    
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

unsigned long LRoverSonics::frontRightDistance() {
    return _frontRightSonic->distance();
}

unsigned long LRoverSonics::frontLeftDistance() {
    return _frontLeftSonic->distance();
}

#pragma mark - LDebugLog

void LRoverSonics::printToSerial() {
    Serial.print("\nF: ");Serial.print(_frontSonic->distance());Serial.print("    L: ");Serial.print(_frontLeftSonic->distance());Serial.print("    R: ");Serial.println(_frontRightSonic->distance());
}

void LRoverSonics::printToLCD(LLCD *lcd) {
    lcd->print(0, 0, "F=");
    lcd->print(2, 0, _frontSonic->distance(), 1);
    lcd->print(6, 0, "FL=");
    lcd->print(9, 0, _frontLeftSonic->distance(), 1);
    lcd->print(13, 0, "FR=");
    lcd->print(15, 0, _frontRightSonic->distance(), 1);
}

#pragma mark -
