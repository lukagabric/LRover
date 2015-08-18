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

#pragma mark - Convenience

double degToRad(double deg) {
    return (M_PI / 180) * deg;
}

double radToDeg(double rad) {
    return (180 / M_PI) * rad;
}

#pragma mark - Distance

double LGPS::distance(double lat1, double lon1, double lat2, double lon2) {
    double latR1 = degToRad(lat1);
    //    double lonR1 = degToRad(lon1);
    
    double latR2 = degToRad(lat2);
    //    double lonR2 = degToRad(lon2);
    
    double dLatR = degToRad(lat2 - lat1);
    double dLonR = degToRad(lon2 - lon1);
    
    double a = pow(sin(dLatR/2.0), 2) + cos(latR1) * cos(latR2) * pow(sin(dLonR/2.0), 2);
    double R = 6371000;
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    return R * c;
}

double LGPS::distanceTo(double lat, double lon) {
    if (!isLocationValid()) return -1;
    
    return distance(latitude(), longitude(), lat, lon);
}

#pragma mark - Bearing

double LGPS::bearingDeg(float lat1, float lon1, float lat2, float lon2) {
    double latR1 = degToRad(lat1);
//    double lonR1 = degToRad(lon1);
    
    double latR2 = degToRad(lat2);
//    double lonR2 = degToRad(lon2);
    
//    double dLatR = degToRad(lat2 - lat1);
    double dLonR = degToRad(lon2 - lon1);
    
    double y = sin(dLonR) * cos(latR2);
    double x = cos(latR1) * sin(latR2) - sin(latR1) * cos(latR2) * cos(dLonR);
    
    double theta = radToDeg(atan2(y, x));
    
    return fmod(theta + 360, 360);
}

double LGPS::bearingDegTo(float lat, float lon) {
    if (!isLocationValid()) return -1;
    
    return bearingDeg(latitude(), longitude(), lat, lon);
}

#pragma mark - LDebugLog

void LGPS::printToSerial() {
    if (isLocationValid()) {
        Serial.print("\nLAT: ");Serial.print(latitude(), 15);Serial.print("    LON: ");Serial.print(longitude(), 15);Serial.print("    AGE: ");Serial.println(age());
    }
    else {
        Serial.println("\nLOCATION UNAVAILABLE");
    }
}

void LGPS::printToLCD(LLCD *lcd) {
    if (isLocationValid()) {
        lcd->print(0, 0, "LAT=");
        lcd->print(4, 0, latitude(), 15);
        lcd->print(0, 1, "LON=");
        lcd->print(4, 1, longitude(), 15);
    }
    else {
        lcd->print(0, 0, "LOCATION");
        lcd->print(0, 1, "UNAVAILABLE");
    }
}

#pragma mark -
