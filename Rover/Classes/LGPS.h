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

class LGPS {
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

    float altitude();
    bool isAltitudeValid();

    void printLocationToLCD(LLCD *lcd);
    void printLocationToSerial();
};

#endif /* defined(__Rover__LGPS__) */
