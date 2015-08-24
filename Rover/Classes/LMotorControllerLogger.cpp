//
//  LMotorControllerLogger.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LMotorControllerLogger.h"

#pragma mark - Constructor

LMotorControllerLogger::LMotorControllerLogger(LMotorController *motorController) {
    _motorController = motorController;
}

#pragma mark - LDebugLog

void LMotorControllerLogger::printToSerial() {
    Serial.print("\nLW: ");Serial.print(_motorController->leftWheelSpeed());Serial.print("    RW: ");Serial.println(_motorController->rightWheelSpeed());
}

void LMotorControllerLogger::printToLCD(LLCD *lcd) {
    lcd->print(0, 0, "LEFT: ");
    lcd->print(6, 0, _motorController->leftWheelSpeed(), 1);
    lcd->print(0, 1, "RIGHT: ");
    lcd->print(6, 1, _motorController->rightWheelSpeed(), 1);
}

#pragma mark -