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

class LWallFollowController {
private:
    LPID *_wallFollowPID;
        
    double _frontDistance, _frontLeftDistance, _frontRightDistance, _leftDistance, _rightDistance;
    
    double leftMinDistance();
    double rightMinDistance();

    bool isObstacleTooClose();
    
    bool isObstacleFront();
    bool isObstacleFrontRight();
    bool isObstacleFrontLeft();
    bool isObstacleRight();
    bool isObstacleLeft();
    
    bool isObstacleOnTheLeftSide();
    bool isObstacleOnTheRightSide();

public:
    LWallFollowController(LPID *wallFollowPID);
    LWheelSpeeds wallFollowOutput(double frontDistance, double frontLeftDistance, double frontRightDistance, double leftDistance, double rightDistance);
};

#endif /* defined(__Rover__LWallFollowController__) */
