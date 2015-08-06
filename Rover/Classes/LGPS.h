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
public:
    LGPS();
    void readGPSData();
    void location(float *lat, float *lon, unsigned long *age);
    bool locationValid(float lat, float lon);
    float altitude();
};

#endif /* defined(__Rover__LGPS__) */
