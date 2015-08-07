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
    unsigned long _time;
public:
    LGPS();

    void updateGPSData();

    float lat, lon, age;
    bool locationValid();

    float altitude;

    void printLocationToLCD(LLCD *lcd);
};

#endif /* defined(__Rover__LGPS__) */
