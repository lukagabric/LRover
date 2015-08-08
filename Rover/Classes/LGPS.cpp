//
//  LGPS.cpp
//  Rover
//
//  Created by Luka Gabric on 05/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LGPS.h"
#include "LLCD.h"

#pragma mark - Constructor

LGPS::LGPS() {
    _gps = new TinyGPS();

    _ss = new SoftwareSerial(10, 11);
    _ss->begin(9600);
    
    _lat = TinyGPS::GPS_INVALID_F_ANGLE;
    _lon = TinyGPS::GPS_INVALID_F_ANGLE;
    _altitude = TinyGPS::GPS_INVALID_F_ALTITUDE;
}

#pragma mark - Read Data

void LGPS::readGPSData() {
    if (millis() - _time < 800) return;
    
    bool newData = false;
    if (_ss->available()) {
        newData = true;
        do {
            _gps->encode(_ss->read());
        } while (_ss->available());
    }
    
    if (newData) {
        _time = millis();
        
        _gps->f_get_position(&_lat, &_lon, &_age);
        _altitude = _gps->f_altitude();
    }
}

#pragma mark - Getters

float LGPS::latitude() {
    return _lat;
}

float LGPS::longitude() {
    return _lon;
}

unsigned long LGPS::age() {
    return _age;
}

bool LGPS::isLocationValid() {
    return (latitude() != TinyGPS::GPS_INVALID_F_ANGLE && longitude() != TinyGPS::GPS_INVALID_F_ANGLE);
}

float LGPS::altitude() {
    return _altitude;
}

bool LGPS::isAltitudeValid() {
    return altitude() != TinyGPS::GPS_INVALID_F_ALTITUDE;
}

#pragma mark - LDebugLog

void LGPS::printToSerial() {
    if (isLocationValid()) {
        Serial.print("\nLAT: ");Serial.print(latitude());Serial.print("    LON: ");Serial.print(longitude());Serial.print("    AGE: ");Serial.println(age());
    }
    else {
        Serial.println("\nLOCATION UNAVAILABLE");
    }
}

void LGPS::printToLCD(LLCD *lcd) {
    if (isLocationValid()) {
        lcd->print(0, 0, "LAT=");
        lcd->print(4, 0, latitude(), 8);
        lcd->print(0, 1, "LON=");
        lcd->print(4, 1, longitude(), 8);
    }
    else {
        lcd->print(0, 0, "LOCATION");
        lcd->print(0, 1, "UNAVAILABLE");
    }
}

#pragma mark -
