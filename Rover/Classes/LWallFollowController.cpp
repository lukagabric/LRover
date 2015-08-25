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

    double maxWheelSpeed = 255;
    _wallFollowPID->SetOutputLimits(-2*maxWheelSpeed, 2*maxWheelSpeed);
}

#pragma mark - Output

LWheelSpeeds LWallFollowController::wallFollowOutput(LObstacleDistances obstacleDistances) {
    double pidOutput = pidOutputForObstacleDistances(obstacleDistances);
    return wallFollowWheelSpeedsForPIDOutput(pidOutput);
}

double LWallFollowController::pidOutputForObstacleDistances(LObstacleDistances obstacleDistances) {
    bool leftFollow = obstacleDistances.leftMinDistance() < obstacleDistances.rightMinDistance();
    double minimumDistance = obstacleDistances.minDistance();
    
    _wallFollowPID->SetControllerDirection(leftFollow ? REVERSE : DIRECT);
    _wallFollowPID->setInput(minimumDistance);
    _wallFollowPID->Compute();

    return _wallFollowPID->output();
}

LWheelSpeeds LWallFollowController::wallFollowWheelSpeedsForPIDOutput(double pidOutput) {
    int leftWheelSpeed = 255;
    int rightWheelSpeed = 255;
    
    if (pidOutput > 0) {
        //turn right
        rightWheelSpeed -= pidOutput;
    }
    else {
        //turn left
        leftWheelSpeed += pidOutput;
    }
    
    return {leftWheelSpeed, rightWheelSpeed};
}

#pragma mark -
