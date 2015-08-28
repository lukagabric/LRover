//
//  LCruiseController.h
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LCruiseController__
#define __Rover__LCruiseController__

#include "LWheelSpeeds.h"
#include "LPID.h"

class LCruiseController {
private:
    LPID *_cruisePID;
    double pidOutputForHeadingOffsetDeg(double headingOffsetDeg);
    LWheelSpeeds cruiseWheelSpeedsForPIDOutput(double pidOutput);
public:
    int minimumForwardWheelSpeed;
    LCruiseController(LPID *cruisePID);
    LWheelSpeeds cruiseOutput(double headingOffsetDeg);
};

#endif /* defined(__Rover__LCruiseController__) */
