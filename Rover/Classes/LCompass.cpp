//
//  LCompass.cpp
//  Rover
//
//  Created by Luka Gabric on 04/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LCompass.h"

#pragma mark - Constructor

LCompass::LCompass(LLowPassFilter *filter) {
    _filter = filter;
    _compass = new HMC5883L();
    _compass->initialize();
    _compass->setSampleAveraging(5);
}

#pragma mark - Update Heading

void LCompass::updateHeading() {
    _compass->getHeading(&_mx, &_my, &_mz);
    
    float heading = atan2(_my, _mx);
    if (heading < 0) {
        heading += 2 * M_PI;
    }
    
    float rawHeadingDeg = heading * 180/M_PI;

    _headingDeg = _filter ? _filter->filterValue(rawHeadingDeg) : rawHeadingDeg;
}

#pragma mark - Getters/Setters

double LCompass::headingDeg() {
    return _headingDeg;
}

void LCompass::setGoalHeading(double goalHeading) {
    _goalHeading = goalHeading;
}

double LCompass::goalHeading() {
    return _goalHeading;
}

double LCompass::offsetFromGoalHeading() {
    double headingOffset = goalHeading() - headingDeg();
    
    if (headingOffset < -180) {
        headingOffset += 360;
    }
    else if (headingOffset > 180) {
        headingOffset -= 360;
    }

    return headingOffset;
}

#pragma mark - LDebugLog

void LCompass::printToSerial() {
    Serial.print("\nHEADING: ");Serial.print(headingDeg());Serial.print("    GOAL HEADING: ");Serial.print(goalHeading());Serial.print("    HEADING OFFSET: ");Serial.println(offsetFromGoalHeading());
}

void LCompass::printToLCD(LLCD *lcd) {
    lcd->print(0, 0, "HEADING =");
    lcd->print(9, 0, headingDeg(), 2);
    lcd->print(0, 1, "OFFSET  = ");
    lcd->print(0, 1, offsetFromGoalHeading(), 2);
}

#pragma mark -
