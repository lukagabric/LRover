//
//  LGPS.h
//  Rover
//
//  Created by Luka Gabric on 05/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LGPS__
#define __Rover__LGPS__

#include <Arduino.h>
#include "TinyGPS.h"
#include "SoftwareSerial.h"

class LGPS {
private:
    TinyGPS *_gps;
    SoftwareSerial *_ss;
    float _lat, _lon;
    unsigned long _age;
    float _altitude;
public:
    LGPS();

    void readGPSData();

    float latitude();
    float longitude();
    unsigned long age();
    bool isLocationValid();
    
    float _goalLat, _goalLon;

    //distance in km
    double distance(double lat1, double lon1, double lat2, double lon2);
    double distanceTo(double lat, double lon);
    
    double bearingDeg(float lat1, float lon1, float lat2, float lon2);
    double bearingDegTo(float lat, float lon);

    float altitude();
    bool isAltitudeValid();
};

#endif /* defined(__Rover__LGPS__) */
