//
//  LGPS.cpp
//  Rover
//
//  Created by Luka Gabric on 05/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LGPS.h"

LGPS::LGPS() {
    _gps = new TinyGPS();

    _ss = new SoftwareSerial(10, 11);
    _ss->begin(9600);
}

void LGPS::readGPSData() {
    unsigned long start = millis();
    do {
        while (_ss->available()) {
            _gps->encode(_ss->read());
        }
    } while (millis() - start < 1000);
}

bool LGPS::location(float *lat, float *lon, unsigned long *age) {
    readGPSData();
    
    _gps->f_get_position(lat, lon, age);
    
    return locationValid(*lat, *lon);
}

bool LGPS::locationValid(float lat, float lon) {
    return (lat != TinyGPS::GPS_INVALID_F_ANGLE && lon != TinyGPS::GPS_INVALID_F_ANGLE);
}

float LGPS::altitude() {
    return _gps->f_altitude();
}

