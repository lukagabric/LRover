//
//  LCruiseController.h
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LCruiseController__
#define __Rover__LCruiseController__

#include "LGeoLocation.h"
#include "LWheelSpeeds.h"
#include "LPID.h"

class LCruiseController {
private:
    LPID *_cruisePID;
    LGeoLocation _lastLocation;
    double _lastHeadingOffsetDeg;
    bool hasLocationChanged(LGeoLocation currentLocation);
    void updateHeadingOffset(LGeoLocation currentLocation, LGeoLocation goalLocation, double currentHeadingDeg);
    double headingOffsetDeg(LGeoLocation currentLocation, LGeoLocation goalLocation, double currentHeadingDeg);
    double pidOutputForHeadingOffsetDeg(double headingOffsetDeg);
    LWheelSpeeds cruiseWheelSpeedsForPIDOutput(double pidOutput);
public:
    LCruiseController(LPID *cruisePID);
    LWheelSpeeds cruiseOutput(LGeoLocation currentLocation, LGeoLocation goalLocation, double currentHeadingDeg);
};

#endif /* defined(__Rover__LCruiseController__) */
