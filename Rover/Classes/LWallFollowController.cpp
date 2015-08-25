//
//  LWallFollowController.cpp
//  Rover
//
//  Created by Luka Gabric on 24/08/15.
//  Copyright (c) 2015 Luka Gabric. All rights reserved.
//

#include "LWallFollowController.h"

#pragma mark - Constructor

LWallFollowController::LWallFollowController(LPID *wallFollowPID) {
    _wallFollowPID = wallFollowPID;
}

#pragma mark - Output

LWheelSpeeds LWallFollowController::wallFollowOutput(LObstacleDistances obstacleDistances) {
    double leftMinimumDistance = obstacleDistances.leftMinDistance();
    double rightMinimumDistance = obstacleDistances.rightMinDistance();
    bool leftFollow = leftMinimumDistance < rightMinimumDistance;
    double distance = leftFollow ? leftMinimumDistance : rightMinimumDistance;
    
    _wallFollowPID->SetControllerDirection(leftFollow ? DIRECT : REVERSE);
    _wallFollowPID->setInput(distance);
    _wallFollowPID->Compute();
    
    return {0, 0};
}

#pragma mark -
