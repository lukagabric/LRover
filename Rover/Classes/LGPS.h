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
    LGeoLocation _location;
    LGeoLocation _goalLocation;
    unsigned long _age;
    float _altitude;
public:
    LGPS();
    ~LGPS();
    
    void readGPSData();
    
    LGeoLocation location();
    
    void setGoalLocation(LGeoLocation goalLocation);
    LGeoLocation goalLocation();
    
    unsigned long age();
    
    double distanceToGoalLocation();
    double bearingDegToGoalLocation();
    
    float altitude();
    bool isAltitudeValid();
};

#endif /* defined(__Rover__LGPS__) */
