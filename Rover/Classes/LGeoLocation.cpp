//
//  LGeoLocation.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LGeoLocation.h"
#include "math.h"

#pragma mark - Constructors

LGeoLocation::LGeoLocation() {
    _latitude = 999;
    _longitude = 999;
}

LGeoLocation::LGeoLocation(double latitude, double longitude) {
    _latitude = latitude;
    _longitude = longitude;
}

#pragma mark - Getters

double LGeoLocation::latitude() {
    return _latitude;
}

double LGeoLocation::longitude() {
    return _longitude;
}

bool LGeoLocation::isValid() {
    if (latitude() < -90 || latitude() > 90 ||
        longitude() < -180 || longitude() > 180) {
        return false;
    }
    
    return true;
}

bool LGeoLocation::isEqualTo(LGeoLocation location) {
    return latitude() == location.latitude() && latitude() == location.longitude();
}

double LGeoLocation::headingDegTo(LGeoLocation location) {
    double fromLatR = degToRad(latitude());
//    double fromLonR = degToRad(longitude());
    
    double toLatR = degToRad(location.latitude());
//    double toLonR = degToRad(location.longitude());
    
//    double dLatR = degToRad(location.latitude() - latitude());
    double dLonR = degToRad(location.longitude() - longitude());
    
    double y = sin(dLonR) * cos(toLatR);
    double x = cos(fromLatR) * sin(toLatR) - sin(fromLatR) * cos(toLatR) * cos(dLonR);
    
    double theta = radToDeg(atan2(y, x));
    
    return fmod(theta + 360, 360);
}

double LGeoLocation::distanceTo(LGeoLocation location) {
    double fromLatR = degToRad(latitude());
//    double fromLonR = degToRad(longitude());
    
    double toLatR = degToRad(location.latitude());
//    double toLonR = degToRad(location.longitude());
    
    double dLatR = degToRad(location.latitude() - latitude());
    double dLonR = degToRad(location.longitude() - longitude());
    
    double a = pow(sin(dLatR/2.0), 2) + cos(fromLatR) * cos(toLatR) * pow(sin(dLonR/2.0), 2);
    double R = 6371000;
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    return R * c;
}

double LGeoLocation::degToRad(double deg) {
    return (M_PI / 180) * deg;
}

double LGeoLocation::radToDeg(double rad) {
    return (180 / M_PI) * rad;
}

#pragma mark -