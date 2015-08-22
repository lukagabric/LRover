//
//  LRoverSonics.cpp
//  Rover
//
//  Created by Luka Gabric on 21/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LRoverSonics.h"
#include "LRoverNavigator.h"
#include "Arduino.h"

LRoverSonics::LRoverSonics() {
    _frontSonic = new LUltrasonic(SONIC_FRONT_ECHO, SONIC_FRONT_TRIG);
    _frontRightSonic = new LUltrasonic(SONIC_FRONT_RIGHT_ECHO, SONIC_FRONT_RIGHT_TRIG);
    _frontLeftSonic = new LUltrasonic(SONIC_FRONT_LEFT_ECHO, SONIC_FRONT_LEFT_TRIG);
    _rightSonic = new LUltrasonic(SONIC_RIGHT_ECHO, SONIC_RIGHT_TRIG);
    _leftSonic = new LUltrasonic(SONIC_LEFT_ECHO, SONIC_LEFT_TRIG);
    
    _sonics.push_back(_frontLeftSonic);
    _sonics.push_back(_rightSonic);
    _sonics.push_back(_frontSonic);
    _sonics.push_back(_leftSonic);
    _sonics.push_back(_frontRightSonic);
    
    _measureState = 0;
}

void LRoverSonics::performNextMeasurement() {
    _measureState = ++_measureState % _sonics.size();
    LUltrasonic *sonic = _sonics.at(_measureState);
    sonic->measureDistance();
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
    Serial.print("\nF: ");Serial.print(_frontSonic->distance());
    Serial.print("    FL: ");Serial.print(_frontLeftSonic->distance());
    Serial.print("    FR: ");Serial.print(_frontRightSonic->distance());
    Serial.print("    L: ");Serial.print(_leftSonic->distance());
    Serial.print("    R: ");Serial.println(_rightSonic->distance());
}

void LRoverSonics::printToLCD(LLCD *lcd) {
    lcd->print(1, 0, _frontLeftSonic->distance(), 0);
    lcd->print(7, 0, _frontSonic->distance(), 0);
    lcd->print(13, 0, _frontRightSonic->distance(), 0);
    lcd->print(1, 1, _leftSonic->distance(), 0);
    lcd->print(13, 1, _rightSonic->distance(), 0);
}

#pragma mark -
