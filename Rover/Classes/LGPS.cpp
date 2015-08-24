//
//  LGPS.cpp
//  Rover
//
//  Created by Luka Gabric on 05/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LGPS.h"
#include "LConverters.h"

#pragma mark - Constructor

LGPS::LGPS() {
    _gps = new TinyGPS();

    _ss = new SoftwareSerial(10, 11);
    _ss->begin(9600);
    
    _lat = TinyGPS::GPS_INVALID_F_ANGLE;
    _lon = TinyGPS::GPS_INVALID_F_ANGLE;

    _altitude = TinyGPS::GPS_INVALID_F_ALTITUDE;
    
    goalLocation = {TinyGPS::GPS_INVALID_F_ANGLE, TinyGPS::GPS_INVALID_F_ANGLE};
}

#pragma mark - Read Data

void LGPS::readGPSData() {
    if (_ss->available()) {
        do {
            _gps->encode(_ss->read());
        } while (_ss->available());
        
        _gps->f_get_position(&_lat, &_lon, &_age);
        _altitude = _gps->f_altitude();
    }
}

#pragma mark - Getters

LGeoLocation LGPS::location() {
    return {_lat, _lon};
}

unsigned long LGPS::age() {
    return _age;
}

bool LGPS::isLocationValid() {
    return (location().latitude != TinyGPS::GPS_INVALID_F_ANGLE && location().longitude != TinyGPS::GPS_INVALID_F_ANGLE);
}

float LGPS::altitude() {
    return _altitude;
}

bool LGPS::isAltitudeValid() {
    return altitude() != TinyGPS::GPS_INVALID_F_ALTITUDE;
}

#pragma mark - Distance

double LGPS::distance(LGeoLocation fromLocation, LGeoLocation toLocation) {
    double fromLatR = degToRad(fromLocation.latitude);
//    double fromLonR = degToRad(fromLocation.longitude);
    
    double toLatR = degToRad(toLocation.latitude);
//    double toLonR = degToRad(toLocation.longitude);
    
    double dLatR = degToRad(toLocation.latitude - fromLocation.latitude);
    double dLonR = degToRad(toLocation.longitude - fromLocation.longitude);
    
    double a = pow(sin(dLatR/2.0), 2) + cos(fromLatR) * cos(toLatR) * pow(sin(dLonR/2.0), 2);
    double R = 6371000;
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    return R * c;
}

double LGPS::distanceTo(LGeoLocation toLocation) {
    if (!isLocationValid()) return -1;
    
    return distance(location(), toLocation);
}

double LGPS::distanceToGoalLocation() {
    if (!isLocationValid() ||
        goalLocation.latitude == TinyGPS::GPS_INVALID_F_ANGLE ||
        goalLocation.longitude == TinyGPS::GPS_INVALID_F_ANGLE) return -1;

    return distance(location(), goalLocation);
}

#pragma mark - Bearing

double LGPS::bearingDeg(LGeoLocation fromLocation, LGeoLocation toLocation) {
    double fromLatR = degToRad(fromLocation.latitude);
//    double fromLonR = degToRad(fromLocation.longitude);
    
    double toLatR = degToRad(toLocation.latitude);
//    double toLonR = degToRad(toLocation.longitude);
    
//    double dLatR = degToRad(toLocation.latitude - fromLocation.latitude);
    double dLonR = degToRad(toLocation.longitude - fromLocation.longitude);
    
    double y = sin(dLonR) * cos(toLatR);
    double x = cos(fromLatR) * sin(toLatR) - sin(fromLatR) * cos(toLatR) * cos(dLonR);
    
    double theta = radToDeg(atan2(y, x));
    
    return fmod(theta + 360, 360);
}

double LGPS::bearingDegTo(LGeoLocation toLocation) {
    if (!isLocationValid()) return -1;
    
    return bearingDeg(location(), toLocation);
}

double LGPS::bearingDegToGoalLocation() {
    if (!isLocationValid() ||
        goalLocation.latitude == TinyGPS::GPS_INVALID_F_ANGLE ||
        goalLocation.longitude == TinyGPS::GPS_INVALID_F_ANGLE) return -1;
    
    return bearingDeg(location(), goalLocation);
}

#pragma mark -
