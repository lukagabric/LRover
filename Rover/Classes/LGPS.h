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
#include "LGeoLocation.h"

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

    LGeoLocation goalLocation;
    
    LGeoLocation location();
    unsigned long age();
    bool isLocationValid();
    
    //distance in km
    double distance(LGeoLocation fromLocation, LGeoLocation toLocation);
    double distanceTo(LGeoLocation toLocation);
    double distanceToGoalLocation();
    
    double bearingDeg(LGeoLocation fromLocation, LGeoLocation toLocation);
    double bearingDegTo(LGeoLocation toLocation);
    double bearingDegToGoalLocation();
    
    float altitude();
    bool isAltitudeValid();
};

#endif /* defined(__Rover__LGPS__) */
