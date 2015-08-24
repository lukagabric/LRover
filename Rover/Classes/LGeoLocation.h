//
//  LGeoLocation.h
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef Rover_LGeoLocation_h
#define Rover_LGeoLocation_h

class LGeoLocation {
private:
    double _latitude;
    double _longitude;
    
public:
    LGeoLocation();
    LGeoLocation(double latitude, double longitude);
    
    double latitude();
    double longitude();

    bool isValid();
    bool isEqualTo(LGeoLocation location);
    
    double bearingDegTo(LGeoLocation location);
    double distanceTo(LGeoLocation location);
    
    double degToRad(double deg);
    double radToDeg(double rad);
};

#endif
