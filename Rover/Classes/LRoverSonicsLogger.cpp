//
//  LRoverSonicsLogger.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LRoverSonicsLogger.h"

#pragma mark - Constructor

LRoverSonicsLogger::LRoverSonicsLogger(LRoverSonics *sonics) {
    _sonics = sonics;
}

#pragma mark - LDebugLog

void LRoverSonicsLogger::printToSerial() {
    Serial.print("\nF: ");Serial.print(_sonics->frontDistance());
    Serial.print("    FL: ");Serial.print(_sonics->frontLeftDistance());
    Serial.print("    FR: ");Serial.print(_sonics->frontRightDistance());
    Serial.print("    L: ");Serial.print(_sonics->leftDistance());
    Serial.print("    R: ");Serial.println(_sonics->rightDistance());
}

void LRoverSonicsLogger::printToLCD(LLCD *lcd) {
    lcd->print(1, 0, _sonics->frontLeftDistance(), 0);
    lcd->print(7, 0, _sonics->frontDistance(), 0);
    lcd->print(13, 0, _sonics->frontRightDistance(), 0);
    lcd->print(1, 1, _sonics->leftDistance(), 0);
    lcd->print(13, 1, _sonics->rightDistance(), 0);
}

#pragma mark -
