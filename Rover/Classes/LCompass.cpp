//
//  LCompass.cpp
//  Rover
//
//  Created by Luka Gabric on 04/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LCompass.h"

#define compass_cal_x_offset 116   // Manually calculated offset in X direction
#define compass_cal_y_offset 225   // Manually calculated offset in Y direction
#define compass_cal_x_gain 1.1     // Stored Gain offset at room temperature
#define compass_cal_y_gain 1.12    // Stored Gain offset at room temperature

#define compass_x_offset 5.75
#define compass_y_offset 33.53
#define compass_x_gainError 0.94
#define compass_y_gainError 0.93

#define compass_gain_fact 1.22

#define compass_rad2degree 57.2957795

#pragma mark - Constructor

LCompass::LCompass(LLowPassFilter *filter) {
    _filter = filter;
    _compass = new HMC5883L();
    _compass->initialize();
    _compass->setSampleAveraging(HMC5883L_AVERAGING_8);
    _compass->setGain(HMC5883L_GAIN_820);
    _compass->setDataRate(HMC5883L_RATE_30);
    _goalHeadingDeg = 0;
    _headingDeg = 0;
}

#pragma mark - Update Heading

void LCompass::updateHeading() {
    _compass->getHeading(&_mx, &_my, &_mz);

    float compass_x_scaled=_mx*compass_gain_fact*compass_x_gainError+compass_x_offset;
    float compass_y_scaled=_my*compass_gain_fact*compass_y_gainError+compass_y_offset;
    
    float rawHeading = atan2(compass_y_scaled, compass_x_scaled);

    if (rawHeading < 0) {
        rawHeading += 2 * M_PI;
    }
    float rawHeadingDeg = rawHeading * 180/M_PI;

//    if (compass_y_scaled > 0) {
//        rawHeadingDeg = 90-atan(compass_x_scaled/compass_y_scaled)*compass_rad2degree;
//    }
//    else if (compass_y_scaled < 0) {
//        rawHeadingDeg = 270-atan(compass_x_scaled/compass_y_scaled)*compass_rad2degree;
//    }
//    else if (compass_y_scaled == 0 && compass_x_scaled < 0) {
//        rawHeadingDeg = 180;
//    }

    _headingDeg = _filter ? _filter->filterValue(rawHeadingDeg) : rawHeadingDeg;
}

#pragma mark - Getters/Setters

double LCompass::headingDeg() {
    return _headingDeg;
}

void LCompass::setGoalHeadingDeg(double goalHeadingDeg) {
    _goalHeadingDeg = goalHeadingDeg;
}

double LCompass::goalHeadingDeg() {
    return _goalHeadingDeg;
}

double LCompass::offsetFromGoalHeadingDeg() {
    double headingOffset = goalHeadingDeg() - headingDeg();
    
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
    Serial.print("\nHEADING: ");Serial.print(headingDeg());Serial.print("    GOAL HEADING: ");Serial.print(goalHeadingDeg());Serial.print("    HEADING OFFSET: ");Serial.println(offsetFromGoalHeadingDeg());
}

void LCompass::printToLCD(LLCD *lcd) {
    lcd->print(0, 0, "OFFSET  =");
    lcd->print(9, 0, offsetFromGoalHeadingDeg(), 4);
    lcd->print(0, 1, "HEADING =");
    lcd->print(9, 1, headingDeg(), 4);
}

#pragma mark -
