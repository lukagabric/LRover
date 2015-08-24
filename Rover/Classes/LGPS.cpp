//
//  LGPS.cpp
//  Rover
//
//  Created by Luka Gabric on 05/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LGPS.h"

#pragma mark - Constructor

LGPS::LGPS() : _ss(10, 11) {
    _ss.begin(9600);

    _altitude = TinyGPS::GPS_INVALID_F_ALTITUDE;
}

#pragma mark - Read Data

void LGPS::readGPSData() {
    if (_ss.available()) {
        do {
            _gps.encode(_ss.read());
        } while (_ss.available());
        
        float lat, lon;
        _gps.f_get_position(&lat, &lon, &_age);
        _location = LGeoLocation(lat, lon);
        _altitude = _gps.f_altitude();
    }
}

#pragma mark - Getters

LGeoLocation LGPS::location() {
    return _location;
}

void LGPS::setGoalLocation(LGeoLocation goalLocation) {
    _goalLocation = goalLocation;
}

LGeoLocation LGPS::goalLocation() {
    return _goalLocation;
}

unsigned long LGPS::age() {
    return _age;
}

float LGPS::altitude() {
    return _altitude;
}

bool LGPS::isAltitudeValid() {
    return altitude() != TinyGPS::GPS_INVALID_F_ALTITUDE;
}

#pragma mark - Distance

double LGPS::distanceToGoalLocation() {
    return location().distanceTo(goalLocation());
}

#pragma mark - Bearing

double LGPS::bearingDegToGoalLocation() {
    return location().bearingDegTo(goalLocation());
}

#pragma mark -
