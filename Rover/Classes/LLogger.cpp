//
//  LLogger.cpp
//  Rover
//
//  Created by Luka Gabric on 08/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LLogger.h"

LLogger::LLogger(LLCD *lcd, std::vector<LDebugLog*> logItems) {
    _lcd = lcd;
    _logItems = logItems;
    _lcdDebugLogState = 0;
}

void LLogger::debugLogToLCD() {
    if (!_lcd) return;
    
    _lcd->clear();
    
    LDebugLog *debugLog = _logItems.at(_lcdDebugLogState);
    debugLog->printToLCD(_lcd);
}

void LLogger::skipNextDebugLogToLCD() {
    _lcdDebugLogState = ++_lcdDebugLogState % _logItems.size();
}

void LLogger::debugLogToSerial() {
    Serial.println("\n===========================================================================");
    for (int i = 0; i < _logItems.size(); i++) {
        LDebugLog *debugLog = _logItems.at(i);
        debugLog->printToSerial();
    }
}
