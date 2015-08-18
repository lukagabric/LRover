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
#include "LLCD.h"
#include "LDebugLog.h"

class LGPS : public LDebugLog {
private:
    TinyGPS *_gps;
    SoftwareSerial *_ss;
    unsigned long _time;
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

    //distance in km
    double distance(double lat1, double lon1, double lat2, double lon2);
    double distanceTo(double lat, double lon);
    
    double bearingDeg(float lat1, float lon1, float lat2, float lon2);
    double bearingDegTo(float lat, float lon);

    float altitude();
    bool isAltitudeValid();

    virtual void printToSerial();
    virtual void printToLCD(LLCD *lcd);
};

#endif /* defined(__Rover__LGPS__) */
