//
//  LPIDLogger.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LPIDLogger.h"

#pragma mark - Constructor

LPIDLogger::LPIDLogger(LPID *pid) {
    _pid = pid;
}

#pragma mark - LDebugLog

void LPIDLogger::printToSerial() {
    Serial.print("\nKp: ");Serial.print(_pid->GetKp());Serial.print("    Ki:");Serial.print(_pid->GetKi());Serial.print("    Kd:");Serial.print(_pid->GetKd());Serial.print("    OUTPUT: ");Serial.println(_pid->output());
}

void LPIDLogger::printToLCD(LLCD *lcd) {
    lcd->print(0, 0, "kp=");
    lcd->print(3, 0, _pid->GetKp(), 2);
    lcd->print(9, 0, "ki=");
    lcd->print(12, 0, _pid->GetKi(), 2);
    lcd->print(0, 1, "kd=");
    lcd->print(3, 1, _pid->GetKd(), 2);
    lcd->print(9, 1, "O=");
    lcd->print(11, 1, _pid->output(), 2);
}

#pragma mark -
