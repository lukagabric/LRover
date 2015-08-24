//
//  LCompassLogger.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LCompassLogger.h"

#pragma mark - Constructor

LCompassLogger::LCompassLogger(LCompass *compass) {
    _compass = compass;
}

#pragma mark - LDebugLog

void LCompassLogger::printToSerial() {
    Serial.print("\nHEADING: ");Serial.print(_compass->headingDeg());Serial.print("    GOAL HEADING: ");Serial.print(_compass->goalHeadingDeg());Serial.print("    HEADING OFFSET: ");Serial.println(_compass->offsetFromGoalHeadingDeg());
}

void LCompassLogger::printToLCD(LLCD *lcd) {
    lcd->print(0, 0, "OFFSET =");
    lcd->print(8, 0, _compass->offsetFromGoalHeadingDeg(), 4);
    lcd->print(0, 1, "HEADING=");
    lcd->print(8, 1, _compass->headingDeg(), 4);
}

#pragma mark -
