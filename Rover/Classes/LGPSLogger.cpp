//
//  LGPSLogger.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LGPSLogger.h"
#include "LLCD.h"

#pragma mark - Constructor

LGPSLogger::LGPSLogger(LGPS *gps) {
    _gps = gps;
}

#pragma mark - LDebugLog

void LGPSLogger::printToSerial() {
    if (_gps->location().isValid()) {
        Serial.print("\nLAT: ");Serial.print(_gps->location().latitude(), 15);Serial.print("    LON: ");Serial.print(_gps->location().longitude(), 15);Serial.print("    AGE: ");Serial.println(_gps->age());
    }
    else {
        Serial.println("\nLOCATION UNAVAILABLE");
    }
}

void LGPSLogger::printToLCD(LLCD *lcd) {
    if (_gps->location().isValid()) {
        if (_gps->goalLocation().isValid()) {
            lcd->print(0, 0, "X=");
            lcd->print(2, 0, _gps->location().latitude(), 2);
            lcd->print(8, 0, "Y=");
            lcd->print(10, 0, _gps->location().longitude(), 2);
            lcd->print(0, 1, "D=");
            lcd->print(2, 1, _gps->location().distanceTo(_gps->goalLocation()), 15);
        }
        else {
            lcd->print(0, 0, "LAT=");
            lcd->print(4, 0, _gps->location().latitude(), 15);
            lcd->print(0, 1, "LON=");
            lcd->print(4, 1, _gps->location().longitude(), 15);
        }
    }
    else {
        lcd->print(0, 0, "LOCATION");
        lcd->print(0, 1, "UNAVAILABLE");
    }
}

#pragma mark -
