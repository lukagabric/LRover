//
//  LUltrasonicLogger.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LUltrasonicLogger.h"

#pragma mark - Constructor

LUltrasonicLogger::LUltrasonicLogger(LUltrasonic *sonic) {
    _sonic = sonic;
}

#pragma mark - LDebugLog

void LUltrasonicLogger::printToSerial() {
    Serial.print("\nDISTANCE: ");Serial.print(_sonic->distance());Serial.println(" cm");
}

void LUltrasonicLogger::printToLCD(LLCD *lcd) {
    lcd->print(0, 0, "DISTANCE (cm)");
    lcd->print(0, 1, _sonic->distance(), 1);
}

#pragma mark -
