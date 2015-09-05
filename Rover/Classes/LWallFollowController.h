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

enum LPIDTuningState {LPIDTuningStateNone = 0, LPIDTuningStateConservative = 1, LPIDTuningStateModerate = 2, LPIDTuningStateAggressive = 3};

class LWallFollowController {
private:
    LPID *_wallFollowPID;
    LPIDTuningState _pidTuningState;
    double pidOutputForObstacleDistances(LObstacleDistances obstacleDistances);
    LWheelSpeeds wallFollowWheelSpeedsForPIDOutput(double pidOutput);
    void updatePIDTunings(LPIDTuningState state);
    void resetPIDTuning();
    bool leftFollow(LObstacleDistances obstacleDistances);
public:
    LWallFollowController(LPID *wallFollowPID);
    void resetWallFollowParameters();
    LWheelSpeeds wallFollowOutput(LObstacleDistances obstacleDistances);
};

#endif /* defined(__Rover__LWallFollowController__) */
