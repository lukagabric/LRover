//
//  LWallFollowController.h
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#ifndef __Rover__LWallFollowController__
#define __Rover__LWallFollowController__

#include "LWheelSpeeds.h"
#include "LPID.h"
#include "LObstacleDistances.h"

class LWallFollowController {
private:
    LPID *_wallFollowPID;
    double pidOutputForObstacleDistances(LObstacleDistances obstacleDistances);
    LWheelSpeeds wallFollowWheelSpeedsForPIDOutput(double pidOutput);
public:
    LWallFollowController(LPID *wallFollowPID);
    LWheelSpeeds wallFollowOutput(LObstacleDistances obstacleDistances);
};

#endif /* defined(__Rover__LWallFollowController__) */
