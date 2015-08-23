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
    if (_gps->isLocationValid()) {
        Serial.print("\nLAT: ");Serial.print(_gps->latitude(), 15);Serial.print("    LON: ");Serial.print(_gps->longitude(), 15);Serial.print("    AGE: ");Serial.println(_gps->age());
    }
    else {
        Serial.println("\nLOCATION UNAVAILABLE");
    }
}

void LGPSLogger::printToLCD(LLCD *lcd) {
    if (_gps->isLocationValid()) {
        if (_gps->_goalLat != TinyGPS::GPS_INVALID_F_ANGLE && _gps->_goalLon != TinyGPS::GPS_INVALID_F_ANGLE) {
            lcd->print(0, 0, "LAT=");
            lcd->print(4, 0, _gps->latitude(), 3);
            lcd->print(8, 0, "LON=");
            lcd->print(11, 0, _gps->longitude(), 3);
            lcd->print(0, 1, "D=");
            lcd->print(3, 1, _gps->distanceTo(_gps->_goalLat, _gps->_goalLon), 15);
        }
        else {
            lcd->print(0, 0, "LAT=");
            lcd->print(4, 0, _gps->latitude(), 15);
            lcd->print(0, 1, "LON=");
            lcd->print(4, 1, _gps->longitude(), 15);
        }
    }
    else {
        lcd->print(0, 0, "LOCATION");
        lcd->print(0, 1, "UNAVAILABLE");
    }
}

#pragma mark -
