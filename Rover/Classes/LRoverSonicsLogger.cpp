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
    LObstacleDistances obstacleDistances = _sonics->obstacleDistances();

    Serial.print("\nF: ");Serial.print(obstacleDistances.frontDistance());
    Serial.print("    FL: ");Serial.print(obstacleDistances.frontLeftDistance());
    Serial.print("    FR: ");Serial.print(obstacleDistances.frontRightDistance());
    Serial.print("    L: ");Serial.print(obstacleDistances.leftDistance());
    Serial.print("    R: ");Serial.println(obstacleDistances.rightDistance());
}

void LRoverSonicsLogger::printToLCD(LLCD *lcd) {
    LObstacleDistances obstacleDistances = _sonics->obstacleDistances();

    lcd->print(1, 0, obstacleDistances.frontLeftDistance(), 0);
    lcd->print(7, 0, obstacleDistances.frontDistance(), 0);
    lcd->print(13, 0, obstacleDistances.frontRightDistance(), 0);
    lcd->print(1, 1, obstacleDistances.leftDistance(), 0);
    lcd->print(13, 1, obstacleDistances.rightDistance(), 0);
}

#pragma mark -
