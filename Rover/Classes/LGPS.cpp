//
//  LGPS.cpp
//  Rover
//
//  Created by Luka Gabric on 05/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LGPS.h"
#include "LLCD.h"

LGPS::LGPS() {
    _gps = new TinyGPS();

    _ss = new SoftwareSerial(10, 11);
    _ss->begin(9600);
}

void LGPS::updateGPSData() {
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
        
        _gps->f_get_position(&lat, &lon, &age);
        altitude = _gps->f_altitude();
    }
}

bool LGPS::locationValid() {
    return (lat != TinyGPS::GPS_INVALID_F_ANGLE && lon != TinyGPS::GPS_INVALID_F_ANGLE);
}

void LGPS::printLocationToLCD(LLCD *lcd) {
    if (locationValid()) {
        lcd->print(0, 0, "LAT=");
        lcd->print(4, 0, lat, 8);
        lcd->print(0, 1, "LON=");
        lcd->print(4, 1, lon, 8);
    }
    else {
        lcd->print(0, 0, "LOCATION");
        lcd->print(0, 1, "UNAVAILABLE");
    }
}
